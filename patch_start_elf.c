#include <stdio.h>
#include <string.h>

typedef struct {
    long offset;
    unsigned char pattern[4];
    unsigned char new_value;
    const char *description;
} Patch;

int apply_patch(FILE *file, const Patch *patch) {
    fseek(file, patch->offset, SEEK_SET);
    
    unsigned char buffer[4];
    size_t read_bytes = fread(buffer, 1, 4, file);
    if (read_bytes != 4) {
        fprintf(stderr, "Failed to read 4 bytes at offset 0x%lx\n", patch->offset);
        return 0;
    }
    
    if (memcmp(buffer, patch->pattern, 4) != 0) {
        fprintf(stderr, "Pattern not found at offset 0x%lx\n", patch->offset);
        fprintf(stderr, "Expected: %02x %02x %02x %02x\n", 
                patch->pattern[0], patch->pattern[1], patch->pattern[2], patch->pattern[3]);
        fprintf(stderr, "Found:    %02x %02x %02x %02x\n", 
                buffer[0], buffer[1], buffer[2], buffer[3]);
        return 0;
    }
    
    buffer[2] = patch->new_value;
    
    fseek(file, patch->offset, SEEK_SET);
    size_t written = fwrite(buffer, 1, 4, file);
    if (written != 4) {
        fprintf(stderr, "Failed to write patch at offset 0x%lx\n", patch->offset);
        return 0;
    }
    
    printf("Successfully patched at offset 0x%lx: %s\n", patch->offset, patch->description);
    return 1;
}

int main() {
    Patch patches[] = {
        {
            .offset = 0x1b357c,
            .pattern = {0x26, 0xb2, 0x55, 0x00},
            .new_value = 0x64,
            .description = "26 b2 55 00 -> 26 b2 64 00"
        },
        {
            .offset = 0x1b3560,
            .pattern = {0x26, 0xb2, 0x5a, 0x00},
            .new_value = 0x69,
            .description = "26 b2 5a 00 -> 26 b2 69 00"
        }
    };
    
    FILE *file = fopen("start.elf", "rb+");
    if (!file) {
        perror("Failed to open start.elf");
        return 1;
    }
    
    int success_count = 0;
    for (int i = 0; i < sizeof(patches) / sizeof(patches[0]); i++) {
        if (apply_patch(file, &patches[i])) {
            success_count++;
        }
    }
    
    fclose(file);
    printf("\nPatched %d out of %d locations\n", success_count, 
           (int)(sizeof(patches) / sizeof(patches[0])));
    
    return success_count == sizeof(patches) / sizeof(patches[0]) ? 0 : 1;
}