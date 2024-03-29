
// file: font/timR14.bdf
// font: -Adobe-Times-Medium-R-Normal--14-140-75-75-P-74-ISO10646-1

#include <font.h>

const struct Font font_timR14_n = {
    .type       = 1,
    .name	= "timR14_n",
    .height	= 14,
    .width	= 12,
    .lineheight = 14,
    .bytescol	= 2,
    .numcol     = 12,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 3, .r0 = 8, .ncol = 1, .xadj = -7, .pos = 0 }, // 33 [2]
	{ .l0 = 2, .r0 = 7, .ncol = 3, .xadj = -6, .pos = 3 }, // 34 [6]
	{ .l0 = 1, .r0 = 4, .ncol = 7, .xadj = -5, .pos = 6 }, // 35 [13]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 17 }, // 36 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 9, .xadj = 0, .pos = 30 }, // 37 [16]
	{ .l0 = 2, .r0 = 0, .ncol = 10, .xadj = -1, .pos = 53 }, // 38 [18]
	{ .l0 = 2, .r0 = 9, .ncol = 1, .xadj = -9, .pos = 77 }, // 39 [2]
	{ .l0 = 2, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 79 }, // 40 [6]
	{ .l0 = 2, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 85 }, // 41 [6]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 91 }, // 42 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 99 }, // 43 [13]
	{ .l0 = 1, .r0 = 9, .ncol = 2, .xadj = -9, .pos = 107 }, // 44 [4]
	{ .l0 = 1, .r0 = 7, .ncol = 4, .xadj = -7, .pos = 110 }, // 45 [7]
	{ .l0 = 2, .r0 = 9, .ncol = 1, .xadj = -9, .pos = 115 }, // 46 [2]
	{ .l0 = 0, .r0 = 7, .ncol = 5, .xadj = -8, .pos = 117 }, // 47 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 123 }, // 48 [11]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 136 }, // 49 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 145 }, // 50 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 159 }, // 51 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 176 }, // 52 [11]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 187 }, // 53 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 201 }, // 54 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 216 }, // 55 [11]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 227 }, // 56 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 241 }, // 57 [11]
	{ .l0 = 2, .r0 = 9, .ncol = 1, .xadj = -8, .pos = 256 }, // 58 [2]
	{ .l0 = 1, .r0 = 9, .ncol = 2, .xadj = -8, .pos = 259 }, // 59 [4]
	{ .l0 = 1, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 263 }, // 60 [13]
	{ .l0 = 1, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 276 }, // 61 [13]
	{ .l0 = 1, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 291 }, // 62 [13]
	{ .l0 = 1, .r0 = 6, .ncol = 5, .xadj = -6, .pos = 304 }, // 63 [9]
    },
    .data       = {
	0xf, 0xa, 0x28,	// 33
	0xb, 0xcb, 0x80,	// 34
	0x39, 0x49, 0x1c, 0x35, 0x3b, 0x1c, 0x35, 0x3b, 0x19, 0x49, 0x80,	// 35
	0x13, 0x22, 0x21, 0x19, 0x21, 0x1f, 0x5, 0x19, 0x19, 0x21, 0x22, 0x1c, 0x30,	// 36
	0x13, 0x52, 0x11, 0x1a, 0x21, 0x19, 0x12, 0x2c, 0x11, 0x41, 0x12, 0x49, 0xa, 0xb, 0x32, 0x12, 0x11, 0x22, 0x19, 0x19, 0x21, 0x2b, 0x30,	// 37
	0x3b, 0x52, 0xa, 0x2b, 0x9, 0x19, 0x21, 0x13, 0x19, 0x21, 0x11, 0xa, 0x9, 0x32, 0x22, 0x49, 0x9, 0xa, 0x42, 0x19, 0x41, 0x21, 0x61, 0x40,	// 38
	0xb, 0x60,	// 39
	0x2d, 0x3a, 0x2a, 0x1a, 0x4a, 0x30,	// 40
	0xa, 0x4a, 0x1a, 0x2a, 0x3d, 0x50,	// 41
	0x11, 0x11, 0x5a, 0x56, 0x52, 0x59, 0x11, 0x50,	// 42
	0x39, 0x69, 0x69, 0x57, 0x51, 0x69, 0x69, 0x60,	// 43
	0x61, 0x53, 0x30,	// 44
	0x39, 0x69, 0x69, 0x69, 0x30,	// 45
	0x4a, 0x28,	// 46
	0x5a, 0x52, 0x4b, 0x43, 0x4a, 0x68,	// 47
	0x17, 0x1, 0x2a, 0x32, 0x21, 0x41, 0x21, 0x41, 0x22, 0x32, 0x2f, 0x1, 0x40,	// 48
	0x11, 0x39, 0x29, 0x39, 0x27, 0x3, 0x69, 0x69, 0x28,	// 49
	0x12, 0x2a, 0x22, 0x2b, 0x21, 0x29, 0x11, 0x22, 0x12, 0x19, 0x2c, 0x21, 0x62, 0x38,	// 50
	0x12, 0x29, 0x2a, 0x32, 0x21, 0x19, 0x21, 0x21, 0x19, 0x21, 0x22, 0x9, 0x9, 0x12, 0x2a, 0x1b, 0x40,	// 51
	0x3a, 0x52, 0x9, 0x4a, 0x11, 0x3a, 0x21, 0x37, 0x3, 0x59, 0x48,	// 52
	0x1b, 0x1a, 0x22, 0x9, 0x29, 0x22, 0xa, 0x21, 0x22, 0x12, 0x11, 0x29, 0x23, 0x38,	// 53
	0x34, 0x43, 0x12, 0x31, 0x9, 0x21, 0x29, 0x11, 0x21, 0x22, 0x12, 0x12, 0x21, 0x24, 0x40,	// 54
	0xa, 0x61, 0x3a, 0x21, 0x2a, 0x31, 0x1a, 0x41, 0xa, 0x52, 0x78,	// 55
	0x13, 0xc, 0x2a, 0xa, 0x1a, 0x21, 0x19, 0x21, 0x22, 0x12, 0x12, 0x2b, 0xc, 0x30,	// 56
	0x14, 0x21, 0x22, 0x12, 0x12, 0x21, 0x21, 0x11, 0x29, 0x21, 0x9, 0x32, 0x13, 0x44, 0x60,	// 57
	0x22, 0x1a, 0x28,	// 58
	0x61, 0x2a, 0x1b, 0x30,	// 59
	0x39, 0x63, 0x59, 0x9, 0x51, 0x19, 0x49, 0x19, 0x41, 0x29, 0x39, 0x29, 0x48,	// 60
	0x31, 0x9, 0x59, 0x9, 0x59, 0x9, 0x59, 0x9, 0x59, 0x9, 0x59, 0x9, 0x59, 0x9, 0x58,	// 61
	0x21, 0x29, 0x39, 0x29, 0x41, 0x19, 0x49, 0x19, 0x51, 0x9, 0x5b, 0x61, 0x60,	// 62
	0x12, 0x59, 0x69, 0x22, 0xa, 0x21, 0x19, 0x53, 0x58,	// 63

    }
};
