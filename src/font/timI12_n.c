
// file: font/timI12.bdf
// font: -Adobe-Times-Medium-I-Normal--12-120-75-75-P-63-ISO10646-1

#include <font.h>

const struct Font font_timI12_n = {
    .type       = 1,
    .name	= "timI12_n",
    .height	= 13,
    .width	= 10,
    .lineheight = 13,
    .bytescol	= 2,
    .numcol     = 10,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 5, .ncol = 3, .xadj = -6, .pos = 0 }, // 33 [5]
	{ .l0 = 2, .r0 = 4, .ncol = 4, .xadj = -5, .pos = 5 }, // 34 [7]
	{ .l0 = 0, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 10 }, // 35 [12]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 21 }, // 36 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 9, .xadj = 0, .pos = 32 }, // 37 [15]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = -1, .pos = 55 }, // 38 [13]
	{ .l0 = 2, .r0 = 6, .ncol = 2, .xadj = -7, .pos = 73 }, // 39 [4]
	{ .l0 = 0, .r0 = 6, .ncol = 4, .xadj = -6, .pos = 76 }, // 40 [7]
	{ .l0 = 1, .r0 = 5, .ncol = 4, .xadj = -6, .pos = 83 }, // 41 [7]
	{ .l0 = 2, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 90 }, // 42 [9]
	{ .l0 = 2, .r0 = 3, .ncol = 5, .xadj = -2, .pos = 98 }, // 43 [9]
	{ .l0 = 0, .r0 = 8, .ncol = 2, .xadj = -7, .pos = 104 }, // 44 [4]
	{ .l0 = 0, .r0 = 6, .ncol = 4, .xadj = -6, .pos = 107 }, // 45 [7]
	{ .l0 = 1, .r0 = 8, .ncol = 1, .xadj = -7, .pos = 112 }, // 46 [2]
	{ .l0 = 1, .r0 = 5, .ncol = 4, .xadj = -6, .pos = 114 }, // 47 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 119 }, // 48 [10]
	{ .l0 = 1, .r0 = 5, .ncol = 4, .xadj = -4, .pos = 130 }, // 49 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 137 }, // 50 [10]
	{ .l0 = 0, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 153 }, // 51 [10]
	{ .l0 = 0, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 166 }, // 52 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 178 }, // 53 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 191 }, // 54 [10]
	{ .l0 = 2, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 204 }, // 55 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 214 }, // 56 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 229 }, // 57 [10]
	{ .l0 = 2, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 242 }, // 58 [4]
	{ .l0 = 1, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 245 }, // 59 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -2, .pos = 249 }, // 60 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -2, .pos = 261 }, // 61 [10]
	{ .l0 = 2, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 274 }, // 62 [10]
	{ .l0 = 3, .r0 = 3, .ncol = 4, .xadj = -4, .pos = 286 }, // 63 [7]
    },
    .data       = {
	0x32, 0x9, 0x33, 0x42, 0x58,	// 33
	0x11, 0x59, 0x69, 0x59, 0x78,	// 34
	0x39, 0x49, 0x13, 0x3c, 0x34, 0x13, 0x3c, 0x34, 0x11, 0x49, 0x68,	// 35
	0x3a, 0x33, 0x22, 0x19, 0x1d, 0x25, 0x19, 0x1a, 0x23, 0x31, 0x60,	// 36
	0x1a, 0x52, 0x9, 0x42, 0x11, 0x19, 0x21, 0x11, 0x12, 0x32, 0x11, 0x41, 0xa, 0xa, 0x32, 0x12, 0x9, 0x22, 0x12, 0x11, 0x41, 0x11, 0x38,	// 37
	0x3a, 0x51, 0x11, 0x41, 0x19, 0x2d, 0x11, 0x21, 0x11, 0x12, 0x2b, 0x19, 0x9, 0x42, 0x11, 0x41, 0x11, 0x20,	// 38
	0x11, 0x59, 0x88,	// 39
	0x2d, 0x32, 0x2a, 0x19, 0x49, 0x9, 0x78,	// 40
	0x61, 0x9, 0x49, 0x1a, 0x2a, 0x35, 0x40,	// 41
	0x11, 0x9, 0x59, 0x55, 0x51, 0x59, 0x9, 0x78,	// 42
	0x31, 0x61, 0x55, 0x51, 0x61, 0x68,	// 43
	0x59, 0x52, 0x40,	// 44
	0x31, 0x61, 0x61, 0x61, 0x50,	// 45
	0x49, 0x30,	// 46
	0x42, 0x4a, 0x43, 0x42, 0x70,	// 47
	0x2c, 0x3a, 0x21, 0x29, 0x31, 0x21, 0x31, 0x29, 0x22, 0x3c, 0x48,	// 48
	0x49, 0x53, 0x21, 0x13, 0x11, 0x23, 0x68,	// 49
	0x42, 0x29, 0x21, 0x9, 0x21, 0x21, 0x11, 0x21, 0x19, 0x19, 0x21, 0x11, 0x21, 0x2a, 0x21, 0x30,	// 50
	0x41, 0x69, 0x29, 0x11, 0x19, 0x21, 0x19, 0x11, 0x29, 0x11, 0xa, 0x3a, 0x58,	// 51
	0x32, 0x51, 0x9, 0x49, 0x11, 0x41, 0x1b, 0x29, 0x13, 0x34, 0x11, 0x38,	// 52
	0x42, 0x32, 0x21, 0x22, 0x9, 0x21, 0x21, 0x11, 0x19, 0x29, 0x1b, 0x31, 0x68,	// 53
	0x2c, 0x3a, 0x21, 0x29, 0x9, 0x21, 0x29, 0x9, 0x19, 0x29, 0x1b, 0x31, 0x68,	// 54
	0x11, 0x2a, 0x21, 0x22, 0x31, 0x12, 0x41, 0x9, 0x52, 0x88,	// 55
	0x33, 0x32, 0x9, 0x19, 0x21, 0x11, 0x21, 0x21, 0x12, 0x11, 0x29, 0x9, 0x12, 0x39, 0x60,	// 56
	0x49, 0x33, 0x19, 0x29, 0x19, 0x9, 0x29, 0x21, 0x9, 0x29, 0x22, 0x3c, 0x48,	// 57
	0x49, 0x39, 0x70,	// 58
	0x59, 0x52, 0x31, 0x48,	// 59
	0x31, 0x59, 0x9, 0x51, 0x9, 0x49, 0x19, 0x41, 0x19, 0x39, 0x29, 0x28,	// 60
	0x29, 0x9, 0x51, 0x9, 0x51, 0x9, 0x51, 0x9, 0x51, 0x9, 0x51, 0x9, 0x38,	// 61
	0x19, 0x29, 0x39, 0x19, 0x41, 0x19, 0x49, 0x9, 0x51, 0x9, 0x59, 0x40,	// 62
	0x12, 0x12, 0x9, 0x21, 0x19, 0x41, 0x11, 0x52, 0x68,	// 63

    }
};
