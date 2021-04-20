
// file: font/luBS10.bdf
// font: -B&H-Lucida-Bold-R-Normal-Sans-10-100-75-75-P-66-ISO10646-1

#include <font.h>

const struct Font font_luBS10 = {
    .type       = 1,
    .name	= "luBS10",
    .height	= 10,
    .width	= 10,
    .bytescol	= 2,
    .numcol     = 10,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -6 },	// exclam
	{ .xadj =  -5 },	// quotedbl
	{ .xadj =  -3 },	// numbersign
	{ .xadj =  -3 },	// dollar
	{ .xadj =  -1 },	// percent
	{ .xadj =  -2 },	// ampersand
	{ .xadj =  -7 },	// quotesingle
	{ .xadj =  -6 },	// parenleft
	{ .xadj =  -6 },	// parenright
	{ .xadj =  -5 },	// asterisk
	{ .xadj =  -3 },	// plus
	{ .xadj =  -7 },	// comma
	{ .xadj =  -7 },	// hyphen
	{ .xadj =  -7 },	// period
	{ .xadj =  -4 },	// slash
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
	{ .xadj =  -7 },	// colon
	{ .xadj =  -7 },	// semicolon
	{ .xadj =  -3 },	// less
	{ .xadj =  -3 },	// equal
	{ .xadj =  -3 },	// greater
	{ .xadj =  -4 },	// question
	{ .xadj =  -1 },	// at
	{ .xadj =  -2 },	// A
	{ .xadj =  -3 },	// B
	{ .xadj =  -2 },	// C
	{ .xadj =  -2 },	// D
	{ .xadj =  -3 },	// E
	{ .xadj =  -4 },	// F
	{ .xadj =  -2 },	// G
	{ .xadj =  -2 },	// H
	{ .xadj =  -6 },	// I
	{ .xadj =  -5 },	// J
	{ .xadj =  -2 },	// K
	{ .xadj =  -4 },	// L
	{ .xadj =   0 },	// M
	{ .xadj =  -2 },	// N
	{ .xadj =  -1 },	// O
	{ .xadj =  -3 },	// P
	{ .xadj =  -1 },	// Q
	{ .xadj =  -3 },	// R
	{ .xadj =  -3 },	// S
	{ .xadj =  -3 },	// T
	{ .xadj =  -2 },	// U
	{ .xadj =  -2 },	// V
	{ .xadj =   0 },	// W
	{ .xadj =  -3 },	// X
	{ .xadj =  -2 },	// Y
	{ .xadj =  -3 },	// Z
	{ .xadj =  -6 },	// bracketleft
	{ .xadj =  -4 },	// backslash
	{ .xadj =  -6 },	// bracketright
	{ .xadj =  -3 },	// asciicircum
	{ .xadj =  -2 },	// underscore
	{ .xadj =  -3 },	// grave
	{ .xadj =  -4 },	// a
	{ .xadj =  -3 },	// b
	{ .xadj =  -4 },	// c
	{ .xadj =  -3 },	// d
	{ .xadj =  -3 },	// e
	{ .xadj =  -5 },	// f
	{ .xadj =  -3 },	// g
	{ .xadj =  -3 },	// h
	{ .xadj =  -6 },	// i
	{ .xadj =  -6 },	// j
	{ .xadj =  -3 },	// k
	{ .xadj =  -6 },	// l
	{ .xadj =   0 },	// m
	{ .xadj =  -3 },	// n
	{ .xadj =  -3 },	// o
	{ .xadj =  -3 },	// p
	{ .xadj =  -3 },	// q
	{ .xadj =  -5 },	// r
	{ .xadj =  -4 },	// s
	{ .xadj =  -5 },	// t
	{ .xadj =  -3 },	// u
	{ .xadj =  -2 },	// v
	{ .xadj =  -1 },	// w
	{ .xadj =  -4 },	// x
	{ .xadj =  -3 },	// y
	{ .xadj =  -4 },	// z
	{ .xadj =  -6 },	// braceleft
	{ .xadj =  -6 },	// bar
	{ .xadj =  -6 },	// braceright
	{ .xadj =  -3 },	// asciitilde
	{ .xadj = -10 },	// 
    },
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0xce, 0x0, 0xde, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0xf, 0x0, 0x3, 0x0, 0x0, 0x0, 0xf, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x0, 0x0, 0x0, 0x0, 0x28, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x0, 0x0, 0xfe, 0x0, 0x28, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x0, 0x0, 0x0, 0x0, 0x8c, 0x0, 0x9e, 0x0, 0xf2, 0x1, 0x9f, 0x0, 0xf2, 0x0, 0x62, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 36	dollar
	0x0, 0x0, 0x4, 0x0, 0xa, 0x0, 0xce, 0x0, 0x64, 0x0, 0x10, 0x0, 0x4c, 0x0, 0xa6, 0x0, 0xe0, 0x0, 0x40, 0x0, 	// 37	percent
	0x0, 0x0, 0x0, 0x0, 0x64, 0x0, 0xfe, 0x0, 0x9a, 0x0, 0xbe, 0x0, 0x64, 0x0, 0xd0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0x0, 0x0, 0x7c, 0x0, 0xfe, 0x0, 0x83, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x0, 0x83, 0x1, 0xfe, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x0, 0x0, 0xa, 0x0, 0xe, 0x0, 0x4, 0x0, 0xa, 0x0, 0xa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x10, 0x0, 0x7c, 0x0, 0x10, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x2, 0xc0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x0, 0x80, 0x1, 0xe0, 0x1, 0x70, 0x0, 0x1c, 0x0, 0xf, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 47	slash
	0x0, 0x0, 0x0, 0x0, 0x7c, 0x0, 0xfe, 0x0, 0x82, 0x0, 0x82, 0x0, 0xfe, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x4, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x0, 0x0, 0x0, 0xc4, 0x0, 0xe6, 0x0, 0xb2, 0x0, 0x92, 0x0, 0x9e, 0x0, 0x8c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x0, 0x0, 0x0, 0x44, 0x0, 0xc6, 0x0, 0x92, 0x0, 0x92, 0x0, 0xfe, 0x0, 0x6c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 51	three
	0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x28, 0x0, 0x24, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x0, 0x0, 0x0, 0x5e, 0x0, 0xde, 0x0, 0x92, 0x0, 0x92, 0x0, 0xf2, 0x0, 0x62, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 53	five
	0x0, 0x0, 0x0, 0x0, 0x7c, 0x0, 0xfe, 0x0, 0x92, 0x0, 0x92, 0x0, 0xf6, 0x0, 0x64, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0xc6, 0x0, 0xe6, 0x0, 0x36, 0x0, 0x1e, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 55	seven
	0x0, 0x0, 0x0, 0x0, 0x6c, 0x0, 0xfe, 0x0, 0x92, 0x0, 0x92, 0x0, 0xfe, 0x0, 0x6c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 56	eight
	0x0, 0x0, 0x0, 0x0, 0x4c, 0x0, 0xde, 0x0, 0x92, 0x0, 0x92, 0x0, 0xfe, 0x0, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0xcc, 0x0, 0xcc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x0, 0x0, 0xcc, 0x2, 0xcc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x38, 0x0, 0x28, 0x0, 0x44, 0x0, 0x44, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x0, 0x0, 0x28, 0x0, 0x28, 0x0, 0x28, 0x0, 0x28, 0x0, 0x28, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x0, 0x0, 0x44, 0x0, 0x44, 0x0, 0x28, 0x0, 0x38, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 62	greater
	0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0xd2, 0x0, 0xd2, 0x0, 0x1e, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 63	question
	0x0, 0x0, 0x0, 0x0, 0x7c, 0x0, 0xc6, 0x0, 0x92, 0x0, 0xaa, 0x0, 0xbe, 0x0, 0xbc, 0x0, 0x20, 0x0, 0x0, 0x0, 	// 64	at
	0x0, 0x0, 0x0, 0x0, 0xe0, 0x0, 0x38, 0x0, 0x26, 0x0, 0x3e, 0x0, 0xf8, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 65	A
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x92, 0x0, 0xfe, 0x0, 0x6c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 66	B
	0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x7c, 0x0, 0xc6, 0x0, 0x82, 0x0, 0x82, 0x0, 0x82, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 67	C
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x82, 0x0, 0xc6, 0x0, 0x7c, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 68	D
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x92, 0x0, 0x92, 0x0, 0x82, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 69	E
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x12, 0x0, 0x12, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 70	F
	0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x7c, 0x0, 0xc6, 0x0, 0x82, 0x0, 0xf2, 0x0, 0xf2, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 71	G
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x10, 0x0, 0x10, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 72	H
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 73	I
	0x0, 0x0, 0x0, 0x2, 0x0, 0x2, 0xfe, 0x3, 0xfe, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 74	J
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x10, 0x0, 0x3c, 0x0, 0x66, 0x0, 0xc2, 0x0, 0x80, 0x0, 0x0, 0x0, 	// 75	K
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x80, 0x0, 0x80, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 76	L
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xe, 0x0, 0x1c, 0x0, 0x78, 0x0, 0x10, 0x0, 0xc, 0x0, 0xfe, 0x0, 0xfe, 0x0, 	// 77	M
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xe, 0x0, 0x1c, 0x0, 0x38, 0x0, 0x70, 0x0, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 78	N
	0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x7c, 0x0, 0xc6, 0x0, 0x82, 0x0, 0xc6, 0x0, 0x7c, 0x0, 0x38, 0x0, 0x0, 0x0, 	// 79	O
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x12, 0x0, 0x1e, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 80	P
	0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x7c, 0x0, 0xc6, 0x0, 0x82, 0x0, 0xc6, 0x1, 0x7c, 0x3, 0x38, 0x2, 0x0, 0x0, 	// 81	Q
	0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x12, 0x0, 0x7e, 0x0, 0xec, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 82	R
	0x0, 0x0, 0x0, 0x0, 0x8c, 0x0, 0x9e, 0x0, 0xba, 0x0, 0xf2, 0x0, 0x62, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 83	S
	0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x2, 0x0, 0xfe, 0x0, 0xfe, 0x0, 0x2, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 84	T
	0x0, 0x0, 0x0, 0x0, 0x7e, 0x0, 0xfe, 0x0, 0x80, 0x0, 0x80, 0x0, 0xfe, 0x0, 0x7e, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 85	U
	0x0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x3e, 0x0, 0xf0, 0x0, 0xe0, 0x0, 0x3e, 0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 86	V
	0x0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x3e, 0x0, 0xf0, 0x0, 0xc0, 0x0, 0x3c, 0x0, 0xf0, 0x0, 0xc0, 0x0, 0x3e, 0x0, 	// 87	W
	0x0, 0x0, 0x0, 0x0, 0xc6, 0x0, 0xee, 0x0, 0x38, 0x0, 0xee, 0x0, 0xc6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 88	X
	0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0xe, 0x0, 0xf8, 0x0, 0xf0, 0x0, 0xe, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 89	Y
	0x0, 0x0, 0x0, 0x0, 0xc2, 0x0, 0xf2, 0x0, 0xba, 0x0, 0x9e, 0x0, 0x86, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 90	Z
	0x0, 0x0, 0x0, 0x0, 0xff, 0x1, 0xff, 0x1, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 91	bracketleft
	0x0, 0x0, 0x3, 0x0, 0xf, 0x0, 0x1c, 0x0, 0x70, 0x0, 0xe0, 0x1, 0x80, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 92	backslash
	0x0, 0x0, 0x1, 0x1, 0xff, 0x1, 0xff, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 93	bracketright
	0x0, 0x0, 0x0, 0x0, 0x60, 0x0, 0x18, 0x0, 0x6, 0x0, 0x1e, 0x0, 0x78, 0x0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 94	asciicircum
	0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 	// 95	underscore
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x3, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 96	grave
	0x0, 0x0, 0x60, 0x0, 0xf4, 0x0, 0x94, 0x0, 0x7c, 0x0, 0xf8, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 97	a
	0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0xff, 0x0, 0x84, 0x0, 0xfc, 0x0, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 98	b
	0x0, 0x0, 0x0, 0x0, 0x78, 0x0, 0xfc, 0x0, 0x84, 0x0, 0x84, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 99	c
	0x0, 0x0, 0x0, 0x0, 0x78, 0x0, 0xfc, 0x0, 0x84, 0x0, 0x7f, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 100	d
	0x0, 0x0, 0x0, 0x0, 0x78, 0x0, 0xfc, 0x0, 0xa4, 0x0, 0xbc, 0x0, 0xb8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 101	e
	0x0, 0x0, 0x4, 0x0, 0xfe, 0x0, 0xff, 0x0, 0x5, 0x0, 0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 102	f
	0x0, 0x0, 0x0, 0x0, 0x78, 0x2, 0xfc, 0x2, 0x84, 0x2, 0xfc, 0x3, 0xfc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 103	g
	0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0xff, 0x0, 0x8, 0x0, 0xfc, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 104	h
	0x0, 0x0, 0x0, 0x0, 0xfd, 0x0, 0xfd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 105	i
	0x0, 0x2, 0x0, 0x2, 0xfd, 0x3, 0xfd, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 106	j
	0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0xff, 0x0, 0x30, 0x0, 0x68, 0x0, 0xc4, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 107	k
	0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 108	l
	0x0, 0x0, 0x0, 0x0, 0xfc, 0x0, 0xf8, 0x0, 0x4, 0x0, 0xfc, 0x0, 0xf8, 0x0, 0x4, 0x0, 0xfc, 0x0, 0xf8, 0x0, 	// 109	m
	0x0, 0x0, 0x0, 0x0, 0xfc, 0x0, 0xf8, 0x0, 0x4, 0x0, 0xfc, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 110	n
	0x0, 0x0, 0x0, 0x0, 0x78, 0x0, 0xfc, 0x0, 0x84, 0x0, 0xfc, 0x0, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 111	o
	0x0, 0x0, 0x0, 0x0, 0xfc, 0x3, 0xf8, 0x3, 0x84, 0x0, 0xfc, 0x0, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 112	p
	0x0, 0x0, 0x0, 0x0, 0x78, 0x0, 0xfc, 0x0, 0x84, 0x0, 0xfc, 0x3, 0xfc, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 113	q
	0x0, 0x0, 0x0, 0x0, 0xfc, 0x0, 0xfc, 0x0, 0x8, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 114	r
	0x0, 0x0, 0x0, 0x0, 0x98, 0x0, 0xbc, 0x0, 0xf4, 0x0, 0x64, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 115	s
	0x0, 0x0, 0x4, 0x0, 0x7e, 0x0, 0xfe, 0x0, 0x84, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 116	t
	0x0, 0x0, 0x0, 0x0, 0x7c, 0x0, 0xfc, 0x0, 0x80, 0x0, 0x7c, 0x0, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 117	u
	0x0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x3c, 0x0, 0xf0, 0x0, 0xc0, 0x0, 0x3c, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 118	v
	0x0, 0x0, 0x0, 0x0, 0x3c, 0x0, 0xfc, 0x0, 0xc0, 0x0, 0x38, 0x0, 0xf8, 0x0, 0xc0, 0x0, 0x3c, 0x0, 0x0, 0x0, 	// 119	w
	0x0, 0x0, 0x0, 0x0, 0xcc, 0x0, 0x3c, 0x0, 0xf0, 0x0, 0xcc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 120	x
	0x0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x3c, 0x3, 0xf0, 0x3, 0xc0, 0x0, 0x3c, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 121	y
	0x0, 0x0, 0x0, 0x0, 0xc4, 0x0, 0xf4, 0x0, 0xbc, 0x0, 0x8c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 122	z
	0x0, 0x0, 0x10, 0x0, 0xd6, 0x0, 0xef, 0x1, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 123	braceleft
	0x0, 0x0, 0x0, 0x0, 0xff, 0x1, 0xff, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 124	bar
	0x0, 0x0, 0x1, 0x1, 0xef, 0x1, 0xd6, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 125	braceright
	0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x8, 0x0, 0x18, 0x0, 0x18, 0x0, 0x10, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 126	asciitilde
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 127	
    }
};
