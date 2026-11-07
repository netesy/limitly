# API Documentation: `index.lm`

## Overview

std/testing/index.lm
Public facade for std.testing.

No implementation lives here. The harness keeps its counters in a Testing
frame instance owned by the caller, because Lymar does not retain
module-level state between calls.

