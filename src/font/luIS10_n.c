
// file: font/luIS10.bdf
// font: -B&H-Lucida-Medium-I-Normal-Sans-10-100-75-75-P-59-ISO10646-1

#include <font.h>

const struct Font font_luIS10_n = {
    .type       = 1,
    .name	= "luIS10_n",
    .height	= 9,
    .width	= 8,
    .lineheight = 10,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 4, .ncol = 3, .xadj = -5, .pos = 0 }, // 33 [4]
	{ .l0 = 2, .r0 = 3, .ncol = 3, .xadj = -4, .pos = 4 }, // 34 [4]
	{ .l0 = 1, .r0 = 0, .ncol = 7, .xadj = -1, .pos = 7 }, // 35 [8]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 18 }, // 36 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 29 }, // 37 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 42 }, // 38 [7]
	{ .l0 = 2, .r0 = 5, .ncol = 1, .xadj = -6, .pos = 57 }, // 39 [2]
	{ .l0 = 1, .r0 = 3, .ncol = 4, .xadj = -5, .pos = 59 }, // 40 [5]
	{ .l0 = 0, .r0 = 4, .ncol = 4, .xadj = -5, .pos = 65 }, // 41 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 71 }, // 42 [6]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 79 }, // 43 [7]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -5, .pos = 86 }, // 44 [3]
	{ .l0 = 2, .r0 = 4, .ncol = 2, .xadj = -5, .pos = 89 }, // 45 [3]
	{ .l0 = 2, .r0 = 5, .ncol = 1, .xadj = -5, .pos = 92 }, // 46 [2]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 94 }, // 47 [7]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 101 }, // 48 [6]
	{ .l0 = 3, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 110 }, // 49 [4]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 115 }, // 50 [6]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 127 }, // 51 [6]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 137 }, // 52 [6]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 147 }, // 53 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 160 }, // 54 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 173 }, // 55 [7]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 184 }, // 56 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 196 }, // 57 [7]
	{ .l0 = 2, .r0 = 4, .ncol = 2, .xadj = -5, .pos = 209 }, // 58 [3]
	{ .l0 = 1, .r0 = 4, .ncol = 3, .xadj = -5, .pos = 212 }, // 59 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 216 }, // 60 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 225 }, // 61 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 236 }, // 62 [7]
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = -3, .pos = 245 }, // 63 [5]
    },
    .data       = {
	0x32, 0x22, 0x2a, 0x58,	// 33
	0x3, 0x7b, 0x58,	// 34
	0x29, 0x31, 0xb, 0x23, 0x23, 0x12, 0x2a, 0x23, 0x9, 0x31, 0x30,	// 35
	0x39, 0x1a, 0x19, 0x11, 0x17, 0x3, 0x11, 0x11, 0x1a, 0x19, 0x48,	// 36
	0x11, 0x39, 0x9, 0x11, 0x21, 0x11, 0x39, 0x39, 0x11, 0x21, 0x11, 0x9, 0x18,	// 37
	0x2b, 0x19, 0x9, 0x11, 0x11, 0xa, 0x11, 0x11, 0x9, 0xa, 0x1a, 0x19, 0x32, 0x9, 0x18,	// 38
	0x3, 0x68,	// 39
	0x24, 0x1a, 0x21, 0x9, 0x39, 0x60,	// 40
	0x41, 0x39, 0x9, 0x22, 0x1c, 0x40,	// 41
	0x19, 0x31, 0x9, 0x39, 0x39, 0x9, 0x31, 0x50,	// 42
	0x21, 0x41, 0x43, 0x23, 0x41, 0x41, 0x30,	// 43
	0x41, 0x32, 0x38,	// 44
	0x21, 0x41, 0x50,	// 45
	0x32, 0x40,	// 46
	0x3a, 0x31, 0x39, 0x32, 0x31, 0x32, 0x48,	// 47
	0x23, 0x22, 0x19, 0x11, 0x29, 0x11, 0x1a, 0x23, 0x38,	// 48
	0x11, 0x41, 0xc, 0x14, 0x48,	// 49
	0x32, 0x11, 0x19, 0x9, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1a, 0x40,	// 50
	0x39, 0x11, 0x29, 0x11, 0x11, 0x11, 0x11, 0x13, 0x22, 0x40,	// 51
	0x22, 0x31, 0x9, 0x29, 0x11, 0x21, 0x14, 0x13, 0x9, 0x30,	// 52
	0x39, 0x1a, 0x19, 0x11, 0x9, 0x19, 0x11, 0x9, 0x11, 0x19, 0x12, 0x21, 0x48,	// 53
	0x2a, 0x2a, 0x11, 0x19, 0x9, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1a, 0x19, 0x48,	// 54
	0x39, 0x11, 0x21, 0x19, 0x19, 0x21, 0x11, 0x29, 0x9, 0x32, 0x40,	// 55
	0x2a, 0x23, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1a, 0xa, 0x28,	// 56
	0x39, 0x1a, 0x19, 0x11, 0x11, 0x11, 0x11, 0x11, 0x9, 0x19, 0x12, 0x2a, 0x38,	// 57
	0x32, 0x1a, 0x58,	// 58
	0x41, 0x32, 0x1a, 0x50,	// 59
	0x21, 0x41, 0x39, 0x9, 0x31, 0x11, 0x21, 0x41, 0x40,	// 60
	0x29, 0x31, 0x9, 0x31, 0x9, 0x31, 0x9, 0x31, 0x9, 0x31, 0x38,	// 61
	0x31, 0x41, 0x21, 0x11, 0x31, 0x9, 0x39, 0x41, 0x30,	// 62
	0x11, 0x1a, 0x11, 0x11, 0x29, 0x11, 0x32, 0x48,	// 63

    }
};
