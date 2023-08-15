#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

#define uint_8 BYTE;

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3) {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Unable to open %s\n", argv[1]);
        return 2;
    }

    // Read header
    // TODO #3
    WAVHEADER headerBuffer;
    int readHeader = fread(&headerBuffer, sizeof(WAVHEADER), 1, input);
    if (readHeader != 1) {
        printf("Read header unsuccessful\n");
        return 3;
    }


    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(headerBuffer) != 1){
        printf("Invalid WAV Header\n");
        return 4;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Output file opened unsuccessful\n");
        return 5;
    }

    // Write header to file
    // TODO #6
    int writeHeader = fwrite(&headerBuffer, sizeof(WAVHEADER), 1, output);
    if (writeHeader != 1) {
        printf("Write header unsuccessful\n");
        return 6;
    }

    // Use get_block_size to calculate size of block
    // TODO #7
    int blockSize = get_block_size(headerBuffer);

    // Write reversed audio to file
    // TODO #8
    // int numOfChannels = headerBuffer.numChannels;
    int endOfHeader = ftell(input);
    fseek(input, blockSize * -1, SEEK_END);
    BYTE audioBuffer[blockSize];

    while (ftell(input) >= endOfHeader) {
        fread(audioBuffer, blockSize, 1, input);
        fwrite(audioBuffer, blockSize, 1, output);
        fseek(input, blockSize * -2, SEEK_CUR);
    }

    // printf("%ld\n", ftell(input));
    // fseek(input, 0, SEEK_END);
    // printf("%ld\n", ftell(input));
    // printf("%d\n", blockSize);

    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E') {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8);
}