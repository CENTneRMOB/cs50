#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //open file
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Cannot open the file\n");
        fclose(file);
        return 1;
    }

    uint8_t buffer[512];
    uint8_t signature[] = {0xff, 0xd8, 0xff};
    bool isWriting = false;
    int fileCounter = 0;

    char outputFileName[8];
    FILE *outputFile;

    while (fread(buffer, 1, 512, file) == 512)
    {
        if (buffer[0] == signature[0] && buffer[1] == signature[1] && buffer[2] == signature[2] && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (isWriting)
            {
                fclose(outputFile);
                isWriting = false;

                sprintf(outputFileName, "%03i.jpg", fileCounter);
                fileCounter += 1;
                outputFile = fopen(outputFileName, "w");
                fwrite(buffer, 1, 512, outputFile);
                isWriting = true;
            }
            else
            {
                sprintf(outputFileName, "%03i.jpg", fileCounter);
                fileCounter += 1;
                outputFile = fopen(outputFileName, "w");
                fwrite(buffer, 1, 512, outputFile);
                isWriting = true;
            }
        }
        else
        {
            if (isWriting)
            {
                fwrite(buffer, 1, 512, outputFile);
            }
            else
            {
                continue;
            }
        }
    }

    fclose(outputFile);
    fclose(file);
}