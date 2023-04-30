
// file: font/luIS12.bdf
// font: -B&H-Lucida-Medium-I-Normal-Sans-12-120-75-75-P-71-ISO10646-1

#include <font.h>

const struct Font font_luIS12_n = {
    .type       = 1,
    .name	= "luIS12_n",
    .height	= 11,
    .width	= 9,
    .lineheight = 12,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = -6, .pos = 0 }, // 33 [5]
	{ .l0 = 2, .r0 = 4, .ncol = 3, .xadj = -4, .pos = 4 }, // 34 [5]
	{ .l0 = 1, .r0 = 0, .ncol = 8, .xadj = -1, .pos = 7 }, // 35 [11]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 20 }, // 36 [9]
	{ .l0 = 2, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 31 }, // 37 [10]
	{ .l0 = 2, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 50 }, // 38 [10]
	{ .l0 = 2, .r0 = 6, .ncol = 1, .xadj = -6, .pos = 66 }, // 39 [2]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -5, .pos = 68 }, // 40 [6]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -5, .pos = 74 }, // 41 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 80 }, // 42 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 87 }, // 43 [9]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 94 }, // 44 [3]
	{ .l0 = 2, .r0 = 4, .ncol = 3, .xadj = -5, .pos = 97 }, // 45 [5]
	{ .l0 = 2, .r0 = 6, .ncol = 1, .xadj = -6, .pos = 101 }, // 46 [2]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -3, .pos = 103 }, // 47 [10]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 111 }, // 48 [9]
	{ .l0 = 4, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 122 }, // 49 [5]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 127 }, // 50 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 142 }, // 51 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 157 }, // 52 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 167 }, // 53 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 180 }, // 54 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 193 }, // 55 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 204 }, // 56 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 219 }, // 57 [9]
	{ .l0 = 2, .r0 = 5, .ncol = 2, .xadj = -6, .pos = 232 }, // 58 [3]
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = -6, .pos = 235 }, // 59 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 239 }, // 60 [10]
	{ .l0 = 2, .r0 = 0, .ncol = 7, .xadj = -1, .pos = 252 }, // 61 [10]
	{ .l0 = 2, .r0 = 0, .ncol = 7, .xadj = -1, .pos = 265 }, // 62 [10]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 278 }, // 63 [7]
    },
    .data       = {
	0x42, 0x2b, 0x2b, 0x70,	// 33
	0x3, 0x9b, 0x78,	// 34
	0x39, 0x31, 0x1b, 0x25, 0x23, 0x19, 0x31, 0x1b, 0x25, 0x23, 0x19, 0x31, 0x38,	// 35
	0x41, 0x23, 0x21, 0x11, 0x1f, 0x5, 0x19, 0x11, 0x23, 0x21, 0x70,	// 36
	0x12, 0x29, 0x11, 0x11, 0x19, 0x19, 0x11, 0x11, 0x2a, 0xa, 0x42, 0xa, 0x29, 0x11, 0x11, 0x19, 0x19, 0x11, 0x20,	// 37
	0x33, 0x39, 0x19, 0x1c, 0x19, 0x11, 0x1a, 0x11, 0x11, 0x11, 0x12, 0x22, 0x21, 0x42, 0x9, 0x20,	// 38
	0x3, 0x68,	// 39
	0x26, 0x1a, 0x31, 0x9, 0x49, 0x70,	// 40
	0x51, 0x49, 0x9, 0x32, 0x1e, 0x40,	// 41
	0x21, 0x41, 0x5b, 0x33, 0x59, 0x41, 0x70,	// 42
	0x29, 0x51, 0x54, 0x24, 0x51, 0x51, 0x58,	// 43
	0x51, 0x42, 0x18,	// 44
	0x29, 0x51, 0x51, 0x60,	// 45
	0x42, 0x30,	// 46
	0x4a, 0x41, 0x42, 0x41, 0x42, 0x41, 0x42, 0x60,	// 47
	0x2c, 0x23, 0x21, 0x11, 0x39, 0x11, 0x39, 0x11, 0x23, 0x24, 0x58,	// 48
	0x11, 0x51, 0x15, 0x15, 0x60,	// 49
	0x42, 0x19, 0x21, 0x9, 0x11, 0x21, 0x11, 0x11, 0x21, 0x11, 0x11, 0x19, 0x19, 0x1b, 0x60,	// 50
	0x41, 0x21, 0x11, 0x19, 0x11, 0x19, 0x19, 0x11, 0x19, 0x19, 0x11, 0x11, 0xb, 0x22, 0x68,	// 51
	0x2a, 0x41, 0x9, 0x32, 0x11, 0x29, 0x24, 0x16, 0x51, 0x50,	// 52
	0x41, 0x2b, 0x19, 0x12, 0x11, 0x19, 0x11, 0x19, 0x11, 0x19, 0x22, 0x21, 0x78,	// 53
	0x33, 0x2b, 0x19, 0x19, 0x11, 0x19, 0x11, 0x19, 0x19, 0x11, 0x23, 0x21, 0x70,	// 54
	0x42, 0x11, 0x22, 0x21, 0x19, 0x31, 0x11, 0x39, 0x9, 0x42, 0x70,	// 55
	0x33, 0x22, 0x9, 0x19, 0x11, 0x11, 0x21, 0x11, 0x19, 0x11, 0x19, 0x11, 0xa, 0x2a, 0x68,	// 56
	0x41, 0x23, 0x21, 0x11, 0x19, 0x19, 0x11, 0x19, 0x11, 0x19, 0x1b, 0x2b, 0x60,	// 57
	0x42, 0x22, 0x40,	// 58
	0x51, 0x42, 0x22, 0x68,	// 59
	0x31, 0x49, 0x9, 0x41, 0x11, 0x31, 0x19, 0x31, 0x21, 0x21, 0x29, 0x21, 0x50,	// 60
	0x31, 0x41, 0x9, 0x41, 0x9, 0x41, 0x9, 0x41, 0x9, 0x41, 0x9, 0x41, 0x48,	// 61
	0x49, 0x21, 0x29, 0x21, 0x21, 0x31, 0x19, 0x31, 0x11, 0x41, 0x9, 0x49, 0x38,	// 62
	0x42, 0x19, 0x12, 0x29, 0x11, 0x39, 0x11, 0x42, 0x40,	// 63

    }
};
