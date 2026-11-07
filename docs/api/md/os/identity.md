# API Documentation: `identity.lm`

## Overview

std/os/identity.lm
Platform, architecture and machine identity, backed by the RT_OS resource.

## Symbols

- **Function**: [`os_name`](#os_name)
- **Function**: [`arch`](#arch)
- **Function**: [`hostname`](#hostname)
- **Function**: [`num_cpu`](#num_cpu)
- **Function**: [`is_windows`](#is_windows)
- **Function**: [`is_linux`](#is_linux)
- **Function**: [`is_macos`](#is_macos)
- **Function**: [`is_wasm`](#is_wasm)
- **Function**: [`is_64bit`](#is_64bit)
- **Function**: [`platform`](#platform)
- **Function**: [`path_separator`](#path_separator)
- **Function**: [`path_list_separator`](#path_list_separator)

---

### `os_name` <a id="os_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn os_name(): str
```

Returns the operating system identifier string ("windows", "linux", "darwin", "android", "freebsd", "wasi", "unknown").

#### Returns

OS name string.

---

### `arch` <a id="arch"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn arch(): str
```

Returns the host processor architecture ("x86_64", "aarch64", "riscv64", "i686", "arm", "wasm32", "unknown").

#### Returns

CPU architecture string.

---

### `hostname` <a id="hostname"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hostname(): str
```

Returns the network hostname of the local machine.

#### Returns

System hostname string.

---

### `num_cpu` <a id="num_cpu"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn num_cpu(): int
```

Returns the count of logical CPU cores available to the process.

#### Returns

Number of logical processor cores (at least 1).

---

### `is_windows` <a id="is_windows"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_windows(): bool
```

Checks whether the host operating system is Windows.

#### Returns

True on Microsoft Windows.

---

### `is_linux` <a id="is_linux"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_linux(): bool
```

Checks whether the host operating system is Linux.

#### Returns

True on Linux.

---

### `is_macos` <a id="is_macos"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_macos(): bool
```

Checks whether the host operating system is macOS / Apple Darwin.

#### Returns

True on macOS.

---

### `is_wasm` <a id="is_wasm"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_wasm(): bool
```

Checks whether the target environment is WebAssembly (WASI or wasm32).

#### Returns

True on WebAssembly targets.

---

### `is_64bit` <a id="is_64bit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_64bit(): bool
```

Checks whether the target processor architecture is 64-bit.

#### Returns

True on 64-bit architectures (x86_64, aarch64, riscv64).

---

### `platform` <a id="platform"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn platform(): str
```

Alias for `os_name()`.

#### Returns

OS platform identifier.

---

### `path_separator` <a id="path_separator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn path_separator(): str
```

Returns the native filesystem path segment separator ("\\" on Windows, "/" on POSIX).

#### Returns

Path separator character.

---

### `path_list_separator` <a id="path_list_separator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn path_list_separator(): str
```

Returns the search-path list delimiter (";" on Windows, ":" on POSIX).

#### Returns

Search path list separator character.

---

