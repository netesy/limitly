# API Documentation: `index.lm`

## Overview

std.ui - Public Fluent & Composable UI Framework for Lymar
Canonical entry point for Lymar Retained UI System

## Symbols

- **Function**: [`style`](#style)
- **Function**: [`shadow`](#shadow)
- **Function**: [`signal`](#signal)
- **Function**: [`signal_bool`](#signal_bool)
- **Function**: [`signal_int`](#signal_int)
- **Function**: [`signal_float`](#signal_float)
- **Function**: [`signal_str`](#signal_str)
- **Function**: [`computed`](#computed)
- **Function**: [`effect`](#effect)
- **Function**: [`effect_with_cleanup`](#effect_with_cleanup)
- **Function**: [`batch_updates`](#batch_updates)
- **Function**: [`dispose_all_effects`](#dispose_all_effects)
- **Function**: [`compute_layout`](#compute_layout)
- **Function**: [`compute_layout_enhanced`](#compute_layout_enhanced)
- **Function**: [`flatten_layout`](#flatten_layout)
- **Function**: [`hit_test_boxes`](#hit_test_boxes)
- **Function**: [`compute_grid_layout`](#compute_grid_layout)
- **Function**: [`responsive_layout`](#responsive_layout)
- **Function**: [`responsive`](#responsive)
- **Function**: [`breakpoint`](#breakpoint)
- **Function**: [`grid_two_column`](#grid_two_column)
- **Function**: [`grid_three_column`](#grid_three_column)
- **Function**: [`grid_with_aspect`](#grid_with_aspect)
- **Function**: [`grid_enhanced`](#grid_enhanced)
- **Function**: [`make_router`](#make_router)
- **Function**: [`make_router_with_base`](#make_router_with_base)
- **Function**: [`router_link`](#router_link)
- **Function**: [`tab_bar`](#tab_bar)
- **Function**: [`breadcrumbs`](#breadcrumbs)
- **Function**: [`accordion`](#accordion)
- **Function**: [`alert`](#alert)
- **Function**: [`badge`](#badge)
- **Function**: [`bar_chart`](#bar_chart)
- **Function**: [`bubble_chart`](#bubble_chart)
- **Function**: [`button`](#button)
- **Function**: [`calendar`](#calendar)
- **Function**: [`card`](#card)
- **Function**: [`checkbox`](#checkbox)
- **Function**: [`color_picker`](#color_picker)
- **Function**: [`column`](#column)
- **Function**: [`dialog`](#dialog)
- **Function**: [`alert_dialog`](#alert_dialog)
- **Function**: [`confirm`](#confirm)
- **Function**: [`confirm_dialog`](#confirm_dialog)
- **Function**: [`modal_backdrop`](#modal_backdrop)
- **Function**: [`diff`](#diff)
- **Function**: [`dock`](#dock)
- **Function**: [`doughnut_chart`](#doughnut_chart)
- **Function**: [`empty`](#empty)
- **Function**: [`file_input`](#file_input)
- **Function**: [`filter`](#filter)
- **Function**: [`form_field`](#form_field)
- **Function**: [`grid`](#grid)
- **Function**: [`image`](#image)
- **Function**: [`indicator`](#indicator)
- **Function**: [`input`](#input)
- **Function**: [`join`](#join)
- **Function**: [`line_chart`](#line_chart)
- **Function**: [`link`](#link)
- **Function**: [`list`](#list)
- **Function**: [`mask`](#mask)
- **Function**: [`overlay`](#overlay)
- **Function**: [`pie_chart`](#pie_chart)
- **Function**: [`plot_histogram`](#plot_histogram)
- **Function**: [`plot_lines`](#plot_lines)
- **Function**: [`polar_area_chart`](#polar_area_chart)
- **Function**: [`progress`](#progress)
- **Function**: [`radar_chart`](#radar_chart)
- **Function**: [`range_slider`](#range_slider)
- **Function**: [`row`](#row)
- **Function**: [`scatter_chart`](#scatter_chart)
- **Function**: [`scroll`](#scroll)
- **Function**: [`select`](#select)
- **Function**: [`multi_select`](#multi_select)
- **Function**: [`slider`](#slider)
- **Function**: [`spacer`](#spacer)
- **Function**: [`stack`](#stack)
- **Function**: [`stat`](#stat)
- **Function**: [`stepper`](#stepper)
- **Function**: [`steps`](#steps)
- **Function**: [`table`](#table)
- **Function**: [`tabs`](#tabs)
- **Function**: [`text`](#text)
- **Function**: [`text_area`](#text_area)
- **Function**: [`textarea`](#textarea)
- **Function**: [`timeline`](#timeline)
- **Function**: [`toast`](#toast)
- **Function**: [`toggle`](#toggle)
- **Function**: [`tooltip`](#tooltip)
- **Function**: [`tree_node`](#tree_node)
- **Function**: [`build`](#build)
- **Function**: [`replay`](#replay)
- **Function**: [`dl_hit_test`](#dl_hit_test)

---

### `style` <a id="style"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn style(): Style
```

── Styles & Layout Constants ─────────────────────────────────────────────────
align_start/center/end and AXIS_* are re-exported via `pub import show` above
(type-safe; the old `var` aliases were invisible in type position).

---

### `shadow` <a id="shadow"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn shadow(r: float = ..., g: float = ..., b: float = ..., a: float = ..., off_x: float = ..., off_y: float = ..., blur: float = ..., spread: float = ...): Shadow
```

── Application & Window ──────────────────────────────────────────────────────

---

### `signal` <a id="signal"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn signal(init_val): Signal
```

── State Management ───────────────────────────────────────────────────────────

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

### `batch_updates` <a id="batch_updates"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn batch_updates(updates: function): nil
```

---

### `dispose_all_effects` <a id="dispose_all_effects"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispose_all_effects(): nil
```

---

### `compute_layout` <a id="compute_layout"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compute_layout(widget: Widget, x: float, y: float, available_w: float, available_h: float): LayoutBox
```

── Layout Operations ─────────────────────────────────────────────────────────

---

### `compute_layout_enhanced` <a id="compute_layout_enhanced"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compute_layout_enhanced(widget: Widget, x: float, y: float, available_w: float, available_h: float): LayoutBox
```

---

### `flatten_layout` <a id="flatten_layout"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn flatten_layout(box: LayoutBox): list
```

---

### `hit_test_boxes` <a id="hit_test_boxes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hit_test_boxes(boxes: list, px: float, py: float): LayoutBox
```

---

### `compute_grid_layout` <a id="compute_grid_layout"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compute_grid_layout(spec: GridSpec, children: list, x: float, y: float, available_w: float, available_h: float): list
```

---

### `responsive_layout` <a id="responsive_layout"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn responsive_layout(breakpoints: list, viewport_w: float, default_widget: Widget): Widget
```

---

### `responsive` <a id="responsive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn responsive(mobile: Widget, tablet: Widget, desktop: Widget, viewport_w: float): Widget
```

---

### `breakpoint` <a id="breakpoint"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn breakpoint(small: Widget, large: Widget, viewport_w: float, threshold: float = ...): Widget
```

---

### `grid_two_column` <a id="grid_two_column"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid_two_column(left: Widget, right: Widget, gap: float = ...): Widget
```

── Grid Layout ─────────────────────────────────────────────────────────────

---

### `grid_three_column` <a id="grid_three_column"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid_three_column(a: Widget, b: Widget, c: Widget, gap: float = ...): Widget
```

---

### `grid_with_aspect` <a id="grid_with_aspect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid_with_aspect(columns_count: int, children: list, aspect_ratio: float, spacing_val: float = ...): Widget
```

---

### `grid_enhanced` <a id="grid_enhanced"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid_enhanced(spec: GridSpec, children: list): Widget
```

---

### `make_router` <a id="make_router"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_router(): Router
```

── Navigation & Routing ─────────────────────────────────────────────────────

---

### `make_router_with_base` <a id="make_router_with_base"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_router_with_base(base: str): Router
```

---

### `router_link` <a id="router_link"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn router_link(label: str, path: str, router: Router): Widget
```

---

### `tab_bar` <a id="tab_bar"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tab_bar(routes: list, router: Router): Widget
```

---

### `breadcrumbs` <a id="breadcrumbs"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn breadcrumbs(router: Router): Widget
```

---

### `accordion` <a id="accordion"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn accordion(title: str, content: Widget, default_open: bool = ...): Widget
```

── Semantic Widget Constructors ──────────────────────────────────────────────

---

### `alert` <a id="alert"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alert(message: str, type_val: str = ...): Widget
```

---

### `badge` <a id="badge"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn badge(label: str): Widget
```

---

### `bar_chart` <a id="bar_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bar_chart(label: str, values: list, labels: list = ...): Widget
```

---

### `bubble_chart` <a id="bubble_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bubble_chart(label: str, values: list): Widget
```

---

### `button` <a id="button"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn button(label: str, on_click: any = ...): Widget
```

---

### `calendar` <a id="calendar"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn calendar(selected_date: str = ...): Widget
```

---

### `card` <a id="card"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn card(title: str, content: Widget): Widget
```

---

### `checkbox` <a id="checkbox"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn checkbox(checked: bool = ..., on_change: any = ...): Widget
```

---

### `color_picker` <a id="color_picker"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_picker(label: str, color: Color, on_change: any = ...): Widget
```

---

### `column` <a id="column"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn column(children: list): Widget
```

---

### `dialog` <a id="dialog"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dialog(title: str, content: Widget, is_open: bool = ..., width: float = ..., height: float = ..., on_close: any = ...): Widget
```

---

### `alert_dialog` <a id="alert_dialog"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alert_dialog(title: str, message: str, on_ok: any = ...): Widget
```

---

### `confirm` <a id="confirm"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn confirm(title: str, message: str, on_yes: any = ..., on_no: any = ...): Widget
```

---

### `confirm_dialog` <a id="confirm_dialog"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn confirm_dialog(title: str, message: str, on_yes: any = ..., on_no: any = ...): Widget
```

---

### `modal_backdrop` <a id="modal_backdrop"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn modal_backdrop(alpha: float = ...): Widget
```

---

### `diff` <a id="diff"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn diff(old_text: str, new_text: str): Widget
```

---

### `dock` <a id="dock"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dock(items: list): Widget
```

---

### `doughnut_chart` <a id="doughnut_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn doughnut_chart(label: str, values: list, labels: list = ...): Widget
```

---

### `empty` <a id="empty"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn empty(): Widget
```

---

### `file_input` <a id="file_input"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn file_input(label: str = ..., on_select: any = ...): Widget
```

---

### `filter` <a id="filter"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn filter(query: str = ..., placeholder: str = ..., on_change: any = ...): Widget
```

---

### `form_field` <a id="form_field"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn form_field(label_text: str, control: Widget, help_text: str = ..., error_text: str = ...): Widget
```

---

### `grid` <a id="grid"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid(columns_count: int, children: list, spacing_val: float = ...): Widget
```

---

### `image` <a id="image"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn image(source: str = ...): Widget
```

---

### `indicator` <a id="indicator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn indicator(status: str = ..., label: str = ...): Widget
```

---

### `input` <a id="input"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn input(value: str = ..., placeholder: str = ..., on_change: any = ...): Widget
```

---

### `join` <a id="join"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn join(items: list): Widget
```

---

### `line_chart` <a id="line_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn line_chart(label: str, values: list): Widget
```

---

### `link` <a id="link"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn link(text_val: str, url: str): Widget
```

---

### `list` <a id="list"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn list(items: list): Widget
```

---

### `mask` <a id="mask"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mask(shape: str = ..., child: Widget = ...): Widget
```

---

### `overlay` <a id="overlay"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn overlay(content: Widget, x: float = ..., y: float = ..., width_val: float = ..., height_val: float = ...): Widget
```

---

### `pie_chart` <a id="pie_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pie_chart(label: str, values: list, labels: list = ...): Widget
```

---

### `plot_histogram` <a id="plot_histogram"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn plot_histogram(label: str, values: list, min_val: float = ..., max_val: float = ...): Widget
```

---

### `plot_lines` <a id="plot_lines"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn plot_lines(label: str, values: list, min_val: float = ..., max_val: float = ...): Widget
```

---

### `polar_area_chart` <a id="polar_area_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn polar_area_chart(label: str, values: list, labels: list = ...): Widget
```

---

### `progress` <a id="progress"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn progress(fraction: float = ..., width_val: float = ...): Widget
```

---

### `radar_chart` <a id="radar_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn radar_chart(label: str, values: list, labels: list = ...): Widget
```

---

### `range_slider` <a id="range_slider"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn range_slider(low: float = ..., high: float = ..., min_val: float = ..., max_val: float = ...): Widget
```

---

### `row` <a id="row"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn row(children: list): Widget
```

---

### `scatter_chart` <a id="scatter_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn scatter_chart(label: str, values: list): Widget
```

---

### `scroll` <a id="scroll"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn scroll(content: Widget): Widget
```

---

### `select` <a id="select"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn select(options: list, selected_idx: int = ..., on_change: any = ...): Widget
```

---

### `multi_select` <a id="multi_select"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn multi_select(options: list, selected_indices: list = ..., on_change: any = ...): Widget
```

---

### `slider` <a id="slider"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn slider(value: float = ..., min_val: float = ..., max_val: float = ..., on_change: any = ...): Widget
```

---

### `spacer` <a id="spacer"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn spacer(flex: float = ...): Widget
```

---

### `stack` <a id="stack"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stack(children: list): Widget
```

---

### `stat` <a id="stat"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stat(title: str, value: str, desc: str = ...): Widget
```

---

### `stepper` <a id="stepper"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stepper(value: int = ..., step: int = ..., min_val: int = ..., max_val: int = ..., on_change: any = ...): Widget
```

---

### `steps` <a id="steps"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn steps(step_titles: list, active_step: int = ...): Widget
```

---

### `table` <a id="table"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn table(headers: list, rows: list): Widget
```

---

### `tabs` <a id="tabs"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tabs(titles: list, pages: list, active: int = ..., on_change: any = ...): Widget
```

---

### `text` <a id="text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn text(content: str): Widget
```

---

### `text_area` <a id="text_area"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn text_area(value: str = ..., placeholder: str = ..., on_change: any = ...): Widget
```

---

### `textarea` <a id="textarea"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn textarea(content: str): Widget
```

---

### `timeline` <a id="timeline"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn timeline(events: list): Widget
```

---

### `toast` <a id="toast"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn toast(message: str, type_val: str = ...): Widget
```

---

### `toggle` <a id="toggle"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn toggle(enabled: bool = ..., on_change: any = ...): Widget
```

---

### `tooltip` <a id="tooltip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tooltip(label: str, content: Widget): Widget
```

---

### `tree_node` <a id="tree_node"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tree_node(label: str, children: list, default_open: bool = ...): Widget
```

---

### `build` <a id="build"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn build(root: Widget, vw: float, vh: float, ts: any = ..., x: float = ..., y: float = ...): DrawList
```

── Hybrid UI Execution Engine ────────────────────────────────────────────────

---

### `replay` <a id="replay"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn replay(dlist_obj: DrawList): nil
```

---

### `dl_hit_test` <a id="dl_hit_test"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_hit_test(dlist_obj: DrawList, px: float, py: float): HitZone
```

---

