
// file: font/uti12.bdf
// font: -Adobe-Utopia-Regular-I-Normal--12-120-75-75-P-67-ISO10646-1

#include <font.h>

const struct Font font_uti12_n = {
    .type       = 1,
    .name	= "uti12_n",
    .height	= 12,
    .width	= 10,
    .bytescol	= 2,
    .numcol     = 10,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -7 },	// exclam
	{ .xadj =  -5 },	// quotedbl
	{ .xadj =  -4 },	// numbersign
	{ .xadj =  -3 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =  -1 },	// ampersand
	{ .xadj =  -6 },	// quotesingle
	{ .xadj =  -6 },	// parenleft
	{ .xadj =  -6 },	// parenright
	{ .xadj =  -5 },	// asterisk
	{ .xadj =  -3 },	// plus
	{ .xadj =  -7 },	// comma
	{ .xadj =  -5 },	// hyphen
	{ .xadj =  -7 },	// period
	{ .xadj =  -7 },	// slash
	{ .xadj =  -4 },	// zero
	{ .xadj =  -4 },	// one
	{ .xadj =  -4 },	// two
	{ .xadj =  -4 },	// three
	{ .xadj =  -4 },	// four
	{ .xadj =  -4 },	// five
	{ .xadj =  -4 },	// six
	{ .xadj =  -4 },	// seven
	{ .xadj =  -4 },	// eight
	{ .xadj =  -4 },	// nine
	{ .xadj =  -7 },	// colon
	{ .xadj =  -7 },	// semicolon
	{ .xadj =  -3 },	// less
	{ .xadj =  -3 },	// equal
	{ .xadj =  -3 },	// greater
	{ .xadj =  -4 },	// question
    },
    .data       = {
	0x0, 0x0, 0xe0, 0x2, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x0, 0x40, 0x0, 0xe8, 0x1, 0x5e, 0x0, 0xe8, 0x1, 0x5e, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x0, 0x3, 0x18, 0x6, 0xb4, 0x3, 0x72, 0x2, 0x6e, 0x1, 0xc3, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x24, 0x2, 0x92, 0x1, 0x4e, 0x0, 0xb4, 0x3, 0x4c, 0x2, 0x26, 0x1, 0xe0, 0x0, 	// 37	percent
	0x0, 0x0, 0xc0, 0x1, 0x20, 0x3, 0x1c, 0x2, 0x22, 0x2, 0xd2, 0x2, 0xc, 0x1, 0x80, 0x2, 0x60, 0x2, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0xe0, 0x7, 0x18, 0x8, 0x4, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x8, 0x0, 0x4, 0x2, 0x3, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0x14, 0x0, 0x8, 0x0, 0x3e, 0x0, 0x8, 0x0, 0x14, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x40, 0x0, 0xf0, 0x1, 0x40, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x8, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0x80, 0x3, 0x70, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0xe0, 0x1, 0x38, 0x2, 0xc, 0x2, 0x82, 0x1, 0xe2, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x80, 0x3, 0x72, 0x2, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0x80, 0x3, 0xc4, 0x2, 0x46, 0x2, 0x22, 0x2, 0x32, 0x3, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x0, 0x1, 0x4, 0x3, 0x26, 0x2, 0x22, 0x3, 0xf2, 0x1, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x0, 0xc0, 0x0, 0xb0, 0x0, 0x9c, 0x2, 0xc6, 0x3, 0xb8, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x0, 0x1, 0x18, 0x3, 0x16, 0x2, 0x12, 0x3, 0xe2, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0xe0, 0x1, 0x38, 0x2, 0x14, 0x2, 0x12, 0x3, 0xe2, 0x1, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x0, 0x0, 0x86, 0x3, 0xe2, 0x0, 0x32, 0x0, 0xa, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x80, 0x1, 0x5c, 0x2, 0x36, 0x2, 0x62, 0x3, 0xd2, 0x1, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x0, 0x3, 0x3c, 0x2, 0x46, 0x2, 0x42, 0x1, 0xe2, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x2, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x8, 0x0, 0x6, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x40, 0x0, 0x40, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0x10, 0x1, 0x10, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x0, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x10, 0x1, 0x10, 0x1, 0xa0, 0x0, 0xa0, 0x0, 0x40, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x0, 0x0, 0xc4, 0x2, 0xa2, 0x0, 0x12, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
