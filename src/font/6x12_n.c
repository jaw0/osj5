
// file: font/6x12.bdf
// font: -Misc-Fixed-Medium-R-SemiCondensed--12-110-75-75-C-60-ISO10646-1

#include <font.h>

const struct Font font_6x12_n = {
    .type       = 1,
    .name	= "6x12_n",
    .height	= 12,
    .width	= 6,
    .bytescol	= 2,
    .numcol     = 6,
    .startchar  = 33,
    .lastchar	= 63,
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0xf8, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x20, 0x1, 0xf0, 0x3, 0x20, 0x1, 0xf0, 0x3, 0x20, 0x1, 0x0, 0x0, 	// 35	numbersign
	0x30, 0x1, 0x48, 0x2, 0xfc, 0x7, 0x48, 0x2, 0x90, 0x1, 0x0, 0x0, 	// 36	dollar
	0x18, 0x3, 0x98, 0x0, 0x40, 0x0, 0x20, 0x3, 0x18, 0x3, 0x0, 0x0, 	// 37	percent
	0xb0, 0x1, 0x48, 0x2, 0xb0, 0x2, 0x0, 0x1, 0x80, 0x2, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0xe0, 0x0, 0x18, 0x3, 0x4, 0x4, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x0, 0x4, 0x4, 0x18, 0x3, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x10, 0x1, 0xa0, 0x0, 0xf8, 0x3, 0xa0, 0x0, 0x10, 0x1, 0x0, 0x0, 	// 42	asterisk
	0x40, 0x0, 0x40, 0x0, 0xf0, 0x1, 0x40, 0x0, 0x40, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x4, 0x0, 0x7, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x3, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x2, 0x80, 0x1, 0x40, 0x0, 0x30, 0x0, 0x8, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0xf0, 0x1, 0x8, 0x2, 0x8, 0x2, 0xf0, 0x1, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x10, 0x2, 0xf8, 0x3, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x10, 0x2, 0x8, 0x3, 0x88, 0x2, 0x48, 0x2, 0x30, 0x2, 0x0, 0x0, 	// 50	two
	0x8, 0x1, 0x8, 0x2, 0x48, 0x2, 0x68, 0x2, 0x98, 0x1, 0x0, 0x0, 	// 51	three
	0xc0, 0x0, 0xa0, 0x0, 0x90, 0x0, 0xf8, 0x3, 0x80, 0x0, 0x0, 0x0, 	// 52	four
	0x38, 0x1, 0x28, 0x2, 0x28, 0x2, 0x28, 0x2, 0xc8, 0x1, 0x0, 0x0, 	// 53	five
	0xe0, 0x1, 0x50, 0x2, 0x48, 0x2, 0x48, 0x2, 0x80, 0x1, 0x0, 0x0, 	// 54	six
	0x8, 0x0, 0x8, 0x0, 0x88, 0x3, 0x68, 0x0, 0x18, 0x0, 0x0, 0x0, 	// 55	seven
	0xb0, 0x1, 0x48, 0x2, 0x48, 0x2, 0x48, 0x2, 0xb0, 0x1, 0x0, 0x0, 	// 56	eight
	0x30, 0x0, 0x48, 0x2, 0x48, 0x2, 0x48, 0x1, 0xf0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x60, 0x3, 0x60, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x4, 0x60, 0x7, 0x60, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x40, 0x0, 0xa0, 0x0, 0x10, 0x1, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0xa0, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x10, 0x1, 0xa0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x10, 0x0, 0x8, 0x0, 0xc8, 0x2, 0x28, 0x0, 0x10, 0x0, 0x0, 0x0, 	// 63	question
    }
};
