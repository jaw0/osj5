
// file: font/timB24.bdf
// font: -Adobe-Times-Bold-R-Normal--24-240-75-75-P-132-ISO10646-1

#include <font.h>

const struct Font font_timB24_n = {
    .type       = 1,
    .name	= "timB24_n",
    .height	= 23,
    .width	= 21,
    .lineheight = 24,
    .bytescol	= 4,
    .numcol     = 21,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 15, .ncol = 4, .xadj = -13, .pos = 0 }, // 33 [12]
	{ .l0 = 2, .r0 = 11, .ncol = 8, .xadj = -9, .pos = 12 }, // 34 [23]
	{ .l0 = 0, .r0 = 9, .ncol = 12, .xadj = -8, .pos = 35 }, // 35 [35]
	{ .l0 = 1, .r0 = 10, .ncol = 10, .xadj = -9, .pos = 70 }, // 36 [29]
	{ .l0 = 1, .r0 = 3, .ncol = 17, .xadj = -2, .pos = 99 }, // 37 [49]
	{ .l0 = 2, .r0 = 2, .ncol = 17, .xadj = 0, .pos = 148 }, // 38 [49]
	{ .l0 = 2, .r0 = 16, .ncol = 3, .xadj = -14, .pos = 197 }, // 39 [9]
	{ .l0 = 1, .r0 = 15, .ncol = 5, .xadj = -13, .pos = 206 }, // 40 [15]
	{ .l0 = 2, .r0 = 14, .ncol = 5, .xadj = -13, .pos = 221 }, // 41 [15]
	{ .l0 = 1, .r0 = 10, .ncol = 10, .xadj = -8, .pos = 236 }, // 42 [29]
	{ .l0 = 1, .r0 = 8, .ncol = 12, .xadj = -7, .pos = 265 }, // 43 [35]
	{ .l0 = 1, .r0 = 16, .ncol = 4, .xadj = -15, .pos = 300 }, // 44 [12]
	{ .l0 = 1, .r0 = 14, .ncol = 6, .xadj = -13, .pos = 312 }, // 45 [18]
	{ .l0 = 1, .r0 = 16, .ncol = 4, .xadj = -15, .pos = 330 }, // 46 [12]
	{ .l0 = 0, .r0 = 14, .ncol = 7, .xadj = -14, .pos = 342 }, // 47 [21]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 363 }, // 48 [32]
	{ .l0 = 2, .r0 = 10, .ncol = 9, .xadj = -9, .pos = 395 }, // 49 [26]
	{ .l0 = 1, .r0 = 10, .ncol = 10, .xadj = -9, .pos = 421 }, // 50 [29]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 450 }, // 51 [32]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 482 }, // 52 [32]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 514 }, // 53 [32]
	{ .l0 = 1, .r0 = 10, .ncol = 10, .xadj = -9, .pos = 546 }, // 54 [29]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 575 }, // 55 [32]
	{ .l0 = 1, .r0 = 9, .ncol = 11, .xadj = -9, .pos = 607 }, // 56 [32]
	{ .l0 = 0, .r0 = 10, .ncol = 11, .xadj = -9, .pos = 639 }, // 57 [32]
	{ .l0 = 2, .r0 = 15, .ncol = 4, .xadj = -13, .pos = 671 }, // 58 [12]
	{ .l0 = 2, .r0 = 15, .ncol = 4, .xadj = -13, .pos = 683 }, // 59 [12]
	{ .l0 = 1, .r0 = 9, .ncol = 11, .xadj = -7, .pos = 695 }, // 60 [32]
	{ .l0 = 1, .r0 = 9, .ncol = 11, .xadj = -7, .pos = 727 }, // 61 [32]
	{ .l0 = 1, .r0 = 9, .ncol = 11, .xadj = -7, .pos = 759 }, // 62 [32]
	{ .l0 = 1, .r0 = 11, .ncol = 9, .xadj = -9, .pos = 791 }, // 63 [26]
    },
    .data       = {
	124, 128, 1, 255, 231, 129, 255, 243, 128, 15, 48, 0,	// 33
	126, 0, 0, 255, 0, 128, 31, 0, 0, 0, 0, 0, 0, 0, 240, 3, 0, 248, 7, 0, 252, 0, 0,	// 34
	0, 24, 0, 48, 12, 0, 24, 254, 0, 252, 127, 224, 255, 1, 240, 195, 0, 128, 225, 15, 192, 255, 7, 254, 31, 0, 63, 12, 0, 24, 6, 0, 12, 0, 0,	// 35
	240, 224, 1, 252, 224, 0, 251, 192, 128, 248, 64, 240, 255, 255, 32, 124, 16, 48, 124, 12, 120, 252, 3, 120, 252, 1, 0, 124, 0,	// 36
	240, 0, 0, 252, 0, 0, 127, 0, 192, 49, 0, 96, 16, 48, 16, 4, 30, 152, 193, 3, 56, 120, 0, 4, 15, 0, 226, 241, 0, 61, 252, 128, 7, 127, 224, 192, 49, 48, 96, 16, 0, 16, 4, 0, 152, 1, 0, 56, 0,	// 37
	0, 248, 0, 0, 254, 0, 128, 255, 0, 224, 120, 128, 31, 56, 224, 15, 24, 248, 15, 12, 140, 31, 7, 194, 159, 1, 51, 127, 128, 31, 63, 128, 7, 63, 0, 136, 63, 0, 108, 30, 0, 30, 14, 0, 3, 3, 128, 128, 0,	// 38
	126, 0, 0, 255, 0, 128, 31, 0, 0,	// 39
	0, 127, 0, 240, 255, 1, 254, 255, 131, 7, 192, 99, 0, 0, 3,	// 40
	6, 0, 48, 14, 0, 14, 254, 255, 3, 252, 127, 0, 240, 7, 0,	// 41
	16, 1, 0, 220, 1, 0, 108, 0, 0, 28, 0, 224, 255, 0, 240, 127, 0, 128, 3, 0, 96, 3, 0, 184, 3, 0, 136, 0, 0,	// 42
	0, 24, 0, 0, 12, 0, 0, 6, 0, 0, 3, 0, 128, 1, 0, 254, 31, 0, 255, 15, 0, 48, 0, 0, 24, 0, 0, 12, 0, 0, 6, 0, 0, 3, 0,	// 43
	0, 128, 97, 0, 224, 29, 0, 240, 7, 0, 240, 0,	// 44
	0, 28, 0, 0, 14, 0, 0, 7, 0, 128, 3, 0, 192, 1, 0, 224, 0, 0,	// 45
	0, 128, 1, 0, 224, 1, 0, 240, 0, 0, 48, 0,	// 46
	0, 0, 3, 0, 240, 1, 0, 31, 0, 240, 1, 0, 31, 0, 240, 1, 0, 24, 0, 0, 0,	// 47
	192, 15, 0, 248, 63, 0, 255, 127, 128, 255, 63, 96, 0, 48, 16, 0, 16, 24, 0, 12, 248, 255, 3, 252, 255, 1, 248, 63, 0, 240, 3, 0,	// 48
	8, 0, 2, 4, 0, 1, 3, 192, 128, 255, 127, 224, 255, 63, 240, 255, 31, 0, 0, 12, 0, 0, 4, 0, 0, 2,	// 49
	48, 0, 3, 12, 192, 1, 3, 240, 192, 1, 124, 224, 128, 59, 240, 240, 28, 248, 31, 14, 248, 7, 7, 248, 128, 3, 0, 240, 0,	// 50
	16, 128, 1, 12, 224, 1, 3, 240, 128, 96, 112, 96, 48, 48, 48, 24, 16, 56, 30, 12, 252, 31, 3, 252, 254, 1, 28, 127, 0, 0, 31, 0,	// 51
	0, 60, 0, 0, 31, 0, 224, 12, 0, 56, 6, 0, 6, 3, 192, 129, 1, 240, 255, 15, 252, 255, 7, 254, 255, 3, 0, 24, 0, 0, 12, 0,	// 52
	0, 128, 1, 224, 225, 1, 254, 240, 192, 115, 112, 224, 56, 48, 112, 60, 16, 56, 30, 12, 28, 31, 3, 14, 255, 1, 7, 63, 128, 0, 0, 0,	// 53
	0, 62, 0, 224, 127, 0, 252, 127, 0, 255, 127, 128, 39, 48, 224, 8, 16, 48, 12, 12, 12, 254, 3, 6, 254, 1, 1, 126, 0,	// 54
	48, 0, 0, 15, 0, 128, 3, 0, 192, 1, 96, 224, 0, 62, 112, 224, 31, 56, 254, 1, 220, 15, 0, 254, 0, 0, 15, 0, 128, 1, 0, 0,	// 55
	0, 240, 0, 124, 254, 0, 127, 127, 192, 255, 96, 96, 60, 32, 16, 60, 16, 24, 62, 8, 252, 63, 6, 124, 254, 1, 28, 254, 0, 0, 30, 0,	// 56
	224, 1, 0, 252, 1, 1, 255, 129, 128, 255, 97, 96, 192, 48, 16, 64, 12, 24, 160, 7, 56, 248, 1, 252, 127, 0, 252, 31, 0, 248, 3, 0,	// 57
	128, 129, 1, 224, 225, 1, 240, 240, 0, 48, 48, 0,	// 58
	128, 129, 97, 224, 225, 29, 240, 240, 7, 48, 240, 0,	// 59
	0, 24, 0, 0, 12, 0, 0, 15, 0, 192, 12, 0, 96, 6, 0, 56, 7, 0, 12, 3, 0, 135, 3, 128, 129, 1, 224, 192, 1, 48, 192, 0,	// 60
	0, 102, 0, 0, 51, 0, 128, 25, 0, 192, 12, 0, 96, 6, 0, 48, 3, 0, 152, 1, 0, 204, 0, 0, 102, 0, 0, 51, 0, 128, 25, 0,	// 61
	192, 0, 3, 224, 192, 1, 96, 96, 0, 112, 56, 0, 48, 12, 0, 56, 7, 0, 152, 1, 0, 204, 0, 0, 60, 0, 0, 12, 0, 0, 6, 0,	// 62
	24, 0, 0, 30, 0, 128, 7, 96, 64, 192, 121, 32, 248, 60, 48, 30, 12, 248, 7, 0, 248, 1, 0, 120, 0, 0,	// 63

    }
};
