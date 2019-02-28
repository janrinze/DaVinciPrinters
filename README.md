Initial repo for all things i learned and create using the Da Vinci 3D printers.

Da Vinci 1.1 plus:

+ Nice enclosure
+ pretty touchscreen interface
+ USB connector for printing from USB memory stick.
- decent prints from the xyzware app but just not what i was hoping for.
- filament issues, no support for other filament than PLA or ABS.
- temperature settings are fixed by the cartridge chip
- limited options for support material

Da Vinci 2.0A duo:

+ Same enclosure as 1.1 plus
+ simple LCD with buttons
- no USB connector for USB memory
- requires a computer (PC/laptop) connected over USB to print
- prints from xyzware cannot be created for dual extruder.
- all issues as above with Da Vinci 1.1 plus.

Using third party slicers:

- KISS slicer required a bit of persuasion to generate gcode that could be converted to .3w files and were printable on the 1.1 plus.
- Slic3r was difficult to tune to make reliable prints
+ Cura has been able to generate decent prints on both 1.1 plus and the 2.0A duo.

External tools to get .3w files:

+ openssl for base64 encoding
+ sed and grep for editing and filtering gcode
+ bash to stitch it together
+ gpr library to do extensive filtering on gcode for things like max speed of movements (too fast and the printer makes lots of scary noises)

