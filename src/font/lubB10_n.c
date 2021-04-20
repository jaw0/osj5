
// file: font/lubB10.bdf
// font: -B&H-LucidaBright-DemiBold-R-Normal--10-100-75-75-P-59-ISO10646-1

#include <font.h>

const struct Font font_lubB10_n = {
    .type       = 1,
    .name	= "lubB10_n",
    .height	= 10,
    .width	= 8,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -5 },	// exclam
	{ .xadj =  -3 },	// quotedbl
	{ .xadj =  -1 },	// numbersign
	{ .xadj =  -2 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =   0 },	// ampersand
	{ .xadj =  -5 },	// quotesingle
	{ .xadj =  -5 },	// parenleft
	{ .xadj =  -5 },	// parenright
	{ .xadj =  -4 },	// asterisk
	{ .xadj =  -2 },	// plus
	{ .xadj =  -5 },	// comma
	{ .xadj =  -5 },	// hyphen
	{ .xadj =  -5 },	// period
	{ .xadj =  -3 },	// slash
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
	{ .xadj =  -5 },	// colon
	{ .xadj =  -5 },	// semicolon
	{ .xadj =  -2 },	// less
	{ .xadj =  -2 },	// equal
	{ .xadj =  -2 },	// greater
	{ .xadj =  -3 },	// question
    },
    .data       = {
	0x0, 0x0, 0xbf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x24, 0x0, 0xf4, 0x0, 0x2f, 0x0, 0xf4, 0x0, 0x2f, 0x0, 0x24, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0xc6, 0x0, 0x89, 0x0, 0xff, 0x1, 0xf3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x0, 0x0, 0x86, 0x0, 0x69, 0x0, 0x36, 0x0, 0x6c, 0x0, 0x96, 0x0, 0x61, 0x0, 0x0, 0x0, 	// 37	percent
	0x78, 0x0, 0xc6, 0x0, 0x8d, 0x0, 0xbd, 0x0, 0x66, 0x0, 0xf8, 0x0, 0x88, 0x0, 0x0, 0x0, 	// 38	ampersand
	0x3, 0x0, 0xf, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0xfe, 0x1, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x0, 0x1, 0x2, 0xfe, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x6, 0x0, 0x7, 0x0, 0x7, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x10, 0x0, 0x10, 0x0, 0x10, 0x0, 0xfe, 0x0, 0x10, 0x0, 0x10, 0x0, 0x10, 0x0, 0x0, 0x0, 	// 43	plus
	0xc0, 0x2, 0xc0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x20, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x80, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x3, 0xc0, 0x1, 0x30, 0x0, 0xe, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x3c, 0x0, 0xc3, 0x0, 0x81, 0x0, 0x81, 0x0, 0xc3, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x81, 0x0, 0xff, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0xc3, 0x0, 0xa1, 0x0, 0x91, 0x0, 0x8e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0xc3, 0x0, 0x89, 0x0, 0x89, 0x0, 0x76, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x18, 0x0, 0x14, 0x0, 0x93, 0x0, 0xff, 0x0, 0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0xcf, 0x0, 0x89, 0x0, 0x99, 0x0, 0x71, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x7c, 0x0, 0x8a, 0x0, 0x89, 0x0, 0x89, 0x0, 0x73, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0xc1, 0x0, 0x71, 0x0, 0x19, 0x0, 0x5, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x76, 0x0, 0x89, 0x0, 0x89, 0x0, 0x99, 0x0, 0x76, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0xce, 0x0, 0x91, 0x0, 0x91, 0x0, 0x53, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x88, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x88, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x10, 0x0, 0x10, 0x0, 0x28, 0x0, 0x6c, 0x0, 0x44, 0x0, 0x82, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x50, 0x0, 0x50, 0x0, 0x50, 0x0, 0x50, 0x0, 0x50, 0x0, 0x50, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x82, 0x0, 0x44, 0x0, 0x6c, 0x0, 0x28, 0x0, 0x10, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x3, 0x0, 0xb1, 0x0, 0x9, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
