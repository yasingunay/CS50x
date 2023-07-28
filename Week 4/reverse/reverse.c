#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

#define HEADER_LONG 44

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc == 3)
    {
        int length = strlen(argv[1]);
        if (argv[1][length - 4] != '.' || argv[1][length - 3] != 'w' || argv[1][length - 2] != 'a' || argv[1][length - 1] != 'v')
        {
            printf("Input is not a WAV file.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Open INPUT file error\n");
        return 1;
    }

    // Read header
    WAVHEADER header;
    if (fread(&header, sizeof(WAVHEADER), 1, input) < 1)
    {
        printf("Read INPUT HEADER error\n");
        return 2;
    }

    // Use check_format to ensure WAV format
    if (check_format(header) == 0)
    {
        printf("Input is not a WAV file.");
        return 3;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Open OUTPUT file error\n");
        return 4;
    }

    // Write header to file
    if (fwrite(&header, sizeof(WAVHEADER), 1, output) < 1)
    {
        printf("Write OUTPUT HEADER file error\n");
        return 5;
    }

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    BYTE buffer[block_size];

    // Move forward one block from the end of the file
    if (fseek(input, block_size, SEEK_END) != 0)
    {
        return 6;
    }
    while (ftell(input) - block_size > sizeof(header))
    {
        // Come back two blocks from the curren position
        fseek(input, -2 * block_size, SEEK_CUR);
        if (fread(&buffer, block_size, 1, input) != 1)
        {
            printf("Read AUDIO DATA from input error\n");
            return 7;
        }
        if (fwrite(&buffer, block_size, 1, output) != 1)
        {
            printf("Write AUDIO DATA to output error\n");
            return 8;
        }
    }
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
        return 1;
    return 0;
}

int get_block_size(WAVHEADER header)
{
    int block_size = ((header.bitsPerSample * header.numChannels) / 8);
    return block_size;
}