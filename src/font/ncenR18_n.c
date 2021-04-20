
// file: font/ncenR18.bdf
// font: -Adobe-New Century Schoolbook-Medium-R-Normal--18-180-75-75-P-103-ISO10646-1

#include <font.h>

const struct Font font_ncenR18_n = {
    .type       = 1,
    .name	= "ncenR18_n",
    .height	= 18,
    .width	= 16,
    .bytescol	= 4,
    .numcol     = 16,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj = -11 },	// exclam
	{ .xadj =  -9 },	// quotedbl
	{ .xadj =  -5 },	// numbersign
	{ .xadj =  -6 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =  -2 },	// ampersand
	{ .xadj = -12 },	// quotesingle
	{ .xadj =  -9 },	// parenleft
	{ .xadj =  -9 },	// parenright
	{ .xadj =  -6 },	// asterisk
	{ .xadj =  -6 },	// plus
	{ .xadj = -12 },	// comma
	{ .xadj = -10 },	// hyphen
	{ .xadj = -12 },	// period
	{ .xadj = -10 },	// slash
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
	{ .xadj = -12 },	// colon
	{ .xadj = -12 },	// semicolon
	{ .xadj =  -6 },	// less
	{ .xadj =  -6 },	// equal
	{ .xadj =  -6 },	// greater
	{ .xadj =  -8 },	// question
    },
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x60, 0x0, 0x0, 0xfe, 0x67, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x4, 0x0, 0x0, 0x40, 0x4, 0x0, 0x0, 0x40, 0x7c, 0x0, 0x0, 0xc0, 0x7, 0x0, 0x0, 0x78, 0x4, 0x0, 0x0, 0x40, 0x7c, 0x0, 0x0, 0xc0, 0x7, 0x0, 0x0, 0x78, 0x4, 0x0, 0x0, 0x40, 0x4, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x70, 0x30, 0x0, 0x0, 0xf8, 0x70, 0x0, 0x0, 0xcc, 0x40, 0x0, 0x0, 0x84, 0x41, 0x0, 0x0, 0xff, 0xff, 0x1, 0x0, 0x4, 0x43, 0x0, 0x0, 0x4, 0x67, 0x0, 0x0, 0x1c, 0x3e, 0x0, 0x0, 0x18, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0xe0, 0x0, 0x0, 0x0, 0xf8, 0x1, 0x0, 0x0, 0x1c, 0x1, 0x0, 0x0, 0x6, 0x1, 0x0, 0x0, 0x82, 0x60, 0x0, 0x0, 0x62, 0x18, 0x0, 0x0, 0x1c, 0x6, 0x0, 0x0, 0x88, 0x1, 0x0, 0x0, 0x68, 0x38, 0x0, 0x0, 0x18, 0x7e, 0x0, 0x0, 0x6, 0x47, 0x0, 0x0, 0x80, 0x41, 0x0, 0x0, 0x80, 0x20, 0x0, 0x0, 0x80, 0x18, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 37	percent
	0x0, 0x3c, 0x0, 0x0, 0x0, 0x7f, 0x0, 0x0, 0xbc, 0x61, 0x0, 0x0, 0xe6, 0x41, 0x0, 0x0, 0xc2, 0x43, 0x0, 0x0, 0x62, 0x47, 0x0, 0x0, 0x36, 0x2e, 0x0, 0x0, 0x9c, 0x3c, 0x0, 0x0, 0x80, 0x3c, 0x0, 0x0, 0x80, 0x73, 0x0, 0x0, 0x80, 0x61, 0x0, 0x0, 0x80, 0x20, 0x0, 0x0, 0x80, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0xc0, 0x1f, 0x0, 0x0, 0xf0, 0x7f, 0x0, 0x0, 0x38, 0xe0, 0x0, 0x0, 0xc, 0x80, 0x1, 0x0, 0x4, 0x0, 0x1, 0x0, 0x2, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x2, 0x0, 0x2, 0x0, 0x4, 0x0, 0x1, 0x0, 0xc, 0x80, 0x1, 0x0, 0x38, 0xe0, 0x0, 0x0, 0xf0, 0x7f, 0x0, 0x0, 0xc0, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0x0, 0x0, 0x6c, 0x0, 0x0, 0x0, 0x28, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0xfe, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x28, 0x0, 0x0, 0x0, 0x6c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0xc0, 0x7f, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x2, 0x0, 0x0, 0x60, 0x1, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x70, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0xc0, 0x3, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0xf0, 0xf, 0x0, 0x0, 0xfc, 0x3f, 0x0, 0x0, 0xc, 0x30, 0x0, 0x0, 0x2, 0x40, 0x0, 0x0, 0x2, 0x40, 0x0, 0x0, 0x2, 0x40, 0x0, 0x0, 0xc, 0x30, 0x0, 0x0, 0xfc, 0x3f, 0x0, 0x0, 0xf0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x4, 0x40, 0x0, 0x0, 0x4, 0x40, 0x0, 0x0, 0x4, 0x40, 0x0, 0x0, 0xfe, 0x7f, 0x0, 0x0, 0xfe, 0x7f, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x18, 0x60, 0x0, 0x0, 0x1c, 0x70, 0x0, 0x0, 0x4, 0x78, 0x0, 0x0, 0x2, 0x6c, 0x0, 0x0, 0x2, 0x66, 0x0, 0x0, 0x2, 0x63, 0x0, 0x0, 0x86, 0x61, 0x0, 0x0, 0xfc, 0x60, 0x0, 0x0, 0x78, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x30, 0x0, 0x0, 0xc, 0x70, 0x0, 0x0, 0xe, 0x40, 0x0, 0x0, 0x82, 0x40, 0x0, 0x0, 0x82, 0x40, 0x0, 0x0, 0x82, 0x40, 0x0, 0x0, 0xc6, 0x61, 0x0, 0x0, 0x7c, 0x3f, 0x0, 0x0, 0x38, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x8, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x80, 0x9, 0x0, 0x0, 0x60, 0x8, 0x0, 0x0, 0x18, 0x48, 0x0, 0x0, 0x4, 0x48, 0x0, 0x0, 0xfe, 0x7f, 0x0, 0x0, 0xfe, 0x7f, 0x0, 0x0, 0x0, 0x48, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x30, 0x0, 0x0, 0xfe, 0x71, 0x0, 0x0, 0x86, 0x40, 0x0, 0x0, 0x46, 0x40, 0x0, 0x0, 0x46, 0x40, 0x0, 0x0, 0x46, 0x40, 0x0, 0x0, 0xc6, 0x60, 0x0, 0x0, 0x86, 0x3f, 0x0, 0x0, 0x2, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0xe0, 0x1f, 0x0, 0x0, 0xf8, 0x3f, 0x0, 0x0, 0x1c, 0x61, 0x0, 0x0, 0x84, 0x40, 0x0, 0x0, 0xc2, 0x40, 0x0, 0x0, 0xc2, 0x40, 0x0, 0x0, 0xc2, 0x61, 0x0, 0x0, 0x8e, 0x3f, 0x0, 0x0, 0xc, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x1e, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x7c, 0x0, 0x0, 0x6, 0x7f, 0x0, 0x0, 0xc6, 0x3, 0x0, 0x0, 0xf6, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x1c, 0x0, 0x0, 0x7c, 0x3e, 0x0, 0x0, 0xe6, 0x61, 0x0, 0x0, 0xc2, 0x40, 0x0, 0x0, 0x82, 0x41, 0x0, 0x0, 0x82, 0x41, 0x0, 0x0, 0xc6, 0x63, 0x0, 0x0, 0x3c, 0x3f, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0xf8, 0x30, 0x0, 0x0, 0xfc, 0x71, 0x0, 0x0, 0x86, 0x43, 0x0, 0x0, 0x2, 0x43, 0x0, 0x0, 0x2, 0x43, 0x0, 0x0, 0x2, 0x21, 0x0, 0x0, 0x86, 0x38, 0x0, 0x0, 0xfc, 0x1f, 0x0, 0x0, 0xf8, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x60, 0x0, 0x0, 0xc0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x2, 0x0, 0xc0, 0x60, 0x1, 0x0, 0xc0, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0xa, 0x0, 0x0, 0x0, 0x1b, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x80, 0x31, 0x0, 0x0, 0x80, 0x20, 0x0, 0x0, 0xc0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0xc0, 0x60, 0x0, 0x0, 0x80, 0x20, 0x0, 0x0, 0x80, 0x31, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x1b, 0x0, 0x0, 0x0, 0xa, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0xc, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x2, 0x60, 0x0, 0x0, 0x2, 0x66, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
