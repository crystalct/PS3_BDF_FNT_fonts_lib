#ifndef __FONTS_BITMAP_H__
#define __FONTS_BITMAP_H__

#include <ppu-types.h>
#include <rsx/rsx.h>
#include <stdarg.h>

#define MAX_CHARS_FNT			1600  //max char per session, unchangable
#define MAX_N_FNT				6  //max fonts number, unchangeable
#define RSX_LABEL_ID			254 // label rendering ID, unchangeable
#define BIT0_FIRST_PIXEL 0
#define BIT7_FIRST_PIXEL 1

typedef struct fnt_dyn {
	u32 fnt;
	u8* text;
	u32 offset;
	u32 r_use;
	u16 width;
	u16 height;
	u16 flags;

} fnt_dyn;

typedef struct fnt_t  {
	u8 isBDF;
	u16 maxwidth;
	u16 height;
	u16 ascent;
	u16 pad;
	u32 firstchar;
	u32 size;
	u32 defaultchar;
	u32 nbits;
	u32 noffset;
	u32 nwidth;
	const u8* bits;
	const u32* offset;
	const u8* width;
	u32 long_offset;
	u32 file_flag;
	void* fnt_ptr;
} fnt_t;

typedef struct Position
{
	f32 x, y, z;
} Position;

typedef struct TexCoord
{
	f32 s, t;
} TexCoord;

typedef struct Color
{
	f32 r, g, b, a;
} Color;


typedef struct fnt_class
{
	fnt_t fnt[MAX_N_FNT];
	u8 number_of_fonts;
	u8 current_font;
	s32 sXPos;
	s32 sYPos;
	f32 sR;
	f32 sG;
	f32 sB;
	f32 sA;
	u8 gly_w[MAX_N_FNT];
	u8 gly_h[MAX_N_FNT];
	s32 sXRes;
	s32 sYRes;
	s32 sLeftSafe;
	s32 sRightSafe;
	s32 sTopSafe;
	s32 sBottomSafe;
	u8 aa_level[MAX_N_FNT];
	u32 fnt_ux[MAX_N_FNT];
	u32 fnt_uy[MAX_N_FNT];
	u32 r_use;
	u32* ntex_off;
	fnt_dyn fnt_font_datas[MAX_N_FNT][MAX_CHARS_FNT];

	gcmContextData* mContext;
	u8* texture_mem;		//fnt_textures

	u8* next_mem;			// Pointer after last fnt texture

	u8* spTextureData;

	u8* mPosition;
	u8* mTexCoord;
	u8* mColor;

	u32 mPositionOffset;
	u32 mTexCoordOffset;
	u32 mColorOffset;

	u8* mpTexture;
	rsxProgramAttrib* mPosIndex;
	rsxProgramAttrib* mTexIndex;
	rsxProgramAttrib* mColIndex;
	rsxProgramAttrib* mTexUnit;

	rsxVertexProgram* mRSXVertexProgram;
	rsxFragmentProgram* mRSXFragmentProgram;

	u32 mFragmentProgramOffset;
	u32 mTextureOffset;

	void* mVertexProgramUCode;				// this is sysmem
	void* mFragmentProgramUCode;			// this is vidmem

	vu32* mLabel;
	u32 mLabelValue;

	u32 sLabelId;

	Position* spPositions[2];
	TexCoord* spTexCoords[2];
	Color* spColors[2];

	Color sDefaultColors[8];

	void (*read_header)(fnt_t* fnt_p);
	void (*load_mem)(const void* ptr, struct fnt_class* fntc);
	int (*load_file)(const char* path, struct fnt_class* fntc);
	void (*free_mem)(struct fnt_class* fnt);
	void (*initShader)(struct fnt_class* fntc);
	
	void (*printStart)(struct fnt_class* fnt);
	u8* (*init_table)(u8* texture, struct fnt_class* fnt, u8 i);
	u32(*get_char)(const char* string, u32 aa_level, u32* next_char, u16* fnt_width, struct fnt_class* fntc);
	u32(*get_width)(const char* str, int mx, struct fnt_class* fntc);
	u32(*get_width_ucs2)(u32 ucs2, struct fnt_class* fntc);
	u8* (*get_bits)(u32 ucs2, struct fnt_class* fntc);
	void (*printPass)(Position* pPositions, TexCoord* pTexCoords, Color* pColors, s32 numVerts, u32* textmem_off, u32 tex_w, u32 tex_h, struct fnt_class* fnt);
	void (*printEnd)(struct fnt_class* fnt);
	int (*vsprintf)(char* buffer, const char* format, va_list arg);
	
} fnt_class;

#ifdef __cplusplus
extern "C" {
#endif
int init_fnt(gcmContextData* context, u32 display_width, u32 display_height, const char* path, u32 mb_rsx_mem, u32 aalevel, fnt_class* fntc);
void printn_fnt(fnt_class* fnt, const char* pszText, s32 count);
void print_fnt(fnt_class* fnt, const char* pszText);
void printf_fnt(fnt_class* fnt, const char* pszText, ...);
int addfnt_from_file_fnt(fnt_class* fnt, const char* pszText, u8 aa_level);
int addfnt_from_bitmap_array_fnt(fnt_class* fnt, u8* font, u8 first_char, u8 last_char, int w, int h, int bits_per_pixel, int byte_order, u8 aa_level);
void shutdown_fnt(fnt_class* fntc);

inline int SetCurrentFont_fnt(fnt_class* fnt, u8 i)
{
	if (i > fnt->number_of_fonts - 1)
		return 1;

	fnt->current_font = i;
	return 0;
}

inline void setPosition_fnt(fnt_class* fntc, s32 x, s32 y)
{
	fntc->sXPos = x;
	fntc->sYPos = y;
}

inline void setColor_fnt(fnt_class* fntc, f32 r, f32 g, f32 b, f32 a)
{
	fntc->sR = r;
	fntc->sG = g;
	fntc->sB = b;
	fntc->sA = a;
}

inline void setSafeArea_fnt(fnt_class* fntc, s32 left, s32 right, s32 top, s32 bottom)
{
	fntc->sLeftSafe = left;
	fntc->sRightSafe = right;
	fntc->sTopSafe = top;
	fntc->sBottomSafe = bottom;
}

inline void getSafeArea_fnt(fnt_class* fntc, s32* pLeft, s32* pRight, s32* pTop, s32* pBottom)
{
	*pLeft = fntc->sLeftSafe;
	*pRight = fntc->sRightSafe;
	*pTop = fntc->sTopSafe;
	*pBottom = fntc->sBottomSafe;
}

inline void setDimension_fnt(fnt_class* fntc, u32 w, u32 h)
{
	fntc->gly_w[fntc->current_font] = w;
	fntc->gly_h[fntc->current_font] = h;
}

inline bool isPrintable_fnt(char c)
{
	return ((u8)c & 0x7f) > 31;
}

#ifdef __cplusplus
}
#endif

#endif // __FONTS_BITMAP_H__