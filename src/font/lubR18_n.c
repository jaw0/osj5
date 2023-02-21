
// file: font/lubR18.bdf
// font: -B&H-LucidaBright-Medium-R-Normal--18-180-75-75-P-103-ISO10646-1

#include <font.h>

const struct Font font_lubR18_n = {
    .type       = 1,
    .name	= "lubR18_n",
    .height	= 17,
    .width	= 13,
    .lineheight = 18,
    .bytescol	= 4,
    .numcol     = 13,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 10, .ncol = 2, .xadj = -8, .pos = 0 }, // 33 [5]
	{ .l0 = 0, .r0 = 7, .ncol = 6, .xadj = -6, .pos = 5 }, // 34 [13]
	{ .l0 = 0, .r0 = 2, .ncol = 11, .xadj = -2, .pos = 18 }, // 35 [24]
	{ .l0 = 2, .r0 = 4, .ncol = 7, .xadj = -2, .pos = 42 }, // 36 [15]
	{ .l0 = 0, .r0 = 0, .ncol = 13, .xadj = -1, .pos = 57 }, // 37 [28]
	{ .l0 = 1, .r0 = 1, .ncol = 11, .xadj = -1, .pos = 85 }, // 38 [24]
	{ .l0 = 1, .r0 = 9, .ncol = 3, .xadj = -9, .pos = 109 }, // 39 [7]
	{ .l0 = 1, .r0 = 8, .ncol = 4, .xadj = -7, .pos = 116 }, // 40 [9]
	{ .l0 = 1, .r0 = 8, .ncol = 4, .xadj = -7, .pos = 125 }, // 41 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 7, .xadj = -5, .pos = 134 }, // 42 [15]
	{ .l0 = 0, .r0 = 2, .ncol = 11, .xadj = -2, .pos = 149 }, // 43 [24]
	{ .l0 = 1, .r0 = 10, .ncol = 2, .xadj = -8, .pos = 173 }, // 44 [5]
	{ .l0 = 1, .r0 = 8, .ncol = 4, .xadj = -7, .pos = 178 }, // 45 [9]
	{ .l0 = 1, .r0 = 10, .ncol = 2, .xadj = -8, .pos = 187 }, // 46 [5]
	{ .l0 = 0, .r0 = 4, .ncol = 9, .xadj = -4, .pos = 192 }, // 47 [20]
	{ .l0 = 1, .r0 = 3, .ncol = 9, .xadj = -2, .pos = 212 }, // 48 [20]
	{ .l0 = 2, .r0 = 5, .ncol = 6, .xadj = -2, .pos = 232 }, // 49 [13]
	{ .l0 = 1, .r0 = 4, .ncol = 8, .xadj = -2, .pos = 245 }, // 50 [17]
	{ .l0 = 1, .r0 = 4, .ncol = 8, .xadj = -2, .pos = 262 }, // 51 [17]
	{ .l0 = 0, .r0 = 3, .ncol = 10, .xadj = -2, .pos = 279 }, // 52 [22]
	{ .l0 = 2, .r0 = 4, .ncol = 7, .xadj = -2, .pos = 301 }, // 53 [15]
	{ .l0 = 1, .r0 = 3, .ncol = 9, .xadj = -2, .pos = 316 }, // 54 [20]
	{ .l0 = 2, .r0 = 3, .ncol = 8, .xadj = -2, .pos = 336 }, // 55 [17]
	{ .l0 = 1, .r0 = 3, .ncol = 9, .xadj = -2, .pos = 353 }, // 56 [20]
	{ .l0 = 1, .r0 = 3, .ncol = 9, .xadj = -2, .pos = 373 }, // 57 [20]
	{ .l0 = 1, .r0 = 10, .ncol = 2, .xadj = -8, .pos = 393 }, // 58 [5]
	{ .l0 = 1, .r0 = 10, .ncol = 2, .xadj = -8, .pos = 398 }, // 59 [5]
	{ .l0 = 0, .r0 = 3, .ncol = 10, .xadj = -2, .pos = 403 }, // 60 [22]
	{ .l0 = 0, .r0 = 3, .ncol = 10, .xadj = -2, .pos = 425 }, // 61 [22]
	{ .l0 = 0, .r0 = 3, .ncol = 10, .xadj = -2, .pos = 447 }, // 62 [22]
	{ .l0 = 1, .r0 = 5, .ncol = 7, .xadj = -4, .pos = 469 }, // 63 [15]
    },
    .data       = {
	254, 55, 252, 96, 0,	// 33
	6, 0, 60, 0, 0, 0, 0, 0, 224, 1, 192, 0, 0,	// 34
	0, 2, 64, 4, 128, 232, 0, 61, 192, 39, 192, 68, 6, 200, 7, 120, 1, 46, 2, 64, 4, 128, 0, 0,	// 35
	60, 56, 248, 64, 8, 131, 248, 255, 35, 24, 66, 224, 131, 131, 3,	// 36
	60, 32, 140, 96, 8, 97, 16, 98, 32, 100, 128, 39, 0, 32, 0, 160, 15, 176, 33, 48, 65, 48, 130, 48, 4, 33, 240, 1,	// 37
	0, 15, 0, 63, 112, 193, 240, 3, 33, 30, 66, 244, 132, 143, 7, 14, 14, 128, 56, 0, 79, 0, 130, 0,	// 38
	6, 0, 60, 0, 24, 0, 0,	// 39
	192, 15, 224, 127, 48, 0, 19, 0, 8,	// 40
	2, 0, 25, 128, 193, 255, 0, 126, 0,	// 41
	8, 0, 16, 1, 192, 1, 112, 0, 0, 7, 0, 17, 0, 2, 0,	// 42
	0, 1, 0, 2, 0, 4, 0, 8, 0, 16, 0, 255, 7, 64, 0, 128, 0, 0, 1, 0, 2, 0, 4, 0,	// 43
	0, 48, 1, 224, 1,	// 44
	0, 1, 0, 2, 0, 4, 0, 8, 0,	// 45
	0, 48, 0, 96, 0,	// 46
	0, 0, 1, 128, 1, 192, 0, 96, 0, 48, 0, 24, 0, 12, 0, 6, 0, 2, 0, 0,	// 47
	240, 7, 248, 63, 16, 64, 16, 0, 33, 0, 66, 0, 4, 1, 4, 254, 15, 240, 7, 0,	// 48
	2, 32, 4, 64, 248, 255, 240, 255, 1, 0, 2, 0, 4,	// 49
	28, 48, 12, 120, 8, 200, 16, 136, 33, 24, 195, 24, 6, 31, 12, 28, 24,	// 50
	14, 56, 4, 97, 8, 130, 16, 4, 33, 8, 194, 56, 6, 207, 7, 158, 7,	// 51
	0, 3, 0, 7, 0, 11, 0, 17, 128, 33, 130, 65, 132, 255, 15, 255, 31, 0, 34, 0, 68, 0,	// 52
	126, 56, 140, 64, 24, 129, 48, 2, 97, 8, 195, 240, 131, 193, 3,	// 53
	240, 7, 240, 63, 48, 66, 16, 2, 33, 4, 66, 8, 132, 48, 12, 199, 15, 0, 15, 0,	// 54
	6, 0, 12, 96, 24, 248, 48, 56, 96, 12, 192, 12, 128, 7, 0, 3, 0,	// 55
	56, 14, 120, 62, 152, 195, 16, 6, 33, 12, 66, 48, 132, 121, 12, 158, 15, 28, 14, 0,	// 56
	120, 0, 248, 113, 24, 134, 16, 8, 33, 16, 66, 32, 4, 33, 6, 254, 7, 240, 7, 0,	// 57
	96, 48, 192, 96, 0,	// 58
	96, 48, 193, 224, 1,	// 59
	0, 1, 0, 2, 0, 10, 0, 20, 0, 68, 0, 140, 1, 8, 2, 8, 12, 16, 16, 16, 64, 0,	// 60
	128, 4, 0, 9, 0, 18, 0, 36, 0, 72, 0, 144, 0, 32, 1, 64, 2, 128, 4, 0, 9, 0,	// 61
	8, 32, 32, 32, 192, 64, 0, 65, 0, 198, 0, 136, 0, 160, 0, 64, 1, 0, 1, 0, 2, 0,	// 62
	14, 0, 4, 0, 8, 220, 16, 188, 97, 12, 128, 15, 0, 7, 0,	// 63

    }
};
