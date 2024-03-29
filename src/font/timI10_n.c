
// file: font/timI10.bdf
// font: -Adobe-Times-Medium-I-Normal--10-100-75-75-P-52-ISO10646-1

#include <font.h>

const struct Font font_timI10_n = {
    .type       = 1,
    .name	= "timI10_n",
    .height	= 10,
    .width	= 9,
    .lineheight = 10,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = -6, .pos = 0 }, // 33 [4]
	{ .l0 = 2, .r0 = 4, .ncol = 3, .xadj = -5, .pos = 5 }, // 34 [4]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = -4, .pos = 8 }, // 35 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 19 }, // 36 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 29 }, // 37 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 44 }, // 38 [9]
	{ .l0 = 3, .r0 = 5, .ncol = 1, .xadj = -6, .pos = 58 }, // 39 [2]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -6, .pos = 60 }, // 40 [5]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -5, .pos = 66 }, // 41 [5]
	{ .l0 = 3, .r0 = 3, .ncol = 3, .xadj = -4, .pos = 72 }, // 42 [4]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -2, .pos = 78 }, // 43 [7]
	{ .l0 = 0, .r0 = 7, .ncol = 2, .xadj = -6, .pos = 84 }, // 44 [3]
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 87 }, // 45 [4]
	{ .l0 = 1, .r0 = 7, .ncol = 1, .xadj = -6, .pos = 91 }, // 46 [2]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -5, .pos = 93 }, // 47 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 98 }, // 48 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -4, .pos = 107 }, // 49 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 114 }, // 50 [7]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 126 }, // 51 [8]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 139 }, // 52 [7]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 149 }, // 53 [8]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 160 }, // 54 [7]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -4, .pos = 170 }, // 55 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 178 }, // 56 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 190 }, // 57 [7]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 200 }, // 58 [3]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 203 }, // 59 [4]
	{ .l0 = 2, .r0 = 4, .ncol = 3, .xadj = -4, .pos = 207 }, // 60 [4]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -2, .pos = 213 }, // 61 [7]
	{ .l0 = 2, .r0 = 4, .ncol = 3, .xadj = -4, .pos = 224 }, // 62 [4]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -4, .pos = 230 }, // 63 [5]
    },
    .data       = {
	0x29, 0x9, 0x2a, 0x32, 0x48,	// 33
	0x3, 0x8b, 0x48,	// 34
	0x29, 0x39, 0xb, 0x2b, 0x2b, 0xb, 0x2b, 0x2b, 0x9, 0x39, 0x40,	// 35
	0x32, 0x22, 0x1a, 0x11, 0xa, 0x11, 0x12, 0x13, 0x22, 0x68,	// 36
	0x12, 0x39, 0x11, 0xa, 0x1b, 0x9, 0x31, 0x9, 0x3a, 0xa, 0x21, 0x11, 0x11, 0x3a, 0x28,	// 37
	0x2b, 0x31, 0x11, 0x23, 0x11, 0x19, 0x9, 0xa, 0x22, 0x1a, 0x32, 0x9, 0x31, 0x38,	// 38
	0x3, 0x68,	// 39
	0x25, 0x1a, 0x29, 0x9, 0x49, 0x40,	// 40
	0x49, 0x49, 0x9, 0x2a, 0x1d, 0x18,	// 41
	0x9, 0x9, 0x41, 0x41, 0x9, 0x40,	// 42
	0x29, 0x49, 0x3d, 0x39, 0x49, 0x50,	// 43
	0x49, 0x3a, 0x28,	// 44
	0x29, 0x49, 0x49, 0x30,	// 45
	0x39, 0x40,	// 46
	0x32, 0x32, 0x39, 0x3a, 0x38,	// 47
	0x23, 0x2a, 0x19, 0x19, 0x29, 0x19, 0x1a, 0x2b, 0x58,	// 48
	0x39, 0x3b, 0x19, 0xa, 0x11, 0x1a, 0x38,	// 49
	0x39, 0x21, 0x1a, 0x19, 0x19, 0x9, 0x19, 0x11, 0x11, 0x22, 0x11, 0x48,	// 50
	0x31, 0x51, 0x21, 0x9, 0x11, 0x19, 0x11, 0x11, 0x19, 0x9, 0xa, 0x29, 0x58,	// 51
	0x22, 0x39, 0x9, 0x31, 0x13, 0x19, 0xb, 0x2a, 0x11, 0x50,	// 52
	0x31, 0x51, 0x29, 0x19, 0x1a, 0x9, 0x11, 0x19, 0x1a, 0x21, 0x60,	// 53
	0x23, 0x31, 0x19, 0x21, 0x9, 0x11, 0x19, 0x1a, 0x21, 0x70,	// 54
	0xa, 0x1a, 0x19, 0x12, 0x29, 0x9, 0x3a, 0x38,	// 55
	0x2a, 0x29, 0x9, 0x11, 0x19, 0xa, 0x11, 0x19, 0x9, 0xa, 0x29, 0x68,	// 56
	0x39, 0x22, 0x19, 0x19, 0x11, 0x9, 0x21, 0x19, 0x33, 0x58,	// 57
	0x39, 0x29, 0x50,	// 58
	0x49, 0x3a, 0x21, 0x40,	// 59
	0x29, 0x41, 0x9, 0x31, 0x19, 0x20,	// 60
	0x21, 0x9, 0x39, 0x9, 0x39, 0x9, 0x39, 0x9, 0x39, 0x9, 0x48,	// 61
	0x19, 0x19, 0x31, 0x9, 0x41, 0x30,	// 62
	0x11, 0x11, 0x9, 0x19, 0x11, 0x31, 0x9, 0x41, 0x38,	// 63

    }
};
