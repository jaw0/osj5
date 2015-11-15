
// file: font/luBS10.bdf
// font: -B&H-Lucida-Bold-R-Normal-Sans-10-100-75-75-P-66-ISO10646-1

#include <font.h>

const struct Font font_luBS10_n = {
    .type       = 1,
    .name	= "luBS10_n",
    .height	= 10,
    .width	= 9,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .data       = {
	0x0, 0x0, 0xce, 0x0, 0xde, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0xf, 0x0, 0x3, 0x0, 0x0, 0x0, 0xf, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x0, 0x28, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x0, 0x0, 0xfe, 0x0, 0x28, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x8c, 0x0, 0x9e, 0x0, 0xf2, 0x1, 0x9f, 0x0, 0xf2, 0x0, 0x62, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x4, 0x0, 0xa, 0x0, 0xce, 0x0, 0x64, 0x0, 0x10, 0x0, 0x4c, 0x0, 0xa6, 0x0, 0xe0, 0x0, 0x40, 0x0, 	// 37	percent
	0x0, 0x0, 0x64, 0x0, 0xfe, 0x0, 0x9a, 0x0, 0xbe, 0x0, 0x64, 0x0, 0xd0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0xf, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0x7c, 0x0, 0xfe, 0x0, 0x83, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x83, 0x1, 0xfe, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0xa, 0x0, 0xe, 0x0, 0x4, 0x0, 0xa, 0x0, 0xa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x10, 0x0, 0x10, 0x0, 0x7c, 0x0, 0x10, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0xc0, 0x2, 0xc0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x10, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0xc0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x80, 0x1, 0xe0, 0x1, 0x70, 0x0, 0x1c, 0x0, 0xf, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0x7c, 0x0, 0xfe, 0x0, 0x82, 0x0, 0x82, 0x0, 0xfe, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x4, 0x0, 0x4, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0xc4, 0x0, 0xe6, 0x0, 0xb2, 0x0, 0x92, 0x0, 0x9e, 0x0, 0x8c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x44, 0x0, 0xc6, 0x0, 0x92, 0x0, 0x92, 0x0, 0xfe, 0x0, 0x6c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x0, 0x30, 0x0, 0x28, 0x0, 0x24, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x5e, 0x0, 0xde, 0x0, 0x92, 0x0, 0x92, 0x0, 0xf2, 0x0, 0x62, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x7c, 0x0, 0xfe, 0x0, 0x92, 0x0, 0x92, 0x0, 0xf6, 0x0, 0x64, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x6, 0x0, 0xc6, 0x0, 0xe6, 0x0, 0x36, 0x0, 0x1e, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x6c, 0x0, 0xfe, 0x0, 0x92, 0x0, 0x92, 0x0, 0xfe, 0x0, 0x6c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x4c, 0x0, 0xde, 0x0, 0x92, 0x0, 0x92, 0x0, 0xfe, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0xcc, 0x0, 0xcc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0xcc, 0x2, 0xcc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x10, 0x0, 0x38, 0x0, 0x28, 0x0, 0x44, 0x0, 0x44, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x28, 0x0, 0x28, 0x0, 0x28, 0x0, 0x28, 0x0, 0x28, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x44, 0x0, 0x44, 0x0, 0x28, 0x0, 0x38, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x2, 0x0, 0xd2, 0x0, 0xd2, 0x0, 0x1e, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};