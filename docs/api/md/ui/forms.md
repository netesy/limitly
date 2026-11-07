# API Documentation: `forms.lm`

## Overview

std/ui/forms - Form State Management with Validation

## Symbols

- **Frame**: [`ValidationResult`](#ValidationResult)
- **Frame**: [`ValidationRule`](#ValidationRule)
- **Function**: [`required_validator`](#required_validator)
- **Function**: [`min_length_validator`](#min_length_validator)
- **Function**: [`max_length_validator`](#max_length_validator)
- **Function**: [`email_validator`](#email_validator)
- **Function**: [`min_value_validator`](#min_value_validator)
- **Function**: [`max_value_validator`](#max_value_validator)
- **Function**: [`pattern_validator`](#pattern_validator)
- **Frame**: [`FormState`](#FormState)
- **Frame**: [`FormBuilder`](#FormBuilder)
- **Function**: [`form_builder`](#form_builder)
- **Function**: [`create_form`](#create_form)
- **Function**: [`bind_text_field`](#bind_text_field)
- **Function**: [`bind_checkbox_field`](#bind_checkbox_field)
- **Function**: [`bind_slider_field`](#bind_slider_field)
- **Function**: [`field_error_widget`](#field_error_widget)

---

### `ValidationResult` <a id="ValidationResult"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ValidationResult
```

── Validation Result ───────────────────────────────────────────────────────

#### Members

- `var pub is_valid: bool` *(field)*
- `var pub error_message: str` *(field)*
- `var pub field_name: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn valid(): ValidationResult` *(method)*
- `pub fn error(message: str, field: str): ValidationResult` *(method)*

---

### `ValidationRule` <a id="ValidationRule"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ValidationRule
```

── Validation Rule ────────────────────────────────────────────────────────

#### Members

- `var pub field_name: str` *(field)*
- `var pub validator: function` *(field)*
- `var pub is_required: bool` *(field)*
- `pub init(field: str, validator_fn: function)` *(constructor)*

---

### `required_validator` <a id="required_validator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn required_validator(field_name: str): ValidationRule
```

── Common Validators ────────────────────────────────────────────────────────

---

### `min_length_validator` <a id="min_length_validator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn min_length_validator(field_name: str, min_len: int): ValidationRule
```

---

### `max_length_validator` <a id="max_length_validator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn max_length_validator(field_name: str, max_len: int): ValidationRule
```

---

### `email_validator` <a id="email_validator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn email_validator(field_name: str): ValidationRule
```

---

### `min_value_validator` <a id="min_value_validator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn min_value_validator(field_name: str, min_val: float): ValidationRule
```

---

### `max_value_validator` <a id="max_value_validator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn max_value_validator(field_name: str, max_val: float): ValidationRule
```

---

### `pattern_validator` <a id="pattern_validator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pattern_validator(field_name: str, pattern: str): ValidationRule
```

---

### `FormState` <a id="FormState"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame FormState
```

── Form State ─────────────────────────────────────────────────────────────

#### Members

- `var pub values: dict` *(field)*
- `var pub errors: dict` *(field)*
- `var pub touched: dict` *(field)*
- `var pub rules: list` *(field)*
- `var pub is_valid: state.Signal` *(field)*
- `var pub is_submitting: state.Signal` *(field)*
- `var pub on_submit: function` *(field)*
- `var pub on_success: function` *(field)*
- `var pub on_error: function` *(field)*
- `var pub initial_values: dict` *(field)*
- `pub init()` *(constructor)*
- `pub fn add_field(field_name: str, initial_value: any): nil` *(method)*
- `pub fn add_rule(rule: ValidationRule): nil` *(method)*
- `pub fn set_value(field_name: str, value: any): nil` *(method)*
- `pub fn get_value(field_name: str): any` *(method)*
- `pub fn mark_touched(field_name: str): nil` *(method)*
- `pub fn validate_field(field_name: str): ValidationResult` *(method)*
- `pub fn validate_all(): nil` *(method)*
- `pub fn get_values(): dict` *(method)*
- `pub fn get_errors(): list` *(method)*
- `pub fn submit(): nil` *(method)*
- `pub fn submit_success(values: any): nil` *(method)*
- `pub fn submit_failure(errors: any): nil` *(method)*
- `pub fn reset(): nil` *(method)*

---

### `FormBuilder` <a id="FormBuilder"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame FormBuilder
```

── Form Builder ───────────────────────────────────────────────────────────

#### Members

- `var pub form_state: FormState` *(field)*
- `pub init()` *(constructor)*
- `pub fn field(name: str, initial: any): FormBuilder` *(method)*
- `pub fn rule(rule: ValidationRule): FormBuilder` *(method)*
- `pub fn required(field_name: str): FormBuilder` *(method)*
- `pub fn min_length(field_name: str, min_len: int): FormBuilder` *(method)*
- `pub fn max_length(field_name: str, max_len: int): FormBuilder` *(method)*
- `pub fn email(field_name: str): FormBuilder` *(method)*
- `pub fn min_value(field_name: str, min_val: float): FormBuilder` *(method)*
- `pub fn max_value(field_name: str, max_val: float): FormBuilder` *(method)*
- `pub fn pattern(field_name: str, pattern: str): FormBuilder` *(method)*
- `pub fn submit_handler(handler: function): FormBuilder` *(method)*
- `pub fn success_handler(handler: function): FormBuilder` *(method)*
- `pub fn error_handler(handler: function): FormBuilder` *(method)*
- `pub fn build(): FormState` *(method)*

---

### `form_builder` <a id="form_builder"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn form_builder(): FormBuilder
```

── Factory Functions ──────────────────────────────────────────────────────

---

### `create_form` <a id="create_form"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_form(): FormState
```

---

### `bind_text_field` <a id="bind_text_field"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_text_field(form: FormState, field_name: str, widget: ui.Widget): ui.Widget
```

── Field Binding Helpers ───────────────────────────────────────────────────

---

### `bind_checkbox_field` <a id="bind_checkbox_field"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_checkbox_field(form: FormState, field_name: str, widget: ui.Widget): ui.Widget
```

---

### `bind_slider_field` <a id="bind_slider_field"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn bind_slider_field(form: FormState, field_name: str, widget: ui.Widget): ui.Widget
```

---

### `field_error_widget` <a id="field_error_widget"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn field_error_widget(form: FormState, field_name: str): ui.Widget
```

---

