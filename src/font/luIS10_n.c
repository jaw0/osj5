
// file: font/luIS10.bdf
// font: -B&H-Lucida-Medium-I-Normal-Sans-10-100-75-75-P-59-ISO10646-1

#include <font.h>

const struct Font font_luIS10_n = {
    .type       = 1,
    .name	= "luIS10_n",
    .height	= 9,
    .width	= 8,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 4, .ncol = 3, .xadj = -5, .pos = 0 }, // 33 [4]
	{ .l0 = 2, .r0 = 3, .ncol = 3, .xadj = -4, .pos = 4 }, // 34 [4]
	{ .l0 = 1, .r0 = 0, .ncol = 7, .xadj = -1, .pos = 8 }, // 35 [8]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 16 }, // 36 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 23 }, // 37 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 30 }, // 38 [7]
	{ .l0 = 2, .r0 = 5, .ncol = 1, .xadj = -6, .pos = 37 }, // 39 [2]
	{ .l0 = 1, .r0 = 3, .ncol = 4, .xadj = -5, .pos = 39 }, // 40 [5]
	{ .l0 = 0, .r0 = 4, .ncol = 4, .xadj = -5, .pos = 44 }, // 41 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 49 }, // 42 [6]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 55 }, // 43 [7]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -5, .pos = 62 }, // 44 [3]
	{ .l0 = 2, .r0 = 4, .ncol = 2, .xadj = -5, .pos = 65 }, // 45 [3]
	{ .l0 = 2, .r0 = 5, .ncol = 1, .xadj = -5, .pos = 68 }, // 46 [2]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 70 }, // 47 [7]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 77 }, // 48 [6]
	{ .l0 = 3, .r0 = 2, .ncol = 3, .xadj = -1, .pos = 83 }, // 49 [4]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 87 }, // 50 [6]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 93 }, // 51 [6]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 99 }, // 52 [6]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 105 }, // 53 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 112 }, // 54 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 119 }, // 55 [7]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 126 }, // 56 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 132 }, // 57 [7]
	{ .l0 = 2, .r0 = 4, .ncol = 2, .xadj = -5, .pos = 139 }, // 58 [3]
	{ .l0 = 1, .r0 = 4, .ncol = 3, .xadj = -5, .pos = 142 }, // 59 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 146 }, // 60 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 153 }, // 61 [7]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = -1, .pos = 160 }, // 62 [7]
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = -3, .pos = 167 }, // 63 [5]
    },
    .data       = {
	192, 48, 24, 0,	// 33
	7, 0, 28, 0,	// 34
	32, 208, 225, 112, 6, 195, 5, 2,	// 35
	128, 24, 201, 255, 36, 70, 0,	// 36
	4, 148, 144, 128, 128, 132, 20,	// 37
	224, 40, 105, 82, 99, 4, 22,	// 38
	7, 0,	// 39
	240, 24, 10, 8, 0,	// 40
	0, 1, 133, 241, 0,	// 41
	8, 20, 16, 80, 32, 0,	// 42
	16, 32, 192, 225, 0, 1, 2,	// 43
	0, 129, 1,	// 44
	16, 32, 0,	// 45
	192, 0,	// 46
	128, 129, 128, 192, 64, 96, 0,	// 47
	112, 24, 9, 18, 195, 1,	// 48
	4, 232, 121, 0,	// 49
	192, 68, 73, 146, 196, 0,	// 50
	128, 4, 73, 146, 195, 0,	// 51
	48, 80, 144, 144, 231, 2,	// 52
	128, 24, 41, 82, 34, 67, 0,	// 53
	96, 48, 81, 146, 36, 70, 0,	// 54
	128, 132, 136, 144, 160, 192, 0,	// 55
	96, 56, 73, 146, 196, 6,	// 56
	128, 24, 73, 146, 34, 131, 1,	// 57
	192, 24, 0,	// 58
	0, 129, 49, 0,	// 59
	16, 32, 160, 64, 66, 128, 0,	// 60
	32, 80, 160, 64, 129, 2, 1,	// 61
	64, 128, 144, 64, 1, 1, 2,	// 62
	196, 36, 72, 96, 0,	// 63

    }
};
