# API Documentation: `dialog.lm`

## Overview

std/ui/dialog - Modal dialog and overlay widgets

## Symbols

- **Function**: [`dialog`](#dialog)
- **Function**: [`alert`](#alert)
- **Function**: [`alert_dialog`](#alert_dialog)
- **Function**: [`confirm`](#confirm)
- **Function**: [`confirm_dialog`](#confirm_dialog)
- **Function**: [`modal_backdrop`](#modal_backdrop)

---

### `dialog` <a id="dialog"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dialog(title: str, content: ui_types.Widget, is_open: bool = ..., width: float = ..., height: float = ..., on_close: any = ...): ui_types.Widget
```

Modal dialog with title, content, close button, and dynamic viewport centering

---

### `alert` <a id="alert"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alert(title: str, message: str, on_ok: any = ...): ui_types.Widget
```

Alert dialog (modal with message and OK button)

---

### `alert_dialog` <a id="alert_dialog"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alert_dialog(title: str, message: str, on_ok: any = ...): ui_types.Widget
```

---

### `confirm` <a id="confirm"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn confirm(title: str, message: str, on_yes: any = ..., on_no: any = ...): ui_types.Widget
```

Confirm dialog (modal with message and Yes/No buttons)

---

### `confirm_dialog` <a id="confirm_dialog"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn confirm_dialog(title: str, message: str, on_yes: any = ..., on_no: any = ...): ui_types.Widget
```

---

### `modal_backdrop` <a id="modal_backdrop"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn modal_backdrop(alpha: float = ...): ui_types.Widget
```

Modal backdrop (darkened background behind dialog)

---

