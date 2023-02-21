
// file: font/lubBI14.bdf
// font: -B&H-LucidaBright-DemiBold-I-Normal--14-140-75-75-P-84-ISO10646-1

#include <font.h>

const struct Font font_lubBI14_n = {
    .type       = 1,
    .name	= "lubBI14_n",
    .height	= 14,
    .width	= 12,
    .lineheight = 14,
    .bytescol	= 2,
    .numcol     = 12,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 7, .ncol = 4, .xadj = -8, .pos = 0 }, // 33 [7]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 7 }, // 34 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 9, .xadj = -3, .pos = 16 }, // 35 [16]
	{ .l0 = 2, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 32 }, // 36 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 10, .xadj = -1, .pos = 46 }, // 37 [18]
	{ .l0 = 1, .r0 = 0, .ncol = 11, .xadj = -1, .pos = 64 }, // 38 [20]
	{ .l0 = 2, .r0 = 8, .ncol = 2, .xadj = -9, .pos = 84 }, // 39 [4]
	{ .l0 = 1, .r0 = 6, .ncol = 5, .xadj = -7, .pos = 88 }, // 40 [9]
	{ .l0 = 0, .r0 = 7, .ncol = 5, .xadj = -7, .pos = 97 }, // 41 [9]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 106 }, // 42 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 115 }, // 43 [14]
	{ .l0 = 0, .r0 = 9, .ncol = 3, .xadj = -8, .pos = 129 }, // 44 [6]
	{ .l0 = 1, .r0 = 8, .ncol = 3, .xadj = -8, .pos = 135 }, // 45 [6]
	{ .l0 = 1, .r0 = 8, .ncol = 3, .xadj = -8, .pos = 141 }, // 46 [6]
	{ .l0 = 0, .r0 = 2, .ncol = 10, .xadj = -5, .pos = 147 }, // 47 [18]
	{ .l0 = 1, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 165 }, // 48 [14]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 179 }, // 49 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 190 }, // 50 [14]
	{ .l0 = 1, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 204 }, // 51 [14]
	{ .l0 = 1, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 218 }, // 52 [14]
	{ .l0 = 2, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 232 }, // 53 [14]
	{ .l0 = 2, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 246 }, // 54 [14]
	{ .l0 = 2, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 260 }, // 55 [14]
	{ .l0 = 1, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 274 }, // 56 [14]
	{ .l0 = 1, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 288 }, // 57 [14]
	{ .l0 = 1, .r0 = 7, .ncol = 4, .xadj = -8, .pos = 302 }, // 58 [7]
	{ .l0 = 0, .r0 = 8, .ncol = 4, .xadj = -8, .pos = 309 }, // 59 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 9, .xadj = -3, .pos = 316 }, // 60 [16]
	{ .l0 = 1, .r0 = 2, .ncol = 9, .xadj = -3, .pos = 332 }, // 61 [16]
	{ .l0 = 0, .r0 = 3, .ncol = 9, .xadj = -3, .pos = 348 }, // 62 [16]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 364 }, // 63 [11]
    },
    .data       = {
	0, 6, 188, 225, 7, 24, 0,	// 33
	30, 128, 3, 0, 0, 120, 0, 14, 0,	// 34
	128, 4, 228, 0, 13, 192, 18, 156, 131, 52, 0, 11, 112, 2, 18, 0,	// 35
	0, 7, 0, 193, 193, 217, 30, 126, 198, 240, 32, 24, 56, 0,	// 36
	24, 132, 143, 33, 50, 200, 6, 222, 0, 200, 0, 125, 32, 17, 68, 134, 240, 0,	// 37
	192, 3, 240, 1, 98, 112, 16, 126, 132, 124, 33, 121, 184, 28, 224, 4, 24, 1, 2, 0,	// 38
	14, 128, 7, 0,	// 39
	192, 15, 252, 135, 3, 18, 0, 2, 0,	// 40
	0, 32, 0, 4, 192, 248, 31, 248, 1,	// 41
	60, 0, 6, 96, 1, 232, 0, 4, 0,	// 42
	128, 0, 32, 0, 8, 0, 30, 248, 0, 32, 0, 8, 0, 2,	// 43
	0, 40, 128, 15, 224, 0,	// 44
	64, 0, 16, 0, 4, 0,	// 45
	0, 6, 128, 1, 96, 0,	// 46
	0, 32, 0, 12, 192, 0, 24, 128, 1, 48, 0, 3, 96, 0, 6, 128, 0, 0,	// 47
	224, 3, 254, 193, 65, 24, 16, 2, 134, 192, 224, 31, 240, 3,	// 48
	0, 4, 0, 33, 112, 232, 31, 254, 132, 1, 1,	// 49
	0, 6, 192, 193, 104, 8, 25, 98, 134, 137, 225, 35, 112, 0,	// 50
	0, 7, 0, 225, 66, 136, 16, 34, 134, 244, 224, 61, 48, 0,	// 51
	128, 0, 48, 0, 10, 64, 18, 136, 7, 253, 225, 79, 24, 2,	// 52
	0, 7, 4, 225, 65, 72, 16, 50, 134, 248, 32, 28, 8, 0,	// 53
	224, 1, 254, 192, 71, 144, 16, 34, 132, 216, 32, 62, 56, 2,	// 54
	0, 134, 193, 97, 24, 24, 3, 38, 128, 5, 224, 0, 24, 0,	// 55
	128, 3, 240, 193, 101, 248, 16, 98, 132, 152, 225, 61, 48, 6,	// 56
	0, 7, 14, 193, 71, 24, 17, 66, 134, 232, 224, 31, 240, 3,	// 57
	0, 6, 136, 1, 35, 192, 0,	// 58
	0, 40, 128, 15, 227, 192, 0,	// 59
	64, 0, 48, 0, 12, 128, 4, 32, 1, 136, 0, 97, 64, 16, 8, 0,	// 60
	32, 1, 72, 0, 18, 128, 4, 32, 1, 72, 0, 18, 128, 4, 32, 1,	// 61
	0, 4, 130, 128, 33, 64, 4, 32, 1, 72, 0, 12, 0, 3, 128, 0,	// 62
	12, 134, 161, 33, 12, 136, 0, 30, 0, 3, 0,	// 63

    }
};
