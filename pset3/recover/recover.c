#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    // basic error checking to see if right no. of args are entered
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }


    char *imagePath = argv[1];
    // didnt bother checking if input is valid

    FILE *infile = fopen(imagePath, "r");
    if (!infile)
    {
        return 1;
    }

    uint8_t buffer[512];
    const uint8_t jpegHeaders[3] = { 0xff, 0xd8, 0xff };
    int num = 0;

    while (!feof(infile))
    {
        fread(buffer, sizeof(buffer), 1, infile);
        if (!memcmp(buffer, jpegHeaders, 3))
        {
            // found a block with matching jpeg headers, proceed to write jpg
            char fileName[8] = "";
            sprintf(fileName, "%03d.jpg", num);
            FILE *outfile = fopen(fileName, "w");

            do
            {
                fwrite(buffer, sizeof(buffer), 1, outfile);
                if (fread(buffer, sizeof(buffer), 1, infile) == 0) 
                    // fread returns no. of bytes read, so when its 0, it means everything is in
                    // the buffer and no more bytes can be read (i.e. EOF) hence we break out of loop
                    break;
            }
            while (memcmp(buffer, jpegHeaders, 3));
            // when we match another set of jpeg headers. break the loop and write the file.

            // finished writing one whole file. close and seek 1 block back
            num++;
            fclose(outfile);
            fseek(infile, -sizeof(buffer), SEEK_CUR);
        }
    }
    fclose(infile);
    return 0;
}
