// UFO OS Kernel — version 0.0.1
// Entry point for the OS kernel

void main() {
    // Print a basic message
    const char* msg = "UFO OS Booted Successfully!";
    for (const char* p = msg; *p; p++) {
        // Low-level print to screen memory (for x86 text mode)
        *((char*)0xb8000 + (p - msg) * 2) = *p;
    }

    while (1) { /* infinite loop */ }
}
