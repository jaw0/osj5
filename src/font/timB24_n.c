
// file: font/timB24.bdf
// font: -Adobe-Times-Bold-R-Normal--24-240-75-75-P-132-ISO10646-1

#include <font.h>

const struct Font font_timB24_n = {
    .type       = 1,
    .name	= "timB24_n",
    .height	= 23,
    .width	= 21,
    .lineheight = 24,
    .bytescol	= 4,
    .numcol     = 21,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 15, .ncol = 4, .xadj = -13, .pos = 0 }, // 33 [12]
	{ .l0 = 2, .r0 = 11, .ncol = 8, .xadj = -9, .pos = 11 }, // 34 [23]
	{ .l0 = 0, .r0 = 9, .ncol = 12, .xadj = -8, .pos = 22 }, // 35 [35]
	{ .l0 = 1, .r0 = 10, .ncol = 10, .xadj = -9, .pos = 45 }, // 36 [29]
	{ .l0 = 1, .r0 = 3, .ncol = 17, .xadj = -2, .pos = 71 }, // 37 [49]
	{ .l0 = 2, .r0 = 2, .ncol = 17, .xadj = 0, .pos = 109 }, // 38 [49]
	{ .l0 = 2, .r0 = 16, .ncol = 3, .xadj = -14, .pos = 147 }, // 39 [9]
	{ .l0 = 1, .r0 = 15, .ncol = 5, .xadj = -13, .pos = 152 }, // 40 [15]
	{ .l0 = 2, .r0 = 14, .ncol = 5, .xadj = -13, .pos = 163 }, // 41 [15]
	{ .l0 = 1, .r0 = 10, .ncol = 10, .xadj = -8, .pos = 174 }, // 42 [29]
	{ .l0 = 1, .r0 = 8, .ncol = 12, .xadj = -7, .pos = 193 }, // 43 [35]
	{ .l0 = 1, .r0 = 16, .ncol = 4, .xadj = -15, .pos = 208 }, // 44 [12]
	{ .l0 = 1, .r0 = 14, .ncol = 6, .xadj = -13, .pos = 215 }, // 45 [18]
	{ .l0 = 1, .r0 = 16, .ncol = 4, .xadj = -15, .pos = 222 }, // 46 [12]
	{ .l0 = 0, .r0 = 14, .ncol = 7, .xadj = -14, .pos = 227 }, // 47 [21]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 235 }, // 48 [32]
	{ .l0 = 2, .r0 = 10, .ncol = 9, .xadj = -9, .pos = 260 }, // 49 [26]
	{ .l0 = 1, .r0 = 10, .ncol = 10, .xadj = -9, .pos = 279 }, // 50 [29]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 303 }, // 51 [32]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 331 }, // 52 [32]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 353 }, // 53 [32]
	{ .l0 = 1, .r0 = 10, .ncol = 10, .xadj = -9, .pos = 380 }, // 54 [29]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 406 }, // 55 [32]
	{ .l0 = 1, .r0 = 9, .ncol = 11, .xadj = -9, .pos = 425 }, // 56 [32]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 452 }, // 57 [32]
	{ .l0 = 2, .r0 = 15, .ncol = 4, .xadj = -13, .pos = 478 }, // 58 [12]
	{ .l0 = 2, .r0 = 15, .ncol = 4, .xadj = -13, .pos = 487 }, // 59 [12]
	{ .l0 = 1, .r0 = 9, .ncol = 11, .xadj = -7, .pos = 498 }, // 60 [32]
	{ .l0 = 1, .r0 = 9, .ncol = 11, .xadj = -7, .pos = 518 }, // 61 [32]
	{ .l0 = 1, .r0 = 9, .ncol = 11, .xadj = -7, .pos = 541 }, // 62 [32]
	{ .l0 = 1, .r0 = 11, .ncol = 9, .xadj = -9, .pos = 561 }, // 63 [26]
    },
    .data       = {
	0x15, 0x42, 0x3f, 0x4, 0x14, 0x37, 0x4, 0x14, 0x3d, 0x42, 0x50,	// 33
	0xe, 0x8f, 0x1, 0x7e, 0xf8, 0xf8, 0xe, 0x8f, 0x1, 0x7e, 0x80,	// 34
	0x5a, 0x7a, 0x22, 0x7a, 0x27, 0x57, 0x6, 0x37, 0x5, 0x5e, 0x22, 0x7a, 0x27, 0x57, 0x6, 0x37, 0x5, 0x5e, 0x22, 0x7a, 0x22, 0x7a, 0xa0,	// 35
	0x24, 0x2c, 0x4e, 0x2b, 0x42, 0xd, 0x32, 0x39, 0x1d, 0x31, 0x2f, 0x7, 0x6, 0x29, 0x25, 0x29, 0x3a, 0x25, 0x1a, 0x3c, 0x1f, 0x1, 0x4c, 0x1f, 0x8d, 0x48,	// 36
	0x24, 0x96, 0x87, 0x7b, 0x1a, 0x7a, 0x29, 0x3a, 0x31, 0x29, 0x34, 0x32, 0x12, 0x2c, 0x4b, 0x2c, 0x59, 0x2c, 0x69, 0x1c, 0x1c, 0x41, 0xc, 0x26, 0x3c, 0x2f, 0x33, 0x33, 0x1a, 0x32, 0x3a, 0x29, 0x79, 0x29, 0x82, 0x12, 0x93, 0x50,	// 37
	0x5d, 0x8f, 0x7f, 0x2, 0x6b, 0x1c, 0x46, 0x33, 0x3f, 0x3a, 0x37, 0x2, 0x32, 0x32, 0x1e, 0x1b, 0x31, 0x27, 0x12, 0x3a, 0x12, 0x17, 0x46, 0x1e, 0x4c, 0x2e, 0x69, 0x1f, 0x62, 0xa, 0x14, 0x64, 0x23, 0x62, 0x32, 0x69, 0x39, 0x40,	// 38
	0xe, 0x8f, 0x1, 0x7e, 0x98,	// 39
	0x47, 0x6f, 0x6, 0x47, 0x7, 0x3, 0x2c, 0x5c, 0x1a, 0x8a, 0x30,	// 40
	0xa, 0x8a, 0x1b, 0x6b, 0x2f, 0x7, 0x3, 0x47, 0x6, 0x6f, 0x68,	// 41
	0x21, 0x19, 0x8b, 0xb, 0x8a, 0xa, 0x9b, 0x87, 0x4, 0x67, 0x4, 0x83, 0x9a, 0xa, 0x8b, 0xb, 0x89, 0x19, 0x80,	// 42
	0x5a, 0xaa, 0xaa, 0xaa, 0xaa, 0x87, 0x5, 0x5f, 0x5, 0x82, 0xaa, 0xaa, 0xaa, 0xaa, 0x70,	// 43
	0x7a, 0x22, 0x74, 0xb, 0x7f, 0x8c, 0x40,	// 44
	0x53, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0x80,	// 45
	0x7a, 0xa4, 0x9c, 0xa2, 0x50,	// 46
	0x82, 0x95, 0x7d, 0x7d, 0x7d, 0x7d, 0x92, 0xd8,	// 47
	0x36, 0x7f, 0x4, 0x57, 0x7, 0x1, 0x47, 0x7, 0x1, 0x3a, 0x6a, 0x31, 0x79, 0x32, 0x6a, 0x3f, 0x7, 0x1, 0x47, 0x7, 0x1, 0x57, 0x4, 0x76, 0x70,	// 48
	0x19, 0x69, 0x41, 0x69, 0x3a, 0x62, 0x3f, 0x7, 0x2, 0x37, 0x7, 0x3, 0x37, 0x7, 0x3, 0xaa, 0xb1, 0xb1, 0x30,	// 49
	0x22, 0x52, 0x42, 0x53, 0x3a, 0x54, 0x33, 0x4d, 0x33, 0x3b, 0xb, 0x34, 0x24, 0x13, 0x37, 0x3, 0x23, 0x3f, 0x1, 0x2b, 0x45, 0x3b, 0x94, 0x40,	// 50
	0x21, 0x52, 0x4a, 0x4c, 0x3a, 0x54, 0x39, 0x2a, 0x2b, 0x32, 0x2a, 0x32, 0x32, 0x2a, 0x39, 0x33, 0x1c, 0x2a, 0x37, 0x4, 0x1a, 0x46, 0xf, 0x1, 0x4b, 0x1f, 0x8d, 0x58,	// 51
	0x54, 0x95, 0x83, 0x12, 0x7b, 0x1a, 0x72, 0x2a, 0x63, 0x32, 0x5f, 0x7, 0x2, 0x37, 0x7, 0x3, 0x37, 0x7, 0x3, 0x8a, 0xaa, 0x60,	// 52
	0x7a, 0x64, 0x24, 0x47, 0x24, 0x34, 0x13, 0x2b, 0x33, 0x1b, 0x32, 0x33, 0x1c, 0x31, 0x33, 0x1c, 0x2a, 0x33, 0x1d, 0x1a, 0x3b, 0x27, 0x2, 0x3b, 0x2e, 0x49, 0xc0,	// 53
	0x4d, 0x7f, 0x3, 0x5f, 0x6, 0x4f, 0x7, 0x1, 0x44, 0x11, 0x32, 0x3b, 0x19, 0x41, 0x3a, 0x22, 0x32, 0x32, 0x2f, 0x2, 0x3a, 0x37, 0x1, 0x39, 0x46, 0x48,	// 54
	0x22, 0x94, 0x9b, 0xa3, 0x62, 0x33, 0x4d, 0x33, 0x37, 0x1, 0x33, 0x1f, 0x1, 0x4b, 0xe, 0x6f, 0x84, 0x9a, 0xb8,	// 55
	0x64, 0x55, 0x17, 0x47, 0xf, 0x3f, 0x3, 0x2a, 0x32, 0x1c, 0x39, 0x31, 0x2c, 0x31, 0x32, 0x25, 0x29, 0x37, 0x5, 0x1a, 0x3d, 0x17, 0x1, 0x4b, 0x27, 0x8c, 0x58,	// 56
	0x2c, 0x8f, 0x39, 0x3f, 0x2, 0x31, 0x3f, 0x3, 0x22, 0x32, 0x3a, 0x22, 0x31, 0x49, 0x1a, 0x3a, 0x41, 0xc, 0x43, 0x2e, 0x4f, 0x6, 0x5f, 0x4, 0x77, 0x70,	// 57
	0x3a, 0x32, 0x64, 0x24, 0x5c, 0x24, 0x62, 0x32, 0x50,	// 58
	0x3a, 0x32, 0x22, 0x34, 0x24, 0xb, 0x3c, 0x27, 0x4a, 0x34, 0x40,	// 59
	0x5a, 0xaa, 0xa4, 0x92, 0x12, 0x8a, 0x12, 0x83, 0x13, 0x7a, 0x22, 0x73, 0x23, 0x6a, 0x32, 0x63, 0x33, 0x5a, 0x42, 0x40,	// 60
	0x4a, 0x12, 0x8a, 0x12, 0x8a, 0x12, 0x8a, 0x12, 0x8a, 0x12, 0x8a, 0x12, 0x8a, 0x12, 0x8a, 0x12, 0x8a, 0x12, 0x8a, 0x12, 0x8a, 0x12, 0x58,	// 61
	0x32, 0x42, 0x5b, 0x33, 0x62, 0x32, 0x6b, 0x23, 0x72, 0x22, 0x7b, 0x13, 0x82, 0x12, 0x8a, 0x12, 0x94, 0xa2, 0xaa, 0x68,	// 62
	0x1a, 0xa4, 0x94, 0x52, 0x39, 0x3b, 0x14, 0x31, 0x2d, 0x14, 0x32, 0x1c, 0x2a, 0x3f, 0x1, 0x86, 0x94, 0x88,	// 63

    }
};
