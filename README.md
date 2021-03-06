# PS3 BDF/FNT unicode fonts library
A simple standard C library to use fonts in Glyph Bitmap Distribution Format (BDF) and Loadable Font File (FNT) formats, in any standard psl1ght RSX 3D project, but not Tiny3Ds.

The Glyph Bitmap Distribution Format is an ancient file format by Adobe, for storing bitmap fonts.
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

## BDF font repositories

You can find many places where download BDF fonts, like:

[Rockbox](https://github.com/mguentner/rockbox/tree/master/fonts), [Dr Markus Kuhn - X11 fonts](https://www.cl.cam.ac.uk/~mgk25/ucs-fonts.html), 
[IBM fonts](https://github.com/farsil/ibmfonts), etc. etc.

Thanks to Timothy Redaelli aka @drizzt for his FNT35 font from [GaiaManager](https://github.com/drizzt/GaiaManager).

## Usage

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
int SetCurrentFont_fnt(fnt_class* fnt, u8 i);
setPosition_fnt(fnt_class* fntc, s32 x, s32 y);
setColor_fnt(fnt_class* fntc, f32 r, f32 g, f32 b, f32 a);
setSafeArea_fnt(fnt_class* fntc, s32 left, s32 right, s32 top, s32 bottom);
getSafeArea_fnt(fnt_class* fntc, s32* pLeft, s32* pRight, s32* pTop, s32* pBottom);
setDimension_fnt(fnt_class* fntc, u32 w, u32 h)
void shutdown_fnt(fnt_class* fntc);
 ```

 ## Antialiasing level

 When you init/load a font, you can select 3 different levels of Antaliasing.
 
 Level 0 (No antialising):
 
 ![image1](level0.png?raw=true)

 Level 1:
 
 ![image1](level1.png?raw=true)

 Level 2:
 
 ![image2](level2.png?raw=true)

 
 ### Sample
 ![sample](image.png?raw=true)