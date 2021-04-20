
// file: font/luRS19.bdf
// font: -B&H-Lucida-Medium-R-Normal-Sans-19-190-75-75-P-108-ISO10646-1

#include <font.h>

const struct Font font_luRS19_n = {
    .type       = 1,
    .name	= "luRS19_n",
    .height	= 19,
    .width	= 14,
    .bytescol	= 4,
    .numcol     = 14,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -8 },	// exclam
	{ .xadj =  -7 },	// quotedbl
	{ .xadj =  -2 },	// numbersign
	{ .xadj =  -2 },	// dollar
	{ .xadj =  -1 },	// percent
	{ .xadj =  -1 },	// ampersand
	{ .xadj = -10 },	// quotesingle
	{ .xadj =  -8 },	// parenleft
	{ .xadj =  -8 },	// parenright
	{ .xadj =  -5 },	// asterisk
	{ .xadj =  -2 },	// plus
	{ .xadj =  -8 },	// comma
	{ .xadj =  -8 },	// hyphen
	{ .xadj =  -8 },	// period
	{ .xadj =  -5 },	// slash
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
	{ .xadj =  -8 },	// colon
	{ .xadj =  -8 },	// semicolon
	{ .xadj =  -2 },	// less
	{ .xadj =  -2 },	// equal
	{ .xadj =  -2 },	// greater
	{ .xadj =  -6 },	// question
    },
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfe, 0x67, 0x0, 0x0, 0xfe, 0x67, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0xc, 0x0, 0x0, 0x60, 0x4c, 0x0, 0x0, 0x60, 0x7c, 0x0, 0x0, 0xe0, 0x7f, 0x0, 0x0, 0xfc, 0xf, 0x0, 0x0, 0x7e, 0x4c, 0x0, 0x0, 0x66, 0x7c, 0x0, 0x0, 0xe0, 0x3f, 0x0, 0x0, 0xfe, 0xf, 0x0, 0x0, 0x7e, 0xc, 0x0, 0x0, 0x62, 0xc, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0x20, 0x0, 0x0, 0x7e, 0x60, 0x0, 0x0, 0xc6, 0x60, 0x0, 0x0, 0xff, 0xff, 0x1, 0x0, 0xff, 0xff, 0x1, 0x0, 0x6, 0xe3, 0x0, 0x0, 0x2, 0x7e, 0x0, 0x0, 0x6, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x3c, 0x40, 0x0, 0x0, 0x7e, 0x60, 0x0, 0x0, 0x66, 0x78, 0x0, 0x0, 0x66, 0x1c, 0x0, 0x0, 0x7e, 0xe, 0x0, 0x0, 0x3c, 0x7, 0x0, 0x0, 0xc0, 0x3, 0x0, 0x0, 0xe0, 0x1e, 0x0, 0x0, 0xf0, 0x7f, 0x0, 0x0, 0xb8, 0x61, 0x0, 0x0, 0x9e, 0x61, 0x0, 0x0, 0x86, 0x7f, 0x0, 0x0, 0x2, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 37	percent
	0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x0, 0x0, 0x80, 0x3f, 0x0, 0x0, 0xfc, 0x71, 0x0, 0x0, 0xfe, 0x60, 0x0, 0x0, 0xc6, 0x63, 0x0, 0x0, 0x66, 0x67, 0x0, 0x0, 0x7e, 0x3e, 0x0, 0x0, 0x3c, 0x3c, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x4f, 0x0, 0x0, 0x0, 0x47, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0x0, 0x0, 0x80, 0x1f, 0x0, 0x0, 0xe0, 0xff, 0x0, 0x0, 0x38, 0xc0, 0x1, 0x0, 0xc, 0x0, 0x3, 0x0, 0x6, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x6, 0x0, 0x6, 0x0, 0xc, 0x0, 0x3, 0x0, 0x38, 0xc0, 0x1, 0x0, 0xe0, 0xff, 0x0, 0x0, 0x80, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x98, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x98, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0xf8, 0x7f, 0x0, 0x0, 0xf8, 0x7f, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x4, 0x0, 0x0, 0xf0, 0x7, 0x0, 0x0, 0xf0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0x6, 0x0, 0x0, 0x80, 0x7, 0x0, 0x0, 0xf0, 0x1, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x80, 0x1f, 0x0, 0x0, 0xe0, 0x3, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0x0, 0x0, 0xe0, 0x7, 0x0, 0x0, 0xf8, 0x1f, 0x0, 0x0, 0x1c, 0x38, 0x0, 0x0, 0xe, 0x70, 0x0, 0x0, 0x6, 0x60, 0x0, 0x0, 0x6, 0x60, 0x0, 0x0, 0xe, 0x70, 0x0, 0x0, 0x1c, 0x38, 0x0, 0x0, 0xf8, 0x1f, 0x0, 0x0, 0xe0, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0xfe, 0x7f, 0x0, 0x0, 0xfe, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x70, 0x0, 0x0, 0x6, 0x78, 0x0, 0x0, 0x6, 0x6e, 0x0, 0x0, 0x6, 0x66, 0x0, 0x0, 0x6, 0x63, 0x0, 0x0, 0x8e, 0x61, 0x0, 0x0, 0xfc, 0x61, 0x0, 0x0, 0x78, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x70, 0x0, 0x0, 0x86, 0x61, 0x0, 0x0, 0x86, 0x61, 0x0, 0x0, 0x86, 0x61, 0x0, 0x0, 0x86, 0x61, 0x0, 0x0, 0x4e, 0x73, 0x0, 0x0, 0x7c, 0x3f, 0x0, 0x0, 0x38, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x80, 0x7, 0x0, 0x0, 0xe0, 0x7, 0x0, 0x0, 0x70, 0x6, 0x0, 0x0, 0x38, 0x6, 0x0, 0x0, 0x1e, 0x6, 0x0, 0x0, 0xfe, 0x7f, 0x0, 0x0, 0xfe, 0x7f, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfe, 0x70, 0x0, 0x0, 0xfe, 0x60, 0x0, 0x0, 0xc6, 0x60, 0x0, 0x0, 0xc6, 0x60, 0x0, 0x0, 0xc6, 0x71, 0x0, 0x0, 0x86, 0x3f, 0x0, 0x0, 0x6, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x0, 0x0, 0xe0, 0x7, 0x0, 0x0, 0xf8, 0x1f, 0x0, 0x0, 0x9c, 0x31, 0x0, 0x0, 0xce, 0x60, 0x0, 0x0, 0xc6, 0x60, 0x0, 0x0, 0xc6, 0x60, 0x0, 0x0, 0xc6, 0x71, 0x0, 0x0, 0x8e, 0x3f, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x70, 0x0, 0x0, 0x6, 0x7c, 0x0, 0x0, 0x6, 0x1f, 0x0, 0x0, 0x86, 0x7, 0x0, 0x0, 0xe6, 0x1, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x38, 0x3f, 0x0, 0x0, 0xfc, 0x73, 0x0, 0x0, 0xce, 0x61, 0x0, 0x0, 0x86, 0x61, 0x0, 0x0, 0x86, 0x61, 0x0, 0x0, 0x4e, 0x73, 0x0, 0x0, 0x3c, 0x3f, 0x0, 0x0, 0x3c, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0xfc, 0x71, 0x0, 0x0, 0x8e, 0x63, 0x0, 0x0, 0x6, 0x63, 0x0, 0x0, 0x6, 0x63, 0x0, 0x0, 0x6, 0x73, 0x0, 0x0, 0x8c, 0x38, 0x0, 0x0, 0xfc, 0x1f, 0x0, 0x0, 0xf0, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x60, 0x0, 0x0, 0x60, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0xe0, 0x7, 0x0, 0x60, 0xe0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x80, 0x7, 0x0, 0x0, 0x80, 0x7, 0x0, 0x0, 0xc0, 0xf, 0x0, 0x0, 0xc0, 0xc, 0x0, 0x0, 0x60, 0x18, 0x0, 0x0, 0x60, 0x18, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x18, 0x60, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x0, 0x0, 0x80, 0xd, 0x0, 0x0, 0x80, 0xd, 0x0, 0x0, 0x80, 0xd, 0x0, 0x0, 0x80, 0xd, 0x0, 0x0, 0x80, 0xd, 0x0, 0x0, 0x80, 0xd, 0x0, 0x0, 0x80, 0xd, 0x0, 0x0, 0x80, 0xd, 0x0, 0x0, 0x80, 0xd, 0x0, 0x0, 0x80, 0xd, 0x0, 0x0, 0x80, 0xd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x0, 0x0, 0x18, 0x60, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x60, 0x18, 0x0, 0x0, 0x60, 0x18, 0x0, 0x0, 0xc0, 0xc, 0x0, 0x0, 0xc0, 0xf, 0x0, 0x0, 0x80, 0x7, 0x0, 0x0, 0x80, 0x7, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0xc, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x6f, 0x0, 0x0, 0x86, 0x6f, 0x0, 0x0, 0xce, 0x1, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
