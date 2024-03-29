
// file: font/lutRS12.bdf
// font: -B&H-LucidaTypewriter-Medium-R-Normal-Sans-12-120-75-75-M-70-ISO10646-1

#include <font.h>

const struct Font font_lutRS12_n = {
    .type       = 1,
    .name	= "lutRS12_n",
    .height	= 11,
    .width	= 7,
    .lineheight = 12,
    .bytescol	= 2,
    .numcol     = 7,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 3, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 0 }, // 33 [3]
	{ .l0 = 2, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 5 }, // 34 [5]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 8 }, // 35 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 21 }, // 36 [7]
	{ .l0 = 0, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 34 }, // 37 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 54 }, // 38 [9]
	{ .l0 = 3, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 70 }, // 39 [2]
	{ .l0 = 2, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 72 }, // 40 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 79 }, // 41 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 86 }, // 42 [7]
	{ .l0 = 0, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 95 }, // 43 [10]
	{ .l0 = 2, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 103 }, // 44 [5]
	{ .l0 = 0, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 107 }, // 45 [10]
	{ .l0 = 2, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 115 }, // 46 [3]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 118 }, // 47 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 124 }, // 48 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 3, .xadj = 0, .pos = 133 }, // 49 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 138 }, // 50 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 152 }, // 51 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 165 }, // 52 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 176 }, // 53 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 190 }, // 54 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 203 }, // 55 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 212 }, // 56 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 226 }, // 57 [7]
	{ .l0 = 2, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 239 }, // 58 [3]
	{ .l0 = 1, .r0 = 3, .ncol = 3, .xadj = 0, .pos = 244 }, // 59 [5]
	{ .l0 = 2, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 250 }, // 60 [6]
	{ .l0 = 0, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 258 }, // 61 [10]
	{ .l0 = 2, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 273 }, // 62 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 281 }, // 63 [7]
    },
    .data       = {
	0xe, 0xa, 0x15, 0x12, 0x18,	// 33
	0x3, 0x9b, 0x78,	// 34
	0x19, 0x11, 0x2f, 0x2, 0x21, 0x11, 0x39, 0x11, 0x2f, 0x2, 0x21, 0x11, 0x50,	// 35
	0x12, 0x21, 0x19, 0x11, 0x21, 0xf, 0x4, 0x9, 0x19, 0x19, 0x19, 0x1b, 0x18,	// 36
	0x12, 0x21, 0x19, 0x11, 0x11, 0x21, 0x11, 0x9, 0x32, 0x9, 0xa, 0x31, 0x9, 0x11, 0x21, 0x11, 0x11, 0x19, 0x22, 0x28,	// 37
	0x33, 0x22, 0x9, 0x19, 0x11, 0x12, 0x19, 0x11, 0x11, 0x9, 0x11, 0x1a, 0x1a, 0x3a, 0x11, 0x38,	// 38
	0x3, 0x68,	// 39
	0x1d, 0x22, 0x2a, 0x9, 0x4a, 0x49, 0x20,	// 40
	0x1, 0x4a, 0x49, 0xa, 0x2a, 0x25, 0x38,	// 41
	0x11, 0x9, 0x49, 0x42, 0xa, 0x41, 0x49, 0x9, 0x38,	// 42
	0x29, 0x51, 0x51, 0x3f, 0x39, 0x51, 0x51, 0x40,	// 43
	0x51, 0x43, 0x42, 0x40,	// 44
	0x29, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x40,	// 45
	0x42, 0x4a, 0x18,	// 46
	0x4a, 0x3a, 0x33, 0x32, 0x3a, 0x50,	// 47
	0x17, 0x19, 0x39, 0x11, 0x39, 0x11, 0x39, 0x1f, 0x18,	// 48
	0x19, 0x49, 0x4f, 0x2, 0x40,	// 49
	0x11, 0x2a, 0x11, 0x29, 0x9, 0x11, 0x21, 0x11, 0x11, 0x19, 0x19, 0x1b, 0x21, 0x10,	// 50
	0x11, 0x29, 0x19, 0x39, 0x11, 0x19, 0x19, 0x11, 0x19, 0x19, 0x1b, 0xb, 0x18,	// 51
	0x2a, 0x41, 0x9, 0x39, 0x11, 0x31, 0x19, 0x2f, 0x2, 0x39, 0x50,	// 52
	0xc, 0x19, 0x19, 0x11, 0x21, 0x11, 0x11, 0x21, 0x11, 0x11, 0x21, 0x11, 0x1c, 0x18,	// 53
	0x17, 0x19, 0x19, 0x19, 0x11, 0x19, 0x19, 0x11, 0x19, 0x19, 0x19, 0x1b, 0x18,	// 54
	0x9, 0x51, 0x2b, 0x11, 0x1a, 0x29, 0x11, 0x3b, 0x40,	// 55
	0x13, 0xb, 0x19, 0x19, 0x19, 0x11, 0x19, 0x19, 0x11, 0x19, 0x19, 0x1b, 0xb, 0x18,	// 56
	0x13, 0x19, 0x19, 0x19, 0x19, 0x11, 0x19, 0x19, 0x11, 0x19, 0x19, 0x1f, 0x18,	// 57
	0x1a, 0x1a, 0x22, 0x1a, 0x18,	// 58
	0x51, 0x1a, 0x1b, 0x1a, 0x1a, 0x40,	// 59
	0x29, 0x49, 0x9, 0x39, 0x19, 0x29, 0x29, 0x30,	// 60
	0x21, 0x9, 0x41, 0x9, 0x41, 0x9, 0x41, 0x9, 0x41, 0x9, 0x41, 0x9, 0x41, 0x9, 0x38,	// 61
	0x11, 0x29, 0x29, 0x19, 0x39, 0x9, 0x49, 0x48,	// 62
	0x9, 0x51, 0x1a, 0xa, 0x11, 0x19, 0x31, 0x19, 0x3b, 0x38,	// 63

    }
};
