
// file: font/lubI14.bdf
// font: -B&H-LucidaBright-Medium-I-Normal--14-140-75-75-P-80-ISO10646-1

#include <font.h>

const struct Font font_lubI14_n = {
    .type       = 1,
    .name	= "lubI14_n",
    .height	= 14,
    .width	= 11,
    .lineheight = 14,
    .bytescol	= 2,
    .numcol     = 11,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 0 }, // 33 [6]
	{ .l0 = 3, .r0 = 4, .ncol = 4, .xadj = -6, .pos = 6 }, // 34 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 9, .xadj = -2, .pos = 13 }, // 35 [16]
	{ .l0 = 2, .r0 = 3, .ncol = 6, .xadj = -2, .pos = 29 }, // 36 [11]
	{ .l0 = 2, .r0 = 0, .ncol = 9, .xadj = 0, .pos = 40 }, // 37 [16]
	{ .l0 = 1, .r0 = 1, .ncol = 9, .xadj = -1, .pos = 56 }, // 38 [16]
	{ .l0 = 2, .r0 = 7, .ncol = 2, .xadj = -8, .pos = 72 }, // 39 [4]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -7, .pos = 76 }, // 40 [9]
	{ .l0 = 0, .r0 = 6, .ncol = 5, .xadj = -7, .pos = 85 }, // 41 [9]
	{ .l0 = 2, .r0 = 3, .ncol = 6, .xadj = -5, .pos = 94 }, // 42 [11]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -2, .pos = 105 }, // 43 [14]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -7, .pos = 119 }, // 44 [4]
	{ .l0 = 2, .r0 = 6, .ncol = 3, .xadj = -7, .pos = 123 }, // 45 [6]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -7, .pos = 129 }, // 46 [4]
	{ .l0 = 0, .r0 = 2, .ncol = 9, .xadj = -5, .pos = 133 }, // 47 [16]
	{ .l0 = 2, .r0 = 1, .ncol = 8, .xadj = -2, .pos = 149 }, // 48 [14]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -2, .pos = 163 }, // 49 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -2, .pos = 172 }, // 50 [14]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 186 }, // 51 [13]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 199 }, // 52 [13]
	{ .l0 = 2, .r0 = 1, .ncol = 8, .xadj = -2, .pos = 212 }, // 53 [14]
	{ .l0 = 2, .r0 = 1, .ncol = 8, .xadj = -2, .pos = 226 }, // 54 [14]
	{ .l0 = 2, .r0 = 1, .ncol = 8, .xadj = -2, .pos = 240 }, // 55 [14]
	{ .l0 = 2, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 254 }, // 56 [13]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -2, .pos = 267 }, // 57 [14]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 281 }, // 58 [6]
	{ .l0 = 0, .r0 = 7, .ncol = 4, .xadj = -7, .pos = 287 }, // 59 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 9, .xadj = -2, .pos = 294 }, // 60 [16]
	{ .l0 = 1, .r0 = 1, .ncol = 9, .xadj = -2, .pos = 310 }, // 61 [16]
	{ .l0 = 0, .r0 = 2, .ncol = 9, .xadj = -2, .pos = 326 }, // 62 [16]
	{ .l0 = 2, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 342 }, // 63 [11]
    },
    .data       = {
	0, 4, 63, 225, 0, 0,	// 33
	14, 0, 0, 224, 0, 8, 0,	// 34
	128, 4, 228, 0, 13, 192, 18, 156, 131, 52, 0, 11, 112, 2, 18, 0,	// 35
	0, 7, 7, 103, 122, 248, 17, 195, 131, 99, 0,	// 36
	0, 4, 143, 32, 18, 200, 2, 76, 0, 236, 129, 68, 16, 25, 130, 1,	// 37
	128, 3, 144, 129, 66, 240, 17, 210, 133, 196, 193, 84, 0, 19, 64, 0,	// 38
	14, 128, 0, 0,	// 39
	192, 31, 28, 200, 0, 8, 0, 2, 0,	// 40
	0, 32, 0, 4, 192, 248, 15, 96, 0,	// 41
	36, 0, 6, 96, 1, 160, 0, 8, 0, 1, 0,	// 42
	128, 0, 32, 0, 8, 0, 30, 248, 0, 32, 0, 8, 0, 2,	// 43
	0, 52, 128, 3,	// 44
	64, 0, 16, 0, 4, 0,	// 45
	0, 6, 128, 1,	// 46
	0, 32, 0, 6, 64, 0, 12, 128, 0, 24, 128, 1, 16, 0, 2, 0,	// 47
	224, 3, 142, 193, 64, 8, 16, 2, 134, 224, 192, 15, 64, 0,	// 48
	0, 4, 0, 33, 120, 248, 19, 6, 4,	// 49
	0, 4, 192, 193, 72, 8, 18, 66, 132, 8, 97, 67, 112, 0,	// 50
	0, 7, 0, 225, 66, 136, 16, 34, 134, 244, 192, 1, 0,	// 51
	192, 0, 40, 0, 9, 32, 18, 132, 7, 63, 97, 8, 0,	// 52
	0, 7, 4, 225, 65, 72, 16, 50, 130, 248, 32, 0, 8, 0,	// 53
	224, 3, 158, 193, 66, 152, 16, 34, 134, 248, 224, 28, 16, 0,	// 54
	0, 132, 192, 33, 24, 8, 1, 50, 128, 4, 224, 0, 8, 0,	// 55
	128, 3, 150, 193, 67, 136, 16, 98, 134, 247, 192, 0, 0,	// 56
	0, 7, 14, 65, 68, 8, 17, 66, 130, 120, 192, 15, 64, 0,	// 57
	0, 6, 140, 1, 3, 0,	// 58
	0, 36, 0, 15, 67, 192, 0,	// 59
	64, 0, 48, 0, 12, 128, 4, 32, 1, 136, 0, 65, 64, 16, 8, 0,	// 60
	32, 1, 72, 0, 18, 128, 4, 32, 1, 72, 0, 18, 128, 4, 32, 1,	// 61
	0, 4, 130, 128, 32, 64, 4, 16, 1, 72, 0, 12, 0, 3, 128, 0,	// 62
	12, 132, 112, 33, 6, 200, 0, 30, 0, 2, 0,	// 63

    }
};
