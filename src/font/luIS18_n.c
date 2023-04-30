
// file: font/luIS18.bdf
// font: -B&H-Lucida-Medium-I-Normal-Sans-18-180-75-75-P-105-ISO10646-1

#include <font.h>

const struct Font font_luIS18_n = {
    .type       = 1,
    .name	= "luIS18_n",
    .height	= 16,
    .width	= 14,
    .lineheight = 18,
    .bytescol	= 2,
    .numcol     = 14,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 8, .ncol = 4, .xadj = -10, .pos = 0 }, // 33 [8]
	{ .l0 = 3, .r0 = 6, .ncol = 5, .xadj = -7, .pos = 6 }, // 34 [10]
	{ .l0 = 2, .r0 = 1, .ncol = 11, .xadj = -2, .pos = 11 }, // 35 [22]
	{ .l0 = 2, .r0 = 2, .ncol = 10, .xadj = -2, .pos = 34 }, // 36 [20]
	{ .l0 = 2, .r0 = 0, .ncol = 12, .xadj = 0, .pos = 55 }, // 37 [24]
	{ .l0 = 2, .r0 = 1, .ncol = 11, .xadj = -1, .pos = 83 }, // 38 [22]
	{ .l0 = 3, .r0 = 9, .ncol = 2, .xadj = -10, .pos = 109 }, // 39 [4]
	{ .l0 = 3, .r0 = 6, .ncol = 5, .xadj = -8, .pos = 112 }, // 40 [10]
	{ .l0 = 1, .r0 = 8, .ncol = 5, .xadj = -8, .pos = 121 }, // 41 [10]
	{ .l0 = 3, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 130 }, // 42 [12]
	{ .l0 = 3, .r0 = 2, .ncol = 9, .xadj = -2, .pos = 141 }, // 43 [18]
	{ .l0 = 1, .r0 = 10, .ncol = 3, .xadj = -10, .pos = 153 }, // 44 [6]
	{ .l0 = 2, .r0 = 7, .ncol = 5, .xadj = -8, .pos = 157 }, // 45 [10]
	{ .l0 = 2, .r0 = 10, .ncol = 2, .xadj = -10, .pos = 163 }, // 46 [4]
	{ .l0 = 0, .r0 = 3, .ncol = 11, .xadj = -5, .pos = 166 }, // 47 [22]
	{ .l0 = 3, .r0 = 1, .ncol = 10, .xadj = -2, .pos = 178 }, // 48 [20]
	{ .l0 = 6, .r0 = 4, .ncol = 4, .xadj = -2, .pos = 197 }, // 49 [8]
	{ .l0 = 3, .r0 = 1, .ncol = 10, .xadj = -2, .pos = 206 }, // 50 [20]
	{ .l0 = 3, .r0 = 1, .ncol = 10, .xadj = -2, .pos = 229 }, // 51 [20]
	{ .l0 = 3, .r0 = 2, .ncol = 9, .xadj = -2, .pos = 252 }, // 52 [18]
	{ .l0 = 3, .r0 = 1, .ncol = 10, .xadj = -2, .pos = 270 }, // 53 [20]
	{ .l0 = 3, .r0 = 1, .ncol = 10, .xadj = -2, .pos = 290 }, // 54 [20]
	{ .l0 = 4, .r0 = 0, .ncol = 10, .xadj = -2, .pos = 314 }, // 55 [20]
	{ .l0 = 3, .r0 = 1, .ncol = 10, .xadj = -2, .pos = 331 }, // 56 [20]
	{ .l0 = 4, .r0 = 1, .ncol = 9, .xadj = -2, .pos = 355 }, // 57 [18]
	{ .l0 = 1, .r0 = 9, .ncol = 4, .xadj = -10, .pos = 378 }, // 58 [8]
	{ .l0 = 0, .r0 = 9, .ncol = 5, .xadj = -10, .pos = 383 }, // 59 [10]
	{ .l0 = 3, .r0 = 2, .ncol = 9, .xadj = -2, .pos = 389 }, // 60 [18]
	{ .l0 = 2, .r0 = 2, .ncol = 10, .xadj = -2, .pos = 404 }, // 61 [20]
	{ .l0 = 3, .r0 = 2, .ncol = 9, .xadj = -2, .pos = 423 }, // 62 [18]
	{ .l0 = 3, .r0 = 4, .ncol = 7, .xadj = -5, .pos = 438 }, // 63 [14]
    },
    .data       = {
	0x62, 0x3d, 0x12, 0x1f, 0x4c, 0x58,	// 33
	0x4, 0x62, 0xf4, 0x62, 0x70,	// 34
	0x49, 0x12, 0x31, 0x25, 0x31, 0x15, 0x46, 0x4c, 0x11, 0x12, 0x1c, 0x25, 0x1a, 0x9, 0x15, 0x46, 0x4c, 0x11, 0x3c, 0x21, 0x3a, 0x9, 0x58,	// 35
	0x61, 0x7a, 0x2b, 0x39, 0x25, 0x24, 0x11, 0x1e, 0x11, 0x19, 0x22, 0x29, 0x19, 0x15, 0x1a, 0x14, 0x1e, 0x21, 0x34, 0x31, 0x68,	// 36
	0x1c, 0x31, 0x26, 0x22, 0x19, 0x29, 0x1a, 0x21, 0x29, 0x12, 0x2e, 0x12, 0x3c, 0x12, 0x69, 0x6a, 0x14, 0x3a, 0x16, 0x2a, 0x11, 0x29, 0x22, 0x19, 0x29, 0x1a, 0x26, 0x18,	// 37
	0x4c, 0x57, 0x49, 0x22, 0x23, 0x9, 0x31, 0x25, 0x31, 0x19, 0x1c, 0x21, 0x19, 0x19, 0xc, 0x9, 0x21, 0x11, 0x23, 0x2c, 0x2c, 0x22, 0x1b, 0x12, 0x4a, 0x38,	// 38
	0x4, 0x62, 0x70,	// 39
	0x37, 0x1, 0x37, 0x4, 0x1c, 0x49, 0xa, 0x69, 0x78,	// 40
	0x79, 0x6a, 0x9, 0x4c, 0x1f, 0x4, 0x37, 0x1, 0x30,	// 41
	0x1a, 0x11, 0x61, 0xa, 0x69, 0x5b, 0xb, 0x61, 0x11, 0x5a, 0x58,	// 42
	0x41, 0x79, 0x79, 0x79, 0x12, 0x4d, 0x4a, 0x11, 0x79, 0x79, 0x79, 0x38,	// 43
	0x79, 0x63, 0x6a, 0x10,	// 44
	0x41, 0x79, 0x79, 0x79, 0x79, 0x38,	// 45
	0x62, 0x72, 0x10,	// 46
	0x79, 0x6b, 0x5c, 0x5b, 0x5c, 0x54, 0x54, 0x5b, 0x5c, 0x5b, 0x69, 0x78,	// 47
	0x36, 0x47, 0x2, 0x33, 0x32, 0x22, 0x49, 0x21, 0x51, 0x19, 0x51, 0x21, 0x4a, 0x22, 0x33, 0x37, 0x2, 0x46, 0x38,	// 48
	0x11, 0x3c, 0x21, 0x1f, 0x1, 0x1f, 0x2, 0x3d, 0x50,	// 49
	0x62, 0x6b, 0x21, 0x3c, 0x1a, 0x32, 0xa, 0x19, 0x32, 0x12, 0x19, 0x31, 0x1a, 0x19, 0x2a, 0x1a, 0x1a, 0x1a, 0x22, 0x1e, 0x2a, 0x24, 0x50,	// 50
	0x61, 0x7a, 0x21, 0x51, 0x1a, 0x21, 0x29, 0x19, 0x29, 0x29, 0x19, 0x29, 0x29, 0x19, 0x23, 0x1a, 0x1a, 0x12, 0xd, 0x25, 0x1b, 0x33, 0x58,	// 51
	0x42, 0x6b, 0x61, 0xa, 0x59, 0x12, 0x51, 0x1a, 0x49, 0x26, 0x21, 0x1f, 0x1, 0x1f, 0x2, 0x3d, 0x12, 0x30,	// 52
	0x61, 0x7a, 0x33, 0x31, 0x1b, 0x11, 0x31, 0x1a, 0x19, 0x31, 0x1a, 0x1a, 0x22, 0x1a, 0x26, 0x22, 0x2c, 0x2a, 0x72, 0x68,	// 53
	0x36, 0x47, 0x2, 0x33, 0x11, 0x1a, 0x22, 0x19, 0x29, 0x21, 0x19, 0x31, 0x19, 0x21, 0x31, 0x19, 0x22, 0x1a, 0x21, 0x2e, 0x22, 0x2b, 0x39, 0x68,	// 54
	0x5b, 0x1a, 0x35, 0x1a, 0x2b, 0x32, 0x22, 0x42, 0x1a, 0x4a, 0x12, 0x52, 0xa, 0x5c, 0x63, 0x6a, 0x68,	// 55
	0x53, 0x65, 0x2b, 0x12, 0x12, 0x25, 0x9, 0x21, 0x21, 0x13, 0x29, 0x19, 0x22, 0x29, 0x19, 0x23, 0x19, 0x22, 0x11, 0xe, 0x25, 0x1b, 0x33, 0x58,	// 56
	0x23, 0x29, 0x2e, 0x22, 0x22, 0x1a, 0x21, 0x19, 0x31, 0x21, 0x19, 0x31, 0x19, 0x21, 0x29, 0x1a, 0x22, 0x19, 0x13, 0x37, 0x2, 0x46, 0x38,	// 57
	0x62, 0x72, 0x32, 0x72, 0x50,	// 58
	0x79, 0x63, 0x6a, 0x32, 0x72, 0x50,	// 59
	0x41, 0x7a, 0x69, 0xa, 0x61, 0x11, 0x59, 0x21, 0x51, 0x21, 0x49, 0x31, 0x41, 0x71, 0x58,	// 60
	0x51, 0x59, 0x19, 0x59, 0x19, 0x59, 0x19, 0x59, 0x19, 0x59, 0x19, 0x59, 0x19, 0x59, 0x19, 0x59, 0x19, 0x59, 0x48,	// 61
	0x61, 0x71, 0x41, 0x31, 0x49, 0x21, 0x51, 0x21, 0x59, 0x11, 0x62, 0x9, 0x6a, 0x79, 0x38,	// 62
	0x11, 0x4a, 0x1a, 0x2a, 0x12, 0x19, 0x2a, 0x41, 0x22, 0x4a, 0x12, 0x55, 0x63, 0x58,	// 63

    }
};
