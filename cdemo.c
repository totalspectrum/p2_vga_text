// C demo for VGA text objects
#define  VGA_BASEPIN 48

//
// sys/p2es_clock.h calculates clock mode settings
// to achieve a target speed of P2_TARGET_MHZ, and
// places the final clock setting and actual frequency
// in _SETFREQ and _CLOCKFREQ respectively
//
#define P2_TARGET_MHZ 200
#include <sys/p2es_clock.h>
#include <string.h>

// include the Spin object
struct __using("vgatext_1024x768.spin2") vga;

#define ESC 27
//#define ESC 'E' // for debugging

// print a line of stars
static void starline() {
    int i;
    for (i = 0; i < vga.cols; i++) {
        vga.tx('*');
    }
}
static void blankline() {
    int i;
    vga.tx('*');
    for (i = 1; i < vga.cols-1; i++) {
        vga.tx(' ');
    }
    vga.tx('*');
}
static void gotoxy(int x, int y) {
    vga.tx(ESC);
    vga.tx('[');
    vga.dec(y);
    vga.tx(';');
    vga.dec(x);
    vga.tx('H');
}
    
static void center(const char *msg) {
    int n = strlen(msg);
    int y = vga.rows/2;
    int x = (vga.cols - n) / 2;
    gotoxy(x, y);
    vga.str(msg);
}

// main routine
void main()
{
    int i;
    clkset(_SETFREQ, _CLOCKFREQ);
    vga.start(VGA_BASEPIN);

    starline();
    for (i = 1; i < vga.rows-1; i++) {
        blankline();
    }
    starline();
    center("Hello, world!");
    for(;;)
        ;
}
