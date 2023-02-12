
// file: font/luBS19.bdf
// font: -B&H-Lucida-Bold-R-Normal-Sans-19-190-75-75-P-122-ISO10646-1

#include <font.h>

const struct Font font_luBS19 = {
    .type       = 1,
    .name	= "luBS19",
    .height	= 18,
    .width	= 19,
    .bytescol	= 4,
    .numcol     = 19,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 14, .ncol = 3, .xadj = -12, .pos = 0 }, // 33 [7]
	{ .l0 = 1, .r0 = 9, .ncol = 9, .xadj = -9, .pos = 7 }, // 34 [21]
	{ .l0 = 1, .r0 = 6, .ncol = 12, .xadj = -6, .pos = 28 }, // 35 [27]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 55 }, // 36 [23]
	{ .l0 = 1, .r0 = 2, .ncol = 16, .xadj = -2, .pos = 78 }, // 37 [36]
	{ .l0 = 1, .r0 = 4, .ncol = 14, .xadj = -4, .pos = 114 }, // 38 [32]
	{ .l0 = 1, .r0 = 14, .ncol = 4, .xadj = -14, .pos = 146 }, // 39 [9]
	{ .l0 = 1, .r0 = 13, .ncol = 5, .xadj = -12, .pos = 155 }, // 40 [12]
	{ .l0 = 1, .r0 = 13, .ncol = 5, .xadj = -12, .pos = 167 }, // 41 [12]
	{ .l0 = 1, .r0 = 11, .ncol = 7, .xadj = -10, .pos = 179 }, // 42 [16]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 195 }, // 43 [23]
	{ .l0 = 1, .r0 = 14, .ncol = 4, .xadj = -12, .pos = 218 }, // 44 [9]
	{ .l0 = 1, .r0 = 14, .ncol = 4, .xadj = -14, .pos = 227 }, // 45 [9]
	{ .l0 = 1, .r0 = 14, .ncol = 4, .xadj = -12, .pos = 236 }, // 46 [9]
	{ .l0 = 0, .r0 = 8, .ncol = 11, .xadj = -8, .pos = 245 }, // 47 [25]
	{ .l0 = 1, .r0 = 6, .ncol = 12, .xadj = -6, .pos = 270 }, // 48 [27]
	{ .l0 = 3, .r0 = 11, .ncol = 5, .xadj = -6, .pos = 297 }, // 49 [12]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -6, .pos = 309 }, // 50 [23]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 332 }, // 51 [23]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 355 }, // 52 [25]
	{ .l0 = 3, .r0 = 7, .ncol = 9, .xadj = -6, .pos = 380 }, // 53 [21]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 401 }, // 54 [25]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 426 }, // 55 [23]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 449 }, // 56 [25]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 474 }, // 57 [25]
	{ .l0 = 2, .r0 = 14, .ncol = 3, .xadj = -12, .pos = 499 }, // 58 [7]
	{ .l0 = 2, .r0 = 14, .ncol = 3, .xadj = -12, .pos = 506 }, // 59 [7]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 513 }, // 60 [25]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 538 }, // 61 [25]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 563 }, // 62 [25]
	{ .l0 = 1, .r0 = 9, .ncol = 9, .xadj = -8, .pos = 588 }, // 63 [21]
	{ .l0 = 2, .r0 = 2, .ncol = 15, .xadj = -3, .pos = 609 }, // 64 [34]
	{ .l0 = 0, .r0 = 5, .ncol = 14, .xadj = -4, .pos = 643 }, // 65 [32]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 675 }, // 66 [23]
	{ .l0 = 0, .r0 = 6, .ncol = 13, .xadj = -5, .pos = 698 }, // 67 [30]
	{ .l0 = 2, .r0 = 4, .ncol = 13, .xadj = -3, .pos = 728 }, // 68 [30]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -7, .pos = 758 }, // 69 [21]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -8, .pos = 779 }, // 70 [21]
	{ .l0 = 1, .r0 = 6, .ncol = 12, .xadj = -5, .pos = 800 }, // 71 [27]
	{ .l0 = 2, .r0 = 5, .ncol = 12, .xadj = -4, .pos = 827 }, // 72 [27]
	{ .l0 = 2, .r0 = 14, .ncol = 3, .xadj = -12, .pos = 854 }, // 73 [7]
	{ .l0 = 1, .r0 = 11, .ncol = 7, .xadj = -9, .pos = 861 }, // 74 [16]
	{ .l0 = 2, .r0 = 5, .ncol = 12, .xadj = -5, .pos = 877 }, // 75 [27]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -7, .pos = 904 }, // 76 [21]
	{ .l0 = 1, .r0 = 3, .ncol = 15, .xadj = -1, .pos = 925 }, // 77 [34]
	{ .l0 = 1, .r0 = 6, .ncol = 12, .xadj = -4, .pos = 959 }, // 78 [27]
	{ .l0 = 1, .r0 = 3, .ncol = 15, .xadj = -3, .pos = 986 }, // 79 [34]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -7, .pos = 1020 }, // 80 [23]
	{ .l0 = 1, .r0 = 1, .ncol = 17, .xadj = -3, .pos = 1043 }, // 81 [39]
	{ .l0 = 2, .r0 = 5, .ncol = 12, .xadj = -5, .pos = 1082 }, // 82 [27]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -8, .pos = 1109 }, // 83 [23]
	{ .l0 = 0, .r0 = 6, .ncol = 13, .xadj = -5, .pos = 1132 }, // 84 [30]
	{ .l0 = 1, .r0 = 6, .ncol = 12, .xadj = -4, .pos = 1162 }, // 85 [27]
	{ .l0 = 0, .r0 = 5, .ncol = 14, .xadj = -5, .pos = 1189 }, // 86 [32]
	{ .l0 = 0, .r0 = 2, .ncol = 17, .xadj = -1, .pos = 1221 }, // 87 [39]
	{ .l0 = 1, .r0 = 6, .ncol = 12, .xadj = -6, .pos = 1260 }, // 88 [27]
	{ .l0 = 1, .r0 = 5, .ncol = 13, .xadj = -5, .pos = 1287 }, // 89 [30]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 1317 }, // 90 [25]
	{ .l0 = 1, .r0 = 13, .ncol = 5, .xadj = -12, .pos = 1342 }, // 91 [12]
	{ .l0 = 0, .r0 = 8, .ncol = 11, .xadj = -8, .pos = 1354 }, // 92 [25]
	{ .l0 = 1, .r0 = 13, .ncol = 5, .xadj = -12, .pos = 1379 }, // 93 [12]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 1391 }, // 94 [25]
	{ .l0 = 1, .r0 = 10, .ncol = 8, .xadj = -9, .pos = 1416 }, // 95 [18]
	{ .l0 = 3, .r0 = 11, .ncol = 5, .xadj = -6, .pos = 1434 }, // 96 [12]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -7, .pos = 1446 }, // 97 [23]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -6, .pos = 1469 }, // 98 [25]
	{ .l0 = 1, .r0 = 10, .ncol = 8, .xadj = -9, .pos = 1494 }, // 99 [18]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 1512 }, // 100 [25]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -7, .pos = 1537 }, // 101 [23]
	{ .l0 = 1, .r0 = 10, .ncol = 8, .xadj = -10, .pos = 1560 }, // 102 [18]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 1578 }, // 103 [25]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 1603 }, // 104 [23]
	{ .l0 = 2, .r0 = 14, .ncol = 3, .xadj = -12, .pos = 1626 }, // 105 [7]
	{ .l0 = 0, .r0 = 13, .ncol = 6, .xadj = -12, .pos = 1633 }, // 106 [14]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 1647 }, // 107 [23]
	{ .l0 = 2, .r0 = 14, .ncol = 3, .xadj = -12, .pos = 1670 }, // 108 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 17, .xadj = 0, .pos = 1677 }, // 109 [39]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 1716 }, // 110 [23]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 1739 }, // 111 [25]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -6, .pos = 1764 }, // 112 [25]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 1789 }, // 113 [25]
	{ .l0 = 2, .r0 = 10, .ncol = 7, .xadj = -10, .pos = 1814 }, // 114 [16]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -7, .pos = 1830 }, // 115 [21]
	{ .l0 = 1, .r0 = 12, .ncol = 6, .xadj = -11, .pos = 1851 }, // 116 [14]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 1865 }, // 117 [23]
	{ .l0 = 0, .r0 = 7, .ncol = 12, .xadj = -6, .pos = 1888 }, // 118 [27]
	{ .l0 = 0, .r0 = 3, .ncol = 16, .xadj = -2, .pos = 1915 }, // 119 [36]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -8, .pos = 1951 }, // 120 [23]
	{ .l0 = 0, .r0 = 7, .ncol = 12, .xadj = -7, .pos = 1974 }, // 121 [27]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -7, .pos = 2001 }, // 122 [23]
	{ .l0 = 1, .r0 = 13, .ncol = 5, .xadj = -12, .pos = 2024 }, // 123 [12]
	{ .l0 = 2, .r0 = 15, .ncol = 2, .xadj = -14, .pos = 2036 }, // 124 [5]
	{ .l0 = 1, .r0 = 13, .ncol = 5, .xadj = -12, .pos = 2041 }, // 125 [12]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 2053 }, // 126 [25]
	{ .l0 = 19, .r0 = 0, .ncol = 0, .xadj = -19, .pos = 2078 }, // 127 [0]
    },
    .data       = {
	63, 48, 252, 207, 240, 63, 3,	// 33
	7, 0, 124, 0, 240, 1, 192, 0, 0, 0, 0, 0, 0, 240, 1, 192, 7, 0, 7, 0, 0,	// 34
	0, 6, 192, 152, 0, 227, 3, 252, 7, 254, 7, 252, 152, 16, 227, 3, 252, 15, 254, 7, 252, 24, 16, 99, 0, 12, 0,	// 35
	192, 192, 193, 7, 135, 63, 24, 254, 97, 159, 255, 255, 63, 142, 225, 29, 134, 127, 56, 252, 0, 192, 1,	// 36
	60, 0, 252, 131, 48, 12, 194, 48, 14, 255, 28, 240, 56, 0, 120, 0, 112, 0, 224, 0, 224, 1, 192, 225, 129, 195, 15, 7, 51, 4, 204, 16, 240, 3, 128, 7,	// 37
	0, 15, 0, 126, 224, 252, 129, 63, 14, 127, 48, 204, 199, 48, 62, 195, 252, 13, 51, 31, 120, 248, 192, 225, 3, 224, 13, 192, 35, 0, 7, 0,	// 38
	7, 0, 252, 0, 240, 3, 192, 1, 0,	// 39
	192, 15, 224, 255, 193, 255, 143, 7, 120, 7, 128, 3,	// 40
	7, 128, 123, 128, 199, 255, 15, 254, 31, 192, 15, 0,	// 41
	4, 0, 88, 0, 208, 3, 192, 0, 0, 61, 0, 88, 0, 64, 0, 0,	// 42
	128, 1, 0, 6, 0, 24, 0, 96, 0, 252, 63, 240, 255, 0, 24, 0, 96, 0, 128, 1, 0, 6, 0,	// 43
	0, 60, 2, 240, 15, 192, 31, 0, 63,	// 44
	128, 1, 0, 6, 0, 24, 0, 96, 0,	// 45
	0, 56, 0, 224, 0, 128, 3, 0, 14,	// 46
	0, 0, 2, 0, 14, 0, 62, 0, 62, 0, 62, 0, 30, 0, 31, 0, 31, 0, 31, 0, 28, 0, 16, 0, 0,	// 47
	240, 3, 240, 63, 224, 255, 129, 1, 6, 3, 48, 12, 192, 48, 0, 195, 0, 12, 6, 24, 248, 127, 192, 255, 0, 252, 0,	// 48
	3, 0, 12, 0, 240, 255, 195, 255, 15, 255, 63, 0,	// 49
	6, 56, 28, 240, 48, 224, 195, 128, 15, 3, 55, 12, 206, 112, 28, 195, 63, 12, 126, 48, 240, 192, 0,	// 50
	6, 56, 12, 195, 48, 12, 195, 48, 12, 195, 48, 12, 195, 112, 158, 195, 239, 15, 62, 31, 112, 56, 0,	// 51
	128, 3, 0, 15, 0, 62, 0, 220, 0, 56, 3, 112, 12, 112, 48, 192, 255, 15, 255, 63, 252, 255, 0, 48, 0,	// 52
	127, 56, 252, 193, 48, 6, 195, 24, 12, 227, 48, 140, 227, 48, 252, 193, 240, 7, 3, 15, 0,	// 53
	240, 3, 240, 63, 224, 255, 129, 51, 14, 103, 48, 140, 193, 48, 6, 195, 56, 14, 227, 31, 28, 127, 0, 120, 0,	// 54
	3, 32, 12, 224, 48, 224, 195, 224, 15, 195, 15, 140, 7, 176, 7, 192, 15, 0, 15, 0, 28, 0, 0,	// 55
	0, 14, 112, 126, 224, 251, 195, 63, 14, 243, 48, 140, 195, 48, 30, 195, 127, 14, 254, 31, 112, 126, 0, 240, 0,	// 56
	120, 0, 248, 227, 224, 31, 195, 113, 12, 131, 49, 12, 198, 48, 152, 195, 49, 7, 254, 31, 240, 63, 0, 63, 0,	// 57
	112, 56, 192, 225, 0, 135, 3,	// 58
	112, 60, 194, 241, 15, 199, 15,	// 59
	128, 0, 0, 6, 0, 24, 0, 240, 0, 192, 3, 128, 25, 0, 102, 0, 12, 3, 56, 28, 96, 96, 192, 129, 3,	// 60
	96, 12, 128, 49, 0, 198, 0, 24, 3, 96, 12, 128, 49, 0, 198, 0, 24, 3, 96, 12, 128, 49, 0, 198, 0,	// 61
	28, 56, 96, 96, 128, 195, 1, 12, 3, 96, 6, 128, 25, 0, 60, 0, 240, 0, 128, 1, 0, 6, 0, 16, 0,	// 62
	7, 0, 12, 0, 48, 48, 195, 224, 12, 195, 51, 156, 3, 240, 3, 128, 15, 0, 28, 0, 0,	// 63
	192, 7, 192, 32, 128, 0, 1, 225, 4, 194, 39, 136, 153, 16, 33, 66, 196, 8, 145, 53, 196, 159, 16, 71, 192, 4, 1, 2, 2, 48, 12, 128, 15, 0,	// 64
	0, 32, 0, 240, 0, 248, 1, 248, 1, 252, 3, 124, 12, 112, 48, 192, 207, 0, 255, 3, 240, 31, 0, 254, 3, 192, 15, 0, 60, 0, 128, 0,	// 65
	255, 63, 252, 255, 240, 255, 195, 48, 12, 195, 48, 140, 195, 240, 27, 195, 239, 15, 28, 31, 0, 60, 0,	// 66
	240, 3, 240, 63, 192, 255, 128, 135, 7, 6, 56, 28, 224, 48, 0, 195, 0, 12, 3, 48, 12, 192, 48, 0, 195, 1, 12, 7, 24, 0,	// 67
	255, 63, 252, 255, 240, 255, 195, 0, 12, 3, 48, 12, 192, 48, 0, 195, 1, 12, 7, 56, 120, 112, 224, 255, 1, 255, 3, 240, 3, 0,	// 68
	255, 63, 252, 255, 240, 255, 195, 48, 12, 195, 48, 12, 195, 48, 12, 195, 48, 12, 3, 48, 0,	// 69
	255, 63, 252, 255, 240, 255, 195, 48, 0, 195, 0, 12, 3, 48, 12, 192, 48, 0, 3, 0, 0,	// 70
	240, 3, 240, 63, 224, 255, 129, 7, 7, 7, 56, 12, 224, 48, 0, 195, 0, 12, 3, 48, 12, 254, 48, 248, 195, 225, 7,	// 71
	255, 63, 252, 255, 240, 255, 3, 48, 0, 192, 0, 0, 3, 0, 12, 0, 48, 0, 192, 0, 252, 255, 240, 255, 195, 255, 15,	// 72
	255, 63, 252, 255, 240, 255, 3,	// 73
	0, 128, 3, 0, 12, 0, 48, 0, 192, 255, 255, 255, 255, 247, 255, 15,	// 74
	255, 63, 252, 255, 240, 255, 3, 48, 0, 224, 1, 192, 31, 192, 251, 128, 195, 15, 7, 60, 12, 224, 16, 0, 3, 0, 8,	// 75
	255, 63, 252, 255, 240, 255, 3, 0, 12, 0, 48, 0, 192, 0, 0, 3, 0, 12, 0, 48, 0,	// 76
	255, 63, 252, 255, 240, 0, 192, 31, 0, 255, 3, 224, 63, 0, 252, 1, 128, 7, 128, 31, 192, 15, 224, 15, 192, 7, 0, 255, 63, 252, 255, 240, 255, 3,	// 77
	255, 63, 252, 255, 240, 1, 128, 15, 0, 120, 0, 192, 7, 0, 62, 0, 224, 1, 0, 31, 0, 248, 240, 255, 195, 255, 15,	// 78
	240, 3, 240, 63, 224, 255, 129, 135, 7, 7, 56, 12, 192, 48, 0, 195, 0, 12, 3, 48, 12, 192, 112, 128, 131, 135, 7, 252, 15, 240, 63, 0, 63, 0,	// 79
	255, 63, 252, 255, 240, 255, 195, 96, 0, 131, 1, 12, 6, 112, 28, 192, 63, 0, 254, 0, 248, 0, 0,	// 80
	240, 3, 240, 63, 224, 255, 129, 135, 7, 7, 56, 12, 192, 48, 0, 195, 0, 12, 3, 48, 12, 192, 113, 128, 143, 135, 127, 252, 223, 241, 63, 15, 63, 60, 0, 112, 0, 64, 0,	// 81
	255, 63, 252, 255, 240, 255, 195, 48, 0, 195, 0, 12, 15, 48, 254, 192, 223, 15, 126, 60, 112, 224, 0, 0, 3, 0, 8,	// 82
	60, 56, 248, 193, 240, 7, 195, 63, 12, 227, 48, 140, 199, 48, 156, 195, 240, 7, 135, 31, 0, 60, 0,	// 83
	3, 0, 12, 0, 48, 0, 192, 0, 0, 3, 0, 252, 255, 240, 255, 195, 255, 15, 3, 0, 12, 0, 48, 0, 192, 0, 0, 3, 0, 0,	// 84
	255, 7, 252, 127, 240, 255, 1, 0, 14, 0, 48, 0, 192, 0, 0, 3, 0, 12, 0, 56, 252, 127, 240, 255, 193, 255, 1,	// 85
	1, 0, 28, 0, 240, 3, 192, 63, 0, 252, 7, 128, 255, 0, 240, 3, 0, 14, 0, 62, 0, 63, 128, 31, 128, 15, 0, 15, 0, 4, 0, 0,	// 86
	1, 0, 252, 0, 240, 63, 128, 255, 15, 224, 63, 0, 240, 0, 254, 131, 255, 0, 63, 0, 252, 15, 224, 255, 3, 248, 15, 0, 60, 0, 255, 192, 63, 192, 15, 0, 3, 0, 0,	// 87
	0, 32, 12, 192, 240, 192, 195, 143, 3, 254, 7, 224, 7, 0, 126, 0, 254, 7, 30, 63, 28, 240, 48, 0, 67, 0, 8,	// 88
	1, 0, 12, 0, 240, 0, 192, 7, 0, 126, 0, 224, 255, 0, 254, 3, 248, 15, 120, 0, 240, 0, 240, 0, 192, 0, 0, 1, 0, 0,	// 89
	3, 48, 12, 240, 48, 224, 195, 224, 15, 195, 55, 204, 207, 176, 15, 195, 31, 12, 31, 48, 60, 192, 48, 0, 3,	// 90
	255, 255, 255, 255, 255, 255, 255, 0, 192, 3, 0, 3,	// 91
	1, 0, 28, 0, 240, 1, 0, 31, 0, 240, 1, 0, 30, 0, 224, 3, 0, 62, 0, 224, 3, 0, 14, 0, 32,	// 92
	3, 0, 15, 0, 252, 255, 255, 255, 255, 255, 255, 3,	// 93
	0, 8, 0, 56, 0, 120, 0, 124, 0, 124, 0, 124, 0, 192, 7, 0, 124, 0, 128, 7, 0, 56, 0, 128, 0,	// 94
	0, 128, 1, 0, 6, 0, 24, 0, 96, 0, 128, 1, 0, 6, 0, 24, 0, 96,	// 95
	1, 0, 4, 0, 48, 0, 128, 0, 0, 2, 0, 0,	// 96
	0, 30, 192, 249, 0, 243, 3, 204, 12, 48, 51, 192, 76, 0, 255, 3, 248, 15, 224, 63, 0, 192, 0,	// 97
	255, 63, 252, 255, 240, 255, 3, 24, 6, 48, 48, 192, 192, 0, 3, 3, 28, 14, 240, 63, 128, 127, 0, 252, 0,	// 98
	128, 7, 128, 127, 0, 254, 1, 28, 14, 48, 48, 192, 192, 0, 3, 3, 28, 12,	// 99
	128, 15, 128, 127, 0, 255, 3, 28, 14, 48, 48, 192, 192, 0, 3, 3, 24, 6, 255, 63, 252, 255, 240, 255, 3,	// 100
	128, 7, 128, 127, 0, 254, 1, 220, 15, 48, 51, 192, 204, 0, 51, 3, 252, 12, 224, 51, 0, 239, 0,	// 101
	48, 0, 248, 255, 240, 255, 195, 255, 15, 51, 0, 204, 0, 48, 3, 192, 0, 0,	// 102
	128, 15, 128, 127, 6, 255, 51, 28, 206, 48, 48, 195, 192, 12, 3, 49, 24, 230, 240, 255, 193, 255, 7, 255, 15,	// 103
	255, 63, 252, 255, 240, 255, 3, 24, 0, 48, 0, 192, 0, 0, 3, 0, 252, 15, 240, 63, 128, 255, 0,	// 104
	243, 63, 204, 255, 48, 255, 3,	// 105
	0, 128, 3, 0, 12, 0, 240, 252, 255, 243, 255, 207, 255, 7,	// 106
	255, 63, 252, 255, 240, 255, 3, 128, 0, 128, 15, 128, 127, 0, 231, 3, 12, 14, 16, 48, 0, 128, 0,	// 107
	255, 63, 252, 255, 240, 255, 3,	// 108
	240, 63, 192, 255, 0, 255, 3, 24, 0, 32, 0, 192, 0, 0, 3, 0, 252, 15, 240, 63, 128, 255, 0, 6, 0, 12, 0, 48, 0, 192, 0, 0, 255, 3, 252, 15, 224, 63, 0,	// 109
	240, 63, 192, 255, 0, 255, 3, 24, 0, 48, 0, 192, 0, 0, 3, 0, 252, 15, 240, 63, 128, 255, 0,	// 110
	128, 7, 128, 127, 0, 254, 1, 28, 14, 48, 48, 192, 192, 0, 3, 3, 28, 14, 224, 31, 128, 127, 0, 120, 0,	// 111
	240, 255, 195, 255, 15, 255, 63, 24, 6, 48, 48, 192, 192, 0, 3, 3, 28, 14, 240, 63, 128, 127, 0, 124, 0,	// 112
	192, 15, 128, 127, 0, 255, 3, 28, 14, 48, 48, 192, 192, 0, 3, 3, 24, 6, 240, 255, 195, 255, 15, 255, 63,	// 113
	240, 63, 192, 255, 0, 255, 3, 56, 0, 112, 0, 192, 1, 0, 7, 0,	// 114
	224, 57, 192, 199, 0, 63, 3, 252, 12, 48, 55, 192, 252, 0, 243, 3, 156, 7, 0, 14, 0,	// 115
	48, 0, 240, 127, 224, 255, 131, 255, 15, 48, 48, 192, 192, 0,	// 116
	240, 31, 192, 255, 0, 255, 3, 0, 12, 0, 48, 0, 192, 0, 128, 1, 252, 15, 240, 63, 192, 255, 0,	// 117
	16, 0, 192, 1, 0, 31, 0, 252, 1, 192, 63, 0, 252, 0, 128, 3, 128, 15, 128, 15, 192, 15, 0, 7, 0, 4, 0,	// 118
	16, 0, 192, 7, 0, 255, 1, 248, 15, 0, 62, 0, 248, 0, 254, 0, 124, 0, 240, 3, 192, 255, 0, 252, 3, 0, 15, 0, 63, 128, 63, 0, 31, 0, 4, 0,	// 119
	16, 32, 192, 192, 0, 207, 3, 252, 7, 224, 7, 0, 127, 0, 254, 3, 60, 15, 48, 56, 64, 128, 0,	// 120
	16, 0, 192, 1, 8, 31, 48, 252, 227, 192, 255, 3, 248, 7, 192, 7, 192, 7, 192, 7, 192, 7, 0, 7, 0, 4, 0,	// 121
	48, 48, 192, 240, 0, 227, 3, 204, 15, 176, 63, 192, 223, 0, 63, 3, 60, 12, 112, 48, 192, 192, 0,	// 122
	0, 3, 120, 140, 247, 255, 255, 63, 255, 99, 56, 3,	// 123
	255, 255, 255, 255, 15,	// 124
	127, 248, 255, 243, 239, 255, 31, 192, 0, 0, 3, 0,	// 125
	0, 7, 0, 31, 0, 12, 0, 48, 0, 192, 1, 0, 14, 0, 112, 0, 128, 1, 0, 6, 0, 31, 0, 28, 0,	// 126
		// 127

    }
};
