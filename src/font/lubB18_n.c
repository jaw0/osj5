
// file: font/lubB18.bdf
// font: -B&H-LucidaBright-DemiBold-R-Normal--18-180-75-75-P-107-ISO10646-1

#include <font.h>

const struct Font font_lubB18_n = {
    .type       = 1,
    .name	= "lubB18_n",
    .height	= 18,
    .width	= 14,
    .bytescol	= 4,
    .numcol     = 14,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -9 },	// exclam
	{ .xadj =  -6 },	// quotedbl
	{ .xadj =  -2 },	// numbersign
	{ .xadj =  -3 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =   0 },	// ampersand
	{ .xadj =  -9 },	// quotesingle
	{ .xadj =  -8 },	// parenleft
	{ .xadj =  -8 },	// parenright
	{ .xadj =  -6 },	// asterisk
	{ .xadj =  -3 },	// plus
	{ .xadj =  -9 },	// comma
	{ .xadj =  -9 },	// hyphen
	{ .xadj =  -9 },	// period
	{ .xadj =  -5 },	// slash
	{ .xadj =  -3 },	// zero
	{ .xadj =  -3 },	// one
	{ .xadj =  -3 },	// two
	{ .xadj =  -3 },	// three
	{ .xadj =  -3 },	// four
	{ .xadj =  -3 },	// five
	{ .xadj =  -3 },	// six
	{ .xadj =  -3 },	// seven
	{ .xadj =  -3 },	// eight
	{ .xadj =  -3 },	// nine
	{ .xadj =  -9 },	// colon
	{ .xadj =  -9 },	// semicolon
	{ .xadj =  -3 },	// less
	{ .xadj =  -3 },	// equal
	{ .xadj =  -3 },	// greater
	{ .xadj =  -5 },	// question
    },
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0xfc, 0x70, 0x0, 0x0, 0xfc, 0x77, 0x0, 0x0, 0xfc, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x4, 0x0, 0x0, 0x40, 0x4, 0x0, 0x0, 0x40, 0x7c, 0x0, 0x0, 0xc0, 0x7, 0x0, 0x0, 0x78, 0x4, 0x0, 0x0, 0x44, 0x44, 0x0, 0x0, 0x40, 0x3c, 0x0, 0x0, 0xc0, 0x7, 0x0, 0x0, 0x7c, 0x4, 0x0, 0x0, 0x40, 0x4, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x78, 0x70, 0x0, 0x0, 0xfc, 0x60, 0x0, 0x0, 0xfc, 0x40, 0x0, 0x0, 0xc4, 0x41, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x4, 0x7f, 0x0, 0x0, 0x4, 0x7e, 0x0, 0x0, 0x1c, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0xf8, 0x40, 0x0, 0x0, 0xfc, 0x41, 0x0, 0x0, 0x4, 0x31, 0x0, 0x0, 0x4, 0x19, 0x0, 0x0, 0xfc, 0xd, 0x0, 0x0, 0xf8, 0x2, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x80, 0x3c, 0x0, 0x0, 0x60, 0x7e, 0x0, 0x0, 0x30, 0x42, 0x0, 0x0, 0x18, 0x42, 0x0, 0x0, 0x4, 0x7e, 0x0, 0x0, 0x4, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 37	percent
	0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x3f, 0x0, 0x0, 0x38, 0x7f, 0x0, 0x0, 0xfc, 0x61, 0x0, 0x0, 0xfc, 0x43, 0x0, 0x0, 0x84, 0x4f, 0x0, 0x0, 0x7c, 0x5e, 0x0, 0x0, 0x7c, 0x3c, 0x0, 0x0, 0x38, 0x70, 0x0, 0x0, 0x0, 0x79, 0x0, 0x0, 0x0, 0x6f, 0x0, 0x0, 0x0, 0x43, 0x0, 0x0, 0x0, 0x41, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x80, 0x1f, 0x0, 0x0, 0xe0, 0x7f, 0x0, 0x0, 0xf0, 0xff, 0x0, 0x0, 0x18, 0x80, 0x1, 0x0, 0x4, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x4, 0x0, 0x2, 0x0, 0x18, 0x80, 0x1, 0x0, 0xf0, 0xff, 0x0, 0x0, 0xe0, 0x7f, 0x0, 0x0, 0x80, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x10, 0x0, 0x0, 0x0, 0xb8, 0x0, 0x0, 0x0, 0xe0, 0x1, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0xe0, 0x1, 0x0, 0x0, 0xb0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0xf0, 0x7f, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x2, 0x0, 0x0, 0xf0, 0x3, 0x0, 0x0, 0xf0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x7, 0x0, 0x0, 0xf0, 0x1f, 0x0, 0x0, 0xf8, 0x3f, 0x0, 0x0, 0x1c, 0x70, 0x0, 0x0, 0x4, 0x40, 0x0, 0x0, 0x4, 0x40, 0x0, 0x0, 0x1c, 0x70, 0x0, 0x0, 0xf8, 0x3f, 0x0, 0x0, 0xf0, 0x1f, 0x0, 0x0, 0xc0, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x40, 0x0, 0x0, 0x4, 0x40, 0x0, 0x0, 0xfc, 0x7f, 0x0, 0x0, 0xfc, 0x7f, 0x0, 0x0, 0xfc, 0x7f, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0x0, 0x0, 0x18, 0x60, 0x0, 0x0, 0xc, 0x78, 0x0, 0x0, 0x4, 0x7c, 0x0, 0x0, 0x4, 0x74, 0x0, 0x0, 0x4, 0x72, 0x0, 0x0, 0x8c, 0x71, 0x0, 0x0, 0xfc, 0x71, 0x0, 0x0, 0xf8, 0x70, 0x0, 0x0, 0x70, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x0, 0x0, 0x1c, 0x70, 0x0, 0x0, 0xc, 0x41, 0x0, 0x0, 0x4, 0x41, 0x0, 0x0, 0x4, 0x41, 0x0, 0x0, 0x4, 0x41, 0x0, 0x0, 0x8c, 0x63, 0x0, 0x0, 0xfc, 0x7f, 0x0, 0x0, 0x78, 0x3e, 0x0, 0x0, 0x30, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x6, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x80, 0x6, 0x0, 0x0, 0x60, 0x6, 0x0, 0x0, 0x30, 0x6, 0x0, 0x0, 0x18, 0x46, 0x0, 0x0, 0xfc, 0x7f, 0x0, 0x0, 0xfc, 0x7f, 0x0, 0x0, 0xfc, 0x7f, 0x0, 0x0, 0x0, 0x46, 0x0, 0x0, 0x0, 0x46, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfc, 0x70, 0x0, 0x0, 0x8c, 0x40, 0x0, 0x0, 0x8c, 0x40, 0x0, 0x0, 0x8c, 0x41, 0x0, 0x0, 0x8c, 0x63, 0x0, 0x0, 0x8c, 0x7f, 0x0, 0x0, 0xc, 0x3f, 0x0, 0x0, 0xc, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x0, 0x0, 0xc0, 0xf, 0x0, 0x0, 0xf0, 0x1f, 0x0, 0x0, 0xf8, 0x3f, 0x0, 0x0, 0x1c, 0x61, 0x0, 0x0, 0x8c, 0x40, 0x0, 0x0, 0x84, 0x40, 0x0, 0x0, 0x84, 0x61, 0x0, 0x0, 0x84, 0x7f, 0x0, 0x0, 0x1c, 0x3f, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x1c, 0x60, 0x0, 0x0, 0x1c, 0x78, 0x0, 0x0, 0x1c, 0x7e, 0x0, 0x0, 0x1c, 0x7, 0x0, 0x0, 0x9c, 0x1, 0x0, 0x0, 0xdc, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x0, 0x0, 0x70, 0x1c, 0x0, 0x0, 0x78, 0x3e, 0x0, 0x0, 0xfc, 0x7e, 0x0, 0x0, 0xcc, 0x61, 0x0, 0x0, 0x84, 0x41, 0x0, 0x0, 0x84, 0x43, 0x0, 0x0, 0x8c, 0x67, 0x0, 0x0, 0x7c, 0x7f, 0x0, 0x0, 0x78, 0x3e, 0x0, 0x0, 0x38, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf8, 0x71, 0x0, 0x0, 0xfc, 0x43, 0x0, 0x0, 0xc, 0x43, 0x0, 0x0, 0x4, 0x42, 0x0, 0x0, 0x4, 0x62, 0x0, 0x0, 0xc, 0x71, 0x0, 0x0, 0xf8, 0x3f, 0x0, 0x0, 0xf0, 0x1f, 0x0, 0x0, 0xe0, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x71, 0x0, 0x0, 0xc0, 0x71, 0x0, 0x0, 0xc0, 0x71, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x61, 0x2, 0x0, 0xc0, 0xe1, 0x3, 0x0, 0xc0, 0xe1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x5, 0x0, 0x0, 0x0, 0x5, 0x0, 0x0, 0x80, 0x8, 0x0, 0x0, 0x80, 0x8, 0x0, 0x0, 0x40, 0x10, 0x0, 0x0, 0x40, 0x10, 0x0, 0x0, 0x20, 0x20, 0x0, 0x0, 0x30, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x0, 0x0, 0x30, 0x60, 0x0, 0x0, 0x20, 0x20, 0x0, 0x0, 0x40, 0x10, 0x0, 0x0, 0x40, 0x10, 0x0, 0x0, 0x80, 0x8, 0x0, 0x0, 0x80, 0x8, 0x0, 0x0, 0x0, 0x5, 0x0, 0x0, 0x0, 0x5, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x4, 0x74, 0x0, 0x0, 0x4, 0x76, 0x0, 0x0, 0x8c, 0x77, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
