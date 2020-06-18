//
// fix up a .dat file (built by fastspin)
// to change the order of bytes so that all
// the bytes for the first scan line come first
// That is, it takes a font in "vertical"
// form (16 wide, 256*32 high) into "horizontal"
// form (16*256 wide, 32 high)
//
// the font size is hardcoded, as is the number of characters
// you can change these, but FONT_WIDTH must be a multiple of 8
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FONT_WIDTH 16
#define FONT_HEIGHT 32
#define FONT_CHARS 256

static void shuffle(unsigned char *inbuf, unsigned char *outbuf)
{
    int n;
    int x, y;
    int c;
    int outstride;

    outstride = (FONT_WIDTH * FONT_CHARS) / 8;
    
    for (n = 0; n < FONT_CHARS; n++) {
        for (y = 0; y < FONT_HEIGHT; y++) {
            for (x = 0; x < FONT_WIDTH/8; x++) {
                c = *inbuf++;
                outbuf[y * outstride + n * (FONT_WIDTH/8) + x] = c;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int bytes = FONT_WIDTH * FONT_HEIGHT * FONT_CHARS / 8;
    int r;
    FILE *f;
    unsigned char *inbuf = malloc(bytes);
    unsigned char *outbuf = malloc(bytes);
    
    if (argc != 3) {
        fprintf(stderr, "Usage: fixdat input.dat output.bin\n");
        return 2;
    }
    f = fopen(argv[1], "rb");
    if (!f) {
        perror(argv[1]);
        return 1;
    }
    r = fread(inbuf, 1, bytes, f);
    if (r != bytes) {
        fprintf(stderr, "read error: got %d bytes expected %d\n", r, bytes);
        return 1;
    }
    fclose(f);
    // HACK: force character 0 to be all 0's
    memset(inbuf, 0, FONT_WIDTH*FONT_HEIGHT/8);
    
    shuffle(inbuf, outbuf);
    f = fopen(argv[2], "wb");
    if (!f) {
        perror(argv[2]);
        return 1;
    }
    r = fwrite(outbuf, 1, bytes, f);
    if (r != bytes) {
        fprintf(stderr, "write error: sent %d bytes expected %d\n", r, bytes);
        return 1;
    }
    fclose(f);
    return 0;
}
