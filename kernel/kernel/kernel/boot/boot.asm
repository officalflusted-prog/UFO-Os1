[BITS 16]
[ORG 0x7C00]
jmp loader
times 510-($-$$) db 0
dw 0xAA55
