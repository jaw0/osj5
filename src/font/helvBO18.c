
// file: font/helvBO18.bdf
// font: -Adobe-Helvetica-Bold-O-Normal--18-180-75-75-P-104-ISO10646-1

#include <font.h>

const struct Font font_helvBO18 = {
    .type       = 1,
    .name	= "helvBO18",
    .height	= 18,
    .width	= 19,
    .bytescol	= 4,
    .numcol     = 19,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 4, .r0 = 8, .ncol = 7, .xadj = -12, .pos = 0 }, // 33 [16]
	{ .l0 = 6, .r0 = 6, .ncol = 7, .xadj = -10, .pos = 16 }, // 34 [16]
	{ .l0 = 3, .r0 = 4, .ncol = 12, .xadj = -7, .pos = 32 }, // 35 [27]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 59 }, // 36 [23]
	{ .l0 = 5, .r0 = 2, .ncol = 12, .xadj = -3, .pos = 82 }, // 37 [27]
	{ .l0 = 4, .r0 = 3, .ncol = 12, .xadj = -5, .pos = 109 }, // 38 [27]
	{ .l0 = 6, .r0 = 10, .ncol = 3, .xadj = -14, .pos = 136 }, // 39 [7]
	{ .l0 = 4, .r0 = 7, .ncol = 8, .xadj = -12, .pos = 143 }, // 40 [18]
	{ .l0 = 2, .r0 = 9, .ncol = 8, .xadj = -11, .pos = 161 }, // 41 [18]
	{ .l0 = 6, .r0 = 7, .ncol = 6, .xadj = -10, .pos = 179 }, // 42 [14]
	{ .l0 = 4, .r0 = 6, .ncol = 9, .xadj = -8, .pos = 193 }, // 43 [21]
	{ .l0 = 3, .r0 = 13, .ncol = 3, .xadj = -14, .pos = 214 }, // 44 [7]
	{ .l0 = 5, .r0 = 8, .ncol = 6, .xadj = -10, .pos = 221 }, // 45 [14]
	{ .l0 = 4, .r0 = 13, .ncol = 2, .xadj = -14, .pos = 235 }, // 46 [5]
	{ .l0 = 3, .r0 = 8, .ncol = 8, .xadj = -14, .pos = 240 }, // 47 [18]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 258 }, // 48 [23]
	{ .l0 = 4, .r0 = 7, .ncol = 8, .xadj = -9, .pos = 281 }, // 49 [18]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 299 }, // 50 [23]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 322 }, // 51 [23]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 345 }, // 52 [23]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 368 }, // 53 [23]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 391 }, // 54 [23]
	{ .l0 = 4, .r0 = 5, .ncol = 10, .xadj = -9, .pos = 414 }, // 55 [23]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 437 }, // 56 [23]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 460 }, // 57 [23]
	{ .l0 = 4, .r0 = 11, .ncol = 4, .xadj = -13, .pos = 483 }, // 58 [9]
	{ .l0 = 3, .r0 = 11, .ncol = 5, .xadj = -13, .pos = 492 }, // 59 [12]
	{ .l0 = 4, .r0 = 6, .ncol = 9, .xadj = -8, .pos = 504 }, // 60 [21]
	{ .l0 = 4, .r0 = 6, .ncol = 9, .xadj = -8, .pos = 525 }, // 61 [21]
	{ .l0 = 4, .r0 = 6, .ncol = 9, .xadj = -8, .pos = 546 }, // 62 [21]
	{ .l0 = 6, .r0 = 4, .ncol = 9, .xadj = -8, .pos = 567 }, // 63 [21]
	{ .l0 = 5, .r0 = 0, .ncol = 14, .xadj = -1, .pos = 588 }, // 64 [32]
	{ .l0 = 3, .r0 = 4, .ncol = 12, .xadj = -6, .pos = 620 }, // 65 [27]
	{ .l0 = 3, .r0 = 4, .ncol = 12, .xadj = -6, .pos = 647 }, // 66 [27]
	{ .l0 = 4, .r0 = 2, .ncol = 13, .xadj = -5, .pos = 674 }, // 67 [30]
	{ .l0 = 3, .r0 = 2, .ncol = 14, .xadj = -5, .pos = 704 }, // 68 [32]
	{ .l0 = 3, .r0 = 3, .ncol = 13, .xadj = -7, .pos = 736 }, // 69 [30]
	{ .l0 = 3, .r0 = 3, .ncol = 13, .xadj = -8, .pos = 766 }, // 70 [30]
	{ .l0 = 4, .r0 = 2, .ncol = 13, .xadj = -5, .pos = 796 }, // 71 [30]
	{ .l0 = 3, .r0 = 2, .ncol = 14, .xadj = -6, .pos = 826 }, // 72 [32]
	{ .l0 = 3, .r0 = 10, .ncol = 6, .xadj = -14, .pos = 858 }, // 73 [14]
	{ .l0 = 3, .r0 = 5, .ncol = 11, .xadj = -9, .pos = 872 }, // 74 [25]
	{ .l0 = 3, .r0 = 1, .ncol = 15, .xadj = -5, .pos = 897 }, // 75 [34]
	{ .l0 = 3, .r0 = 7, .ncol = 9, .xadj = -9, .pos = 931 }, // 76 [21]
	{ .l0 = 3, .r0 = 0, .ncol = 16, .xadj = -2, .pos = 952 }, // 77 [36]
	{ .l0 = 3, .r0 = 1, .ncol = 15, .xadj = -5, .pos = 988 }, // 78 [34]
	{ .l0 = 4, .r0 = 1, .ncol = 14, .xadj = -4, .pos = 1022 }, // 79 [32]
	{ .l0 = 3, .r0 = 3, .ncol = 13, .xadj = -7, .pos = 1054 }, // 80 [30]
	{ .l0 = 4, .r0 = 0, .ncol = 15, .xadj = -3, .pos = 1084 }, // 81 [34]
	{ .l0 = 3, .r0 = 3, .ncol = 13, .xadj = -6, .pos = 1118 }, // 82 [30]
	{ .l0 = 4, .r0 = 4, .ncol = 11, .xadj = -7, .pos = 1148 }, // 83 [25]
	{ .l0 = 5, .r0 = 3, .ncol = 11, .xadj = -8, .pos = 1173 }, // 84 [25]
	{ .l0 = 4, .r0 = 2, .ncol = 13, .xadj = -6, .pos = 1198 }, // 85 [30]
	{ .l0 = 6, .r0 = 2, .ncol = 11, .xadj = -6, .pos = 1228 }, // 86 [25]
	{ .l0 = 5, .r0 = 0, .ncol = 14, .xadj = -1, .pos = 1253 }, // 87 [32]
	{ .l0 = 2, .r0 = 2, .ncol = 15, .xadj = -7, .pos = 1285 }, // 88 [34]
	{ .l0 = 6, .r0 = 2, .ncol = 11, .xadj = -6, .pos = 1319 }, // 89 [25]
	{ .l0 = 2, .r0 = 4, .ncol = 13, .xadj = -8, .pos = 1344 }, // 90 [30]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -13, .pos = 1374 }, // 91 [21]
	{ .l0 = 5, .r0 = 11, .ncol = 3, .xadj = -14, .pos = 1395 }, // 92 [7]
	{ .l0 = 1, .r0 = 9, .ncol = 9, .xadj = -13, .pos = 1402 }, // 93 [21]
	{ .l0 = 5, .r0 = 5, .ncol = 9, .xadj = -8, .pos = 1423 }, // 94 [21]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -9, .pos = 1444 }, // 95 [23]
	{ .l0 = 6, .r0 = 8, .ncol = 5, .xadj = -14, .pos = 1467 }, // 96 [12]
	{ .l0 = 3, .r0 = 7, .ncol = 9, .xadj = -9, .pos = 1479 }, // 97 [21]
	{ .l0 = 3, .r0 = 5, .ncol = 11, .xadj = -8, .pos = 1500 }, // 98 [25]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 1525 }, // 99 [23]
	{ .l0 = 3, .r0 = 4, .ncol = 12, .xadj = -8, .pos = 1548 }, // 100 [27]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 1575 }, // 101 [23]
	{ .l0 = 4, .r0 = 7, .ncol = 8, .xadj = -12, .pos = 1598 }, // 102 [18]
	{ .l0 = 3, .r0 = 5, .ncol = 11, .xadj = -8, .pos = 1616 }, // 103 [25]
	{ .l0 = 3, .r0 = 5, .ncol = 11, .xadj = -8, .pos = 1641 }, // 104 [25]
	{ .l0 = 3, .r0 = 10, .ncol = 6, .xadj = -14, .pos = 1666 }, // 105 [14]
	{ .l0 = 0, .r0 = 10, .ncol = 9, .xadj = -14, .pos = 1680 }, // 106 [21]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 1701 }, // 107 [23]
	{ .l0 = 3, .r0 = 10, .ncol = 6, .xadj = -14, .pos = 1724 }, // 108 [14]
	{ .l0 = 3, .r0 = 1, .ncol = 15, .xadj = -4, .pos = 1738 }, // 109 [34]
	{ .l0 = 3, .r0 = 5, .ncol = 11, .xadj = -8, .pos = 1772 }, // 110 [25]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 1797 }, // 111 [23]
	{ .l0 = 2, .r0 = 5, .ncol = 12, .xadj = -8, .pos = 1820 }, // 112 [27]
	{ .l0 = 3, .r0 = 5, .ncol = 11, .xadj = -8, .pos = 1847 }, // 113 [25]
	{ .l0 = 3, .r0 = 8, .ncol = 8, .xadj = -12, .pos = 1872 }, // 114 [18]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 1890 }, // 115 [23]
	{ .l0 = 4, .r0 = 8, .ncol = 7, .xadj = -12, .pos = 1913 }, // 116 [16]
	{ .l0 = 3, .r0 = 5, .ncol = 11, .xadj = -8, .pos = 1929 }, // 117 [25]
	{ .l0 = 4, .r0 = 6, .ncol = 9, .xadj = -10, .pos = 1954 }, // 118 [21]
	{ .l0 = 4, .r0 = 2, .ncol = 13, .xadj = -5, .pos = 1975 }, // 119 [30]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -9, .pos = 2005 }, // 120 [23]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -10, .pos = 2028 }, // 121 [23]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -10, .pos = 2051 }, // 122 [23]
	{ .l0 = 4, .r0 = 8, .ncol = 7, .xadj = -11, .pos = 2074 }, // 123 [16]
	{ .l0 = 2, .r0 = 10, .ncol = 7, .xadj = -14, .pos = 2090 }, // 124 [16]
	{ .l0 = 4, .r0 = 8, .ncol = 7, .xadj = -10, .pos = 2106 }, // 125 [16]
	{ .l0 = 5, .r0 = 5, .ncol = 9, .xadj = -8, .pos = 2122 }, // 126 [21]
	{ .l0 = 19, .r0 = 0, .ncol = 0, .xadj = -19, .pos = 2143 }, // 127 [0]
    },
    .data       = {
	0, 48, 0, 192, 0, 56, 3, 254, 0, 255, 0, 124, 0, 112, 0, 0,	// 33
	28, 0, 60, 0, 112, 0, 0, 0, 0, 28, 0, 60, 0, 112, 0, 0,	// 34
	0, 6, 0, 24, 0, 99, 3, 204, 15, 240, 15, 224, 219, 224, 243, 131, 253, 3, 248, 6, 248, 24, 96, 99, 0, 12, 0,	// 35
	0, 24, 192, 225, 128, 15, 3, 55, 60, 204, 63, 240, 199, 240, 156, 3, 227, 7, 28, 15, 96, 0, 0,	// 36
	56, 48, 240, 225, 96, 198, 129, 217, 3, 190, 7, 112, 7, 0, 206, 1, 158, 15, 28, 51, 56, 204, 96, 240, 1, 128, 3,	// 37
	0, 15, 0, 126, 0, 156, 3, 63, 12, 254, 48, 152, 231, 96, 254, 129, 207, 3, 28, 31, 0, 238, 0, 24, 3, 0, 8,	// 38
	28, 0, 60, 0, 112, 0, 0,	// 39
	128, 63, 128, 255, 131, 255, 31, 15, 224, 14, 0, 27, 0, 56, 0, 64, 0, 0,	// 40
	0, 0, 2, 0, 12, 0, 120, 0, 112, 7, 240, 248, 255, 193, 255, 1, 252, 1,	// 41
	50, 0, 120, 0, 192, 1, 192, 15, 0, 36, 0, 24, 0, 0,	// 42
	0, 3, 0, 12, 0, 176, 1, 224, 7, 224, 31, 128, 31, 0, 54, 0, 192, 0, 0, 3, 0,	// 43
	0, 128, 0, 224, 2, 128, 7,	// 44
	0, 3, 0, 12, 0, 48, 0, 192, 0, 0, 3, 0, 12, 0,	// 45
	0, 56, 0, 224, 0,	// 46
	0, 48, 0, 240, 0, 240, 0, 240, 0, 240, 0, 240, 0, 240, 0, 192, 0, 0,	// 47
	192, 7, 192, 127, 192, 255, 3, 7, 14, 14, 48, 24, 224, 224, 224, 129, 255, 3, 252, 7, 192, 7, 0,	// 48
	16, 0, 96, 0, 128, 129, 3, 230, 15, 252, 63, 248, 31, 224, 7, 128, 1, 0,	// 49
	0, 56, 96, 240, 192, 225, 131, 195, 13, 134, 51, 24, 199, 96, 28, 131, 59, 12, 126, 48, 240, 0, 0,	// 50
	0, 12, 0, 112, 128, 129, 3, 7, 12, 206, 48, 24, 227, 96, 220, 131, 251, 7, 126, 15, 240, 0, 0,	// 51
	0, 7, 0, 30, 0, 124, 0, 184, 1, 112, 6, 224, 248, 192, 253, 131, 255, 1, 126, 6, 56, 0, 0,	// 52
	0, 28, 128, 241, 128, 7, 131, 31, 12, 110, 48, 152, 227, 96, 252, 129, 241, 7, 6, 7, 24, 0, 0,	// 53
	192, 3, 192, 127, 128, 255, 3, 111, 14, 206, 48, 24, 195, 96, 156, 131, 225, 7, 14, 15, 48, 0, 0,	// 54
	0, 48, 24, 240, 96, 224, 131, 225, 3, 198, 3, 152, 3, 96, 7, 128, 15, 0, 30, 0, 56, 0, 0,	// 55
	0, 14, 0, 124, 128, 251, 3, 127, 12, 238, 48, 24, 195, 96, 156, 131, 249, 7, 126, 15, 240, 0, 0,	// 56
	0, 24, 192, 225, 128, 15, 3, 127, 12, 142, 49, 24, 230, 96, 248, 129, 243, 3, 252, 3, 224, 1, 0,	// 57
	0, 56, 0, 224, 0, 7, 0, 28, 0,	// 58
	0, 128, 0, 224, 2, 128, 7, 28, 0, 112, 0, 0,	// 59
	0, 1, 0, 14, 0, 56, 0, 176, 1, 192, 6, 0, 49, 0, 198, 0, 24, 2, 32, 0, 0,	// 60
	0, 12, 0, 51, 0, 204, 0, 48, 3, 192, 12, 0, 51, 0, 204, 0, 48, 3, 192, 0, 0,	// 61
	0, 8, 128, 48, 0, 198, 0, 24, 1, 192, 6, 0, 27, 0, 56, 0, 224, 0, 0, 1, 0,	// 62
	12, 51, 56, 206, 240, 60, 195, 56, 0, 99, 0, 204, 1, 240, 3, 192, 7, 0, 14, 0, 0,	// 63
	128, 15, 128, 255, 128, 15, 7, 15, 56, 14, 207, 24, 127, 118, 142, 217, 28, 102, 51, 142, 205, 62, 54, 254, 193, 61, 6, 54, 28, 56, 60, 0,	// 64
	0, 48, 0, 240, 0, 240, 3, 240, 3, 240, 7, 240, 27, 224, 99, 192, 131, 1, 7, 6, 252, 255, 224, 255, 3, 252, 15,	// 65
	0, 60, 0, 255, 128, 255, 195, 255, 12, 255, 48, 28, 195, 48, 12, 195, 48, 12, 227, 57, 252, 255, 240, 251, 129, 199, 3,	// 66
	192, 7, 192, 127, 192, 255, 129, 15, 14, 14, 48, 28, 192, 112, 0, 195, 0, 14, 3, 28, 12, 120, 240, 224, 128, 131, 1, 12, 0, 0,	// 67
	0, 60, 0, 254, 128, 255, 195, 255, 12, 63, 48, 28, 192, 48, 0, 195, 0, 14, 3, 24, 12, 112, 112, 240, 128, 255, 1, 254, 3, 224, 3, 0,	// 68
	0, 56, 0, 254, 128, 255, 195, 255, 13, 255, 48, 28, 195, 48, 12, 195, 48, 12, 195, 48, 12, 195, 48, 12, 192, 0, 0, 3, 0, 0,	// 69
	0, 56, 0, 254, 128, 255, 195, 255, 1, 255, 0, 28, 3, 48, 12, 192, 48, 0, 195, 0, 12, 3, 48, 0, 192, 0, 0, 3, 0, 0,	// 70
	192, 7, 192, 127, 128, 255, 1, 15, 14, 14, 48, 24, 192, 112, 24, 195, 96, 12, 131, 25, 12, 254, 240, 248, 195, 227, 1, 14, 0, 0,	// 71
	0, 56, 0, 254, 128, 255, 195, 255, 1, 255, 0, 28, 3, 0, 12, 0, 48, 0, 192, 56, 0, 255, 128, 255, 195, 255, 1, 127, 0, 28, 0, 0,	// 72
	0, 56, 0, 254, 128, 255, 195, 255, 1, 127, 0, 28, 0, 0,	// 73
	0, 30, 0, 248, 0, 224, 3, 0, 12, 0, 48, 0, 224, 0, 248, 3, 254, 7, 255, 7, 252, 1, 112, 0, 0,	// 74
	0, 56, 0, 254, 128, 255, 195, 255, 1, 255, 0, 156, 7, 0, 63, 0, 254, 3, 56, 31, 112, 248, 224, 128, 195, 1, 12, 7, 32, 12, 0, 16, 0, 0,	// 75
	0, 56, 0, 254, 128, 255, 195, 255, 13, 127, 48, 28, 192, 0, 0, 3, 0, 12, 0, 48, 0,	// 76
	0, 56, 0, 254, 128, 255, 195, 127, 0, 63, 0, 252, 7, 128, 255, 3, 224, 15, 0, 62, 0, 62, 0, 60, 0, 60, 0, 120, 56, 112, 252, 224, 255, 195, 255, 1,	// 77
	0, 56, 0, 254, 128, 255, 195, 255, 1, 127, 0, 252, 0, 192, 15, 0, 252, 0, 192, 15, 0, 248, 0, 248, 3, 254, 15, 255, 3, 252, 0, 112, 0, 0,	// 78
	192, 7, 192, 127, 192, 255, 129, 15, 14, 14, 48, 28, 192, 112, 0, 195, 0, 14, 3, 56, 12, 112, 112, 240, 129, 255, 3, 254, 3, 224, 3, 0,	// 79
	0, 56, 0, 254, 128, 255, 195, 255, 1, 255, 0, 28, 3, 48, 12, 192, 48, 0, 195, 0, 140, 3, 240, 7, 192, 31, 0, 62, 0, 0,	// 80
	128, 7, 192, 127, 128, 255, 1, 31, 14, 30, 48, 24, 192, 112, 0, 195, 128, 13, 3, 62, 12, 112, 48, 192, 195, 193, 15, 254, 55, 248, 15, 128, 7, 0,	// 81
	0, 56, 0, 254, 128, 255, 195, 255, 1, 255, 0, 28, 3, 48, 12, 192, 48, 0, 195, 56, 140, 255, 240, 255, 195, 223, 1, 62, 0, 0,	// 82
	0, 28, 112, 240, 224, 195, 131, 31, 12, 119, 48, 140, 195, 48, 158, 195, 240, 15, 143, 31, 60, 60, 224, 0, 0,	// 83
	3, 0, 12, 224, 48, 248, 195, 254, 15, 255, 7, 252, 1, 112, 0, 192, 0, 0, 3, 0, 12, 0, 48, 0, 0,	// 84
	128, 31, 224, 127, 240, 255, 195, 31, 12, 7, 48, 0, 192, 0, 128, 3, 0, 15, 128, 31, 224, 63, 240, 63, 192, 31, 0, 7, 0, 0,	// 85
	255, 1, 252, 255, 240, 255, 3, 0, 15, 0, 31, 0, 63, 0, 63, 0, 63, 0, 63, 0, 60, 0, 48, 0, 0,	// 86
	255, 1, 252, 255, 240, 255, 3, 128, 15, 128, 15, 128, 15, 128, 15, 192, 15, 0, 255, 63, 252, 255, 0, 192, 3, 192, 3, 224, 7, 224, 7, 0,	// 87
	0, 48, 0, 224, 0, 192, 195, 128, 3, 15, 7, 252, 14, 192, 31, 0, 248, 3, 224, 63, 192, 241, 128, 3, 3, 7, 0, 15, 0, 28, 0, 48, 0, 0,	// 88
	31, 0, 252, 227, 240, 255, 3, 240, 15, 128, 7, 128, 7, 128, 15, 128, 31, 0, 31, 0, 28, 0, 48, 0, 0,	// 89
	0, 48, 0, 224, 0, 192, 3, 128, 15, 3, 55, 12, 206, 48, 28, 195, 56, 12, 115, 48, 236, 192, 240, 1, 192, 3, 0, 7, 0, 0,	// 90
	0, 192, 3, 224, 15, 248, 63, 252, 207, 255, 7, 255, 1, 240, 0, 192, 0, 0, 3, 0, 0,	// 91
	127, 0, 252, 255, 0, 248, 3,	// 92
	0, 0, 3, 0, 12, 0, 60, 0, 254, 131, 255, 207, 255, 240, 127, 192, 31, 0, 15, 0, 0,	// 93
	192, 0, 128, 3, 0, 7, 0, 14, 0, 28, 0, 56, 0, 224, 3, 0, 62, 0, 192, 0, 0,	// 94
	0, 0, 3, 0, 12, 0, 48, 0, 192, 0, 0, 3, 0, 12, 0, 48, 0, 192, 0, 0, 3, 0, 12,	// 95
	1, 0, 12, 0, 112, 0, 128, 1, 0, 4, 0, 0,	// 96
	0, 28, 0, 248, 0, 246, 3, 204, 12, 176, 17, 192, 230, 0, 251, 3, 252, 15, 224, 7, 0,	// 97
	0, 56, 0, 254, 128, 255, 195, 255, 7, 255, 48, 156, 193, 0, 131, 3, 12, 7, 240, 31, 128, 63, 0, 60, 0,	// 98
	0, 15, 0, 127, 0, 254, 3, 56, 12, 112, 48, 192, 192, 0, 131, 3, 12, 7, 112, 12, 128, 1, 0,	// 99
	0, 15, 0, 127, 0, 254, 3, 56, 12, 112, 48, 192, 96, 0, 195, 3, 248, 15, 248, 63, 252, 31, 240, 7, 192, 1, 0,	// 100
	0, 15, 0, 127, 0, 254, 3, 248, 12, 112, 51, 192, 204, 0, 179, 3, 252, 6, 224, 27, 0, 15, 0,	// 101
	48, 56, 192, 254, 128, 255, 131, 255, 1, 127, 0, 220, 0, 48, 3, 192, 0, 0,	// 102
	0, 143, 1, 127, 14, 254, 51, 56, 204, 112, 48, 195, 96, 14, 195, 31, 248, 63, 240, 63, 192, 15, 0, 3, 0,	// 103
	0, 56, 0, 254, 128, 255, 195, 255, 1, 127, 0, 156, 1, 0, 131, 3, 204, 15, 240, 63, 192, 31, 0, 14, 0,	// 104
	0, 56, 0, 254, 0, 255, 195, 252, 1, 115, 0, 12, 0, 0,	// 105
	0, 0, 3, 0, 12, 0, 56, 0, 254, 128, 255, 193, 255, 48, 127, 192, 28, 0, 3, 0, 0,	// 106
	0, 56, 0, 254, 128, 255, 195, 255, 1, 255, 3, 28, 63, 0, 238, 3, 28, 15, 48, 48, 64, 0, 0,	// 107
	0, 56, 0, 254, 128, 255, 195, 255, 1, 127, 0, 28, 0, 0,	// 108
	0, 56, 0, 254, 0, 255, 3, 252, 1, 240, 0, 128, 225, 0, 243, 3, 252, 15, 240, 7, 128, 3, 0, 134, 3, 204, 15, 240, 63, 192, 31, 0, 14, 0,	// 109
	0, 56, 0, 254, 0, 255, 3, 252, 1, 112, 0, 128, 1, 0, 131, 3, 204, 15, 240, 63, 192, 31, 0, 14, 0,	// 110
	0, 15, 0, 127, 0, 254, 3, 56, 12, 112, 48, 192, 224, 0, 195, 1, 252, 7, 224, 15, 0, 15, 0,	// 111
	0, 128, 3, 224, 15, 248, 63, 252, 31, 240, 31, 192, 195, 0, 6, 3, 12, 14, 48, 28, 192, 127, 0, 254, 0, 240, 0,	// 112
	0, 15, 0, 127, 0, 254, 3, 56, 12, 112, 48, 192, 96, 14, 195, 63, 248, 255, 240, 127, 192, 31, 0, 7, 0,	// 113
	0, 56, 0, 254, 0, 255, 3, 252, 1, 224, 0, 192, 1, 0, 3, 0, 12, 0,	// 114
	0, 24, 0, 227, 0, 158, 3, 248, 12, 112, 51, 192, 236, 0, 243, 1, 220, 7, 112, 14, 128, 1, 0,	// 115
	48, 28, 192, 254, 128, 255, 131, 255, 12, 126, 0, 216, 0, 0, 3, 0,	// 116
	0, 28, 0, 254, 0, 255, 3, 252, 12, 112, 48, 0, 96, 0, 192, 3, 224, 15, 240, 63, 192, 31, 0, 7, 0,	// 117
	240, 15, 192, 255, 0, 255, 3, 0, 15, 0, 31, 0, 31, 0, 63, 0, 60, 0, 48, 0, 0,	// 118
	240, 1, 192, 255, 0, 255, 3, 0, 15, 0, 15, 192, 15, 0, 255, 3, 252, 15, 0, 60, 0, 62, 0, 127, 0, 124, 0, 112, 0, 0,	// 119
	0, 48, 0, 224, 0, 195, 1, 188, 3, 240, 7, 0, 30, 0, 252, 3, 56, 15, 112, 48, 192, 0, 0,	// 120
	0, 0, 195, 15, 12, 255, 56, 252, 127, 0, 248, 0, 240, 1, 248, 1, 252, 1, 240, 1, 192, 1, 0,	// 121
	0, 48, 0, 224, 0, 195, 3, 140, 15, 48, 55, 192, 206, 0, 31, 3, 60, 12, 112, 0, 192, 0, 0,	// 122
	0, 1, 0, 206, 7, 252, 191, 191, 195, 127, 0, 14, 0, 16, 0, 0,	// 123
	0, 0, 3, 192, 15, 240, 63, 252, 15, 255, 3, 252, 0, 48, 0, 0,	// 124
	0, 0, 2, 0, 28, 192, 255, 188, 127, 255, 7, 56, 14, 0, 16, 0,	// 125
	0, 3, 0, 14, 0, 24, 0, 96, 0, 128, 3, 0, 12, 0, 48, 0, 224, 0, 128, 1, 0,	// 126
		// 127

    }
};
