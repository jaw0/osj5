
// file: font/timR10.bdf
// font: -Adobe-Times-Medium-R-Normal--10-100-75-75-P-54-ISO10646-1

#include <font.h>

const struct Font font_timR10_n = {
    .type       = 1,
    .name	= "timR10_n",
    .height	= 10,
    .width	= 8,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -5 },	// exclam
	{ .xadj =  -4 },	// quotedbl
	{ .xadj =  -3 },	// numbersign
	{ .xadj =  -3 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =   0 },	// ampersand
	{ .xadj =  -6 },	// quotesingle
	{ .xadj =  -4 },	// parenleft
	{ .xadj =  -4 },	// parenright
	{ .xadj =  -3 },	// asterisk
	{ .xadj =  -2 },	// plus
	{ .xadj =  -5 },	// comma
	{ .xadj =  -4 },	// hyphen
	{ .xadj =  -5 },	// period
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
	{ .xadj =  -5 },	// colon
	{ .xadj =  -5 },	// semicolon
	{ .xadj =  -3 },	// less
	{ .xadj =  -2 },	// equal
	{ .xadj =  -3 },	// greater
	{ .xadj =  -4 },	// question
    },
    .data       = {
	0x0, 0x0, 0xbe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x6, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x28, 0x0, 0xfe, 0x0, 0x28, 0x0, 0xfe, 0x0, 0x28, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0xcc, 0x0, 0x92, 0x0, 0x93, 0x1, 0x66, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0xc, 0x0, 0x92, 0x0, 0x6e, 0x0, 0x12, 0x0, 0x6a, 0x0, 0x96, 0x0, 0x72, 0x0, 0x0, 0x0, 	// 37	percent
	0x60, 0x0, 0x9c, 0x0, 0x9a, 0x0, 0xb6, 0x0, 0x68, 0x0, 0xd8, 0x0, 0x88, 0x0, 0x40, 0x0, 	// 38	ampersand
	0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x70, 0x0, 0x8c, 0x1, 0x2, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x2, 0x2, 0x8c, 0x1, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0xa, 0x0, 0x4, 0x0, 0xa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x20, 0x0, 0x20, 0x0, 0xf8, 0x0, 0x20, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x80, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x20, 0x0, 0x20, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0xc0, 0x0, 0x38, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x7c, 0x0, 0x82, 0x0, 0x82, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x84, 0x0, 0xfe, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x84, 0x0, 0xc2, 0x0, 0xb2, 0x0, 0x8c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x84, 0x0, 0x92, 0x0, 0x92, 0x0, 0x6c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x30, 0x0, 0x28, 0x0, 0x24, 0x0, 0xfe, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0xc8, 0x0, 0x8e, 0x0, 0x8a, 0x0, 0x72, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x78, 0x0, 0x8c, 0x0, 0x8a, 0x0, 0x72, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x6, 0x0, 0xe2, 0x0, 0x1a, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x6c, 0x0, 0x92, 0x0, 0x92, 0x0, 0x6c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x9c, 0x0, 0xa2, 0x0, 0x62, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x88, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x88, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x20, 0x0, 0x50, 0x0, 0x88, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x50, 0x0, 0x50, 0x0, 0x50, 0x0, 0x50, 0x0, 0x50, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x88, 0x0, 0x50, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x6, 0x0, 0xb2, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
