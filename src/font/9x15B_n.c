
// file: font/9x15B.bdf
// font: -Misc-Fixed-Bold-R-Normal--15-140-75-75-C-90-ISO10646-1

#include <font.h>

const struct Font font_9x15B_n = {
    .type       = 1,
    .name	= "9x15B_n",
    .height	= 15,
    .width	= 9,
    .bytescol	= 2,
    .numcol     = 9,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 3, .r0 = 4, .ncol = 2, .xadj = 0, .pos = 0 }, // 33 [4]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 4 }, // 34 [10]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 14 }, // 35 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 28 }, // 36 [14]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 42 }, // 37 [15]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 57 }, // 38 [15]
	{ .l0 = 3, .r0 = 4, .ncol = 2, .xadj = 0, .pos = 72 }, // 39 [4]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 76 }, // 40 [10]
	{ .l0 = 2, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 86 }, // 41 [10]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 96 }, // 42 [14]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 110 }, // 43 [15]
	{ .l0 = 3, .r0 = 3, .ncol = 3, .xadj = 0, .pos = 125 }, // 44 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 131 }, // 45 [15]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = 0, .pos = 146 }, // 46 [8]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 154 }, // 47 [15]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 169 }, // 48 [15]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = 0, .pos = 184 }, // 49 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 196 }, // 50 [15]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 211 }, // 51 [15]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 226 }, // 52 [15]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 241 }, // 53 [15]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 256 }, // 54 [15]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 271 }, // 55 [15]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 286 }, // 56 [15]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 301 }, // 57 [15]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = 0, .pos = 316 }, // 58 [8]
	{ .l0 = 2, .r0 = 3, .ncol = 4, .xadj = 0, .pos = 324 }, // 59 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = 0, .pos = 332 }, // 60 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 344 }, // 61 [15]
	{ .l0 = 1, .r0 = 2, .ncol = 6, .xadj = 0, .pos = 359 }, // 62 [12]
	{ .l0 = 1, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 371 }, // 63 [14]
    },
    .data       = {
	252, 11, 254, 5,	// 33
	28, 0, 14, 0, 0, 128, 3, 192, 1, 0,	// 34
	32, 1, 252, 3, 254, 1, 36, 128, 127, 192, 63, 128, 4, 0,	// 35
	112, 4, 124, 6, 50, 130, 255, 131, 152, 192, 124, 64, 28, 0,	// 36
	24, 8, 30, 7, 198, 1, 56, 0, 14, 192, 49, 112, 60, 8, 12,	// 37
	0, 7, 220, 7, 63, 130, 28, 193, 219, 192, 56, 0, 60, 0, 19,	// 38
	60, 0, 30, 0,	// 39
	224, 1, 252, 3, 135, 195, 0, 35, 0, 1,	// 40
	2, 16, 3, 12, 135, 3, 255, 0, 30, 0,	// 41
	128, 0, 80, 1, 248, 0, 56, 0, 62, 0, 21, 0, 2, 0,	// 42
	128, 0, 64, 0, 32, 0, 254, 0, 127, 0, 4, 0, 2, 0, 1,	// 43
	0, 76, 0, 62, 0, 15,	// 44
	128, 0, 64, 0, 32, 0, 16, 0, 8, 0, 4, 0, 2, 0, 1,	// 45
	0, 8, 0, 14, 0, 7, 0, 1,	// 46
	0, 8, 0, 7, 192, 1, 56, 0, 14, 192, 1, 112, 0, 8, 0,	// 47
	224, 1, 248, 1, 134, 129, 129, 193, 192, 192, 48, 192, 15, 192, 3,	// 48
	16, 8, 12, 4, 255, 131, 255, 1, 128, 0, 64, 0,	// 49
	16, 8, 12, 6, 131, 131, 96, 65, 152, 96, 70, 224, 33, 96, 16,	// 50
	8, 4, 6, 6, 1, 130, 8, 65, 132, 96, 103, 224, 30, 32, 6,	// 51
	128, 1, 224, 0, 88, 0, 38, 128, 17, 224, 127, 240, 63, 0, 2,	// 52
	124, 2, 62, 3, 17, 131, 4, 65, 130, 32, 99, 16, 31, 0, 7,	// 53
	240, 3, 252, 3, 35, 131, 8, 65, 132, 96, 102, 96, 30, 0, 6,	// 54
	4, 0, 2, 0, 1, 128, 224, 65, 252, 32, 7, 240, 0, 56, 0,	// 55
	16, 3, 220, 3, 59, 131, 8, 65, 132, 96, 103, 224, 30, 32, 6,	// 56
	48, 0, 60, 3, 51, 131, 16, 65, 136, 96, 98, 224, 31, 224, 7,	// 57
	64, 8, 112, 14, 56, 7, 8, 1,	// 58
	64, 0, 112, 38, 56, 31, 136, 7,	// 59
	192, 0, 240, 0, 204, 0, 195, 192, 192, 32, 64, 0,	// 60
	64, 2, 32, 1, 144, 0, 72, 0, 36, 0, 18, 0, 9, 128, 4,	// 61
	4, 8, 6, 6, 134, 1, 102, 0, 30, 0, 6, 0,	// 62
	24, 0, 14, 0, 65, 131, 176, 65, 12, 224, 3, 224, 0, 0,	// 63

    }
};
