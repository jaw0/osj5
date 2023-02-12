
// file: font/lubB19.bdf
// font: -B&H-LucidaBright-DemiBold-R-Normal--19-190-75-75-P-114-ISO10646-1

#include <font.h>

const struct Font font_lubB19_n = {
    .type       = 1,
    .name	= "lubB19_n",
    .height	= 20,
    .width	= 15,
    .bytescol	= 4,
    .numcol     = 15,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 10, .ncol = 3, .xadj = -10, .pos = 0 }, // 33 [8]
	{ .l0 = 2, .r0 = 6, .ncol = 7, .xadj = -6, .pos = 8 }, // 34 [18]
	{ .l0 = 1, .r0 = 2, .ncol = 12, .xadj = -2, .pos = 26 }, // 35 [30]
	{ .l0 = 3, .r0 = 4, .ncol = 8, .xadj = -3, .pos = 56 }, // 36 [20]
	{ .l0 = 1, .r0 = 0, .ncol = 14, .xadj = -1, .pos = 76 }, // 37 [35]
	{ .l0 = 1, .r0 = 0, .ncol = 14, .xadj = 0, .pos = 111 }, // 38 [35]
	{ .l0 = 2, .r0 = 10, .ncol = 3, .xadj = -10, .pos = 146 }, // 39 [8]
	{ .l0 = 2, .r0 = 8, .ncol = 5, .xadj = -9, .pos = 154 }, // 40 [13]
	{ .l0 = 2, .r0 = 8, .ncol = 5, .xadj = -9, .pos = 167 }, // 41 [13]
	{ .l0 = 2, .r0 = 6, .ncol = 7, .xadj = -7, .pos = 180 }, // 42 [18]
	{ .l0 = 1, .r0 = 3, .ncol = 11, .xadj = -3, .pos = 198 }, // 43 [28]
	{ .l0 = 2, .r0 = 10, .ncol = 3, .xadj = -10, .pos = 226 }, // 44 [8]
	{ .l0 = 2, .r0 = 9, .ncol = 4, .xadj = -10, .pos = 234 }, // 45 [10]
	{ .l0 = 2, .r0 = 10, .ncol = 3, .xadj = -10, .pos = 244 }, // 46 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 10, .xadj = -5, .pos = 252 }, // 47 [25]
	{ .l0 = 1, .r0 = 3, .ncol = 11, .xadj = -3, .pos = 277 }, // 48 [28]
	{ .l0 = 4, .r0 = 4, .ncol = 7, .xadj = -3, .pos = 305 }, // 49 [18]
	{ .l0 = 2, .r0 = 4, .ncol = 9, .xadj = -3, .pos = 323 }, // 50 [23]
	{ .l0 = 2, .r0 = 4, .ncol = 9, .xadj = -3, .pos = 346 }, // 51 [23]
	{ .l0 = 1, .r0 = 2, .ncol = 12, .xadj = -3, .pos = 369 }, // 52 [30]
	{ .l0 = 3, .r0 = 4, .ncol = 8, .xadj = -3, .pos = 399 }, // 53 [20]
	{ .l0 = 2, .r0 = 3, .ncol = 10, .xadj = -3, .pos = 419 }, // 54 [25]
	{ .l0 = 3, .r0 = 3, .ncol = 9, .xadj = -3, .pos = 444 }, // 55 [23]
	{ .l0 = 2, .r0 = 3, .ncol = 10, .xadj = -3, .pos = 467 }, // 56 [25]
	{ .l0 = 2, .r0 = 3, .ncol = 10, .xadj = -3, .pos = 492 }, // 57 [25]
	{ .l0 = 2, .r0 = 10, .ncol = 3, .xadj = -10, .pos = 517 }, // 58 [8]
	{ .l0 = 2, .r0 = 10, .ncol = 3, .xadj = -10, .pos = 525 }, // 59 [8]
	{ .l0 = 0, .r0 = 5, .ncol = 10, .xadj = -3, .pos = 533 }, // 60 [25]
	{ .l0 = 1, .r0 = 3, .ncol = 11, .xadj = -3, .pos = 558 }, // 61 [28]
	{ .l0 = 1, .r0 = 4, .ncol = 10, .xadj = -3, .pos = 586 }, // 62 [25]
	{ .l0 = 1, .r0 = 5, .ncol = 9, .xadj = -5, .pos = 611 }, // 63 [23]
    },
    .data       = {
	252, 224, 192, 255, 14, 252, 224, 0,	// 33
	28, 0, 192, 7, 0, 28, 0, 0, 0, 0, 28, 0, 192, 7, 0, 28, 0, 0,	// 34
	0, 8, 0, 132, 0, 64, 232, 0, 228, 1, 224, 9, 192, 133, 0, 64, 232, 0, 228, 1, 224, 9, 192, 133, 0, 64, 8, 0, 4, 0,	// 35
	112, 224, 192, 15, 12, 252, 129, 192, 56, 8, 255, 255, 67, 240, 15, 4, 254, 192, 193, 7,	// 36
	112, 128, 128, 15, 8, 4, 65, 64, 16, 2, 4, 17, 128, 207, 0, 112, 6, 0, 48, 0, 128, 57, 0, 204, 7, 32, 130, 0, 33, 8, 8, 130, 64, 192, 7,	// 37
	0, 60, 0, 224, 7, 56, 127, 128, 23, 14, 252, 129, 64, 124, 8, 196, 158, 192, 207, 11, 120, 120, 128, 19, 15, 0, 241, 0, 240, 13, 0, 135, 0, 16, 8,	// 38
	28, 0, 192, 7, 0, 28, 0, 0,	// 39
	0, 63, 0, 252, 15, 240, 255, 131, 3, 112, 12, 0, 8,	// 40
	12, 0, 136, 3, 112, 240, 255, 3, 252, 15, 0, 63, 0,	// 41
	16, 0, 128, 11, 0, 224, 1, 192, 1, 0, 224, 1, 0, 11, 0, 24, 0, 0,	// 42
	0, 4, 0, 64, 0, 0, 4, 0, 64, 0, 0, 4, 0, 255, 15, 0, 4, 0, 64, 0, 0, 4, 0, 64, 0, 0, 4, 0,	// 43
	0, 224, 8, 0, 254, 0, 224, 7,	// 44
	0, 6, 0, 96, 0, 0, 6, 0, 96, 0,	// 45
	0, 224, 0, 0, 14, 0, 224, 0,	// 46
	0, 0, 8, 0, 224, 0, 128, 1, 0, 6, 0, 24, 0, 96, 0, 128, 1, 0, 6, 0, 28, 0, 64, 0, 0,	// 47
	192, 15, 0, 255, 3, 248, 127, 192, 1, 14, 4, 128, 64, 0, 8, 4, 128, 192, 1, 14, 248, 127, 0, 255, 3, 192, 15, 0,	// 48
	4, 128, 64, 0, 8, 252, 255, 192, 255, 15, 252, 255, 0, 0, 8, 0, 128, 0,	// 49
	24, 192, 192, 0, 15, 4, 248, 64, 64, 14, 4, 230, 192, 48, 14, 252, 225, 128, 31, 14, 112, 224, 0,	// 50
	28, 224, 192, 16, 8, 4, 129, 64, 16, 8, 4, 131, 192, 56, 12, 252, 126, 128, 239, 7, 112, 60, 0,	// 51
	0, 12, 0, 224, 0, 0, 13, 0, 204, 0, 96, 12, 0, 195, 0, 24, 140, 192, 255, 15, 252, 255, 192, 255, 15, 0, 140, 0, 192, 8,	// 52
	252, 224, 192, 8, 8, 140, 128, 192, 24, 8, 140, 195, 192, 240, 7, 12, 127, 192, 224, 3,	// 53
	192, 15, 0, 255, 3, 248, 127, 192, 17, 12, 140, 128, 64, 8, 8, 132, 193, 64, 248, 15, 28, 127, 0, 224, 3,	// 54
	28, 0, 192, 1, 12, 28, 240, 192, 193, 15, 28, 14, 192, 57, 0, 220, 0, 192, 3, 0, 28, 0, 0,	// 55
	112, 56, 128, 207, 7, 252, 254, 192, 60, 12, 132, 131, 64, 56, 8, 140, 199, 192, 239, 15, 120, 126, 0, 195, 3,	// 56
	240, 1, 128, 63, 14, 252, 135, 192, 96, 8, 4, 132, 64, 64, 12, 12, 226, 128, 255, 7, 240, 63, 0, 252, 0,	// 57
	192, 225, 0, 28, 14, 192, 225, 0,	// 58
	192, 225, 8, 28, 126, 192, 225, 7,	// 59
	0, 6, 0, 96, 0, 0, 9, 0, 144, 0, 128, 16, 0, 8, 1, 64, 32, 0, 4, 2, 32, 64, 0, 3, 12,	// 60
	0, 17, 0, 16, 1, 0, 17, 0, 16, 1, 0, 17, 0, 16, 1, 0, 17, 0, 16, 1, 0, 17, 0, 16, 1, 0, 17, 0,	// 61
	48, 192, 0, 2, 4, 64, 32, 0, 4, 2, 128, 16, 0, 8, 1, 0, 9, 0, 144, 0, 0, 6, 0, 96, 0,	// 62
	28, 0, 192, 0, 0, 4, 236, 64, 224, 14, 4, 238, 192, 16, 0, 252, 0, 128, 7, 0, 48, 0, 0,	// 63

    }
};
