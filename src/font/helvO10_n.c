
// file: font/helvO10.bdf
// font: -Adobe-Helvetica-Medium-O-Normal--10-100-75-75-P-57-ISO10646-1

#include <font.h>

const struct Font font_helvO10_n = {
    .type       = 1,
    .name	= "helvO10_n",
    .height	= 10,
    .width	= 9,
    .lineheight = 10,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 4, .ncol = 3, .xadj = -5, .pos = 0 }, // 33 [4]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -5, .pos = 4 }, // 34 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -2, .pos = 9 }, // 35 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 20 }, // 36 [8]
	{ .l0 = 2, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 31 }, // 37 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 51 }, // 38 [9]
	{ .l0 = 2, .r0 = 6, .ncol = 1, .xadj = -7, .pos = 67 }, // 39 [2]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -5, .pos = 69 }, // 40 [5]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -5, .pos = 75 }, // 41 [5]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -5, .pos = 81 }, // 42 [5]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -3, .pos = 86 }, // 43 [5]
	{ .l0 = 0, .r0 = 7, .ncol = 2, .xadj = -6, .pos = 91 }, // 44 [3]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -3, .pos = 94 }, // 45 [5]
	{ .l0 = 1, .r0 = 7, .ncol = 1, .xadj = -6, .pos = 99 }, // 46 [2]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -6, .pos = 101 }, // 47 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 106 }, // 48 [8]
	{ .l0 = 3, .r0 = 3, .ncol = 3, .xadj = -3, .pos = 117 }, // 49 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 122 }, // 50 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 137 }, // 51 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 150 }, // 52 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 161 }, // 53 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 176 }, // 54 [8]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 189 }, // 55 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 199 }, // 56 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 212 }, // 57 [8]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 225 }, // 58 [3]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 228 }, // 59 [4]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -3, .pos = 232 }, // 60 [5]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = -2, .pos = 239 }, // 61 [7]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -3, .pos = 248 }, // 62 [5]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 255 }, // 63 [7]
    },
    .data       = {
	0x39, 0x2b, 0x23, 0x48,	// 33
	0x11, 0x3a, 0x51, 0x3a, 0x40,	// 34
	0x29, 0x39, 0xb, 0x2b, 0x2b, 0xb, 0x2b, 0x2b, 0x9, 0x39, 0x40,	// 35
	0x31, 0x2a, 0x1a, 0x11, 0x14, 0x1c, 0x11, 0x12, 0x13, 0x29, 0x58,	// 36
	0xb, 0x19, 0x11, 0x11, 0x11, 0x19, 0x9, 0x11, 0x22, 0xa, 0xa, 0x21, 0x11, 0x9, 0x19, 0x11, 0x11, 0x11, 0x1b, 0x28,	// 37
	0x2a, 0x39, 0x11, 0x1b, 0x19, 0x11, 0x12, 0x11, 0x11, 0x11, 0xa, 0x22, 0x11, 0x9, 0x31, 0x38,	// 38
	0x3, 0x68,	// 39
	0x25, 0x1a, 0x29, 0x9, 0x41, 0x48,	// 40
	0x49, 0x41, 0x9, 0x2a, 0x1d, 0x20,	// 41
	0x11, 0x3a, 0x4a, 0x39, 0x48,	// 42
	0x21, 0x4b, 0x2b, 0x49, 0x28,	// 43
	0x49, 0x3a, 0x28,	// 44
	0x21, 0x49, 0x49, 0x49, 0x28,	// 45
	0x39, 0x40,	// 46
	0x32, 0x32, 0x32, 0x32, 0x40,	// 47
	0x1c, 0x22, 0x21, 0x12, 0x29, 0x11, 0x2a, 0x11, 0x22, 0x24, 0x48,	// 48
	0x9, 0x1b, 0x1c, 0x2a, 0x50,	// 49
	0x32, 0x19, 0x19, 0x9, 0x11, 0x19, 0x11, 0x11, 0x19, 0x11, 0x11, 0x11, 0x19, 0x1a, 0x58,	// 50
	0x31, 0x21, 0x29, 0x11, 0x11, 0x19, 0x11, 0x11, 0x19, 0x11, 0x14, 0x22, 0x58,	// 51
	0x29, 0x42, 0x39, 0x9, 0x31, 0x13, 0x19, 0xb, 0x23, 0x11, 0x40,	// 52
	0x2a, 0x2a, 0x19, 0x12, 0x9, 0x19, 0x11, 0x11, 0x19, 0x11, 0x11, 0x11, 0x19, 0x1a, 0x40,	// 53
	0x1c, 0x23, 0x19, 0x11, 0x11, 0x19, 0x11, 0x11, 0x19, 0x11, 0x1b, 0x21, 0x60,	// 54
	0x1, 0x2a, 0x11, 0x21, 0x21, 0x12, 0x29, 0x9, 0x3a, 0x70,	// 55
	0x2a, 0x24, 0x11, 0x11, 0x11, 0x19, 0x11, 0x11, 0x19, 0x11, 0x14, 0x22, 0x58,	// 56
	0x31, 0x23, 0x19, 0x11, 0x19, 0x11, 0x11, 0x19, 0x11, 0x11, 0x1b, 0x24, 0x48,	// 57
	0x39, 0x21, 0x58,	// 58
	0x49, 0x3a, 0x19, 0x48,	// 59
	0x21, 0x41, 0x9, 0x39, 0x11, 0x29, 0x38,	// 60
	0x29, 0x39, 0x9, 0x39, 0x9, 0x39, 0x9, 0x39, 0x60,	// 61
	0x31, 0x29, 0x11, 0x39, 0x9, 0x41, 0x28,	// 62
	0x39, 0x19, 0x12, 0x21, 0x11, 0x31, 0x11, 0x3a, 0x68,	// 63

    }
};
