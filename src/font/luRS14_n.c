
// file: font/luRS14.bdf
// font: -B&H-Lucida-Medium-R-Normal-Sans-14-140-75-75-P-81-ISO10646-1

#include <font.h>

const struct Font font_luRS14_n = {
    .type       = 1,
    .name	= "luRS14_n",
    .height	= 13,
    .width	= 10,
    .lineheight = 14,
    .bytescol	= 2,
    .numcol     = 10,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 8, .ncol = 1, .xadj = -7, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 5, .ncol = 4, .xadj = -4, .pos = 3 }, // 34 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = -1, .pos = 7 }, // 35 [13]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 24 }, // 36 [12]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 43 }, // 37 [13]
	{ .l0 = 1, .r0 = 0, .ncol = 9, .xadj = 0, .pos = 64 }, // 38 [15]
	{ .l0 = 1, .r0 = 8, .ncol = 1, .xadj = -7, .pos = 88 }, // 39 [2]
	{ .l0 = 1, .r0 = 5, .ncol = 4, .xadj = -5, .pos = 90 }, // 40 [7]
	{ .l0 = 0, .r0 = 6, .ncol = 4, .xadj = -5, .pos = 98 }, // 41 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 5, .xadj = -3, .pos = 106 }, // 42 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 115 }, // 43 [12]
	{ .l0 = 0, .r0 = 7, .ncol = 3, .xadj = -6, .pos = 123 }, // 44 [5]
	{ .l0 = 1, .r0 = 6, .ncol = 3, .xadj = -5, .pos = 127 }, // 45 [5]
	{ .l0 = 1, .r0 = 8, .ncol = 1, .xadj = -7, .pos = 131 }, // 46 [2]
	{ .l0 = 0, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 133 }, // 47 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 141 }, // 48 [12]
	{ .l0 = 2, .r0 = 5, .ncol = 3, .xadj = -1, .pos = 154 }, // 49 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 159 }, // 50 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 178 }, // 51 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 198 }, // 52 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 211 }, // 53 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 231 }, // 54 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 250 }, // 55 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 262 }, // 56 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 284 }, // 57 [12]
	{ .l0 = 1, .r0 = 8, .ncol = 1, .xadj = -7, .pos = 303 }, // 58 [2]
	{ .l0 = 0, .r0 = 7, .ncol = 3, .xadj = -6, .pos = 306 }, // 59 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -1, .pos = 311 }, // 60 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 322 }, // 61 [12]
	{ .l0 = 2, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 337 }, // 62 [10]
	{ .l0 = 1, .r0 = 4, .ncol = 5, .xadj = -4, .pos = 348 }, // 63 [9]
    },
    .data       = {
	0xf, 0xa, 0x28,	// 33
	0x4, 0xf8, 0x24, 0x68,	// 34
	0x21, 0x11, 0x49, 0x11, 0x37, 0x3, 0x31, 0x11, 0x49, 0x11, 0x37, 0x3, 0x31, 0x11, 0x49, 0x11, 0x28,	// 35
	0x13, 0x21, 0x21, 0x19, 0x21, 0x19, 0x19, 0x21, 0x17, 0x5, 0x11, 0x21, 0x19, 0x19, 0x21, 0x19, 0x21, 0x23, 0x40,	// 36
	0x12, 0x29, 0x21, 0x11, 0x19, 0x29, 0x11, 0x11, 0x3a, 0x11, 0x59, 0x12, 0x39, 0x11, 0x11, 0x29, 0x19, 0x11, 0x21, 0x2a, 0x18,	// 37
	0x3b, 0x2b, 0x9, 0x19, 0x19, 0x19, 0x21, 0x19, 0x19, 0x21, 0x19, 0x1a, 0x19, 0x19, 0x11, 0x11, 0x9, 0x2a, 0x22, 0x43, 0x9, 0x41, 0x21, 0x28,	// 38
	0x4, 0x60,	// 39
	0x1e, 0x2a, 0x32, 0x11, 0x51, 0x9, 0x51, 0x28,	// 40
	0x1, 0x51, 0x9, 0x51, 0x12, 0x32, 0x2e, 0x40,	// 41
	0x11, 0x9, 0x59, 0x52, 0xa, 0x51, 0x59, 0x9, 0x78,	// 42
	0x31, 0x61, 0x61, 0x4f, 0x49, 0x61, 0x61, 0x58,	// 43
	0x61, 0x59, 0x52, 0x18,	// 44
	0x31, 0x61, 0x61, 0x38,	// 45
	0x4a, 0x28,	// 46
	0x59, 0x52, 0x4a, 0x4a, 0x4a, 0x4a, 0x51, 0x88,	// 47
	0x1e, 0x31, 0x31, 0x21, 0x41, 0x19, 0x41, 0x19, 0x41, 0x21, 0x31, 0x36, 0x48,	// 48
	0x11, 0x61, 0x5f, 0x3, 0x18,	// 49
	0x11, 0x39, 0x19, 0x3a, 0x19, 0x31, 0x9, 0x19, 0x29, 0x11, 0x19, 0x21, 0x19, 0x19, 0x19, 0x21, 0x23, 0x29, 0x38,	// 50
	0x11, 0x31, 0x21, 0x41, 0x19, 0x19, 0x21, 0x19, 0x19, 0x21, 0x19, 0x19, 0x21, 0x21, 0x9, 0x9, 0x11, 0x31, 0x1a, 0x48,	// 51
	0x32, 0x51, 0x9, 0x49, 0x11, 0x41, 0x19, 0x39, 0x21, 0x37, 0x3, 0x49, 0x50,	// 52
	0xd, 0x19, 0x21, 0x19, 0x21, 0x19, 0x19, 0x21, 0x19, 0x19, 0x21, 0x19, 0x19, 0x21, 0x19, 0x21, 0x11, 0x21, 0x2a, 0x48,	// 53
	0x1e, 0x31, 0x11, 0x19, 0x21, 0x11, 0x29, 0x19, 0x11, 0x29, 0x19, 0x11, 0x29, 0x19, 0x19, 0x19, 0x29, 0x1b, 0x48,	// 54
	0x9, 0x61, 0x61, 0x33, 0x19, 0x22, 0x31, 0x19, 0x41, 0x11, 0x4b, 0x70,	// 55
	0x19, 0x1a, 0x31, 0x9, 0x9, 0x11, 0x21, 0x19, 0x21, 0x19, 0x19, 0x21, 0x19, 0x19, 0x21, 0x21, 0x9, 0x9, 0x11, 0x31, 0x1a, 0x48,	// 56
	0x1b, 0x19, 0x29, 0x19, 0x19, 0x19, 0x29, 0x11, 0x19, 0x29, 0x11, 0x19, 0x29, 0x11, 0x21, 0x19, 0x11, 0x36, 0x48,	// 57
	0x22, 0x1a, 0x28,	// 58
	0x61, 0x59, 0x2a, 0x1a, 0x18,	// 59
	0x31, 0x61, 0x59, 0x9, 0x49, 0x19, 0x41, 0x19, 0x39, 0x29, 0x28,	// 60
	0x29, 0x9, 0x51, 0x9, 0x51, 0x9, 0x51, 0x9, 0x51, 0x9, 0x51, 0x9, 0x51, 0x9, 0x50,	// 61
	0x19, 0x29, 0x39, 0x19, 0x41, 0x19, 0x49, 0x9, 0x59, 0x61, 0x40,	// 62
	0x11, 0x59, 0x61, 0x22, 0xa, 0x19, 0x19, 0x4b, 0x78,	// 63

    }
};
