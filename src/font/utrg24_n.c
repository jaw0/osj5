
// file: font/utrg24.bdf
// font: -Adobe-Utopia-Regular-R-Normal--25-240-75-75-P-135-ISO10646-1

#include <font.h>

const struct Font font_utrg24_n = {
    .type       = 1,
    .name	= "utrg24_n",
    .height	= 22,
    .width	= 20,
    .bytescol	= 4,
    .numcol     = 20,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj = -14 },	// exclam
	{ .xadj =  -9 },	// quotedbl
	{ .xadj =  -7 },	// numbersign
	{ .xadj =  -7 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =  -2 },	// ampersand
	{ .xadj = -13 },	// quotesingle
	{ .xadj = -12 },	// parenleft
	{ .xadj = -12 },	// parenright
	{ .xadj = -10 },	// asterisk
	{ .xadj =  -6 },	// plus
	{ .xadj = -13 },	// comma
	{ .xadj = -10 },	// hyphen
	{ .xadj = -14 },	// period
	{ .xadj =  -9 },	// slash
	{ .xadj =  -7 },	// zero
	{ .xadj =  -7 },	// one
	{ .xadj =  -7 },	// two
	{ .xadj =  -7 },	// three
	{ .xadj =  -7 },	// four
	{ .xadj =  -7 },	// five
	{ .xadj =  -7 },	// six
	{ .xadj =  -7 },	// seven
	{ .xadj =  -7 },	// eight
	{ .xadj =  -7 },	// nine
	{ .xadj = -14 },	// colon
	{ .xadj = -14 },	// semicolon
	{ .xadj =  -6 },	// less
	{ .xadj =  -6 },	// equal
	{ .xadj =  -6 },	// greater
	{ .xadj = -10 },	// question
    },
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0xfc, 0x1f, 0x7, 0x0, 0xfc, 0x1f, 0x7, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfc, 0x1, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfc, 0x1, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x10, 0x0, 0x0, 0x80, 0xd0, 0x1, 0x0, 0x80, 0xfc, 0x1, 0x0, 0xc0, 0x3f, 0x0, 0x0, 0xf8, 0x13, 0x0, 0x0, 0xb8, 0x10, 0x0, 0x0, 0x80, 0xd0, 0x1, 0x0, 0x80, 0xfc, 0x1, 0x0, 0xc0, 0x3f, 0x0, 0x0, 0xf8, 0x13, 0x0, 0x0, 0xb8, 0x10, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x0, 0x0, 0x60, 0x0, 0x3, 0x0, 0xf8, 0x1, 0x3, 0x0, 0xf8, 0x3, 0x6, 0x0, 0x8c, 0x3, 0x4, 0x0, 0x4, 0x7, 0x4, 0x0, 0xff, 0xff, 0x3f, 0x0, 0x4, 0xe, 0x4, 0x0, 0xc, 0x1c, 0x6, 0x0, 0x18, 0xfc, 0x3, 0x0, 0x18, 0xf8, 0x3, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x0, 0x0, 0x0, 0x0, 0xf0, 0x1, 0x0, 0x0, 0xf8, 0x3, 0x0, 0x0, 0xc, 0x6, 0x0, 0x0, 0x4, 0x4, 0x6, 0x0, 0x4, 0x4, 0x3, 0x0, 0xc, 0xc6, 0x0, 0x0, 0xf8, 0x63, 0x0, 0x0, 0xf8, 0x19, 0x0, 0x0, 0x8, 0xc, 0x0, 0x0, 0x8, 0x3, 0x0, 0x0, 0x88, 0xf1, 0x1, 0x0, 0x68, 0xf8, 0x3, 0x0, 0x38, 0xc, 0x6, 0x0, 0xc, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x0, 0x0, 0xc, 0x6, 0x0, 0x0, 0xf8, 0x3, 0x0, 0x0, 0xf0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 37	percent
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf8, 0x1, 0x0, 0x70, 0xfc, 0x3, 0x0, 0xf8, 0xe, 0x3, 0x0, 0xf8, 0x7, 0x6, 0x0, 0x8c, 0x3, 0x4, 0x0, 0x4, 0x7, 0x4, 0x0, 0x4, 0x1f, 0x4, 0x0, 0x8c, 0x39, 0x4, 0x0, 0xf8, 0x70, 0x4, 0x0, 0x70, 0xe0, 0x2, 0x0, 0x0, 0xc0, 0x3, 0x0, 0x0, 0x80, 0x3, 0x0, 0x0, 0x80, 0x7, 0x0, 0x0, 0x7e, 0x6, 0x0, 0x0, 0x3e, 0x4, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfc, 0x1, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0xff, 0x3, 0x0, 0xf0, 0xff, 0xf, 0x0, 0x38, 0x0, 0x1c, 0x0, 0xc, 0x0, 0x30, 0x0, 0x4, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x20, 0x0, 0xc, 0x0, 0x30, 0x0, 0x38, 0x0, 0x1c, 0x0, 0xf0, 0xff, 0xf, 0x0, 0xc0, 0xff, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0xb0, 0x1, 0x0, 0x0, 0xb0, 0x1, 0x0, 0x0, 0xa0, 0x0, 0x0, 0x0, 0x40, 0x6, 0x0, 0x0, 0xfc, 0x7, 0x0, 0x0, 0x4c, 0x0, 0x0, 0x0, 0xa0, 0x0, 0x0, 0x0, 0xb0, 0x1, 0x0, 0x0, 0xb0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x80, 0xff, 0x7, 0x0, 0x80, 0xff, 0x7, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x22, 0x0, 0x0, 0x0, 0x17, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0xe0, 0x7, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0x1f, 0x0, 0x0, 0xe0, 0x3, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x7f, 0x0, 0x0, 0xf0, 0xff, 0x1, 0x0, 0xf8, 0xff, 0x3, 0x0, 0x8, 0x0, 0x2, 0x0, 0x4, 0x0, 0x4, 0x0, 0x4, 0x0, 0x4, 0x0, 0x4, 0x0, 0x4, 0x0, 0x8, 0x0, 0x2, 0x0, 0xf8, 0xff, 0x3, 0x0, 0xf0, 0xff, 0x1, 0x0, 0xc0, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x4, 0x0, 0x10, 0x0, 0x4, 0x0, 0x18, 0x0, 0x4, 0x0, 0xf8, 0xff, 0x7, 0x0, 0xfc, 0xff, 0x7, 0x0, 0xfc, 0xff, 0x7, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x7, 0x0, 0x78, 0x80, 0x7, 0x0, 0x38, 0xc0, 0x6, 0x0, 0xc, 0x60, 0x6, 0x0, 0x4, 0x20, 0x6, 0x0, 0x4, 0x10, 0x6, 0x0, 0x4, 0x18, 0x6, 0x0, 0xc, 0xe, 0x6, 0x0, 0xf8, 0x7, 0x6, 0x0, 0xf8, 0x3, 0x6, 0x0, 0xf0, 0x1, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x0, 0x0, 0x30, 0x80, 0x1, 0x0, 0x78, 0xc0, 0x3, 0x0, 0x38, 0x80, 0x3, 0x0, 0xc, 0x2, 0x6, 0x0, 0x4, 0x2, 0x4, 0x0, 0x4, 0x2, 0x4, 0x0, 0x4, 0x2, 0x4, 0x0, 0xc, 0x7, 0x6, 0x0, 0xf8, 0xfd, 0x3, 0x0, 0xf8, 0xfd, 0x3, 0x0, 0xf0, 0xf8, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x2c, 0x0, 0x0, 0x0, 0x27, 0x0, 0x0, 0xc0, 0x21, 0x0, 0x0, 0xf0, 0x20, 0x4, 0x0, 0x3c, 0x20, 0x4, 0x0, 0x9c, 0xff, 0x7, 0x0, 0xcc, 0xff, 0x7, 0x0, 0xe0, 0xff, 0x7, 0x0, 0x0, 0x20, 0x4, 0x0, 0x0, 0x20, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x1, 0x0, 0xfc, 0xc7, 0x3, 0x0, 0xc, 0x82, 0x3, 0x0, 0xc, 0x1, 0x6, 0x0, 0xc, 0x1, 0x4, 0x0, 0xc, 0x1, 0x4, 0x0, 0xc, 0x1, 0x4, 0x0, 0xc, 0x3, 0x6, 0x0, 0xc, 0xfe, 0x3, 0x0, 0xc, 0xfe, 0x3, 0x0, 0x4, 0xfc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x7f, 0x0, 0x0, 0xf0, 0xff, 0x1, 0x0, 0xf8, 0xff, 0x3, 0x0, 0x8, 0x4, 0x2, 0x0, 0x4, 0x2, 0x4, 0x0, 0x4, 0x2, 0x4, 0x0, 0x4, 0x2, 0x4, 0x0, 0xc, 0x6, 0x2, 0x0, 0x38, 0xfc, 0x3, 0x0, 0x78, 0xfc, 0x1, 0x0, 0x30, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x80, 0x3, 0x0, 0xc, 0xe0, 0x7, 0x0, 0xc, 0xf8, 0x3, 0x0, 0xc, 0x1e, 0x0, 0x0, 0xc, 0x3, 0x0, 0x0, 0xcc, 0x0, 0x0, 0x0, 0x6c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x0, 0x0, 0x60, 0xf0, 0x0, 0x0, 0xf8, 0xfd, 0x3, 0x0, 0xf8, 0xfd, 0x3, 0x0, 0xc, 0x7, 0x6, 0x0, 0x4, 0x2, 0x4, 0x0, 0x4, 0x2, 0x4, 0x0, 0x4, 0x2, 0x4, 0x0, 0xc, 0x7, 0x6, 0x0, 0xf8, 0xfd, 0x3, 0x0, 0xf8, 0xfd, 0x3, 0x0, 0x60, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x81, 0x1, 0x0, 0xf0, 0xc7, 0x3, 0x0, 0xf8, 0x87, 0x3, 0x0, 0x8, 0xc, 0x6, 0x0, 0x4, 0x8, 0x4, 0x0, 0x4, 0x8, 0x4, 0x0, 0x4, 0x8, 0x4, 0x0, 0x8, 0x4, 0x2, 0x0, 0xf8, 0xff, 0x3, 0x0, 0xf0, 0xff, 0x1, 0x0, 0xc0, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x2, 0x0, 0xc0, 0x1, 0x7, 0x0, 0xc0, 0x1, 0x7, 0x0, 0x80, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x22, 0x0, 0xc0, 0x1, 0x17, 0x0, 0xc0, 0x1, 0xf, 0x0, 0x80, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0xcc, 0x0, 0x0, 0x0, 0xcc, 0x0, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x3, 0x3, 0x0, 0x0, 0x3, 0x3, 0x0, 0x80, 0x1, 0x6, 0x0, 0x80, 0x1, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x0, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x0, 0x0, 0x80, 0x1, 0x6, 0x0, 0x80, 0x1, 0x6, 0x0, 0x0, 0x3, 0x3, 0x0, 0x0, 0x3, 0x3, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0xcc, 0x0, 0x0, 0x0, 0xcc, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x18, 0x2, 0x0, 0xc, 0x3c, 0x7, 0x0, 0x4, 0x36, 0x7, 0x0, 0xc, 0x23, 0x2, 0x0, 0xfc, 0x1, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
