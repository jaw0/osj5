
// file: font/10x20.bdf
// font: -Misc-Fixed-Medium-R-Normal--20-200-75-75-C-100-ISO10646-1

#include <font.h>

const struct Font font_10x20_n = {
    .type       = 1,
    .name	= "10x20_n",
    .height	= 20,
    .width	= 10,
    .bytescol	= 4,
    .numcol     = 10,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 4, .r0 = 4, .ncol = 2, .xadj = 0, .pos = 0 }, // 33 [5]
	{ .l0 = 2, .r0 = 2, .ncol = 6, .xadj = 0, .pos = 5 }, // 34 [15]
	{ .l0 = 1, .r0 = 0, .ncol = 9, .xadj = 0, .pos = 20 }, // 35 [23]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 43 }, // 36 [20]
	{ .l0 = 1, .r0 = 0, .ncol = 9, .xadj = 0, .pos = 63 }, // 37 [23]
	{ .l0 = 1, .r0 = 0, .ncol = 9, .xadj = 0, .pos = 86 }, // 38 [23]
	{ .l0 = 4, .r0 = 4, .ncol = 2, .xadj = 0, .pos = 109 }, // 39 [5]
	{ .l0 = 3, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 114 }, // 40 [13]
	{ .l0 = 2, .r0 = 3, .ncol = 5, .xadj = 0, .pos = 127 }, // 41 [13]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 140 }, // 42 [20]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 160 }, // 43 [20]
	{ .l0 = 3, .r0 = 3, .ncol = 4, .xadj = 0, .pos = 180 }, // 44 [10]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 190 }, // 45 [20]
	{ .l0 = 4, .r0 = 3, .ncol = 3, .xadj = 0, .pos = 210 }, // 46 [8]
	{ .l0 = 2, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 218 }, // 47 [18]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 236 }, // 48 [20]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 256 }, // 49 [20]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 276 }, // 50 [20]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 296 }, // 51 [20]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 316 }, // 52 [20]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 336 }, // 53 [20]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 356 }, // 54 [20]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 376 }, // 55 [20]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 396 }, // 56 [20]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 416 }, // 57 [20]
	{ .l0 = 4, .r0 = 3, .ncol = 3, .xadj = 0, .pos = 436 }, // 58 [8]
	{ .l0 = 3, .r0 = 3, .ncol = 4, .xadj = 0, .pos = 444 }, // 59 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = 0, .pos = 454 }, // 60 [18]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 472 }, // 61 [20]
	{ .l0 = 2, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 492 }, // 62 [18]
	{ .l0 = 1, .r0 = 1, .ncol = 8, .xadj = 0, .pos = 510 }, // 63 [20]
    },
    .data       = {
	248, 223, 128, 255, 13,	// 33
	56, 0, 128, 7, 0, 0, 0, 0, 0, 0, 120, 0, 128, 3, 0,	// 34
	0, 8, 0, 136, 7, 128, 127, 0, 255, 0, 240, 120, 0, 248, 7, 240, 15, 0, 143, 0, 128, 0, 0,	// 35
	224, 33, 0, 63, 6, 16, 66, 128, 255, 15, 248, 255, 0, 33, 4, 48, 126, 0, 194, 3,	// 36
	96, 0, 0, 15, 12, 144, 240, 0, 207, 3, 96, 111, 0, 60, 15, 240, 144, 0, 3, 15, 0, 96, 0,	// 37
	0, 124, 0, 239, 15, 248, 195, 128, 120, 8, 248, 204, 0, 135, 7, 0, 112, 0, 128, 13, 0, 136, 0,	// 38
	248, 0, 128, 7, 0,	// 39
	128, 15, 0, 254, 3, 112, 112, 128, 1, 12, 8, 128, 0,	// 40
	8, 128, 128, 1, 12, 112, 112, 0, 254, 3, 128, 15, 0,	// 41
	0, 2, 0, 172, 1, 192, 31, 0, 112, 0, 0, 7, 0, 252, 1, 192, 26, 0, 32, 0,	// 42
	0, 2, 0, 32, 0, 0, 2, 0, 252, 1, 192, 31, 0, 32, 0, 0, 2, 0, 32, 0,	// 43
	0, 0, 1, 0, 28, 0, 192, 1, 0, 12,	// 44
	0, 2, 0, 32, 0, 0, 2, 0, 32, 0, 0, 2, 0, 32, 0, 0, 2, 0, 32, 0,	// 45
	0, 224, 0, 0, 14, 0, 224, 0,	// 46
	0, 192, 0, 0, 15, 0, 60, 0, 240, 0, 192, 3, 0, 15, 0, 48, 0, 0,	// 47
	128, 15, 0, 254, 3, 112, 112, 128, 1, 12, 24, 192, 0, 7, 7, 224, 63, 0, 248, 0,	// 48
	64, 128, 0, 6, 8, 48, 128, 128, 255, 15, 248, 255, 0, 0, 8, 0, 128, 0, 0, 8,	// 49
	96, 224, 0, 7, 15, 24, 152, 128, 192, 8, 8, 132, 128, 97, 8, 240, 131, 0, 30, 8,	// 50
	96, 48, 0, 7, 7, 24, 192, 128, 32, 8, 8, 130, 128, 113, 12, 240, 125, 0, 142, 3,	// 51
	0, 14, 0, 240, 0, 128, 9, 0, 140, 0, 96, 8, 0, 255, 15, 248, 255, 0, 128, 0,	// 52
	248, 35, 128, 63, 6, 8, 194, 128, 16, 8, 8, 129, 128, 48, 12, 8, 126, 128, 192, 3,	// 53
	224, 63, 0, 255, 7, 24, 194, 128, 16, 8, 8, 129, 128, 49, 12, 48, 126, 0, 192, 3,	// 54
	8, 0, 128, 0, 12, 8, 240, 128, 192, 3, 8, 15, 128, 60, 0, 248, 0, 128, 3, 0,	// 55
	224, 56, 0, 223, 7, 24, 199, 128, 32, 8, 8, 130, 128, 113, 12, 240, 125, 0, 142, 3,	// 56
	224, 1, 0, 63, 6, 24, 198, 128, 64, 8, 8, 132, 128, 33, 12, 240, 127, 0, 254, 3,	// 57
	0, 195, 0, 48, 12, 0, 195, 0,	// 58
	0, 0, 1, 48, 28, 0, 195, 1, 48, 12,	// 59
	0, 2, 0, 112, 0, 128, 13, 0, 140, 1, 96, 48, 0, 3, 6, 24, 192, 0,	// 60
	128, 16, 0, 8, 1, 128, 16, 0, 8, 1, 128, 16, 0, 8, 1, 128, 16, 0, 8, 1,	// 61
	24, 192, 0, 3, 6, 96, 48, 0, 140, 1, 128, 13, 0, 112, 0, 0, 2, 0,	// 62
	224, 0, 0, 15, 0, 24, 0, 128, 192, 13, 8, 222, 128, 49, 0, 240, 1, 0, 14, 0,	// 63

    }
};
