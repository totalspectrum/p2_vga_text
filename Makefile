zip: vgatile.zip

FONTS=unscii-16.bin unscii-16.bdf unscii-8.bin unscii-8.bdf unscii-8-fantasy.bin unscii-8-fantasy.bdf unscii-8-thin.bin unscii-8-thin.bdf

DRIVERS=vgatext_640x480.spin2 vgatext_800x600.spin2 vgatext_1024x768.spin2 vga_tile_driver.spin2 vga_text_routines.spinh std_text_routines.spinh
DEMOS=demo.spin2 cdemo.c basdemo.bas

vgatile.zip: README.txt $(FONTS) $(DRIVERS) $(DEMOS) makebitmap.c vga.map picture.ans
	rm -rf vgatile.zip
	zip -r vgatile.zip $^

%.bin: %.bdf makebitmap vga.map
	./makebitmap $< vga.map

%.bdf: %.pcf
	pcf2bdf -o $@ $<

makebitmap: makebitmap.c
