
// file: font/clR6x12.bdf
// font: -Schumacher-Clean-Medium-R-Normal--12-120-75-75-C-60-ISO10646-1

#include <font.h>

const struct Font font_clR6x12_n = {
    .type       = 1,
    .name	= "clR6x12_n",
    .height	= 12,
    .width	= 6,
    .bytescol	= 2,
    .numcol     = 6,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 2 }, // 34 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 7 }, // 35 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 15 }, // 36 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 23 }, // 37 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 31 }, // 38 [8]
	{ .l0 = 2, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 39 }, // 39 [2]
	{ .l0 = 2, .r0 = 1, .ncol = 3, .xadj = 0, .pos = 41 }, // 40 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 46 }, // 41 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 51 }, // 42 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 59 }, // 43 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 67 }, // 44 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 72 }, // 45 [8]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 80 }, // 46 [3]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 83 }, // 47 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 91 }, // 48 [8]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 99 }, // 49 [3]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 102 }, // 50 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 110 }, // 51 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 118 }, // 52 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 126 }, // 53 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 134 }, // 54 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 142 }, // 55 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 150 }, // 56 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 158 }, // 57 [8]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 166 }, // 58 [3]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 169 }, // 59 [5]
	{ .l0 = 0, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 174 }, // 60 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 183 }, // 61 [8]
	{ .l0 = 0, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 191 }, // 62 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 200 }, // 63 [8]
    },
    .data       = {
	126, 1,	// 33
	14, 0, 0, 14, 0,	// 34
	80, 192, 31, 80, 192, 31, 80, 0,	// 35
	144, 128, 10, 252, 129, 10, 72, 0,	// 36
	140, 192, 4, 32, 0, 25, 136, 1,	// 37
	216, 64, 18, 68, 65, 8, 64, 1,	// 38
	14, 0,	// 39
	248, 96, 48, 1, 4,	// 40
	1, 100, 48, 248, 0,	// 41
	80, 0, 2, 248, 0, 2, 80, 0,	// 42
	32, 0, 2, 248, 0, 2, 32, 0,	// 43
	0, 4, 56, 128, 1,	// 44
	32, 0, 2, 32, 0, 2, 32, 0,	// 45
	128, 1, 24,	// 46
	0, 3, 12, 48, 192, 0, 3, 0,	// 47
	252, 32, 18, 18, 161, 16, 252, 0,	// 48
	4, 224, 31,	// 49
	132, 33, 20, 34, 33, 17, 12, 1,	// 50
	132, 32, 16, 18, 33, 17, 236, 0,	// 51
	64, 0, 7, 76, 225, 31, 64, 1,	// 52
	158, 32, 17, 18, 33, 17, 226, 0,	// 53
	248, 64, 17, 18, 33, 17, 224, 0,	// 54
	6, 32, 0, 130, 33, 6, 30, 0,	// 55
	236, 32, 17, 18, 33, 17, 236, 0,	// 56
	28, 32, 18, 34, 33, 10, 124, 0,	// 57
	152, 129, 25,	// 58
	0, 132, 57, 152, 1,	// 59
	32, 0, 2, 80, 0, 5, 136, 128, 8,	// 60
	80, 0, 5, 80, 0, 5, 80, 0,	// 61
	136, 128, 8, 80, 0, 5, 32, 0, 2,	// 62
	4, 32, 0, 98, 33, 1, 12, 0,	// 63

    }
};
