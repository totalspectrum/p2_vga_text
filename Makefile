FASTSPIN=/home/ersmith/Parallax/spin2cpp/build/fastspin

default:
	echo "make zip:            make a distribution zip file"
	echo "make demo.binary:    make Spin demo"
	echo "make basdemo.binary: make Basic demo"

zip: vgatile.zip

FONTS=unscii-16.bin unscii-16.bdf unscii-8.bin unscii-8.bdf unscii-8-fantasy.bin unscii-8-fantasy.bdf unscii-8-thin.bin unscii-8-thin.bdf spleen-16x32.bin spleen-16x32.bdf

CDRIVER=ccode/Makefile ccode/vgatext.c ccode/vgatext.h ccode/vga_tile_driver.c ccode/vga_tile_driver.h

DRIVERS=vgatext_640x480.spin2 vgatext_800x600.spin2 vgatext_1024x768.spin2 vgatext_1024_16x32.spin2 vga_tile_driver.spin2 vga_text_routines.spinh std_text_routines.spinh $(CDRIVER)

DEMOS=demo.spin2 basdemo.bas ccode/cdemo.c

vgatile.zip: README.txt Makefile $(FONTS) $(DRIVERS) $(DEMOS) makebitmap.c vga.map picture.ans
	rm -rf vgatile.zip
	zip -r vgatile.zip $^

%.bin: %.bdf makebitmap vga.map
	./makebitmap $< vga.map

%.bdf: %.pcf
	pcf2bdf -o $@ $<

demo.binary: demo.spin2 $(DRIVERS)
	$(FASTSPIN) -2 -o demo.binary demo.spin2
basdemo.binary: basdemo.bas vgatext_800x600.spin2 vga_tile_driver.spin2 vga_text_routines.spinh std_text_routines.spinh
	$(FASTSPIN) -2 -o basdemo.binary basdemo.bas

makebitmap: makebitmap.c
