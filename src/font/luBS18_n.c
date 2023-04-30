
// file: font/luBS18.bdf
// font: -B&H-Lucida-Bold-R-Normal-Sans-18-180-75-75-P-120-ISO10646-1

#include <font.h>

const struct Font font_luBS18_n = {
    .type       = 1,
    .name	= "luBS18_n",
    .height	= 17,
    .width	= 17,
    .lineheight = 18,
    .bytescol	= 4,
    .numcol     = 17,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 13, .ncol = 3, .xadj = -12, .pos = 0 }, // 33 [7]
	{ .l0 = 1, .r0 = 8, .ncol = 8, .xadj = -7, .pos = 8 }, // 34 [17]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 16 }, // 35 [22]
	{ .l0 = 2, .r0 = 6, .ncol = 9, .xadj = -4, .pos = 35 }, // 36 [20]
	{ .l0 = 1, .r0 = 0, .ncol = 16, .xadj = 0, .pos = 57 }, // 37 [34]
	{ .l0 = 1, .r0 = 3, .ncol = 13, .xadj = -2, .pos = 92 }, // 38 [28]
	{ .l0 = 1, .r0 = 13, .ncol = 3, .xadj = -12, .pos = 118 }, // 39 [7]
	{ .l0 = 2, .r0 = 10, .ncol = 5, .xadj = -10, .pos = 122 }, // 40 [11]
	{ .l0 = 0, .r0 = 12, .ncol = 5, .xadj = -10, .pos = 132 }, // 41 [11]
	{ .l0 = 1, .r0 = 8, .ncol = 8, .xadj = -8, .pos = 142 }, // 42 [17]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 157 }, // 43 [22]
	{ .l0 = 1, .r0 = 13, .ncol = 3, .xadj = -12, .pos = 170 }, // 44 [7]
	{ .l0 = 1, .r0 = 12, .ncol = 4, .xadj = -12, .pos = 175 }, // 45 [9]
	{ .l0 = 1, .r0 = 13, .ncol = 3, .xadj = -12, .pos = 180 }, // 46 [7]
	{ .l0 = 0, .r0 = 6, .ncol = 11, .xadj = -6, .pos = 184 }, // 47 [24]
	{ .l0 = 1, .r0 = 5, .ncol = 11, .xadj = -4, .pos = 196 }, // 48 [24]
	{ .l0 = 3, .r0 = 9, .ncol = 5, .xadj = -4, .pos = 217 }, // 49 [11]
	{ .l0 = 2, .r0 = 6, .ncol = 9, .xadj = -4, .pos = 226 }, // 50 [20]
	{ .l0 = 2, .r0 = 6, .ncol = 9, .xadj = -4, .pos = 248 }, // 51 [20]
	{ .l0 = 1, .r0 = 5, .ncol = 11, .xadj = -4, .pos = 271 }, // 52 [24]
	{ .l0 = 2, .r0 = 6, .ncol = 9, .xadj = -4, .pos = 290 }, // 53 [20]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 313 }, // 54 [22]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 337 }, // 55 [22]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 354 }, // 56 [22]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 379 }, // 57 [22]
	{ .l0 = 1, .r0 = 13, .ncol = 3, .xadj = -12, .pos = 403 }, // 58 [7]
	{ .l0 = 1, .r0 = 13, .ncol = 3, .xadj = -12, .pos = 410 }, // 59 [7]
	{ .l0 = 1, .r0 = 6, .ncol = 10, .xadj = -4, .pos = 418 }, // 60 [22]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 435 }, // 61 [22]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 456 }, // 62 [22]
	{ .l0 = 1, .r0 = 7, .ncol = 9, .xadj = -6, .pos = 473 }, // 63 [20]
    },
    .data       = {
	0x15, 0x2b, 0x27, 0x1, 0x13, 0x26, 0x23, 0x38,	// 33
	0xd, 0x64, 0x6a, 0xf8, 0x95, 0x64, 0x6a, 0x70,	// 34
	0x4a, 0x5a, 0x16, 0x3f, 0x3, 0x27, 0x2, 0x45, 0x12, 0x5a, 0x16, 0x3f, 0x3, 0x27, 0x2, 0x45, 0x12, 0x5a, 0x80,	// 35
	0x23, 0x2a, 0x35, 0x23, 0x27, 0x22, 0x22, 0x17, 0x7, 0x1, 0x1b, 0x1f, 0x7, 0x1, 0x12, 0x22, 0x27, 0x23, 0x25, 0x32, 0x2b, 0x58,	// 36
	0x23, 0x6d, 0x31, 0x23, 0xb, 0x22, 0x22, 0x1a, 0x1a, 0x2b, 0xb, 0x12, 0x3d, 0x12, 0x4b, 0x12, 0x72, 0x72, 0x72, 0x13, 0x4a, 0x15, 0x3a, 0x13, 0xb, 0x2a, 0x1a, 0x1a, 0x22, 0x23, 0xb, 0x21, 0x35, 0x6b, 0x20,	// 37
	0x4c, 0x66, 0x3a, 0x16, 0x36, 0x1b, 0x27, 0x22, 0x22, 0x14, 0x1a, 0x22, 0x1d, 0xa, 0x26, 0xe, 0x2c, 0x1c, 0x3a, 0x2c, 0x5e, 0x4c, 0x12, 0x4b, 0x1a, 0x28,	// 38
	0xd, 0x64, 0x6a, 0x98,	// 39
	0x36, 0x4f, 0x3, 0x2f, 0x7, 0x14, 0x44, 0xa, 0x62, 0x18,	// 40
	0xa, 0x62, 0xc, 0x44, 0x17, 0x7, 0x2f, 0x3, 0x4e, 0x40,	// 41
	0x22, 0x7a, 0xa, 0x69, 0xa, 0x53, 0x9, 0x63, 0x9, 0x79, 0xa, 0x62, 0xa, 0x62, 0x58,	// 42
	0x42, 0x7a, 0x7a, 0x7a, 0x5f, 0x3, 0x3f, 0x3, 0x5a, 0x7a, 0x7a, 0x7a, 0x68,	// 43
	0x63, 0x9, 0x65, 0x64, 0x30,	// 44
	0x42, 0x7a, 0x7a, 0x7a, 0x58,	// 45
	0x63, 0x73, 0x73, 0x38,	// 46
	0x7a, 0x6c, 0x65, 0x55, 0x55, 0x56, 0x55, 0x55, 0x55, 0x64, 0x6a, 0x98,	// 47
	0x2f, 0x47, 0x4, 0x37, 0x4, 0x2b, 0x3b, 0x22, 0x4a, 0x22, 0x4a, 0x22, 0x4a, 0x23, 0x3b, 0x2f, 0x4, 0x37, 0x4, 0x47, 0x50,	// 48
	0x1a, 0x7a, 0x7f, 0x5, 0x27, 0x6, 0x27, 0x6, 0x28,	// 49
	0x1a, 0x34, 0x23, 0x2d, 0x22, 0x2e, 0x22, 0x23, 0xb, 0x22, 0x22, 0x13, 0x22, 0x1b, 0x13, 0x27, 0x1b, 0x2d, 0x23, 0x33, 0x2b, 0x48,	// 50
	0x1a, 0x3a, 0x2b, 0x3b, 0x22, 0x1a, 0x22, 0x22, 0x1a, 0x22, 0x22, 0x1a, 0x22, 0x22, 0x14, 0x13, 0x25, 0xe, 0x34, 0x15, 0x3a, 0x23, 0x58,	// 51
	0x43, 0x6c, 0x62, 0xa, 0x5a, 0x12, 0x52, 0x1a, 0x4a, 0x22, 0x47, 0x6, 0x27, 0x6, 0x27, 0x6, 0x5a, 0x7a, 0x58,	// 52
	0x17, 0x1a, 0x2f, 0x1b, 0x23, 0x12, 0x22, 0x23, 0x12, 0x22, 0x23, 0x13, 0x1a, 0x23, 0x13, 0x1a, 0x23, 0x1e, 0x2b, 0x1e, 0x2b, 0x24, 0x58,	// 53
	0x2f, 0x47, 0x4, 0x37, 0x4, 0x2a, 0x1a, 0x1b, 0x22, 0x12, 0x2a, 0x22, 0x12, 0x2a, 0x22, 0x13, 0x22, 0x23, 0xf, 0x2, 0x2a, 0x17, 0x5d, 0x50,	// 54
	0x13, 0x73, 0x3b, 0x23, 0x2d, 0x23, 0x26, 0x23, 0x1c, 0x3b, 0x13, 0x4b, 0xb, 0x56, 0x5d, 0x64, 0x88,	// 55
	0x23, 0x1b, 0x3d, 0xd, 0x2f, 0x6, 0x22, 0x13, 0x22, 0x22, 0x1b, 0x1a, 0x22, 0x1b, 0x1a, 0x22, 0x1c, 0x12, 0x25, 0xf, 0x2c, 0x15, 0x3a, 0x23, 0x50,	// 56
	0x25, 0x5f, 0x12, 0x2f, 0x2, 0xb, 0x22, 0x23, 0x12, 0x22, 0x2a, 0x12, 0x22, 0x2a, 0x12, 0x23, 0x1a, 0x1a, 0x2f, 0x4, 0x37, 0x4, 0x47, 0x58,	// 57
	0x2b, 0x23, 0x3b, 0x23, 0x3b, 0x23, 0x38,	// 58
	0x2b, 0x23, 0x9, 0x2b, 0x25, 0x2b, 0x24, 0x30,	// 59
	0x42, 0x7a, 0x74, 0x6c, 0x62, 0x12, 0x5a, 0x12, 0x52, 0x22, 0x4a, 0x22, 0x42, 0x32, 0x3a, 0x32, 0x48,	// 60
	0x32, 0x12, 0x5a, 0x12, 0x5a, 0x12, 0x5a, 0x12, 0x5a, 0x12, 0x5a, 0x12, 0x5a, 0x12, 0x5a, 0x12, 0x5a, 0x12, 0x5a, 0x12, 0x58,	// 61
	0x22, 0x32, 0x3a, 0x32, 0x42, 0x22, 0x4a, 0x22, 0x52, 0x12, 0x5a, 0x12, 0x64, 0x6c, 0x72, 0x7a, 0x68,	// 62
	0x1a, 0x73, 0x72, 0x22, 0x13, 0x22, 0x1b, 0x13, 0x22, 0x1a, 0x1b, 0x22, 0x12, 0x5e, 0x64, 0x72, 0x90,	// 63

    }
};
