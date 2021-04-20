
// file: font/courO08.bdf
// font: -Adobe-Courier-Medium-O-Normal--8-80-75-75-M-50-ISO10646-1

#include <font.h>

const struct Font font_courO08_n = {
    .type       = 1,
    .name	= "courO08_n",
    .height	= 8,
    .width	= 6,
    .bytescol	= 1,
    .numcol     = 6,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -1 },	// exclam
	{ .xadj =  -1 },	// quotedbl
	{ .xadj =  -1 },	// numbersign
	{ .xadj =  -1 },	// dollar
	{ .xadj =  -1 },	// percent
	{ .xadj =  -1 },	// ampersand
	{ .xadj =   0 },	// quotesingle
	{ .xadj =  -1 },	// parenleft
	{ .xadj =  -1 },	// parenright
	{ .xadj =  -1 },	// asterisk
	{ .xadj =  -1 },	// plus
	{ .xadj =  -1 },	// comma
	{ .xadj =  -1 },	// hyphen
	{ .xadj =  -1 },	// period
	{ .xadj =  -1 },	// slash
	{ .xadj =  -1 },	// zero
	{ .xadj =  -1 },	// one
	{ .xadj =  -1 },	// two
	{ .xadj =  -1 },	// three
	{ .xadj =  -1 },	// four
	{ .xadj =  -1 },	// five
	{ .xadj =  -1 },	// six
	{ .xadj =  -1 },	// seven
	{ .xadj =  -1 },	// eight
	{ .xadj =  -1 },	// nine
	{ .xadj =  -1 },	// colon
	{ .xadj =  -1 },	// semicolon
	{ .xadj =  -1 },	// less
	{ .xadj =  -1 },	// equal
	{ .xadj =  -1 },	// greater
	{ .xadj =  -1 },	// question
    },
    .data       = {
	0x0, 0x0, 0x58, 0x6, 0x0, 0x0, 	// 33	exclam
	0x0, 0x8, 0x6, 0x8, 0x6, 0x0, 	// 34	quotedbl
	0x10, 0x74, 0x1e, 0x74, 0x1e, 0x4, 	// 35	numbersign
	0x40, 0xd8, 0x54, 0x36, 0x4, 0x0, 	// 36	dollar
	0x0, 0x2c, 0x16, 0x68, 0x34, 0x0, 	// 37	percent
	0x0, 0x60, 0x58, 0x34, 0x54, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x4, 0x3, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0x38, 0x44, 0x2, 0x0, 	// 40	parenleft
	0x0, 0x40, 0x22, 0x1c, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0xc, 0xe, 0x4, 0x0, 	// 42	asterisk
	0x0, 0x10, 0x70, 0x1c, 0x10, 0x0, 	// 43	plus
	0x0, 0x80, 0x40, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x10, 0x10, 0x10, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x40, 0x30, 0xc, 0x2, 0x0, 	// 47	slash
	0x0, 0x78, 0x44, 0x22, 0x1e, 0x0, 	// 48	zero
	0x40, 0x44, 0x74, 0x4e, 0x0, 0x0, 	// 49	one
	0x40, 0x64, 0x52, 0x4a, 0x6, 0x0, 	// 50	two
	0x20, 0x40, 0x4a, 0x3a, 0xc, 0x0, 	// 51	three
	0x10, 0x18, 0x74, 0x1e, 0x10, 0x0, 	// 52	four
	0x0, 0x48, 0x4e, 0x32, 0x2, 0x0, 	// 53	five
	0x0, 0x30, 0x4c, 0x4a, 0x32, 0x0, 	// 54	six
	0x0, 0x4, 0x72, 0xa, 0x6, 0x0, 	// 55	seven
	0x0, 0x70, 0x4c, 0x4a, 0x36, 0x0, 	// 56	eight
	0x40, 0x4c, 0x32, 0x12, 0xc, 0x0, 	// 57	nine
	0x0, 0x0, 0x40, 0x8, 0x0, 0x0, 	// 58	colon
	0x0, 0x80, 0x48, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x10, 0x28, 0x4, 0x0, 0x0, 	// 60	less
	0x20, 0x28, 0x28, 0x28, 0x8, 0x0, 	// 61	equal
	0x0, 0x20, 0x14, 0x8, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x44, 0x12, 0xc, 0x0, 	// 63	question
    }
};
