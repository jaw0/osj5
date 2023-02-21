
// file: font/lubI19.bdf
// font: -B&H-LucidaBright-Medium-I-Normal--19-190-75-75-P-109-ISO10646-1

#include <font.h>

const struct Font font_lubI19_n = {
    .type       = 1,
    .name	= "lubI19_n",
    .height	= 19,
    .width	= 15,
    .lineheight = 19,
    .bytescol	= 4,
    .numcol     = 15,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 9, .ncol = 5, .xadj = -10, .pos = 0 }, // 33 [12]
	{ .l0 = 4, .r0 = 6, .ncol = 5, .xadj = -8, .pos = 12 }, // 34 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 12, .xadj = -3, .pos = 24 }, // 35 [29]
	{ .l0 = 3, .r0 = 3, .ncol = 9, .xadj = -3, .pos = 53 }, // 36 [22]
	{ .l0 = 2, .r0 = 0, .ncol = 13, .xadj = -1, .pos = 75 }, // 37 [31]
	{ .l0 = 2, .r0 = 0, .ncol = 13, .xadj = -1, .pos = 106 }, // 38 [31]
	{ .l0 = 3, .r0 = 10, .ncol = 2, .xadj = -11, .pos = 137 }, // 39 [5]
	{ .l0 = 2, .r0 = 6, .ncol = 7, .xadj = -9, .pos = 142 }, // 40 [17]
	{ .l0 = 0, .r0 = 9, .ncol = 6, .xadj = -9, .pos = 159 }, // 41 [15]
	{ .l0 = 3, .r0 = 5, .ncol = 7, .xadj = -6, .pos = 174 }, // 42 [17]
	{ .l0 = 1, .r0 = 3, .ncol = 11, .xadj = -3, .pos = 191 }, // 43 [27]
	{ .l0 = 1, .r0 = 11, .ncol = 3, .xadj = -10, .pos = 218 }, // 44 [8]
	{ .l0 = 2, .r0 = 8, .ncol = 5, .xadj = -9, .pos = 226 }, // 45 [12]
	{ .l0 = 1, .r0 = 11, .ncol = 3, .xadj = -10, .pos = 238 }, // 46 [8]
	{ .l0 = 0, .r0 = 3, .ncol = 12, .xadj = -6, .pos = 246 }, // 47 [29]
	{ .l0 = 2, .r0 = 3, .ncol = 10, .xadj = -3, .pos = 275 }, // 48 [24]
	{ .l0 = 2, .r0 = 6, .ncol = 7, .xadj = -3, .pos = 299 }, // 49 [17]
	{ .l0 = 1, .r0 = 3, .ncol = 11, .xadj = -3, .pos = 316 }, // 50 [27]
	{ .l0 = 2, .r0 = 3, .ncol = 10, .xadj = -3, .pos = 343 }, // 51 [24]
	{ .l0 = 1, .r0 = 4, .ncol = 10, .xadj = -3, .pos = 367 }, // 52 [24]
	{ .l0 = 2, .r0 = 3, .ncol = 10, .xadj = -3, .pos = 391 }, // 53 [24]
	{ .l0 = 2, .r0 = 3, .ncol = 10, .xadj = -3, .pos = 415 }, // 54 [24]
	{ .l0 = 3, .r0 = 1, .ncol = 11, .xadj = -3, .pos = 439 }, // 55 [27]
	{ .l0 = 3, .r0 = 3, .ncol = 9, .xadj = -3, .pos = 466 }, // 56 [22]
	{ .l0 = 2, .r0 = 3, .ncol = 10, .xadj = -3, .pos = 488 }, // 57 [24]
	{ .l0 = 2, .r0 = 9, .ncol = 4, .xadj = -10, .pos = 512 }, // 58 [10]
	{ .l0 = 1, .r0 = 9, .ncol = 5, .xadj = -10, .pos = 522 }, // 59 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 12, .xadj = -3, .pos = 534 }, // 60 [29]
	{ .l0 = 1, .r0 = 2, .ncol = 12, .xadj = -3, .pos = 563 }, // 61 [29]
	{ .l0 = 0, .r0 = 3, .ncol = 12, .xadj = -3, .pos = 592 }, // 62 [29]
	{ .l0 = 3, .r0 = 5, .ncol = 7, .xadj = -6, .pos = 621 }, // 63 [17]
    },
    .data       = {
	0, 64, 0, 64, 2, 252, 1, 252, 0, 96, 0, 0,	// 33
	30, 0, 48, 0, 0, 0, 0, 60, 0, 96, 0, 0,	// 34
	0, 66, 0, 145, 3, 136, 3, 64, 6, 0, 46, 4, 24, 29, 176, 56, 64, 116, 0, 96, 2, 192, 17, 128, 137, 0, 68, 0, 0,	// 35
	0, 112, 192, 1, 3, 31, 112, 140, 253, 32, 28, 4, 159, 17, 12, 252, 64, 192, 1, 14, 0, 0,	// 36
	0, 64, 192, 3, 3, 51, 4, 4, 17, 32, 76, 0, 63, 1, 32, 6, 0, 216, 15, 32, 67, 128, 8, 2, 66, 8, 8, 60, 32, 0, 0,	// 37
	0, 30, 0, 248, 1, 64, 24, 0, 129, 128, 7, 4, 254, 33, 8, 61, 65, 136, 7, 38, 112, 224, 201, 3, 192, 19, 0, 134, 0, 16, 0,	// 38
	14, 0, 240, 1, 0,	// 39
	0, 254, 0, 254, 31, 56, 0, 49, 0, 64, 0, 0, 2, 0, 8, 0, 0,	// 40
	0, 0, 4, 0, 16, 0, 96, 4, 192, 193, 224, 3, 248, 7, 0,	// 41
	72, 0, 64, 6, 0, 12, 0, 92, 0, 32, 13, 0, 12, 0, 32, 0, 0,	// 42
	0, 2, 0, 16, 0, 128, 0, 0, 4, 0, 32, 7, 192, 15, 224, 9, 0, 64, 0, 0, 2, 0, 16, 0, 128, 0, 0,	// 43
	0, 0, 4, 128, 31, 0, 60, 0,	// 44
	0, 1, 0, 8, 0, 64, 0, 0, 2, 0, 16, 0,	// 45
	0, 96, 0, 0, 3, 0, 24, 0,	// 46
	0, 0, 4, 0, 16, 0, 96, 0, 192, 0, 0, 1, 0, 6, 0, 12, 0, 16, 0, 96, 0, 192, 0, 0, 1, 0, 4, 0, 0,	// 47
	128, 31, 128, 255, 1, 14, 24, 24, 128, 96, 0, 4, 1, 48, 8, 192, 192, 128, 3, 252, 15, 192, 15, 0,	// 48
	0, 64, 0, 0, 2, 0, 16, 4, 248, 32, 254, 7, 255, 32, 56, 0, 1,	// 49
	0, 64, 0, 128, 3, 0, 22, 24, 144, 32, 64, 4, 1, 33, 8, 4, 65, 48, 8, 198, 64, 224, 3, 0, 15, 0, 0,	// 50
	0, 112, 0, 0, 2, 2, 16, 28, 129, 32, 8, 4, 65, 48, 8, 199, 192, 236, 3, 60, 14, 192, 0, 0,	// 51
	0, 4, 0, 48, 0, 64, 1, 128, 9, 0, 66, 4, 8, 50, 32, 240, 129, 255, 9, 254, 68, 16, 32, 0,	// 52
	0, 112, 0, 0, 2, 31, 16, 132, 128, 32, 4, 4, 97, 48, 8, 198, 64, 240, 3, 2, 6, 16, 0, 0,	// 53
	128, 31, 0, 255, 1, 62, 24, 184, 128, 64, 4, 4, 33, 32, 8, 129, 64, 248, 3, 130, 15, 112, 0, 0,	// 54
	0, 96, 0, 128, 131, 0, 7, 4, 12, 32, 48, 0, 65, 0, 8, 1, 64, 4, 0, 26, 0, 48, 0, 128, 0, 0, 0,	// 55
	0, 60, 0, 240, 1, 94, 24, 248, 129, 32, 12, 4, 193, 48, 8, 205, 192, 236, 3, 60, 8, 0,	// 56
	0, 48, 128, 15, 2, 254, 16, 24, 134, 96, 32, 4, 1, 17, 8, 200, 192, 224, 3, 252, 15, 192, 31, 0,	// 57
	0, 96, 0, 2, 3, 24, 8, 192, 0, 0,	// 58
	0, 0, 4, 0, 63, 16, 120, 192, 0, 0, 6, 0,	// 59
	0, 1, 0, 24, 0, 192, 0, 0, 9, 0, 200, 0, 32, 4, 0, 65, 0, 4, 6, 32, 32, 128, 0, 3, 4, 0, 16, 0, 0,	// 60
	0, 8, 0, 68, 0, 32, 2, 0, 17, 0, 136, 0, 64, 4, 0, 34, 0, 16, 1, 128, 8, 0, 68, 0, 32, 2, 0, 1, 0,	// 61
	0, 64, 0, 0, 1, 6, 8, 32, 32, 0, 3, 1, 16, 4, 0, 33, 0, 152, 0, 128, 4, 0, 24, 0, 192, 0, 0, 4, 0,	// 62
	12, 64, 48, 48, 130, 192, 1, 4, 3, 32, 12, 0, 51, 0, 240, 0, 0,	// 63

    }
};
