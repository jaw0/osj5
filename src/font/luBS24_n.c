
// file: font/luBS24.bdf
// font: -B&H-Lucida-Bold-R-Normal-Sans-24-240-75-75-P-152-ISO10646-1

#include <font.h>

const struct Font font_luBS24_n = {
    .type       = 1,
    .name	= "luBS24_n",
    .height	= 25,
    .width	= 22,
    .lineheight = 25,
    .bytescol	= 4,
    .numcol     = 22,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 15, .ncol = 5, .xadj = -14, .pos = 0 }, // 33 [16]
	{ .l0 = 1, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 16 }, // 34 [35]
	{ .l0 = 1, .r0 = 6, .ncol = 15, .xadj = -6, .pos = 34 }, // 35 [47]
	{ .l0 = 2, .r0 = 7, .ncol = 13, .xadj = -6, .pos = 68 }, // 36 [41]
	{ .l0 = 0, .r0 = 1, .ncol = 21, .xadj = 0, .pos = 102 }, // 37 [66]
	{ .l0 = 0, .r0 = 4, .ncol = 18, .xadj = -3, .pos = 148 }, // 38 [57]
	{ .l0 = 1, .r0 = 16, .ncol = 5, .xadj = -16, .pos = 192 }, // 39 [16]
	{ .l0 = 1, .r0 = 14, .ncol = 7, .xadj = -13, .pos = 201 }, // 40 [22]
	{ .l0 = 1, .r0 = 14, .ncol = 7, .xadj = -13, .pos = 218 }, // 41 [22]
	{ .l0 = 1, .r0 = 12, .ncol = 9, .xadj = -11, .pos = 235 }, // 42 [29]
	{ .l0 = 1, .r0 = 6, .ncol = 15, .xadj = -6, .pos = 253 }, // 43 [47]
	{ .l0 = 2, .r0 = 15, .ncol = 5, .xadj = -14, .pos = 272 }, // 44 [16]
	{ .l0 = 1, .r0 = 16, .ncol = 5, .xadj = -15, .pos = 282 }, // 45 [16]
	{ .l0 = 2, .r0 = 15, .ncol = 5, .xadj = -14, .pos = 288 }, // 46 [16]
	{ .l0 = 0, .r0 = 8, .ncol = 14, .xadj = -8, .pos = 294 }, // 47 [44]
	{ .l0 = 1, .r0 = 6, .ncol = 15, .xadj = -6, .pos = 309 }, // 48 [47]
	{ .l0 = 4, .r0 = 11, .ncol = 7, .xadj = -6, .pos = 342 }, // 49 [22]
	{ .l0 = 1, .r0 = 8, .ncol = 13, .xadj = -6, .pos = 360 }, // 50 [41]
	{ .l0 = 2, .r0 = 7, .ncol = 13, .xadj = -6, .pos = 393 }, // 51 [41]
	{ .l0 = 1, .r0 = 6, .ncol = 15, .xadj = -6, .pos = 427 }, // 52 [47]
	{ .l0 = 3, .r0 = 7, .ncol = 12, .xadj = -6, .pos = 458 }, // 53 [38]
	{ .l0 = 1, .r0 = 7, .ncol = 14, .xadj = -6, .pos = 493 }, // 54 [44]
	{ .l0 = 3, .r0 = 6, .ncol = 13, .xadj = -6, .pos = 530 }, // 55 [41]
	{ .l0 = 1, .r0 = 7, .ncol = 14, .xadj = -6, .pos = 555 }, // 56 [44]
	{ .l0 = 1, .r0 = 7, .ncol = 14, .xadj = -6, .pos = 591 }, // 57 [44]
	{ .l0 = 2, .r0 = 15, .ncol = 5, .xadj = -14, .pos = 628 }, // 58 [16]
	{ .l0 = 2, .r0 = 15, .ncol = 5, .xadj = -14, .pos = 639 }, // 59 [16]
	{ .l0 = 1, .r0 = 7, .ncol = 14, .xadj = -6, .pos = 654 }, // 60 [44]
	{ .l0 = 1, .r0 = 7, .ncol = 14, .xadj = -6, .pos = 676 }, // 61 [44]
	{ .l0 = 1, .r0 = 7, .ncol = 14, .xadj = -6, .pos = 705 }, // 62 [44]
	{ .l0 = 1, .r0 = 9, .ncol = 12, .xadj = -8, .pos = 727 }, // 63 [38]
    },
    .data       = {
	0x1f, 0x1, 0x33, 0x47, 0x5, 0x13, 0x47, 0x5, 0x13, 0x47, 0x5, 0x13, 0x47, 0x1, 0x33, 0x40,	// 33
	0x14, 0xaf, 0x1, 0x8f, 0x1, 0x8f, 0x1, 0x8a, 0xf8, 0x8c, 0xaf, 0x1, 0x8f, 0x1, 0x8f, 0x1, 0x8c, 0xc0,	// 34
	0x6a, 0x8a, 0x22, 0x8a, 0x22, 0x13, 0x62, 0x1f, 0x1, 0x67, 0x3, 0x6f, 0x3, 0x6e, 0x22, 0x6a, 0x12, 0x22, 0x13, 0x62, 0x27, 0x67, 0x4, 0x67, 0x3, 0x6e, 0x22, 0x6b, 0xa, 0x22, 0x8a, 0x21, 0x92, 0x88,	// 35
	0x83, 0x5d, 0x3b, 0x4f, 0x33, 0x47, 0x1, 0x33, 0x47, 0x2, 0x2b, 0x2e, 0x17, 0x7, 0x1, 0x17, 0x7, 0x7, 0x2, 0x17, 0x7, 0x1e, 0x2b, 0x25, 0x13, 0x43, 0x2f, 0x2, 0x43, 0x37, 0x4b, 0x3e, 0xa3, 0x58,	// 36
	0x2c, 0xa6, 0x97, 0x1, 0x41, 0x43, 0x13, 0x3a, 0x43, 0x13, 0x33, 0x43, 0x13, 0x25, 0x47, 0x1, 0x1d, 0x56, 0x1d, 0x64, 0x1c, 0x9d, 0x9d, 0x9d, 0x9c, 0x15, 0x6c, 0x17, 0x55, 0x17, 0x2, 0x45, 0x1b, 0x1b, 0x43, 0x2b, 0x1b, 0x42, 0x33, 0x1b, 0x41, 0x3f, 0x2, 0x8f, 0x9d, 0x50,	// 37
	0x6c, 0xa6, 0x97, 0x1, 0x5b, 0x17, 0x2, 0x57, 0x7, 0x2, 0x47, 0x2, 0x24, 0x47, 0x3, 0x23, 0x47, 0x4, 0x1b, 0x43, 0x17, 0x1, 0xb, 0x43, 0x17, 0x5, 0x47, 0x7, 0x2, 0x4f, 0xf, 0x1, 0x55, 0x27, 0x53, 0x36, 0x7f, 0x3, 0x7e, 0x12, 0x7d, 0x21, 0x7b, 0x90,	// 38
	0x14, 0xaf, 0x1, 0x8f, 0x1, 0x8f, 0x1, 0x8c, 0xb0,	// 39
	0x57, 0x7f, 0x6, 0x5f, 0x7, 0x1, 0x4f, 0x7, 0x3, 0x3f, 0x7, 0x5, 0x2e, 0x4e, 0x1c, 0x7c, 0x8,	// 40
	0x14, 0x7c, 0x1e, 0x4e, 0x2f, 0x7, 0x5, 0x3f, 0x7, 0x3, 0x4f, 0x7, 0x1, 0x5f, 0x6, 0x7f, 0x48,	// 41
	0x32, 0xac, 0xa, 0xa2, 0xb, 0x82, 0x9, 0xb, 0x8b, 0xb2, 0x9, 0xc, 0x9a, 0xa, 0x94, 0xa, 0xa2, 0xc0,	// 42
	0x5b, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0x8f, 0x7, 0x5f, 0x7, 0x5f, 0x7, 0x83, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0x60,	// 43
	0x7d, 0x12, 0x85, 0xb, 0x87, 0x1, 0x8f, 0x1, 0x8e, 0x38,	// 44
	0x5b, 0xb3, 0xb3, 0xb3, 0xb3, 0x70,	// 45
	0x7d, 0xa5, 0xa5, 0xa5, 0xa5, 0x40,	// 46
	0xb9, 0xb3, 0xa5, 0x97, 0x87, 0x86, 0x8e, 0x87, 0x87, 0x87, 0x87, 0x95, 0xa3, 0xb1, 0xc0,	// 47
	0x47, 0x87, 0x4, 0x6f, 0x6, 0x5f, 0x7, 0x1, 0x57, 0x7, 0x1, 0x4c, 0x4c, 0x43, 0x5b, 0x43, 0x5b, 0x43, 0x5b, 0x44, 0x4c, 0x4f, 0x7, 0x1, 0x57, 0x7, 0x1, 0x5f, 0x6, 0x6f, 0x4, 0x87, 0x58,	// 48
	0x1b, 0xb3, 0xb7, 0x7, 0x3, 0x47, 0x7, 0x3, 0x47, 0x7, 0x3, 0x47, 0x7, 0x3, 0x47, 0x7, 0x3, 0x30,	// 49
	0x23, 0x4c, 0x4b, 0x45, 0x43, 0x4d, 0x43, 0x46, 0x43, 0x3f, 0x43, 0x34, 0xb, 0x43, 0x2c, 0x13, 0x44, 0x1d, 0x13, 0x47, 0x4, 0x1b, 0x47, 0x3, 0x23, 0x4f, 0x1, 0x2b, 0x56, 0x33, 0x5c, 0x3b, 0x40,	// 50
	0x23, 0x4b, 0x52, 0x54, 0x43, 0x23, 0x23, 0x43, 0x23, 0x23, 0x43, 0x23, 0x23, 0x43, 0x23, 0x23, 0x44, 0x14, 0x23, 0x47, 0x4, 0x14, 0x47, 0x7, 0x3, 0x4f, 0x7, 0x1, 0x56, 0x17, 0x5c, 0x26, 0xa3, 0x58,	// 51
	0x64, 0x9e, 0x97, 0x8f, 0x1, 0x85, 0xb, 0x7d, 0x13, 0x74, 0x23, 0x6c, 0x2b, 0x67, 0x7, 0x3, 0x47, 0x7, 0x3, 0x47, 0x7, 0x3, 0x47, 0x7, 0x3, 0x47, 0x7, 0x3, 0x93, 0xb3, 0x50,	// 52
	0x1f, 0x2, 0x23, 0x4f, 0x2, 0x2b, 0x47, 0x2, 0x2b, 0x43, 0x1b, 0x2b, 0x43, 0x1b, 0x2b, 0x43, 0x1c, 0x23, 0x43, 0x1c, 0x1c, 0x43, 0x27, 0x3, 0x43, 0x27, 0x2, 0x4b, 0x27, 0x2, 0x4b, 0x2f, 0x53, 0x3c, 0x60,	// 53
	0x47, 0x87, 0x4, 0x6f, 0x6, 0x5f, 0x7, 0x1, 0x57, 0x7, 0x2, 0x45, 0x13, 0x1c, 0x44, 0x13, 0x2b, 0x43, 0x1b, 0x2b, 0x43, 0x1c, 0x1c, 0x43, 0x1f, 0x4, 0x43, 0x1f, 0x3, 0x4b, 0x27, 0x2, 0x53, 0x1f, 0x1, 0x9d, 0x50,	// 54
	0x1b, 0xb3, 0x5b, 0x43, 0x4d, 0x43, 0x3f, 0x43, 0x37, 0x1, 0x43, 0x27, 0x3, 0x43, 0x1f, 0x63, 0x16, 0x73, 0xd, 0x87, 0x1, 0x8f, 0x95, 0xa4, 0xa8,	// 55
	0x74, 0x64, 0x26, 0x56, 0x17, 0x57, 0x7, 0x2, 0x47, 0x7, 0x3, 0x43, 0x15, 0x1c, 0x43, 0x1b, 0x2b, 0x43, 0x1c, 0x23, 0x44, 0x14, 0x23, 0x47, 0x4, 0x14, 0x4f, 0x7, 0x1, 0x56, 0xf, 0x1, 0x5c, 0x1e, 0xa4, 0x50,	// 56
	0x35, 0x9f, 0x1, 0x1b, 0x57, 0x2, 0x23, 0x4f, 0x3, 0x1b, 0x47, 0x4, 0x1b, 0x44, 0x1c, 0x1b, 0x43, 0x2b, 0x1b, 0x43, 0x2a, 0x1c, 0x44, 0x1b, 0x15, 0x47, 0x7, 0x2, 0x57, 0x7, 0x1, 0x5f, 0x6, 0x6f, 0x4, 0x87, 0x60,	// 57
	0x3d, 0x1d, 0x65, 0x1d, 0x65, 0x1d, 0x65, 0x1d, 0x65, 0x1d, 0x40,	// 58
	0x3d, 0x1d, 0x12, 0x45, 0x1d, 0xb, 0x45, 0x1f, 0x1, 0x4d, 0x1f, 0x1, 0x4d, 0x1e, 0x38,	// 59
	0x61, 0xc2, 0xba, 0xb4, 0xac, 0xa6, 0x9e, 0x93, 0x13, 0x8b, 0x13, 0x83, 0x23, 0x7b, 0x23, 0x73, 0x33, 0x6b, 0x33, 0x63, 0x43, 0x38,	// 60
	0x4b, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x83, 0x1b, 0x48,	// 61
	0x33, 0x43, 0x63, 0x33, 0x6b, 0x33, 0x73, 0x23, 0x7b, 0x23, 0x83, 0x13, 0x8b, 0x13, 0x96, 0x9e, 0xa4, 0xac, 0xb2, 0xba, 0xc1, 0x68,	// 62
	0x23, 0xab, 0xb3, 0xb3, 0x3a, 0x13, 0x43, 0x33, 0x13, 0x43, 0x2c, 0x13, 0x44, 0x1d, 0x13, 0x47, 0x5, 0x13, 0x47, 0x2, 0x8f, 0x96, 0xa4, 0xa0,	// 63

    }
};
