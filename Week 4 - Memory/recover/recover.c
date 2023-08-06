#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// New type to store a byte of data
typedef uint8_t BYTE;

// Number of "block size" 512
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check for 2 command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open memory card (aka card.raw)
    FILE *input = fopen(argv[1], "r");
    {
        // check for fail to peon
        if (input == NULL)
        {
            printf("The forensic image cannot be opened for reading\n");
            return 1;
        }
    }

    // 1 block size = 512 bytes
    BYTE buffer[BLOCK_SIZE];

    // Declare jpeg filename size
    char filename[8];

    // Count image
    int count_image = 0;

    FILE *output = NULL;

    // Repeat until end of the card
    // Read 512 bytes into a buffer
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // If start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if it is the firstc JPEG
            if (count_image == 0)
            {
                sprintf(filename, "%03i.jpg", count_image);
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    printf("jpeg file cannot be opened\n");
                    return 2;
                }
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);
                count_image++;
            }
            // if already found a JPEG
            else if (count_image > 0)
            {
                fclose(output);
                sprintf(filename, "%03i.jpg", count_image);
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    printf("jpeg file cannot be opened\n");
                    return 2;
                }
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);
                count_image++;
            }
        }
        // If it is not the start of the JPEG
        // if already found JPEG
        else if (count_image > 0)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);
        }
    }
    fclose(output);
    fclose(input);
}
