
// file: font/timBI08.bdf
// font: -Adobe-Times-Bold-I-Normal--8-80-75-75-P-47-ISO10646-1

#include <font.h>

const struct Font font_timBI08_n = {
    .type       = 1,
    .name	= "timBI08_n",
    .height	= 8,
    .width	= 9,
    .lineheight = 8,
    .bytescol	= 1,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -4 },	// exclam
	{ .xadj =  -4 },	// quotedbl
	{ .xadj =  -3 },	// numbersign
	{ .xadj =  -5 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =  -3 },	// ampersand
	{ .xadj =  -5 },	// quotesingle
	{ .xadj =  -4 },	// parenleft
	{ .xadj =  -4 },	// parenright
	{ .xadj =  -3 },	// asterisk
	{ .xadj =  -3 },	// plus
	{ .xadj =  -6 },	// comma
	{ .xadj =  -7 },	// hyphen
	{ .xadj =  -6 },	// period
	{ .xadj =  -5 },	// slash
	{ .xadj =  -5 },	// zero
	{ .xadj =  -5 },	// one
	{ .xadj =  -5 },	// two
	{ .xadj =  -5 },	// three
	{ .xadj =  -5 },	// four
	{ .xadj =  -5 },	// five
	{ .xadj =  -5 },	// six
	{ .xadj =  -5 },	// seven
	{ .xadj =  -5 },	// eight
	{ .xadj =  -5 },	// nine
	{ .xadj =  -7 },	// colon
	{ .xadj =  -5 },	// semicolon
	{ .xadj =  -4 },	// less
	{ .xadj =  -3 },	// equal
	{ .xadj =  -4 },	// greater
	{ .xadj =  -5 },	// question
    },
    .data       = {
	0x0, 0x0, 0x2c, 0x2f, 0x3, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x3, 0x1, 0x3, 0x1, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x0, 0x1a, 0x1f, 0xb, 0x1e, 0xb, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x24, 0x6e, 0x3b, 0x12, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x0, 0x4, 0xe, 0x2a, 0x14, 0x8, 0x14, 0x3a, 0x28, 	// 37	percent
	0x0, 0x10, 0x3c, 0x2e, 0x2a, 0x1a, 0x28, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0x38, 0x7c, 0x86, 0x1, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x80, 0x61, 0x3e, 0x1c, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0x2, 0x7, 0x7, 0x2, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x8, 0x38, 0x3e, 0xe, 0x8, 0x0, 0x0, 0x0, 	// 43	plus
	0x40, 0x70, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x8, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x30, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0x78, 0x7f, 0x7, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x3c, 0x3e, 0x22, 0x1e, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x34, 0x3e, 0xe, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x30, 0x3a, 0x2e, 0x26, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x20, 0x2a, 0x3e, 0x16, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x18, 0x34, 0x3e, 0x16, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x30, 0x2e, 0x1a, 0x2, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x3c, 0x2e, 0x1a, 0x2, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x30, 0x3a, 0xe, 0x6, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x34, 0x3e, 0x2a, 0x16, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x2c, 0x3a, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x30, 0x34, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x40, 0x70, 0x34, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x18, 0x3c, 0x24, 0x2, 0x2, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x14, 0x14, 0x14, 0x14, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x20, 0x12, 0x1e, 0xc, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x29, 0x2d, 0x7, 0x2, 0x0, 0x0, 0x0, 	// 63	question
    }
};
