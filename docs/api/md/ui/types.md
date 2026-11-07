# API Documentation: `types.lm`

## Overview

std.ui.types - Type definitions for Fluent, Retained UI System

## Symbols

- **Type Alias**: [`Align`](#Align)
- **Trait**: [`WidgetTrait`](#WidgetTrait)
- **Frame**: [`Point`](#Point)
- **Function**: [`point`](#point)
- **Frame**: [`Size`](#Size)
- **Function**: [`size`](#size)
- **Frame**: [`Rect`](#Rect)
- **Function**: [`rect`](#rect)
- **Function**: [`axis_flag`](#axis_flag)
- **Function**: [`align_flag`](#align_flag)
- **Function**: [`weight_value`](#weight_value)
- **Function**: [`semantic_name`](#semantic_name)
- **Function**: [`mask_shape_name`](#mask_shape_name)
- **Function**: [`alert_kind_of`](#alert_kind_of)
- **Function**: [`dot_state_of`](#dot_state_of)
- **Function**: [`semantic_alert_name`](#semantic_alert_name)
- **Function**: [`dot_state_name`](#dot_state_name)
- **Function**: [`alert_kind_name`](#alert_kind_name)
- **Function**: [`dot_state_name`](#dot_state_name)
- **Frame**: [`Style`](#Style)
- **Function**: [`style`](#style)
- **Frame**: [`Widget`](#Widget)
- **Function**: [`text`](#text)
- **Function**: [`button`](#button)
- **Function**: [`textarea`](#textarea)
- **Function**: [`column`](#column)
- **Function**: [`row`](#row)
- **Function**: [`stack`](#stack)
- **Function**: [`spacer`](#spacer)
- **Function**: [`empty`](#empty)
- **Frame**: [`ContainerData`](#ContainerData)
- **Function**: [`container_data`](#container_data)
- **Frame**: [`TextData`](#TextData)
- **Function**: [`text_data`](#text_data)
- **Frame**: [`ButtonData`](#ButtonData)
- **Function**: [`button_data`](#button_data)
- **Frame**: [`LayoutConstraint`](#LayoutConstraint)
- **Frame**: [`Blueprint`](#Blueprint)
- **Function**: [`empty_constraints`](#empty_constraints)
- **Function**: [`empty_blueprints`](#empty_blueprints)
- **Function**: [`blueprint_add_constraint`](#blueprint_add_constraint)
- **Function**: [`blueprint_add_child`](#blueprint_add_child)
- **Function**: [`variant_code`](#variant_code)
- **Function**: [`blueprint_container`](#blueprint_container)
- **Function**: [`blueprint_text`](#blueprint_text)
- **Function**: [`blueprint_button`](#blueprint_button)
- **Function**: [`constraint`](#constraint)
- **Function**: [`select`](#select)
- **Function**: [`multi_select`](#multi_select)
- **Function**: [`link`](#link)
- **Function**: [`pie_chart`](#pie_chart)
- **Function**: [`table`](#table)
- **Function**: [`alert`](#alert)
- **Function**: [`alert_k`](#alert_k)
- **Function**: [`accordion`](#accordion)
- **Function**: [`bar_chart`](#bar_chart)
- **Function**: [`image`](#image)
- **Function**: [`plot_histogram`](#plot_histogram)
- **Function**: [`stat`](#stat)
- **Function**: [`timeline`](#timeline)
- **Function**: [`color_rgb8`](#color_rgb8)
- **Function**: [`range_slider`](#range_slider)
- **Function**: [`mask`](#mask)
- **Function**: [`mask_shape`](#mask_shape)
- **Function**: [`stepper`](#stepper)
- **Function**: [`calendar`](#calendar)
- **Function**: [`toggle`](#toggle)
- **Function**: [`line_chart`](#line_chart)
- **Function**: [`form_field`](#form_field)
- **Function**: [`tooltip`](#tooltip)
- **Function**: [`progress`](#progress)
- **Function**: [`tree_node`](#tree_node)
- **Function**: [`grid`](#grid)
- **Function**: [`radar_chart`](#radar_chart)
- **Function**: [`list`](#list)
- **Function**: [`badge`](#badge)
- **Function**: [`color_picker`](#color_picker)
- **Function**: [`file_input`](#file_input)
- **Function**: [`steps`](#steps)
- **Function**: [`toast`](#toast)
- **Function**: [`toast_k`](#toast_k)
- **Function**: [`filter`](#filter)
- **Function**: [`card`](#card)
- **Function**: [`scroll`](#scroll)
- **Function**: [`plot_lines`](#plot_lines)
- **Function**: [`text_area`](#text_area)
- **Function**: [`tabs`](#tabs)
- **Function**: [`polar_area_chart`](#polar_area_chart)
- **Function**: [`join`](#join)
- **Function**: [`dock`](#dock)
- **Function**: [`bubble_chart`](#bubble_chart)
- **Function**: [`scatter_chart`](#scatter_chart)
- **Function**: [`doughnut_chart`](#doughnut_chart)
- **Function**: [`overlay`](#overlay)
- **Function**: [`diff`](#diff)
- **Function**: [`checkbox`](#checkbox)
- **Function**: [`indicator`](#indicator)
- **Function**: [`indicator_k`](#indicator_k)
- **Function**: [`slider`](#slider)
- **Function**: [`input`](#input)

---

### `Align` <a id="Align"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type Align = Alignment
```

---

### `WidgetTrait` <a id="WidgetTrait"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait WidgetTrait
```

#### Members

- `fn mark_for_removal(): nil` *(method requirement)*

---

### `Point` <a id="Point"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Point
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*

---

### `point` <a id="point"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn point(x: float, y: float): Point
```

---

### `Size` <a id="Size"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Size
```

#### Members

- `var pub width: float` *(field)*
- `var pub height: float` *(field)*

---

### `size` <a id="size"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn size(w: float, h: float): Size
```

---

### `Rect` <a id="Rect"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Rect
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub w: float` *(field)*
- `var pub h: float` *(field)*

---

### `rect` <a id="rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rect(x: float, y: float, w: float, h: float): Rect
```

---

### `axis_flag` <a id="axis_flag"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn axis_flag(a: Axis): int
```

---

### `align_flag` <a id="align_flag"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn align_flag(a: Align): int
```

---

### `weight_value` <a id="weight_value"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn weight_value(w: Weight): int
```

---

### `semantic_name` <a id="semantic_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn semantic_name(s: Semantic): str
```

ARIA spelling for each semantic role.

---

### `mask_shape_name` <a id="mask_shape_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mask_shape_name(m: MaskShape): str
```

---

### `alert_kind_of` <a id="alert_kind_of"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alert_kind_of(type_val: str): AlertKind
```

Stringly-typed legacy spellings fold into the nominal domain through match.

---

### `dot_state_of` <a id="dot_state_of"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dot_state_of(status: str): DotState
```

---

### `semantic_alert_name` <a id="semantic_alert_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn semantic_alert_name(kind: AlertKind): str
```

---

### `dot_state_name` <a id="dot_state_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dot_state_name(state: DotState): str
```

---

### `alert_kind_name` <a id="alert_kind_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alert_kind_name(k: AlertKind): str
```

Canonical spellings written back into the legacy string lanes the renderers
still read, so the enum stays the single source of truth.

---

### `dot_state_name` <a id="dot_state_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dot_state_name(s: DotState): str
```

---

### `Style` <a id="Style"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Style
```

Reusable Style Model (LVGL / CSS Inspired)

#### Members

- `var pub has_bg: bool` *(field)*
- `var pub bg: Color` *(field)*
- `var pub has_fg: bool` *(field)*
- `var pub fg: Color` *(field)*
- `var pub has_padding: bool` *(field)*
- `var pub pad_l: float` *(field)*
- `var pub pad_t: float` *(field)*
- `var pub pad_r: float` *(field)*
- `var pub pad_b: float` *(field)*
- `var pub has_radius: bool` *(field)*
- `var pub radius: float` *(field)*
- `var pub has_font_size: bool` *(field)*
- `var pub font_size_val: float` *(field)*
- `var pub has_weight: bool` *(field)*
- `var pub weight_val: int` *(field)*
- `var pub has_spacing: bool` *(field)*
- `var pub spacing_val: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn background(c: Color): Style` *(method)*
- `pub fn foreground(c: Color): Style` *(method)*
- `pub fn color(c: Color): Style` *(method)*
- `pub fn padding(p: float): Style` *(method)*
- `pub fn padding_xy(x: float, y: float): Style` *(method)*
- `pub fn corner_radius(r: float): Style` *(method)*
- `pub fn font_size(s: float): Style` *(method)*
- `pub fn weight(w: int): Style` *(method)*
- `pub fn bold(): Style` *(method)*
- `pub fn spacing(s: float): Style` *(method)*
- `pub fn merge(other: Style): Style` *(method)*

---

### `style` <a id="style"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn style(): Style
```

---

### `Widget` <a id="Widget"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Widget: WidgetTrait
```

Unified Retained UI Node with Fluent Modifiers

#### Members

- `var pub children: list` *(field)*
- `pub init(k: WidgetKind)` *(constructor)*
- `pub fn color(c: Color): Widget` *(method)*
- `pub fn foreground(c: Color): Widget` *(method)*
- `pub fn background(c: Color): Widget` *(method)*
- `pub fn font_size(s: float): Widget` *(method)*
- `pub fn bold(): Widget` *(method)*
- `pub fn weight(w: Weight): Widget` *(method)*
- `pub fn padding(p: float): Widget` *(method)*
- `pub fn padding_xy(x: float, y: float): Widget` *(method)*
- `pub fn padding_rect(l: float, t: float, r: float, b: float): Widget` *(method)*
- `pub fn corner_radius(r: float): Widget` *(method)*
- `pub fn spacing(s: float): Widget` *(method)*
- `pub fn align(a: Align): Widget` *(method)*
- `pub fn width(w: float): Widget` *(method)*
- `pub fn height(h: float): Widget` *(method)*
- `pub fn size(w: float, h: float): Widget` *(method)*
- `pub fn on_click(act: any): Widget` *(method)*
- `pub fn pressed(s: Style): Widget` *(method)*
- `pub fn style(s: Style): Widget` *(method)*
- `pub fn min_width(w: float): Widget` *(method)*
- `pub fn max_width(w: float): Widget` *(method)*
- `pub fn min_height(h: float): Widget` *(method)*
- `pub fn max_height(h: float): Widget` *(method)*
- `pub fn grow(factor: float): Widget` *(method)*
- `pub fn shrink(factor: float): Widget` *(method)*
- `pub fn aspect_ratio(ratio: float): Widget` *(method)*
- `pub fn fill(): Widget` *(method)*
- `pub fn role(s: Semantic): Widget` *(method)*
- `pub fn role_str(r: str): Widget` *(method)*
- `pub fn aria_label(lbl: str): Widget` *(method)*
- `pub fn aria_hint(hint: str): Widget` *(method)*
- `pub fn aria_live(mode: str): Widget` *(method)*
- `pub fn focusable(): Widget` *(method)*
- `pub fn hidden_from_a11y(): Widget` *(method)*
- `pub fn opacity(o: float): Widget` *(method)*
- `pub fn scale(s: float): Widget` *(method)*
- `pub fn shadow(s: shadow.Shadow): Widget` *(method)*
- `pub fn animate(): Widget` *(method)*
- `pub fn spring(): Widget` *(method)*
- `pub fn transition(trans: anim.Transition): Widget` *(method)*
- `pub fn on_change(cb: any): Widget` *(method)*
- `pub fn checked(c: bool): Widget` *(method)*
- `pub fn disabled(): Widget` *(method)*
- `pub fn hover(s: Style): Widget` *(method)*
- `pub fn enter(t: anim.Transition): Widget` *(method)*
- `pub fn exit(t: anim.Transition): Widget` *(method)*
- `pub fn mark_for_removal(): nil` *(method)*
- `pub fn background_color(c: Color): Widget` *(method)*
- `pub fn bind_text(sig: any): Widget` *(method)*
- `pub fn bind_checked(sig: any): Widget` *(method)*
- `pub fn bind_value(sig: any): Widget` *(method)*
- `pub fn bind_enabled(sig: any): Widget` *(method)*

---

### `text` <a id="text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn text(content: str): Widget
```

Semantic Widget Constructors

---

### `button` <a id="button"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn button(label: str, on_click: any = ...): Widget
```

---

### `textarea` <a id="textarea"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn textarea(content: str): Widget
```

---

### `column` <a id="column"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn column(children: list): Widget
```

---

### `row` <a id="row"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn row(children: list): Widget
```

---

### `stack` <a id="stack"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stack(children: list): Widget
```

---

### `spacer` <a id="spacer"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn spacer(flex: float = ...): Widget
```

---

### `empty` <a id="empty"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn empty(): Widget
```

---

### `ContainerData` <a id="ContainerData"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ContainerData
```

Blueprint data structures

#### Members

- `var pub axis: Axis` *(field)*
- `var pub spacing: float` *(field)*
- `var pub padding: Rect` *(field)*
- `var pub background: Color` *(field)*

---

### `container_data` <a id="container_data"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn container_data(axis: Axis): ContainerData
```

---

### `TextData` <a id="TextData"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TextData
```

#### Members

- `var pub content: str` *(field)*
- `var pub font_size: float` *(field)*
- `var pub color: Color` *(field)*
- `var pub font_weight: int` *(field)*

---

### `text_data` <a id="text_data"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn text_data(content: str): TextData
```

---

### `ButtonData` <a id="ButtonData"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ButtonData
```

#### Members

- `var pub label: str` *(field)*
- `var pub background: Color` *(field)*
- `var pub text_color: Color` *(field)*
- `var pub corner_radius: float` *(field)*
- `var pub padding: Rect` *(field)*
- `var pub enabled: int` *(field)*

---

### `button_data` <a id="button_data"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn button_data(label: str): ButtonData
```

---

### `LayoutConstraint` <a id="LayoutConstraint"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame LayoutConstraint
```

#### Members

- `var pub mode: int` *(field)*
- `var pub value_num: int` *(field)*

---

### `Blueprint` <a id="Blueprint"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Blueprint
```

#### Members

- `var pub variant_type: int` *(field)*
- `var pub container_data_val: ContainerData` *(field)*
- `var pub text_data_val: TextData` *(field)*
- `var pub button_data_val: ButtonData` *(field)*
- `var pub constraints: list` *(field)*
- `var pub children: list` *(field)*

---

### `empty_constraints` <a id="empty_constraints"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn empty_constraints(): list
```

---

### `empty_blueprints` <a id="empty_blueprints"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn empty_blueprints(): list
```

---

### `blueprint_add_constraint` <a id="blueprint_add_constraint"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn blueprint_add_constraint(bp: Blueprint, c: LayoutConstraint): Blueprint
```

---

### `blueprint_add_child` <a id="blueprint_add_child"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn blueprint_add_child(bp: Blueprint, child: Blueprint): Blueprint
```

---

### `variant_code` <a id="variant_code"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn variant_code(v: BlueprintVariant): int
```

---

### `blueprint_container` <a id="blueprint_container"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn blueprint_container(children: list = ..., axis: Axis = ...): Blueprint
```

---

### `blueprint_text` <a id="blueprint_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn blueprint_text(content: str): Blueprint
```

---

### `blueprint_button` <a id="blueprint_button"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn blueprint_button(label: str): Blueprint
```

---

### `constraint` <a id="constraint"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn constraint(m: ConstraintMode, value: int): LayoutConstraint
```

Typed constraint: the ConstraintMode enum crosses into the packed int once,
through match.

---

### `select` <a id="select"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn select(options: list, selected_idx: int = ..., on_change: any = ...): Widget
```

Extra widgets from std/ui.lm

---

### `multi_select` <a id="multi_select"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn multi_select(options: list, selected_indices: list = ..., on_change: any = ...): Widget
```

---

### `link` <a id="link"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn link(text_val: str, url: str): Widget
```

---

### `pie_chart` <a id="pie_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pie_chart(label: str, values: list, labels: list = ...): Widget
```

---

### `table` <a id="table"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn table(headers: list, rows: list): Widget
```

---

### `alert` <a id="alert"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alert(message: str, type_val: str = ...): Widget
```

---

### `alert_k` <a id="alert_k"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alert_k(message: str, kind: AlertKind): Widget
```

Nominal form: the palette is chosen by an exhaustive match, never a ladder.

---

### `accordion` <a id="accordion"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn accordion(title: str, content: Widget, default_open: bool = ...): Widget
```

---

### `bar_chart` <a id="bar_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bar_chart(label: str, values: list, labels: list = ...): Widget
```

---

### `image` <a id="image"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn image(source: str = ...): Widget
```

---

### `plot_histogram` <a id="plot_histogram"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn plot_histogram(label: str, values: list, min_val: float = ..., max_val: float = ...): Widget
```

---

### `stat` <a id="stat"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stat(title: str, value: str, desc: str = ...): Widget
```

---

### `timeline` <a id="timeline"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn timeline(events: list): Widget
```

---

### `color_rgb8` <a id="color_rgb8"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_rgb8(r: int, g: int, b: int): Color
```

---

### `range_slider` <a id="range_slider"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn range_slider(low: float = ..., high: float = ..., min_val: float = ..., max_val: float = ...): Widget
```

---

### `mask` <a id="mask"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mask(shape: str = ..., child: Widget = ...): Widget
```

---

### `mask_shape` <a id="mask_shape"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mask_shape(shape: MaskShape, child: Widget = ...): Widget
```

Nominal form of `mask`.

---

### `stepper` <a id="stepper"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stepper(value: int = ..., step: int = ..., min_val: int = ..., max_val: int = ..., on_change: any = ...): Widget
```

---

### `calendar` <a id="calendar"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn calendar(selected_date: str = ...): Widget
```

---

### `toggle` <a id="toggle"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn toggle(enabled: bool = ..., on_change: any = ...): Widget
```

---

### `line_chart` <a id="line_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn line_chart(label: str, values: list): Widget
```

---

### `form_field` <a id="form_field"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn form_field(label_text: str, control: Widget, help_text: str = ..., error_text: str = ...): Widget
```

---

### `tooltip` <a id="tooltip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tooltip(label: str, content: Widget): Widget
```

---

### `progress` <a id="progress"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn progress(fraction: float = ..., width_val: float = ...): Widget
```

---

### `tree_node` <a id="tree_node"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tree_node(label: str, children: list, default_open: bool = ...): Widget
```

---

### `grid` <a id="grid"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid(columns_count: int, children: list, spacing_val: float = ...): Widget
```

---

### `radar_chart` <a id="radar_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn radar_chart(label: str, values: list, labels: list = ...): Widget
```

---

### `list` <a id="list"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn list(items: list): Widget
```

---

### `badge` <a id="badge"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn badge(label: str): Widget
```

---

### `color_picker` <a id="color_picker"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_picker(label: str, color: Color, on_change: any = ...): Widget
```

---

### `file_input` <a id="file_input"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn file_input(label: str = ..., on_select: any = ...): Widget
```

---

### `steps` <a id="steps"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn steps(step_titles: list, active_step: int = ...): Widget
```

---

### `toast` <a id="toast"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn toast(message: str, type_val: str = ...): Widget
```

---

### `toast_k` <a id="toast_k"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn toast_k(message: str, kind: AlertKind): Widget
```

---

### `filter` <a id="filter"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn filter(query: str = ..., placeholder: str = ..., on_change: any = ...): Widget
```

---

### `card` <a id="card"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn card(title: str, content: Widget): Widget
```

---

### `scroll` <a id="scroll"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn scroll(content: Widget): Widget
```

---

### `plot_lines` <a id="plot_lines"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn plot_lines(label: str, values: list, min_val: float = ..., max_val: float = ...): Widget
```

---

### `text_area` <a id="text_area"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn text_area(value: str = ..., placeholder: str = ..., on_change: any = ...): Widget
```

---

### `tabs` <a id="tabs"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tabs(titles: list, pages: list, active: int = ..., on_change: any = ...): Widget
```

---

### `polar_area_chart` <a id="polar_area_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn polar_area_chart(label: str, values: list, labels: list = ...): Widget
```

---

### `join` <a id="join"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn join(items: list): Widget
```

---

### `dock` <a id="dock"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dock(items: list): Widget
```

---

### `bubble_chart` <a id="bubble_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bubble_chart(label: str, values: list): Widget
```

---

### `scatter_chart` <a id="scatter_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn scatter_chart(label: str, values: list): Widget
```

---

### `doughnut_chart` <a id="doughnut_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn doughnut_chart(label: str, values: list, labels: list = ...): Widget
```

---

### `overlay` <a id="overlay"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn overlay(content: Widget, x: float = ..., y: float = ..., width_val: float = ..., height_val: float = ...): Widget
```

---

### `diff` <a id="diff"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn diff(old_text: str, new_text: str): Widget
```

---

### `checkbox` <a id="checkbox"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn checkbox(checked: bool = ..., on_change: any = ...): Widget
```

---

### `indicator` <a id="indicator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn indicator(status: str = ..., label: str = ...): Widget
```

---

### `indicator_k` <a id="indicator_k"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn indicator_k(status: DotState, label: str = ...): Widget
```

Nominal form: dot color chosen by exhaustive match.

---

### `slider` <a id="slider"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn slider(value: float = ..., min_val: float = ..., max_val: float = ..., on_change: any = ...): Widget
```

---

### `input` <a id="input"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn input(value: str = ..., placeholder: str = ..., on_change: any = ...): Widget
```

---

