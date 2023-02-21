
// file: font/9x15.bdf
// font: -Misc-Fixed-Medium-R-Normal--15-140-75-75-C-90-ISO10646-1

#include <font.h>

const struct Font font_9x15_n = {
    .type       = 1,
    .name	= "9x15_n",
    .height	= 15,
    .width	= 9,
    .lineheight = 15,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 4, .r0 = 4, .ncol = 1, .xadj = 0, .pos = 0 }, // 33 [2]
	{ .l0 = 3, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 2 }, // 34 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = 0, .pos = 10 }, // 35 [12]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 22 }, // 36 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 36 }, // 37 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 50 }, // 38 [14]
	{ .l0 = 4, .r0 = 4, .ncol = 1, .xadj = 0, .pos = 64 }, // 39 [2]
	{ .l0 = 3, .r0 = 3, .ncol = 3, .xadj = 0, .pos = 66 }, // 40 [6]
	{ .l0 = 3, .r0 = 3, .ncol = 3, .xadj = 0, .pos = 72 }, // 41 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 78 }, // 42 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 92 }, // 43 [14]
	{ .l0 = 4, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 106 }, // 44 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 110 }, // 45 [14]
	{ .l0 = 4, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 124 }, // 46 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 128 }, // 47 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 142 }, // 48 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 156 }, // 49 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 170 }, // 50 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 184 }, // 51 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 198 }, // 52 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 212 }, // 53 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 226 }, // 54 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 240 }, // 55 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 254 }, // 56 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 268 }, // 57 [14]
	{ .l0 = 4, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 282 }, // 58 [4]
	{ .l0 = 4, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 286 }, // 59 [4]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 290 }, // 60 [10]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 300 }, // 61 [14]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 314 }, // 62 [10]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 324 }, // 63 [14]
    },
    .data       = {
	254, 12,	// 33
	28, 0, 0, 0, 0, 128, 3, 0,	// 34
	32, 1, 252, 3, 72, 0, 36, 128, 127, 0, 9, 0,	// 35
	48, 4, 36, 4, 34, 130, 255, 131, 136, 64, 72, 64, 24, 0,	// 36
	24, 8, 18, 3, 70, 0, 24, 0, 98, 192, 72, 16, 24, 0,	// 37
	56, 7, 98, 4, 49, 2, 167, 0, 32, 0, 40, 0, 34, 0,	// 38
	28, 0,	// 39
	240, 3, 6, 134, 0, 4,	// 40
	2, 16, 6, 6, 252, 0,	// 41
	136, 0, 40, 0, 8, 128, 63, 0, 2, 128, 2, 32, 2, 0,	// 42
	128, 0, 64, 0, 32, 0, 254, 0, 8, 0, 4, 0, 2, 0,	// 43
	0, 76, 0, 30,	// 44
	128, 0, 64, 0, 32, 0, 16, 0, 8, 0, 4, 0, 2, 0,	// 45
	0, 12, 0, 6,	// 46
	0, 8, 0, 3, 64, 0, 24, 0, 2, 192, 0, 16, 0, 0,	// 47
	240, 3, 4, 2, 1, 130, 0, 65, 128, 64, 32, 192, 15, 0,	// 48
	32, 8, 8, 4, 2, 130, 255, 1, 128, 0, 64, 0, 32, 0,	// 49
	24, 12, 2, 5, 65, 130, 16, 65, 132, 32, 65, 96, 32, 0,	// 50
	4, 4, 2, 4, 1, 130, 8, 65, 134, 160, 66, 48, 30, 0,	// 51
	128, 1, 160, 0, 72, 0, 34, 128, 16, 224, 127, 0, 4, 0,	// 52
	124, 4, 34, 4, 9, 130, 4, 65, 130, 32, 65, 16, 31, 0,	// 53
	240, 7, 68, 4, 17, 130, 8, 65, 132, 32, 66, 0, 30, 0,	// 54
	4, 0, 2, 0, 1, 131, 96, 64, 12, 160, 1, 48, 0, 0,	// 55
	16, 3, 84, 2, 17, 130, 8, 65, 132, 64, 37, 64, 12, 0,	// 56
	120, 0, 66, 4, 33, 130, 16, 65, 136, 32, 34, 224, 15, 0,	// 57
	96, 12, 48, 6,	// 58
	96, 76, 48, 30,	// 59
	192, 0, 144, 0, 132, 0, 129, 64, 128, 0,	// 60
	64, 2, 32, 1, 144, 0, 72, 0, 36, 0, 18, 0, 9, 0,	// 61
	4, 8, 4, 2, 132, 0, 36, 0, 12, 0,	// 62
	24, 0, 2, 0, 1, 128, 96, 65, 8, 32, 2, 224, 0, 0,	// 63

    }
};
