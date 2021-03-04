# PS3 BDF/FNT unicode fonts library
A simple standard C library to use fonts in Glyph Bitmap Distribution Format (BDF) and Loadable Font File (FNT) formats, in any standard psl1ght RSX 3D project.

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
If you have a Linux and/or BSD system with an X server you probably already have a font server like xfs. You can use all the fonts available on this font server to create BDF files which you then can convert to FNT format. The procedure is quite easy:
```
fstobdf -s unix/:7100 -fn -misc-fixed-medium-r-normal--13-120-75-75-c-70-iso8859-1 > fixed-12.bdf
convbdf -f fixed-12.bdf
```
`fixed-12.fnt` will be created!

You can also load standard fixed array fonts, from memory, but they usually aren't unicode.

Usage:

make lib

 -- To make lib file
  
make install

 -- To make libs file and install into $PORTLIBS 
  
make

 -- To make example


 ## Public Functions
 ```
int init_fnt(gcmContextData* context, u32 display_width, u32 display_height, const char* path, u32 mb_rsx_mem, u32 aalevel, fnt_class* fntc);
void printn_fnt(fnt_class* fnt, const char* pszText, s32 count);
void print_fnt(fnt_class* fnt, const char* pszText);
void printf_fnt(fnt_class* fnt, const char* pszText, ...);
int addfnt_from_file_fnt(fnt_class* fnt, const char* pszText, u8 aa_level);
int addfnt_from_bitmap_array_fnt(fnt_class* fnt, u8* font, u8 first_char, u8 last_char, int w, int h, int bits_per_pixel, int byte_order, u8 aa_level);
void shutdown_fnt(fnt_class* fntc);
 ```