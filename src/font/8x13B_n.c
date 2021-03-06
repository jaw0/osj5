
// file: font/8x13B.bdf
// font: -Misc-Fixed-Bold-R-Normal--13-120-75-75-C-80-ISO10646-1

#include <font.h>

const struct Font font_8x13B_n = {
    .type       = 1,
    .name	= "8x13B_n",
    .height	= 13,
    .width	= 8,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 63,
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfe, 0x6, 0xfe, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x1e, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0xb0, 0x1, 0xfc, 0x7, 0xfc, 0x7, 0xb0, 0x1, 0xfc, 0x7, 0xfc, 0x7, 0xb0, 0x1, 0x0, 0x0, 	// 35	numbersign
	0x38, 0x2, 0x7c, 0x6, 0x64, 0x4, 0xfe, 0xf, 0xc4, 0x4, 0xcc, 0x7, 0x88, 0x3, 0x0, 0x0, 	// 36	dollar
	0xe, 0x6, 0xa, 0x7, 0xce, 0x1, 0xf0, 0x0, 0x38, 0x7, 0xe, 0x5, 0x6, 0x7, 0x0, 0x0, 	// 37	percent
	0x60, 0x3, 0xf0, 0x7, 0x90, 0x4, 0x90, 0x4, 0xf0, 0x7, 0x60, 0x7, 0x0, 0x5, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0xe0, 0x0, 0xf8, 0x3, 0x1c, 0x7, 0x6, 0xc, 0x2, 0x8, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x0, 0x2, 0x8, 0x6, 0xc, 0x1c, 0x7, 0xf8, 0x3, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x20, 0x0, 0x20, 0x3, 0xe0, 0x1, 0xf8, 0x0, 0xe0, 0x1, 0x20, 0x3, 0x20, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x60, 0x0, 0x60, 0x0, 0xf8, 0x1, 0xf8, 0x1, 0x60, 0x0, 0x60, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x0, 0x0, 0x80, 0x8, 0x80, 0xf, 0x80, 0x7, 0x80, 0x3, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x7, 0x0, 0x7, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x7, 0x80, 0x3, 0xc0, 0x0, 0x60, 0x0, 0x30, 0x0, 0x1c, 0x0, 0xe, 0x0, 0x0, 0x0, 	// 47	slash
	0xf8, 0x1, 0xfc, 0x3, 0x6, 0x6, 0x2, 0x4, 0x6, 0x6, 0xfc, 0x3, 0xf8, 0x1, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x8, 0x4, 0xc, 0x4, 0xfe, 0x7, 0xfe, 0x7, 0x0, 0x4, 0x0, 0x4, 0x0, 0x0, 	// 49	one
	0xc, 0x6, 0xe, 0x7, 0x82, 0x5, 0xc2, 0x4, 0x62, 0x4, 0x3e, 0x4, 0x1c, 0x4, 0x0, 0x0, 	// 50	two
	0x2, 0x2, 0x2, 0x6, 0x22, 0x4, 0x32, 0x4, 0x3a, 0x4, 0xee, 0x7, 0xc6, 0x3, 0x0, 0x0, 	// 51	three
	0xe0, 0x0, 0xf0, 0x0, 0x98, 0x0, 0x8c, 0x0, 0xfe, 0x7, 0xfe, 0x7, 0x80, 0x0, 0x0, 0x0, 	// 52	four
	0x3e, 0x2, 0x3e, 0x6, 0x32, 0x4, 0x12, 0x4, 0x12, 0x4, 0xf2, 0x7, 0xe2, 0x3, 0x0, 0x0, 	// 53	five
	0xf8, 0x3, 0xfc, 0x7, 0x66, 0x6, 0x22, 0x4, 0x22, 0x4, 0xe2, 0x7, 0xc0, 0x3, 0x0, 0x0, 	// 54	six
	0x2, 0x0, 0x2, 0x0, 0x82, 0x7, 0xe2, 0x7, 0x72, 0x0, 0x1e, 0x0, 0xe, 0x0, 0x0, 0x0, 	// 55	seven
	0xdc, 0x3, 0xfe, 0x7, 0x22, 0x4, 0x22, 0x4, 0x22, 0x4, 0xfe, 0x7, 0xdc, 0x3, 0x0, 0x0, 	// 56	eight
	0x3c, 0x0, 0x7e, 0x4, 0x42, 0x4, 0x42, 0x4, 0x66, 0x6, 0xfe, 0x3, 0xfc, 0x1, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0x10, 0x2, 0x38, 0x7, 0x38, 0x7, 0x10, 0x2, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x0, 0x0, 0x90, 0x8, 0xb8, 0xf, 0xb8, 0x7, 0x90, 0x3, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x40, 0x0, 0xe0, 0x0, 0xb0, 0x1, 0x18, 0x3, 0xc, 0x6, 0x4, 0x4, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x4, 0x4, 0xc, 0x6, 0x18, 0x3, 0xb0, 0x1, 0xe0, 0x0, 0x40, 0x0, 0x0, 0x0, 	// 62	greater
	0xc, 0x0, 0xe, 0x0, 0x2, 0x0, 0xc2, 0x6, 0xe2, 0x6, 0x3e, 0x0, 0x1c, 0x0, 0x0, 0x0, 	// 63	question
    }
};
