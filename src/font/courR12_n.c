
// file: font/courR12.bdf
// font: -Adobe-Courier-Medium-R-Normal--12-120-75-75-M-70-ISO10646-1

#include <font.h>

const struct Font font_courR12_n = {
    .type       = 1,
    .name	= "courR12_n",
    .height	= 11,
    .width	= 7,
    .bytescol	= 2,
    .numcol     = 7,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 3, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 0 }, // 33 [2]
	{ .l0 = 2, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 2 }, // 34 [5]
	{ .l0 = 0, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 7 }, // 35 [10]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 17 }, // 36 [7]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 24 }, // 37 [9]
	{ .l0 = 0, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 33 }, // 38 [10]
	{ .l0 = 3, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 43 }, // 39 [2]
	{ .l0 = 3, .r0 = 1, .ncol = 3, .xadj = 0, .pos = 45 }, // 40 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 3, .xadj = 0, .pos = 50 }, // 41 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 55 }, // 42 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 62 }, // 43 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 2, .xadj = 0, .pos = 69 }, // 44 [3]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 72 }, // 45 [7]
	{ .l0 = 2, .r0 = 4, .ncol = 1, .xadj = 0, .pos = 79 }, // 46 [2]
	{ .l0 = 1, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 81 }, // 47 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 90 }, // 48 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 97 }, // 49 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 104 }, // 50 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 111 }, // 51 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 118 }, // 52 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 127 }, // 53 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 136 }, // 54 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 143 }, // 55 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 150 }, // 56 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 157 }, // 57 [7]
	{ .l0 = 3, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 164 }, // 58 [2]
	{ .l0 = 2, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 166 }, // 59 [3]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 169 }, // 60 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 175 }, // 61 [7]
	{ .l0 = 2, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 182 }, // 62 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 188 }, // 63 [7]
    },
    .data       = {
	127, 1,	// 33
	14, 0, 128, 3, 0,	// 34
	64, 64, 14, 30, 156, 131, 7, 39, 32, 0,	// 35
	204, 144, 200, 204, 68, 66, 12,	// 36
	68, 80, 129, 42, 168, 2, 21, 68, 0,	// 37
	192, 96, 137, 76, 68, 98, 12, 80, 64, 4,	// 38
	14, 0,	// 39
	248, 48, 88, 0, 1,	// 40
	1, 52, 24, 62, 0,	// 41
	8, 64, 129, 7, 80, 128, 0,	// 42
	32, 0, 1, 62, 64, 0, 2,	// 43
	0, 2, 12,	// 44
	32, 0, 1, 8, 64, 0, 2,	// 45
	0, 1,	// 46
	0, 2, 12, 24, 48, 96, 128, 0, 0,	// 47
	254, 8, 72, 64, 2, 226, 15,	// 48
	2, 17, 200, 127, 0, 2, 16,	// 49
	142, 9, 74, 72, 34, 226, 24,	// 50
	130, 8, 72, 68, 34, 226, 14,	// 51
	96, 128, 2, 19, 132, 242, 31, 160, 0,	// 52
	128, 248, 72, 68, 34, 18, 145, 112, 0,	// 53
	252, 144, 72, 68, 34, 18, 14,	// 54
	3, 8, 64, 112, 122, 48, 0,	// 55
	238, 136, 72, 68, 34, 226, 14,	// 56
	30, 9, 73, 72, 66, 225, 7,	// 57
	16, 1,	// 58
	0, 130, 12,	// 59
	32, 128, 2, 34, 8, 2,	// 60
	80, 128, 2, 20, 160, 0, 5,	// 61
	4, 65, 4, 20, 64, 0,	// 62
	4, 16, 128, 88, 36, 192, 0,	// 63

    }
};
