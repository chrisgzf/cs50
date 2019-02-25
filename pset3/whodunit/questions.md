# Questions

## What's `stdint.h`?

(copy pasted from wikipedia)

stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Easily denote how many bits each variable uses, and whether they are signed or unsigned. stdint.h also includes macros to easily check the minimum and maximum values of integers of certain bit widths.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

* BYTE - 1 byte (8 bits - unsigned)
* DWORD - 4 bytes (32 bits - unsigned)
* LONG - 4 bytes (32 bits - signed)
* WORD - 2 bytes (16 bits - unsigned)

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

bfType (WORD - 2 bytes) - specifies the file type. Must be 'BM'.

## What's the difference between `bfSize` and `biSize`?

(from documentation)
* bfSize - The size, in bytes, of the bitmap file.
* biSize - The number of bytes required by the structure.

I'm guessing bfSize is the total number of bytes required for the WHOLE file, whereas biSize specifies the number of bytes required only by the actual bitmap pixel information.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner. DIB stands for device-independent bitmaps.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

* biBitCount
The number of bits-per-pixel. The biBitCount member of the BITMAPINFOHEADER structure determines the number of bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in `copy.c`?

It might return NULL if there is a file IO error, which can include, but are not limited to:
* file does not exist
* no rights to read the file
* no rights to write a file in chosen directory
* no rights to write to an existing file
* other misc screwups (hardware errors, etc)

## Why is the third argument to `fread` always `1` in our code?

The specifications on what bytes to read in what order is already clearly defined by the structs in bmp.h, as such, since we are reading with sizeof(name-of-bmp-struct), and we only need to read it once (as per the file specifications), we only need to pass a third argument '1'.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4

As bi.biWidth = 3, and sizeof(RGBTRIPLE) = 3, the expression evaluates to 3.

## What does `fseek` do?

From ```man fseek```:
The fseek() function sets the file position indicator for the stream pointed to by stream.  The new position, measured in bytes, is obtained by adding offset bytes to the position specified by whence.  If whence is set to SEEK_SET, SEEK_CUR, or SEEK_END, the offset is relative to the start of the file, the current position indicator, or end-of-file, respectively. A successful call to the fseek() function clears the end-of-file indicator for the stream and undoes any effects of the ungetc(3) function on the same stream.

## What is `SEEK_CUR`?

Argument for fseek() such that it seeks from the current position indicator.
