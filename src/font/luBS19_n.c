
// file: font/luBS19.bdf
// font: -B&H-Lucida-Bold-R-Normal-Sans-19-190-75-75-P-122-ISO10646-1

#include <font.h>

const struct Font font_luBS19_n = {
    .type       = 1,
    .name	= "luBS19_n",
    .height	= 21,
    .width	= 17,
    .lineheight = 21,
    .bytescol	= 4,
    .numcol     = 17,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 12, .ncol = 3, .xadj = -10, .pos = 0 }, // 33 [8]
	{ .l0 = 1, .r0 = 7, .ncol = 9, .xadj = -7, .pos = 9 }, // 34 [24]
	{ .l0 = 1, .r0 = 4, .ncol = 12, .xadj = -4, .pos = 18 }, // 35 [32]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 45 }, // 36 [27]
	{ .l0 = 1, .r0 = 0, .ncol = 16, .xadj = 0, .pos = 70 }, // 37 [42]
	{ .l0 = 1, .r0 = 2, .ncol = 14, .xadj = -2, .pos = 103 }, // 38 [37]
	{ .l0 = 1, .r0 = 12, .ncol = 4, .xadj = -12, .pos = 133 }, // 39 [11]
	{ .l0 = 1, .r0 = 11, .ncol = 5, .xadj = -10, .pos = 138 }, // 40 [14]
	{ .l0 = 1, .r0 = 11, .ncol = 5, .xadj = -10, .pos = 148 }, // 41 [14]
	{ .l0 = 1, .r0 = 9, .ncol = 7, .xadj = -8, .pos = 158 }, // 42 [19]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 170 }, // 43 [27]
	{ .l0 = 1, .r0 = 12, .ncol = 4, .xadj = -10, .pos = 183 }, // 44 [11]
	{ .l0 = 1, .r0 = 12, .ncol = 4, .xadj = -12, .pos = 190 }, // 45 [11]
	{ .l0 = 1, .r0 = 12, .ncol = 4, .xadj = -10, .pos = 195 }, // 46 [11]
	{ .l0 = 0, .r0 = 6, .ncol = 11, .xadj = -6, .pos = 200 }, // 47 [29]
	{ .l0 = 1, .r0 = 4, .ncol = 12, .xadj = -4, .pos = 212 }, // 48 [32]
	{ .l0 = 3, .r0 = 9, .ncol = 5, .xadj = -4, .pos = 235 }, // 49 [14]
	{ .l0 = 1, .r0 = 6, .ncol = 10, .xadj = -4, .pos = 244 }, // 50 [27]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 269 }, // 51 [27]
	{ .l0 = 1, .r0 = 5, .ncol = 11, .xadj = -4, .pos = 296 }, // 52 [29]
	{ .l0 = 3, .r0 = 5, .ncol = 9, .xadj = -4, .pos = 315 }, // 53 [24]
	{ .l0 = 1, .r0 = 5, .ncol = 11, .xadj = -4, .pos = 338 }, // 54 [29]
	{ .l0 = 2, .r0 = 5, .ncol = 10, .xadj = -4, .pos = 365 }, // 55 [27]
	{ .l0 = 1, .r0 = 5, .ncol = 11, .xadj = -4, .pos = 383 }, // 56 [29]
	{ .l0 = 1, .r0 = 5, .ncol = 11, .xadj = -4, .pos = 409 }, // 57 [29]
	{ .l0 = 2, .r0 = 12, .ncol = 3, .xadj = -10, .pos = 436 }, // 58 [8]
	{ .l0 = 2, .r0 = 12, .ncol = 3, .xadj = -10, .pos = 443 }, // 59 [8]
	{ .l0 = 1, .r0 = 5, .ncol = 11, .xadj = -4, .pos = 452 }, // 60 [29]
	{ .l0 = 1, .r0 = 5, .ncol = 11, .xadj = -4, .pos = 470 }, // 61 [29]
	{ .l0 = 1, .r0 = 5, .ncol = 11, .xadj = -4, .pos = 493 }, // 62 [29]
	{ .l0 = 1, .r0 = 7, .ncol = 9, .xadj = -6, .pos = 511 }, // 63 [24]
    },
    .data       = {
	0x1e, 0x32, 0x3f, 0x3, 0x12, 0x3f, 0x3, 0x12, 0x28,	// 33
	0x1b, 0x95, 0x85, 0x82, 0xf8, 0xf5, 0x85, 0x83, 0x90,	// 34
	0x62, 0x72, 0x1a, 0x11, 0x5a, 0x1d, 0x5f, 0x2, 0x4f, 0x3, 0x56, 0x1a, 0x11, 0x39, 0x1a, 0x1d, 0x5f, 0x3, 0x47, 0x3, 0x56, 0x1a, 0x51, 0x1a, 0x1a, 0x72, 0x80,	// 35
	0x32, 0x33, 0x45, 0x2b, 0x3f, 0x2a, 0x3f, 0x1, 0x22, 0x25, 0x17, 0x6, 0xf, 0x5, 0x1d, 0x22, 0x24, 0xb, 0x3a, 0x27, 0x1, 0x3b, 0x26, 0x8b, 0x60,	// 36
	0x2c, 0x7f, 0x1, 0x29, 0x3a, 0x22, 0x29, 0x3a, 0x22, 0x1b, 0x3f, 0x1, 0x13, 0x54, 0x1b, 0x84, 0x83, 0x8b, 0x84, 0x83, 0x24, 0x4b, 0x26, 0x3b, 0x2a, 0x12, 0x39, 0x3a, 0x12, 0x39, 0x3e, 0x84, 0x28,	// 37
	0x5c, 0x86, 0x4b, 0x17, 0x4f, 0x1b, 0x3f, 0x2a, 0x3a, 0x15, 0x1a, 0x3a, 0x1d, 0x12, 0x3a, 0x17, 0xa, 0x3a, 0x12, 0x15, 0x4c, 0x25, 0x4b, 0x25, 0x74, 0xa, 0x6c, 0x19, 0x6b, 0x58,	// 38
	0x1b, 0x96, 0x7e, 0x7b, 0x98,	// 39
	0x4e, 0x67, 0x5, 0x47, 0x7, 0x34, 0x44, 0x23, 0x63, 0x38,	// 40
	0x1b, 0x63, 0x24, 0x44, 0x37, 0x7, 0x47, 0x5, 0x66, 0x68,	// 41
	0x29, 0x9a, 0x9, 0x81, 0xc, 0x7a, 0x99, 0xc, 0x82, 0x9, 0x91, 0xa0,	// 42
	0x52, 0x9a, 0x9a, 0x9a, 0x77, 0x5, 0x4f, 0x5, 0x72, 0x9a, 0x9a, 0x9a, 0x78,	// 43
	0x6c, 0x19, 0x6f, 0x1, 0x6f, 0x76, 0x30,	// 44
	0x52, 0x9a, 0x9a, 0x9a, 0x68,	// 45
	0x73, 0x93, 0x93, 0x93, 0x40,	// 46
	0xa1, 0x93, 0x85, 0x75, 0x75, 0x74, 0x75, 0x75, 0x75, 0x83, 0x91, 0x90,	// 47
	0x3e, 0x6f, 0x3, 0x57, 0x5, 0x4a, 0x42, 0x42, 0x52, 0x3a, 0x52, 0x3a, 0x52, 0x3a, 0x52, 0x42, 0x42, 0x4f, 0x5, 0x57, 0x3, 0x6e, 0x60,	// 48
	0x1a, 0x9a, 0x9f, 0x7, 0x3f, 0x7, 0x3f, 0x7, 0x58,	// 49
	0x22, 0x43, 0x3b, 0x3c, 0x3a, 0x3d, 0x3a, 0x3d, 0x3a, 0x33, 0xa, 0x3a, 0x2b, 0x12, 0x3b, 0x1b, 0x1a, 0x3f, 0x1, 0x22, 0x46, 0x2a, 0x4c, 0x32, 0x50,	// 50
	0x22, 0x43, 0x3a, 0x22, 0x22, 0x3a, 0x22, 0x22, 0x3a, 0x22, 0x22, 0x3a, 0x22, 0x22, 0x3a, 0x22, 0x22, 0x3b, 0x14, 0x13, 0x3e, 0xf, 0x45, 0x15, 0x53, 0x23, 0x60,	// 51
	0x53, 0x8c, 0x85, 0x7b, 0xa, 0x73, 0x12, 0x6b, 0x1a, 0x5b, 0x2a, 0x5f, 0x7, 0x3f, 0x7, 0x3f, 0x7, 0x7a, 0x48,	// 52
	0x1f, 0x23, 0x3f, 0x2a, 0x3a, 0x1a, 0x2a, 0x3a, 0x1a, 0x2a, 0x3a, 0x1b, 0x22, 0x3a, 0x1b, 0x1b, 0x3a, 0x27, 0x42, 0x27, 0x42, 0x34, 0x48,	// 53
	0x3e, 0x6f, 0x3, 0x57, 0x5, 0x4b, 0x12, 0x1b, 0x3b, 0x12, 0x2a, 0x3a, 0x1a, 0x2a, 0x3a, 0x1a, 0x2a, 0x3a, 0x1b, 0x1b, 0x3a, 0x1f, 0x1, 0x43, 0x1f, 0x7c, 0x40,	// 54
	0x1a, 0x59, 0x3a, 0x4b, 0x3a, 0x3d, 0x3a, 0x2f, 0x3a, 0x26, 0x4a, 0x1c, 0x62, 0xc, 0x76, 0x7c, 0x8b, 0xa8,	// 55
	0x63, 0x5b, 0x16, 0x4d, 0xf, 0x3f, 0x1, 0x1b, 0x3a, 0x14, 0x22, 0x3a, 0x1b, 0x22, 0x3a, 0x1c, 0x1a, 0x3f, 0x2, 0x13, 0x47, 0x5, 0x53, 0x16, 0x84, 0x38,	// 56
	0x34, 0x7f, 0x1b, 0x47, 0x1, 0x1a, 0x3b, 0x1b, 0x1a, 0x3a, 0x2a, 0x1a, 0x3a, 0x2a, 0x1a, 0x3a, 0x2a, 0x13, 0x3b, 0x1a, 0x13, 0x4f, 0x5, 0x57, 0x3, 0x6e, 0x48,	// 57
	0x3b, 0x23, 0x5b, 0x23, 0x5b, 0x23, 0x28,	// 58
	0x3b, 0x1c, 0x19, 0x3b, 0x1f, 0x1, 0x3b, 0x1e, 0x18,	// 59
	0x51, 0xa2, 0x9a, 0x94, 0x8c, 0x82, 0x12, 0x7a, 0x12, 0x72, 0x22, 0x63, 0x23, 0x5a, 0x32, 0x53, 0x33, 0x28,	// 60
	0x42, 0x1a, 0x72, 0x1a, 0x72, 0x1a, 0x72, 0x1a, 0x72, 0x1a, 0x72, 0x1a, 0x72, 0x1a, 0x72, 0x1a, 0x72, 0x1a, 0x72, 0x1a, 0x72, 0x1a, 0x38,	// 61
	0x2b, 0x33, 0x52, 0x32, 0x5b, 0x23, 0x62, 0x22, 0x72, 0x12, 0x7a, 0x12, 0x84, 0x8c, 0x92, 0x9a, 0xa1, 0x50,	// 62
	0x1b, 0x92, 0x9a, 0x32, 0x12, 0x3a, 0x2b, 0x12, 0x3a, 0x24, 0x12, 0x3b, 0x13, 0x6e, 0x85, 0x8b, 0x80,	// 63

    }
};
