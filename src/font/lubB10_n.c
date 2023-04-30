
// file: font/lubB10.bdf
// font: -B&H-LucidaBright-DemiBold-R-Normal--10-100-75-75-P-59-ISO10646-1

#include <font.h>

const struct Font font_lubB10_n = {
    .type       = 1,
    .name	= "lubB10_n",
    .height	= 10,
    .width	= 8,
    .lineheight = 10,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 6, .ncol = 1, .xadj = -5, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 4, .ncol = 3, .xadj = -3, .pos = 3 }, // 34 [4]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 6 }, // 35 [8]
	{ .l0 = 1, .r0 = 3, .ncol = 4, .xadj = -2, .pos = 19 }, // 36 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 29 }, // 37 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 44 }, // 38 [9]
	{ .l0 = 0, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 59 }, // 39 [4]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -5, .pos = 63 }, // 40 [3]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -5, .pos = 68 }, // 41 [3]
	{ .l0 = 0, .r0 = 4, .ncol = 4, .xadj = -4, .pos = 73 }, // 42 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = -2, .pos = 78 }, // 43 [9]
	{ .l0 = 0, .r0 = 6, .ncol = 2, .xadj = -5, .pos = 86 }, // 44 [3]
	{ .l0 = 0, .r0 = 6, .ncol = 2, .xadj = -5, .pos = 90 }, // 45 [3]
	{ .l0 = 0, .r0 = 6, .ncol = 2, .xadj = -5, .pos = 93 }, // 46 [3]
	{ .l0 = 0, .r0 = 3, .ncol = 5, .xadj = -3, .pos = 96 }, // 47 [7]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 102 }, // 48 [8]
	{ .l0 = 2, .r0 = 3, .ncol = 3, .xadj = -2, .pos = 113 }, // 49 [4]
	{ .l0 = 1, .r0 = 3, .ncol = 4, .xadj = -2, .pos = 119 }, // 50 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 4, .xadj = -2, .pos = 130 }, // 51 [5]
	{ .l0 = 0, .r0 = 3, .ncol = 5, .xadj = -2, .pos = 141 }, // 52 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 4, .xadj = -2, .pos = 152 }, // 53 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -2, .pos = 163 }, // 54 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -2, .pos = 176 }, // 55 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -2, .pos = 186 }, // 56 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -2, .pos = 200 }, // 57 [7]
	{ .l0 = 1, .r0 = 6, .ncol = 1, .xadj = -5, .pos = 213 }, // 58 [2]
	{ .l0 = 1, .r0 = 6, .ncol = 1, .xadj = -5, .pos = 216 }, // 59 [2]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 219 }, // 60 [8]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 230 }, // 61 [8]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 243 }, // 62 [8]
	{ .l0 = 1, .r0 = 3, .ncol = 4, .xadj = -3, .pos = 254 }, // 63 [5]
    },
    .data       = {
	0x6, 0x9, 0x40,	// 33
	0x4, 0x84, 0x40,	// 34
	0x11, 0x11, 0x31, 0xc, 0x14, 0x9, 0x31, 0xc, 0x14, 0x9, 0x31, 0x11, 0x40,	// 35
	0xa, 0x1a, 0x11, 0x11, 0x19, 0x17, 0x2, 0xa, 0x14, 0x10,	// 36
	0xa, 0x21, 0x11, 0x11, 0xa, 0x22, 0xa, 0x32, 0xa, 0x22, 0x9, 0x11, 0x11, 0x22, 0x38,	// 37
	0x1c, 0x22, 0x1a, 0x11, 0xa, 0x19, 0x11, 0xc, 0x9, 0x1a, 0x12, 0x35, 0x29, 0x19, 0x20,	// 38
	0x2, 0x44, 0x32, 0x50,	// 39
	0xf, 0x1, 0x9, 0x41, 0x20,	// 40
	0x1, 0x41, 0xf, 0x1, 0x28,	// 41
	0xa, 0x3b, 0x3b, 0x42, 0x38,	// 42
	0x21, 0x49, 0x49, 0x37, 0x31, 0x49, 0x49, 0x38,	// 43
	0x32, 0x9, 0x34, 0x20,	// 44
	0x29, 0x49, 0x40,	// 45
	0x39, 0x49, 0x30,	// 46
	0x42, 0x33, 0x2a, 0x2b, 0x32, 0x70,	// 47
	0x14, 0x22, 0x22, 0x11, 0x31, 0x11, 0x31, 0x12, 0x22, 0x24, 0x40,	// 48
	0x1, 0x31, 0x17, 0x1, 0x49, 0x20,	// 49
	0x2, 0x22, 0x11, 0x21, 0x9, 0x11, 0x19, 0x11, 0x1b, 0x19, 0x10,	// 50
	0x2, 0x22, 0x11, 0x11, 0x19, 0x11, 0x11, 0x19, 0x1a, 0xb, 0x18,	// 51
	0x1a, 0x39, 0x9, 0x2a, 0x11, 0x11, 0x17, 0x1, 0x31, 0x11, 0x40,	// 52
	0x4, 0x12, 0x11, 0x11, 0x19, 0x11, 0x12, 0x11, 0x11, 0x1b, 0x18,	// 53
	0x15, 0x21, 0x9, 0x19, 0x11, 0x11, 0x19, 0x11, 0x11, 0x19, 0x12, 0x13, 0x48,	// 54
	0x1, 0x2a, 0x11, 0x1b, 0x19, 0x12, 0x29, 0x9, 0x3a, 0x70,	// 55
	0xa, 0xb, 0x19, 0x11, 0x19, 0x11, 0x11, 0x19, 0x11, 0x12, 0x11, 0x1a, 0xb, 0x48,	// 56
	0xb, 0x12, 0x11, 0x19, 0x11, 0x11, 0x19, 0x11, 0x12, 0x11, 0x9, 0x25, 0x50,	// 57
	0x19, 0x19, 0x40,	// 58
	0x19, 0x1b, 0x30,	// 59
	0x21, 0x49, 0x41, 0x9, 0x32, 0xa, 0x29, 0x19, 0x21, 0x29, 0x30,	// 60
	0x21, 0x9, 0x39, 0x9, 0x39, 0x9, 0x39, 0x9, 0x39, 0x9, 0x39, 0x9, 0x38,	// 61
	0x9, 0x29, 0x21, 0x19, 0x2a, 0xa, 0x31, 0x9, 0x41, 0x49, 0x48,	// 62
	0x2, 0x41, 0x1a, 0x9, 0x11, 0x11, 0x3b, 0x30,	// 63

    }
};
