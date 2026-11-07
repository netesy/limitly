# API Documentation: `navigation.lm`

## Overview

std/ui/navigation.lm
Complete client-side router for Lymar UI applications.

Concepts:
  Route        — pattern string + builder function that returns a Widget
  Router       — owns the route table, history stack, and current match
  RouterParams — key-value pairs extracted from a matched URL pattern
  Middleware   — optional pre-navigation guard (e.g. auth check)

## Symbols

- **Frame**: [`RouterParams`](#RouterParams)
- **Function**: [`split_path`](#split_path)
- **Function**: [`match_pattern`](#match_pattern)
- **Type Alias**: [`RouteFn`](#RouteFn)
- **Frame**: [`Route`](#Route)
- **Frame**: [`HistoryEntry`](#HistoryEntry)
- **Type Alias**: [`MiddlewareFn`](#MiddlewareFn)
- **Frame**: [`Router`](#Router)
- **Function**: [`make_router`](#make_router)
- **Function**: [`make_router_with_base`](#make_router_with_base)
- **Function**: [`router_link`](#router_link)
- **Function**: [`tab_bar`](#tab_bar)
- **Function**: [`breadcrumbs`](#breadcrumbs)

---

### `RouterParams` <a id="RouterParams"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame RouterParams
```

── Route Params ──────────────────────────────────────────────────────────────

#### Members

- `var pub keys: list` *(field)*
- `var pub values: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn get(key: str): str` *(method)*
- `pub fn get_int(key: str): int` *(method)*
- `pub fn has(key: str): bool` *(method)*
- `pub fn set(key: str, value: str): nil` *(method)*
- `pub fn to_str(): str` *(method)*

---

### `split_path` <a id="split_path"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn split_path(path: str): list
```

── Pattern Matching ──────────────────────────────────────────────────────────
Split a string by "/" into segments.

---

### `match_pattern` <a id="match_pattern"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn match_pattern(pattern: str, path: str): tuple
```

Attempt to match `path` against `pattern`.
Returns (matched: bool, params: RouterParams).

---

### `RouteFn` <a id="RouteFn"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type RouteFn = function
```

── Route ─────────────────────────────────────────────────────────────────────

---

### `Route` <a id="Route"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Route
```

#### Members

- `var pub pattern: str` *(field)*
- `var pub handler: RouteFn` *(field)*
- `var pub name: str` *(field)*
- `var pub meta: str` *(field)*
- `pub init(pattern: str, handler: RouteFn)` *(constructor)*

---

### `HistoryEntry` <a id="HistoryEntry"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame HistoryEntry
```

── Navigation Entry ──────────────────────────────────────────────────────────

#### Members

- `var pub path: str` *(field)*
- `var pub title: str` *(field)*
- `var pub state: str` *(field)*
- `pub init()` *(constructor)*

---

### `MiddlewareFn` <a id="MiddlewareFn"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type MiddlewareFn = function
```

── Middleware ────────────────────────────────────────────────────────────────
Return "" to allow, or a redirect path string to redirect.

---

### `Router` <a id="Router"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Router
```

── Router ────────────────────────────────────────────────────────────────────

#### Members

- `var pub routes: list` *(field)*
- `var pub history: list` *(field)*
- `var pub history_idx: int` *(field)*
- `var pub current_path: str` *(field)*
- `var pub current_params: RouterParams` *(field)*
- `var pub current_route: int` *(field)*
- `var pub not_found_fn: RouteFn` *(field)*
- `var pub middlewares: list` *(field)*
- `var pub base_path: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(pattern: str, handler: RouteFn): Router` *(method)*
- `pub fn add_named(pattern: str, handler: RouteFn, name: str): Router` *(method)*
- `pub fn not_found(handler: RouteFn): Router` *(method)*
- `pub fn use_middleware(mw: MiddlewareFn): Router` *(method)*
- `fn run_middlewares(from_path: str, to_path: str): str` *(method)*
- `fn strip_base(path: str): str` *(method)*
- `fn find_match(path: str): int` *(method)*
- `pub fn navigate(path: str): nil` *(method)*
- `pub fn can_go_back(): bool` *(method)*
- `pub fn can_go_forward(): bool` *(method)*
- `pub fn go_back(): nil` *(method)*
- `pub fn go_forward(): nil` *(method)*
- `pub fn go(delta: int): nil` *(method)*
- `pub fn replace(path: str): nil` *(method)*
- `pub fn navigate_to(name: str, params: RouterParams): nil` *(method)*
- `pub fn current_widget(): ui.Widget` *(method)*
- `pub fn widget_for(path: str): ui.Widget` *(method)*
- `pub fn url_for(name: str, params: RouterParams): str` *(method)*
- `pub fn current_entry(): HistoryEntry` *(method)*
- `pub fn history_len(): int` *(method)*

---

### `make_router` <a id="make_router"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_router(): Router
```

── Factory ───────────────────────────────────────────────────────────────────

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
pub fn router_link(label: str, path: str, router: Router): ui.Widget
```

── Link Widget ───────────────────────────────────────────────────────────────

---

### `tab_bar` <a id="tab_bar"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tab_bar(routes: list, router: Router): ui.Widget
```

── Tab Bar Widget ────────────────────────────────────────────────────────────

---

### `breadcrumbs` <a id="breadcrumbs"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn breadcrumbs(router: Router): ui.Widget
```

── Breadcrumb Widget ─────────────────────────────────────────────────────────

---

