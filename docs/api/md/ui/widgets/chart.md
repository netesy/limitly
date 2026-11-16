# API Documentation: `chart.lm`

## Overview

std/ui/widgets/chart.lm
Widget — ported from legacy Fluent Chart (+ chart factories).
kinds: BarChart, LineChart, PieChart (PlotHistogram renders as bars,
matching the legacy emit which aliases histogram→bar).
values: [float] series; labels: [str] optional category labels (unused
in v1 paint, kept for API parity). min_val/max_val accepted for parity;
v1 auto-scales to the data max like the legacy emit.

## Symbols

- **Frame**: [`Chart`](#Chart)
- **Function**: [`chart`](#chart)
- **Function**: [`bar_chart`](#bar_chart)
- **Function**: [`line_chart`](#line_chart)
- **Function**: [`pie_chart`](#pie_chart)
- **Function**: [`plot_histogram`](#plot_histogram)
- **Function**: [`plot_lines`](#plot_lines)

---

### `Chart` <a id="Chart"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Chart
```

#### Members

- `var pub chart_kind: ui_types.WidgetKind` *(field)*
- `var pub label: str` *(field)*
- `var pub values: list` *(field)*
- `var pub labels: list` *(field)*
- `var pub min_val: float` *(field)*
- `var pub max_val: float` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub line_color: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub pal_r: list` *(field)*
- `var pub pal_g: list` *(field)*
- `var pub pal_b: list` *(field)*
- `var pub _cw: float` *(field)*
- `var pub _ch: float` *(field)*
- `var pub _maxv: float` *(field)*
- `var pub _total: float` *(field)*
- `pub init(kind: ui_types.WidgetKind)` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `fn is_bar(): int` *(method)*
- `fn is_line(): int` *(method)*
- `fn compute_max(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `fn paint_bars(): nil` *(method)*
- `fn paint_lines(): nil` *(method)*
- `fn paint_pie(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `chart` <a id="chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn chart(kind: ui_types.WidgetKind, lbl: str = ..., vals: list = ..., lbls: list = ..., min_v: float = ..., max_v: float = ...): Chart
```

---

### `bar_chart` <a id="bar_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bar_chart(lbl: str = ..., vals: list = ...): Chart
```

---

### `line_chart` <a id="line_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn line_chart(lbl: str = ..., vals: list = ...): Chart
```

---

### `pie_chart` <a id="pie_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pie_chart(lbl: str = ..., vals: list = ...): Chart
```

---

### `plot_histogram` <a id="plot_histogram"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn plot_histogram(lbl: str = ..., vals: list = ...): Chart
```

---

### `plot_lines` <a id="plot_lines"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn plot_lines(lbl: str = ..., vals: list = ...): Chart
```

---

