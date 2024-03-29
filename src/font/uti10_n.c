
// file: font/uti10.bdf
// font: -Adobe-Utopia-Regular-I-Normal--10-100-75-75-P-55-ISO10646-1

#include <font.h>

const struct Font font_uti10_n = {
    .type       = 1,
    .name	= "uti10_n",
    .height	= 10,
    .width	= 8,
    .lineheight = 10,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -6, .pos = 0 }, // 33 [3]
	{ .l0 = 2, .r0 = 3, .ncol = 3, .xadj = -3, .pos = 4 }, // 34 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 7 }, // 35 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = -2, .pos = 16 }, // 36 [8]
	{ .l0 = 2, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 27 }, // 37 [8]
	{ .l0 = 1, .r0 = 0, .ncol = 7, .xadj = 0, .pos = 41 }, // 38 [9]
	{ .l0 = 2, .r0 = 5, .ncol = 1, .xadj = -5, .pos = 57 }, // 39 [2]
	{ .l0 = 2, .r0 = 3, .ncol = 3, .xadj = -4, .pos = 59 }, // 40 [4]
	{ .l0 = 1, .r0 = 4, .ncol = 3, .xadj = -4, .pos = 64 }, // 41 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 69 }, // 42 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -2, .pos = 77 }, // 43 [7]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -5, .pos = 83 }, // 44 [3]
	{ .l0 = 1, .r0 = 4, .ncol = 3, .xadj = -4, .pos = 86 }, // 45 [4]
	{ .l0 = 1, .r0 = 6, .ncol = 1, .xadj = -5, .pos = 90 }, // 46 [2]
	{ .l0 = 1, .r0 = 4, .ncol = 3, .xadj = -4, .pos = 92 }, // 47 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 96 }, // 48 [7]
	{ .l0 = 2, .r0 = 3, .ncol = 3, .xadj = -3, .pos = 105 }, // 49 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 111 }, // 50 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 123 }, // 51 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 133 }, // 52 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 144 }, // 53 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 154 }, // 54 [7]
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = -3, .pos = 164 }, // 55 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 172 }, // 56 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -3, .pos = 182 }, // 57 [7]
	{ .l0 = 1, .r0 = 5, .ncol = 2, .xadj = -5, .pos = 192 }, // 58 [3]
	{ .l0 = 0, .r0 = 5, .ncol = 3, .xadj = -5, .pos = 195 }, // 59 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -2, .pos = 199 }, // 60 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -2, .pos = 208 }, // 61 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = -2, .pos = 219 }, // 62 [7]
	{ .l0 = 2, .r0 = 3, .ncol = 3, .xadj = -3, .pos = 228 }, // 63 [4]
    },
    .data       = {
	0x22, 0x9, 0x1b, 0x50,	// 33
	0xb, 0x8b, 0x40,	// 34
	0x19, 0xb, 0x2b, 0x2b, 0xb, 0x2b, 0x2b, 0x9, 0x50,	// 35
	0x31, 0x2a, 0x1a, 0x11, 0x14, 0x1c, 0x11, 0x12, 0x1a, 0x29, 0x58,	// 36
	0x13, 0x31, 0x11, 0x11, 0x1b, 0xa, 0x29, 0x9, 0x3a, 0xb, 0x19, 0x11, 0x11, 0x30,	// 37
	0x2a, 0x29, 0x9, 0x11, 0x19, 0x9, 0x19, 0x19, 0x11, 0x11, 0x22, 0xa, 0x49, 0x3a, 0x9, 0x20,	// 38
	0xb, 0x60,	// 39
	0x25, 0x1a, 0x29, 0x9, 0x50,	// 40
	0x49, 0x9, 0x2a, 0x1d, 0x28,	// 41
	0x11, 0x9, 0x41, 0x3d, 0x39, 0x41, 0x9, 0x58,	// 42
	0x29, 0x49, 0x3d, 0x39, 0x49, 0x50,	// 43
	0x49, 0x3a, 0x28,	// 44
	0x29, 0x49, 0x49, 0x30,	// 45
	0x39, 0x40,	// 46
	0x32, 0x2b, 0x2a, 0x48,	// 47
	0x23, 0x2a, 0x19, 0x19, 0x29, 0x19, 0x1a, 0x2b, 0x58,	// 48
	0x39, 0x19, 0x14, 0x1b, 0x19, 0x20,	// 49
	0x39, 0x21, 0x1a, 0x19, 0x19, 0x9, 0x19, 0x11, 0x11, 0x22, 0x19, 0x40,	// 50
	0x31, 0x29, 0x21, 0x19, 0x11, 0x11, 0x19, 0x13, 0x2a, 0x60,	// 51
	0x22, 0x39, 0x9, 0x9, 0x21, 0x13, 0x19, 0xb, 0x9, 0x39, 0x50,	// 52
	0x31, 0x23, 0x19, 0x19, 0x9, 0x19, 0x19, 0x13, 0x21, 0x70,	// 53
	0x23, 0x2a, 0x19, 0x19, 0x9, 0x19, 0x19, 0x13, 0x29, 0x68,	// 54
	0xa, 0x1a, 0x19, 0x19, 0x29, 0xa, 0x32, 0x38,	// 55
	0x2a, 0x2b, 0x11, 0x19, 0x11, 0x11, 0x19, 0x13, 0x2a, 0x60,	// 56
	0x31, 0x2b, 0x11, 0x19, 0x19, 0x9, 0x19, 0x1a, 0x2b, 0x58,	// 57
	0x39, 0x29, 0x50,	// 58
	0x49, 0x3a, 0x21, 0x40,	// 59
	0x29, 0x49, 0x41, 0x9, 0x39, 0x9, 0x31, 0x19, 0x40,	// 60
	0x21, 0x9, 0x39, 0x9, 0x39, 0x9, 0x39, 0x9, 0x39, 0x9, 0x48,	// 61
	0x19, 0x19, 0x31, 0x9, 0x39, 0x9, 0x41, 0x49, 0x50,	// 62
	0x11, 0x11, 0x9, 0x19, 0x11, 0x33, 0x40,	// 63

    }
};
