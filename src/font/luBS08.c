
// file: font/luBS08.bdf
// font: -B&H-Lucida-Bold-R-Normal-Sans-8-80-75-75-P-50-ISO10646-1

#include <font.h>

const struct Font font_luBS08 = {
    .type       = 1,
    .name	= "luBS08",
    .height	= 8,
    .width	= 8,
    .lineheight = 8,
    .bytescol	= 1,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = (const struct FontMetric[]){
	{ .xadj =  -5 },	// exclam
	{ .xadj =  -4 },	// quotedbl
	{ .xadj =  -3 },	// numbersign
	{ .xadj =  -3 },	// dollar
	{ .xadj =  -1 },	// percent
	{ .xadj =  -2 },	// ampersand
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
	{ .xadj =  -3 },	// question
	{ .xadj =  -1 },	// at
	{ .xadj =  -2 },	// A
	{ .xadj =  -3 },	// B
	{ .xadj =  -2 },	// C
	{ .xadj =  -1 },	// D
	{ .xadj =  -3 },	// E
	{ .xadj =  -3 },	// F
	{ .xadj =  -2 },	// G
	{ .xadj =  -1 },	// H
	{ .xadj =  -5 },	// I
	{ .xadj =  -4 },	// J
	{ .xadj =  -2 },	// K
	{ .xadj =  -3 },	// L
	{ .xadj =   0 },	// M
	{ .xadj =  -2 },	// N
	{ .xadj =  -1 },	// O
	{ .xadj =  -3 },	// P
	{ .xadj =  -1 },	// Q
	{ .xadj =  -2 },	// R
	{ .xadj =  -3 },	// S
	{ .xadj =  -2 },	// T
	{ .xadj =  -2 },	// U
	{ .xadj =  -2 },	// V
	{ .xadj =   0 },	// W
	{ .xadj =  -2 },	// X
	{ .xadj =  -2 },	// Y
	{ .xadj =  -3 },	// Z
	{ .xadj =  -5 },	// bracketleft
	{ .xadj =  -3 },	// backslash
	{ .xadj =  -5 },	// bracketright
	{ .xadj =  -3 },	// asciicircum
	{ .xadj =  -4 },	// underscore
	{ .xadj =  -3 },	// grave
	{ .xadj =  -3 },	// a
	{ .xadj =  -2 },	// b
	{ .xadj =  -4 },	// c
	{ .xadj =  -2 },	// d
	{ .xadj =  -3 },	// e
	{ .xadj =  -4 },	// f
	{ .xadj =  -2 },	// g
	{ .xadj =  -2 },	// h
	{ .xadj =  -5 },	// i
	{ .xadj =  -5 },	// j
	{ .xadj =  -3 },	// k
	{ .xadj =  -5 },	// l
	{ .xadj =   0 },	// m
	{ .xadj =  -2 },	// n
	{ .xadj =  -3 },	// o
	{ .xadj =  -2 },	// p
	{ .xadj =  -2 },	// q
	{ .xadj =  -4 },	// r
	{ .xadj =  -3 },	// s
	{ .xadj =  -5 },	// t
	{ .xadj =  -2 },	// u
	{ .xadj =  -3 },	// v
	{ .xadj =  -1 },	// w
	{ .xadj =  -3 },	// x
	{ .xadj =  -3 },	// y
	{ .xadj =  -3 },	// z
	{ .xadj =  -5 },	// braceleft
	{ .xadj =  -6 },	// bar
	{ .xadj =  -5 },	// braceright
	{ .xadj =  -3 },	// asciitilde
	{ .xadj =  -8 },	// 
    },
    .data       = {
	0x0, 0x2f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x3, 0x1, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0x34, 0x3c, 0x37, 0x1f, 0x15, 0x0, 0x0, 0x0, 	// 35	numbersign
	0x44, 0x4e, 0xff, 0x52, 0x32, 0x0, 0x0, 0x0, 	// 36	dollar
	0x6, 0x29, 0x1e, 0xc, 0x36, 0x31, 0x30, 0x0, 	// 37	percent
	0x18, 0x27, 0x2d, 0x3d, 0x33, 0x2c, 0x0, 0x0, 	// 38	ampersand
	0x7, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x3c, 0xc3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0xc3, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x3, 0x1, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x8, 0x8, 0x3e, 0x8, 0x8, 0x0, 0x0, 0x0, 	// 43	plus
	0xa0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x8, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x20, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x80, 0x60, 0x18, 0x6, 0x1, 0x0, 0x0, 0x0, 	// 47	slash
	0x1e, 0x21, 0x21, 0x21, 0x1e, 0x0, 0x0, 0x0, 	// 48	zero
	0x0, 0x1, 0x3f, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 49	one
	0x0, 0x31, 0x31, 0x29, 0x26, 0x0, 0x0, 0x0, 	// 50	two
	0x0, 0x21, 0x25, 0x25, 0x1a, 0x0, 0x0, 0x0, 	// 51	three
	0xc, 0xe, 0xb, 0x3f, 0x8, 0x0, 0x0, 0x0, 	// 52	four
	0x0, 0x27, 0x25, 0x25, 0x19, 0x0, 0x0, 0x0, 	// 53	five
	0x1e, 0x25, 0x25, 0x25, 0x19, 0x0, 0x0, 0x0, 	// 54	six
	0x0, 0x21, 0x39, 0x7, 0x3, 0x0, 0x0, 0x0, 	// 55	seven
	0x1a, 0x25, 0x25, 0x2d, 0x1a, 0x0, 0x0, 0x0, 	// 56	eight
	0x26, 0x29, 0x29, 0x29, 0x1e, 0x0, 0x0, 0x0, 	// 57	nine
	0x0, 0x24, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0xe4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x8, 0x8, 0x14, 0x14, 0x22, 0x0, 0x0, 0x0, 	// 60	less
	0x14, 0x14, 0x14, 0x14, 0x14, 0x0, 0x0, 0x0, 	// 61	equal
	0x22, 0x14, 0x14, 0x8, 0x8, 0x0, 0x0, 0x0, 	// 62	greater
	0x1, 0x29, 0x9, 0x7, 0x0, 0x0, 0x0, 0x0, 	// 63	question
	0x1c, 0x22, 0x39, 0x2d, 0x17, 0x13, 0xe, 0x0, 	// 64	at
	0x30, 0x1c, 0xb, 0xf, 0x3c, 0x20, 0x0, 0x0, 	// 65	A
	0x0, 0x3f, 0x25, 0x2d, 0x3b, 0x0, 0x0, 0x0, 	// 66	B
	0x1e, 0x33, 0x21, 0x21, 0x21, 0x0, 0x0, 0x0, 	// 67	C
	0x3f, 0x21, 0x21, 0x21, 0x23, 0x1e, 0x0, 0x0, 	// 68	D
	0x0, 0x3f, 0x25, 0x25, 0x21, 0x0, 0x0, 0x0, 	// 69	E
	0x0, 0x3f, 0x9, 0x9, 0x0, 0x0, 0x0, 0x0, 	// 70	F
	0x1e, 0x33, 0x21, 0x21, 0x39, 0x0, 0x0, 0x0, 	// 71	G
	0x0, 0x3f, 0x4, 0x4, 0x4, 0x3f, 0x0, 0x0, 	// 72	H
	0x0, 0x3f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 73	I
	0x80, 0x80, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 74	J
	0x0, 0x3f, 0x4, 0x1a, 0x21, 0x21, 0x0, 0x0, 	// 75	K
	0x0, 0x3f, 0x20, 0x20, 0x20, 0x0, 0x0, 0x0, 	// 76	L
	0x0, 0x3f, 0x7, 0x1c, 0x38, 0x7, 0x3f, 0x0, 	// 77	M
	0x0, 0x3f, 0x2, 0xc, 0x10, 0x3f, 0x0, 0x0, 	// 78	N
	0x1e, 0x33, 0x21, 0x21, 0x33, 0x1e, 0x0, 0x0, 	// 79	O
	0x0, 0x3f, 0x9, 0x9, 0x7, 0x0, 0x0, 0x0, 	// 80	P
	0x1e, 0x33, 0x21, 0x21, 0x73, 0xde, 0x40, 0x0, 	// 81	Q
	0x0, 0x3f, 0x9, 0x19, 0x27, 0x20, 0x0, 0x0, 	// 82	R
	0x26, 0x27, 0x29, 0x19, 0x0, 0x0, 0x0, 0x0, 	// 83	S
	0x1, 0x1, 0x3f, 0x1, 0x1, 0x0, 0x0, 0x0, 	// 84	T
	0x0, 0x1f, 0x20, 0x20, 0x20, 0x1f, 0x0, 0x0, 	// 85	U
	0x1, 0x7, 0x38, 0x30, 0xe, 0x1, 0x0, 0x0, 	// 86	V
	0x1, 0x3e, 0x38, 0x7, 0x3c, 0x3c, 0x3, 0x0, 	// 87	W
	0x21, 0x1b, 0xc, 0x33, 0x21, 0x0, 0x0, 0x0, 	// 88	X
	0x1, 0x3, 0x3c, 0x6, 0x1, 0x0, 0x0, 0x0, 	// 89	Y
	0x0, 0x31, 0x39, 0x27, 0x23, 0x0, 0x0, 0x0, 	// 90	Z
	0x0, 0xff, 0x81, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 91	bracketleft
	0x1, 0x6, 0x18, 0x60, 0x80, 0x0, 0x0, 0x0, 	// 92	backslash
	0x81, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 93	bracketright
	0x10, 0xc, 0x3, 0xc, 0x10, 0x0, 0x0, 0x0, 	// 94	asciicircum
	0x80, 0x80, 0x80, 0x80, 0x0, 0x0, 0x0, 0x0, 	// 95	underscore
	0x0, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 96	grave
	0x34, 0x34, 0x34, 0x3c, 0x0, 0x0, 0x0, 0x0, 	// 97	a
	0x3f, 0x24, 0x24, 0x24, 0x18, 0x0, 0x0, 0x0, 	// 98	b
	0x0, 0x18, 0x24, 0x24, 0x0, 0x0, 0x0, 0x0, 	// 99	c
	0x18, 0x24, 0x24, 0x24, 0x3f, 0x0, 0x0, 0x0, 	// 100	d
	0x18, 0x3c, 0x2c, 0x2c, 0x0, 0x0, 0x0, 0x0, 	// 101	e
	0x4, 0x3f, 0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 102	f
	0x98, 0xa4, 0xa4, 0xe4, 0x7c, 0x0, 0x0, 0x0, 	// 103	g
	0x0, 0x3f, 0x4, 0x4, 0x3c, 0x0, 0x0, 0x0, 	// 104	h
	0x0, 0x3d, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 105	i
	0x80, 0xfd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 106	j
	0x0, 0x3f, 0x18, 0x3c, 0x24, 0x0, 0x0, 0x0, 	// 107	k
	0x0, 0x3f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 108	l
	0x0, 0x3c, 0x4, 0x4, 0x3c, 0x4, 0x4, 0x3c, 	// 109	m
	0x0, 0x3c, 0x4, 0x4, 0x3c, 0x0, 0x0, 0x0, 	// 110	n
	0x18, 0x24, 0x24, 0x24, 0x18, 0x0, 0x0, 0x0, 	// 111	o
	0xfc, 0x24, 0x24, 0x24, 0x18, 0x0, 0x0, 0x0, 	// 112	p
	0x18, 0x24, 0x24, 0x24, 0xfc, 0x0, 0x0, 0x0, 	// 113	q
	0x0, 0x3c, 0x4, 0x4, 0x0, 0x0, 0x0, 0x0, 	// 114	r
	0x0, 0x2c, 0x2c, 0x34, 0x34, 0x0, 0x0, 0x0, 	// 115	s
	0x0, 0x3f, 0x24, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 116	t
	0x0, 0x3c, 0x20, 0x20, 0x3c, 0x0, 0x0, 0x0, 	// 117	u
	0x4, 0x1c, 0x20, 0x38, 0x4, 0x0, 0x0, 0x0, 	// 118	v
	0x4, 0x38, 0x30, 0xc, 0x3c, 0x38, 0xc, 0x0, 	// 119	w
	0x24, 0x1c, 0x38, 0x24, 0x0, 0x0, 0x0, 0x0, 	// 120	x
	0x4, 0x9c, 0x60, 0x18, 0x4, 0x0, 0x0, 0x0, 	// 121	y
	0x24, 0x34, 0x2c, 0x24, 0x0, 0x0, 0x0, 0x0, 	// 122	z
	0x0, 0x10, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 123	braceleft
	0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 124	bar
	0x0, 0xff, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 125	braceright
	0x18, 0x8, 0x18, 0x10, 0x18, 0x0, 0x0, 0x0, 	// 126	asciitilde
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 127	
    }
};
