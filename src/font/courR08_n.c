
// file: font/courR08.bdf
// font: -Adobe-Courier-Medium-R-Normal--8-80-75-75-M-50-ISO10646-1

#include <font.h>

const struct Font font_courR08_n = {
    .type       = 1,
    .name	= "courR08_n",
    .height	= 9,
    .width	= 6,
    .lineheight = 9,
    .bytescol	= 2,
    .numcol     = 6,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 3, .ncol = 1, .xadj = -1, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 3 }, // 34 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 6 }, // 35 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 15 }, // 36 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 22 }, // 37 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 34 }, // 38 [6]
	{ .l0 = 2, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 45 }, // 39 [2]
	{ .l0 = 1, .r0 = 3, .ncol = 2, .xadj = -1, .pos = 47 }, // 40 [3]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = -1, .pos = 51 }, // 41 [3]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 55 }, // 42 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 61 }, // 43 [6]
	{ .l0 = 1, .r0 = 3, .ncol = 2, .xadj = -1, .pos = 67 }, // 44 [3]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 70 }, // 45 [4]
	{ .l0 = 2, .r0 = 3, .ncol = 1, .xadj = -1, .pos = 74 }, // 46 [2]
	{ .l0 = 0, .r0 = 2, .ncol = 4, .xadj = -1, .pos = 76 }, // 47 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 81 }, // 48 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 86 }, // 49 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 91 }, // 50 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 99 }, // 51 [4]
	{ .l0 = 0, .r0 = 2, .ncol = 4, .xadj = -1, .pos = 106 }, // 52 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 112 }, // 53 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 120 }, // 54 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 127 }, // 55 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 132 }, // 56 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 140 }, // 57 [4]
	{ .l0 = 2, .r0 = 3, .ncol = 1, .xadj = -1, .pos = 147 }, // 58 [2]
	{ .l0 = 1, .r0 = 3, .ncol = 2, .xadj = -1, .pos = 150 }, // 59 [3]
	{ .l0 = 1, .r0 = 3, .ncol = 2, .xadj = -1, .pos = 154 }, // 60 [3]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 158 }, // 61 [4]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = -1, .pos = 165 }, // 62 [3]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 169 }, // 63 [4]
    },
    .data       = {
	0xc, 0x9, 0x48,	// 33
	0xb, 0x7b, 0x50,	// 34
	0x19, 0x9, 0x35, 0x13, 0x9, 0x35, 0x13, 0x9, 0x30,	// 35
	0x12, 0x9, 0x1c, 0xb, 0x19, 0x9, 0x48,	// 36
	0x12, 0x11, 0x19, 0x9, 0x9, 0x26, 0x21, 0x9, 0x9, 0x19, 0x12, 0x30,	// 37
	0x29, 0x32, 0x9, 0x21, 0x9, 0x9, 0x21, 0x11, 0x39, 0x9, 0x28,	// 38
	0x3, 0x68,	// 39
	0x1b, 0x22, 0x1a, 0x38,	// 40
	0xa, 0x1a, 0x23, 0x48,	// 41
	0x11, 0x9, 0x2b, 0x39, 0x9, 0x48,	// 42
	0x21, 0x41, 0x35, 0x31, 0x41, 0x38,	// 43
	0x41, 0x32, 0x38,	// 44
	0x21, 0x41, 0x41, 0x48,	// 45
	0x31, 0x48,	// 46
	0x3a, 0x2a, 0x2a, 0x2a, 0x50,	// 47
	0x14, 0x21, 0x21, 0x24, 0x40,	// 48
	0x11, 0x19, 0x1e, 0x41, 0x38,	// 49
	0x11, 0x12, 0x19, 0x11, 0x9, 0x22, 0x11, 0x38,	// 50
	0x11, 0x11, 0x21, 0x9, 0x11, 0x24, 0x40,	// 51
	0x1a, 0x31, 0x9, 0x2e, 0x31, 0x40,	// 52
	0xb, 0x11, 0x19, 0x9, 0x11, 0x19, 0x12, 0x40,	// 53
	0x15, 0x19, 0x11, 0x9, 0x19, 0x12, 0x40,	// 54
	0xa, 0x39, 0x13, 0x1b, 0x50,	// 55
	0xa, 0xa, 0x21, 0x9, 0x11, 0x1a, 0xa, 0x40,	// 56
	0x12, 0x11, 0x19, 0x11, 0x9, 0x1d, 0x40,	// 57
	0x21, 0x9, 0x48,	// 58
	0x39, 0x29, 0x9, 0x40,	// 59
	0x1a, 0x31, 0x11, 0x48,	// 60
	0x19, 0x9, 0x31, 0x9, 0x31, 0x9, 0x40,	// 61
	0x11, 0x11, 0x32, 0x50,	// 62
	0x11, 0x39, 0x11, 0x9, 0x22, 0x50,	// 63

    }
};
