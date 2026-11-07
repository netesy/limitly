# API Documentation: `state.lm`

## Overview

── State Management with Batch Updates ──────────────────────────────────────
Dirty notification callback — set by context.lm at startup via register_dirty_notifier()

## Symbols

- **Function**: [`register_dirty_notifier`](#register_dirty_notifier)
- **Trait**: [`Reactive`](#Reactive)
- **Frame**: [`Signal`](#Signal)
- **Frame**: [`ComputedSignal`](#ComputedSignal)
- **Frame**: [`Effect`](#Effect)
- **Function**: [`signal`](#signal)
- **Function**: [`signal_bool`](#signal_bool)
- **Function**: [`signal_int`](#signal_int)
- **Function**: [`signal_float`](#signal_float)
- **Function**: [`signal_str`](#signal_str)
- **Function**: [`computed`](#computed)
- **Function**: [`effect`](#effect)
- **Function**: [`effect_with_cleanup`](#effect_with_cleanup)
- **Function**: [`dispose_all_effects`](#dispose_all_effects)
- **Function**: [`batch_begin`](#batch_begin)
- **Function**: [`batch_end`](#batch_end)
- **Function**: [`mark_element_dirty_signal`](#mark_element_dirty_signal)
- **Function**: [`batch_updates`](#batch_updates)
- **Function**: [`bind_text`](#bind_text)
- **Function**: [`bind_bool`](#bind_bool)
- **Function**: [`bind_float`](#bind_float)
- **Function**: [`bind_int`](#bind_int)
- **Function**: [`bind_two_way_text`](#bind_two_way_text)
- **Function**: [`bind_two_way_bool`](#bind_two_way_bool)
- **Function**: [`bind_two_way_float`](#bind_two_way_float)

---

### `register_dirty_notifier` <a id="register_dirty_notifier"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn register_dirty_notifier(cb: function): nil
```

---

### `Reactive` <a id="Reactive"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Reactive
```

#### Members

- `fn get(): any` *(method requirement)*
- `fn subscribe(callback: function): nil` *(method requirement)*

---

### `Signal` <a id="Signal"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Signal: Reactive
```

#### Members

- `var pub value: any` *(field)*
- `pub init(init_val: any)` *(constructor)*
- `pub fn subscriber_count(): int` *(method)*
- `pub fn get(): any` *(method)*
- `pub fn set(new_val: any): nil` *(method)*

---

### `ComputedSignal` <a id="ComputedSignal"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ComputedSignal: Reactive
```

#### Members

- `var pub compute_fn: function` *(field)*
- `var pub value: any` *(field)*
- `var pub is_dirty: int` *(field)*
- `pub init(compute: function, deps: list)` *(constructor)*
- `pub fn get(): any` *(method)*
- `pub fn dep_count(): int` *(method)*
- `pub fn poke(): nil` *(method)*
- `fn _computed_dep_changed(new_val: any): nil` *(method)*

---

### `Effect` <a id="Effect"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Effect
```

#### Members

- `var pub effect_fn: function` *(field)*
- `var pub cleanup_fn: function` *(field)*
- `var pub is_active: int` *(field)*
- `pub init(user_effect: function, deps: list)` *(constructor)*
- `pub fn dispose(): nil` *(method)*
- `pub fn dep_count(): int` *(method)*
- `fn _effect_dep_changed(new_val: any): nil` *(method)*

---

### `signal` <a id="signal"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn signal(init_val): Signal
```

---

### `signal_bool` <a id="signal_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn signal_bool(init_val: bool): Signal
```

---

### `signal_int` <a id="signal_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn signal_int(init_val: int): Signal
```

---

### `signal_float` <a id="signal_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn signal_float(init_val: float): Signal
```

---

### `signal_str` <a id="signal_str"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn signal_str(init_val: str): Signal
```

---

### `computed` <a id="computed"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn computed(compute_fn: function, deps: list): ComputedSignal
```

Computed signal (derived state)

---

### `effect` <a id="effect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn effect(effect_fn: function, deps: list): Effect
```

Effect (side effect that runs when dependencies change)

---

### `effect_with_cleanup` <a id="effect_with_cleanup"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn effect_with_cleanup(effect_fn: function, cleanup_fn: function, deps: list): Effect
```

Effect with cleanup

---

### `dispose_all_effects` <a id="dispose_all_effects"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispose_all_effects(): nil
```

Dispose all active effects

---

### `batch_begin` <a id="batch_begin"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn batch_begin(): nil
```

Batch state updates (debounces dirty marking)

---

### `batch_end` <a id="batch_end"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn batch_end(): nil
```

---

### `mark_element_dirty_signal` <a id="mark_element_dirty_signal"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn mark_element_dirty_signal(): nil
```

Notify the UI context that something changed

---

### `batch_updates` <a id="batch_updates"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn batch_updates(updates: function): nil
```

Batch update pattern

---

### `bind_text` <a id="bind_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_text(sig: Signal, widget_mutator: function): nil
```

── Widget Signal Binding Helpers ───────────────────────────────────────────
Bind a signal's value to a widget's text property

---

### `bind_bool` <a id="bind_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_bool(sig: Signal, widget_mutator: function): nil
```

Bind a signal's value to a widget's boolean property (e.g., is_checked, is_enabled)

---

### `bind_float` <a id="bind_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_float(sig: Signal, widget_mutator: function): nil
```

Bind a signal's value to a widget's float property (e.g., slider_val, opacity_val)

---

### `bind_int` <a id="bind_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_int(sig: Signal, widget_mutator: function): nil
```

Bind a signal's value to a widget's int property

---

### `bind_two_way_text` <a id="bind_two_way_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_two_way_text(sig: Signal, get_widget_fn: function, set_widget_fn: function): function
```

Two-way binding: signal to widget and widget to signal
Returns a cleanup function to unsubscribe

---

### `bind_two_way_bool` <a id="bind_two_way_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_two_way_bool(sig: Signal, get_widget_fn: function, set_widget_fn: function): function
```

Two-way binding for boolean (checkbox, toggle)

---

### `bind_two_way_float` <a id="bind_two_way_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_two_way_float(sig: Signal, get_widget_fn: function, set_widget_fn: function): function
```

Two-way binding for float (slider)

---

