
// file: font/luRS12.bdf
// font: -B&H-Lucida-Medium-R-Normal-Sans-12-120-75-75-P-71-ISO10646-1

#include <font.h>

const struct Font font_luRS12_n = {
    .type       = 1,
    .name	= "luRS12_n",
    .height	= 11,
    .width	= 9,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 7, .ncol = 1, .xadj = -6, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = -4, .pos = 2 }, // 34 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 7 }, // 35 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 16 }, // 36 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 25 }, // 37 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 8, .xadj = 0, .pos = 35 }, // 38 [11]
	{ .l0 = 1, .r0 = 7, .ncol = 1, .xadj = -6, .pos = 46 }, // 39 [2]
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 48 }, // 40 [5]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -5, .pos = 53 }, // 41 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -3, .pos = 58 }, // 42 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 65 }, // 43 [10]
	{ .l0 = 0, .r0 = 7, .ncol = 2, .xadj = -6, .pos = 75 }, // 44 [3]
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 78 }, // 45 [5]
	{ .l0 = 1, .r0 = 7, .ncol = 1, .xadj = -6, .pos = 83 }, // 46 [2]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -3, .pos = 85 }, // 47 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 92 }, // 48 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 3, .xadj = -1, .pos = 101 }, // 49 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 106 }, // 50 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 115 }, // 51 [9]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = -1, .pos = 124 }, // 52 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 134 }, // 53 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 143 }, // 54 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 152 }, // 55 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 161 }, // 56 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 170 }, // 57 [9]
	{ .l0 = 1, .r0 = 7, .ncol = 1, .xadj = -6, .pos = 179 }, // 58 [2]
	{ .l0 = 0, .r0 = 7, .ncol = 2, .xadj = -6, .pos = 181 }, // 59 [3]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 184 }, // 60 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 193 }, // 61 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 203 }, // 62 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -3, .pos = 212 }, // 63 [7]
    },
    .data       = {
	126, 3,	// 33
	7, 0, 192, 1, 0,	// 34
	72, 240, 31, 18, 144, 224, 63, 36, 0,	// 35
	28, 145, 144, 248, 127, 36, 36, 226, 0,	// 36
	12, 145, 132, 20, 88, 3, 37, 36, 17, 6,	// 37
	192, 97, 145, 140, 68, 36, 37, 198, 0, 6, 76,	// 38
	7, 0,	// 39
	248, 48, 88, 0, 1,	// 40
	1, 52, 24, 62, 0,	// 41
	20, 64, 128, 13, 16, 64, 1,	// 42
	32, 0, 1, 8, 248, 3, 2, 16, 128, 0,	// 43
	0, 4, 24,	// 44
	32, 0, 1, 8, 0,	// 45
	0, 3,	// 46
	0, 6, 12, 28, 24, 48, 0,	// 47
	248, 32, 136, 128, 4, 68, 16, 124, 0,	// 48
	4, 32, 128, 255, 0,	// 49
	4, 18, 152, 160, 132, 36, 34, 14, 1,	// 50
	4, 17, 144, 136, 68, 36, 34, 238, 0,	// 51
	96, 128, 2, 18, 136, 32, 4, 255, 1, 1,	// 52
	30, 145, 144, 132, 36, 36, 33, 241, 0,	// 53
	252, 17, 145, 136, 68, 36, 34, 226, 0,	// 54
	2, 16, 152, 48, 100, 160, 0, 3, 0,	// 55
	220, 17, 145, 136, 68, 36, 34, 238, 0,	// 56
	28, 17, 145, 136, 68, 36, 34, 254, 0,	// 57
	24, 3,	// 58
	0, 196, 24,	// 59
	32, 128, 2, 34, 16, 65, 16, 130, 0,	// 60
	80, 128, 2, 20, 160, 0, 5, 40, 64, 1,	// 61
	4, 33, 8, 34, 16, 1, 5, 16, 0,	// 62
	2, 16, 155, 8, 68, 192, 1,	// 63

    }
};
