
// file: font/lutRS08.bdf
// font: -B&H-LucidaTypewriter-Medium-R-Normal-Sans-8-80-75-75-M-50-ISO10646-1

#include <font.h>

const struct Font font_lutRS08_n = {
    .type       = 1,
    .name	= "lutRS08_n",
    .height	= 8,
    .width	= 5,
    .lineheight = 8,
    .bytescol	= 1,
    .numcol     = 5,
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
	0x0, 0x0, 0x2f, 0x0, 0x0, 	// 33	exclam
	0x0, 0x3, 0x0, 0x3, 0x0, 	// 34	quotedbl
	0x3a, 0xf, 0x3e, 0xb, 0x0, 	// 35	numbersign
	0x0, 0x27, 0x7f, 0x39, 0x0, 	// 36	dollar
	0x27, 0x1f, 0x3e, 0x39, 0x0, 	// 37	percent
	0x18, 0x27, 0x3f, 0x58, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x3, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x3c, 0x43, 0x81, 0x0, 	// 40	parenleft
	0x0, 0x81, 0x42, 0x3c, 0x0, 	// 41	parenright
	0x6, 0x7, 0x6, 0x6, 0x0, 	// 42	asterisk
	0x8, 0x8, 0x3c, 0x8, 0x8, 	// 43	plus
	0x0, 0x0, 0xe0, 0x0, 0x0, 	// 44	comma
	0x8, 0x8, 0x8, 0x8, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x20, 0x0, 0x0, 	// 46	period
	0xc0, 0x70, 0xe, 0x3, 0x0, 	// 47	slash
	0x1e, 0x21, 0x21, 0x1e, 0x0, 	// 48	zero
	0x21, 0x21, 0x3f, 0x20, 0x20, 	// 49	one
	0x0, 0x31, 0x29, 0x27, 0x0, 	// 50	two
	0x0, 0x25, 0x25, 0x1b, 0x0, 	// 51	three
	0x18, 0x16, 0x3f, 0x10, 0x0, 	// 52	four
	0x0, 0x27, 0x25, 0x19, 0x0, 	// 53	five
	0x0, 0x1e, 0x25, 0x25, 0x19, 	// 54	six
	0x0, 0x31, 0xd, 0x3, 0x0, 	// 55	seven
	0x1a, 0x2d, 0x2d, 0x1b, 0x0, 	// 56	eight
	0x26, 0x29, 0x29, 0x1e, 0x0, 	// 57	nine
	0x0, 0x0, 0x24, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0xe4, 0x0, 0x0, 	// 59	semicolon
	0x18, 0x18, 0x3c, 0x24, 0x0, 	// 60	less
	0x18, 0x18, 0x18, 0x18, 0x0, 	// 61	equal
	0x24, 0x3c, 0x18, 0x18, 0x0, 	// 62	greater
	0x3, 0x29, 0x5, 0x7, 0x0, 	// 63	question
    }
};
