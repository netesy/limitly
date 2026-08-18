#include <stdio.h>
#include <stddef.h>
#include "src/runtime/runtime.h"
int main() { printf("type: %zu, value: %zu\n", offsetof(LmBox, type), offsetof(LmBox, value)); return 0; }
