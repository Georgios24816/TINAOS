#ifndef ATA_C
#define ATA_C
#include <drivers/ata.h>

void select_drive(uint8_t bus, uint8_t slot)
{
    //Check if we are on the primary bus
    if(bus == PRIMARY_DRIVE)
    {
        //Check if slot is master
        if(slot == MASTER_DRIVE)
            //Write 0xA0 for selection
            outb(PRIMARY_IO + ATA_HD_SEL, 0xA0);
        else
            //Write 0xB0 for selection
            outb(PRIMARY_IO + ATA_HD_SEL, 0xB0);
    }
    else
        //Check if slot is master
        if(slot == MASTER_DRIVE)
            //Write 0xA0 for secondary selection
            outb(SECONDARY_IO + ATA_HD_SEL, 0xA0);
        else
            //Write 0xB0 for secondary selection
            outb(SECONDARY_IO + ATA_HD_SEL, 0xB0);
}

uint8_t identify_drive(uint8_t bus, uint8_t drive)
{
    //For drive stuff
    uint16_t io = 0;
    //Select the drive
    select_drive(bus, drive);
    //Check if bus is primary
    if(bus == PRIMARY_IO)
        //Set io to primary drive
        io = PRIMARY_IO;
    else
        //Set io to secondary drive
        io = SECONDARY_IO;
    //Set sector count to 0
    outb(io + ATA_SECTOR_COUNT_0, 0);
    //Set LBA 0 to 0
    outb(io + ATA_LBA_0, 0);
    //Set LBA 1 to 0
    outb(io + ATA_LBA_1, 0);
    //Set LBA 2 to 0
    outb(io + ATA_LBA_2, 0);
    //Send the identify command
    outb(io + ATA_COMMAND, ATA_IDENTIFY);
    //Get the status
    uint8_t status = inb(io + ATA_STATUS);
    //Check if status != 0xFFFF
    if(status)
    {
        //Notify that we will be polling now
        write_current_operation("identify_drive", "Polling drive until BSY bit is free");
        //Loop until BSY bit is free
        while(inb(io + ATA_STATUS) & ATA_BSY != 0);
        //Read the status
read_status:    status = inb(io + ATA_STATUS);
        //We are now polling until DRQ bit is free
        write_current_operation("identify_drive", "Polling until DRQ bit is free");
        //Loop while DRQ is set, go to read_status
        while(!(status & ATA_DRQ)) goto read_status;
        //Print that the drive is online
        cprintf(green, "[ATA] => identify_drive: %s drive is online", bus==PRIMARY_DRIVE?"Primary":"Secondary");
        //Now we have to read the data
        for(int i = 0; i < 256; i++)
        {
            //Read into the ata buffer
            *(uint16_t *)(ata_buffer + i * 2) = inw(io + ATA_DATA);
        }
    }
}

void initiliaze_ata_driver()
{
    identify_drive(PRIMARY_DRIVE, MASTER_DRIVE);
    identify_drive(SECONDARY_DRIVE, SLAVE_DRIVE);
    char* str = (char*) malloc(40);
    for(int idx = 0; idx < 40; idx+= 2)
    {
        str[idx] = ata_buffer[ATA_MODEL + idx + 1];
        str[idx + 1] = ata_buffer[ATA_MODEL + idx];
    }

    printf("Device: %s", str);
}

#endif