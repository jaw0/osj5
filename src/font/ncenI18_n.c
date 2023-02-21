
// file: font/ncenI18.bdf
// font: -Adobe-New Century Schoolbook-Medium-I-Normal--18-180-75-75-P-104-ISO10646-1

#include <font.h>

const struct Font font_ncenI18_n = {
    .type       = 1,
    .name	= "ncenI18_n",
    .height	= 17,
    .width	= 16,
    .lineheight = 18,
    .bytescol	= 4,
    .numcol     = 16,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 10, .ncol = 4, .xadj = -9, .pos = 0 }, // 33 [9]
	{ .l0 = 2, .r0 = 9, .ncol = 5, .xadj = -9, .pos = 9 }, // 34 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 10, .xadj = -5, .pos = 20 }, // 35 [22]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 42 }, // 36 [20]
	{ .l0 = 1, .r0 = 0, .ncol = 15, .xadj = 0, .pos = 62 }, // 37 [32]
	{ .l0 = 1, .r0 = 1, .ncol = 14, .xadj = -1, .pos = 94 }, // 38 [30]
	{ .l0 = 2, .r0 = 13, .ncol = 1, .xadj = -12, .pos = 124 }, // 39 [3]
	{ .l0 = 1, .r0 = 9, .ncol = 6, .xadj = -9, .pos = 127 }, // 40 [13]
	{ .l0 = 0, .r0 = 10, .ncol = 6, .xadj = -9, .pos = 140 }, // 41 [13]
	{ .l0 = 1, .r0 = 7, .ncol = 8, .xadj = -7, .pos = 153 }, // 42 [17]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 170 }, // 43 [20]
	{ .l0 = 0, .r0 = 13, .ncol = 3, .xadj = -11, .pos = 190 }, // 44 [7]
	{ .l0 = 0, .r0 = 11, .ncol = 5, .xadj = -10, .pos = 197 }, // 45 [11]
	{ .l0 = 1, .r0 = 13, .ncol = 2, .xadj = -11, .pos = 208 }, // 46 [5]
	{ .l0 = 2, .r0 = 9, .ncol = 5, .xadj = -6, .pos = 213 }, // 47 [11]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 224 }, // 48 [20]
	{ .l0 = 2, .r0 = 8, .ncol = 6, .xadj = -6, .pos = 244 }, // 49 [13]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 257 }, // 50 [20]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 277 }, // 51 [20]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 297 }, // 52 [20]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 317 }, // 53 [20]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 337 }, // 54 [20]
	{ .l0 = 2, .r0 = 5, .ncol = 9, .xadj = -6, .pos = 357 }, // 55 [20]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 377 }, // 56 [20]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -6, .pos = 397 }, // 57 [20]
	{ .l0 = 1, .r0 = 12, .ncol = 3, .xadj = -11, .pos = 417 }, // 58 [7]
	{ .l0 = 0, .r0 = 12, .ncol = 4, .xadj = -11, .pos = 424 }, // 59 [9]
	{ .l0 = 0, .r0 = 6, .ncol = 10, .xadj = -5, .pos = 433 }, // 60 [22]
	{ .l0 = 1, .r0 = 6, .ncol = 9, .xadj = -5, .pos = 455 }, // 61 [20]
	{ .l0 = 1, .r0 = 5, .ncol = 10, .xadj = -5, .pos = 475 }, // 62 [22]
	{ .l0 = 2, .r0 = 7, .ncol = 7, .xadj = -7, .pos = 497 }, // 63 [15]
    },
    .data       = {
	0, 48, 192, 103, 252, 1, 120, 0, 0,	// 33
	31, 0, 6, 0, 0, 0, 248, 0, 48, 0, 0,	// 34
	0, 2, 64, 4, 128, 248, 0, 31, 224, 35, 0, 196, 7, 248, 0, 31, 1, 32, 2, 64, 0, 0,	// 35
	0, 48, 224, 112, 176, 131, 35, 198, 33, 127, 194, 49, 194, 224, 6, 135, 3, 6, 0, 0,	// 36
	112, 0, 248, 1, 56, 2, 24, 4, 16, 4, 35, 134, 129, 195, 0, 97, 0, 50, 28, 26, 126, 12, 142, 0, 6, 1, 4, 1, 136, 1, 224, 0,	// 37
	0, 15, 0, 63, 0, 195, 224, 2, 225, 7, 34, 60, 68, 232, 137, 8, 15, 31, 56, 28, 80, 0, 153, 0, 14, 1, 12, 1, 8, 0,	// 38
	31, 0, 0,	// 39
	192, 15, 224, 127, 224, 192, 97, 0, 36, 0, 32, 0, 0,	// 40
	0, 128, 0, 128, 4, 192, 112, 224, 192, 255, 0, 126, 0,	// 41
	56, 0, 36, 1, 88, 3, 192, 1, 128, 3, 192, 26, 128, 36, 0, 28, 0,	// 42
	0, 1, 0, 2, 0, 4, 0, 8, 0, 255, 1, 32, 0, 64, 0, 128, 0, 0, 1, 0,	// 43
	0, 0, 1, 96, 1, 192, 1,	// 44
	0, 1, 0, 2, 0, 4, 0, 8, 0, 16, 0,	// 45
	0, 48, 0, 96, 0,	// 46
	0, 112, 0, 28, 0, 7, 192, 1, 112, 0, 0,	// 47
	192, 15, 240, 63, 240, 192, 16, 0, 17, 0, 34, 0, 194, 192, 3, 255, 3, 252, 0, 0,	// 48
	0, 32, 0, 64, 16, 248, 32, 255, 225, 31, 226, 3, 4,	// 49
	0, 48, 24, 112, 56, 240, 16, 176, 17, 48, 35, 48, 70, 56, 12, 63, 24, 30, 12, 0,	// 50
	0, 24, 0, 112, 48, 128, 112, 2, 17, 4, 34, 24, 67, 232, 131, 207, 3, 14, 0, 0,	// 51
	0, 6, 0, 11, 0, 17, 0, 33, 129, 65, 130, 192, 135, 248, 143, 255, 18, 31, 36, 0,	// 52
	0, 24, 0, 112, 192, 129, 120, 1, 49, 2, 98, 4, 195, 248, 131, 225, 3, 1, 0, 0,	// 53
	192, 15, 240, 63, 240, 194, 16, 2, 17, 2, 34, 4, 66, 8, 135, 227, 7, 134, 3, 0,	// 54
	12, 0, 6, 0, 12, 224, 24, 240, 49, 56, 96, 28, 192, 14, 128, 7, 0, 3, 0, 0,	// 55
	0, 14, 0, 62, 112, 134, 240, 3, 49, 6, 34, 8, 68, 48, 134, 209, 15, 30, 7, 0,	// 56
	112, 24, 248, 113, 56, 132, 16, 8, 17, 16, 34, 16, 194, 208, 3, 255, 3, 252, 0, 0,	// 57
	0, 48, 192, 96, 128, 1, 0,	// 58
	0, 0, 1, 96, 129, 193, 1, 3, 0,	// 59
	0, 1, 0, 2, 0, 14, 0, 20, 0, 108, 0, 136, 0, 24, 3, 16, 4, 48, 24, 32, 32, 0,	// 60
	64, 2, 128, 4, 0, 9, 0, 18, 0, 36, 0, 72, 0, 144, 0, 32, 1, 64, 2, 0,	// 61
	16, 16, 96, 48, 128, 32, 0, 99, 0, 68, 0, 216, 0, 160, 0, 192, 1, 0, 1, 0, 2, 0,	// 62
	128, 49, 140, 101, 4, 9, 8, 9, 16, 3, 224, 3, 128, 3, 0,	// 63

    }
};
