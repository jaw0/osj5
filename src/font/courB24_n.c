
// file: font/courB24.bdf
// font: -Adobe-Courier-Bold-R-Normal--24-240-75-75-M-150-ISO10646-1

#include <font.h>

const struct Font font_courB24_n = {
    .type       = 1,
    .name	= "courB24_n",
    .height	= 21,
    .width	= 15,
    .lineheight = 24,
    .bytescol	= 4,
    .numcol     = 15,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 4, .r0 = 7, .ncol = 4, .xadj = 0, .pos = 0 }, // 33 [11]
	{ .l0 = 2, .r0 = 5, .ncol = 8, .xadj = 0, .pos = 11 }, // 34 [21]
	{ .l0 = 0, .r0 = 3, .ncol = 12, .xadj = 0, .pos = 32 }, // 35 [32]
	{ .l0 = 1, .r0 = 4, .ncol = 10, .xadj = 0, .pos = 64 }, // 36 [27]
	{ .l0 = 1, .r0 = 4, .ncol = 10, .xadj = 0, .pos = 91 }, // 37 [27]
	{ .l0 = 1, .r0 = 3, .ncol = 11, .xadj = 0, .pos = 118 }, // 38 [29]
	{ .l0 = 4, .r0 = 8, .ncol = 3, .xadj = 0, .pos = 147 }, // 39 [8]
	{ .l0 = 5, .r0 = 5, .ncol = 5, .xadj = 0, .pos = 155 }, // 40 [14]
	{ .l0 = 2, .r0 = 8, .ncol = 5, .xadj = 0, .pos = 169 }, // 41 [14]
	{ .l0 = 1, .r0 = 4, .ncol = 10, .xadj = 0, .pos = 183 }, // 42 [27]
	{ .l0 = 0, .r0 = 3, .ncol = 12, .xadj = 0, .pos = 210 }, // 43 [32]
	{ .l0 = 3, .r0 = 7, .ncol = 5, .xadj = 0, .pos = 242 }, // 44 [14]
	{ .l0 = 1, .r0 = 3, .ncol = 11, .xadj = 0, .pos = 256 }, // 45 [29]
	{ .l0 = 4, .r0 = 8, .ncol = 3, .xadj = 0, .pos = 285 }, // 46 [8]
	{ .l0 = 1, .r0 = 3, .ncol = 11, .xadj = 0, .pos = 293 }, // 47 [29]
	{ .l0 = 1, .r0 = 4, .ncol = 10, .xadj = 0, .pos = 322 }, // 48 [27]
	{ .l0 = 1, .r0 = 4, .ncol = 10, .xadj = 0, .pos = 349 }, // 49 [27]
	{ .l0 = 0, .r0 = 4, .ncol = 11, .xadj = 0, .pos = 376 }, // 50 [29]
	{ .l0 = 0, .r0 = 4, .ncol = 11, .xadj = 0, .pos = 405 }, // 51 [29]
	{ .l0 = 0, .r0 = 4, .ncol = 11, .xadj = 0, .pos = 434 }, // 52 [29]
	{ .l0 = 1, .r0 = 3, .ncol = 11, .xadj = 0, .pos = 463 }, // 53 [29]
	{ .l0 = 2, .r0 = 3, .ncol = 10, .xadj = 0, .pos = 492 }, // 54 [27]
	{ .l0 = 1, .r0 = 4, .ncol = 10, .xadj = 0, .pos = 519 }, // 55 [27]
	{ .l0 = 1, .r0 = 4, .ncol = 10, .xadj = 0, .pos = 546 }, // 56 [27]
	{ .l0 = 2, .r0 = 3, .ncol = 10, .xadj = 0, .pos = 573 }, // 57 [27]
	{ .l0 = 4, .r0 = 8, .ncol = 3, .xadj = 0, .pos = 600 }, // 58 [8]
	{ .l0 = 2, .r0 = 8, .ncol = 5, .xadj = 0, .pos = 608 }, // 59 [14]
	{ .l0 = 0, .r0 = 2, .ncol = 13, .xadj = 0, .pos = 622 }, // 60 [35]
	{ .l0 = 0, .r0 = 3, .ncol = 12, .xadj = 0, .pos = 657 }, // 61 [32]
	{ .l0 = 0, .r0 = 2, .ncol = 13, .xadj = 0, .pos = 689 }, // 62 [35]
	{ .l0 = 2, .r0 = 4, .ncol = 9, .xadj = 0, .pos = 724 }, // 63 [24]
    },
    .data       = {
	252, 1, 192, 255, 51, 248, 127, 6, 254, 0, 0,	// 33
	252, 1, 128, 15, 0, 240, 0, 0, 0, 0, 0, 0, 0, 248, 3, 0, 31, 0, 224, 1, 0,	// 34
	0, 24, 0, 24, 3, 0, 227, 31, 224, 255, 243, 255, 1, 254, 49, 0, 48, 254, 1, 254, 63, 255, 31, 224, 31, 3, 0, 99, 0, 96, 0, 0,	// 35
	240, 240, 0, 63, 30, 48, 134, 1, 134, 97, 240, 48, 252, 30, 134, 31, 198, 48, 224, 49, 7, 60, 126, 0, 128, 7, 0,	// 36
	0, 8, 0, 15, 1, 48, 51, 0, 66, 2, 64, 104, 15, 152, 53, 3, 158, 66, 0, 88, 8, 0, 153, 1, 32, 30, 0,	// 37
	0, 240, 0, 156, 63, 192, 63, 6, 140, 195, 128, 225, 24, 48, 184, 3, 14, 62, 128, 193, 7, 0, 220, 1, 128, 49, 0, 0, 6,	// 38
	124, 0, 128, 63, 0, 240, 1, 0,	// 39
	128, 127, 0, 254, 127, 240, 1, 62, 7, 0, 110, 0, 128, 1,	// 40
	6, 0, 216, 1, 128, 243, 1, 62, 248, 255, 1, 248, 7, 0,	// 41
	48, 0, 0, 134, 1, 128, 57, 0, 160, 3, 224, 31, 0, 252, 3, 0, 208, 1, 0, 115, 0, 48, 12, 0, 6, 0, 0,	// 42
	0, 6, 0, 192, 0, 0, 24, 0, 0, 3, 0, 96, 0, 240, 255, 3, 254, 127, 0, 48, 0, 0, 6, 0, 192, 0, 0, 24, 0, 0, 3, 0,	// 43
	0, 0, 12, 0, 224, 0, 0, 15, 0, 224, 0, 0, 12, 0,	// 44
	0, 6, 0, 192, 0, 0, 24, 0, 0, 3, 0, 96, 0, 0, 12, 0, 128, 1, 0, 48, 0, 0, 6, 0, 192, 0, 0, 24, 0,	// 45
	0, 192, 1, 0, 56, 0, 0, 7,	// 46
	0, 0, 12, 0, 224, 1, 0, 15, 0, 120, 0, 192, 3, 0, 30, 0, 240, 0, 128, 7, 0, 60, 0, 224, 1, 0, 12, 0, 0,	// 47
	240, 63, 128, 255, 31, 48, 0, 3, 3, 192, 96, 0, 24, 12, 0, 131, 1, 96, 96, 0, 6, 252, 255, 0, 254, 7, 0,	// 48
	12, 128, 129, 1, 48, 48, 0, 6, 7, 192, 224, 255, 31, 252, 255, 3, 0, 96, 0, 0, 12, 0, 128, 1, 0, 48, 0,	// 49
	0, 128, 1, 7, 56, 240, 128, 7, 7, 248, 96, 128, 27, 12, 56, 131, 129, 99, 48, 56, 12, 142, 131, 129, 63, 48, 224, 3, 6,	// 50
	0, 96, 0, 3, 28, 112, 0, 7, 7, 192, 96, 48, 24, 12, 6, 131, 193, 96, 48, 28, 12, 206, 199, 129, 223, 31, 224, 241, 1,	// 51
	0, 24, 0, 192, 3, 0, 126, 0, 240, 12, 128, 135, 25, 56, 48, 131, 3, 102, 240, 255, 15, 254, 255, 1, 0, 51, 0, 96, 6,	// 52
	0, 96, 192, 63, 28, 248, 7, 7, 195, 192, 96, 12, 24, 140, 1, 131, 49, 96, 48, 14, 14, 134, 227, 192, 240, 31, 0, 248, 0,	// 53
	192, 63, 0, 254, 31, 224, 153, 3, 142, 225, 192, 24, 24, 28, 3, 131, 97, 96, 48, 28, 14, 6, 255, 192, 192, 15, 0,	// 54
	14, 0, 192, 1, 0, 24, 0, 0, 3, 0, 96, 0, 28, 12, 240, 131, 193, 15, 48, 63, 0, 254, 0, 192, 3, 0, 0,	// 55
	120, 124, 128, 223, 31, 48, 30, 7, 131, 193, 96, 48, 24, 12, 6, 131, 193, 96, 96, 60, 14, 252, 254, 0, 143, 15, 0,	// 56
	240, 131, 129, 255, 48, 48, 56, 6, 3, 198, 96, 192, 24, 12, 24, 131, 129, 49, 96, 24, 7, 252, 127, 0, 254, 3, 0,	// 57
	192, 193, 1, 56, 56, 0, 7, 7,	// 58
	0, 0, 12, 0, 224, 0, 7, 15, 224, 224, 0, 28, 12, 0,	// 59
	0, 6, 0, 192, 0, 0, 60, 0, 128, 7, 0, 152, 1, 0, 51, 0, 48, 12, 0, 134, 1, 96, 96, 0, 12, 12, 192, 0, 3, 24, 96, 0, 1, 8, 0,	// 60
	128, 25, 0, 48, 3, 0, 102, 0, 192, 12, 0, 152, 1, 0, 51, 0, 96, 6, 0, 204, 0, 128, 25, 0, 48, 3, 0, 102, 0, 192, 12, 0,	// 61
	16, 128, 0, 6, 24, 192, 0, 3, 48, 48, 0, 6, 6, 128, 97, 0, 48, 12, 0, 204, 0, 128, 25, 0, 224, 1, 0, 60, 0, 0, 3, 0, 96, 0, 0,	// 62
	120, 0, 128, 15, 0, 48, 0, 0, 6, 206, 192, 224, 25, 24, 12, 0, 199, 0, 192, 31, 0, 240, 1, 0,	// 63

    }
};
