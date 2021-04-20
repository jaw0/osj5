
// file: font/luBIS08.bdf
// font: -B&H-Lucida-Bold-I-Normal-Sans-8-80-75-75-P-49-ISO10646-1

#include <font.h>

const struct Font font_luBIS08_n = {
    .type       = 1,
    .name	= "luBIS08_n",
    .height	= 9,
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
	{ .xadj =  -1 },	// percent
	{ .xadj =  -1 },	// ampersand
	{ .xadj =  -6 },	// quotesingle
	{ .xadj =  -5 },	// parenleft
	{ .xadj =  -5 },	// parenright
	{ .xadj =  -4 },	// asterisk
	{ .xadj =  -3 },	// plus
	{ .xadj =  -5 },	// comma
	{ .xadj =  -6 },	// hyphen
	{ .xadj =  -5 },	// period
	{ .xadj =  -3 },	// slash
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
	{ .xadj =  -3 },	// equal
	{ .xadj =  -3 },	// greater
	{ .xadj =  -4 },	// question
    },
    .data       = {
	0x40, 0x0, 0x5e, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x0, 0x68, 0x0, 0x78, 0x0, 0x6e, 0x0, 0x3a, 0x0, 0x2e, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x40, 0x0, 0xcc, 0x1, 0x7e, 0x0, 0x73, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x0, 0x0, 0x5c, 0x0, 0x32, 0x0, 0x1c, 0x0, 0x8, 0x0, 0x44, 0x0, 0x62, 0x0, 0x62, 0x0, 	// 37	percent
	0x0, 0x0, 0x30, 0x0, 0x48, 0x0, 0x4e, 0x0, 0x7a, 0x0, 0x66, 0x0, 0x18, 0x0, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0xe, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0xf8, 0x1, 0xc, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x1, 0xe2, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0xc, 0x0, 0xa, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x10, 0x0, 0x70, 0x0, 0x10, 0x0, 0x1c, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x40, 0x1, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x10, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x40, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x1, 0x80, 0x0, 0x60, 0x0, 0x18, 0x0, 0x4, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0x38, 0x0, 0x46, 0x0, 0x62, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x62, 0x0, 0x7e, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0x40, 0x0, 0x62, 0x0, 0x52, 0x0, 0x4a, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x40, 0x0, 0x4a, 0x0, 0x4a, 0x0, 0x7a, 0x0, 0x26, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x10, 0x0, 0x18, 0x0, 0x54, 0x0, 0x7e, 0x0, 0x16, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x40, 0x0, 0x4e, 0x0, 0x4a, 0x0, 0x32, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x38, 0x0, 0x4c, 0x0, 0x4a, 0x0, 0x6a, 0x0, 0x12, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x42, 0x0, 0x32, 0x0, 0x1a, 0x0, 0x6, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x70, 0x0, 0x5c, 0x0, 0x4a, 0x0, 0x5a, 0x0, 0x36, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x48, 0x0, 0x56, 0x0, 0x52, 0x0, 0x32, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x48, 0x0, 0x48, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x40, 0x1, 0xc8, 0x1, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x10, 0x0, 0x30, 0x0, 0x28, 0x0, 0x48, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x28, 0x0, 0x28, 0x0, 0x28, 0x0, 0x28, 0x0, 0x28, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x40, 0x0, 0x20, 0x0, 0x2c, 0x0, 0x28, 0x0, 0x28, 0x0, 0x10, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x52, 0x0, 0x52, 0x0, 0xa, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
