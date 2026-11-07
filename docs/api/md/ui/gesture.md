# API Documentation: `gesture.lm`

## Overview

std/ui/gesture - Gesture recognition and handling

## Symbols

- **Frame**: [`GestureState`](#GestureState)
- **Function**: [`detect_tap`](#detect_tap)
- **Function**: [`detect_long_press`](#detect_long_press)
- **Function**: [`detect_double_tap`](#detect_double_tap)
- **Function**: [`detect_swipe`](#detect_swipe)
- **Function**: [`detect_pan`](#detect_pan)
- **Function**: [`update_gesture_on_pointer_down`](#update_gesture_on_pointer_down)
- **Function**: [`update_gesture_on_pointer_move`](#update_gesture_on_pointer_move)
- **Function**: [`update_gesture_on_pointer_up`](#update_gesture_on_pointer_up)
- **Function**: [`get_last_gesture`](#get_last_gesture)

---

### `GestureState` <a id="GestureState"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GestureState
```

Gesture state tracking

#### Members

- `var pub pointer_down_time: float` *(field)*
- `var pub pointer_down_x: float` *(field)*
- `var pub pointer_down_y: float` *(field)*
- `var pub last_tap_time: float` *(field)*
- `var pub tap_count: int` *(field)*
- `var pub is_long_press_active: int` *(field)*
- `pub init()` *(constructor)*

---

### `detect_tap` <a id="detect_tap"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn detect_tap(child: ui_types.Widget, on_tap): ui_types.Widget
```

Detect and handle tap gesture

---

### `detect_long_press` <a id="detect_long_press"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn detect_long_press(child: ui_types.Widget, on_long_press): ui_types.Widget
```

Detect and handle long press (hold for 500ms)

---

### `detect_double_tap` <a id="detect_double_tap"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn detect_double_tap(child: ui_types.Widget, on_double_tap): ui_types.Widget
```

Detect double tap (two taps within 300ms)

---

### `detect_swipe` <a id="detect_swipe"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn detect_swipe(child: ui_types.Widget, on_swipe): ui_types.Widget
```

Detect swipe gesture (fast drag in one direction)

---

### `detect_pan` <a id="detect_pan"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn detect_pan(child: ui_types.Widget, on_pan): ui_types.Widget
```

Detect pan/drag gesture (continuous movement)

---

### `update_gesture_on_pointer_down` <a id="update_gesture_on_pointer_down"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn update_gesture_on_pointer_down(gesture_key: str, x: float, y: float, current_time: float): nil
```

Update gesture state based on pointer down event.
`key in dict` is not an operator in Lymar - `in` only appears in `iter` and
`for` clauses. A missing key reads back as nil, so presence is a nil check.

---

### `update_gesture_on_pointer_move` <a id="update_gesture_on_pointer_move"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn update_gesture_on_pointer_move(gesture_key: str, x: float, y: float): float
```

Update gesture state based on pointer move (for swipe/pan detection)

---

### `update_gesture_on_pointer_up` <a id="update_gesture_on_pointer_up"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn update_gesture_on_pointer_up(gesture_key: str, current_time: float): int
```

Update gesture state based on pointer up (for long press and tap)

---

### `get_last_gesture` <a id="get_last_gesture"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_last_gesture(gesture_key: str): str
```

Get last detected gesture type

---

