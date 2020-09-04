#ifndef ATA_H
#define ATA_H
#include <stdbool.h>
#include <sys/system.h>
//For checking and connecting to ATA drives
#define VENDOR_ID 0x8086
#define DEVICE_ID 0x7010

#define PRIMARY_DRIVE 0x00
#define SECONDARY_DRIVE 0x01
#define MASTER_DRIVE 0x00
#define SLAVE_DRIVE 0x01
#define PRIMARY_IO 0x1F0
#define SECONDARY_IO 0x170

#define ATA_HD_SEL 0x06

#define ATA_DATA 0x00
#define ATA_ERROR 0x01
#define ATA_FEATURES 0x01
#define ATA_SECTOR_COUNT_0 0x02
#define ATA_SECTOR_COUNT_1 0x08
#define ATA_LBA_0 0x03
#define ATA_LBA_1 0x04
#define ATA_LBA_2 0x05
#define ATA_LBA_3 0x09
#define ATA_LBA_4 0x0A
#define ATA_LBA_5 0x0B
#define ATA_COMMAND 0x07
#define ATA_STATUS 0x07
#define ATA_IDENTIFY 0xEC

#define ATA_BSY 0x80
#define ATA_DRDY 0x40
#define ATA_DF 0x20
#define ATA_DSC 0x10
#define ATA_DRQ 0x08
#define ATA_CORR 0x04
#define ATA_IDX 0x02
#define ATA_ERR 0x01

uint8_t* ata_buffer = 0;

//Device identifiers
#define ATA_MODEL 54
#endif