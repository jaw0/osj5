
// file: font/luIS14.bdf
// font: -B&H-Lucida-Medium-I-Normal-Sans-14-140-75-75-P-82-ISO10646-1

#include <font.h>

const struct Font font_luIS14_n = {
    .type       = 1,
    .name	= "luIS14_n",
    .height	= 13,
    .width	= 11,
    .bytescol	= 2,
    .numcol     = 11,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -7 },	// exclam
	{ .xadj =  -6 },	// quotedbl
	{ .xadj =  -2 },	// numbersign
	{ .xadj =  -2 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =  -1 },	// ampersand
	{ .xadj =  -8 },	// quotesingle
	{ .xadj =  -6 },	// parenleft
	{ .xadj =  -6 },	// parenright
	{ .xadj =  -4 },	// asterisk
	{ .xadj =  -2 },	// plus
	{ .xadj =  -8 },	// comma
	{ .xadj =  -6 },	// hyphen
	{ .xadj =  -8 },	// period
	{ .xadj =  -4 },	// slash
	{ .xadj =  -2 },	// zero
	{ .xadj =  -2 },	// one
	{ .xadj =  -2 },	// two
	{ .xadj =  -2 },	// three
	{ .xadj =  -2 },	// four
	{ .xadj =  -2 },	// five
	{ .xadj =  -2 },	// six
	{ .xadj =  -2 },	// seven
	{ .xadj =  -2 },	// eight
	{ .xadj =  -2 },	// nine
	{ .xadj =  -8 },	// colon
	{ .xadj =  -8 },	// semicolon
	{ .xadj =  -2 },	// less
	{ .xadj =  -2 },	// equal
	{ .xadj =  -2 },	// greater
	{ .xadj =  -4 },	// question
    },
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0xe0, 0x6, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x90, 0x7, 0xf0, 0x0, 0x9e, 0x0, 0x90, 0x7, 0xf0, 0x0, 0x9e, 0x0, 0x10, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x1c, 0x4, 0xa2, 0xf, 0x62, 0x4, 0x5f, 0x4, 0x82, 0x3, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x0, 0x0, 0x0, 0x0, 0xc, 0x4, 0x12, 0x2, 0x12, 0x1, 0x8c, 0x0, 0x60, 0x0, 0x10, 0x3, 0x88, 0x4, 0x84, 0x4, 0x2, 0x3, 	// 37	percent
	0x0, 0x0, 0x0, 0x0, 0x80, 0x3, 0x40, 0x4, 0x2c, 0x4, 0x12, 0x4, 0x62, 0x4, 0x92, 0x2, 0x12, 0x3, 0x8c, 0x4, 0x60, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0x0, 0x0, 0xf0, 0x3, 0xc, 0x4, 0x2, 0x8, 0x1, 0x8, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x8, 0x1, 0x8, 0x1, 0x4, 0x2, 0x3, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x14, 0x0, 0x68, 0x0, 0x16, 0x0, 0x28, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x3, 0xe0, 0x0, 0x58, 0x0, 0x40, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x10, 0x0, 0x8, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0x0, 0x8, 0x0, 0x6, 0x0, 0x1, 0xc0, 0x0, 0x30, 0x0, 0x8, 0x0, 0x6, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x3, 0x38, 0x4, 0x4, 0x4, 0x2, 0x4, 0x2, 0x2, 0xc2, 0x1, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0xc4, 0x7, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x4, 0x5, 0x82, 0x4, 0x42, 0x4, 0x42, 0x4, 0x22, 0x4, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x4, 0x4, 0x22, 0x4, 0x22, 0x4, 0x22, 0x2, 0xd2, 0x1, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0xb0, 0x0, 0x88, 0x0, 0x84, 0x0, 0xc2, 0x7, 0xbe, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x30, 0x4, 0x2e, 0x4, 0x22, 0x4, 0x22, 0x2, 0xc2, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x3, 0x38, 0x4, 0x24, 0x4, 0x22, 0x4, 0x22, 0x2, 0xc2, 0x1, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x6, 0x82, 0x1, 0x42, 0x0, 0x22, 0x0, 0x12, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x0, 0x0, 0x80, 0x3, 0x5c, 0x4, 0x22, 0x4, 0x22, 0x4, 0x22, 0x4, 0xd2, 0x3, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x38, 0x4, 0x44, 0x4, 0x42, 0x4, 0x42, 0x2, 0xc2, 0x1, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x10, 0x0, 0x8, 0x0, 0x6, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0xa0, 0x0, 0x20, 0x1, 0x10, 0x2, 0x10, 0x0, 0x8, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0xa0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x2, 0x0, 0x1, 0x8, 0x1, 0x90, 0x0, 0xa0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x84, 0x6, 0x42, 0x0, 0x22, 0x0, 0x22, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
