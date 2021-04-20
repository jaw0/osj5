
// file: font/luBS24.bdf
// font: -B&H-Lucida-Bold-R-Normal-Sans-24-240-75-75-P-152-ISO10646-1

#include <font.h>

const struct Font font_luBS24_n = {
    .type       = 1,
    .name	= "luBS24_n",
    .height	= 25,
    .width	= 22,
    .bytescol	= 4,
    .numcol     = 22,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj = -14 },	// exclam
	{ .xadj =  -9 },	// quotedbl
	{ .xadj =  -6 },	// numbersign
	{ .xadj =  -6 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =  -3 },	// ampersand
	{ .xadj = -16 },	// quotesingle
	{ .xadj = -13 },	// parenleft
	{ .xadj = -13 },	// parenright
	{ .xadj = -11 },	// asterisk
	{ .xadj =  -6 },	// plus
	{ .xadj = -14 },	// comma
	{ .xadj = -15 },	// hyphen
	{ .xadj = -14 },	// period
	{ .xadj =  -8 },	// slash
	{ .xadj =  -6 },	// zero
	{ .xadj =  -6 },	// one
	{ .xadj =  -6 },	// two
	{ .xadj =  -6 },	// three
	{ .xadj =  -6 },	// four
	{ .xadj =  -6 },	// five
	{ .xadj =  -6 },	// six
	{ .xadj =  -6 },	// seven
	{ .xadj =  -6 },	// eight
	{ .xadj =  -6 },	// nine
	{ .xadj = -14 },	// colon
	{ .xadj = -14 },	// semicolon
	{ .xadj =  -6 },	// less
	{ .xadj =  -6 },	// equal
	{ .xadj =  -6 },	// greater
	{ .xadj =  -8 },	// question
    },
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0x7, 0xe, 0x0, 0xf8, 0x7f, 0xe, 0x0, 0xf8, 0x7f, 0xe, 0x0, 0xf8, 0x7f, 0xe, 0x0, 0xf8, 0x7, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0xfc, 0x3, 0x0, 0x0, 0xfc, 0x3, 0x0, 0x0, 0xfc, 0x3, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0xfc, 0x3, 0x0, 0x0, 0xfc, 0x3, 0x0, 0x0, 0xfc, 0x3, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x80, 0x61, 0x0, 0x0, 0x80, 0x61, 0xe, 0x0, 0x80, 0xf1, 0xf, 0x0, 0x80, 0xff, 0x1, 0x0, 0xe0, 0x7f, 0x0, 0x0, 0xf8, 0x61, 0x0, 0x0, 0x98, 0x61, 0xe, 0x0, 0x80, 0xe1, 0xf, 0x0, 0x80, 0xff, 0x3, 0x0, 0xe0, 0x7f, 0x0, 0x0, 0xf8, 0x61, 0x0, 0x0, 0xb8, 0x61, 0x0, 0x0, 0x80, 0x21, 0x0, 0x0, 0x80, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x0, 0xe0, 0x3, 0xe, 0x0, 0xf0, 0x7, 0xe, 0x0, 0xf8, 0x7, 0xe, 0x0, 0xf8, 0xf, 0xe, 0x0, 0x3f, 0xff, 0x7f, 0x0, 0xff, 0xff, 0x7f, 0x0, 0xff, 0x3f, 0x7e, 0x0, 0x38, 0x7c, 0xe, 0x0, 0x38, 0xf8, 0xf, 0x0, 0x38, 0xf0, 0x7, 0x0, 0x38, 0xe0, 0x7, 0x0, 0x0, 0xc0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0xe0, 0x1, 0x0, 0x0, 0xf0, 0x3, 0x0, 0x0, 0xf8, 0x7, 0x8, 0x0, 0x38, 0x7, 0xc, 0x0, 0x38, 0x7, 0xe, 0x0, 0x38, 0x87, 0xf, 0x0, 0xf8, 0xc7, 0x7, 0x0, 0xf0, 0xe3, 0x3, 0x0, 0xe0, 0xf1, 0x0, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x1f, 0x0, 0x0, 0x80, 0xe7, 0x3, 0x0, 0xc0, 0xf3, 0x7, 0x0, 0xf0, 0xf9, 0xf, 0x0, 0xf8, 0x38, 0xe, 0x0, 0x38, 0x38, 0xe, 0x0, 0x18, 0x38, 0xe, 0x0, 0x8, 0xf8, 0xf, 0x0, 0x0, 0xf0, 0x7, 0x0, 0x0, 0xe0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 37	percent
	0x0, 0xe0, 0x1, 0x0, 0x0, 0xf0, 0x3, 0x0, 0x0, 0xf8, 0x7, 0x0, 0xe0, 0xfc, 0x7, 0x0, 0xf0, 0xff, 0xf, 0x0, 0xf8, 0xf, 0xf, 0x0, 0xf8, 0x1f, 0xe, 0x0, 0xf8, 0x3f, 0xe, 0x0, 0x38, 0xff, 0xe, 0x0, 0x38, 0xff, 0xf, 0x0, 0xf8, 0xff, 0x7, 0x0, 0xf8, 0xfb, 0x7, 0x0, 0xf0, 0xe1, 0xf, 0x0, 0xe0, 0xc0, 0xf, 0x0, 0x0, 0xfc, 0xf, 0x0, 0x0, 0xfc, 0xc, 0x0, 0x0, 0x7c, 0x8, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0xfc, 0x3, 0x0, 0x0, 0xfc, 0x3, 0x0, 0x0, 0xfc, 0x3, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0x0, 0x0, 0x0, 0xfc, 0x1, 0x0, 0x80, 0xff, 0xf, 0x0, 0xc0, 0xff, 0x1f, 0x0, 0xe0, 0xff, 0x3f, 0x0, 0xf0, 0xff, 0x7f, 0x0, 0xf8, 0x1, 0xfc, 0x0, 0x3c, 0x0, 0xe0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x0, 0x0, 0x0, 0x3c, 0x0, 0xe0, 0x1, 0xf8, 0x1, 0xfc, 0x0, 0xf0, 0xff, 0x7f, 0x0, 0xe0, 0xff, 0x3f, 0x0, 0xc0, 0xff, 0x1f, 0x0, 0x80, 0xff, 0xf, 0x0, 0x0, 0xfc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0xf0, 0x6, 0x0, 0x0, 0xc0, 0xe, 0x0, 0x0, 0x58, 0x7, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x58, 0xf, 0x0, 0x0, 0xc0, 0x6, 0x0, 0x0, 0xf0, 0x6, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0xc0, 0xff, 0xf, 0x0, 0xc0, 0xff, 0xf, 0x0, 0xc0, 0xff, 0xf, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0xcf, 0x0, 0x0, 0x80, 0xef, 0x0, 0x0, 0x80, 0x7f, 0x0, 0x0, 0x80, 0x7f, 0x0, 0x0, 0x80, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0xf, 0x0, 0x0, 0x80, 0xf, 0x0, 0x0, 0x80, 0xf, 0x0, 0x0, 0x80, 0xf, 0x0, 0x0, 0x80, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0xfe, 0x0, 0x0, 0x80, 0x3f, 0x0, 0x0, 0xe0, 0x7, 0x0, 0x0, 0xf8, 0x1, 0x0, 0x0, 0x7f, 0x0, 0x0, 0xc0, 0x1f, 0x0, 0x0, 0xf0, 0x7, 0x0, 0x0, 0xfc, 0x1, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0x0, 0x0, 0xc0, 0xff, 0x1, 0x0, 0xe0, 0xff, 0x3, 0x0, 0xf0, 0xff, 0x7, 0x0, 0xf0, 0xff, 0x7, 0x0, 0x78, 0x0, 0xf, 0x0, 0x38, 0x0, 0xe, 0x0, 0x38, 0x0, 0xe, 0x0, 0x38, 0x0, 0xe, 0x0, 0x78, 0x0, 0xf, 0x0, 0xf0, 0xff, 0x7, 0x0, 0xf0, 0xff, 0x7, 0x0, 0xe0, 0xff, 0x3, 0x0, 0xc0, 0xff, 0x1, 0x0, 0x0, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0xf8, 0xff, 0xf, 0x0, 0xf8, 0xff, 0xf, 0x0, 0xf8, 0xff, 0xf, 0x0, 0xf8, 0xff, 0xf, 0x0, 0xf8, 0xff, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0x0, 0x0, 0x70, 0x0, 0xf, 0x0, 0x70, 0x80, 0xf, 0x0, 0x38, 0x80, 0xf, 0x0, 0x38, 0xc0, 0xf, 0x0, 0x38, 0xe0, 0xf, 0x0, 0x38, 0xf0, 0xe, 0x0, 0x38, 0x78, 0xe, 0x0, 0x78, 0x7c, 0xe, 0x0, 0xf8, 0x3f, 0xe, 0x0, 0xf8, 0x1f, 0xe, 0x0, 0xf0, 0xf, 0xe, 0x0, 0xe0, 0x7, 0xe, 0x0, 0xc0, 0x3, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x0, 0x7, 0x0, 0x30, 0x0, 0xf, 0x0, 0x38, 0x1c, 0xe, 0x0, 0x38, 0x1c, 0xe, 0x0, 0x38, 0x1c, 0xe, 0x0, 0x38, 0x1c, 0xe, 0x0, 0x78, 0x1e, 0xe, 0x0, 0xf8, 0x3f, 0xf, 0x0, 0xf8, 0xff, 0xf, 0x0, 0xf0, 0xff, 0x7, 0x0, 0xf0, 0xf3, 0x7, 0x0, 0xe0, 0xe1, 0x7, 0x0, 0x0, 0xc0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0xfe, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0x80, 0xef, 0x0, 0x0, 0xc0, 0xe7, 0x0, 0x0, 0xe0, 0xe1, 0x0, 0x0, 0xf0, 0xe0, 0x0, 0x0, 0xf8, 0xff, 0xf, 0x0, 0xf8, 0xff, 0xf, 0x0, 0xf8, 0xff, 0xf, 0x0, 0xf8, 0xff, 0xf, 0x0, 0xf8, 0xff, 0xf, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0xf, 0x7, 0x0, 0xf8, 0xf, 0xe, 0x0, 0xf8, 0xf, 0xe, 0x0, 0x38, 0xe, 0xe, 0x0, 0x38, 0xe, 0xe, 0x0, 0x38, 0x1e, 0xe, 0x0, 0x38, 0x1e, 0xf, 0x0, 0x38, 0xfc, 0xf, 0x0, 0x38, 0xfc, 0x7, 0x0, 0x38, 0xfc, 0x7, 0x0, 0x38, 0xf8, 0x3, 0x0, 0x38, 0xe0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0x0, 0x0, 0xc0, 0xff, 0x1, 0x0, 0xe0, 0xff, 0x3, 0x0, 0xf0, 0xff, 0x7, 0x0, 0xf0, 0xff, 0xf, 0x0, 0xf8, 0x1c, 0xf, 0x0, 0x78, 0xe, 0xe, 0x0, 0x38, 0xe, 0xe, 0x0, 0x38, 0x1e, 0xf, 0x0, 0x38, 0xfe, 0xf, 0x0, 0x38, 0xfe, 0x7, 0x0, 0x38, 0xfc, 0x7, 0x0, 0x70, 0xfc, 0x3, 0x0, 0x0, 0xf0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0xe, 0x0, 0x38, 0x80, 0xf, 0x0, 0x38, 0xe0, 0xf, 0x0, 0x38, 0xf0, 0xf, 0x0, 0x38, 0xfc, 0xf, 0x0, 0x38, 0xfe, 0x0, 0x0, 0x38, 0x3f, 0x0, 0x0, 0xb8, 0xf, 0x0, 0x0, 0xf8, 0x7, 0x0, 0x0, 0xf8, 0x3, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x3, 0x0, 0xe0, 0xe1, 0x7, 0x0, 0xf0, 0xf3, 0x7, 0x0, 0xf0, 0xff, 0xf, 0x0, 0xf8, 0xff, 0xf, 0x0, 0x38, 0x1f, 0xf, 0x0, 0x38, 0xe, 0xe, 0x0, 0x38, 0x1e, 0xe, 0x0, 0x78, 0x1e, 0xe, 0x0, 0xf8, 0x3f, 0xf, 0x0, 0xf0, 0xff, 0x7, 0x0, 0xf0, 0xfb, 0x7, 0x0, 0xe0, 0xf1, 0x3, 0x0, 0x0, 0xe0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x7, 0x0, 0x0, 0xe0, 0x1f, 0x7, 0x0, 0xf0, 0x1f, 0xe, 0x0, 0xf0, 0x3f, 0xe, 0x0, 0xf8, 0x3f, 0xe, 0x0, 0x78, 0x3c, 0xe, 0x0, 0x38, 0x38, 0xe, 0x0, 0x38, 0x18, 0xf, 0x0, 0x78, 0x9c, 0xf, 0x0, 0xf8, 0xff, 0x7, 0x0, 0xf0, 0xff, 0x7, 0x0, 0xe0, 0xff, 0x3, 0x0, 0xc0, 0xff, 0x1, 0x0, 0x0, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x8f, 0xf, 0x0, 0x80, 0x8f, 0xf, 0x0, 0x80, 0x8f, 0xf, 0x0, 0x80, 0x8f, 0xf, 0x0, 0x80, 0x8f, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x8f, 0xcf, 0x0, 0x80, 0x8f, 0xef, 0x0, 0x80, 0x8f, 0x7f, 0x0, 0x80, 0x8f, 0x7f, 0x0, 0x80, 0x8f, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0xce, 0x1, 0x0, 0x0, 0xce, 0x1, 0x0, 0x0, 0x87, 0x3, 0x0, 0x0, 0x87, 0x3, 0x0, 0x80, 0x3, 0x7, 0x0, 0x80, 0x3, 0x7, 0x0, 0xc0, 0x1, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x0, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x8e, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x1, 0xe, 0x0, 0x80, 0x3, 0x7, 0x0, 0x80, 0x3, 0x7, 0x0, 0x0, 0x87, 0x3, 0x0, 0x0, 0x87, 0x3, 0x0, 0x0, 0xce, 0x1, 0x0, 0x0, 0xce, 0x1, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x38, 0x60, 0xe, 0x0, 0x38, 0x70, 0xe, 0x0, 0x38, 0x78, 0xe, 0x0, 0x78, 0x7c, 0xe, 0x0, 0xf8, 0x7f, 0xe, 0x0, 0xf8, 0xf, 0x0, 0x0, 0xf0, 0x7, 0x0, 0x0, 0xf0, 0x3, 0x0, 0x0, 0xe0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
