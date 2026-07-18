# UI Framework LIR Lowering Strategy

## Overview

The Limitly UI framework lowers declarative UI blueprints through a three-stage Multi-Tree Pipeline that compiles directly to LIR instructions for the Register VM and AOT compilation. This document describes the lowering strategy, memory layouts, and compiler optimizations.

## Multi-Tree Pipeline Architecture

### Layer 1: Blueprint (Stack-Allocated, Immutable)

Blueprints are short-lived, stack-allocated structures that represent the declarative UI tree. They are lowered immediately during the application event loop driver.

**Memory Layout:**
```
Blueprint (stack frame):
  - variant: ElementVariant (tagged union, 8 bytes)
  - constraints: LayoutConstraint[] (pointer + length, 16 bytes)
  - children: Blueprint[] (pointer + length, 16 bytes)
  Total: 40 bytes (stack-allocated)
```

**LIR Lowering:**
```limit
// Blueprint construction
vstack([text("Hello"), button("Click")])

// Lowers to:
%r0 = LoadConst ContainerData(axis=Vertical)
%r1 = LoadConst TextData(content="Hello")
%r2 = MakeEnum(Text, %r1)
%r3 = LoadConst ButtonData(label="Click")
%r4 = MakeEnum(Button, %r3)
%r5 = AllocArray(2)  // children array
%r6 = StoreArray(%r5, 0, %r2)
%r7 = StoreArray(%r5, 1, %r4)
%r8 = MakeEnum(Container, %r0)
%r9 = MakeBlueprint(variant=%r8, children=%r5)
```

### Layer 2: Retained Element Tree (Heap-Allocated, Persistent)

The retained element tree is a persistent, heap-allocated structure that tracks UI state across frames. Elements use RAII destructors to automatically clean up native resources when they go out of scope.

**Memory Layout:**
```
Element (heap-allocated):
  - id: ElementId (8 bytes)
  - parent_id: ElementId (8 bytes)
  - variant: ElementVariant (tagged union, 8 bytes)
  - state: ElementState (tagged union, 8 bytes)
  - constraints: LayoutConstraint[] (pointer + length, 16 bytes)
  - metrics: LayoutMetrics (32 bytes)
  - visible: bool (1 byte + 7 padding)
  - children: ElementId[] (pointer + length, 16 bytes)
  - event_tokens: EventToken[] (pointer + length, 16 bytes)
  - native_resources: ResourceId[] (pointer + length, 16 bytes)
  Total: 129 bytes (heap-allocated, 16-byte aligned)
```

**RAII Destructor Lowering:**
```limit
// Element goes out of scope
// Compiler generates:
%r0 = LoadElement(element_ptr)
%r1 = GetField(%r0, native_resources)
%r2 = GetArrayLength(%r1)
%r3 = Call cleanup_element_resources(%r0)
%r4 = Call unregister_element_dependencies(%r0)
%r5 = Call delete_from_element_map(element_id)
```

**Sum Type Evaluation:**
ElementVariant is a tagged union. The compiler computes exact byte offsets at compile-time:

```limit
// ElementVariant layout (computed at compile-time):
// Tag: 0 bytes (stored in low 3 bits of pointer)
// ContainerData: 0-64 bytes
// TextData: 64-128 bytes
// ButtonData: 128-192 bytes
// etc.

// Pattern matching lowers to jump table:
%r0 = LoadElementVariant(element_ptr)
%r1 = GetTag(%r0)  // Extract tag from low 3 bits
JumpTable(%r1, label_container, label_text, label_button, ...)

label_container:
  %r2 = GetPayload(%r0, offset=0)  // Direct byte offset
  // Process container
  Jump end_match

label_text:
  %r2 = GetPayload(%r0, offset=64)  // Direct byte offset
  // Process text
  Jump end_match
```

### Layer 3: Render Command Stream (Flattened, Byte-Packed)

The render command stream is a flattened sequence of draw actions packed into byte-buffers for zero-overhead dispatch through the graphics context.

**Memory Layout:**
```
RenderCommand (byte-packed):
  - command_type: u8 (1 byte)
  - padding: 3 bytes
  - payload: union (32 bytes, variant-specific)
  Total: 36 bytes (cache-line friendly)
```

**Command Stream Buffer:**
```
RenderBuffer (heap-allocated):
  - commands: RenderCommand[] (pointer + length, 16 bytes)
  - capacity: usize (8 bytes)
  - count: usize (8 bytes)
  Total: 32 bytes + command_data
```

**LIR Lowering for Command Dispatch:**
```limit
// Flatten element tree to command stream
%r0 = LoadElement(root_id)
%r1 = GetField(%r0, metrics)
%r2 = GetField(%r1, position)
%r3 = GetField(%r1, size)
%r4 = MakeDrawRectCommand(rect, color)
%r5 = MakeEnum(DrawRect, %r4)
%r6 = AppendToCommandStream(%r5)
%r7 = Call submit_render_commands(command_stream)
```

## Reactive State Management

### State Container Layout

State containers use Sum Types to handle multi-variant user data payloads without generics:

```
StateContainer (heap-allocated):
  - id: int (8 bytes)
  - value: StateValue (tagged union, 8 bytes)
  - subscribers: ElementId[] (pointer + length, 16 bytes)
  - version: int (8 bytes)
  Total: 40 bytes (heap-allocated)
```

**StateValue Sum Type Layout:**
```
StateValue (tagged union):
  - Tag: 3 bits (stored in pointer low bits)
  - IntState: int payload (8 bytes)
  - FloatState: float payload (8 bytes)
  - StringState: str pointer (8 bytes)
  - BoolState: bool (1 byte + padding)
  - ColorState: Color struct (16 bytes)
  - SizeState: Size struct (16 bytes)
  - PointState: Point struct (16 bytes)
  - CustomState: (ptr, size) pair (16 bytes)
```

**State Update Lowering:**
```limit
// set_state(state_id, new_value)
%r0 = LoadStateContainer(state_id)
%r1 = LoadField(%r0, value)
%r2 = LoadField(%r0, subscribers)
%r3 = GetArrayLength(%r2)
%r4 = StoreField(%r0, value, new_value)
%r5 = LoadField(%r0, version)
%r6 = Add(%r5, 1)
%r7 = StoreField(%r0, version, %r6)

// Notify subscribers
%r8 = Call mark_element_dirty(subscriber_id)
%r9 = MakeChangeEvent(element_id, old_value, new_value)
%r10 = AppendToEventQueue(%r9)
```

## Event Token System

Closures and events use event tokens instead of raw pointers to avoid dangling references across frame updates.

**Event Token Layout:**
```
EventToken: int (8 bytes)
  - High 32 bits: callback registry index
  - Low 32 bits: frame ID for validation
```

**Callback Registration Lowering:**
```limit
// register_event_handler(element_id, event_type, callback)
%r0 = LoadElement(element_id)
%r1 = MakeEventHandler(element_id, event_type, callback_token)
%r2 = AppendToEventHandlerRegistry(%r1)
%r3 = GetField(%r0, event_tokens)
%r4 = AppendToArray(%r3, handler_token)
%r5 = StoreField(%r0, event_tokens, %r4)
```

**Callback Invocation Lowering:**
```limit
// invoke_callback(token, event)
%r0 = ExtractCallbackIndex(token)
%r1 = ValidateFrameId(token)
%r2 = LoadCallbackFromRegistry(%r0)
%r3 = Call enter_callback()  // Stack frame isolation
%r4 = Call %r2(event)  // Dynamic invocation
%r5 = Call leave_callback()  // Restore VM state
```

## Layout Pass Lowering

The layout pass computes element metrics using a single-threaded, cache-local algorithm that avoids virtual dispatch.

**Layout Metrics Layout:**
```
LayoutMetrics:
  - position: Point (16 bytes)
  - size: Size (16 bytes)
  - baseline: float (8 bytes)
  Total: 40 bytes
```

**Layout Computation Lowering:**
```limit
// compute_element_layout(element_id, position, available_size)
%r0 = LoadElement(element_id)
%r1 = GetField(%r0, constraints)
%r2 = GetField(%r0, variant)
%r3 = GetTag(%r2)
JumpTable(%r3, layout_container, layout_text, layout_button, ...)

layout_container:
  %r4 = GetPayload(%r2, offset=0)
  %r5 = GetField(%r4, axis)
  %r6 = GetField(%r4, spacing)
  %r7 = GetField(%r4, padding)
  // Compute child layouts iteratively
  %r8 = GetField(%r0, children)
  %r9 = GetArrayLength(%r8)
  %r10 = LoopStart(%r9)
  // ... layout computation loop
  Jump end_layout

layout_text:
  %r4 = GetPayload(%r2, offset=64)
  %r5 = GetField(%r4, font_size)
  %r6 = GetField(%r4, content)
  %r7 = Call measure_text(%r6, %r5)
  // Store metrics
  Jump end_layout
```

## Render Pass Lowering

The render pass flattens the element tree into a sequential command stream that dispatches directly to the graphics context.

**Command Dispatch Lowering:**
```limit
// render_element(element_id, offset)
%r0 = LoadElement(element_id)
%r1 = GetField(%r0, variant)
%r2 = GetTag(%r1)
%r3 = GetField(%r0, metrics)
%r4 = GetField(%r3, position)
%r5 = Add(%r4, offset)
%r6 = GetField(%r3, size)
%r7 = MakeRect(%r5, %r6)
JumpTable(%r2, render_container, render_text, render_button, ...)

render_container:
  %r8 = GetPayload(%r1, offset=0)
  %r9 = GetField(%r8, background)
  %r10 = GetField(%r8, border)
  %r11 = GetField(%r8, clip_content)
  // Emit draw commands
  %r12 = MakeDrawRectCommand(%r7, %r9)
  %r13 = AppendToCommandStream(%r12)
  // Render children recursively
  Jump end_render

render_button:
  %r8 = GetPayload(%r1, offset=128)
  %r9 = GetField(%r8, background)
  %r10 = GetField(%r0, state)
  // Select color based on state
  %r11 = MatchState(%r10, Idle->%r9, Hovered->hover_bg, Pressed->pressed_bg)
  %r12 = MakeDrawRectCommand(%r7, %r11)
  %r13 = AppendToCommandStream(%r12)
  Jump end_render
```

## Memory Alignment and Fragmentation Prevention

All heap allocations use explicit alignment helpers to prevent fragmentation:

```limit
// Alignment helpers
fn align_up(ptr: pubptr, alignment: int): pubptr {
    var mask: int = alignment - 1
    return (ptr + mask) & ~mask
}

fn verify_pointer_alignment(ptr: pubptr, alignment: int): int {
    return (ptr & (alignment - 1)) == 0
}
```

**Allocation Lowering:**
```limit
// allocate_element()
%r0 = Call sizeof(Element)  // 129 bytes
%r1 = Add(%r0, 15)  // Round up to 16-byte alignment
%r2 = And(%r1, ~15)
%r3 = Call ffi_alloc(%r2)
%r4 = Call verify_pointer_alignment(%r3, 16)
%r5 = Call ffi_memset(%r3, 0, %r2)
%r6 = StoreElementId(%r3, next_element_id)
```

## AOT Compilation Optimizations

For AOT compilation, the UI framework leverages compile-time Sum Type evaluation to emit sequential memory-store blocks instead of runtime virtual dispatch:

**Compile-Time Tag Resolution:**
```cpp
// builtin_functions.cpp - Sum Type lowering
void execute_make_enum(const LIR_Inst* pc) {
    // Compute exact byte offset at compile-time based on tag
    int tag = to_int(registers[pc->a]);
    size_t offset = compute_enum_tag_offset(tag);
    
    // Direct byte store instead of virtual dispatch
    void* dest = UNBOX_PTR(registers[pc->dst]) + offset;
    memcpy(dest, UNBOX_PTR(registers[pc->b]), get_enum_payload_size(tag));
}
```

**Jump Table Generation:**
```cpp
// Pattern matching lowers to jump table with computed offsets
void execute_get_tag(const LIR_Inst* pc) {
    void* enum_ptr = UNBOX_PTR(registers[pc->a]);
    uint8_t tag = *(uint8_t*)enum_ptr & TAG_MASK;
    registers[pc->dst] = BOX_INT(tag);
}

void execute_get_payload(const LIR_Inst* pc) {
    void* enum_ptr = UNBOX_PTR(registers[pc->a]);
    uint8_t tag = *(uint8_t*)enum_ptr & TAG_MASK;
    size_t offset = get_enum_payload_offset(tag);
    registers[pc->dst] = BOX_PTR((char*)enum_ptr + offset);
}
```

## Integration with std::app Event Loop

The UI framework integrates with the std::app event loop driver through the frame_update callback:

```limit
// Application setup
fn main(): void {
    var config: app.WindowConfig = app.default_window_config()
    config.title = "Limitly UI Application"
    app.app_init(config)
    
    ui.ui_init()
    
    var state_id: int = ui.create_state(ui.StateValue.IntState(0))
    
    app.set_frame_callback(fn(delta_time: float): void {
        ui.frame_update(delta_time)
    })
    
    app.app_run()
    
    ui.ui_shutdown()
    app.app_shutdown()
}
```

**Frame Update Lowering:**
```limit
// frame_update(delta_time)
%r0 = Call process_events()
%r1 = LoadUIContextDirty()
%r2 = BranchIfNot(%r1, skip_layout)
%r3 = Call get_window_width()
%r4 = Call get_window_height()
%r5 = Call layout_pass(%r3, %r4)
%r6 = StoreUIContextDirty(0)
skip_layout:
%r7 = Call render_pass()
%r8 = Call submit_render_commands(%r7)
```

## Summary

The Limitly UI framework lowers to efficient LIR through:
1. **Stack-allocated blueprints** for immediate resolution in the event loop
2. **Heap-allocated retained tree** with RAII destructors for automatic cleanup
3. **Flattened command stream** for zero-overhead graphics dispatch
4. **Sum Type pattern matching** with compile-time tag resolution
5. **Event token system** to avoid pointer capture in closures
6. **Explicit alignment helpers** to prevent memory fragmentation
7. **Single-threaded frame execution** for deterministic behavior

All lowering strategies avoid generics, hidden allocations, and virtual dispatch, relying instead on:
- Tagged unions with computed byte offsets
- Direct memory store operations
- Jump tables for pattern matching
- RAII destructors for cleanup
- Numeric IDs for dependency tracking
