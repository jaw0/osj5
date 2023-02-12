
// file: font/courR14.bdf
// font: -Adobe-Courier-Medium-R-Normal--14-140-75-75-M-90-ISO10646-1

#include <font.h>

const struct Font font_courR14_n = {
    .type       = 1,
    .name	= "courR14_n",
    .height	= 13,
    .width	= 9,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 6, .ncol = 1, .xadj = 0, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = 0, .pos = 2 }, // 34 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = 0, .pos = 9 }, // 35 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = 0, .pos = 18 }, // 36 [9]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = 0, .pos = 27 }, // 37 [12]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 39 }, // 38 [10]
	{ .l0 = 2, .r0 = 6, .ncol = 1, .xadj = 0, .pos = 49 }, // 39 [2]
	{ .l0 = 2, .r0 = 4, .ncol = 3, .xadj = 0, .pos = 51 }, // 40 [5]
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = 0, .pos = 56 }, // 41 [5]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = 0, .pos = 61 }, // 42 [9]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = 0, .pos = 70 }, // 43 [12]
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = 0, .pos = 82 }, // 44 [5]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 87 }, // 45 [10]
	{ .l0 = 2, .r0 = 5, .ncol = 2, .xadj = 0, .pos = 97 }, // 46 [4]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 101 }, // 47 [10]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 111 }, // 48 [10]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = 0, .pos = 121 }, // 49 [9]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 130 }, // 50 [10]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 140 }, // 51 [10]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 150 }, // 52 [10]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 160 }, // 53 [10]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 170 }, // 54 [10]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 180 }, // 55 [10]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 190 }, // 56 [10]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 200 }, // 57 [10]
	{ .l0 = 2, .r0 = 5, .ncol = 2, .xadj = 0, .pos = 210 }, // 58 [4]
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = 0, .pos = 214 }, // 59 [5]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = 0, .pos = 219 }, // 60 [12]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = 0, .pos = 231 }, // 61 [12]
	{ .l0 = 0, .r0 = 2, .ncol = 7, .xadj = 0, .pos = 243 }, // 62 [12]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = 0, .pos = 255 }, // 63 [9]
    },
    .data       = {
	254, 4,	// 33
	60, 0, 0, 0, 0, 30, 0,	// 34
	160, 128, 255, 128, 2, 254, 3, 10, 0,	// 35
	56, 131, 68, 28, 121, 34, 193, 24, 0,	// 36
	140, 64, 18, 72, 1, 182, 1, 74, 32, 9, 196, 0,	// 37
	128, 3, 142, 32, 18, 132, 129, 41, 0, 8,	// 38
	60, 0,	// 39
	240, 131, 129, 9, 64,	// 40
	2, 144, 129, 193, 15,	// 41
	144, 0, 10, 240, 0, 40, 0, 9, 0,	// 42
	64, 0, 8, 0, 1, 252, 1, 4, 128, 0, 16, 0,	// 43
	0, 24, 192, 1, 24,	// 44
	64, 0, 8, 0, 1, 32, 0, 4, 128, 0,	// 45
	0, 6, 192, 0,	// 46
	0, 12, 96, 0, 3, 24, 192, 0, 4, 0,	// 47
	252, 67, 128, 8, 16, 1, 34, 64, 248, 7,	// 48
	8, 132, 128, 248, 31, 0, 2, 64, 0,	// 49
	12, 70, 160, 8, 18, 33, 34, 66, 56, 12,	// 50
	4, 66, 128, 136, 16, 17, 34, 66, 184, 7,	// 51
	192, 1, 38, 48, 4, 129, 226, 127, 0, 10,	// 52
	0, 194, 135, 136, 16, 17, 34, 66, 132, 7,	// 53
	248, 129, 72, 136, 16, 17, 34, 66, 128, 7,	// 54
	6, 64, 0, 8, 0, 193, 35, 7, 28, 0,	// 55
	220, 67, 132, 136, 16, 17, 34, 66, 184, 7,	// 56
	60, 64, 136, 8, 17, 33, 66, 34, 240, 3,	// 57
	48, 6, 198, 0,	// 58
	0, 24, 198, 193, 24,	// 59
	64, 0, 20, 128, 2, 136, 0, 17, 16, 4, 130, 0,	// 60
	160, 0, 20, 128, 2, 80, 0, 10, 64, 1, 40, 0,	// 61
	8, 2, 65, 64, 4, 136, 0, 10, 64, 1, 16, 0,	// 62
	24, 128, 0, 16, 22, 34, 128, 3, 0,	// 63

    }
};
