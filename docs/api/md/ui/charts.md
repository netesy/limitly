# API Documentation: `charts.lm`

## Overview

std/ui/charts.lm
Comprehensive Charts & Data Visualization Module for std.ui

## Symbols

- **Function**: [`plot_lines`](#plot_lines)
- **Function**: [`plot_histogram`](#plot_histogram)
- **Function**: [`bar_chart`](#bar_chart)
- **Function**: [`line_chart`](#line_chart)
- **Function**: [`pie_chart`](#pie_chart)
- **Function**: [`doughnut_chart`](#doughnut_chart)
- **Function**: [`bubble_chart`](#bubble_chart)
- **Function**: [`scatter_chart`](#scatter_chart)
- **Function**: [`polar_area_chart`](#polar_area_chart)
- **Function**: [`radar_chart`](#radar_chart)

---

### `plot_lines` <a id="plot_lines"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn plot_lines(label: str, values: list, min_val: float = ..., max_val: float = ...): ui.Widget
```

---

### `plot_histogram` <a id="plot_histogram"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn plot_histogram(label: str, values: list, min_val: float = ..., max_val: float = ...): ui.Widget
```

---

### `bar_chart` <a id="bar_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bar_chart(label: str, values: list, labels: list = ...): ui.Widget
```

---

### `line_chart` <a id="line_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn line_chart(label: str, values: list): ui.Widget
```

---

### `pie_chart` <a id="pie_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pie_chart(label: str, values: list, labels: list = ...): ui.Widget
```

---

### `doughnut_chart` <a id="doughnut_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn doughnut_chart(label: str, values: list, labels: list = ...): ui.Widget
```

---

### `bubble_chart` <a id="bubble_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bubble_chart(label: str, values: list): ui.Widget
```

---

### `scatter_chart` <a id="scatter_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn scatter_chart(label: str, values: list): ui.Widget
```

---

### `polar_area_chart` <a id="polar_area_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn polar_area_chart(label: str, values: list, labels: list = ...): ui.Widget
```

---

### `radar_chart` <a id="radar_chart"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn radar_chart(label: str, values: list, labels: list = ...): ui.Widget
```

---

