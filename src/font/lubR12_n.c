
// file: font/lubR12.bdf
// font: -B&H-LucidaBright-Medium-R-Normal--12-120-75-75-P-68-ISO10646-1

#include <font.h>

const struct Font font_lubR12_n = {
    .type       = 1,
    .name	= "lubR12_n",
    .height	= 11,
    .width	= 8,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 6, .ncol = 1, .xadj = -5, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -3, .pos = 2 }, // 34 [3]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 5 }, // 35 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -1, .pos = 15 }, // 36 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 22 }, // 37 [9]
	{ .l0 = 0, .r0 = 0, .ncol = 8, .xadj = 0, .pos = 31 }, // 38 [11]
	{ .l0 = 0, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 42 }, // 39 [5]
	{ .l0 = 0, .r0 = 5, .ncol = 3, .xadj = -4, .pos = 47 }, // 40 [5]
	{ .l0 = 0, .r0 = 5, .ncol = 3, .xadj = -4, .pos = 52 }, // 41 [5]
	{ .l0 = 0, .r0 = 3, .ncol = 5, .xadj = -2, .pos = 57 }, // 42 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 64 }, // 43 [10]
	{ .l0 = 1, .r0 = 6, .ncol = 1, .xadj = -5, .pos = 74 }, // 44 [2]
	{ .l0 = 0, .r0 = 5, .ncol = 3, .xadj = -4, .pos = 76 }, // 45 [5]
	{ .l0 = 1, .r0 = 6, .ncol = 1, .xadj = -5, .pos = 81 }, // 46 [2]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 83 }, // 47 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 92 }, // 48 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -1, .pos = 101 }, // 49 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -1, .pos = 108 }, // 50 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -1, .pos = 115 }, // 51 [7]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 122 }, // 52 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -1, .pos = 131 }, // 53 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 138 }, // 54 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 147 }, // 55 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 156 }, // 56 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 165 }, // 57 [9]
	{ .l0 = 1, .r0 = 6, .ncol = 1, .xadj = -5, .pos = 174 }, // 58 [2]
	{ .l0 = 1, .r0 = 6, .ncol = 1, .xadj = -5, .pos = 176 }, // 59 [2]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 178 }, // 60 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 188 }, // 61 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 198 }, // 62 [10]
	{ .l0 = 0, .r0 = 3, .ncol = 5, .xadj = -2, .pos = 208 }, // 63 [7]
    },
    .data       = {
	127, 1,	// 33
	7, 56, 0,	// 34
	32, 32, 143, 15, 74, 195, 135, 19, 16, 0,	// 35
	206, 209, 200, 255, 34, 50, 14,	// 36
	6, 73, 134, 13, 240, 97, 145, 112, 0,	// 37
	240, 112, 76, 66, 114, 98, 28, 72, 192, 5, 34,	// 38
	3, 56, 192, 0, 0,	// 39
	252, 17, 80, 0, 1,	// 40
	1, 20, 16, 127, 0,	// 41
	2, 112, 192, 0, 28, 32, 0,	// 42
	32, 0, 1, 8, 252, 3, 2, 16, 128, 0,	// 43
	0, 7,	// 44
	32, 0, 1, 8, 0,	// 45
	0, 1,	// 46
	0, 4, 28, 56, 112, 224, 128, 0, 0,	// 47
	124, 16, 68, 64, 2, 34, 8, 62, 0,	// 48
	1, 9, 200, 127, 0, 2, 16,	// 49
	134, 9, 74, 72, 34, 226, 16,	// 50
	131, 137, 72, 68, 34, 226, 14,	// 51
	48, 192, 1, 9, 70, 242, 31, 144, 0,	// 52
	143, 73, 72, 66, 50, 19, 15,	// 53
	124, 144, 68, 66, 18, 146, 152, 121, 0,	// 54
	129, 9, 71, 12, 50, 80, 128, 1, 0,	// 55
	230, 200, 76, 68, 34, 146, 27, 115, 0,	// 56
	158, 25, 73, 72, 66, 34, 9, 62, 0,	// 57
	8, 1,	// 58
	136, 7,	// 59
	16, 128, 1, 30, 144, 64, 8, 66, 8, 4,	// 60
	80, 128, 2, 20, 160, 0, 5, 40, 64, 1,	// 61
	2, 33, 4, 33, 144, 128, 7, 24, 128, 0,	// 62
	7, 8, 64, 92, 50, 96, 0,	// 63

    }
};
