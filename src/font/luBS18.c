
// file: font/luBS18.bdf
// font: -B&H-Lucida-Bold-R-Normal-Sans-18-180-75-75-P-120-ISO10646-1

#include <font.h>

const struct Font font_luBS18 = {
    .type       = 1,
    .name	= "luBS18",
    .height	= 17,
    .width	= 19,
    .lineheight = 18,
    .bytescol	= 4,
    .numcol     = 19,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 15, .ncol = 3, .xadj = -14, .pos = 0 }, // 33 [7]
	{ .l0 = 1, .r0 = 10, .ncol = 8, .xadj = -9, .pos = 7 }, // 34 [17]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 24 }, // 35 [22]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -6, .pos = 46 }, // 36 [20]
	{ .l0 = 1, .r0 = 2, .ncol = 16, .xadj = -2, .pos = 66 }, // 37 [34]
	{ .l0 = 1, .r0 = 5, .ncol = 13, .xadj = -4, .pos = 100 }, // 38 [28]
	{ .l0 = 1, .r0 = 15, .ncol = 3, .xadj = -14, .pos = 128 }, // 39 [7]
	{ .l0 = 2, .r0 = 12, .ncol = 5, .xadj = -12, .pos = 135 }, // 40 [11]
	{ .l0 = 0, .r0 = 14, .ncol = 5, .xadj = -12, .pos = 146 }, // 41 [11]
	{ .l0 = 1, .r0 = 10, .ncol = 8, .xadj = -10, .pos = 157 }, // 42 [17]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 174 }, // 43 [22]
	{ .l0 = 1, .r0 = 15, .ncol = 3, .xadj = -14, .pos = 196 }, // 44 [7]
	{ .l0 = 1, .r0 = 14, .ncol = 4, .xadj = -14, .pos = 203 }, // 45 [9]
	{ .l0 = 1, .r0 = 15, .ncol = 3, .xadj = -14, .pos = 212 }, // 46 [7]
	{ .l0 = 0, .r0 = 8, .ncol = 11, .xadj = -8, .pos = 219 }, // 47 [24]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 243 }, // 48 [24]
	{ .l0 = 3, .r0 = 11, .ncol = 5, .xadj = -6, .pos = 267 }, // 49 [11]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -6, .pos = 278 }, // 50 [20]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -6, .pos = 298 }, // 51 [20]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 318 }, // 52 [24]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -6, .pos = 342 }, // 53 [20]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 362 }, // 54 [22]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 384 }, // 55 [22]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 406 }, // 56 [22]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 428 }, // 57 [22]
	{ .l0 = 1, .r0 = 15, .ncol = 3, .xadj = -14, .pos = 450 }, // 58 [7]
	{ .l0 = 1, .r0 = 15, .ncol = 3, .xadj = -14, .pos = 457 }, // 59 [7]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -6, .pos = 464 }, // 60 [22]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 486 }, // 61 [22]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 508 }, // 62 [22]
	{ .l0 = 1, .r0 = 9, .ncol = 9, .xadj = -8, .pos = 530 }, // 63 [20]
	{ .l0 = 1, .r0 = 4, .ncol = 14, .xadj = -3, .pos = 550 }, // 64 [30]
	{ .l0 = 1, .r0 = 5, .ncol = 13, .xadj = -5, .pos = 580 }, // 65 [28]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 608 }, // 66 [22]
	{ .l0 = 1, .r0 = 6, .ncol = 12, .xadj = -5, .pos = 630 }, // 67 [26]
	{ .l0 = 2, .r0 = 5, .ncol = 12, .xadj = -4, .pos = 656 }, // 68 [26]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -7, .pos = 682 }, // 69 [20]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -8, .pos = 702 }, // 70 [20]
	{ .l0 = 1, .r0 = 6, .ncol = 12, .xadj = -5, .pos = 722 }, // 71 [26]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -4, .pos = 748 }, // 72 [24]
	{ .l0 = 2, .r0 = 14, .ncol = 3, .xadj = -12, .pos = 772 }, // 73 [7]
	{ .l0 = 0, .r0 = 12, .ncol = 7, .xadj = -10, .pos = 779 }, // 74 [15]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -5, .pos = 794 }, // 75 [24]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -8, .pos = 818 }, // 76 [20]
	{ .l0 = 2, .r0 = 3, .ncol = 14, .xadj = -1, .pos = 838 }, // 77 [30]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -5, .pos = 868 }, // 78 [22]
	{ .l0 = 1, .r0 = 4, .ncol = 14, .xadj = -3, .pos = 890 }, // 79 [30]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 920 }, // 80 [22]
	{ .l0 = 1, .r0 = 3, .ncol = 15, .xadj = -3, .pos = 942 }, // 81 [32]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 974 }, // 82 [22]
	{ .l0 = 1, .r0 = 9, .ncol = 9, .xadj = -8, .pos = 996 }, // 83 [20]
	{ .l0 = 1, .r0 = 5, .ncol = 13, .xadj = -5, .pos = 1016 }, // 84 [28]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -4, .pos = 1044 }, // 85 [24]
	{ .l0 = 1, .r0 = 5, .ncol = 13, .xadj = -5, .pos = 1068 }, // 86 [28]
	{ .l0 = 1, .r0 = 2, .ncol = 16, .xadj = -1, .pos = 1096 }, // 87 [34]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 1130 }, // 88 [24]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 1154 }, // 89 [24]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -7, .pos = 1178 }, // 90 [22]
	{ .l0 = 2, .r0 = 12, .ncol = 5, .xadj = -12, .pos = 1200 }, // 91 [11]
	{ .l0 = 0, .r0 = 8, .ncol = 11, .xadj = -8, .pos = 1211 }, // 92 [24]
	{ .l0 = 0, .r0 = 14, .ncol = 5, .xadj = -12, .pos = 1235 }, // 93 [11]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -6, .pos = 1246 }, // 94 [20]
	{ .l0 = 1, .r0 = 6, .ncol = 12, .xadj = -5, .pos = 1266 }, // 95 [26]
	{ .l0 = 4, .r0 = 10, .ncol = 5, .xadj = -6, .pos = 1292 }, // 96 [11]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -7, .pos = 1303 }, // 97 [22]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 1325 }, // 98 [22]
	{ .l0 = 1, .r0 = 9, .ncol = 9, .xadj = -8, .pos = 1347 }, // 99 [20]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -6, .pos = 1367 }, // 100 [22]
	{ .l0 = 1, .r0 = 9, .ncol = 9, .xadj = -8, .pos = 1389 }, // 101 [20]
	{ .l0 = 1, .r0 = 11, .ncol = 7, .xadj = -11, .pos = 1409 }, // 102 [15]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -6, .pos = 1424 }, // 103 [22]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -6, .pos = 1446 }, // 104 [20]
	{ .l0 = 2, .r0 = 14, .ncol = 3, .xadj = -12, .pos = 1466 }, // 105 [7]
	{ .l0 = 0, .r0 = 14, .ncol = 5, .xadj = -12, .pos = 1473 }, // 106 [11]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 1484 }, // 107 [22]
	{ .l0 = 2, .r0 = 14, .ncol = 3, .xadj = -12, .pos = 1506 }, // 108 [7]
	{ .l0 = 2, .r0 = 2, .ncol = 15, .xadj = 0, .pos = 1513 }, // 109 [32]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -6, .pos = 1545 }, // 110 [20]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -6, .pos = 1565 }, // 111 [24]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 1589 }, // 112 [22]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -6, .pos = 1611 }, // 113 [22]
	{ .l0 = 2, .r0 = 10, .ncol = 7, .xadj = -10, .pos = 1633 }, // 114 [15]
	{ .l0 = 1, .r0 = 9, .ncol = 9, .xadj = -8, .pos = 1648 }, // 115 [20]
	{ .l0 = 1, .r0 = 11, .ncol = 7, .xadj = -11, .pos = 1668 }, // 116 [15]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -6, .pos = 1683 }, // 117 [20]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -7, .pos = 1703 }, // 118 [22]
	{ .l0 = 1, .r0 = 4, .ncol = 14, .xadj = -3, .pos = 1725 }, // 119 [30]
	{ .l0 = 1, .r0 = 9, .ncol = 9, .xadj = -8, .pos = 1755 }, // 120 [20]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -7, .pos = 1775 }, // 121 [22]
	{ .l0 = 1, .r0 = 9, .ncol = 9, .xadj = -8, .pos = 1797 }, // 122 [20]
	{ .l0 = 2, .r0 = 12, .ncol = 5, .xadj = -12, .pos = 1817 }, // 123 [11]
	{ .l0 = 2, .r0 = 15, .ncol = 2, .xadj = -13, .pos = 1828 }, // 124 [5]
	{ .l0 = 0, .r0 = 14, .ncol = 5, .xadj = -12, .pos = 1833 }, // 125 [11]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -6, .pos = 1844 }, // 126 [22]
	{ .l0 = 19, .r0 = 0, .ncol = 0, .xadj = -19, .pos = 1866 }, // 127 [0]
    },
    .data       = {
	62, 56, 252, 115, 248, 225, 0,	// 33
	31, 0, 30, 0, 12, 0, 0, 0, 0, 0, 224, 3, 192, 3, 128, 1, 0,	// 34
	0, 3, 96, 126, 192, 255, 240, 31, 224, 51, 0, 230, 7, 252, 15, 255, 1, 62, 3, 96, 0, 0,	// 35
	112, 48, 240, 225, 240, 135, 97, 254, 255, 56, 254, 255, 12, 195, 31, 14, 31, 24, 28, 0,	// 36
	56, 0, 248, 64, 184, 195, 48, 198, 224, 206, 128, 207, 0, 206, 0, 192, 0, 192, 0, 192, 28, 192, 124, 192, 220, 193, 24, 195, 112, 135, 192, 7, 0, 7,	// 37
	0, 15, 0, 63, 96, 126, 224, 199, 225, 15, 195, 60, 134, 241, 13, 191, 31, 60, 30, 48, 120, 0, 252, 0, 158, 1, 28, 3,	// 38
	31, 0, 30, 0, 12, 0, 0,	// 39
	224, 7, 240, 63, 248, 255, 121, 128, 55, 0, 12,	// 40
	3, 192, 30, 224, 249, 255, 193, 255, 0, 126, 0,	// 41
	24, 0, 176, 1, 64, 3, 112, 1, 224, 2, 0, 26, 0, 54, 0, 12, 0,	// 42
	128, 1, 0, 3, 0, 6, 0, 12, 128, 255, 1, 255, 3, 96, 0, 192, 0, 128, 1, 0, 3, 0,	// 43
	0, 184, 0, 240, 1, 224, 1,	// 44
	128, 1, 0, 3, 0, 6, 0, 12, 0,	// 45
	0, 56, 0, 112, 0, 224, 0,	// 46
	0, 192, 0, 224, 1, 224, 3, 240, 1, 248, 0, 252, 0, 124, 0, 62, 0, 31, 0, 30, 0, 12, 0, 0,	// 47
	240, 7, 248, 63, 240, 127, 112, 192, 97, 0, 195, 0, 134, 1, 12, 7, 28, 252, 31, 248, 63, 192, 31, 0,	// 48
	12, 0, 24, 0, 240, 255, 240, 255, 225, 255, 3,	// 49
	12, 60, 28, 124, 24, 252, 48, 220, 97, 152, 195, 56, 135, 63, 14, 62, 28, 56, 56, 0,	// 50
	12, 24, 28, 112, 24, 195, 48, 134, 97, 12, 195, 60, 135, 239, 7, 158, 15, 24, 14, 0,	// 51
	128, 3, 128, 7, 128, 13, 128, 25, 128, 49, 128, 97, 128, 255, 15, 255, 31, 254, 63, 0, 6, 0, 12, 0,	// 52
	254, 24, 252, 113, 56, 195, 112, 134, 225, 28, 195, 57, 134, 227, 7, 199, 15, 14, 15, 0,	// 53
	240, 7, 248, 63, 240, 127, 48, 198, 97, 6, 195, 12, 134, 57, 12, 247, 31, 204, 31, 0, 31, 0,	// 54
	14, 0, 28, 112, 56, 248, 112, 248, 225, 120, 192, 57, 128, 59, 0, 63, 0, 62, 0, 60, 0, 0,	// 55
	56, 14, 248, 62, 248, 255, 48, 135, 97, 28, 195, 56, 134, 241, 12, 223, 31, 60, 31, 48, 28, 0,	// 56
	248, 0, 248, 51, 248, 239, 48, 156, 97, 48, 195, 96, 134, 99, 12, 254, 15, 252, 31, 224, 15, 0,	// 57
	112, 56, 224, 112, 192, 225, 0,	// 58
	112, 184, 224, 240, 193, 225, 1,	// 59
	128, 1, 0, 3, 0, 15, 0, 30, 0, 102, 0, 204, 0, 12, 3, 24, 6, 24, 24, 48, 48, 0,	// 60
	96, 6, 192, 12, 128, 25, 0, 51, 0, 102, 0, 204, 0, 152, 1, 48, 3, 96, 6, 192, 12, 0,	// 61
	24, 24, 48, 48, 192, 48, 128, 97, 0, 102, 0, 204, 0, 240, 0, 224, 1, 128, 1, 0, 3, 0,	// 62
	12, 0, 28, 0, 24, 230, 48, 206, 97, 140, 195, 12, 128, 31, 0, 30, 0, 24, 0, 0,	// 63
	224, 7, 240, 63, 112, 96, 96, 158, 97, 126, 195, 70, 134, 69, 12, 203, 27, 246, 55, 236, 40, 24, 16, 96, 48, 192, 63, 0, 62, 0,	// 64
	0, 48, 0, 124, 0, 254, 0, 63, 128, 55, 192, 99, 128, 199, 0, 191, 1, 248, 3, 192, 31, 0, 254, 0, 240, 1, 0, 3,	// 65
	254, 63, 252, 127, 248, 255, 48, 134, 97, 12, 195, 24, 134, 127, 14, 223, 15, 28, 31, 0, 28, 0,	// 66
	224, 3, 240, 31, 240, 127, 224, 240, 224, 128, 195, 0, 135, 1, 12, 3, 24, 6, 48, 12, 96, 56, 96, 96, 192, 0,	// 67
	254, 63, 252, 127, 248, 255, 48, 128, 97, 0, 195, 0, 134, 1, 12, 7, 28, 28, 28, 248, 63, 224, 63, 0, 31, 0,	// 68
	254, 63, 252, 127, 248, 255, 48, 134, 97, 12, 195, 24, 134, 49, 12, 99, 24, 6, 48, 0,	// 69
	254, 63, 252, 127, 248, 255, 48, 6, 96, 12, 192, 24, 128, 49, 0, 99, 0, 6, 0, 0,	// 70
	224, 3, 240, 31, 240, 127, 224, 240, 224, 128, 195, 0, 135, 1, 12, 3, 24, 6, 48, 12, 126, 56, 252, 96, 248, 1,	// 71
	254, 63, 252, 127, 248, 255, 0, 6, 0, 12, 0, 24, 0, 48, 0, 96, 0, 254, 63, 252, 127, 248, 255, 0,	// 72
	254, 63, 252, 127, 248, 255, 0,	// 73
	0, 192, 0, 128, 1, 0, 3, 0, 231, 255, 199, 255, 143, 255, 7,	// 74
	254, 63, 252, 127, 248, 255, 0, 14, 0, 62, 0, 230, 0, 142, 3, 14, 15, 14, 60, 12, 112, 0, 192, 0,	// 75
	254, 63, 252, 127, 248, 255, 0, 128, 1, 0, 3, 0, 6, 0, 12, 0, 24, 0, 48, 0,	// 76
	254, 63, 252, 127, 248, 0, 224, 15, 0, 127, 0, 248, 3, 128, 7, 0, 15, 192, 7, 224, 1, 240, 0, 240, 255, 225, 255, 195, 255, 7,	// 77
	254, 63, 252, 127, 248, 0, 192, 3, 0, 31, 0, 120, 0, 224, 3, 0, 15, 254, 63, 252, 127, 0,	// 78
	224, 3, 240, 31, 240, 127, 224, 224, 224, 128, 195, 0, 134, 1, 12, 3, 24, 6, 48, 28, 112, 112, 112, 224, 255, 128, 255, 0, 124, 0,	// 79
	254, 63, 252, 127, 248, 255, 48, 12, 96, 24, 192, 48, 128, 115, 0, 127, 0, 252, 0, 112, 0, 0,	// 80
	224, 3, 240, 31, 240, 127, 224, 224, 224, 128, 195, 0, 134, 1, 12, 3, 24, 6, 112, 28, 240, 112, 112, 227, 255, 134, 255, 12, 124, 24, 0, 48,	// 81
	254, 63, 252, 127, 248, 255, 48, 12, 96, 24, 192, 112, 128, 243, 3, 191, 31, 124, 60, 112, 112, 0,	// 82
	120, 24, 248, 113, 248, 195, 48, 143, 97, 30, 195, 120, 134, 241, 15, 199, 15, 12, 15, 0,	// 83
	6, 0, 12, 0, 24, 0, 48, 0, 96, 0, 192, 255, 135, 255, 15, 255, 31, 6, 0, 12, 0, 24, 0, 48, 0, 96, 0, 0,	// 84
	254, 7, 252, 63, 248, 127, 0, 192, 1, 0, 3, 0, 6, 0, 12, 0, 28, 254, 31, 252, 63, 248, 31, 0,	// 85
	6, 0, 124, 0, 248, 3, 192, 31, 0, 252, 0, 224, 7, 0, 15, 0, 30, 128, 15, 224, 7, 248, 3, 240, 0, 96, 0, 0,	// 86
	62, 0, 252, 3, 248, 63, 0, 254, 1, 192, 3, 192, 7, 240, 3, 254, 0, 252, 1, 192, 31, 0, 252, 0, 224, 1, 240, 195, 255, 129, 127, 0, 31, 0,	// 87
	6, 48, 60, 120, 248, 120, 224, 63, 0, 63, 0, 120, 0, 248, 3, 188, 15, 60, 62, 28, 112, 24, 192, 0,	// 88
	6, 0, 60, 0, 248, 1, 192, 7, 0, 254, 3, 240, 7, 224, 15, 120, 0, 126, 0, 60, 0, 24, 0, 0,	// 89
	6, 56, 12, 120, 24, 252, 48, 252, 97, 126, 195, 126, 134, 63, 12, 63, 24, 30, 48, 28, 96, 0,	// 90
	255, 255, 254, 255, 253, 255, 27, 0, 54, 0, 12,	// 91
	3, 0, 30, 0, 124, 0, 224, 3, 0, 31, 0, 252, 0, 224, 3, 0, 31, 0, 248, 0, 224, 1, 0, 3,	// 92
	3, 192, 6, 128, 253, 255, 251, 255, 247, 255, 15,	// 93
	0, 14, 0, 31, 128, 7, 192, 3, 192, 1, 0, 15, 0, 120, 0, 192, 7, 0, 14, 0,	// 94
	0, 192, 0, 128, 1, 0, 3, 0, 6, 0, 12, 0, 24, 0, 48, 0, 96, 0, 192, 0, 128, 1, 0, 3, 0, 6,	// 95
	2, 0, 4, 0, 24, 0, 48, 0, 64, 0, 0,	// 96
	0, 28, 192, 124, 192, 249, 128, 153, 1, 51, 3, 102, 2, 252, 7, 240, 31, 192, 63, 0, 96, 0,	// 97
	255, 63, 254, 127, 252, 127, 0, 131, 1, 3, 3, 6, 6, 28, 14, 248, 15, 224, 31, 128, 15, 0,	// 98
	128, 15, 192, 63, 128, 127, 128, 195, 1, 3, 3, 6, 6, 12, 12, 56, 12, 96, 24, 0,	// 99
	128, 15, 192, 63, 128, 255, 128, 195, 1, 3, 3, 6, 6, 8, 134, 255, 15, 255, 63, 254, 127, 0,	// 100
	128, 15, 192, 63, 128, 127, 128, 219, 1, 51, 3, 102, 6, 252, 12, 240, 29, 192, 27, 0,	// 101
	48, 0, 248, 127, 248, 255, 248, 255, 49, 3, 96, 6, 192, 12, 0,	// 102
	128, 7, 192, 159, 129, 127, 135, 227, 12, 131, 25, 6, 51, 8, 99, 248, 255, 240, 255, 224, 255, 0,	// 103
	255, 63, 254, 127, 252, 255, 0, 3, 0, 3, 0, 6, 0, 252, 15, 248, 31, 224, 63, 0,	// 104
	243, 63, 230, 127, 204, 255, 0,	// 105
	0, 128, 1, 0, 207, 255, 155, 255, 55, 255, 3,	// 106
	255, 63, 254, 127, 252, 255, 0, 24, 0, 120, 0, 248, 1, 184, 7, 56, 30, 48, 56, 0, 96, 0,	// 107
	255, 63, 254, 127, 252, 255, 0,	// 108
	240, 63, 224, 127, 128, 255, 0, 3, 0, 3, 0, 6, 0, 252, 15, 248, 31, 224, 63, 192, 0, 192, 0, 128, 1, 0, 255, 3, 254, 7, 248, 15,	// 109
	240, 63, 224, 127, 128, 255, 0, 3, 0, 3, 0, 6, 0, 252, 15, 248, 31, 224, 63, 0,	// 110
	128, 7, 192, 63, 128, 127, 128, 195, 1, 3, 3, 6, 6, 12, 12, 56, 28, 224, 31, 192, 63, 0, 30, 0,	// 111
	240, 255, 225, 255, 131, 255, 7, 131, 0, 3, 3, 6, 6, 28, 14, 248, 15, 224, 31, 128, 15, 0,	// 112
	128, 15, 192, 63, 128, 255, 128, 195, 1, 3, 3, 6, 6, 8, 6, 248, 255, 240, 255, 225, 255, 3,	// 113
	240, 63, 224, 127, 192, 255, 0, 6, 0, 6, 0, 14, 0, 28, 0,	// 114
	192, 24, 192, 115, 192, 199, 128, 157, 1, 51, 3, 230, 6, 140, 15, 56, 15, 96, 12, 0,	// 115
	48, 0, 240, 31, 248, 127, 240, 255, 1, 3, 3, 6, 6, 12, 12,	// 116
	240, 31, 224, 127, 192, 255, 0, 128, 1, 0, 3, 0, 3, 252, 7, 248, 31, 240, 63, 0,	// 117
	240, 0, 224, 7, 192, 63, 0, 252, 1, 224, 3, 128, 7, 192, 3, 224, 3, 240, 1, 224, 0, 0,	// 118
	240, 1, 224, 31, 192, 255, 0, 248, 1, 192, 3, 224, 1, 120, 0, 240, 3, 224, 63, 0, 126, 0, 240, 0, 120, 0, 63, 0, 30, 0,	// 119
	48, 48, 224, 121, 192, 127, 0, 62, 0, 48, 0, 240, 1, 184, 15, 56, 30, 48, 48, 0,	// 120
	112, 0, 224, 3, 192, 31, 6, 252, 14, 224, 31, 128, 15, 192, 7, 224, 3, 240, 1, 224, 0, 0,	// 121
	48, 56, 96, 120, 192, 248, 128, 249, 1, 123, 3, 126, 6, 124, 12, 120, 24, 112, 48, 0,	// 122
	142, 113, 62, 243, 253, 255, 155, 59, 54, 0, 12,	// 123
	255, 255, 254, 255, 1,	// 124
	3, 192, 230, 142, 253, 255, 251, 204, 231, 24, 7,	// 125
	128, 1, 128, 3, 0, 3, 0, 6, 0, 28, 0, 56, 0, 96, 0, 192, 0, 192, 1, 128, 1, 0,	// 126
		// 127

    }
};
