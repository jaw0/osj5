
// file: font/9x15.bdf
// font: -Misc-Fixed-Medium-R-Normal--15-140-75-75-C-90-ISO10646-1

#include <font.h>

const struct Font font_9x15_n = {
    .type       = 1,
    .name	= "9x15_n",
    .height	= 15,
    .width	= 9,
    .lineheight = 15,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 4, .r0 = 4, .ncol = 1, .xadj = 0, .pos = 0 }, // 33 [2]
	{ .l0 = 3, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 3 }, // 34 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = 0, .pos = 7 }, // 35 [12]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 20 }, // 36 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 39 }, // 37 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 55 }, // 38 [14]
	{ .l0 = 4, .r0 = 4, .ncol = 1, .xadj = 0, .pos = 72 }, // 39 [2]
	{ .l0 = 3, .r0 = 3, .ncol = 3, .xadj = 0, .pos = 74 }, // 40 [6]
	{ .l0 = 3, .r0 = 3, .ncol = 3, .xadj = 0, .pos = 80 }, // 41 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 86 }, // 42 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 98 }, // 43 [14]
	{ .l0 = 4, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 106 }, // 44 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 110 }, // 45 [14]
	{ .l0 = 4, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 118 }, // 46 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 121 }, // 47 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 129 }, // 48 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 142 }, // 49 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 154 }, // 50 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 174 }, // 51 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 193 }, // 52 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 206 }, // 53 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 226 }, // 54 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 244 }, // 55 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 256 }, // 56 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 278 }, // 57 [14]
	{ .l0 = 4, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 296 }, // 58 [4]
	{ .l0 = 4, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 301 }, // 59 [4]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 307 }, // 60 [10]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 317 }, // 61 [14]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 332 }, // 62 [10]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 342 }, // 63 [14]
    },
    .data       = {
	0xf, 0x12, 0x20,	// 33
	0x13, 0xf8, 0x5b, 0x70,	// 34
	0x29, 0x11, 0x4f, 0x1, 0x49, 0x11, 0x59, 0x11, 0x4f, 0x1, 0x49, 0x11, 0x60,	// 35
	0x22, 0x21, 0x39, 0x11, 0x21, 0x31, 0x19, 0x19, 0x2f, 0x4, 0x29, 0x19, 0x19, 0x31, 0x21, 0x11, 0x39, 0x22, 0x58,	// 36
	0x1a, 0x31, 0x29, 0x11, 0x1a, 0x3a, 0x19, 0x62, 0x61, 0x1a, 0x3a, 0x19, 0x11, 0x29, 0x32, 0x58,	// 37
	0x1b, 0x13, 0x31, 0x1a, 0x19, 0x29, 0x1a, 0x19, 0x33, 0x11, 0x9, 0x69, 0x69, 0x9, 0x59, 0x19, 0x50,	// 38
	0x13, 0x58,	// 39
	0x26, 0x3a, 0x32, 0x21, 0x51, 0x28,	// 40
	0x9, 0x51, 0x22, 0x32, 0x3e, 0x40,	// 41
	0x19, 0x19, 0x59, 0x9, 0x69, 0x5f, 0x59, 0x69, 0x9, 0x59, 0x19, 0x70,	// 42
	0x39, 0x71, 0x71, 0x5f, 0x59, 0x71, 0x71, 0x70,	// 43
	0x52, 0x11, 0x54, 0x18,	// 44
	0x39, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71, 0x70,	// 45
	0x52, 0x6a, 0x28,	// 46
	0x59, 0x62, 0x61, 0x62, 0x61, 0x62, 0x61, 0x98,	// 47
	0x26, 0x41, 0x31, 0x31, 0x41, 0x29, 0x41, 0x29, 0x41, 0x31, 0x31, 0x46, 0x60,	// 48
	0x29, 0x29, 0x39, 0x31, 0x31, 0x39, 0x2f, 0x3, 0x71, 0x71, 0x71, 0x50,	// 49
	0x1a, 0x2a, 0x29, 0x31, 0x9, 0x29, 0x29, 0x11, 0x29, 0x21, 0x19, 0x29, 0x19, 0x21, 0x29, 0x11, 0x29, 0x32, 0x31, 0x50,	// 50
	0x11, 0x39, 0x31, 0x41, 0x29, 0x41, 0x29, 0x19, 0x21, 0x29, 0x12, 0x21, 0x29, 0x9, 0x9, 0x21, 0x2a, 0x1c, 0x58,	// 51
	0x3a, 0x61, 0x9, 0x59, 0x11, 0x51, 0x19, 0x49, 0x21, 0x47, 0x3, 0x59, 0x68,	// 52
	0x15, 0x19, 0x31, 0x19, 0x21, 0x29, 0x11, 0x29, 0x29, 0x11, 0x29, 0x29, 0x11, 0x29, 0x29, 0x11, 0x29, 0x29, 0x1d, 0x58,	// 53
	0x27, 0x39, 0x19, 0x19, 0x29, 0x19, 0x21, 0x29, 0x19, 0x21, 0x29, 0x19, 0x21, 0x29, 0x19, 0x21, 0x54, 0x58,	// 54
	0x11, 0x71, 0x71, 0x3a, 0x29, 0x2a, 0x39, 0x1a, 0x49, 0xa, 0x5a, 0x90,	// 55
	0x21, 0x1a, 0x41, 0x9, 0x9, 0x11, 0x31, 0x19, 0x21, 0x29, 0x19, 0x21, 0x29, 0x19, 0x21, 0x31, 0x9, 0x9, 0x11, 0x41, 0x1a, 0x60,	// 56
	0x1c, 0x51, 0x21, 0x19, 0x29, 0x21, 0x19, 0x29, 0x21, 0x19, 0x29, 0x21, 0x19, 0x29, 0x19, 0x19, 0x3f, 0x60,	// 57
	0x2a, 0x1a, 0x42, 0x1a, 0x28,	// 58
	0x2a, 0x1a, 0x11, 0x2a, 0x1c, 0x18,	// 59
	0x32, 0x61, 0x11, 0x51, 0x21, 0x41, 0x31, 0x31, 0x41, 0x40,	// 60
	0x31, 0x11, 0x59, 0x11, 0x59, 0x11, 0x59, 0x11, 0x59, 0x11, 0x59, 0x11, 0x59, 0x11, 0x60,	// 61
	0x11, 0x41, 0x31, 0x31, 0x41, 0x21, 0x51, 0x11, 0x62, 0x60,	// 62
	0x1a, 0x61, 0x71, 0x71, 0x2a, 0x9, 0x29, 0x21, 0x49, 0x19, 0x5b, 0x80,	// 63

    }
};
