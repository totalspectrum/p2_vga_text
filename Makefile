zip: vgatile.zip

FONTS=unscii-16.bin unscii-16.bdf unscii-8.bin unscii-8.bdf unscii-8-fantasy.bin unscii-8-fantasy.bdf unscii-8-thin.bin unscii-8-thin.bdf

vgatile.zip: README.txt $(FONTS) makebitmap.c vga.map vga640x480.spin2 vga800x600.spin2 vga1024x768.spin2 vga_tile_driver.spin2 vga_text_routines.spinh std_text_routines.spinh picture.ans
	rm -rf vgatile.zip
	zip -r vgatile.zip $^

%.bin: %.bdf makebitmap vga.map
	./makebitmap $< vga.map

%.bdf: %.pcf
	pcf2bdf -o $@ $<

makebitmap: makebitmap.c
