#ifndef PCI_H
#define PCI_H

typedef struct
{
    uint16_t vendor;
    uint16_t device;
    int driver;
} pci_device;

#endif