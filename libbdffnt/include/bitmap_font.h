#ifndef __BITMAPFONT_H__
#define __BITMAPFONT_H__

#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include "bdffnt.h"


#define BITMAPFNT_PRIMITIVE					GCM_TYPE_QUADS
#define NUM_VERTS_PER_GLYPH					4
#define BITMAPFNT_GLYPH_WIDTH				16
#define BITMAPFNT_GLYPH_HEIGHT				18

#define BITMAPFNT_TAB_SIZE					4
#define BITMAPFNT_MAX_CHAR_COUNT			1024 //max char per frame
#define BITMAPFNT_DEFAULT_SAFE_AREA			00

#define MAX_STR								2048

void free_mem_fnt(fnt_class* fnt);
void printStart_fnt(fnt_class* fnt);
void printPass_fnt(Position* pPositions, TexCoord* pTexCoords, Color* pColors, s32 numVerts, u32* textmem_off, u32 tex_w, u32 tex_h, fnt_class* fnt);
void printEnd_fnt();

void printf_fnt(fnt_class* fnt, const char* pszText, ...);
u32 get_char_fnt(const char* string, u32 aa_level, u32* next_char, u16* fnt_width, fnt_class* fntc);
void read_header_fnt(fnt_t* fnt_p);
u8* get_bits_fnt(u32 ucs2, fnt_class* fntc);
int load_file_fnt(const char* path, struct fnt_class* fntc);
void load_mem_fnt(const void* ptr, fnt_class* fntc);
u32 get_width_ucs2_fnt(u32 ucs2, fnt_class* fntc);
u32 get_width_fnt(const char* str, int mx, fnt_class* fntc);
u8* init_table_fnt(u8* texture, fnt_class* fntc, u8 i);
void initShader_fnt(fnt_class* fntc);


char* utf8_utf16(u16* utf16, const char* utf8);
void utf8_to_utf16(u16* utf16, const char* utf8);

inline u16 utf16len(const u16* utf16)
{
	u16 len = 0;
	while (utf16[len] != '\0')
		len++;
	return len;
}

inline f32 calcPos(f32 pos, s32 dim)
{
	return (pos - ((f32)dim * 0.5f)) / ((f32)dim * 0.5f);
}



#endif // __BITMAPFONT_H__