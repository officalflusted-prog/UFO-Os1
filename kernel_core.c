// UFO OS Core Kernel
// Handles basic boot and system init

void kernel_main(void) {
    const char *msg = "🛸 UFO OS Core Loaded Successfully!\n";
    char *vga = (char*)0xb8000;

    for (int i = 0; msg[i] != '\0'; i++) {
        vga[i * 2] = msg[i];
        vga[i * 2 + 1] = 0x0A; // Green text on black
    }

    while (1) { }
}
