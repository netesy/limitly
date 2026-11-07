# API Documentation: `replay.lm`

## Overview

std/ui/replay.lm
Replays a DrawList to the GPU.
Pure linear iteration — zero recursion, zero tree traversal.
This is the final GPU submission stage of the hybrid pipeline.

## Symbols

- **Function**: [`replay`](#replay)

---

### `replay` <a id="replay"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn replay(draw_list: dl.DrawList): nil
```

Replays a DrawList to the GPU — pure linear iteration, zero recursion.

---

