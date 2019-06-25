// C demo for VGA text objects
#define  VGA_BASEPIN 48

//
// sys/p2es_clock.h calculates clock mode settings
// to achieve a target speed of P2_TARGET_MHZ, and
// places the final clock setting and actual frequency
// in _SETFREQ and _CLOCKFREQ respectively
//
#define P2_TARGET_MHZ 200
#include <stdio.h>
#include <string.h>

extern void sleep(int);

// include the Spin object
#ifdef __FLEXC__
#include <sys/p2es_clock.h>
struct __using("vgatext_1024x768.spin2") vga;
#define vga_rows vga.rows
#define vga_cols vga.cols
#define vga_tx(c) vga.tx(c)
#define vga_dec(c) vga.dec(c)
#define vga_str(s) vga.str(s)
#define vga_start(pin) vga.start(pin)
#else
#include "p2es_clock.h"
#include "vgatext.h"

vgatext vga;
#define vga_rows VGATEXT_ROWS
#define vga_cols VGATEXT_COLS
#define vga_start(pin) vgatext_start(&vga, pin)
#define vga_tx(c) vgatext_tx(&vga, c)
#define vga_dec(c) vgatext_dec(&vga, c)
#define vga_str(s) vgatext_str(&vga, s)
#endif

#define ESC 27
//#define ESC 'E' // for debugging

// print a line of stars
static void starline() {
    int i;
    for (i = 0; i < vga_cols; i++) {
        vga_tx('*');
    }
}
static void blankline() {
    int i;
    vga_tx('*');
    for (i = 1; i < vga_cols-1; i++) {
        vga_tx(' ');
    }
    vga_tx('*');
}
static void gotoxy(int x, int y) {
    vga_tx(ESC);
    vga_tx('[');
    vga_dec(y);
    vga_tx(';');
    vga_dec(x);
    vga_tx('H');
}
    
static void center(const char *msg) {
    int n = strlen(msg);
    int y = vga_rows/2;
    int x = (vga_cols - n) / 2;
    gotoxy(x, y);
    vga_str(msg);
}


// main routine
void main()
{
    int i;
    int r;
    
    sleep(1);
    printf("start\n");
    sleep(1);
    
    clkset(_SETFREQ, _CLOCKFREQ);
    sleep(1);
    printf("done clock setting\n");
    r = vga_start(VGA_BASEPIN);
    printf("vga_start returned %d\n", r);
    
    starline();
    for (i = 1; i < vga_rows-1; i++) {
        blankline();
    }
    starline();
    center("Hello, world!");
    for(;;)
        ;
}
