#include <windows.h>
int main() {
    void* p = VirtualAlloc(0, 12, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    return p ? 0 : 1;
}
