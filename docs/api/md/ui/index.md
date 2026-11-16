# API Documentation: `index.lm`

## Overview

std/ui/index.lm
Facade for the retained component UI — the only application UI system.

This is the canonical surface: `import std.ui as ui` yields the typed
Component contract, geometry, widgets, containers, signals and the
frame driver under one namespace.

  import std.ui as ui;
  import std.app as app;

  var root = ui.column(6.0);
  root.add(ui.label("Hello"));
  root.add(ui.button("Fire", nil, on_fire));
  root.add(ui.checkbox("Enable", false));
  var a = app.App("Title", 800, 600);
  a.ui(root);
  a.run();

State flows through signals (ui.signal_int/ui.signal_float/ui.signal_str/
ui.signal_bool, ui.computed_str), never through callbacks — bind before
add() and the tree sees live values across the trait snapshot.

## Symbols

- **Function**: [`pick_file`](#pick_file)
- **Function**: [`pick_save`](#pick_save)
- **Function**: [`file_dialog_owner`](#file_dialog_owner)

---

### `pick_file` <a id="pick_file"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pick_file(owner: int = ..., title: str = ...): str?
```

Native file dialogs (std.ui.file_dialog) — Win32-backed pick_file/pick_save.

---

### `pick_save` <a id="pick_save"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pick_save(owner: int = ..., title: str = ...): str?
```

---

### `file_dialog_owner` <a id="file_dialog_owner"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn file_dialog_owner(hwnd: int): nil
```

---

