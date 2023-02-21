
// file: font/timI14.bdf
// font: -Adobe-Times-Medium-I-Normal--14-140-75-75-P-73-ISO10646-1

#include <font.h>

const struct Font font_timI14_n = {
    .type       = 1,
    .name	= "timI14_n",
    .height	= 14,
    .width	= 12,
    .lineheight = 14,
    .bytescol	= 2,
    .numcol     = 12,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 6, .ncol = 4, .xadj = -7, .pos = 0 }, // 33 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 7, .xadj = -6, .pos = 7 }, // 34 [13]
	{ .l0 = 1, .r0 = 4, .ncol = 7, .xadj = -5, .pos = 20 }, // 35 [13]
	{ .l0 = 1, .r0 = 4, .ncol = 7, .xadj = -5, .pos = 33 }, // 36 [13]
	{ .l0 = 1, .r0 = 0, .ncol = 11, .xadj = 0, .pos = 46 }, // 37 [20]
	{ .l0 = 1, .r0 = 2, .ncol = 9, .xadj = -1, .pos = 66 }, // 38 [16]
	{ .l0 = 1, .r0 = 7, .ncol = 4, .xadj = -9, .pos = 82 }, // 39 [7]
	{ .l0 = 1, .r0 = 7, .ncol = 4, .xadj = -7, .pos = 89 }, // 40 [7]
	{ .l0 = 1, .r0 = 7, .ncol = 4, .xadj = -7, .pos = 96 }, // 41 [7]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 103 }, // 42 [9]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 112 }, // 43 [13]
	{ .l0 = 1, .r0 = 9, .ncol = 2, .xadj = -8, .pos = 125 }, // 44 [4]
	{ .l0 = 2, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 129 }, // 45 [6]
	{ .l0 = 1, .r0 = 10, .ncol = 1, .xadj = -9, .pos = 135 }, // 46 [2]
	{ .l0 = 0, .r0 = 7, .ncol = 5, .xadj = -8, .pos = 137 }, // 47 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 146 }, // 48 [11]
	{ .l0 = 2, .r0 = 6, .ncol = 4, .xadj = -5, .pos = 157 }, // 49 [7]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 164 }, // 50 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 175 }, // 51 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 186 }, // 52 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 197 }, // 53 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 208 }, // 54 [11]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 219 }, // 55 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 230 }, // 56 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 241 }, // 57 [11]
	{ .l0 = 2, .r0 = 8, .ncol = 2, .xadj = -8, .pos = 252 }, // 58 [4]
	{ .l0 = 1, .r0 = 8, .ncol = 3, .xadj = -8, .pos = 256 }, // 59 [6]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 262 }, // 60 [13]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 275 }, // 61 [13]
	{ .l0 = 3, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 288 }, // 62 [13]
	{ .l0 = 3, .r0 = 5, .ncol = 4, .xadj = -5, .pos = 301 }, // 63 [7]
    },
    .data       = {
	0, 4, 96, 0, 7, 56, 0,	// 33
	16, 0, 3, 96, 0, 72, 0, 12, 128, 1, 32, 0, 0,	// 34
	128, 0, 228, 1, 15, 120, 30, 240, 128, 39, 0, 1, 0,	// 35
	0, 3, 0, 193, 241, 136, 19, 62, 198, 112, 192, 0, 0,	// 36
	24, 0, 9, 32, 66, 72, 12, 142, 0, 25, 64, 49, 48, 18, 70, 4, 144, 0, 24, 0,	// 37
	128, 3, 16, 1, 66, 240, 16, 242, 130, 196, 192, 104, 128, 17, 32, 2,	// 38
	16, 0, 3, 96, 0, 8, 0,	// 39
	128, 31, 28, 200, 0, 8, 0,	// 40
	0, 32, 0, 38, 112, 240, 3,	// 41
	20, 0, 2, 224, 3, 32, 0, 20, 0,	// 42
	128, 0, 32, 0, 8, 192, 31, 128, 0, 32, 0, 8, 0,	// 43
	0, 10, 128, 1,	// 44
	128, 0, 32, 0, 8, 0,	// 45
	0, 6,	// 46
	0, 6, 96, 0, 6, 96, 0, 6, 0,	// 47
	224, 3, 6, 65, 64, 8, 8, 130, 1, 31, 0,	// 48
	0, 4, 224, 33, 71, 56, 0,	// 49
	0, 6, 65, 33, 72, 8, 17, 34, 6, 7, 0,	// 50
	0, 2, 0, 65, 66, 136, 8, 210, 1, 3, 0,	// 51
	192, 0, 40, 0, 105, 32, 7, 180, 128, 35, 0,	// 52
	0, 6, 7, 33, 65, 200, 8, 226, 129, 0, 0,	// 53
	224, 3, 142, 65, 66, 144, 8, 194, 129, 0, 0,	// 54
	4, 134, 64, 32, 12, 136, 0, 26, 128, 1, 0,	// 55
	128, 3, 18, 65, 67, 136, 9, 146, 1, 3, 0,	// 56
	0, 4, 14, 65, 36, 8, 9, 166, 1, 31, 0,	// 57
	0, 6, 12, 0,	// 58
	0, 10, 128, 1, 3, 0,	// 59
	128, 0, 32, 0, 20, 128, 8, 32, 2, 4, 1, 65, 0,	// 60
	64, 1, 80, 0, 20, 0, 5, 64, 1, 80, 0, 20, 0,	// 61
	16, 4, 4, 1, 34, 128, 8, 64, 1, 32, 0, 8, 0,	// 62
	140, 133, 16, 32, 2, 112, 0,	// 63

    }
};
