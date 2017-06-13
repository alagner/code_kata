#include <stdio.h>
#include <stdlib.h>
#include "mbr_structure.h"
#include "errors.h"

static const size_t mbr_size = 512;

void
print_usage(const char* name) {
   fprintf(stderr, "Usage: %s:%s\n", name, "/path/to/read");
}

void
print_mbr_with_stdlib(const char* filename) {

    struct mbr_contents mbr_buffer;
    FILE* file_to_read;
    size_t i;
    size_t fread_ret_val;
    file_to_read = fopen(filename, "r");
    if (file_to_read == NULL) {
       die("Error opening file"); 
    }

    if (mbr_size != fread(&mbr_buffer, (size_t)1, mbr_size, file_to_read)){
        die("Error reading file");
    }

    /* should check the closing, but it doesn't really matter */
    fclose(file_to_read);

    fprintf(stdout, "%s", "Bootloader\n");
    for (i = 0; i < sizeof(mbr_buffer.bootloader); ++i) {
        fprintf(stdout, "%02X", mbr_buffer.bootloader[i]);
    }
    fprintf(stdout, "%s", "\n");
    fprintf(stdout, "%s", "\n");

    for (i = 0; i < 4; ++i) {
        fprintf(stdout, "Partition %u\n", i+1);
        fprintf(stdout, "%s %02X\n", "Bootable", mbr_buffer.partitions[i].bootable);
        fprintf(stdout, "%s %02X\n", "Initial cylinder header", mbr_buffer.partitions[i].initial_cyl.header);
        fprintf(stdout, "%s %02X", "Initial cylinder addr", mbr_buffer.partitions[i].initial_cyl.cyl[0]);
        fprintf(stdout, "%02X\n", mbr_buffer.partitions[i].initial_cyl.cyl[1]);
        fprintf(stdout, "%s %02X\n", "Type", mbr_buffer.partitions[i].type);
        fprintf(stdout, "%s %02X\n", "Last cylinder header", mbr_buffer.partitions[i].last_cyl.header);
        fprintf(stdout, "%s %02X", "Last cylinder addr", mbr_buffer.partitions[i].last_cyl.cyl[0]);
        fprintf(stdout, "%02X\n", mbr_buffer.partitions[i].last_cyl.cyl[1]);

        fprintf(stdout, "%s %X\n", "LBA sector addr", mbr_buffer.partitions[i].sector_LBA_addr);
        fprintf(stdout, "%s %u\n", "Sector count", mbr_buffer.partitions[i].sector_count);
        fprintf(stdout, "%s", "=====\n");
        fprintf(stdout, "%s", "\n");
    }

    
    fprintf(stdout, "%s %02X %02X\n", "Signature", (unsigned) mbr_buffer.signature[0], (unsigned) mbr_buffer.signature[1]);

}


int
main(int argc, char* const argv[]) {


    if (argc < 2) {
        print_usage(argv[0]);
        return  -1;
    }
    print_mbr_with_stdlib(argv[1]);

    return 0;
}
