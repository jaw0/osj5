
// file: font/luBS12.bdf
// font: -B&H-Lucida-Bold-R-Normal-Sans-12-120-75-75-P-79-ISO10646-1

#include <font.h>

const struct Font font_luBS12_n = {
    .type       = 1,
    .name	= "luBS12_n",
    .height	= 12,
    .width	= 11,
    .bytescol	= 2,
    .numcol     = 11,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -7, .pos = 0 }, // 33 [3]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 3 }, // 34 [8]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 11 }, // 35 [11]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 22 }, // 36 [9]
	{ .l0 = 0, .r0 = 0, .ncol = 11, .xadj = 0, .pos = 31 }, // 37 [17]
	{ .l0 = 2, .r0 = 1, .ncol = 8, .xadj = -1, .pos = 48 }, // 38 [12]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -8, .pos = 60 }, // 39 [3]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -6, .pos = 63 }, // 40 [6]
	{ .l0 = 0, .r0 = 7, .ncol = 4, .xadj = -6, .pos = 69 }, // 41 [6]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 75 }, // 42 [8]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 83 }, // 43 [11]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -8, .pos = 94 }, // 44 [3]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 97 }, // 45 [5]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -8, .pos = 102 }, // 46 [3]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 105 }, // 47 [11]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 116 }, // 48 [9]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -3, .pos = 125 }, // 49 [6]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 131 }, // 50 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 140 }, // 51 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 149 }, // 52 [11]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 160 }, // 53 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 169 }, // 54 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 178 }, // 55 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 187 }, // 56 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 196 }, // 57 [9]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -8, .pos = 205 }, // 58 [3]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -8, .pos = 208 }, // 59 [3]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 211 }, // 60 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 220 }, // 61 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 229 }, // 62 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -4, .pos = 238 }, // 63 [8]
    },
    .data       = {
	62, 227, 55,	// 33
	15, 48, 0, 0, 240, 0, 3, 0,	// 34
	72, 224, 63, 254, 131, 4, 254, 227, 63, 72, 0,	// 35
	28, 225, 35, 242, 247, 39, 226, 67, 28,	// 36
	12, 224, 1, 18, 227, 25, 204, 0, 7, 152, 193, 60, 70, 2, 60, 128, 1,	// 37
	140, 225, 61, 50, 34, 38, 222, 194, 24, 96, 3, 34,	// 38
	15, 48, 0,	// 39
	248, 224, 63, 7, 23, 64,	// 40
	1, 116, 112, 254, 131, 15,	// 41
	20, 128, 0, 62, 128, 0, 20, 0,	// 42
	32, 0, 2, 32, 192, 31, 32, 0, 2, 32, 0,	// 43
	0, 11, 112,	// 44
	32, 0, 2, 32, 0,	// 45
	0, 3, 48,	// 46
	0, 6, 120, 224, 1, 7, 60, 240, 0, 3, 0,	// 47
	252, 225, 63, 2, 34, 32, 254, 195, 31,	// 48
	4, 64, 0, 254, 227, 63,	// 49
	4, 99, 56, 194, 35, 54, 62, 195, 49,	// 50
	4, 97, 48, 34, 34, 34, 254, 195, 29,	// 51
	224, 0, 13, 200, 64, 12, 254, 227, 63, 192, 0,	// 52
	0, 225, 51, 38, 98, 34, 230, 99, 28,	// 53
	252, 225, 63, 34, 34, 34, 230, 67, 28,	// 54
	6, 96, 48, 198, 99, 15, 62, 224, 0,	// 55
	220, 225, 63, 50, 34, 38, 254, 195, 29,	// 56
	28, 225, 51, 34, 34, 34, 254, 195, 31,	// 57
	24, 131, 49,	// 58
	24, 139, 113,	// 59
	32, 0, 7, 216, 128, 8, 140, 65, 16,	// 60
	80, 0, 5, 80, 0, 5, 80, 0, 5,	// 61
	4, 193, 24, 136, 128, 13, 112, 0, 2,	// 62
	4, 32, 54, 114, 227, 1, 12, 0,	// 63

    }
};
