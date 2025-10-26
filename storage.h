#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>
#include <stddef.h>

// Initialize ATA driver (sets up detection state)
void ata_init(void);

// Read a 512-byte sector from LBA into buffer (returns 0 on success, non-zero on error)
int ata_read_sector_lba28(uint32_t lba, uint8_t* buffer);

#endif
