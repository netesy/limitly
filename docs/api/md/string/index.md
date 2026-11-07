# API Documentation: `index.lm`

## Overview

std/string/index.lm
Public facade for std.string.

This file deliberately contains NO implementation. Every symbol is defined in
an implementation submodule and re-exported here, so callers keep the flat
`import std.string as s; s.split(...)` surface while the logic stays organised
by concern:

  string.lm   - frame String (wrapper around a str value)
  builder.lm  - frame Builder + builder()
  basic.lm    - length, byte_at, substr, substring, compare
  search.lm   - contains, starts_with, ends_with
  casing.lm   - to_lower, to_upper, uppercase
  split.lm    - split
  join.lm     - join
  trim.lm     - trim
  replace.lm  - replace

