
// file: font/timI12.bdf
// font: -Adobe-Times-Medium-I-Normal--12-120-75-75-P-63-ISO10646-1

#include <font.h>

const struct Font font_timI12_n = {
    .type       = 1,
    .name	= "timI12_n",
    .height	= 13,
    .width	= 10,
    .bytescol	= 2,
    .numcol     = 10,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 5, .ncol = 3, .xadj = -6, .pos = 0 }, // 33 [5]
	{ .l0 = 2, .r0 = 4, .ncol = 4, .xadj = -5, .pos = 5 }, // 34 [7]
	{ .l0 = 0, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 12 }, // 35 [12]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 24 }, // 36 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 9, .xadj = 0, .pos = 34 }, // 37 [15]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = -1, .pos = 49 }, // 38 [13]
	{ .l0 = 2, .r0 = 6, .ncol = 2, .xadj = -7, .pos = 62 }, // 39 [4]
	{ .l0 = 0, .r0 = 6, .ncol = 4, .xadj = -6, .pos = 66 }, // 40 [7]
	{ .l0 = 1, .r0 = 5, .ncol = 4, .xadj = -6, .pos = 73 }, // 41 [7]
	{ .l0 = 2, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 80 }, // 42 [9]
	{ .l0 = 2, .r0 = 3, .ncol = 5, .xadj = -2, .pos = 89 }, // 43 [9]
	{ .l0 = 0, .r0 = 8, .ncol = 2, .xadj = -7, .pos = 98 }, // 44 [4]
	{ .l0 = 0, .r0 = 6, .ncol = 4, .xadj = -6, .pos = 102 }, // 45 [7]
	{ .l0 = 1, .r0 = 8, .ncol = 1, .xadj = -7, .pos = 109 }, // 46 [2]
	{ .l0 = 1, .r0 = 5, .ncol = 4, .xadj = -6, .pos = 111 }, // 47 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 118 }, // 48 [10]
	{ .l0 = 1, .r0 = 5, .ncol = 4, .xadj = -4, .pos = 128 }, // 49 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 135 }, // 50 [10]
	{ .l0 = 0, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 145 }, // 51 [10]
	{ .l0 = 0, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 155 }, // 52 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 165 }, // 53 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 175 }, // 54 [10]
	{ .l0 = 2, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 185 }, // 55 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 194 }, // 56 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 204 }, // 57 [10]
	{ .l0 = 2, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 214 }, // 58 [4]
	{ .l0 = 1, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 218 }, // 59 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -2, .pos = 223 }, // 60 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -2, .pos = 233 }, // 61 [10]
	{ .l0 = 2, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 243 }, // 62 [10]
	{ .l0 = 3, .r0 = 3, .ncol = 4, .xadj = -4, .pos = 253 }, // 63 [7]
    },
    .data       = {
	192, 2, 7, 24, 0,	// 33
	4, 64, 0, 16, 0, 1, 0,	// 34
	128, 0, 114, 192, 3, 207, 1, 15, 60, 1, 4, 0,	// 35
	128, 129, 195, 136, 15, 31, 49, 28, 8, 0,	// 36
	24, 128, 5, 152, 8, 201, 192, 4, 104, 3, 179, 48, 19, 32, 1,	// 37
	128, 1, 72, 128, 8, 62, 33, 25, 28, 5, 152, 0, 9,	// 38
	4, 64, 0, 0,	// 39
	224, 3, 131, 17, 64, 1, 0,	// 40
	0, 80, 0, 49, 24, 248, 0,	// 41
	20, 0, 1, 248, 0, 4, 64, 1, 0,	// 42
	64, 0, 8, 192, 7, 32, 0, 4, 0,	// 43
	0, 8, 192, 0,	// 44
	64, 0, 8, 0, 1, 32, 0,	// 45
	0, 2,	// 46
	0, 3, 24, 224, 0, 3, 0,	// 47
	224, 1, 67, 16, 8, 129, 32, 12, 120, 0,	// 48
	0, 2, 112, 200, 9, 7, 0,	// 49
	0, 131, 80, 8, 9, 17, 33, 33, 24, 2,	// 50
	0, 1, 64, 144, 8, 145, 32, 13, 24, 0,	// 51
	192, 0, 20, 64, 2, 196, 65, 14, 60, 1,	// 52
	0, 3, 67, 88, 8, 137, 32, 14, 4, 0,	// 53
	224, 1, 67, 80, 8, 138, 32, 14, 4, 0,	// 54
	4, 67, 24, 200, 0, 5, 96, 0, 0,	// 55
	192, 129, 69, 72, 8, 153, 160, 12, 8, 0,	// 56
	0, 2, 71, 16, 5, 161, 32, 12, 120, 0,	// 57
	0, 2, 2, 0,	// 58
	0, 8, 192, 64, 0,	// 59
	64, 0, 20, 128, 2, 136, 0, 17, 16, 4,	// 60
	160, 0, 20, 128, 2, 80, 0, 10, 64, 1,	// 61
	8, 2, 34, 64, 4, 80, 0, 10, 128, 0,	// 62
	204, 66, 4, 72, 0, 6, 0,	// 63

    }
};
