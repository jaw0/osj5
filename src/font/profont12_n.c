
// file: font/profont12.bdf
// font: ProFont12

#include <font.h>

const struct Font font_profont12_n = {
    .type       = 1,
    .name	= "profont12_n",
    .height	= 11,
    .width	= 6,
    .lineheight = 11,
    .bytescol	= 2,
    .numcol     = 6,
    .startchar  = 33,
    .lastchar	= 63,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 3 }, // 34 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 6 }, // 35 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 15 }, // 36 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 28 }, // 37 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 41 }, // 38 [7]
	{ .l0 = 2, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 55 }, // 39 [2]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 57 }, // 40 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 63 }, // 41 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 69 }, // 42 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 77 }, // 43 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 83 }, // 44 [3]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 87 }, // 45 [5]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 91 }, // 46 [3]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 94 }, // 47 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 100 }, // 48 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 112 }, // 49 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 121 }, // 50 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 135 }, // 51 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 148 }, // 52 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 159 }, // 53 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 173 }, // 54 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 185 }, // 55 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 193 }, // 56 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 207 }, // 57 [7]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 219 }, // 58 [3]
	{ .l0 = 1, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 224 }, // 59 [3]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 230 }, // 60 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 238 }, // 61 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 249 }, // 62 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 257 }, // 63 [7]
    },
    .data       = {
	0xe, 0x9, 0x38,	// 33
	0x3, 0x9b, 0x78,	// 34
	0x11, 0x9, 0x3d, 0x39, 0x9, 0x3d, 0x39, 0x9, 0x38,	// 35
	0x12, 0x19, 0x21, 0x11, 0x19, 0x17, 0x3, 0x11, 0x11, 0x19, 0x21, 0x13, 0x20,	// 36
	0x12, 0x1a, 0x19, 0x11, 0x9, 0x2b, 0xb, 0x21, 0x12, 0x11, 0x1b, 0x12, 0x20,	// 37
	0x12, 0xb, 0x21, 0x11, 0x19, 0x19, 0x9, 0xa, 0x9, 0x21, 0x21, 0x49, 0x9, 0x18,	// 38
	0x3, 0x68,	// 39
	0x16, 0x21, 0x31, 0x11, 0x41, 0x40,	// 40
	0x1, 0x41, 0x11, 0x31, 0x26, 0x50,	// 41
	0x11, 0x9, 0x49, 0x45, 0x41, 0x49, 0x9, 0x38,	// 42
	0x29, 0x51, 0x45, 0x41, 0x51, 0x30,	// 43
	0x3a, 0x9, 0x3b, 0x18,	// 44
	0x29, 0x51, 0x51, 0x60,	// 45
	0x3a, 0x4a, 0x20,	// 46
	0x4a, 0x3a, 0x3a, 0x3a, 0x3a, 0x48,	// 47
	0x16, 0x21, 0x19, 0x11, 0x19, 0x11, 0x19, 0x19, 0x9, 0x21, 0x26, 0x20,	// 48
	0x11, 0x29, 0x21, 0x29, 0x1f, 0x1, 0x51, 0x51, 0x18,	// 49
	0x11, 0x22, 0x19, 0x21, 0x9, 0x19, 0x19, 0x11, 0x19, 0x11, 0x19, 0x22, 0x21, 0x18,	// 50
	0x11, 0x21, 0x21, 0x31, 0x19, 0x11, 0x19, 0x19, 0x11, 0x19, 0x22, 0xb, 0x20,	// 51
	0x22, 0x41, 0x9, 0x39, 0x11, 0x11, 0x1f, 0x1, 0x39, 0x11, 0x18,	// 52
	0xc, 0x11, 0x21, 0x11, 0x19, 0x19, 0x11, 0x19, 0x19, 0x11, 0x19, 0x19, 0x1b, 0x20,	// 53
	0x16, 0x21, 0x11, 0x19, 0x19, 0x11, 0x19, 0x19, 0x11, 0x19, 0x3b, 0x20,	// 54
	0x9, 0x51, 0x51, 0x1c, 0x19, 0x11, 0x3b, 0x40,	// 55
	0x12, 0xb, 0x21, 0x11, 0x19, 0x19, 0x11, 0x19, 0x19, 0x11, 0x19, 0x22, 0xb, 0x20,	// 56
	0x13, 0x39, 0x19, 0x11, 0x19, 0x19, 0x11, 0x19, 0x19, 0x11, 0x26, 0x20,	// 57
	0x1a, 0x12, 0x2a, 0x12, 0x20,	// 58
	0x1a, 0x12, 0x9, 0x1a, 0x13, 0x18,	// 59
	0x21, 0x49, 0x9, 0x39, 0x19, 0x29, 0x29, 0x38,	// 60
	0x19, 0x9, 0x41, 0x9, 0x41, 0x9, 0x41, 0x9, 0x41, 0x9, 0x30,	// 61
	0x9, 0x29, 0x29, 0x19, 0x39, 0x9, 0x49, 0x50,	// 62
	0x11, 0x49, 0x51, 0x21, 0x9, 0x19, 0x19, 0x3b, 0x38,	// 63

    }
};
