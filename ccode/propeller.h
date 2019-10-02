//
// propeller.h for p2gcc
// this is just enough to get the VGA demo working!
//

extern int cognew2(void *addr, void *param);
extern void clkset(unsigned int mode, unsigned int freq);

#define _clkfreq (*(unsigned int *)0x14)
#define cognew(x, y) cognew2(x, y)
#define cogstop(x)
