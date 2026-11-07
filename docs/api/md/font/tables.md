# API Documentation: `tables.lm`

## Overview

std/font/tables.lm
TrueType and OpenType table directory and core table parsing (cmap, head, hhea, hmtx, loca, maxp).

## Symbols

- **Frame**: [`TableRecord`](#TableRecord)
- **Frame**: [`KerningEntry`](#KerningEntry)
- **Frame**: [`CachedGlyphMetrics`](#CachedGlyphMetrics)
- **Frame**: [`CmapFormat4`](#CmapFormat4)
- **Frame**: [`CmapGroup`](#CmapGroup)
- **Frame**: [`CmapFormat12`](#CmapFormat12)
- **Frame**: [`Info`](#Info)
- **Function**: [`get_num_fonts`](#get_num_fonts)
- **Function**: [`get_font_offset`](#get_font_offset)
- **Function**: [`parse_tables`](#parse_tables)

---

### `TableRecord` <a id="TableRecord"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TableRecord
```

#### Members

- `var pub tag: int` *(field)*
- `var pub offset: int` *(field)*
- `var pub length: int` *(field)*
- `pub init()` *(constructor)*

---

### `KerningEntry` <a id="KerningEntry"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame KerningEntry
```

#### Members

- `var pub glyph1: int` *(field)*
- `var pub glyph2: int` *(field)*
- `var pub advance: int` *(field)*
- `pub init()` *(constructor)*

---

### `CachedGlyphMetrics` <a id="CachedGlyphMetrics"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame CachedGlyphMetrics
```

#### Members

- `var pub advance: int` *(field)*
- `var pub lsb: int` *(field)*
- `pub init()` *(constructor)*

---

### `CmapFormat4` <a id="CmapFormat4"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame CmapFormat4
```

#### Members

- `var pub seg_count: int` *(field)*
- `var pub end_codes: list` *(field)*
- `var pub start_codes: list` *(field)*
- `var pub id_deltas: list` *(field)*
- `var pub id_range_offsets: list` *(field)*
- `var pub id_range_offsets_base: int` *(field)*
- `var pub is_valid: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn get_glyph_index(reader: r.ByteReader, codepoint: int): int` *(method)*

---

### `CmapGroup` <a id="CmapGroup"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame CmapGroup
```

#### Members

- `var pub start_char: int` *(field)*
- `var pub end_char: int` *(field)*
- `var pub start_glyph: int` *(field)*
- `pub init()` *(constructor)*

---

### `CmapFormat12` <a id="CmapFormat12"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame CmapFormat12
```

#### Members

- `var pub groups: list` *(field)*
- `var pub is_valid: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn get_glyph_index(codepoint: int): int` *(method)*

---

### `Info` <a id="Info"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Info
```

#### Members

- `var pub units_per_em: int` *(field)*
- `var pub index_to_loc_format: int` *(field)*
- `var pub num_glyphs: int` *(field)*
- `var pub ascent: int` *(field)*
- `var pub descent: int` *(field)*
- `var pub line_gap: int` *(field)*
- `var pub num_h_metrics: int` *(field)*
- `var pub loca_offset: int` *(field)*
- `var pub glyf_offset: int` *(field)*
- `var pub hmtx_offset: int` *(field)*
- `var pub cmap_format4: CmapFormat4` *(field)*
- `var pub cmap_format12: CmapFormat12` *(field)*
- `var pub has_os2: bool` *(field)*
- `var pub typo_ascent: int` *(field)*
- `var pub typo_descent: int` *(field)*
- `var pub typo_line_gap: int` *(field)*
- `var pub has_kern: bool` *(field)*
- `var pub kern_offset: int` *(field)*
- `var pub kerning_pairs: list` *(field)*
- `var pub glyph_metrics_cache: list` *(field)*
- `var pub is_valid: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn get_glyph_index(reader: r.ByteReader, codepoint: int): int` *(method)*
- `pub fn get_glyph_offset_and_length(reader: r.ByteReader, glyph_idx: int): tuple` *(method)*
- `pub fn get_glyph_hmetrics(reader: r.ByteReader, glyph_idx: int): tuple` *(method)*
- `pub fn build_glyph_metrics_cache(reader: r.ByteReader)` *(method)*
- `pub fn get_kern_advance(glyph1: int, glyph2: int): int` *(method)*

---

### `get_num_fonts` <a id="get_num_fonts"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_num_fonts(reader: r.ByteReader): int
```

---

### `get_font_offset` <a id="get_font_offset"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_font_offset(reader: r.ByteReader, font_index: int): int
```

---

### `parse_tables` <a id="parse_tables"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_tables(reader: r.ByteReader): Info?
```

---

