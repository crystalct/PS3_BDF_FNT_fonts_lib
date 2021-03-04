# PS3 BDF/FNT unicode fonts library
A simple standard C library to use fonts in Glyph Bitmap Distribution Format (BDF) and Loadable Font File (FNT) formats, usable in any standard psl1ght RSX 3D project.

The Glyph Bitmap Distribution Format is an ancient file format by Adobe is a, for storing bitmap fonts.
Loadable Font File (that isn't Windows Font File) is a simple binary font format used by [Rockbox](https://www.rockbox.org/). It is a fixed-size raster font format that supports unicode.
Using this library you can load directly FNT files from memory or from file. If you want use BDF file format you have to convert it to FNT file format using a convertor from Rockbox: [convbdf.exe](https://www.rockbox.org/wiki/pub/Main/RockboxFontConvertor/rockbox_font_convertor_v1.2.zip).
```
Usage convbdf.exe: convbdf [options] [input-files]
                   convbdf [options] [-o output-file] [single-input-file]
Options:
    -c     Convert .bdf to .c source file
    -f     Convert .bdf to .fnt font file
    -s N   Start output at character encodings >= N
    -l N   Limit output to character encodings <= N
    -n     Don't generate bitmaps as comments in .c file
```

Usage:

make lib

 -- To make lib file
  
make install

 -- To make libs file and install into $PORTLIBS 
  
make

 -- To make example
