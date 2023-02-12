
// file: font/utrg18.bdf
// font: -Adobe-Utopia-Regular-R-Normal--19-180-75-75-P-101-ISO10646-1

#include <font.h>

const struct Font font_utrg18_n = {
    .type       = 1,
    .name	= "utrg18_n",
    .height	= 17,
    .width	= 16,
    .bytescol	= 4,
    .numcol     = 16,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 13, .ncol = 2, .xadj = -11, .pos = 0 }, // 33 [5]
	{ .l0 = 1, .r0 = 10, .ncol = 5, .xadj = -8, .pos = 5 }, // 34 [11]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 16 }, // 35 [17]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 33 }, // 36 [17]
	{ .l0 = 2, .r0 = 1, .ncol = 13, .xadj = 0, .pos = 50 }, // 37 [28]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -3, .pos = 78 }, // 38 [26]
	{ .l0 = 1, .r0 = 13, .ncol = 2, .xadj = -11, .pos = 104 }, // 39 [5]
	{ .l0 = 2, .r0 = 11, .ncol = 3, .xadj = -10, .pos = 109 }, // 40 [7]
	{ .l0 = 1, .r0 = 12, .ncol = 3, .xadj = -10, .pos = 116 }, // 41 [7]
	{ .l0 = 0, .r0 = 9, .ncol = 7, .xadj = -8, .pos = 123 }, // 42 [15]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -5, .pos = 138 }, // 43 [20]
	{ .l0 = 0, .r0 = 13, .ncol = 3, .xadj = -11, .pos = 158 }, // 44 [7]
	{ .l0 = 1, .r0 = 10, .ncol = 5, .xadj = -9, .pos = 165 }, // 45 [11]
	{ .l0 = 1, .r0 = 13, .ncol = 2, .xadj = -11, .pos = 176 }, // 46 [5]
	{ .l0 = 1, .r0 = 10, .ncol = 5, .xadj = -8, .pos = 181 }, // 47 [11]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 192 }, // 48 [17]
	{ .l0 = 2, .r0 = 8, .ncol = 6, .xadj = -6, .pos = 209 }, // 49 [13]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 222 }, // 50 [17]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 239 }, // 51 [17]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 256 }, // 52 [17]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 273 }, // 53 [17]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 290 }, // 54 [17]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 307 }, // 55 [17]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 324 }, // 56 [17]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -6, .pos = 341 }, // 57 [17]
	{ .l0 = 1, .r0 = 13, .ncol = 2, .xadj = -11, .pos = 358 }, // 58 [5]
	{ .l0 = 0, .r0 = 13, .ncol = 3, .xadj = -11, .pos = 363 }, // 59 [7]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -5, .pos = 370 }, // 60 [20]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -5, .pos = 390 }, // 61 [20]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -5, .pos = 410 }, // 62 [20]
	{ .l0 = 1, .r0 = 9, .ncol = 6, .xadj = -8, .pos = 430 }, // 63 [13]
    },
    .data       = {
	254, 51, 252, 103, 0,	// 33
	62, 0, 28, 0, 0, 0, 240, 1, 224, 0, 0,	// 34
	0, 2, 32, 60, 192, 15, 240, 16, 0, 225, 1, 126, 128, 135, 0, 8, 0,	// 35
	56, 24, 248, 96, 152, 131, 16, 254, 243, 31, 66, 112, 134, 193, 7, 6, 7,	// 36
	124, 0, 4, 1, 8, 130, 16, 196, 192, 71, 128, 96, 0, 33, 0, 50, 0, 20, 31, 24, 65, 8, 130, 0, 4, 1, 240, 1,	// 37
	0, 15, 48, 63, 240, 67, 16, 3, 33, 12, 66, 56, 4, 207, 8, 12, 11, 0, 28, 0, 56, 0, 207, 0, 12, 1,	// 38
	62, 0, 28, 0, 0,	// 39
	240, 63, 24, 128, 9, 0, 4,	// 40
	2, 0, 25, 128, 193, 255, 0,	// 41
	68, 0, 80, 0, 64, 0, 240, 7, 0, 1, 0, 5, 0, 17, 0,	// 42
	0, 2, 0, 4, 0, 8, 0, 16, 0, 254, 3, 64, 0, 128, 0, 0, 1, 0, 2, 0,	// 43
	0, 144, 0, 240, 0, 192, 0,	// 44
	0, 2, 0, 4, 0, 8, 0, 16, 0, 32, 0,	// 45
	0, 48, 0, 96, 0,	// 46
	0, 56, 0, 12, 0, 7, 128, 1, 224, 0, 0,	// 47
	248, 15, 248, 63, 24, 192, 16, 0, 33, 0, 194, 0, 6, 255, 7, 252, 7,	// 48
	4, 32, 8, 64, 248, 255, 240, 255, 1, 0, 2, 0, 4,	// 49
	12, 56, 24, 120, 24, 216, 16, 144, 33, 16, 195, 48, 6, 63, 12, 60, 28,	// 50
	12, 24, 24, 48, 24, 193, 16, 2, 33, 4, 194, 28, 6, 239, 7, 140, 7,	// 51
	0, 6, 0, 11, 128, 19, 192, 33, 225, 65, 194, 252, 7, 252, 15, 0, 18,	// 52
	254, 24, 140, 48, 24, 193, 48, 2, 97, 4, 194, 24, 134, 225, 7, 129, 7,	// 53
	248, 15, 248, 63, 24, 194, 16, 2, 33, 4, 194, 24, 6, 227, 7, 134, 7,	// 54
	14, 0, 12, 0, 24, 224, 48, 248, 97, 60, 192, 14, 128, 7, 0, 3, 0,	// 55
	56, 14, 248, 62, 24, 195, 16, 4, 33, 8, 194, 56, 6, 223, 7, 28, 7,	// 56
	120, 24, 248, 49, 24, 198, 16, 8, 33, 16, 194, 16, 6, 255, 7, 252, 7,	// 57
	96, 48, 192, 96, 0,	// 58
	0, 144, 192, 240, 128, 193, 0,	// 59
	0, 2, 0, 4, 0, 28, 0, 40, 0, 216, 0, 16, 1, 48, 6, 32, 8, 96, 48, 0,	// 60
	128, 8, 0, 17, 0, 34, 0, 68, 0, 136, 0, 16, 1, 32, 2, 64, 4, 128, 8, 0,	// 61
	96, 48, 128, 32, 0, 99, 0, 68, 0, 216, 0, 160, 0, 192, 1, 0, 1, 0, 2, 0,	// 62
	12, 0, 12, 99, 8, 207, 16, 19, 224, 3, 128, 3, 0,	// 63

    }
};
