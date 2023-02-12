
// file: font/luBIS08.bdf
// font: -B&H-Lucida-Bold-I-Normal-Sans-8-80-75-75-P-49-ISO10646-1

#include <font.h>

const struct Font font_luBIS08_n = {
    .type       = 1,
    .name	= "luBIS08_n",
    .height	= 9,
    .width	= 8,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 0, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 0 }, // 33 [4]
	{ .l0 = 1, .r0 = 3, .ncol = 4, .xadj = -4, .pos = 4 }, // 34 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 9 }, // 35 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 15 }, // 36 [6]
	{ .l0 = 1, .r0 = 0, .ncol = 7, .xadj = -1, .pos = 21 }, // 37 [8]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 29 }, // 38 [7]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -6, .pos = 36 }, // 39 [3]
	{ .l0 = 1, .r0 = 4, .ncol = 3, .xadj = -5, .pos = 39 }, // 40 [4]
	{ .l0 = 0, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 43 }, // 41 [4]
	{ .l0 = 1, .r0 = 4, .ncol = 3, .xadj = -4, .pos = 47 }, // 42 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 51 }, // 43 [6]
	{ .l0 = 0, .r0 = 6, .ncol = 2, .xadj = -5, .pos = 57 }, // 44 [3]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -6, .pos = 60 }, // 45 [3]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -5, .pos = 63 }, // 46 [3]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -3, .pos = 66 }, // 47 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 4, .xadj = -3, .pos = 73 }, // 48 [5]
	{ .l0 = 2, .r0 = 3, .ncol = 3, .xadj = -3, .pos = 78 }, // 49 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 82 }, // 50 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 88 }, // 51 [6]
	{ .l0 = 0, .r0 = 3, .ncol = 5, .xadj = -3, .pos = 94 }, // 52 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 100 }, // 53 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 106 }, // 54 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 112 }, // 55 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 118 }, // 56 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 124 }, // 57 [6]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -5, .pos = 130 }, // 58 [3]
	{ .l0 = 0, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 133 }, // 59 [4]
	{ .l0 = 0, .r0 = 3, .ncol = 5, .xadj = -3, .pos = 137 }, // 60 [6]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 143 }, // 61 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -3, .pos = 149 }, // 62 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 4, .xadj = -4, .pos = 156 }, // 63 [5]
    },
    .data       = {
	64, 188, 24, 0,	// 33
	6, 0, 0, 48, 0,	// 34
	104, 240, 184, 209, 225, 2,	// 35
	64, 152, 251, 153, 35, 0,	// 36
	92, 100, 112, 64, 64, 68, 140, 24,	// 37
	48, 144, 56, 209, 99, 6, 3,	// 38
	14, 4, 0,	// 39
	248, 25, 8, 0,	// 40
	0, 197, 241, 0,	// 41
	12, 20, 48, 0,	// 42
	16, 224, 64, 224, 0, 1,	// 43
	64, 129, 1,	// 44
	16, 32, 0,	// 45
	64, 128, 0,	// 46
	0, 1, 129, 193, 64, 64, 0,	// 47
	56, 140, 136, 241, 1,	// 48
	98, 252, 24, 0,	// 49
	64, 196, 72, 81, 226, 0,	// 50
	64, 148, 40, 209, 99, 2,	// 51
	16, 48, 80, 241, 99, 1,	// 52
	64, 156, 40, 145, 33, 0,	// 53
	56, 152, 40, 81, 35, 1,	// 54
	66, 100, 104, 48, 32, 0,	// 55
	112, 184, 40, 209, 98, 3,	// 56
	72, 172, 72, 145, 193, 1,	// 57
	72, 144, 0,	// 58
	64, 145, 35, 0,	// 59
	16, 96, 160, 64, 66, 0,	// 60
	40, 80, 160, 64, 129, 2,	// 61
	64, 64, 176, 64, 129, 2, 2,	// 62
	82, 164, 40, 48, 0,	// 63

    }
};
