// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // parsing runtime arguments
    float scaleFactor = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // save old bmp in a dynamically allocated 2d array first
    RGBTRIPLE **oldBmp = malloc(abs(bi.biHeight) * sizeof(RGBTRIPLE*));
    if (oldBmp)
    {
	    for (int i = 0, n = abs(bi.biHeight); i < n; i++)
	    {
		    oldBmp[i] = malloc(sizeof(RGBTRIPLE) * bi.biWidth);
	    }
    }

    // determine padding for infile scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // read RGB triple from infile
            fread(&(oldBmp[i][j]), sizeof(RGBTRIPLE), 1, inptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }
    fclose(inptr);

    int oldWidth = bi.biWidth;
    int oldHeight = abs(bi.biHeight);
    int newWidth = round(bi.biWidth * scaleFactor);
    int newHeight = round(abs(bi.biHeight) * scaleFactor);

    // need to change biWidth, biHeight (make sure its negative), biSizeImage
    bi.biWidth = newWidth;
    bi.biHeight = newHeight * -1;
    padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = newHeight * (newWidth * sizeof(RGBTRIPLE) + padding);
    // documentation is confusing but biSize is actually just sizeof(BITMAPINFOHEADER)
    // i.e. in this case its a fixed value of 40 bytes
 
    // need to calculate and change bfSize (total size of file) in bf
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    for (int i = 1, biHeight = abs(bi.biHeight); i <= biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 1; j <= bi.biWidth; j++)
        {
		// note that you need to cast the ints to float for division
		int col = ceil((float)i / (float)newHeight * (float)oldHeight);
		int row = ceil((float)j / (float)newWidth * (float)oldWidth);
                // write RGB triple to outfile
		// when accessing oldBmp indices, care to decrement by 1 as the array is indexed from 0
		// for the above col and row calculation, we cannot do the arithmetic starting from 0
		// or the resizing math will not work out. e.g. 1/3 != 0/2
		// hence, we must start counting with actual counting numbers
                fwrite(&(oldBmp[col - 1][row - 1]), sizeof(RGBTRIPLE), 1, outptr);
        }

	// add padding
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // free oldBmp
    for (int i = 0; i < oldHeight; i++)
    {
	    free(oldBmp[i]);
    }
    free(oldBmp);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
