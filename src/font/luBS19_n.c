
// file: font/luBS19.bdf
// font: -B&H-Lucida-Bold-R-Normal-Sans-19-190-75-75-P-122-ISO10646-1

#include <font.h>

const struct Font font_luBS19_n = {
    .type       = 1,
    .name	= "luBS19_n",
    .height	= 21,
    .width	= 17,
    .bytescol	= 4,
    .numcol     = 17,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj = -10 },	// exclam
	{ .xadj =  -7 },	// quotedbl
	{ .xadj =  -4 },	// numbersign
	{ .xadj =  -4 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =  -2 },	// ampersand
	{ .xadj = -12 },	// quotesingle
	{ .xadj = -10 },	// parenleft
	{ .xadj = -10 },	// parenright
	{ .xadj =  -8 },	// asterisk
	{ .xadj =  -4 },	// plus
	{ .xadj = -10 },	// comma
	{ .xadj = -12 },	// hyphen
	{ .xadj = -10 },	// period
	{ .xadj =  -6 },	// slash
	{ .xadj =  -4 },	// zero
	{ .xadj =  -4 },	// one
	{ .xadj =  -4 },	// two
	{ .xadj =  -4 },	// three
	{ .xadj =  -4 },	// four
	{ .xadj =  -4 },	// five
	{ .xadj =  -4 },	// six
	{ .xadj =  -4 },	// seven
	{ .xadj =  -4 },	// eight
	{ .xadj =  -4 },	// nine
	{ .xadj = -10 },	// colon
	{ .xadj = -10 },	// semicolon
	{ .xadj =  -4 },	// less
	{ .xadj =  -4 },	// equal
	{ .xadj =  -4 },	// greater
	{ .xadj =  -6 },	// question
    },
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0x81, 0x1, 0x0, 0xf8, 0x9f, 0x1, 0x0, 0xf8, 0x9f, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x80, 0x31, 0x1, 0x0, 0x80, 0xf1, 0x1, 0x0, 0x80, 0xff, 0x0, 0x0, 0xf0, 0x3f, 0x0, 0x0, 0xf8, 0x31, 0x1, 0x0, 0x88, 0xf1, 0x1, 0x0, 0x80, 0xff, 0x1, 0x0, 0xf0, 0x3f, 0x0, 0x0, 0xf8, 0x31, 0x0, 0x0, 0x88, 0x31, 0x0, 0x0, 0x80, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0xc0, 0x1, 0x0, 0xf0, 0xc1, 0x1, 0x0, 0xf8, 0x83, 0x1, 0x0, 0xf8, 0x87, 0x1, 0x0, 0x9f, 0xff, 0xf, 0x0, 0xff, 0x8f, 0xf, 0x0, 0x18, 0xde, 0x1, 0x0, 0x18, 0xfe, 0x1, 0x0, 0x38, 0xfc, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x0, 0x0, 0x0, 0x0, 0xe0, 0x1, 0x0, 0x0, 0xf8, 0x7, 0x1, 0x0, 0x18, 0x6, 0x1, 0x0, 0x18, 0xc6, 0x1, 0x0, 0xf8, 0xe7, 0x0, 0x0, 0xe0, 0x71, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0xc0, 0x3, 0x0, 0x0, 0xe0, 0xf0, 0x0, 0x0, 0x70, 0xf8, 0x1, 0x0, 0x38, 0x98, 0x1, 0x0, 0x8, 0x98, 0x1, 0x0, 0x8, 0xf8, 0x1, 0x0, 0x0, 0xf0, 0x0, 0x0, 	// 37	percent
	0x0, 0x0, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x70, 0xfe, 0x0, 0x0, 0xf0, 0xc7, 0x1, 0x0, 0xf8, 0x83, 0x1, 0x0, 0x98, 0x8f, 0x1, 0x0, 0x18, 0x9f, 0x1, 0x0, 0x98, 0xbf, 0x1, 0x0, 0x98, 0xf9, 0x0, 0x0, 0xf0, 0xf0, 0x1, 0x0, 0xe0, 0xf0, 0x1, 0x0, 0x0, 0xbc, 0x1, 0x0, 0x0, 0x1e, 0x1, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0xf8, 0x1, 0x0, 0x0, 0xf8, 0x1, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0x0, 0x0, 0x0, 0x7e, 0x0, 0x0, 0xc0, 0xff, 0x3, 0x0, 0xe0, 0xff, 0x7, 0x0, 0xf0, 0x0, 0xf, 0x0, 0x38, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x1c, 0x0, 0xf0, 0x0, 0xf, 0x0, 0xe0, 0xff, 0x7, 0x0, 0xc0, 0xff, 0x3, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0xb0, 0x0, 0x0, 0x0, 0xe8, 0x1, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0xe8, 0x1, 0x0, 0x0, 0xb0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0xe0, 0xff, 0x1, 0x0, 0xe0, 0xff, 0x1, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x0, 0x0, 0x0, 0xe0, 0x11, 0x0, 0x0, 0xe0, 0x1f, 0x0, 0x0, 0xe0, 0xf, 0x0, 0x0, 0xe0, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x1, 0x0, 0x0, 0xc0, 0x1, 0x0, 0x0, 0xc0, 0x1, 0x0, 0x0, 0xc0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x1f, 0x0, 0x0, 0xc0, 0x7, 0x0, 0x0, 0xf0, 0x1, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x80, 0xf, 0x0, 0x0, 0xe0, 0x3, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0x0, 0x0, 0x80, 0x1f, 0x0, 0x0, 0xe0, 0x7f, 0x0, 0x0, 0xf0, 0xff, 0x0, 0x0, 0x30, 0xc0, 0x0, 0x0, 0x18, 0x80, 0x1, 0x0, 0x18, 0x80, 0x1, 0x0, 0x18, 0x80, 0x1, 0x0, 0x18, 0x80, 0x1, 0x0, 0x30, 0xc0, 0x0, 0x0, 0xf0, 0xff, 0x0, 0x0, 0xe0, 0x7f, 0x0, 0x0, 0x80, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0xf8, 0xff, 0x1, 0x0, 0xf8, 0xff, 0x1, 0x0, 0xf8, 0xff, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0x0, 0x0, 0x30, 0xc0, 0x1, 0x0, 0x38, 0xe0, 0x1, 0x0, 0x18, 0xf0, 0x1, 0x0, 0x18, 0xf0, 0x1, 0x0, 0x18, 0xb8, 0x1, 0x0, 0x18, 0x9c, 0x1, 0x0, 0x38, 0x8e, 0x1, 0x0, 0xf8, 0x87, 0x1, 0x0, 0xf0, 0x83, 0x1, 0x0, 0xe0, 0x81, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0xc0, 0x1, 0x0, 0x18, 0x86, 0x1, 0x0, 0x18, 0x86, 0x1, 0x0, 0x18, 0x86, 0x1, 0x0, 0x18, 0x86, 0x1, 0x0, 0x18, 0x86, 0x1, 0x0, 0x38, 0xcf, 0x1, 0x0, 0xf8, 0xfd, 0x1, 0x0, 0xf0, 0xf9, 0x0, 0x0, 0xe0, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x1f, 0x0, 0x0, 0x80, 0x1b, 0x0, 0x0, 0xc0, 0x19, 0x0, 0x0, 0xe0, 0x18, 0x0, 0x0, 0x38, 0x18, 0x0, 0x0, 0xf8, 0xff, 0x1, 0x0, 0xf8, 0xff, 0x1, 0x0, 0xf8, 0xff, 0x1, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0xc3, 0x1, 0x0, 0xf8, 0x83, 0x1, 0x0, 0x18, 0x83, 0x1, 0x0, 0x18, 0x83, 0x1, 0x0, 0x18, 0x87, 0x1, 0x0, 0x18, 0xc7, 0x1, 0x0, 0x18, 0xfe, 0x0, 0x0, 0x18, 0xfe, 0x0, 0x0, 0x18, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x0, 0x0, 0x80, 0x1f, 0x0, 0x0, 0xe0, 0x7f, 0x0, 0x0, 0xf0, 0xff, 0x0, 0x0, 0x70, 0xc6, 0x1, 0x0, 0x38, 0x83, 0x1, 0x0, 0x18, 0x83, 0x1, 0x0, 0x18, 0x83, 0x1, 0x0, 0x18, 0xc7, 0x1, 0x0, 0x18, 0xff, 0x0, 0x0, 0x38, 0xfe, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x1, 0x0, 0x18, 0xc0, 0x1, 0x0, 0x18, 0xf0, 0x1, 0x0, 0x18, 0xfc, 0x1, 0x0, 0x18, 0x7e, 0x0, 0x0, 0x18, 0xf, 0x0, 0x0, 0xd8, 0x3, 0x0, 0x0, 0xf8, 0x1, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0xe0, 0xfc, 0x0, 0x0, 0xf0, 0xfd, 0x1, 0x0, 0xf8, 0xc7, 0x1, 0x0, 0x98, 0x87, 0x1, 0x0, 0x18, 0x87, 0x1, 0x0, 0x18, 0x8f, 0x1, 0x0, 0xf8, 0xcf, 0x1, 0x0, 0xf0, 0xff, 0x0, 0x0, 0xe0, 0xfc, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x3, 0x0, 0x0, 0xf0, 0xc7, 0x1, 0x0, 0xf0, 0x8f, 0x1, 0x0, 0x38, 0x8e, 0x1, 0x0, 0x18, 0x8c, 0x1, 0x0, 0x18, 0x8c, 0x1, 0x0, 0x18, 0xcc, 0x1, 0x0, 0x38, 0xe6, 0x0, 0x0, 0xf0, 0xff, 0x0, 0x0, 0xe0, 0x7f, 0x0, 0x0, 0x80, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0xc3, 0x1, 0x0, 0x80, 0xc3, 0x1, 0x0, 0x80, 0xc3, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0xe3, 0x11, 0x0, 0x80, 0xe3, 0x1f, 0x0, 0x80, 0xe3, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x33, 0x0, 0x0, 0x0, 0x33, 0x0, 0x0, 0x80, 0x61, 0x0, 0x0, 0xc0, 0xe1, 0x0, 0x0, 0xc0, 0xc0, 0x0, 0x0, 0xe0, 0xc0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x0, 0x0, 0xe0, 0xc0, 0x1, 0x0, 0xc0, 0xc0, 0x0, 0x0, 0xc0, 0xe1, 0x0, 0x0, 0x80, 0x61, 0x0, 0x0, 0x0, 0x33, 0x0, 0x0, 0x0, 0x33, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x18, 0x98, 0x1, 0x0, 0x18, 0x9c, 0x1, 0x0, 0x18, 0x9e, 0x1, 0x0, 0x38, 0x7, 0x0, 0x0, 0xf8, 0x1, 0x0, 0x0, 0xf0, 0x1, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
