
// file: font/helvO10.bdf
// font: -Adobe-Helvetica-Medium-O-Normal--10-100-75-75-P-57-ISO10646-1

#include <font.h>

const struct Font font_helvO10_n = {
    .type       = 1,
    .name	= "helvO10_n",
    .height	= 10,
    .width	= 9,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -5 },	// exclam
	{ .xadj =  -5 },	// quotedbl
	{ .xadj =  -2 },	// numbersign
	{ .xadj =  -3 },	// dollar
	{ .xadj =   0 },	// percent
	{ .xadj =  -1 },	// ampersand
	{ .xadj =  -7 },	// quotesingle
	{ .xadj =  -5 },	// parenleft
	{ .xadj =  -5 },	// parenright
	{ .xadj =  -5 },	// asterisk
	{ .xadj =  -3 },	// plus
	{ .xadj =  -6 },	// comma
	{ .xadj =  -3 },	// hyphen
	{ .xadj =  -6 },	// period
	{ .xadj =  -6 },	// slash
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
	{ .xadj =  -6 },	// colon
	{ .xadj =  -6 },	// semicolon
	{ .xadj =  -3 },	// less
	{ .xadj =  -2 },	// equal
	{ .xadj =  -3 },	// greater
	{ .xadj =  -3 },	// question
    },
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x38, 0x0, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x3, 0x0, 0x4, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x0, 0x20, 0x0, 0xe8, 0x0, 0x38, 0x0, 0xee, 0x0, 0x38, 0x0, 0x2e, 0x0, 0x8, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x40, 0x0, 0x8c, 0x1, 0xf2, 0x0, 0x9e, 0x0, 0x73, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x0, 0x0, 0x0, 0x0, 0x8e, 0x0, 0x49, 0x0, 0x25, 0x0, 0xdb, 0x0, 0xa4, 0x0, 0x92, 0x0, 0x71, 0x0, 	// 37	percent
	0x0, 0x0, 0x60, 0x0, 0x90, 0x0, 0x8e, 0x0, 0x99, 0x0, 0x69, 0x0, 0xa6, 0x0, 0x10, 0x0, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0xf0, 0x1, 0xc, 0x2, 0x2, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x2, 0x0, 0x1, 0xc1, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x3, 0x0, 0x6, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x70, 0x0, 0x1c, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x2, 0x80, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x10, 0x0, 0x10, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0xc0, 0x0, 0x30, 0x0, 0xc, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0x78, 0x0, 0x86, 0x0, 0x83, 0x0, 0xc1, 0x0, 0x61, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe2, 0x0, 0x1e, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0xc0, 0x0, 0xa2, 0x0, 0x91, 0x0, 0x91, 0x0, 0x89, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x40, 0x0, 0x82, 0x0, 0x89, 0x0, 0x89, 0x0, 0x79, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x0, 0x20, 0x0, 0x30, 0x0, 0x28, 0x0, 0xe4, 0x0, 0x3a, 0x0, 0x27, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x60, 0x0, 0x8c, 0x0, 0x8b, 0x0, 0x89, 0x0, 0x49, 0x0, 0x31, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x78, 0x0, 0x8e, 0x0, 0x89, 0x0, 0x89, 0x0, 0x71, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x0, 0x0, 0xc1, 0x0, 0x21, 0x0, 0x19, 0x0, 0x5, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x60, 0x0, 0x9e, 0x0, 0x89, 0x0, 0x89, 0x0, 0x79, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x40, 0x0, 0x8e, 0x0, 0x91, 0x0, 0x91, 0x0, 0x71, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x80, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x2, 0x80, 0x1, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x28, 0x0, 0x48, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x28, 0x0, 0x28, 0x0, 0x28, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x24, 0x0, 0x28, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x32, 0x0, 0x9, 0x0, 0x9, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
    }
};
