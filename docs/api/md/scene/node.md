# API Documentation: `node.lm`

## Overview

std/scene/node.lm
Node submodule for std.scene. Scene graph nodes, 2D/3D scene trees, and transformation hierarchies.

## Symbols

- **Trait**: [`NodeTrait`](#NodeTrait)
- **Frame**: [`Node`](#Node)

---

### `NodeTrait` <a id="NodeTrait"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait NodeTrait
```

#### Members

- `fn add_child(child: Node): nil` *(method requirement)*

---

### `Node` <a id="Node"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Node: NodeTrait
```

#### Members

- `pub init()` *(constructor)*
- `pub fn add_child(child: Node): nil` *(method)*
- `pub fn apply_base(): nil` *(method)*

---

