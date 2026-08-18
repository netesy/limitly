#include <windows.h>
#include <stdio.h>

int main() {
    // Simulate what lm_str_concat does
    DWORD size = 12; // len("hello ") + len("world") + 1
    void* p = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!p) {
        DWORD err = GetLastError();
        printf("VirtualAlloc failed: %lu\n", err);
        return 1;
    }
    printf("VirtualAlloc succeeded: %p\n", p);
    
    // Write to it
    char* buf = (char*)p;
    const char* s1 = "hello ";
    const char* s2 = "world";
    int i = 0;
    while (s1[i]) { buf[i] = s1[i]; i++; }
    int j = 0;
    while (s2[j]) { buf[i+j] = s2[j]; j++; }
    buf[i+j] = 0;
    printf("Result: %s\n", buf);
    VirtualFree(p, 0, MEM_RELEASE);
    return 0;
}
