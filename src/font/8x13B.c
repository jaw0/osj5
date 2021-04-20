
// file: font/8x13B.bdf
// font: -Misc-Fixed-Bold-R-Normal--13-120-75-75-C-80-ISO10646-1

#include <font.h>

const struct Font font_8x13B = {
    .type       = 1,
    .name	= "8x13B",
    .height	= 13,
    .width	= 8,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .data       = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfe, 0x6, 0xfe, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 33	exclam
	0x0, 0x0, 0x1e, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 34	quotedbl
	0xb0, 0x1, 0xfc, 0x7, 0xfc, 0x7, 0xb0, 0x1, 0xfc, 0x7, 0xfc, 0x7, 0xb0, 0x1, 0x0, 0x0, 	// 35	numbersign
	0x38, 0x2, 0x7c, 0x6, 0x64, 0x4, 0xfe, 0xf, 0xc4, 0x4, 0xcc, 0x7, 0x88, 0x3, 0x0, 0x0, 	// 36	dollar
	0xe, 0x6, 0xa, 0x7, 0xce, 0x1, 0xf0, 0x0, 0x38, 0x7, 0xe, 0x5, 0x6, 0x7, 0x0, 0x0, 	// 37	percent
	0x60, 0x3, 0xf0, 0x7, 0x90, 0x4, 0x90, 0x4, 0xf0, 0x7, 0x60, 0x7, 0x0, 0x5, 0x0, 0x0, 	// 38	ampersand
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 39	quotesingle
	0x0, 0x0, 0xe0, 0x0, 0xf8, 0x3, 0x1c, 0x7, 0x6, 0xc, 0x2, 0x8, 0x0, 0x0, 0x0, 0x0, 	// 40	parenleft
	0x0, 0x0, 0x2, 0x8, 0x6, 0xc, 0x1c, 0x7, 0xf8, 0x3, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 41	parenright
	0x20, 0x0, 0x20, 0x3, 0xe0, 0x1, 0xf8, 0x0, 0xe0, 0x1, 0x20, 0x3, 0x20, 0x0, 0x0, 0x0, 	// 42	asterisk
	0x0, 0x0, 0x60, 0x0, 0x60, 0x0, 0xf8, 0x1, 0xf8, 0x1, 0x60, 0x0, 0x60, 0x0, 0x0, 0x0, 	// 43	plus
	0x0, 0x0, 0x0, 0x0, 0x80, 0x8, 0x80, 0xf, 0x80, 0x7, 0x80, 0x3, 0x0, 0x0, 0x0, 0x0, 	// 44	comma
	0x0, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x0, 0x0, 	// 45	hyphen
	0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x7, 0x0, 0x7, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 	// 46	period
	0x0, 0x7, 0x80, 0x3, 0xc0, 0x0, 0x60, 0x0, 0x30, 0x0, 0x1c, 0x0, 0xe, 0x0, 0x0, 0x0, 	// 47	slash
	0xf8, 0x1, 0xfc, 0x3, 0x6, 0x6, 0x2, 0x4, 0x6, 0x6, 0xfc, 0x3, 0xf8, 0x1, 0x0, 0x0, 	// 48	zero
	0x0, 0x0, 0x8, 0x4, 0xc, 0x4, 0xfe, 0x7, 0xfe, 0x7, 0x0, 0x4, 0x0, 0x4, 0x0, 0x0, 	// 49	one
	0xc, 0x6, 0xe, 0x7, 0x82, 0x5, 0xc2, 0x4, 0x62, 0x4, 0x3e, 0x4, 0x1c, 0x4, 0x0, 0x0, 	// 50	two
	0x2, 0x2, 0x2, 0x6, 0x22, 0x4, 0x32, 0x4, 0x3a, 0x4, 0xee, 0x7, 0xc6, 0x3, 0x0, 0x0, 	// 51	three
	0xe0, 0x0, 0xf0, 0x0, 0x98, 0x0, 0x8c, 0x0, 0xfe, 0x7, 0xfe, 0x7, 0x80, 0x0, 0x0, 0x0, 	// 52	four
	0x3e, 0x2, 0x3e, 0x6, 0x32, 0x4, 0x12, 0x4, 0x12, 0x4, 0xf2, 0x7, 0xe2, 0x3, 0x0, 0x0, 	// 53	five
	0xf8, 0x3, 0xfc, 0x7, 0x66, 0x6, 0x22, 0x4, 0x22, 0x4, 0xe2, 0x7, 0xc0, 0x3, 0x0, 0x0, 	// 54	six
	0x2, 0x0, 0x2, 0x0, 0x82, 0x7, 0xe2, 0x7, 0x72, 0x0, 0x1e, 0x0, 0xe, 0x0, 0x0, 0x0, 	// 55	seven
	0xdc, 0x3, 0xfe, 0x7, 0x22, 0x4, 0x22, 0x4, 0x22, 0x4, 0xfe, 0x7, 0xdc, 0x3, 0x0, 0x0, 	// 56	eight
	0x3c, 0x0, 0x7e, 0x4, 0x42, 0x4, 0x42, 0x4, 0x66, 0x6, 0xfe, 0x3, 0xfc, 0x1, 0x0, 0x0, 	// 57	nine
	0x0, 0x0, 0x0, 0x0, 0x10, 0x2, 0x38, 0x7, 0x38, 0x7, 0x10, 0x2, 0x0, 0x0, 0x0, 0x0, 	// 58	colon
	0x0, 0x0, 0x0, 0x0, 0x90, 0x8, 0xb8, 0xf, 0xb8, 0x7, 0x90, 0x3, 0x0, 0x0, 0x0, 0x0, 	// 59	semicolon
	0x0, 0x0, 0x40, 0x0, 0xe0, 0x0, 0xb0, 0x1, 0x18, 0x3, 0xc, 0x6, 0x4, 0x4, 0x0, 0x0, 	// 60	less
	0x0, 0x0, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x20, 0x1, 0x0, 0x0, 	// 61	equal
	0x0, 0x0, 0x4, 0x4, 0xc, 0x6, 0x18, 0x3, 0xb0, 0x1, 0xe0, 0x0, 0x40, 0x0, 0x0, 0x0, 	// 62	greater
	0xc, 0x0, 0xe, 0x0, 0x2, 0x0, 0xc2, 0x6, 0xe2, 0x6, 0x3e, 0x0, 0x1c, 0x0, 0x0, 0x0, 	// 63	question
	0xf8, 0x3, 0xfc, 0x7, 0xc, 0x6, 0xec, 0x5, 0x3c, 0x5, 0x3c, 0x5, 0xf8, 0x5, 0x0, 0x0, 	// 64	at
	0xf8, 0x7, 0xfc, 0x7, 0x46, 0x0, 0x46, 0x0, 0x46, 0x0, 0xfc, 0x7, 0xf8, 0x7, 0x0, 0x0, 	// 65	A
	0x2, 0x4, 0xfe, 0x7, 0xfe, 0x7, 0x22, 0x4, 0x22, 0x4, 0xfe, 0x7, 0xdc, 0x3, 0x0, 0x0, 	// 66	B
	0xfc, 0x3, 0xfe, 0x7, 0x6, 0x6, 0x2, 0x4, 0x2, 0x4, 0xe, 0x7, 0xc, 0x3, 0x0, 0x0, 	// 67	C
	0x2, 0x4, 0xfe, 0x7, 0xfe, 0x7, 0x2, 0x4, 0x2, 0x4, 0xfe, 0x7, 0xfc, 0x3, 0x0, 0x0, 	// 68	D
	0xfe, 0x7, 0xfe, 0x7, 0x22, 0x4, 0x22, 0x4, 0x22, 0x4, 0x2, 0x4, 0x2, 0x4, 0x0, 0x0, 	// 69	E
	0xfe, 0x7, 0xfe, 0x7, 0x22, 0x0, 0x22, 0x0, 0x22, 0x0, 0x2, 0x0, 0x2, 0x0, 0x0, 0x0, 	// 70	F
	0xfc, 0x3, 0xfe, 0x7, 0x2, 0x4, 0x2, 0x4, 0x82, 0x4, 0x8e, 0x7, 0x8c, 0x3, 0x0, 0x0, 	// 71	G
	0xfe, 0x7, 0xfe, 0x7, 0x20, 0x0, 0x20, 0x0, 0x20, 0x0, 0xfe, 0x7, 0xfe, 0x7, 0x0, 0x0, 	// 72	H
	0x0, 0x0, 0x0, 0x0, 0x2, 0x4, 0xfe, 0x7, 0xfe, 0x7, 0x2, 0x4, 0x0, 0x0, 0x0, 0x0, 	// 73	I
	0x0, 0x3, 0x0, 0x7, 0x0, 0x4, 0x0, 0x4, 0x2, 0x4, 0xfe, 0x7, 0xfe, 0x3, 0x0, 0x0, 	// 74	J
	0xfe, 0x7, 0xfe, 0x7, 0x60, 0x0, 0xf0, 0x0, 0x98, 0x1, 0xe, 0x7, 0x6, 0x6, 0x0, 0x0, 	// 75	K
	0xfe, 0x7, 0xfe, 0x7, 0x0, 0x4, 0x0, 0x4, 0x0, 0x4, 0x0, 0x4, 0x0, 0x6, 0x0, 0x0, 	// 76	L
	0xfe, 0x7, 0xfe, 0x7, 0x18, 0x0, 0x30, 0x0, 0x18, 0x0, 0xfe, 0x7, 0xfe, 0x7, 0x0, 0x0, 	// 77	M
	0xfe, 0x7, 0xfe, 0x7, 0x38, 0x0, 0x60, 0x0, 0xc0, 0x1, 0xfe, 0x7, 0xfe, 0x7, 0x0, 0x0, 	// 78	N
	0xfc, 0x3, 0xfe, 0x7, 0x2, 0x4, 0x2, 0x4, 0x2, 0x4, 0xfe, 0x7, 0xfc, 0x3, 0x0, 0x0, 	// 79	O
	0xfe, 0x7, 0xfe, 0x7, 0x42, 0x0, 0x42, 0x0, 0x42, 0x0, 0x7e, 0x0, 0x3c, 0x0, 0x0, 0x0, 	// 80	P
	0xfc, 0x3, 0xfe, 0x7, 0x2, 0x4, 0x2, 0x6, 0x2, 0x6, 0xfe, 0xf, 0xfc, 0xb, 0x0, 0x0, 	// 81	Q
	0xfe, 0x7, 0xfe, 0x7, 0x62, 0x0, 0x62, 0x0, 0xe2, 0x1, 0xbe, 0x7, 0x1c, 0x6, 0x0, 0x0, 	// 82	R
	0x1c, 0x3, 0x3e, 0x7, 0x22, 0x4, 0x22, 0x4, 0x22, 0x4, 0xee, 0x7, 0xcc, 0x3, 0x0, 0x0, 	// 83	S
	0x0, 0x0, 0x2, 0x0, 0x2, 0x0, 0xfe, 0x7, 0xfe, 0x7, 0x2, 0x0, 0x2, 0x0, 0x0, 0x0, 	// 84	T
	0xfe, 0x3, 0xfe, 0x7, 0x0, 0x4, 0x0, 0x4, 0x0, 0x4, 0xfe, 0x7, 0xfe, 0x3, 0x0, 0x0, 	// 85	U
	0x1e, 0x0, 0xfe, 0x0, 0xc0, 0x3, 0x0, 0x7, 0xc0, 0x3, 0xfe, 0x0, 0x1e, 0x0, 0x0, 0x0, 	// 86	V
	0xfe, 0x3, 0xfe, 0x7, 0x0, 0x6, 0x80, 0x3, 0x0, 0x6, 0xfe, 0x7, 0xfe, 0x3, 0x0, 0x0, 	// 87	W
	0x6, 0x6, 0x9e, 0x7, 0xf8, 0x1, 0x60, 0x0, 0xf8, 0x1, 0x9e, 0x7, 0x6, 0x6, 0x0, 0x0, 	// 88	X
	0x0, 0x0, 0xe, 0x0, 0x3e, 0x0, 0xf0, 0x7, 0xf0, 0x7, 0x3e, 0x0, 0xe, 0x0, 0x0, 0x0, 	// 89	Y
	0x2, 0x7, 0x82, 0x7, 0xc2, 0x4, 0x62, 0x4, 0x32, 0x4, 0x1e, 0x4, 0xe, 0x4, 0x0, 0x0, 	// 90	Z
	0x0, 0x0, 0xfe, 0xf, 0xfe, 0xf, 0x2, 0x8, 0x2, 0x8, 0x2, 0x8, 0x0, 0x0, 0x0, 0x0, 	// 91	bracketleft
	0xe, 0x0, 0x1c, 0x0, 0x30, 0x0, 0x60, 0x0, 0xc0, 0x0, 0x80, 0x3, 0x0, 0x7, 0x0, 0x0, 	// 92	backslash
	0x0, 0x0, 0x2, 0x8, 0x2, 0x8, 0x2, 0x8, 0xfe, 0xf, 0xfe, 0xf, 0x0, 0x0, 0x0, 0x0, 	// 93	bracketright
	0x10, 0x0, 0x18, 0x0, 0xc, 0x0, 0x6, 0x0, 0xc, 0x0, 0x18, 0x0, 0x10, 0x0, 0x0, 0x0, 	// 94	asciicircum
	0x0, 0x8, 0x0, 0x8, 0x0, 0x8, 0x0, 0x8, 0x0, 0x8, 0x0, 0x8, 0x0, 0x8, 0x0, 0x0, 	// 95	underscore
	0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x6, 0x0, 0xc, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 96	grave
	0x80, 0x3, 0xd0, 0x7, 0x50, 0x4, 0x50, 0x4, 0x50, 0x2, 0xf0, 0x7, 0xe0, 0x7, 0x0, 0x0, 	// 97	a
	0xfe, 0x7, 0xfe, 0x7, 0x20, 0x2, 0x10, 0x4, 0x10, 0x4, 0xf0, 0x7, 0xe0, 0x3, 0x0, 0x0, 	// 98	b
	0xe0, 0x3, 0xf0, 0x7, 0x30, 0x6, 0x10, 0x4, 0x10, 0x4, 0x30, 0x6, 0x20, 0x2, 0x0, 0x0, 	// 99	c
	0xe0, 0x3, 0xf0, 0x7, 0x10, 0x4, 0x10, 0x4, 0x20, 0x2, 0xfe, 0x7, 0xfe, 0x7, 0x0, 0x0, 	// 100	d
	0xe0, 0x3, 0xf0, 0x7, 0x90, 0x4, 0x90, 0x4, 0x90, 0x4, 0xf0, 0x6, 0xe0, 0x2, 0x0, 0x0, 	// 101	e
	0x40, 0x0, 0xfc, 0x7, 0xfe, 0x7, 0x42, 0x0, 0x42, 0x0, 0x46, 0x0, 0x4, 0x0, 0x0, 0x0, 	// 102	f
	0xe0, 0xa, 0xf0, 0x1f, 0x10, 0x17, 0x10, 0x17, 0xf0, 0x15, 0xf0, 0x1c, 0x10, 0x8, 0x0, 0x0, 	// 103	g
	0xfe, 0x7, 0xfe, 0x7, 0x20, 0x0, 0x10, 0x0, 0x10, 0x0, 0xf0, 0x7, 0xe0, 0x7, 0x0, 0x0, 	// 104	h
	0x0, 0x0, 0x0, 0x0, 0x20, 0x4, 0xec, 0x7, 0xec, 0x7, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 	// 105	i
	0x0, 0xc, 0x0, 0x1c, 0x0, 0x10, 0x0, 0x10, 0x20, 0x10, 0xec, 0x1f, 0xec, 0xf, 0x0, 0x0, 	// 106	j
	0xfe, 0x7, 0xfe, 0x7, 0xc0, 0x0, 0xe0, 0x1, 0x30, 0x3, 0x10, 0x6, 0x0, 0x4, 0x0, 0x0, 	// 107	k
	0x0, 0x0, 0x0, 0x0, 0x2, 0x4, 0xfe, 0x7, 0xfe, 0x7, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 	// 108	l
	0xe0, 0x7, 0xf0, 0x7, 0x30, 0x0, 0xe0, 0x0, 0x30, 0x0, 0xf0, 0x7, 0xe0, 0x7, 0x0, 0x0, 	// 109	m
	0xf0, 0x7, 0xf0, 0x7, 0x20, 0x0, 0x10, 0x0, 0x10, 0x0, 0xf0, 0x7, 0xe0, 0x7, 0x0, 0x0, 	// 110	n
	0xe0, 0x3, 0xf0, 0x7, 0x10, 0x4, 0x10, 0x4, 0x10, 0x4, 0xf0, 0x7, 0xe0, 0x3, 0x0, 0x0, 	// 111	o
	0xf0, 0x1f, 0xf0, 0x1f, 0x20, 0x2, 0x10, 0x4, 0x10, 0x4, 0xf0, 0x7, 0xe0, 0x3, 0x0, 0x0, 	// 112	p
	0xe0, 0x3, 0xf0, 0x7, 0x10, 0x4, 0x10, 0x4, 0x20, 0x2, 0xf0, 0x1f, 0xf0, 0x1f, 0x0, 0x0, 	// 113	q
	0xf0, 0x7, 0xf0, 0x7, 0x20, 0x0, 0x10, 0x0, 0x10, 0x0, 0x30, 0x0, 0x20, 0x0, 0x0, 0x0, 	// 114	r
	0x20, 0x2, 0x70, 0x6, 0xd0, 0x4, 0x90, 0x4, 0x90, 0x5, 0x30, 0x7, 0x20, 0x2, 0x0, 0x0, 	// 115	s
	0x20, 0x0, 0xfe, 0x3, 0xfe, 0x7, 0x20, 0x4, 0x20, 0x4, 0x20, 0x6, 0x0, 0x2, 0x0, 0x0, 	// 116	t
	0xf0, 0x3, 0xf0, 0x7, 0x0, 0x4, 0x0, 0x4, 0x0, 0x2, 0xf0, 0x7, 0xf0, 0x7, 0x0, 0x0, 	// 117	u
	0xf0, 0x0, 0xf0, 0x3, 0x0, 0x7, 0x0, 0x4, 0x0, 0x7, 0xf0, 0x3, 0xf0, 0x0, 0x0, 0x0, 	// 118	v
	0xf0, 0x3, 0xf0, 0x7, 0x0, 0x6, 0x80, 0x3, 0x0, 0x6, 0xf0, 0x7, 0xf0, 0x3, 0x0, 0x0, 	// 119	w
	0x30, 0x6, 0x70, 0x7, 0xc0, 0x1, 0x80, 0x0, 0xc0, 0x1, 0x70, 0x7, 0x30, 0x6, 0x0, 0x0, 	// 120	x
	0xf0, 0x9, 0xf0, 0x1b, 0x0, 0x12, 0x0, 0x12, 0x0, 0x11, 0xf0, 0x1f, 0xf0, 0xf, 0x0, 0x0, 	// 121	y
	0x10, 0x6, 0x10, 0x7, 0x90, 0x5, 0xd0, 0x4, 0x70, 0x4, 0x30, 0x4, 0x10, 0x4, 0x0, 0x0, 	// 122	z
	0x0, 0x0, 0x40, 0x0, 0x5c, 0x7, 0xfe, 0xf, 0xa2, 0x8, 0x2, 0x8, 0x2, 0x8, 0x0, 0x0, 	// 123	braceleft
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfe, 0x7, 0xfe, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 124	bar
	0x0, 0x0, 0x2, 0x8, 0x2, 0x8, 0xa2, 0x8, 0xfe, 0xf, 0x5c, 0x7, 0x40, 0x0, 0x0, 0x0, 	// 125	braceright
	0x18, 0x0, 0xc, 0x0, 0xc, 0x0, 0x1c, 0x0, 0x18, 0x0, 0x18, 0x0, 0xc, 0x0, 0x0, 0x0, 	// 126	asciitilde
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	// 127	
    }
};
