
// file: font/helvR18.bdf
// font: -Adobe-Helvetica-Medium-R-Normal--18-180-75-75-P-98-ISO10646-1

#include <font.h>

const struct Font font_helvR18_n = {
    .type       = 1,
    .name	= "helvR18_n",
    .height	= 18,
    .width	= 16,
    .lineheight = 18,
    .bytescol	= 4,
    .numcol     = 16,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 12, .ncol = 2, .xadj = -10, .pos = 0 }, // 33 [5]
	{ .l0 = 0, .r0 = 11, .ncol = 5, .xadj = -11, .pos = 7 }, // 34 [12]
	{ .l0 = 0, .r0 = 6, .ncol = 10, .xadj = -6, .pos = 13 }, // 35 [23]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 30 }, // 36 [21]
	{ .l0 = 1, .r0 = 1, .ncol = 14, .xadj = 0, .pos = 53 }, // 37 [32]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -3, .pos = 78 }, // 38 [27]
	{ .l0 = 1, .r0 = 14, .ncol = 1, .xadj = -13, .pos = 101 }, // 39 [3]
	{ .l0 = 1, .r0 = 11, .ncol = 4, .xadj = -10, .pos = 103 }, // 40 [9]
	{ .l0 = 1, .r0 = 11, .ncol = 4, .xadj = -10, .pos = 111 }, // 41 [9]
	{ .l0 = 1, .r0 = 10, .ncol = 5, .xadj = -9, .pos = 120 }, // 42 [12]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 128 }, // 43 [18]
	{ .l0 = 1, .r0 = 13, .ncol = 2, .xadj = -11, .pos = 139 }, // 44 [5]
	{ .l0 = 1, .r0 = 10, .ncol = 5, .xadj = -9, .pos = 143 }, // 45 [12]
	{ .l0 = 1, .r0 = 13, .ncol = 2, .xadj = -11, .pos = 149 }, // 46 [5]
	{ .l0 = 0, .r0 = 11, .ncol = 5, .xadj = -11, .pos = 152 }, // 47 [12]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 158 }, // 48 [18]
	{ .l0 = 2, .r0 = 9, .ncol = 5, .xadj = -6, .pos = 173 }, // 49 [12]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 181 }, // 50 [18]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 202 }, // 51 [18]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 222 }, // 52 [21]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 238 }, // 53 [18]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 258 }, // 54 [18]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 279 }, // 55 [18]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 293 }, // 56 [18]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 314 }, // 57 [18]
	{ .l0 = 1, .r0 = 13, .ncol = 2, .xadj = -11, .pos = 335 }, // 58 [5]
	{ .l0 = 1, .r0 = 13, .ncol = 2, .xadj = -11, .pos = 340 }, // 59 [5]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 346 }, // 60 [18]
	{ .l0 = 2, .r0 = 7, .ncol = 7, .xadj = -5, .pos = 361 }, // 61 [16]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 376 }, // 62 [18]
	{ .l0 = 1, .r0 = 8, .ncol = 7, .xadj = -6, .pos = 391 }, // 63 [16]
    },
    .data       = {
	0x7, 0x3, 0x12, 0x27, 0x1, 0x22, 0x40,	// 33
	0x5, 0x6b, 0xf8, 0x15, 0x6b, 0xa8,	// 34
	0x4a, 0x5a, 0x1a, 0x5a, 0x1d, 0x47, 0x45, 0x1a, 0x5a, 0x1d, 0x47, 0x45, 0x1a, 0x5a, 0x1a, 0x5a, 0x80,	// 35
	0x1b, 0x22, 0x45, 0x1b, 0x32, 0x13, 0x1b, 0x2a, 0x1a, 0x22, 0x27, 0x7, 0x2, 0x1a, 0x22, 0x1a, 0x2b, 0x1a, 0x13, 0x32, 0x25, 0x73, 0x60,	// 36
	0x14, 0x6e, 0x62, 0x12, 0x62, 0x12, 0x2a, 0x2e, 0x1c, 0x34, 0x14, 0x64, 0x64, 0x64, 0x1c, 0x33, 0x26, 0x29, 0x32, 0x12, 0x62, 0x12, 0x66, 0x6c, 0x48,	// 37
	0x3d, 0x43, 0xf, 0x37, 0x1b, 0x2a, 0x12, 0x2a, 0x2a, 0x13, 0x22, 0x2f, 0x1, 0x13, 0x33, 0x16, 0x73, 0x6e, 0x63, 0xb, 0x82, 0x89, 0x20,	// 38
	0x5, 0x98,	// 39
	0x27, 0x3, 0x37, 0x7, 0x1b, 0x53, 0xa, 0x72,	// 40
	0x2, 0x72, 0xb, 0x53, 0x1f, 0x7, 0x37, 0x3, 0x20,	// 41
	0x11, 0x11, 0x73, 0x6d, 0x7b, 0x79, 0x11, 0x90,	// 42
	0x42, 0x82, 0x82, 0x67, 0x3, 0x47, 0x3, 0x62, 0x82, 0x82, 0x40,	// 43
	0x62, 0x11, 0x6c, 0x30,	// 44
	0x42, 0x82, 0x82, 0x82, 0x82, 0x70,	// 45
	0x62, 0x82, 0x40,	// 46
	0x62, 0x66, 0x46, 0x46, 0x62, 0xb0,	// 47
	0x27, 0x4f, 0x4, 0x33, 0x3b, 0x2a, 0x4a, 0x2a, 0x4a, 0x2b, 0x3b, 0x37, 0x4, 0x4f, 0x38,	// 48
	0x12, 0x82, 0x82, 0x7f, 0x6, 0x2f, 0x6, 0x50,	// 49
	0x12, 0x34, 0x32, 0x2d, 0x2a, 0x2b, 0xa, 0x2a, 0x23, 0x12, 0x2a, 0x1b, 0x1a, 0x2a, 0x13, 0x22, 0x35, 0x2a, 0x3b, 0x32, 0x20,	// 50
	0x1a, 0x2a, 0x43, 0x2b, 0x32, 0x4a, 0x2a, 0x1a, 0x22, 0x2a, 0x1a, 0x22, 0x2a, 0x14, 0x13, 0x34, 0xe, 0x42, 0x1c, 0x30,	// 51
	0x43, 0x74, 0x63, 0xa, 0x5b, 0x12, 0x52, 0x22, 0x4a, 0x2a, 0x47, 0x6, 0x2f, 0x6, 0x6a, 0x68,	// 52
	0xf, 0x13, 0x37, 0x14, 0x2a, 0x12, 0x2a, 0x2a, 0x12, 0x2a, 0x2a, 0x12, 0x2a, 0x2a, 0x13, 0x1b, 0x2a, 0x1f, 0x65, 0x30,	// 53
	0x27, 0x1, 0x47, 0x4, 0x33, 0x19, 0x1b, 0x2a, 0x1a, 0x22, 0x2a, 0x1a, 0x22, 0x2a, 0x1a, 0x22, 0x32, 0x1e, 0x3a, 0x24, 0x30,	// 54
	0xa, 0x82, 0x4a, 0x2a, 0x35, 0x2a, 0x25, 0x3a, 0x14, 0x52, 0xb, 0x64, 0x73, 0x70,	// 55
	0x1b, 0x1b, 0x47, 0x4, 0x33, 0x13, 0x13, 0x2a, 0x21, 0x22, 0x2a, 0x21, 0x22, 0x2b, 0x13, 0x13, 0x37, 0x4, 0x43, 0x1b, 0x30,	// 56
	0x1c, 0x22, 0x3e, 0x1b, 0x2a, 0x22, 0x1a, 0x2a, 0x22, 0x1a, 0x2a, 0x22, 0x1a, 0x2b, 0x19, 0x1b, 0x37, 0x4, 0x47, 0x1, 0x38,	// 57
	0x22, 0x32, 0x42, 0x32, 0x40,	// 58
	0x22, 0x32, 0x11, 0x2a, 0x34, 0x30,	// 59
	0x49, 0x83, 0x72, 0xa, 0x6a, 0xa, 0x62, 0x1a, 0x5a, 0x1a, 0x52, 0x2a, 0x4a, 0x2a, 0x20,	// 60
	0x32, 0x12, 0x62, 0x12, 0x62, 0x12, 0x62, 0x12, 0x62, 0x12, 0x62, 0x12, 0x62, 0x12, 0x40,	// 61
	0x2a, 0x2a, 0x4a, 0x2a, 0x52, 0x1a, 0x5a, 0x1a, 0x62, 0xa, 0x6a, 0xa, 0x73, 0x81, 0x40,	// 62
	0xb, 0x74, 0x72, 0x24, 0x12, 0x22, 0x1d, 0x12, 0x22, 0x13, 0x5e, 0x6c, 0x78,	// 63

    }
};
