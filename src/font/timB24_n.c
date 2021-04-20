
// file: font/timB24.bdf
// font: -Adobe-Times-Bold-R-Normal--24-240-75-75-P-132-ISO10646-1

#include <font.h>

const struct Font font_timB24_n = {
    .type       = 1,
    .name	= "timB24_n",
    .height	= 23,
    .width	= 21,
    .bytescol	= 4,
    .numcol     = 21,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj = -13 },	// exclam
	{ .xadj =  -9 },	// quotedbl
	{ .xadj =  -8 },	// numbersign
	{ .xadj =  -9 },	// dollar
	{ .xadj =  -2 },	// percent
	{ .xadj =   0 },	// ampersand
	{ .xadj = -14 },	// quotesingle
	{ .xadj = -13 },	// parenleft
	{ .xadj = -13 },	// parenright
	{ .xadj =  -8 },	// asterisk
	{ .xadj =  -7 },	// plus
	{ .xadj = -15 },	// comma
	{ .xadj = -13 },	// hyphen
	{ .xadj = -15 },	// period
	{ .xadj = -14 },	// slash
	{ .xadj =  -9 },	// zero
	{ .xadj =  -9 },	// one
	{ .xadj =  -9 },	// two
	{ .xadj =  -9 },	// three
	{ .xadj =  -9 },	// four
	{ .xadj =  -9 },	// five
	{ .xadj =  -9 },	// six
	{ .xadj =  -9 },	// seven
	{ .xadj =  -9 },	// eight
	{ .xadj =  -9 },	// nine
	{ .xadj = -13 },	// colon
	{ .xadj = -13 },	// semicolon
	{ .xadj =  -7 },	// less
	{ .xadj =  -7 },	// equal
	{ .xadj =  -7 },	// greater
	{ .xadj =  -9 },	// question
    },
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7c, 0x80, 0x1, 0x0, 0xfe, 0xcf, 0x3, 0x0, 0xfe, 0xcf, 0x3, 0x0, 0x7c, 0x80, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0xfe, 0x1, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0xfe, 0x1, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x18, 0x0, 0x0, 0x60, 0x18, 0x0, 0x0, 0x60, 0xf8, 0x3, 0x0, 0xe0, 0xff, 0x3, 0x0, 0xfe, 0x1f, 0x0, 0x0, 0x7e, 0x18, 0x0, 0x0, 0x60, 0xf8, 0x3, 0x0, 0xe0, 0xff, 0x3, 0x0, 0xfe, 0x1f, 0x0, 0x0, 0x7e, 0x18, 0x0, 0x0, 0x60, 0x18, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x0, 0x0, 0xf0, 0xe0, 0x1, 0x0, 0xf8, 0xc1, 0x1, 0x0, 0xec, 0x3, 0x3, 0x0, 0xc4, 0x7, 0x2, 0x0, 0xff, 0xff, 0xf, 0x0, 0x84, 0xf, 0x2, 0x0, 0xc, 0x1f, 0x3, 0x0, 0x3c, 0xfe, 0x1, 0x0, 0x78, 0xfc, 0x1, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf8, 0x1, 0x0, 0x0, 0xfc, 0x1, 0x0, 0x0, 0x8e, 0x1, 0x0, 0x0, 0x6, 0x1, 0x3, 0x0, 0x82, 0xc0, 0x3, 0x0, 0x66, 0xf0, 0x0, 0x0, 0x1c, 0x3c, 0x0, 0x0, 0x4, 0xf, 0x0, 0x0, 0xc4, 0xe3, 0x1, 0x0, 0xf4, 0xf0, 0x3, 0x0, 0x3c, 0xf8, 0x3, 0x0, 0xe, 0x1c, 0x3, 0x0, 0x6, 0xc, 0x2, 0x0, 0x0, 0x4, 0x1, 0x0, 0x0, 0xcc, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 37	percent
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0xfc, 0x1, 0x0, 0x0, 0xfe, 0x3, 0x0, 0x0, 0xc7, 0x3, 0x0, 0xf8, 0x81, 0x3, 0x0, 0xfc, 0x1, 0x3, 0x0, 0xfe, 0x3, 0x3, 0x0, 0xc6, 0x8f, 0x3, 0x0, 0xc2, 0x9f, 0x1, 0x0, 0x66, 0xfe, 0x0, 0x0, 0x7e, 0xfc, 0x0, 0x0, 0x3c, 0xf8, 0x1, 0x0, 0x80, 0xf8, 0x3, 0x0, 0x80, 0xcd, 0x3, 0x0, 0x80, 0x87, 0x3, 0x0, 0x80, 0x81, 0x1, 0x0, 0x80, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0xfe, 0x1, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0x0, 0x0, 0xe0, 0xff, 0x3, 0x0, 0xf8, 0xff, 0xf, 0x0, 0x3c, 0x0, 0x1e, 0x0, 0x6, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x30, 0x0, 0x1c, 0x0, 0x1c, 0x0, 0xf8, 0xff, 0xf, 0x0, 0xe0, 0xff, 0x3, 0x0, 0x0, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0x0, 0x0, 0x10, 0x1, 0x0, 0x0, 0xb8, 0x3, 0x0, 0x0, 0xb0, 0x1, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0xfe, 0xf, 0x0, 0x0, 0xfe, 0xf, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0xb0, 0x1, 0x0, 0x0, 0xb8, 0x3, 0x0, 0x0, 0x10, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0xc0, 0xff, 0x3, 0x0, 0xc0, 0xff, 0x3, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x61, 0x0, 0x0, 0xc0, 0x3b, 0x0, 0x0, 0xc0, 0x1f, 0x0, 0x0, 0x80, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x1, 0x0, 0x0, 0xc0, 0x3, 0x0, 0x0, 0xc0, 0x3, 0x0, 0x0, 0x80, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0x3, 0x0, 0x0, 0xe0, 0x3, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x80, 0xf, 0x0, 0x0, 0xf0, 0x1, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0xc0, 0xf, 0x0, 0x0, 0xf0, 0x7f, 0x0, 0x0, 0xfc, 0xff, 0x1, 0x0, 0xfc, 0xff, 0x1, 0x0, 0x6, 0x0, 0x3, 0x0, 0x2, 0x0, 0x2, 0x0, 0x6, 0x0, 0x3, 0x0, 0xfc, 0xff, 0x1, 0x0, 0xfc, 0xff, 0x1, 0x0, 0xf0, 0x7f, 0x0, 0x0, 0xc0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x2, 0x0, 0x8, 0x0, 0x2, 0x0, 0xc, 0x0, 0x3, 0x0, 0xfc, 0xff, 0x3, 0x0, 0xfe, 0xff, 0x3, 0x0, 0xfe, 0xff, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x3, 0x0, 0x18, 0x80, 0x3, 0x0, 0xc, 0xc0, 0x3, 0x0, 0xe, 0xe0, 0x3, 0x0, 0xe, 0xb8, 0x3, 0x0, 0x1e, 0x9e, 0x3, 0x0, 0xfe, 0x87, 0x3, 0x0, 0xfc, 0x83, 0x3, 0x0, 0xf8, 0x80, 0x3, 0x0, 0x0, 0xe0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x10, 0x80, 0x1, 0x0, 0x18, 0xc0, 0x3, 0x0, 0xc, 0xc0, 0x3, 0x0, 0x4, 0x83, 0x3, 0x0, 0x6, 0x3, 0x3, 0x0, 0x6, 0x3, 0x2, 0x0, 0x8e, 0x7, 0x3, 0x0, 0xfe, 0x8f, 0x1, 0x0, 0xfc, 0xfe, 0x1, 0x0, 0x38, 0xfe, 0x0, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x3c, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x80, 0x33, 0x0, 0x0, 0xc0, 0x31, 0x0, 0x0, 0x60, 0x30, 0x0, 0x0, 0x38, 0x30, 0x0, 0x0, 0xfc, 0xff, 0x3, 0x0, 0xfe, 0xff, 0x3, 0x0, 0xfe, 0xff, 0x3, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x80, 0x1, 0x0, 0xc0, 0xc3, 0x3, 0x0, 0xf8, 0xc3, 0x3, 0x0, 0x9e, 0x83, 0x3, 0x0, 0x8e, 0x3, 0x3, 0x0, 0x8e, 0x7, 0x2, 0x0, 0x8e, 0x7, 0x3, 0x0, 0x8e, 0x8f, 0x1, 0x0, 0xe, 0xff, 0x1, 0x0, 0xe, 0x7e, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0xc0, 0xff, 0x0, 0x0, 0xf0, 0xff, 0x1, 0x0, 0xf8, 0xff, 0x3, 0x0, 0x78, 0x2, 0x3, 0x0, 0x1c, 0x1, 0x2, 0x0, 0xc, 0x3, 0x3, 0x0, 0x6, 0xff, 0x1, 0x0, 0x6, 0xfe, 0x1, 0x0, 0x2, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x30, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0xe, 0x0, 0x3, 0x0, 0xe, 0xe0, 0x3, 0x0, 0xe, 0xfc, 0x3, 0x0, 0x8e, 0x7f, 0x0, 0x0, 0xee, 0x7, 0x0, 0x0, 0xfe, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf8, 0xfc, 0x1, 0x0, 0xfc, 0xfd, 0x1, 0x0, 0xfe, 0x7, 0x3, 0x0, 0xc6, 0x3, 0x2, 0x0, 0x82, 0x7, 0x2, 0x0, 0x86, 0xf, 0x2, 0x0, 0xfe, 0x1f, 0x3, 0x0, 0x7c, 0xfe, 0x1, 0x0, 0x38, 0xfc, 0x1, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0xe0, 0x1, 0x0, 0x0, 0xf8, 0x3, 0x2, 0x0, 0xfc, 0x7, 0x2, 0x0, 0xfc, 0xf, 0x3, 0x0, 0x6, 0xc, 0x3, 0x0, 0x2, 0x88, 0x1, 0x0, 0x6, 0xe8, 0x1, 0x0, 0x1c, 0xfc, 0x0, 0x0, 0xfc, 0x7f, 0x0, 0x0, 0xf8, 0x3f, 0x0, 0x0, 0xe0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x81, 0x1, 0x0, 0xc0, 0xc3, 0x3, 0x0, 0xc0, 0xc3, 0x3, 0x0, 0x80, 0x81, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x81, 0x61, 0x0, 0xc0, 0xc3, 0x3b, 0x0, 0xc0, 0xc3, 0x1f, 0x0, 0x80, 0x81, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0xe7, 0x0, 0x0, 0x0, 0xc3, 0x0, 0x0, 0x80, 0xc3, 0x1, 0x0, 0x80, 0x81, 0x1, 0x0, 0xc0, 0x81, 0x3, 0x0, 0xc0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x3, 0x0, 0xc0, 0x81, 0x3, 0x0, 0x80, 0x81, 0x1, 0x0, 0x80, 0xc3, 0x1, 0x0, 0x0, 0xc3, 0x0, 0x0, 0x0, 0xe7, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x1e, 0x80, 0x1, 0x0, 0x2, 0xce, 0x3, 0x0, 0x82, 0xcf, 0x3, 0x0, 0xc6, 0x83, 0x1, 0x0, 0xfe, 0x1, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
