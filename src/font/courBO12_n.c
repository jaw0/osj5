
// file: font/courBO12.bdf
// font: -Adobe-Courier-Bold-O-Normal--12-120-75-75-M-70-ISO10646-1

#include <font.h>

const struct Font font_courBO12_n = {
    .type       = 1,
    .name	= "courBO12_n",
    .height	= 12,
    .width	= 8,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = -1, .pos = 0 }, // 33 [6]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 6 }, // 34 [8]
	{ .l0 = 1, .r0 = 0, .ncol = 7, .xadj = -1, .pos = 14 }, // 35 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 25 }, // 36 [11]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 36 }, // 37 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 45 }, // 38 [11]
	{ .l0 = 3, .r0 = 3, .ncol = 2, .xadj = -1, .pos = 56 }, // 39 [3]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 59 }, // 40 [9]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 68 }, // 41 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 77 }, // 42 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -1, .pos = 85 }, // 43 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 3, .xadj = -1, .pos = 93 }, // 44 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -1, .pos = 98 }, // 45 [8]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -1, .pos = 106 }, // 46 [3]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -1, .pos = 109 }, // 47 [8]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 117 }, // 48 [9]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 126 }, // 49 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 135 }, // 50 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 146 }, // 51 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = -1, .pos = 157 }, // 52 [11]
	{ .l0 = 1, .r0 = 0, .ncol = 7, .xadj = -1, .pos = 168 }, // 53 [11]
	{ .l0 = 1, .r0 = 0, .ncol = 7, .xadj = -1, .pos = 179 }, // 54 [11]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 190 }, // 55 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 199 }, // 56 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 208 }, // 57 [9]
	{ .l0 = 2, .r0 = 3, .ncol = 3, .xadj = -1, .pos = 217 }, // 58 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 4, .xadj = -1, .pos = 222 }, // 59 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 228 }, // 60 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -1, .pos = 237 }, // 61 [9]
	{ .l0 = 0, .r0 = 2, .ncol = 6, .xadj = -1, .pos = 246 }, // 62 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 5, .xadj = -1, .pos = 255 }, // 63 [8]
    },
    .data       = {
	0, 3, 54, 62, 96, 0,	// 33
	28, 192, 0, 0, 192, 1, 12, 0,	// 34
	64, 128, 60, 120, 224, 60, 120, 224, 4, 8, 0,	// 35
	0, 3, 48, 24, 206, 35, 228, 115, 28, 12, 0,	// 36
	152, 64, 5, 76, 0, 50, 144, 2, 25,	// 37
	128, 1, 60, 120, 194, 46, 204, 129, 56, 64, 2,	// 38
	28, 192, 1,	// 39
	128, 3, 126, 120, 200, 1, 4, 32, 0,	// 40
	0, 8, 64, 0, 38, 56, 252, 129, 7,	// 41
	40, 128, 3, 28, 128, 2, 8, 0,	// 42
	64, 0, 28, 240, 1, 7, 64, 0,	// 43
	0, 4, 112, 0, 3,	// 44
	64, 0, 4, 64, 0, 4, 64, 0,	// 45
	0, 3, 48,	// 46
	0, 6, 24, 96, 128, 1, 6, 0,	// 47
	240, 193, 51, 6, 34, 48, 230, 193, 7,	// 48
	0, 2, 32, 132, 67, 63, 126, 226, 32,	// 49
	0, 2, 48, 132, 99, 52, 98, 227, 19, 28, 0,	// 50
	0, 1, 48, 4, 98, 34, 226, 227, 29, 28, 0,	// 51
	192, 0, 14, 176, 130, 56, 228, 227, 47, 158, 0,	// 52
	0, 129, 51, 62, 34, 50, 230, 97, 12, 2, 0,	// 53
	224, 129, 63, 44, 66, 34, 230, 35, 28, 2, 0,	// 54
	6, 99, 56, 226, 32, 7, 30, 224, 0,	// 55
	192, 193, 55, 54, 34, 54, 246, 193, 1,	// 56
	24, 194, 35, 38, 35, 26, 254, 192, 7,	// 57
	0, 3, 51, 48, 0,	// 58
	0, 4, 112, 48, 3, 3,	// 59
	64, 0, 12, 224, 1, 50, 48, 2, 1,	// 60
	128, 0, 10, 160, 0, 10, 160, 0, 2,	// 61
	0, 2, 48, 16, 1, 27, 224, 0, 4,	// 62
	24, 195, 52, 100, 192, 3, 24, 0,	// 63

    }
};
