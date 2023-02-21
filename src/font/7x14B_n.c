
// file: font/7x14B.bdf
// font: -Misc-Fixed-Bold-R-Normal--14-130-75-75-C-70-ISO10646-1

#include <font.h>

const struct Font font_7x14B_n = {
    .type       = 1,
    .name	= "7x14B_n",
    .height	= 14,
    .width	= 7,
    .lineheight = 14,
    .bytescol	= 2,
    .numcol     = 7,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 0 }, // 33 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 4 }, // 34 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 13 }, // 35 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 24 }, // 36 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 35 }, // 37 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 46 }, // 38 [11]
	{ .l0 = 2, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 57 }, // 39 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 61 }, // 40 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 70 }, // 41 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 79 }, // 42 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 90 }, // 43 [11]
	{ .l0 = 2, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 101 }, // 44 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 107 }, // 45 [11]
	{ .l0 = 2, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 118 }, // 46 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 122 }, // 47 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 133 }, // 48 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 144 }, // 49 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 155 }, // 50 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 166 }, // 51 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 177 }, // 52 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 188 }, // 53 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 199 }, // 54 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 210 }, // 55 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 221 }, // 56 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 232 }, // 57 [11]
	{ .l0 = 2, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 243 }, // 58 [4]
	{ .l0 = 2, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 247 }, // 59 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 253 }, // 60 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 264 }, // 61 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 275 }, // 62 [11]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 286 }, // 63 [11]
    },
    .data       = {
	252, 13, 127, 3,	// 33
	30, 128, 7, 0, 0, 120, 0, 30, 0,	// 34
	32, 1, 255, 195, 255, 240, 63, 252, 15, 72, 0,	// 35
	48, 6, 18, 194, 255, 241, 127, 136, 8, 204, 1,	// 36
	24, 12, 143, 67, 122, 224, 37, 28, 15, 131, 1,	// 37
	0, 7, 238, 195, 143, 16, 29, 252, 15, 110, 2,	// 38
	30, 128, 7, 0,	// 39
	224, 3, 254, 195, 193, 25, 192, 2, 32,	// 40
	2, 160, 1, 204, 193, 225, 63, 224, 3,	// 41
	140, 1, 20, 192, 31, 240, 7, 80, 0, 99, 0,	// 42
	128, 0, 32, 0, 127, 192, 31, 128, 0, 32, 0,	// 43
	0, 36, 0, 15, 192, 1,	// 44
	128, 0, 32, 0, 8, 0, 2, 128, 0, 32, 0,	// 45
	0, 12, 0, 3,	// 46
	0, 56, 128, 15, 124, 192, 7, 62, 128, 3, 0,	// 47
	248, 7, 255, 67, 128, 16, 32, 252, 15, 254, 1,	// 48
	16, 8, 6, 194, 255, 240, 63, 0, 8, 0, 2,	// 49
	24, 12, 135, 67, 176, 16, 39, 252, 8, 14, 2,	// 50
	24, 6, 135, 67, 132, 16, 33, 252, 15, 238, 1,	// 51
	128, 3, 240, 0, 38, 224, 63, 252, 15, 128, 0,	// 52
	124, 6, 159, 67, 130, 144, 32, 228, 15, 241, 1,	// 53
	240, 7, 254, 195, 132, 16, 33, 220, 15, 230, 1,	// 54
	28, 0, 7, 64, 252, 208, 63, 60, 0, 3, 0,	// 55
	56, 7, 255, 67, 140, 16, 35, 252, 15, 206, 1,	// 56
	120, 6, 191, 67, 136, 16, 50, 252, 7, 254, 0,	// 57
	48, 6, 140, 1,	// 58
	0, 18, 140, 7, 227, 0,	// 59
	128, 0, 112, 0, 54, 192, 24, 24, 12, 2, 2,	// 60
	64, 2, 144, 0, 36, 0, 9, 64, 2, 144, 0,	// 61
	8, 8, 6, 3, 99, 128, 13, 192, 1, 32, 0,	// 62
	24, 0, 7, 64, 220, 144, 55, 60, 0, 6, 0,	// 63

    }
};
