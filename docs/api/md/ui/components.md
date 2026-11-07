# API Documentation: `components.lm`

## Overview

std/ui/components.lm
Zero-Cost Component Embedding Architecture for Lymar Retained UI.

Replaces monolithic 60-field God objects with fine-grained, composable
component frames utilizing Lymar's `embed` mechanism.
Flattened fields have zero pointer overhead; promoted methods provide
fluent builder ergonomics without wrapper allocations.

Interaction slots are typed optional functions -- `(fn(): nil)?` -- never
raw `any`, and every invocation routes through a fallible `EventResult?`
pipeline so call sites carry no nil-check ladders.

## Symbols

- **Trait**: [`Fluent`](#Fluent)
- **Frame**: [`LayoutMetrics`](#LayoutMetrics)
- **Type Alias**: [`LayoutBox`](#LayoutBox)
- **Frame**: [`VisualStyle`](#VisualStyle)
- **Frame**: [`Clickable`](#Clickable)
- **Frame**: [`Changeable`](#Changeable)
- **Frame**: [`Focusable`](#Focusable)
- **Frame**: [`Button`](#Button)
- **Frame**: [`Label`](#Label)
- **Frame**: [`Slider`](#Slider)
- **Frame**: [`Checkbox`](#Checkbox)
- **Frame**: [`TextInput`](#TextInput)
- **Frame**: [`ProgressBar`](#ProgressBar)
- **Frame**: [`Container`](#Container)
- **Frame**: [`Spacer`](#Spacer)
- **Function**: [`column`](#column)
- **Function**: [`row`](#row)

---

### `Fluent` <a id="Fluent"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Fluent
```

#### Members

- `fn kind_name(): str` *(method requirement)*

---

### `LayoutMetrics` <a id="LayoutMetrics"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame LayoutMetrics
```

#### Members

- `var pub width_val: float` *(field)*
- `var pub height_val: float` *(field)*
- `var pub pad_l: float` *(field)*
- `var pub pad_t: float` *(field)*
- `var pub pad_r: float` *(field)*
- `var pub pad_b: float` *(field)*
- `var pub spacing_val: float` *(field)*
- `var pub flex_val: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_dimensions(w: float, h: float): nil` *(method)*
- `pub fn set_padding(p: float): nil` *(method)*

---

### `LayoutBox` <a id="LayoutBox"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type LayoutBox = LayoutMetrics
```

---

### `VisualStyle` <a id="VisualStyle"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame VisualStyle
```

#### Members

- `var pub bg: Color` *(field)*
- `var pub fg: Color` *(field)*
- `var pub radius: float` *(field)*
- `var pub opacity_val: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_colors(background: Color, foreground: Color): nil` *(method)*
- `pub fn set_radius(r: float): nil` *(method)*

---

### `Clickable` <a id="Clickable"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Clickable
```

#### Members

- `var pub is_pressed: bool` *(field)*
- `var pub is_hovered: bool` *(field)*
- `var pub on_click_action: function?` *(field)*
- `var pub click_count: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_on_click(action: function): nil` *(method)*
- `pub fn click(): EventResult?` *(method)*
- `pub fn trigger_click(): nil` *(method)*

---

### `Changeable` <a id="Changeable"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Changeable
```

#### Members

- `var pub on_change_action: function?` *(field)*
- `var pub change_count: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_on_change(action: function): nil` *(method)*
- `pub fn notify_change(): EventResult?` *(method)*

---

### `Focusable` <a id="Focusable"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Focusable
```

#### Members

- `var pub is_focused: bool` *(field)*
- `var pub cursor_pos: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn focus(): nil` *(method)*
- `pub fn blur(): nil` *(method)*

---

### `Button` <a id="Button"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Button: Fluent
```

#### Members

- `var pub label: str` *(field)*
- `pub init(text: str)` *(constructor)*
- `pub fn kind_name(): str` *(method)*
- `pub fn background(c: Color): Button` *(method)*
- `pub fn foreground(c: Color): Button` *(method)*
- `pub fn padding(p: float): Button` *(method)*
- `pub fn corner_radius(r: float): Button` *(method)*
- `pub fn width(w: float): Button` *(method)*
- `pub fn height(h: float): Button` *(method)*

---

### `Label` <a id="Label"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Label: Fluent
```

#### Members

- `var pub text: str` *(field)*
- `var pub font_size_val: float` *(field)*
- `var pub is_bold: bool` *(field)*
- `pub init(txt: str)` *(constructor)*
- `pub fn kind_name(): str` *(method)*
- `pub fn color(c: Color): Label` *(method)*
- `pub fn font_size(sz: float): Label` *(method)*
- `pub fn bold(): Label` *(method)*

---

### `Slider` <a id="Slider"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Slider: Fluent
```

#### Members

- `var pub value: float` *(field)*
- `var pub min_val: float` *(field)*
- `var pub max_val: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind_name(): str` *(method)*
- `pub fn set_range(min_v: float, max_v: float): Slider` *(method)*
- `pub fn on_change(action: function): Slider` *(method)*
- `pub fn set_value(v: float): Slider` *(method)*
- `pub fn value_of(v: float): Slider` *(method)*
- `pub fn ratio(): float` *(method)*

---

### `Checkbox` <a id="Checkbox"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Checkbox: Fluent
```

#### Members

- `var pub label: str` *(field)*
- `var pub is_checked: bool` *(field)*
- `pub init(text: str)` *(constructor)*
- `pub fn kind_name(): str` *(method)*
- `pub fn on_change(action: function): Checkbox` *(method)*
- `pub fn toggle(): EventResult?` *(method)*

---

### `TextInput` <a id="TextInput"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TextInput: Fluent
```

#### Members

- `var pub text: str` *(field)*
- `var pub placeholder: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind_name(): str` *(method)*
- `pub fn on_change(action: function): TextInput` *(method)*
- `pub fn set_text(next: str): TextInput` *(method)*
- `pub fn display_text(): str` *(method)*

---

### `ProgressBar` <a id="ProgressBar"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ProgressBar: Fluent
```

#### Members

- `var pub value: float` *(field)*
- `var pub max_val: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind_name(): str` *(method)*
- `pub fn set_progress(v: float): ProgressBar` *(method)*
- `pub fn ratio(): float` *(method)*

---

### `Container` <a id="Container"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Container: Fluent
```

#### Members

- `var pub children: list` *(field)*
- `var pub flow: Flow` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind_name(): str` *(method)*
- `pub fn add(c: Fluent): Container` *(method)*
- `pub fn layout(f: Flow): Container` *(method)*
- `pub fn is_vertical(): bool` *(method)*
- `pub fn background(c: Color): Container` *(method)*
- `pub fn padding(p: float): Container` *(method)*
- `pub fn spacing(s: float): Container` *(method)*

---

### `Spacer` <a id="Spacer"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Spacer: Fluent
```

#### Members

- `pub init()` *(constructor)*
- `pub fn kind_name(): str` *(method)*
- `pub fn flex(f: float): Spacer` *(method)*

---

### `column` <a id="column"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn column(children: list = ...): Container
```

---

### `row` <a id="row"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn row(children: list = ...): Container
```

---

