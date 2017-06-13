#ifndef MBR_STRUCTURE_H
#define MBR_STRUCTURE_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


struct cylinder  {
    uint8_t header;
    uint8_t cyl[2];
} __attribute__((packed));

struct partinfo {
    uint8_t bootable;
    struct cylinder initial_cyl;
    uint8_t type;
    struct cylinder last_cyl;
    uint32_t sector_LBA_addr;
    uint32_t sector_count;

} __attribute__((packed));


struct mbr_contents {
   uint8_t bootloader[446]; 
   struct partinfo partitions[4];
   uint8_t signature[2];
} __attribute__((packed));



#ifdef __cplusplus
}
#endif //__cplusplus

#endif //MBR_STRUCTURE_H
