#include "storage.h"
#include "ports.h"

// Standard primary IDE ports
#define ATA_DATA       0x1F0
#define ATA_ERROR      0x1F1
#define ATA_SECTOR_CNT 0x1F2
#define ATA_SECTOR_NUM 0x1F3
#define ATA_CYL_LOW    0x1F4
#define ATA_CYL_HIGH   0x1F5
#define ATA_DRIVE_HEAD 0x1F6
#define ATA_STATUS     0x1F7
#define ATA_COMMAND    0x1F7
#define ATA_ALT_STATUS 0x3F6
#define ATA_DEV_CTRL   0x3F6

// Status bits
#define ATA_SR_BSY  0x80
#define ATA_SR_DRQ  0x08
#define ATA_SR_ERR  0x01

// Commands
#define ATA_CMD_READ_PIO  0x20
#define ATA_CMD_IDENTIFY  0xEC

// Wait until BSY clears (returns 0 on success, -1 on timeout)
static int ata_wait_bs_clear(void) {
    for (int i = 0; i < 1000000; ++i) {
        uint8_t status = inb(ATA_STATUS);
        if (!(status & ATA_SR_BSY)) return 0;
    }
    return -1;
}

// Wait until DRQ sets (data ready), return 0 success, -1 timeout/error
static int ata_wait_drq(void) {
    for (int i = 0; i < 1000000; ++i) {
        uint8_t status = inb(ATA_STATUS);
        if (status & ATA_SR_ERR) return -1;
        if (status & ATA_SR_DRQ) return 0;
    }
    return -1;
}

void ata_init(void) {
    // Basic check: select master and send IDENTIFY
    outb(ATA_DRIVE_HEAD, 0xA0); // 0xA0 = 0b10100000: select master, LBA=0
    outb(ATA_SECTOR_CNT, 0);
    outb(ATA_SECTOR_NUM, 0);
    outb(ATA_CYL_LOW, 0);
    outb(ATA_CYL_HIGH, 0);
    outb(ATA_COMMAND, ATA_CMD_IDENTIFY);

    // Check status
    uint8_t status = inb(ATA_STATUS);
    if (status == 0) {
        // no device
        return;
    }
    // Wait for DRQ or ERR
    if (ata_wait_drq() == 0) {
        // We could read identify data (256 words) using inw(ATA_DATA)
        // For now we ignore contents — driver exists.
        for (int i = 0; i < 256; ++i) {
            volatile uint16_t v = inw(ATA_DATA);
            (void)v;
        }
    }
}

// Read a 512-byte sector using LBA28 addressing on primary master
int ata_read_sector_lba28(uint32_t lba, uint8_t* buffer) {
    if (lba > 0x0FFFFFFF) return -1; // LBA28 limit

    // Wait for BSY clear
    if (ata_wait_bs_clear() != 0) return -1;

    outb(ATA_DEV_CTRL, 0); // disable interrupts
    outb(ATA_SECTOR_CNT, 1); // read 1 sector
    outb(ATA_SECTOR_NUM, (uint8_t)(lba & 0xFF));
    outb(ATA_CYL_LOW, (uint8_t)((lba >> 8) & 0xFF));
    outb(ATA_CYL_HIGH, (uint8_t)((lba >> 16) & 0xFF));
    outb(ATA_DRIVE_HEAD, (uint8_t)(0xE0 | ((lba >> 24) & 0x0F))); // 0xE0 sets LBA & master

    outb(ATA_COMMAND, ATA_CMD_READ_PIO);

    // Wait for DRQ
    if (ata_wait_drq() != 0) return -1;

    // Read 256 words (512 bytes)
    for (int i = 0; i < 256; ++i) {
        uint16_t word = inw(ATA_DATA);
        buffer[i*2    ] = (uint8_t)(word & 0xFF);
        buffer[i*2 + 1] = (uint8_t)((word >> 8) & 0xFF);
    }

    // Optional: check status for errors
    uint8_t status = inb(ATA_STATUS);
    if (status & ATA_SR_ERR) return -1;

    return 0;
}
