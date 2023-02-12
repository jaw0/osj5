
// file: font/lubB12.bdf
// font: -B&H-LucidaBright-DemiBold-R-Normal--12-120-75-75-P-71-ISO10646-1

#include <font.h>

const struct Font font_lubB12_n = {
    .type       = 1,
    .name	= "lubB12_n",
    .height	= 12,
    .width	= 9,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 0 }, // 33 [3]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -3, .pos = 3 }, // 34 [8]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 11 }, // 35 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -2, .pos = 22 }, // 36 [8]
	{ .l0 = 1, .r0 = 0, .ncol = 8, .xadj = 0, .pos = 30 }, // 37 [12]
	{ .l0 = 1, .r0 = 0, .ncol = 8, .xadj = 0, .pos = 42 }, // 38 [12]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 54 }, // 39 [5]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -5, .pos = 59 }, // 40 [5]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -5, .pos = 64 }, // 41 [5]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -4, .pos = 69 }, // 42 [8]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 77 }, // 43 [11]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 88 }, // 44 [3]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 91 }, // 45 [5]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 96 }, // 46 [3]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = -3, .pos = 99 }, // 47 [9]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 108 }, // 48 [11]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 119 }, // 49 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 128 }, // 50 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 137 }, // 51 [9]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 146 }, // 52 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -2, .pos = 157 }, // 53 [8]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 165 }, // 54 [11]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 176 }, // 55 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 185 }, // 56 [9]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 194 }, // 57 [11]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 205 }, // 58 [3]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 208 }, // 59 [3]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 211 }, // 60 [11]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 222 }, // 61 [11]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 233 }, // 62 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -3, .pos = 244 }, // 63 [8]
    },
    .data       = {
	30, 227, 55,	// 33
	6, 224, 1, 0, 224, 1, 6, 0,	// 34
	64, 128, 60, 124, 160, 52, 248, 224, 4, 8, 0,	// 35
	140, 227, 33, 255, 39, 62, 198, 1,	// 36
	28, 226, 51, 190, 192, 7, 176, 129, 60, 198, 35, 24,	// 37
	192, 193, 62, 62, 35, 39, 206, 195, 56, 224, 3, 34,	// 38
	6, 224, 1, 6, 0,	// 39
	240, 193, 127, 2, 8,	// 40
	2, 200, 127, 240, 1,	// 41
	20, 192, 1, 6, 192, 1, 4, 0,	// 42
	64, 0, 4, 64, 192, 63, 64, 0, 4, 64, 0,	// 43
	0, 15, 240,	// 44
	192, 0, 12, 192, 0,	// 45
	0, 3, 48,	// 46
	0, 8, 96, 192, 1, 7, 12, 32, 0,	// 47
	248, 192, 31, 6, 35, 32, 6, 195, 31, 248, 0,	// 48
	2, 34, 32, 254, 227, 63, 0, 2, 32,	// 49
	14, 35, 56, 66, 35, 50, 62, 195, 49,	// 50
	6, 35, 34, 34, 34, 38, 222, 195, 28,	// 51
	96, 0, 7, 104, 64, 38, 254, 227, 63, 96, 2,	// 52
	62, 99, 34, 102, 98, 62, 198, 1,	// 53
	248, 192, 31, 22, 35, 33, 50, 34, 63, 230, 1,	// 54
	6, 99, 56, 230, 96, 3, 30, 96, 0,	// 55
	204, 225, 61, 50, 34, 34, 254, 195, 28,	// 56
	60, 227, 39, 98, 34, 36, 70, 195, 31, 248, 0,	// 57
	48, 3, 51,	// 58
	48, 15, 115,	// 59
	32, 0, 6, 96, 0, 9, 152, 129, 16, 4, 2,	// 60
	160, 0, 10, 160, 0, 10, 160, 0, 10, 160, 0,	// 61
	4, 130, 16, 152, 1, 9, 96, 0, 6, 64, 0,	// 62
	6, 32, 60, 226, 227, 1, 12, 0,	// 63

    }
};
