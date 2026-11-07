# API Documentation: `index.lm`

## Overview

Provides foundation types and common type definitions

## Symbols

- **Type Alias**: [`StdError`](#StdError)
- **Type Alias**: [`IndexOutOfBounds`](#IndexOutOfBounds)
- **Type Alias**: [`EmptyCollection`](#EmptyCollection)
- **Type Alias**: [`CapacityExceeded`](#CapacityExceeded)
- **Type Alias**: [`CollectionError`](#CollectionError)
- **Type Alias**: [`InvalidEncoding`](#InvalidEncoding)
- **Type Alias**: [`PatternNotFound`](#PatternNotFound)
- **Type Alias**: [`InvalidFormat`](#InvalidFormat)
- **Type Alias**: [`StringError`](#StringError)
- **Type Alias**: [`DomainError`](#DomainError)
- **Type Alias**: [`OverflowError`](#OverflowError)
- **Type Alias**: [`UnderflowError`](#UnderflowError)
- **Type Alias**: [`DivisionByZero`](#DivisionByZero)
- **Type Alias**: [`MathError`](#MathError)
- **Type Alias**: [`InvalidDateTime`](#InvalidDateTime)
- **Type Alias**: [`ParseError`](#ParseError)
- **Type Alias**: [`TimezoneError`](#TimezoneError)
- **Type Alias**: [`TimeError`](#TimeError)
- **Type Alias**: [`IntMemoryPool`](#IntMemoryPool)
- **Type Alias**: [`StrMemoryPool`](#StrMemoryPool)
- **Frame**: [`Rc`](#Rc)

---

### `StdError` <a id="StdError"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type StdError = struct
```

Common error types for standard library

---

### `IndexOutOfBounds` <a id="IndexOutOfBounds"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type IndexOutOfBounds = struct
```

Collection error variants

---

### `EmptyCollection` <a id="EmptyCollection"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type EmptyCollection = struct
```

---

### `CapacityExceeded` <a id="CapacityExceeded"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type CapacityExceeded = struct
```

---

### `CollectionError` <a id="CollectionError"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type CollectionError = union
```

Category-specific error types

---

### `InvalidEncoding` <a id="InvalidEncoding"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type InvalidEncoding = struct
```

String error variants

---

### `PatternNotFound` <a id="PatternNotFound"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type PatternNotFound = struct
```

---

### `InvalidFormat` <a id="InvalidFormat"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type InvalidFormat = struct
```

---

### `StringError` <a id="StringError"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type StringError = union
```

---

### `DomainError` <a id="DomainError"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type DomainError = struct
```

Math error variants

---

### `OverflowError` <a id="OverflowError"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type OverflowError = struct
```

---

### `UnderflowError` <a id="UnderflowError"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type UnderflowError = struct
```

---

### `DivisionByZero` <a id="DivisionByZero"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type DivisionByZero = struct
```

---

### `MathError` <a id="MathError"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type MathError = union
```

---

### `InvalidDateTime` <a id="InvalidDateTime"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type InvalidDateTime = struct
```

Time error variants

---

### `ParseError` <a id="ParseError"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type ParseError = struct
```

---

### `TimezoneError` <a id="TimezoneError"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type TimezoneError = struct
```

---

### `TimeError` <a id="TimeError"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type TimeError = union
```

---

### `IntMemoryPool` <a id="IntMemoryPool"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type IntMemoryPool = struct
```

Memory management types

---

### `StrMemoryPool` <a id="StrMemoryPool"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type StrMemoryPool = struct
```

---

### `Rc` <a id="Rc"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Rc
```

Reference counting for shared ownership — staged frame template

#### Members

- `var pub data: T` *(field)*
- `var pub ref_count: int` *(field)*
- `pub init(v: T)` *(constructor)*
- `pub fn strong_count(): int` *(method)*
- `pub fn inc_ref(): nil` *(method)*
- `pub fn dec_ref(): nil` *(method)*

---

