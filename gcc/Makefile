SPIN2CPP=/home/ersmith/Parallax/spin2cpp/build/spin2cpp
P2GCC=/home/ersmith/Parallax/p2gcc/p2gcc -I .
#P2GCC=p2gcc

default: cdemo.bin

cdemo.bin: cdemo.c vgatext.c
	$(P2GCC) -o cdemo.bin cdemo.c vgatext.c vga_tile_driver.c

cdemo.c: ../cdemo.c
	cp $< $@

#vga_tile_driver.c: ../vga_tile_driver.spin 
#	cp $< $@
#	$(SPIN2CPP) -I.. --p2 --ccode vga_tile_driver.spin

vgatext.c: ../vgatext_800x600.spin2  ../vga_tile_driver.spin2 ../vga_text_routines.spinh
	cp $< vgatext.spin
	$(SPIN2CPP) -I.. --p2 --ccode vgatext.spin
