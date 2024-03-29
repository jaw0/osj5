
// file: font/lutBS12.bdf
// font: -B&H-LucidaTypewriter-Bold-R-Normal-Sans-12-120-75-75-M-70-ISO10646-1

#include <font.h>

const struct Font font_lutBS12_n = {
    .type       = 1,
    .name	= "lutBS12_n",
    .height	= 13,
    .width	= 7,
    .lineheight = 13,
    .bytescol	= 2,
    .numcol     = 7,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 3, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 0 }, // 33 [4]
	{ .l0 = 2, .r0 = 0, .ncol = 5, .xadj = 0, .pos = 5 }, // 34 [9]
	{ .l0 = 0, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 10 }, // 35 [12]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 25 }, // 36 [10]
	{ .l0 = 0, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 39 }, // 37 [12]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 57 }, // 38 [10]
	{ .l0 = 2, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 72 }, // 39 [4]
	{ .l0 = 2, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 75 }, // 40 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 83 }, // 41 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 91 }, // 42 [9]
	{ .l0 = 0, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 99 }, // 43 [12]
	{ .l0 = 3, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 107 }, // 44 [4]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 111 }, // 45 [10]
	{ .l0 = 3, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 118 }, // 46 [4]
	{ .l0 = 0, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 121 }, // 47 [12]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 129 }, // 48 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 140 }, // 49 [7]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 147 }, // 50 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 162 }, // 51 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 178 }, // 52 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 189 }, // 53 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 203 }, // 54 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 217 }, // 55 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 227 }, // 56 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 242 }, // 57 [10]
	{ .l0 = 3, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 256 }, // 58 [4]
	{ .l0 = 3, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 261 }, // 59 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 267 }, // 60 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 278 }, // 61 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 291 }, // 62 [10]
	{ .l0 = 2, .r0 = 0, .ncol = 5, .xadj = 0, .pos = 302 }, // 63 [9]
    },
    .data       = {
	0x15, 0x12, 0x26, 0xa, 0x40,	// 33
	0xc, 0x4a, 0xc4, 0x4a, 0x88,	// 34
	0x21, 0x11, 0x3f, 0x2, 0x27, 0x2, 0x31, 0x11, 0x3f, 0x2, 0x27, 0x2, 0x31, 0x11, 0x50,	// 35
	0x1b, 0x19, 0x2d, 0x19, 0x21, 0x12, 0x1e, 0x1a, 0x11, 0x21, 0x1d, 0x29, 0x1b, 0x28,	// 36
	0x1a, 0x22, 0x21, 0x11, 0x12, 0x2c, 0x9, 0x42, 0x9, 0xa, 0x41, 0x9, 0x11, 0x2a, 0x14, 0x22, 0x22, 0x40,	// 37
	0x1b, 0xb, 0x2f, 0x2, 0x21, 0x1a, 0x11, 0x24, 0xa, 0x9, 0x2a, 0x1a, 0x4a, 0xa, 0x20,	// 38
	0xc, 0x4a, 0x80,	// 39
	0x1f, 0x2f, 0x2, 0x1a, 0x3a, 0x11, 0x49, 0x28,	// 40
	0x9, 0x49, 0x12, 0x3a, 0x1f, 0x2, 0x2f, 0x38,	// 41
	0x19, 0x9, 0x59, 0x55, 0x51, 0x59, 0x9, 0x70,	// 42
	0x31, 0x61, 0x61, 0x4f, 0x49, 0x61, 0x61, 0x58,	// 43
	0x4a, 0x9, 0x4b, 0x38,	// 44
	0x31, 0x61, 0x61, 0x61, 0x61, 0x61, 0x40,	// 45
	0x4a, 0x5a, 0x40,	// 46
	0x52, 0x4c, 0x43, 0x43, 0x44, 0x3c, 0x4a, 0x78,	// 47
	0x1f, 0x2f, 0x2, 0x21, 0x39, 0x21, 0x39, 0x27, 0x2, 0x2f, 0x28,	// 48
	0x19, 0x61, 0x5f, 0x2, 0x27, 0x2, 0x30,	// 49
	0x19, 0x23, 0x22, 0x1c, 0x21, 0x1a, 0xa, 0x21, 0x12, 0x12, 0x25, 0x12, 0x2b, 0x1a, 0x20,	// 50
	0x19, 0x29, 0x2a, 0x11, 0x12, 0x21, 0x19, 0x19, 0x21, 0x19, 0x19, 0x27, 0x2, 0x2b, 0xb, 0x28,	// 51
	0x33, 0x42, 0xa, 0x39, 0x1a, 0x37, 0x2, 0x27, 0x2, 0x4a, 0x30,	// 52
	0x49, 0x2d, 0x12, 0x22, 0x11, 0x19, 0x22, 0x11, 0x19, 0x22, 0x15, 0x22, 0x1b, 0x28,	// 53
	0x1f, 0x2f, 0x2, 0x21, 0x19, 0x19, 0x21, 0x19, 0x19, 0x22, 0x15, 0x29, 0x1b, 0x28,	// 54
	0x12, 0x5a, 0x23, 0x22, 0x15, 0x22, 0xb, 0x3c, 0x4b, 0x50,	// 55
	0x1b, 0xb, 0x2f, 0x2, 0x21, 0x12, 0x19, 0x21, 0x1a, 0x11, 0x27, 0x2, 0x2b, 0xb, 0x28,	// 56
	0x1b, 0x19, 0x2d, 0x12, 0x21, 0x19, 0x19, 0x21, 0x19, 0x19, 0x27, 0x2, 0x2f, 0x28,	// 57
	0x22, 0x1a, 0x32, 0x1a, 0x40,	// 58
	0x22, 0x1a, 0x9, 0x22, 0x1b, 0x38,	// 59
	0x31, 0x5b, 0x4a, 0xa, 0x41, 0x19, 0x3a, 0x1a, 0x31, 0x29, 0x28,	// 60
	0x29, 0x9, 0x51, 0x9, 0x51, 0x9, 0x51, 0x9, 0x51, 0x9, 0x51, 0x9, 0x38,	// 61
	0x19, 0x29, 0x32, 0x1a, 0x39, 0x19, 0x42, 0xa, 0x4b, 0x59, 0x40,	// 62
	0x19, 0x59, 0x1a, 0xa, 0x21, 0x13, 0xa, 0x24, 0x52, 0x78,	// 63

    }
};
