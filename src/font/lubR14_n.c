
// file: font/lubR14.bdf
// font: -B&H-LucidaBright-Medium-R-Normal--14-140-75-75-P-80-ISO10646-1

#include <font.h>

const struct Font font_lubR14_n = {
    .type       = 1,
    .name	= "lubR14_n",
    .height	= 14,
    .width	= 11,
    .lineheight = 14,
    .bytescol	= 2,
    .numcol     = 11,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 9, .ncol = 1, .xadj = -7, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -6, .pos = 3 }, // 34 [6]
	{ .l0 = 0, .r0 = 2, .ncol = 9, .xadj = -2, .pos = 6 }, // 35 [16]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -2, .pos = 27 }, // 36 [9]
	{ .l0 = 0, .r0 = 0, .ncol = 11, .xadj = -2, .pos = 40 }, // 37 [20]
	{ .l0 = 0, .r0 = 1, .ncol = 10, .xadj = -1, .pos = 68 }, // 38 [18]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -8, .pos = 93 }, // 39 [6]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 97 }, // 40 [6]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 103 }, // 41 [6]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -4, .pos = 109 }, // 42 [9]
	{ .l0 = 0, .r0 = 2, .ncol = 9, .xadj = -2, .pos = 115 }, // 43 [16]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -7, .pos = 126 }, // 44 [4]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -6, .pos = 130 }, // 45 [6]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -7, .pos = 134 }, // 46 [4]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 137 }, // 47 [13]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 145 }, // 48 [13]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -2, .pos = 158 }, // 49 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -2, .pos = 167 }, // 50 [11]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -2, .pos = 184 }, // 51 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 201 }, // 52 [13]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -2, .pos = 215 }, // 53 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 229 }, // 54 [13]
	{ .l0 = 2, .r0 = 3, .ncol = 6, .xadj = -2, .pos = 248 }, // 55 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 260 }, // 56 [13]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 280 }, // 57 [13]
	{ .l0 = 1, .r0 = 9, .ncol = 1, .xadj = -7, .pos = 299 }, // 58 [2]
	{ .l0 = 1, .r0 = 9, .ncol = 1, .xadj = -7, .pos = 302 }, // 59 [2]
	{ .l0 = 0, .r0 = 3, .ncol = 8, .xadj = -2, .pos = 305 }, // 60 [14]
	{ .l0 = 0, .r0 = 3, .ncol = 8, .xadj = -2, .pos = 319 }, // 61 [14]
	{ .l0 = 0, .r0 = 3, .ncol = 8, .xadj = -2, .pos = 336 }, // 62 [14]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -4, .pos = 350 }, // 63 [9]
    },
    .data       = {
	0xf, 0x11, 0x28,	// 33
	0xb, 0xcb, 0x80,	// 34
	0x39, 0x51, 0x11, 0x11, 0x39, 0xc, 0x34, 0x9, 0x3a, 0x9, 0x11, 0xa, 0x39, 0xc, 0x34, 0x9, 0x39, 0x11, 0x11, 0x51, 0x58,	// 35
	0x13, 0x1b, 0x21, 0x19, 0x21, 0x1f, 0x6, 0x11, 0x21, 0x19, 0x23, 0x1b, 0x30,	// 36
	0x13, 0x29, 0x21, 0x19, 0x1a, 0x21, 0x19, 0x12, 0x29, 0x19, 0xa, 0x3b, 0xa, 0x5a, 0x5a, 0xb, 0x3a, 0x9, 0x19, 0x2a, 0x11, 0x19, 0x22, 0x19, 0x19, 0x21, 0x2b, 0x50,	// 37
	0x34, 0x49, 0x1a, 0x2c, 0x21, 0x21, 0x12, 0x21, 0x21, 0x1a, 0x19, 0x21, 0x19, 0x9, 0x11, 0x2b, 0x19, 0x9, 0x49, 0x12, 0x4b, 0x9, 0x49, 0x19, 0x38,	// 38
	0xa, 0x63, 0x5a, 0x88,	// 39
	0x27, 0x2a, 0x3a, 0x11, 0x59, 0x30,	// 40
	0x9, 0x52, 0x12, 0x39, 0x37, 0x48,	// 41
	0x11, 0x73, 0x4a, 0x73, 0x51, 0x68,	// 42
	0x39, 0x69, 0x69, 0x69, 0x4f, 0x1, 0x51, 0x69, 0x69, 0x69, 0x40,	// 43
	0x4a, 0x11, 0x4c, 0x28,	// 44
	0x31, 0x69, 0x69, 0x68,	// 45
	0x51, 0x69, 0x38,	// 46
	0x69, 0x5a, 0x4b, 0x4b, 0x4b, 0x4a, 0x59, 0x90,	// 47
	0x1e, 0x39, 0x31, 0x29, 0x41, 0x21, 0x41, 0x21, 0x41, 0x29, 0x31, 0x3e, 0x58,	// 48
	0x9, 0x41, 0x21, 0x41, 0x27, 0x3, 0x69, 0x69, 0x28,	// 49
	0x12, 0x2a, 0x21, 0x31, 0x9, 0x21, 0x29, 0x11, 0x21, 0x21, 0x19, 0x22, 0x12, 0x19, 0x2c, 0x21, 0x38,	// 50
	0xb, 0x23, 0x21, 0x19, 0x21, 0x21, 0x19, 0x21, 0x21, 0x19, 0x21, 0x21, 0x1a, 0x12, 0x2b, 0xc, 0x40,	// 51
	0x32, 0x5b, 0x51, 0x11, 0x49, 0x19, 0x3a, 0x21, 0x11, 0x27, 0x3, 0x51, 0x11, 0x48,	// 52
	0xc, 0x1b, 0x21, 0x11, 0x29, 0x21, 0x11, 0x29, 0x21, 0x19, 0x1a, 0x21, 0x23, 0x38,	// 53
	0x1e, 0x3a, 0x11, 0x11, 0x29, 0x19, 0x21, 0x21, 0x19, 0x21, 0x21, 0x19, 0x21, 0x21, 0x19, 0x1a, 0x23, 0x14, 0x50,	// 54
	0x9, 0x3a, 0x21, 0x2b, 0x29, 0x22, 0x39, 0x12, 0x49, 0x9, 0x5a, 0x78,	// 55
	0x13, 0xc, 0x2a, 0xa, 0x1a, 0x21, 0x19, 0x21, 0x21, 0x19, 0x21, 0x21, 0x1a, 0x19, 0x22, 0x12, 0x12, 0x2b, 0x13, 0x50,	// 56
	0x14, 0x13, 0x22, 0x19, 0x19, 0x21, 0x21, 0x19, 0x21, 0x21, 0x19, 0x21, 0x21, 0x19, 0x29, 0x11, 0x12, 0x3d, 0x60,	// 57
	0x21, 0x29, 0x28,	// 58
	0x21, 0x2c, 0x10,	// 59
	0x31, 0x6a, 0x62, 0x59, 0x11, 0x51, 0x11, 0x49, 0x21, 0x41, 0x21, 0x39, 0x31, 0x18,	// 60
	0x29, 0x11, 0x51, 0x11, 0x51, 0x11, 0x51, 0x11, 0x51, 0x11, 0x51, 0x11, 0x51, 0x11, 0x51, 0x11, 0x28,	// 61
	0x19, 0x31, 0x39, 0x21, 0x41, 0x21, 0x49, 0x11, 0x51, 0x11, 0x5a, 0x62, 0x69, 0x30,	// 62
	0xb, 0x59, 0x69, 0x23, 0x9, 0x21, 0x19, 0x53, 0x58,	// 63

    }
};
