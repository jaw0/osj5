
// file: font/profont17.bdf
// font: ProFont17

#include <font.h>

const struct Font font_profont17_n = {
    .type       = 1,
    .name	= "profont17_n",
    .height	= 16,
    .width	= 10,
    .lineheight = 16,
    .bytescol	= 2,
    .numcol     = 10,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 3, .r0 = 5, .ncol = 2, .xadj = 0, .pos = 0 }, // 33 [4]
	{ .l0 = 1, .r0 = 4, .ncol = 5, .xadj = 0, .pos = 4 }, // 34 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = 0, .pos = 14 }, // 35 [14]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 28 }, // 36 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 44 }, // 37 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 60 }, // 38 [16]
	{ .l0 = 3, .r0 = 5, .ncol = 2, .xadj = 0, .pos = 76 }, // 39 [4]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 80 }, // 40 [12]
	{ .l0 = 1, .r0 = 3, .ncol = 6, .xadj = 0, .pos = 92 }, // 41 [12]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 104 }, // 42 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 120 }, // 43 [16]
	{ .l0 = 1, .r0 = 5, .ncol = 4, .xadj = 0, .pos = 136 }, // 44 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 5, .xadj = 0, .pos = 144 }, // 45 [10]
	{ .l0 = 2, .r0 = 5, .ncol = 3, .xadj = 0, .pos = 154 }, // 46 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 9, .xadj = 0, .pos = 160 }, // 47 [18]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 178 }, // 48 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 194 }, // 49 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 210 }, // 50 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 226 }, // 51 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 242 }, // 52 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 258 }, // 53 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 274 }, // 54 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 290 }, // 55 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 306 }, // 56 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 322 }, // 57 [16]
	{ .l0 = 2, .r0 = 5, .ncol = 3, .xadj = 0, .pos = 338 }, // 58 [6]
	{ .l0 = 1, .r0 = 5, .ncol = 4, .xadj = 0, .pos = 344 }, // 59 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = 0, .pos = 352 }, // 60 [14]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 366 }, // 61 [16]
	{ .l0 = 1, .r0 = 2, .ncol = 7, .xadj = 0, .pos = 382 }, // 62 [14]
	{ .l0 = 0, .r0 = 2, .ncol = 8, .xadj = 0, .pos = 396 }, // 63 [16]
    },
    .data       = {
	252, 27, 252, 27,	// 33
	31, 0, 31, 0, 0, 0, 31, 0, 31, 0,	// 34
	176, 1, 248, 3, 248, 3, 176, 1, 248, 3, 248, 3, 176, 1,	// 35
	48, 6, 120, 14, 204, 24, 255, 127, 255, 127, 204, 25, 152, 15, 16, 7,	// 36
	48, 28, 120, 30, 204, 3, 252, 7, 252, 15, 236, 25, 60, 15, 28, 6,	// 37
	112, 15, 248, 31, 140, 25, 204, 27, 120, 30, 48, 14, 0, 27, 0, 17,	// 38
	31, 0, 31, 0,	// 39
	240, 7, 248, 15, 12, 24, 6, 48, 3, 96, 1, 64,	// 40
	1, 64, 3, 96, 6, 48, 12, 24, 248, 15, 240, 7,	// 41
	152, 1, 152, 1, 240, 0, 252, 3, 252, 3, 240, 0, 152, 1, 152, 1,	// 42
	128, 1, 128, 1, 128, 1, 240, 15, 240, 15, 128, 1, 128, 1, 128, 1,	// 43
	0, 128, 0, 220, 0, 124, 0, 60,	// 44
	128, 1, 128, 1, 128, 1, 128, 1, 128, 1,	// 45
	0, 28, 0, 28, 0, 28,	// 46
	0, 192, 0, 240, 0, 60, 0, 15, 192, 3, 240, 0, 60, 0, 15, 0, 3, 0,	// 47
	240, 7, 248, 15, 12, 27, 140, 25, 204, 24, 108, 24, 248, 15, 240, 7,	// 48
	0, 24, 24, 24, 24, 24, 252, 31, 252, 31, 0, 24, 0, 24, 0, 24,	// 49
	48, 24, 56, 28, 12, 30, 12, 27, 140, 25, 204, 24, 120, 24, 48, 24,	// 50
	48, 6, 56, 14, 12, 24, 204, 24, 204, 24, 204, 25, 120, 15, 48, 6,	// 51
	128, 3, 192, 3, 96, 3, 48, 3, 24, 27, 252, 31, 252, 31, 0, 27,	// 52
	124, 4, 124, 12, 108, 24, 108, 24, 108, 24, 108, 24, 204, 15, 140, 7,	// 53
	240, 7, 248, 15, 108, 24, 108, 24, 108, 24, 108, 24, 204, 15, 128, 7,	// 54
	12, 0, 12, 0, 12, 0, 12, 31, 140, 31, 204, 0, 124, 0, 60, 0,	// 55
	48, 6, 120, 15, 204, 25, 204, 25, 204, 25, 204, 25, 120, 15, 48, 6,	// 56
	240, 0, 248, 25, 12, 27, 12, 27, 12, 27, 12, 27, 248, 15, 240, 7,	// 57
	224, 28, 224, 28, 224, 28,	// 58
	0, 128, 224, 220, 224, 124, 224, 60,	// 59
	128, 0, 192, 1, 96, 3, 48, 6, 24, 12, 12, 24, 4, 16,	// 60
	96, 3, 96, 3, 96, 3, 96, 3, 96, 3, 96, 3, 96, 3, 96, 3,	// 61
	4, 16, 12, 24, 24, 12, 48, 6, 96, 3, 192, 1, 128, 0,	// 62
	48, 0, 56, 0, 12, 0, 12, 27, 140, 25, 204, 0, 120, 0, 48, 0,	// 63

    }
};
