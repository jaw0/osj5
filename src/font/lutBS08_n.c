
// file: font/lutBS08.bdf
// font: -B&H-LucidaTypewriter-Bold-R-Normal-Sans-8-80-75-75-M-50-ISO10646-1

#include <font.h>

const struct Font font_lutBS08_n = {
    .type       = 1,
    .name	= "lutBS08_n",
    .height	= 9,
    .width	= 5,
    .lineheight = 9,
    .bytescol	= 2,
    .numcol     = 5,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 2, .ncol = 1, .xadj = 0, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 1, .ncol = 3, .xadj = 0, .pos = 3 }, // 34 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 6 }, // 35 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 3, .xadj = 0, .pos = 14 }, // 36 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 22 }, // 37 [5]
	{ .l0 = 0, .r0 = 0, .ncol = 5, .xadj = 0, .pos = 29 }, // 38 [6]
	{ .l0 = 2, .r0 = 2, .ncol = 1, .xadj = 0, .pos = 39 }, // 39 [2]
	{ .l0 = 1, .r0 = 1, .ncol = 3, .xadj = 0, .pos = 41 }, // 40 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 3, .xadj = 0, .pos = 47 }, // 41 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 53 }, // 42 [5]
	{ .l0 = 0, .r0 = 0, .ncol = 5, .xadj = 0, .pos = 59 }, // 43 [6]
	{ .l0 = 2, .r0 = 2, .ncol = 1, .xadj = 0, .pos = 65 }, // 44 [2]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 67 }, // 45 [5]
	{ .l0 = 2, .r0 = 2, .ncol = 1, .xadj = 0, .pos = 72 }, // 46 [2]
	{ .l0 = 0, .r0 = 0, .ncol = 5, .xadj = 0, .pos = 74 }, // 47 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 80 }, // 48 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 3, .xadj = 0, .pos = 87 }, // 49 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 3, .xadj = 0, .pos = 92 }, // 50 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 3, .xadj = 0, .pos = 100 }, // 51 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 109 }, // 52 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 3, .xadj = 0, .pos = 115 }, // 53 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 123 }, // 54 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 3, .xadj = 0, .pos = 132 }, // 55 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 138 }, // 56 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 149 }, // 57 [5]
	{ .l0 = 2, .r0 = 2, .ncol = 1, .xadj = 0, .pos = 158 }, // 58 [2]
	{ .l0 = 2, .r0 = 2, .ncol = 1, .xadj = 0, .pos = 161 }, // 59 [2]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 164 }, // 60 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 170 }, // 61 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 175 }, // 62 [5]
	{ .l0 = 1, .r0 = 0, .ncol = 4, .xadj = 0, .pos = 181 }, // 63 [5]
    },
    .data       = {
	0xc, 0x9, 0x48,	// 33
	0xa, 0x82, 0x58,	// 34
	0x19, 0xa, 0x1e, 0x19, 0xc, 0x1b, 0x9, 0x38,	// 35
	0xb, 0x11, 0x12, 0xa, 0xb, 0x9, 0x13, 0x38,	// 36
	0xb, 0x11, 0x1e, 0x1e, 0x19, 0x13, 0x30,	// 37
	0x22, 0x23, 0x11, 0x19, 0xa, 0x9, 0x1a, 0x12, 0x33, 0x28,	// 38
	0xb, 0x60,	// 39
	0x1c, 0x1a, 0x21, 0x11, 0x31, 0x28,	// 40
	0x9, 0x31, 0x11, 0x21, 0x24, 0x38,	// 41
	0x12, 0x34, 0x2c, 0x31, 0x9, 0x40,	// 42
	0x21, 0x41, 0x3c, 0x31, 0x41, 0x38,	// 43
	0x33, 0x38,	// 44
	0x29, 0x41, 0x41, 0x41, 0x38,	// 45
	0x31, 0x48,	// 46
	0x41, 0x32, 0x2a, 0x2a, 0x31, 0x50,	// 47
	0x14, 0x21, 0x21, 0x19, 0x21, 0x24, 0x38,	// 48
	0x9, 0x21, 0x1e, 0x41, 0x38,	// 49
	0x9, 0x1a, 0x19, 0x11, 0x9, 0x1b, 0x11, 0x38,	// 50
	0x9, 0x9, 0x11, 0x19, 0x9, 0x11, 0x1a, 0xa, 0x40,	// 51
	0x1a, 0x2a, 0x9, 0x2e, 0x31, 0x40,	// 52
	0xb, 0x11, 0x19, 0x9, 0x11, 0x19, 0x12, 0x40,	// 53
	0x14, 0x23, 0x11, 0x19, 0x9, 0x11, 0x19, 0x12, 0x38,	// 54
	0x9, 0x1a, 0x19, 0xa, 0x2a, 0x58,	// 55
	0x11, 0xa, 0x21, 0x9, 0x11, 0x19, 0xa, 0x9, 0x1a, 0xa, 0x38,	// 56
	0x12, 0x11, 0x19, 0x11, 0x9, 0x19, 0x13, 0x24, 0x38,	// 57
	0x19, 0x11, 0x48,	// 58
	0x19, 0x13, 0x38,	// 59
	0x21, 0x42, 0x3a, 0x31, 0x11, 0x30,	// 60
	0x22, 0x3a, 0x3a, 0x3a, 0x38,	// 61
	0x19, 0x11, 0x32, 0x3a, 0x41, 0x38,	// 62
	0xa, 0x39, 0x11, 0x9, 0x19, 0x9, 0x3a, 0x48,	// 63

    }
};
