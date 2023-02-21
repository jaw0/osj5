
// file: font/ncenI10.bdf
// font: -Adobe-New Century Schoolbook-Medium-I-Normal--10-100-75-75-P-60-ISO10646-1

#include <font.h>

const struct Font font_ncenI10_n = {
    .type       = 1,
    .name	= "ncenI10_n",
    .height	= 10,
    .width	= 9,
    .lineheight = 10,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 0 }, // 33 [4]
	{ .l0 = 2, .r0 = 4, .ncol = 3, .xadj = -3, .pos = 4 }, // 34 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 8 }, // 35 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 17 }, // 36 [7]
	{ .l0 = 1, .r0 = 0, .ncol = 8, .xadj = 0, .pos = 24 }, // 37 [10]
	{ .l0 = 1, .r0 = 0, .ncol = 8, .xadj = 0, .pos = 34 }, // 38 [10]
	{ .l0 = 2, .r0 = 6, .ncol = 1, .xadj = -5, .pos = 44 }, // 39 [2]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -4, .pos = 46 }, // 40 [5]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -4, .pos = 51 }, // 41 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -3, .pos = 56 }, // 42 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -3, .pos = 63 }, // 43 [7]
	{ .l0 = 0, .r0 = 7, .ncol = 2, .xadj = -7, .pos = 70 }, // 44 [3]
	{ .l0 = 1, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 73 }, // 45 [4]
	{ .l0 = 1, .r0 = 7, .ncol = 1, .xadj = -7, .pos = 77 }, // 46 [2]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 79 }, // 47 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 86 }, // 48 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -4, .pos = 93 }, // 49 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 98 }, // 50 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -4, .pos = 105 }, // 51 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -4, .pos = 112 }, // 52 [5]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -4, .pos = 117 }, // 53 [5]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -4, .pos = 122 }, // 54 [5]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -4, .pos = 127 }, // 55 [5]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -4, .pos = 132 }, // 56 [5]
	{ .l0 = 1, .r0 = 4, .ncol = 4, .xadj = -4, .pos = 137 }, // 57 [5]
	{ .l0 = 1, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 142 }, // 58 [3]
	{ .l0 = 0, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 145 }, // 59 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 149 }, // 60 [8]
	{ .l0 = 1, .r0 = 3, .ncol = 5, .xadj = -3, .pos = 157 }, // 61 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = -2, .pos = 164 }, // 62 [8]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = -3, .pos = 172 }, // 63 [5]
    },
    .data       = {
	128, 225, 96, 0,	// 33
	14, 0, 224, 0,	// 34
	64, 64, 7, 7, 119, 112, 112, 1, 1,	// 35
	128, 49, 44, 209, 56, 6, 0,	// 36
	28, 72, 224, 24, 25, 28, 24, 7, 18, 56,	// 37
	224, 64, 196, 145, 72, 210, 48, 6, 22, 8,	// 38
	14, 0,	// 39
	224, 97, 72, 128, 0,	// 40
	0, 2, 36, 12, 15,	// 41
	20, 32, 224, 3, 2, 20, 0,	// 42
	64, 0, 1, 31, 16, 64, 0,	// 43
	0, 2, 6,	// 44
	64, 0, 1, 4,	// 45
	128, 1,	// 46
	0, 3, 3, 3, 3, 2, 0,	// 47
	240, 49, 36, 144, 48, 62, 0,	// 48
	0, 17, 68, 158, 71,	// 49
	128, 49, 37, 146, 100, 12, 0,	// 50
	128, 81, 36, 145, 58, 4, 0,	// 51
	96, 96, 69, 158, 87,	// 52
	144, 121, 36, 137, 24,	// 53
	240, 176, 36, 145, 60,	// 54
	6, 8, 167, 131, 1,	// 55
	224, 113, 36, 145, 59,	// 56
	60, 137, 36, 13, 15,	// 57
	128, 193, 0,	// 58
	0, 2, 6, 3,	// 59
	64, 0, 1, 10, 40, 16, 65, 4,	// 60
	160, 128, 2, 10, 40, 160, 0,	// 61
	16, 65, 4, 10, 40, 64, 0, 1,	// 62
	100, 73, 161, 0, 1,	// 63

    }
};
