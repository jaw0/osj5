
// file: font/timB10.bdf
// font: -Adobe-Times-Bold-R-Normal--10-100-75-75-P-57-ISO10646-1

#include <font.h>

const struct Font font_timB10_n = {
    .type       = 1,
    .name	= "timB10_n",
    .height	= 11,
    .width	= 9,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -5, .pos = 0 }, // 33 [3]
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = -4, .pos = 3 }, // 34 [5]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -3, .pos = 8 }, // 35 [7]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -4, .pos = 15 }, // 36 [7]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = 0, .pos = 22 }, // 37 [10]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 32 }, // 38 [10]
	{ .l0 = 0, .r0 = 8, .ncol = 1, .xadj = -6, .pos = 42 }, // 39 [2]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -5, .pos = 44 }, // 40 [5]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -5, .pos = 49 }, // 41 [5]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -3, .pos = 54 }, // 42 [7]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -3, .pos = 61 }, // 43 [7]
	{ .l0 = 0, .r0 = 7, .ncol = 2, .xadj = -5, .pos = 68 }, // 44 [3]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 71 }, // 45 [5]
	{ .l0 = 0, .r0 = 7, .ncol = 2, .xadj = -6, .pos = 76 }, // 46 [3]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 79 }, // 47 [5]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -4, .pos = 84 }, // 48 [6]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -4, .pos = 90 }, // 49 [6]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -4, .pos = 96 }, // 50 [6]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -4, .pos = 102 }, // 51 [6]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -4, .pos = 108 }, // 52 [7]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -4, .pos = 115 }, // 53 [6]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -4, .pos = 121 }, // 54 [6]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -4, .pos = 127 }, // 55 [7]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -4, .pos = 134 }, // 56 [6]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -4, .pos = 140 }, // 57 [6]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -5, .pos = 146 }, // 58 [3]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -5, .pos = 149 }, // 59 [3]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -3, .pos = 152 }, // 60 [7]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -3, .pos = 159 }, // 61 [7]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -3, .pos = 166 }, // 62 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -3, .pos = 173 }, // 63 [6]
    },
    .data       = {
	222, 240, 6,	// 33
	14, 0, 128, 3, 0,	// 34
	40, 240, 7, 10, 252, 129, 2,	// 35
	204, 208, 196, 127, 100, 65, 6,	// 36
	140, 112, 130, 10, 172, 193, 14, 83, 136, 1,	// 37
	96, 224, 135, 39, 100, 193, 6, 120, 64, 2,	// 38
	14, 0,	// 39
	240, 224, 159, 129, 1,	// 40
	6, 230, 31, 60, 0,	// 41
	20, 224, 128, 15, 56, 64, 1,	// 42
	32, 0, 1, 62, 64, 0, 2,	// 43
	192, 0, 14,	// 44
	32, 0, 1, 8, 0,	// 45
	192, 0, 6,	// 46
	224, 192, 129, 3, 0,	// 47
	124, 240, 135, 32, 248, 0,	// 48
	132, 240, 135, 63, 0, 1,	// 49
	196, 48, 135, 55, 152, 1,	// 50
	196, 144, 132, 63, 216, 0,	// 51
	48, 64, 1, 57, 252, 1, 2,	// 52
	222, 176, 132, 61, 192, 0,	// 53
	120, 224, 135, 37, 228, 0,	// 54
	12, 48, 134, 61, 60, 32, 0,	// 55
	108, 240, 132, 60, 216, 0,	// 56
	156, 16, 133, 31, 120, 0,	// 57
	216, 192, 6,	// 58
	216, 192, 14,	// 59
	32, 128, 3, 20, 176, 129, 8,	// 60
	80, 128, 2, 20, 160, 0, 5,	// 61
	136, 192, 6, 20, 224, 0, 2,	// 62
	12, 16, 134, 55, 24, 0,	// 63

    }
};
