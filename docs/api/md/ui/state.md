# API Documentation: `state.lm`

## Overview

std/ui/state.lm
Type-Safe Reactive State Management (Zero `any` via Staged Frame Templates)

## Symbols

- **Function**: [`register_dirty_notifier`](#register_dirty_notifier)
- **Function**: [`mark_element_dirty_signal`](#mark_element_dirty_signal)
- **Function**: [`batch_begin`](#batch_begin)
- **Function**: [`batch_end`](#batch_end)
- **Function**: [`batch_updates`](#batch_updates)
- **Frame**: [`SignalNode`](#SignalNode)
- **Frame**: [`Signal`](#Signal)
- **Frame**: [`ComputedSignal`](#ComputedSignal)
- **Frame**: [`Effect`](#Effect)
- **Function**: [`effect`](#effect)
- **Function**: [`effect_with_cleanup`](#effect_with_cleanup)
- **Function**: [`dispose_all_effects`](#dispose_all_effects)
- **Frame**: [`BoolSignal`](#BoolSignal)
- **Frame**: [`IntSignal`](#IntSignal)
- **Frame**: [`FloatSignal`](#FloatSignal)
- **Frame**: [`StrSignal`](#StrSignal)
- **Frame**: [`ComputedStr`](#ComputedStr)
- **Function**: [`signal_bool`](#signal_bool)
- **Function**: [`signal_int`](#signal_int)
- **Function**: [`signal_float`](#signal_float)
- **Function**: [`signal_str`](#signal_str)
- **Function**: [`computed_str`](#computed_str)
- **Function**: [`bind_text`](#bind_text)
- **Function**: [`bind_bool`](#bind_bool)
- **Function**: [`bind_float`](#bind_float)
- **Function**: [`bind_int`](#bind_int)

---

### `register_dirty_notifier` <a id="register_dirty_notifier"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn register_dirty_notifier(cb: function): nil
```

---

### `mark_element_dirty_signal` <a id="mark_element_dirty_signal"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn mark_element_dirty_signal(): nil
```

---

### `batch_begin` <a id="batch_begin"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn batch_begin(): nil
```

---

### `batch_end` <a id="batch_end"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn batch_end(): nil
```

---

### `batch_updates` <a id="batch_updates"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn batch_updates(updates: function): nil
```

---

### `SignalNode` <a id="SignalNode"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame SignalNode
```

#### Members

- `var pub listeners: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn attach(cb: function): nil` *(method)*
- `pub fn notify(): nil` *(method)*
- `pub fn listener_count(): int` *(method)*

---

### `Signal` <a id="Signal"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Signal
```

#### Members

- `var pub value: T` *(field)*
- `var pub subscribers: list` *(field)*
- `var pub node: SignalNode` *(field)*
- `pub init(init_val: T)` *(constructor)*
- `pub fn subscriber_count(): int` *(method)*
- `pub fn subscribe(callback: function): nil` *(method)*
- `pub fn get(): T` *(method)*
- `pub fn set(new_val: T): nil` *(method)*

---

### `ComputedSignal` <a id="ComputedSignal"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ComputedSignal
```

#### Members

- `var pub compute_fn: function` *(field)*
- `var pub value: T` *(field)*
- `var pub is_dirty: int` *(field)*
- `var pub subscribers: list` *(field)*
- `var pub dependencies: list` *(field)*
- `var pub node: SignalNode` *(field)*
- `pub init(compute: function, deps: list)` *(constructor)*
- `pub fn subscribe(callback: function): nil` *(method)*
- `pub fn dep_count(): int` *(method)*
- `pub fn get(): T` *(method)*
- `pub fn poke(): nil` *(method)*

---

### `Effect` <a id="Effect"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Effect
```

#### Members

- `var pub effect_fn: function` *(field)*
- `var pub cleanup_fn: function?` *(field)*
- `var pub is_active: int` *(field)*
- `var pub dependencies: list` *(field)*
- `pub init(user_effect: function, deps: list)` *(constructor)*
- `pub fn dispose(): nil` *(method)*
- `pub fn dep_count(): int` *(method)*
- `fn _effect_dep_changed(): nil` *(method)*

---

### `effect` <a id="effect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn effect(effect_fn: function, deps: list): Effect
```

---

### `effect_with_cleanup` <a id="effect_with_cleanup"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn effect_with_cleanup(effect_fn: function, cleanup_fn: function, deps: list): Effect
```

---

### `dispose_all_effects` <a id="dispose_all_effects"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispose_all_effects(): nil
```

---

### `BoolSignal` <a id="BoolSignal"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame BoolSignal
```

#### Members

- `var pub value: bool` *(field)*
- `var pub subscribers: list` *(field)*
- `var pub node: SignalNode` *(field)*
- `pub init()` *(constructor)*
- `pub fn subscribe(callback: function): nil` *(method)*
- `pub fn get(): bool` *(method)*
- `pub fn set(new_val: bool): nil` *(method)*

---

### `IntSignal` <a id="IntSignal"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame IntSignal
```

#### Members

- `var pub value: int` *(field)*
- `var pub subscribers: list` *(field)*
- `var pub node: SignalNode` *(field)*
- `pub init()` *(constructor)*
- `pub fn subscribe(callback: function): nil` *(method)*
- `pub fn get(): int` *(method)*
- `pub fn set(new_val: int): nil` *(method)*

---

### `FloatSignal` <a id="FloatSignal"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame FloatSignal
```

#### Members

- `var pub value: float` *(field)*
- `var pub subscribers: list` *(field)*
- `var pub node: SignalNode` *(field)*
- `pub init()` *(constructor)*
- `pub fn subscribe(callback: function): nil` *(method)*
- `pub fn get(): float` *(method)*
- `pub fn set(new_val: float): nil` *(method)*

---

### `StrSignal` <a id="StrSignal"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame StrSignal
```

#### Members

- `var pub value: str` *(field)*
- `var pub subscribers: list` *(field)*
- `var pub node: SignalNode` *(field)*
- `pub init()` *(constructor)*
- `pub fn subscribe(callback: function): nil` *(method)*
- `pub fn get(): str` *(method)*
- `pub fn set(new_val: str): nil` *(method)*

---

### `ComputedStr` <a id="ComputedStr"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ComputedStr
```

#### Members

- `var pub compute_fn: function` *(field)*
- `var pub value: str` *(field)*
- `var pub is_dirty: int` *(field)*
- `var pub subscribers: list` *(field)*
- `var pub dependencies: list` *(field)*
- `var pub node: SignalNode` *(field)*
- `pub init(compute: function, deps: list)` *(constructor)*
- `pub fn subscribe(callback: function): nil` *(method)*
- `pub fn get(): str` *(method)*
- `pub fn poke(): nil` *(method)*

---

### `signal_bool` <a id="signal_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn signal_bool(init_val: bool): BoolSignal
```

---

### `signal_int` <a id="signal_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn signal_int(init_val: int): IntSignal
```

---

### `signal_float` <a id="signal_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn signal_float(init_val: float): FloatSignal
```

---

### `signal_str` <a id="signal_str"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn signal_str(init_val: str): StrSignal
```

---

### `computed_str` <a id="computed_str"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn computed_str(compute_fn: function, deps: list): ComputedStr
```

---

### `bind_text` <a id="bind_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_text(sig: StrSignal, widget_mutator: function): nil
```

---

### `bind_bool` <a id="bind_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_bool(sig: BoolSignal, widget_mutator: function): nil
```

---

### `bind_float` <a id="bind_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_float(sig: FloatSignal, widget_mutator: function): nil
```

---

### `bind_int` <a id="bind_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_int(sig: IntSignal, widget_mutator: function): nil
```

---

