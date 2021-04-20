
// file: font/lubB14.bdf
// font: -B&H-LucidaBright-DemiBold-R-Normal--14-140-75-75-P-84-ISO10646-1

#include <font.h>

const struct Font font_lubB14_n = {
    .type       = 1,
    .name	= "lubB14_n",
    .height	= 14,
    .width	= 11,
    .bytescol	= 2,
    .numcol     = 11,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -7 },	// exclam
	{ .xadj =  -5 },	// quotedbl
	{ .xadj =  -2 },	// numbersign
	{ .xadj =  -2 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =   0 },	// ampersand
	{ .xadj =  -7 },	// quotesingle
	{ .xadj =  -6 },	// parenleft
	{ .xadj =  -6 },	// parenright
	{ .xadj =  -5 },	// asterisk
	{ .xadj =  -2 },	// plus
	{ .xadj =  -7 },	// comma
	{ .xadj =  -7 },	// hyphen
	{ .xadj =  -7 },	// period
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
	{ .xadj =  -7 },	// colon
	{ .xadj =  -7 },	// semicolon
	{ .xadj =  -2 },	// less
	{ .xadj =  -2 },	// equal
	{ .xadj =  -2 },	// greater
	{ .xadj =  -4 },	// question
    },
    .data       = {
	0x0, 0x0, 0x3e, 0x6, 0xfe, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x6, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x80, 0x0, 0x90, 0x4, 0xd0, 0x3, 0xbc, 0x0, 0x92, 0x4, 0xd0, 0x3, 0xbc, 0x0, 0x92, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x1c, 0x7, 0x1e, 0x6, 0x32, 0x4, 0xff, 0x1f, 0xc2, 0x7, 0x8e, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x1c, 0x4, 0x3e, 0x6, 0x22, 0x3, 0xbe, 0x1, 0x5c, 0x0, 0xa0, 0x3, 0xd8, 0x7, 0x4c, 0x4, 0xc6, 0x7, 0x82, 0x3, 0x0, 0x0, 	// 37	percent
	0x80, 0x3, 0xc0, 0x3, 0x3c, 0x6, 0x3e, 0x4, 0xf2, 0x4, 0x9e, 0x7, 0xc, 0x3, 0x20, 0x7, 0xe0, 0x4, 0x20, 0x4, 0x0, 0x0, 	// 38	ampersand
	0x6, 0x0, 0x1e, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0xe0, 0x3, 0xf8, 0xf, 0xc, 0x18, 0x2, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x2, 0x20, 0xc, 0x18, 0xf8, 0xf, 0xe0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0x1c, 0x0, 0x38, 0x0, 0x6, 0x0, 0x38, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x80, 0x0, 0x80, 0x0, 0x80, 0x0, 0x80, 0x0, 0xf8, 0x7, 0x80, 0x0, 0x80, 0x0, 0x80, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x0, 0x3e, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0xc0, 0x0, 0xc0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x6, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x20, 0x0, 0x18, 0x0, 0x6, 0xc0, 0x1, 0x30, 0x0, 0xc, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0xf8, 0x1, 0xfc, 0x3, 0x6, 0x6, 0x2, 0x4, 0x2, 0x4, 0x6, 0x6, 0xfc, 0x3, 0xf8, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x2, 0x4, 0x2, 0x4, 0xfe, 0x7, 0xfe, 0x7, 0x0, 0x4, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0xe, 0x6, 0x6, 0x7, 0x82, 0x6, 0xc2, 0x6, 0x66, 0x6, 0x3e, 0x6, 0x1c, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0xe, 0x7, 0x22, 0x4, 0x22, 0x4, 0x22, 0x4, 0x66, 0x6, 0xde, 0x3, 0x8c, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0xc0, 0x0, 0xe0, 0x0, 0xd0, 0x0, 0xc8, 0x0, 0xc6, 0x4, 0xfe, 0x7, 0xfe, 0x7, 0xc0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x0, 0x0, 0x3e, 0x7, 0x26, 0x4, 0x26, 0x4, 0x66, 0x6, 0xe6, 0x3, 0xc6, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0xf0, 0x1, 0xfc, 0x3, 0x46, 0x6, 0x22, 0x4, 0x22, 0x4, 0x62, 0x6, 0xee, 0x3, 0xc0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x6, 0x6, 0x6, 0x7, 0xc6, 0x1, 0x66, 0x0, 0x36, 0x0, 0xe, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x9c, 0x3, 0xde, 0x7, 0x32, 0x6, 0x62, 0x4, 0x62, 0x4, 0xde, 0x7, 0x8c, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x3c, 0x0, 0x7c, 0x7, 0x66, 0x4, 0x42, 0x4, 0x42, 0x4, 0x26, 0x6, 0xfc, 0x3, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x30, 0x6, 0x30, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x30, 0x3e, 0x30, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x40, 0x0, 0xc0, 0x0, 0xc0, 0x0, 0x20, 0x1, 0x20, 0x1, 0x10, 0x2, 0x10, 0x2, 0x8, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x8, 0x4, 0x10, 0x2, 0x10, 0x2, 0x20, 0x1, 0x20, 0x1, 0xc0, 0x0, 0xc0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0xe, 0x0, 0x82, 0x6, 0xc2, 0x6, 0x26, 0x0, 0x1e, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
