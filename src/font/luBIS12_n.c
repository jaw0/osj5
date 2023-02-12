
// file: font/luBIS12.bdf
// font: -B&H-Lucida-Bold-I-Normal-Sans-12-120-75-75-P-79-ISO10646-1

#include <font.h>

const struct Font font_luBIS12_n = {
    .type       = 1,
    .name	= "luBIS12_n",
    .height	= 12,
    .width	= 11,
    .bytescol	= 2,
    .numcol     = 11,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -7, .pos = 0 }, // 33 [6]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -4, .pos = 6 }, // 34 [8]
	{ .l0 = 0, .r0 = 2, .ncol = 9, .xadj = -3, .pos = 14 }, // 35 [14]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 28 }, // 36 [11]
	{ .l0 = 1, .r0 = 1, .ncol = 9, .xadj = 0, .pos = 39 }, // 37 [14]
	{ .l0 = 1, .r0 = 1, .ncol = 9, .xadj = -1, .pos = 53 }, // 38 [14]
	{ .l0 = 2, .r0 = 7, .ncol = 2, .xadj = -8, .pos = 67 }, // 39 [3]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 70 }, // 40 [8]
	{ .l0 = 0, .r0 = 6, .ncol = 5, .xadj = -6, .pos = 78 }, // 41 [8]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 86 }, // 42 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -2, .pos = 95 }, // 43 [12]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -8, .pos = 107 }, // 44 [5]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 112 }, // 45 [5]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -8, .pos = 117 }, // 46 [3]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 120 }, // 47 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 131 }, // 48 [11]
	{ .l0 = 2, .r0 = 5, .ncol = 4, .xadj = -3, .pos = 142 }, // 49 [6]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 148 }, // 50 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 159 }, // 51 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 170 }, // 52 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 181 }, // 53 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 192 }, // 54 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 203 }, // 55 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 214 }, // 56 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 225 }, // 57 [11]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 236 }, // 58 [5]
	{ .l0 = 0, .r0 = 7, .ncol = 4, .xadj = -7, .pos = 241 }, // 59 [6]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 247 }, // 60 [11]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -2, .pos = 258 }, // 61 [12]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -2, .pos = 270 }, // 62 [11]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 281 }, // 63 [9]
    },
    .data       = {
	0, 3, 55, 126, 224, 0,	// 33
	15, 48, 0, 0, 240, 0, 3, 0,	// 34
	128, 128, 56, 248, 227, 15, 142, 131, 63, 254, 224, 8, 8, 0,	// 35
	0, 194, 33, 254, 39, 39, 255, 35, 28, 2, 0,	// 36
	12, 226, 49, 146, 225, 5, 172, 1, 61, 76, 98, 60, 130, 1,	// 37
	192, 193, 62, 62, 34, 39, 226, 227, 25, 12, 3, 46, 96, 0,	// 38
	15, 48, 0,	// 39
	240, 195, 127, 14, 52, 0, 1, 0,	// 40
	0, 4, 96, 129, 243, 31, 126, 0,	// 41
	20, 128, 0, 56, 224, 0, 8, 64, 1,	// 42
	32, 0, 2, 32, 0, 30, 60, 0, 2, 32, 0, 2,	// 43
	0, 8, 112, 0, 3,	// 44
	32, 0, 2, 32, 0,	// 45
	0, 3, 48,	// 46
	0, 6, 120, 224, 1, 7, 60, 240, 0, 3, 0,	// 47
	224, 193, 63, 30, 34, 32, 194, 227, 31, 60, 0,	// 48
	4, 64, 62, 254, 227, 3,	// 49
	0, 67, 56, 70, 35, 54, 50, 227, 51, 28, 0,	// 50
	0, 65, 48, 38, 34, 34, 242, 227, 29, 12, 0,	// 51
	96, 0, 5, 72, 64, 60, 254, 227, 7, 64, 0,	// 52
	0, 129, 49, 22, 98, 51, 246, 97, 14, 6, 0,	// 53
	192, 129, 63, 60, 98, 34, 226, 99, 28, 4, 0,	// 54
	0, 99, 56, 198, 97, 6, 54, 224, 1, 14, 0,	// 55
	128, 193, 60, 62, 34, 35, 226, 227, 29, 12, 0,	// 56
	0, 193, 49, 62, 34, 50, 226, 225, 15, 28, 0,	// 57
	0, 131, 49, 24, 0,	// 58
	0, 8, 112, 24, 131, 1,	// 59
	64, 0, 14, 176, 1, 17, 24, 195, 32, 4, 0,	// 60
	64, 0, 5, 80, 0, 5, 80, 0, 5, 80, 0, 1,	// 61
	0, 66, 48, 140, 129, 8, 216, 0, 7, 32, 0,	// 62
	0, 35, 54, 114, 32, 1, 30, 192, 0,	// 63

    }
};
