SPIN2CPP=/home/ersmith/Parallax/spin2cpp/build/spin2cpp
FASTSPIN=/home/ersmith/Parallax/spin2cpp/build/fastspin
CATALINA=/home/ersmith/Parallax/catalina/bin/catalina

#GCC=/home/ersmith/Parallax/p2gcc/p2gcc
GCC=riscv-none-embed-gcc -Os -T riscvp2.ld


default: gcc catalina flexc flexc_spin

gcc: cdemo.c vgatext.c
	$(GCC) -o gcc.bin cdemo.c vgatext.c vga_tile_driver.c

catalina: cdemo.c vgatext.c
	$(CATALINA) -p2 -lci -C P2_EVAL -C NATIVE -o catalina cdemo.c vgatext.c vga_tile_driver.c

#
# flexc can be built in 2 ways
flexc: cdemo.c vgatext.c
	$(FASTSPIN) -2 -o flexc.bin cdemo.c vgatext.c vga_tile_driver.c

flexc_spin: cdemo.c vgatext.c
	$(FASTSPIN) -DUSE_SPIN_DIRECTLY -2 -o flexc_spin.bin cdemo.c

#vga_tile_driver.c: ../vga_tile_driver.spin 
#	cp $< $@
#	$(SPIN2CPP) -I.. --p2 --ccode vga_tile_driver.spin

vgatext.c: ../vgatext_800x600.spin2  ../vga_tile_driver.spin2 ../vga_text_routines.spinh
	cp $< vgatext.spin
	$(SPIN2CPP) -I.. --p2 --ccode vgatext.spin

clean:
	rm -f *.bin *.lst *.p2asm *.o

realclean: clean
	rm -f vgatext.* vga_tile_driver.*
