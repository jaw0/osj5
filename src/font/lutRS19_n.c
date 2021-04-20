
// file: font/lutRS19.bdf
// font: -B&H-LucidaTypewriter-Medium-R-Normal-Sans-19-190-75-75-M-110-ISO10646-1

#include <font.h>

const struct Font font_lutRS19_n = {
    .type       = 1,
    .name	= "lutRS19_n",
    .height	= 19,
    .width	= 11,
    .bytescol	= 4,
    .numcol     = 11,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =   0 },	// exclam
	{ .xadj =   0 },	// quotedbl
	{ .xadj =   0 },	// numbersign
	{ .xadj =   0 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =   0 },	// ampersand
	{ .xadj =   0 },	// quotesingle
	{ .xadj =   0 },	// parenleft
	{ .xadj =   0 },	// parenright
	{ .xadj =   0 },	// asterisk
	{ .xadj =   0 },	// plus
	{ .xadj =   0 },	// comma
	{ .xadj =   0 },	// hyphen
	{ .xadj =   0 },	// period
	{ .xadj =   0 },	// slash
	{ .xadj =   0 },	// zero
	{ .xadj =   0 },	// one
	{ .xadj =   0 },	// two
	{ .xadj =   0 },	// three
	{ .xadj =   0 },	// four
	{ .xadj =   0 },	// five
	{ .xadj =   0 },	// six
	{ .xadj =   0 },	// seven
	{ .xadj =   0 },	// eight
	{ .xadj =   0 },	// nine
	{ .xadj =   0 },	// colon
	{ .xadj =   0 },	// semicolon
	{ .xadj =   0 },	// less
	{ .xadj =   0 },	// equal
	{ .xadj =   0 },	// greater
	{ .xadj =   0 },	// question
    },
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfe, 0x67, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x2, 0x0, 0x0, 0x20, 0x42, 0x0, 0x0, 0x20, 0x3e, 0x0, 0x0, 0xe0, 0x3, 0x0, 0x0, 0x3c, 0x2, 0x0, 0x0, 0x26, 0x62, 0x0, 0x0, 0x20, 0x1e, 0x0, 0x0, 0xe0, 0x3, 0x0, 0x0, 0x3e, 0x2, 0x0, 0x0, 0x22, 0x2, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0x60, 0x0, 0x0, 0x7e, 0x60, 0x0, 0x0, 0xc2, 0x40, 0x0, 0x0, 0xff, 0xff, 0x1, 0x0, 0x82, 0x63, 0x0, 0x0, 0x2, 0x7f, 0x0, 0x0, 0x6, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x0, 0x0, 0x0, 0x0, 0x3c, 0x40, 0x0, 0x0, 0x66, 0x60, 0x0, 0x0, 0x42, 0x18, 0x0, 0x0, 0x66, 0x6, 0x0, 0x0, 0x3c, 0x3, 0x0, 0x0, 0xc0, 0x3e, 0x0, 0x0, 0x60, 0x63, 0x0, 0x0, 0x18, 0x41, 0x0, 0x0, 0x6, 0x63, 0x0, 0x0, 0x2, 0x3e, 0x0, 0x0, 	// 37	percent
	0x0, 0x1e, 0x0, 0x0, 0x0, 0x3f, 0x0, 0x0, 0xbc, 0x60, 0x0, 0x0, 0xfe, 0x40, 0x0, 0x0, 0xc2, 0x43, 0x0, 0x0, 0x62, 0x4f, 0x0, 0x0, 0x3e, 0x7e, 0x0, 0x0, 0x1c, 0x38, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x4f, 0x0, 0x0, 0x0, 0x43, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0xf, 0x0, 0x0, 0xf0, 0x3f, 0x0, 0x0, 0x38, 0xe0, 0x0, 0x0, 0xc, 0x80, 0x1, 0x0, 0x6, 0x0, 0x1, 0x0, 0x6, 0x0, 0x3, 0x0, 0x2, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x2, 0x0, 0x6, 0x0, 0x3, 0x0, 0x4, 0x0, 0x1, 0x0, 0xc, 0x80, 0x1, 0x0, 0x38, 0xe0, 0x0, 0x0, 0xf0, 0x7f, 0x0, 0x0, 0xc0, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x98, 0x0, 0x0, 0x0, 0xd0, 0x1, 0x0, 0x0, 0x4e, 0x0, 0x0, 0x0, 0x4e, 0x0, 0x0, 0x0, 0xd0, 0x1, 0x0, 0x0, 0x98, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0xe0, 0x7f, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x4, 0x0, 0x0, 0x70, 0x7, 0x0, 0x0, 0xf0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x80, 0x3, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x80, 0x3, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0x0, 0x0, 0xf0, 0xf, 0x0, 0x0, 0xfc, 0x3f, 0x0, 0x0, 0xc, 0x30, 0x0, 0x0, 0x2, 0x40, 0x0, 0x0, 0x2, 0x40, 0x0, 0x0, 0x2, 0x40, 0x0, 0x0, 0xc, 0x30, 0x0, 0x0, 0xfc, 0x3f, 0x0, 0x0, 0xf0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x8, 0x40, 0x0, 0x0, 0x4, 0x40, 0x0, 0x0, 0x4, 0x40, 0x0, 0x0, 0x4, 0x40, 0x0, 0x0, 0xfc, 0x7f, 0x0, 0x0, 0xfe, 0x7f, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0x0, 0x0, 0x4, 0x60, 0x0, 0x0, 0x2, 0x78, 0x0, 0x0, 0x2, 0x5c, 0x0, 0x0, 0x2, 0x46, 0x0, 0x0, 0x2, 0x43, 0x0, 0x0, 0x86, 0x41, 0x0, 0x0, 0xfc, 0x40, 0x0, 0x0, 0x78, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x60, 0x0, 0x0, 0x82, 0x40, 0x0, 0x0, 0x82, 0x40, 0x0, 0x0, 0x82, 0x40, 0x0, 0x0, 0x82, 0x41, 0x0, 0x0, 0x46, 0x61, 0x0, 0x0, 0x7c, 0x3f, 0x0, 0x0, 0x3c, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0xc0, 0x4, 0x0, 0x0, 0x60, 0x4, 0x0, 0x0, 0x10, 0x4, 0x0, 0x0, 0xc, 0x4, 0x0, 0x0, 0xfe, 0x7f, 0x0, 0x0, 0xfe, 0x7f, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7e, 0x60, 0x0, 0x0, 0x42, 0x40, 0x0, 0x0, 0x42, 0x40, 0x0, 0x0, 0xc2, 0x40, 0x0, 0x0, 0x82, 0x61, 0x0, 0x0, 0x82, 0x3f, 0x0, 0x0, 0x2, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x0, 0x0, 0xe0, 0xf, 0x0, 0x0, 0xf8, 0x3f, 0x0, 0x0, 0x8c, 0x20, 0x0, 0x0, 0x46, 0x40, 0x0, 0x0, 0x42, 0x40, 0x0, 0x0, 0x42, 0x40, 0x0, 0x0, 0xc2, 0x60, 0x0, 0x0, 0x86, 0x3f, 0x0, 0x0, 0x0, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x60, 0x0, 0x0, 0x6, 0x78, 0x0, 0x0, 0x6, 0xe, 0x0, 0x0, 0x86, 0x1, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x38, 0x3e, 0x0, 0x0, 0x7c, 0x61, 0x0, 0x0, 0xe6, 0x40, 0x0, 0x0, 0xc2, 0x41, 0x0, 0x0, 0xc2, 0x41, 0x0, 0x0, 0x66, 0x63, 0x0, 0x0, 0x3c, 0x3f, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0xfc, 0x61, 0x0, 0x0, 0x6, 0x43, 0x0, 0x0, 0x2, 0x42, 0x0, 0x0, 0x2, 0x42, 0x0, 0x0, 0x2, 0x62, 0x0, 0x0, 0x4, 0x31, 0x0, 0x0, 0xfc, 0x1f, 0x0, 0x0, 0xf0, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x60, 0x0, 0x0, 0x60, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x70, 0x4, 0x0, 0x60, 0xf0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x80, 0x19, 0x0, 0x0, 0x80, 0x10, 0x0, 0x0, 0xc0, 0x30, 0x0, 0x0, 0x40, 0x20, 0x0, 0x0, 0x60, 0x60, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x0, 0x0, 0x60, 0x60, 0x0, 0x0, 0x40, 0x20, 0x0, 0x0, 0xc0, 0x30, 0x0, 0x0, 0x80, 0x10, 0x0, 0x0, 0x80, 0x19, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x2, 0x66, 0x0, 0x0, 0x2, 0x67, 0x0, 0x0, 0x82, 0x0, 0x0, 0x0, 0x46, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
