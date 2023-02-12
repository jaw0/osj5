
// file: font/luBIS10.bdf
// font: -B&H-Lucida-Bold-I-Normal-Sans-10-100-75-75-P-67-ISO10646-1

#include <font.h>

const struct Font font_luBIS10_n = {
    .type       = 1,
    .name	= "luBIS10_n",
    .height	= 9,
    .width	= 9,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -5, .pos = 0 }, // 33 [5]
	{ .l0 = 2, .r0 = 4, .ncol = 3, .xadj = -4, .pos = 5 }, // 34 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = -2, .pos = 9 }, // 35 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -2, .pos = 18 }, // 36 [8]
	{ .l0 = 1, .r0 = 0, .ncol = 8, .xadj = 0, .pos = 26 }, // 37 [9]
	{ .l0 = 1, .r0 = 0, .ncol = 8, .xadj = -1, .pos = 35 }, // 38 [9]
	{ .l0 = 2, .r0 = 6, .ncol = 1, .xadj = -6, .pos = 44 }, // 39 [2]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -5, .pos = 46 }, // 40 [6]
	{ .l0 = 0, .r0 = 4, .ncol = 5, .xadj = -5, .pos = 52 }, // 41 [6]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 58 }, // 42 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 65 }, // 43 [7]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 72 }, // 44 [4]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 76 }, // 45 [3]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 79 }, // 46 [3]
	{ .l0 = 0, .r0 = 3, .ncol = 6, .xadj = -3, .pos = 82 }, // 47 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 89 }, // 48 [7]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -2, .pos = 96 }, // 49 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 101 }, // 50 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 108 }, // 51 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 115 }, // 52 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 122 }, // 53 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -2, .pos = 129 }, // 54 [8]
	{ .l0 = 2, .r0 = 1, .ncol = 6, .xadj = -2, .pos = 137 }, // 55 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -2, .pos = 144 }, // 56 [8]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -2, .pos = 152 }, // 57 [8]
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 160 }, // 58 [4]
	{ .l0 = 0, .r0 = 5, .ncol = 4, .xadj = -5, .pos = 164 }, // 59 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 169 }, // 60 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 176 }, // 61 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 183 }, // 62 [7]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 190 }, // 63 [6]
    },
    .data       = {
	192, 176, 121, 48, 0,	// 33
	7, 0, 28, 0,	// 34
	32, 208, 225, 243, 225, 12, 134, 11, 4,	// 35
	128, 24, 249, 215, 245, 79, 140, 0,	// 36
	4, 148, 185, 161, 129, 133, 149, 57, 32,	// 37
	96, 232, 121, 210, 229, 134, 24, 44, 8,	// 38
	7, 0,	// 39
	240, 248, 59, 28, 16, 0,	// 40
	0, 1, 135, 251, 227, 1,	// 41
	8, 20, 24, 96, 160, 64, 0,	// 42
	16, 32, 192, 225, 0, 1, 2,	// 43
	0, 129, 3, 3,	// 44
	16, 32, 0,	// 45
	192, 128, 1,	// 46
	128, 193, 195, 225, 240, 96, 0,	// 47
	112, 248, 25, 18, 230, 135, 3,	// 48
	4, 232, 249, 243, 0,	// 49
	192, 200, 137, 147, 230, 141, 1,	// 50
	64, 8, 73, 146, 231, 135, 1,	// 51
	48, 80, 144, 243, 231, 3, 4,	// 52
	64, 56, 89, 178, 103, 198, 0,	// 53
	96, 240, 113, 178, 36, 79, 12, 1,	// 54
	192, 204, 217, 176, 224, 192, 0,	// 55
	96, 248, 121, 146, 36, 207, 15, 3,	// 56
	64, 24, 121, 146, 38, 199, 7, 3,	// 57
	192, 152, 49, 0,	// 58
	0, 129, 51, 99, 0,	// 59
	16, 112, 160, 97, 66, 128, 0,	// 60
	32, 80, 160, 64, 129, 2, 1,	// 61
	64, 128, 144, 97, 129, 3, 2,	// 62
	196, 164, 73, 240, 192, 0,	// 63

    }
};
