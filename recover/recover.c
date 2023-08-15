#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // invalid command-line argument
    if (argc != 2) {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // read file
    // printf("%s\n", argv[1]);
    FILE *image = fopen(argv[1], "r");
    if (image == NULL) {
        printf("Unable to read %s\n", argv[1]);
        return 1;
    }

    // buffer
    // BYTE *buffer = calloc(sizeof(BYTE), 512);
    BYTE buffer[sizeof(BYTE) * 512];

    FILE *jpg = NULL;
    int fileCounter = 0;
    char fileName[8];

    while (fread(buffer, sizeof(BYTE), 512, image) == 512) {
        // check if current buffer is image
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef) {
            // another image
            if (fileCounter > 0) {
                fclose(jpg);
            }
            // open next image
            sprintf(fileName, "%03d.jpg", fileCounter);
            fileCounter += 1;
            jpg = fopen(fileName, "w");

            // write to image
            fwrite(buffer, sizeof(BYTE), 512, jpg);
        }
        else if (jpg != NULL) {
            fwrite(buffer, sizeof(BYTE), 512, jpg);
        }
    }

    // close last image
    fclose(jpg);
    // free(buffer);
    fclose(image);
    return 0;
}