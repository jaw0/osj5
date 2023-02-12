
// file: font/lubI12.bdf
// font: -B&H-LucidaBright-Medium-I-Normal--12-120-75-75-P-67-ISO10646-1

#include <font.h>

const struct Font font_lubI12_n = {
    .type       = 1,
    .name	= "lubI12_n",
    .height	= 11,
    .width	= 10,
    .bytescol	= 2,
    .numcol     = 10,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 6, .ncol = 3, .xadj = -7, .pos = 0 }, // 33 [5]
	{ .l0 = 2, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 5 }, // 34 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -3, .pos = 10 }, // 35 [10]
	{ .l0 = 2, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 20 }, // 36 [9]
	{ .l0 = 1, .r0 = 0, .ncol = 9, .xadj = -1, .pos = 29 }, // 37 [13]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = -1, .pos = 42 }, // 38 [11]
	{ .l0 = 2, .r0 = 7, .ncol = 1, .xadj = -7, .pos = 53 }, // 39 [2]
	{ .l0 = 1, .r0 = 5, .ncol = 4, .xadj = -6, .pos = 55 }, // 40 [6]
	{ .l0 = 0, .r0 = 6, .ncol = 4, .xadj = -6, .pos = 61 }, // 41 [6]
	{ .l0 = 2, .r0 = 4, .ncol = 4, .xadj = -5, .pos = 67 }, // 42 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -3, .pos = 73 }, // 43 [10]
	{ .l0 = 1, .r0 = 7, .ncol = 2, .xadj = -7, .pos = 83 }, // 44 [3]
	{ .l0 = 1, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 86 }, // 45 [5]
	{ .l0 = 1, .r0 = 7, .ncol = 2, .xadj = -7, .pos = 91 }, // 46 [3]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = -5, .pos = 94 }, // 47 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -3, .pos = 105 }, // 48 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 5, .xadj = -3, .pos = 114 }, // 49 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -3, .pos = 121 }, // 50 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -3, .pos = 131 }, // 51 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -3, .pos = 140 }, // 52 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -3, .pos = 149 }, // 53 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -3, .pos = 158 }, // 54 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 7, .xadj = -3, .pos = 167 }, // 55 [10]
	{ .l0 = 2, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 177 }, // 56 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = -3, .pos = 186 }, // 57 [9]
	{ .l0 = 1, .r0 = 6, .ncol = 3, .xadj = -7, .pos = 195 }, // 58 [5]
	{ .l0 = 1, .r0 = 6, .ncol = 3, .xadj = -7, .pos = 200 }, // 59 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = -3, .pos = 205 }, // 60 [11]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = -3, .pos = 216 }, // 61 [10]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 226 }, // 62 [11]
	{ .l0 = 2, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 237 }, // 63 [7]
    },
    .data       = {
	0, 225, 195, 0, 0,	// 33
	7, 0, 192, 1, 0,	// 34
	160, 33, 3, 79, 206, 211, 3, 19, 20, 0,	// 35
	128, 113, 88, 122, 62, 18, 142, 1, 0,	// 36
	0, 121, 68, 18, 78, 128, 13, 154, 88, 36, 28, 1, 0,	// 37
	224, 128, 140, 67, 118, 146, 142, 235, 192, 5, 2,	// 38
	7, 0,	// 39
	240, 227, 160, 0, 2, 0,	// 40
	0, 4, 80, 112, 124, 0,	// 41
	10, 48, 192, 3, 4, 0,	// 42
	32, 0, 1, 8, 252, 35, 2, 16, 128, 0,	// 43
	0, 5, 24,	// 44
	32, 0, 1, 8, 0,	// 45
	0, 1, 8,	// 46
	0, 4, 24, 32, 192, 0, 1, 6, 8, 32, 0,	// 47
	248, 112, 140, 64, 2, 18, 12, 63, 0,	// 48
	0, 1, 72, 112, 254, 50, 16,	// 49
	0, 1, 206, 73, 66, 18, 145, 133, 56, 0,	// 50
	128, 1, 200, 68, 34, 146, 15, 39, 0,	// 51
	48, 64, 1, 73, 68, 211, 151, 17, 0,	// 52
	128, 97, 200, 66, 18, 19, 143, 0, 0,	// 53
	248, 224, 140, 66, 18, 146, 141, 57, 0,	// 54
	0, 9, 70, 8, 50, 144, 128, 2, 12, 0,	// 55
	224, 112, 201, 70, 34, 146, 15, 3, 0,	// 56
	128, 241, 201, 72, 66, 19, 14, 63, 0,	// 57
	0, 65, 8, 2, 0,	// 58
	0, 69, 28, 2, 0,	// 59
	16, 128, 1, 12, 144, 128, 8, 66, 16, 68, 0,	// 60
	80, 128, 2, 20, 160, 0, 5, 40, 64, 1,	// 61
	0, 17, 132, 32, 8, 129, 4, 36, 192, 0, 4,	// 62
	70, 9, 67, 4, 30, 96, 0,	// 63

    }
};
