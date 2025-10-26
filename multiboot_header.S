/*
 * Minimal Multiboot header (must be within first 8192 bytes)
 * This tells GRUB this is a Multiboot-compliant kernel.
 */
    .section .multiboot
    .align 4
    .globl multiboot_header
multiboot_header:
    .long 0x1BADB002        /* magic */
    .long 0x00010003        /* flags: align modules + memory info + others */
    .long -(0x1BADB002 + 0x00010003) /* checksum */
    .long 0                  /* reserved for loader-provided info (optional) */
