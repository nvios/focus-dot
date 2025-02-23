#include <Adafruit_GFX.h>

// Org_01
const uint8_t Org_01Bitmaps[] PROGMEM = {
    0xE8, 0xE8, 0xA0, 0x57, 0xD5, 0xF5, 0x00, 0xFD, 0x3E, 0x5F, 0x80, 0x88,
    0x88, 0x88, 0x80, 0xF4, 0xBF, 0x2E, 0x80, 0x80, 0x6A, 0x40, 0x95, 0x80,
    0xAA, 0x80, 0x5D, 0x00, 0xC0, 0xF0, 0x80, 0x08, 0x88, 0x88, 0x00, 0xFC,
    0x63, 0x1F, 0x80, 0xF8, 0xF8, 0x7F, 0x0F, 0x80, 0xF8, 0x7E, 0x1F, 0x80,
    0x8C, 0x7E, 0x10, 0x80, 0xFC, 0x3E, 0x1F, 0x80, 0xFC, 0x3F, 0x1F, 0x80,
    0xF8, 0x42, 0x10, 0x80, 0xFC, 0x7F, 0x1F, 0x80, 0xFC, 0x7E, 0x1F, 0x80,
    0xA0, 0xB0, 0x2A, 0x22, 0xF0, 0xF0, 0x88, 0xA8, 0xF8, 0x4E, 0x02, 0x00,
    0xFD, 0x6F, 0x0F, 0x80, 0xFC, 0x7F, 0x18, 0x80, 0xF4, 0x7D, 0x1F, 0x00,
    0xFC, 0x21, 0x0F, 0x80, 0xF4, 0x63, 0x1F, 0x00, 0xFC, 0x3F, 0x0F, 0x80,
    0xFC, 0x3F, 0x08, 0x00, 0xFC, 0x2F, 0x1F, 0x80, 0x8C, 0x7F, 0x18, 0x80,
    0xF9, 0x08, 0x4F, 0x80, 0x78, 0x85, 0x2F, 0x80, 0x8D, 0xB1, 0x68, 0x80,
    0x84, 0x21, 0x0F, 0x80, 0xFD, 0x6B, 0x5A, 0x80, 0xFC, 0x63, 0x18, 0x80,
    0xFC, 0x63, 0x1F, 0x80, 0xFC, 0x7F, 0x08, 0x00, 0xFC, 0x63, 0x3F, 0x80,
    0xFC, 0x7F, 0x29, 0x00, 0xFC, 0x3E, 0x1F, 0x80, 0xF9, 0x08, 0x42, 0x00,
    0x8C, 0x63, 0x1F, 0x80, 0x8C, 0x62, 0xA2, 0x00, 0xAD, 0x6B, 0x5F, 0x80,
    0x8A, 0x88, 0xA8, 0x80, 0x8C, 0x54, 0x42, 0x00, 0xF8, 0x7F, 0x0F, 0x80,
    0xEA, 0xC0, 0x82, 0x08, 0x20, 0x80, 0xD5, 0xC0, 0x54, 0xF8, 0x80, 0xF1,
    0xFF, 0x8F, 0x99, 0xF0, 0xF8, 0x8F, 0x1F, 0x99, 0xF0, 0xFF, 0x8F, 0x6B,
    0xA4, 0xF9, 0x9F, 0x10, 0x8F, 0x99, 0x90, 0xF0, 0x55, 0xC0, 0x8A, 0xF9,
    0x90, 0xF8, 0xFD, 0x63, 0x10, 0xF9, 0x99, 0xF9, 0x9F, 0xF9, 0x9F, 0x80,
    0xF9, 0x9F, 0x20, 0xF8, 0x88, 0x47, 0x1F, 0x27, 0xC8, 0x42, 0x00, 0x99,
    0x9F, 0x99, 0x97, 0x8C, 0x6B, 0xF0, 0x96, 0x69, 0x99, 0x9F, 0x10, 0x2E,
    0x8F, 0x2B, 0x22, 0xF8, 0x89, 0xA8, 0x0F, 0xE0};

const GFXglyph Org_01Glyphs[] PROGMEM = {
    {0, 0, 0, 4, 0, 1},    // 0x20 ' '
    {1, 1, 5, 2, 0, -4},   // 0x21 '!'
    {2, 3, 1, 4, 0, -4},   // 0x22 '"'
    {3, 5, 5, 6, 0, -4},   // 0x23 '#'
    {7, 5, 5, 6, 0, -4},   // 0x24 '$'
    {11, 5, 5, 6, 0, -4},  // 0x25 '%'
    {15, 5, 5, 6, 0, -4},  // 0x26 '&'
    {19, 1, 1, 2, 0, -4},  // 0x27 '''
    {20, 2, 5, 3, 0, -4},  // 0x28 '('
    {22, 2, 5, 3, 0, -4},  // 0x29 ')'
    {24, 3, 3, 4, 0, -3},  // 0x2A '*'
    {26, 3, 3, 4, 0, -3},  // 0x2B '+'
    {28, 1, 2, 2, 0, 0},   // 0x2C ','
    {29, 4, 1, 5, 0, -2},  // 0x2D '-'
    {30, 1, 1, 2, 0, 0},   // 0x2E '.'
    {31, 5, 5, 6, 0, -4},  // 0x2F '/'
    {35, 5, 5, 6, 0, -4},  // 0x30 '0'
    {39, 1, 5, 2, 0, -4},  // 0x31 '1'
    {40, 5, 5, 6, 0, -4},  // 0x32 '2'
    {44, 5, 5, 6, 0, -4},  // 0x33 '3'
    {48, 5, 5, 6, 0, -4},  // 0x34 '4'
    {52, 5, 5, 6, 0, -4},  // 0x35 '5'
    {56, 5, 5, 6, 0, -4},  // 0x36 '6'
    {60, 5, 5, 6, 0, -4},  // 0x37 '7'
    {64, 5, 5, 6, 0, -4},  // 0x38 '8'
    {68, 5, 5, 6, 0, -4},  // 0x39 '9'
    {72, 1, 4, 2, 0, -3},  // 0x3A ':'
    {73, 1, 4, 2, 0, -3},  // 0x3B ';'
    {74, 3, 5, 4, 0, -4},  // 0x3C '<'
    {76, 4, 3, 5, 0, -3},  // 0x3D '='
    {78, 3, 5, 4, 0, -4},  // 0x3E '>'
    {80, 5, 5, 6, 0, -4},  // 0x3F '?'
    {84, 5, 5, 6, 0, -4},  // 0x40 '@'
    {88, 5, 5, 6, 0, -4},  // 0x41 'A'
    {92, 5, 5, 6, 0, -4},  // 0x42 'B'
    {96, 5, 5, 6, 0, -4},  // 0x43 'C'
    {100, 5, 5, 6, 0, -4}, // 0x44 'D'
    {104, 5, 5, 6, 0, -4}, // 0x45 'E'
    {108, 5, 5, 6, 0, -4}, // 0x46 'F'
    {112, 5, 5, 6, 0, -4}, // 0x47 'G'
    {116, 5, 5, 6, 0, -4}, // 0x48 'H'
    {120, 5, 5, 6, 0, -4}, // 0x49 'I'
    {124, 5, 5, 6, 0, -4}, // 0x4A 'J'
    {128, 5, 5, 6, 0, -4}, // 0x4B 'K'
    {132, 5, 5, 6, 0, -4}, // 0x4C 'L'
    {136, 5, 5, 6, 0, -4}, // 0x4D 'M'
    {140, 5, 5, 6, 0, -4}, // 0x4E 'N'
    {144, 5, 5, 6, 0, -4}, // 0x4F 'O'
    {148, 5, 5, 6, 0, -4}, // 0x50 'P'
    {152, 5, 5, 6, 0, -4}, // 0x51 'Q'
    {156, 5, 5, 6, 0, -4}, // 0x52 'R'
    {160, 5, 5, 6, 0, -4}, // 0x53 'S'
    {164, 5, 5, 6, 0, -4}, // 0x54 'T'
    {168, 5, 5, 6, 0, -4}, // 0x55 'U'
    {172, 5, 5, 6, 0, -4}, // 0x56 'V'
    {176, 5, 5, 6, 0, -4}, // 0x57 'W'
    {180, 5, 5, 6, 0, -4}, // 0x58 'X'
    {184, 5, 5, 6, 0, -4}, // 0x59 'Y'
    {188, 5, 5, 6, 0, -4}, // 0x5A 'Z'
    {192, 2, 5, 3, 0, -4}, // 0x5B '['
    {194, 5, 5, 6, 0, -4}, // 0x5C '\'
    {198, 2, 5, 3, 0, -4}, // 0x5D ']'
    {200, 3, 2, 4, 0, -4}, // 0x5E '^'
    {201, 5, 1, 6, 0, 1},  // 0x5F '_'
    {202, 1, 1, 2, 0, -4}, // 0x60 '`'
    {203, 4, 4, 5, 0, -3}, // 0x61 'a'
    {205, 4, 5, 5, 0, -4}, // 0x62 'b'
    {208, 4, 4, 5, 0, -3}, // 0x63 'c'
    {210, 4, 5, 5, 0, -4}, // 0x64 'd'
    {213, 4, 4, 5, 0, -3}, // 0x65 'e'
    {215, 3, 5, 4, 0, -4}, // 0x66 'f'
    {217, 4, 5, 5, 0, -3}, // 0x67 'g'
    {220, 4, 5, 5, 0, -4}, // 0x68 'h'
    {223, 1, 4, 2, 0, -3}, // 0x69 'i'
    {224, 2, 5, 3, 0, -3}, // 0x6A 'j'
    {226, 4, 5, 5, 0, -4}, // 0x6B 'k'
    {229, 1, 5, 2, 0, -4}, // 0x6C 'l'
    {230, 5, 4, 6, 0, -3}, // 0x6D 'm'
    {233, 4, 4, 5, 0, -3}, // 0x6E 'n'
    {235, 4, 4, 5, 0, -3}, // 0x6F 'o'
    {237, 4, 5, 5, 0, -3}, // 0x70 'p'
    {240, 4, 5, 5, 0, -3}, // 0x71 'q'
    {243, 4, 4, 5, 0, -3}, // 0x72 'r'
    {245, 4, 4, 5, 0, -3}, // 0x73 's'
    {247, 5, 5, 6, 0, -4}, // 0x74 't'
    {251, 4, 4, 5, 0, -3}, // 0x75 'u'
    {253, 4, 4, 5, 0, -3}, // 0x76 'v'
    {255, 5, 4, 6, 0, -3}, // 0x77 'w'
    {258, 4, 4, 5, 0, -3}, // 0x78 'x'
    {260, 4, 5, 5, 0, -3}, // 0x79 'y'
    {263, 4, 4, 5, 0, -3}, // 0x7A 'z'
    {265, 3, 5, 4, 0, -4}, // 0x7B '{'
    {267, 1, 5, 2, 0, -4}, // 0x7C '|'
    {268, 3, 5, 4, 0, -4}, // 0x7D '}'
    {270, 5, 3, 6, 0, -3}  // 0x7E '~'
};

const GFXfont Org_01 PROGMEM = {(uint8_t *)Org_01Bitmaps,
                                (GFXglyph *)Org_01Glyphs, 0x20, 0x7E, 7};

// Num_01
const uint8_t Num_01Bitmaps[] PROGMEM = {
    0xFC, 0x63, 0x1F, 0x80, 0xE1, 0x08, 0x4F, 0x80, 0xF8, 0x7F, 0x0F, 0x80,
    0xF8, 0x7E, 0x1F, 0x80, 0x8C, 0x7E, 0x10, 0x80, 0xFC, 0x3E, 0x1F, 0x80,
    0xFC, 0x3F, 0x1F, 0x80, 0xF8, 0x42, 0x10, 0x80, 0xFC, 0x7F, 0x1F, 0x80,
    0xFC, 0x7E, 0x1F, 0x80, 0xA0};

const GFXglyph Num_01Glyphs[] PROGMEM = {
    {0, 5, 5, 6, 0, -4},  // 0x30 '0'
    {4, 5, 5, 6, 0, -4},  // 0x31 '1'
    {8, 5, 5, 6, 0, -4},  // 0x32 '2'
    {12, 5, 5, 6, 0, -4}, // 0x33 '3'
    {16, 5, 5, 6, 0, -4}, // 0x34 '4'
    {20, 5, 5, 6, 0, -4}, // 0x35 '5'
    {24, 5, 5, 6, 0, -4}, // 0x36 '6'
    {28, 5, 5, 6, 0, -4}, // 0x37 '7'
    {32, 5, 5, 6, 0, -4}, // 0x38 '8'
    {36, 5, 5, 6, 0, -4}, // 0x39 '9'
    {40, 1, 4, 2, 0, -3}  // 0x3A ':'
};

const GFXfont Num_01 PROGMEM = {(uint8_t *)Num_01Bitmaps,
                                (GFXglyph *)Num_01Glyphs, 0x30, 0x3A, 7};

// Aura
const uint8_t AuraBitmaps[] PROGMEM = {
    0x77, 0xFF, 0xF7, 0x00, 0x00, 0x30, 0x00, 0x00, 0xC0, 0x00, 0x07, 0x80,
    0x00, 0x1E, 0x00, 0x00, 0x48, 0x00, 0x03, 0x30, 0x00, 0x0C, 0x40, 0x00,
    0x61, 0x80, 0x01, 0x86, 0x00, 0x04, 0x0C, 0x00, 0x30, 0x30, 0x00, 0x80,
    0x40, 0x06, 0x01, 0x80, 0x18, 0x06, 0x00, 0xC0, 0x0C, 0x03, 0x00, 0x30,
    0x08, 0x00, 0x40, 0x60, 0x01, 0x81, 0x80, 0x06, 0x0C, 0x00, 0x0C, 0x20,
    0x00, 0x10, 0x80, 0x00, 0x66, 0x00, 0x01, 0x90, 0x00, 0x02, 0xC0, 0x00,
    0x0E, 0x00, 0x00, 0x10, 0xFF, 0xE0, 0x40, 0x08, 0x20, 0x02, 0x10, 0x00,
    0x88, 0x00, 0x44, 0x00, 0x22, 0x00, 0x11, 0x00, 0x08, 0x80, 0x08, 0x40,
    0x0C, 0x3F, 0xFC, 0x10, 0x01, 0x88, 0x00, 0x24, 0x00, 0x0A, 0x00, 0x05,
    0x00, 0x01, 0x80, 0x00, 0xC0, 0x00, 0x60, 0x00, 0x30, 0x00, 0x18, 0x00,
    0x0C, 0x00, 0x0A, 0x00, 0x05, 0x00, 0x04, 0x80, 0x0C, 0x7F, 0xF8, 0x00,
    0x00, 0x7F, 0x00, 0x01, 0x80, 0xE0, 0x02, 0x00, 0x38, 0x08, 0x00, 0x0C,
    0x10, 0x00, 0x06, 0x20, 0x00, 0x03, 0x60, 0x00, 0x01, 0x40, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00,
    0x60, 0x00, 0x03, 0x30, 0x00, 0x03, 0x10, 0x00, 0x06, 0x0C, 0x00, 0x0C,
    0x06, 0x00, 0x38, 0x01, 0x80, 0xE0, 0x00, 0x7F, 0x80, 0xFF, 0xE0, 0x08,
    0x03, 0x80, 0x80, 0x06, 0x08, 0x00, 0x30, 0x80, 0x00, 0x88, 0x00, 0x04,
    0x80, 0x00, 0x48, 0x00, 0x02, 0x80, 0x00, 0x28, 0x00, 0x01, 0x80, 0x00,
    0x18, 0x00, 0x01, 0x80, 0x00, 0x18, 0x00, 0x01, 0x80, 0x00, 0x18, 0x00,
    0x01, 0x80, 0x00, 0x18, 0x00, 0x03, 0x80, 0x00, 0x28, 0x00, 0x06, 0x80,
    0x00, 0x48, 0x00, 0x08, 0x80, 0x01, 0x08, 0x00, 0x60, 0x80, 0x18, 0x0F,
    0xFE, 0x00, 0xFF, 0xFC, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00,
    0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0xFF, 0xF8,
    0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00,
    0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00,
    0x80, 0x00, 0x80, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x08, 0x00, 0x20,
    0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x0F,
    0xFF, 0xA0, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02,
    0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00,
    0x80, 0x02, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x07, 0x01, 0xE0, 0x20, 0x01,
    0xC3, 0x00, 0x01, 0x10, 0x00, 0x00, 0x40, 0x00, 0x02, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x40, 0x00, 0x02, 0x00, 0x00, 0x08, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x80, 0x00, 0x02, 0x00, 0x00, 0x08, 0x00, 0x00, 0x60, 0x00, 0x01,
    0x80, 0x00, 0x06, 0x00, 0x00, 0x14, 0x00, 0x00, 0x50, 0x00, 0x01, 0x20,
    0x00, 0x04, 0x40, 0x00, 0x11, 0x80, 0x00, 0x43, 0x00, 0x01, 0x03, 0x00,
    0x0C, 0x07, 0x01, 0xE0, 0x03, 0xFC, 0x00, 0x80, 0x00, 0xC0, 0x00, 0x60,
    0x00, 0x30, 0x00, 0x18, 0x00, 0x0C, 0x00, 0x06, 0x00, 0x03, 0x00, 0x01,
    0x80, 0x00, 0xC0, 0x00, 0x7F, 0xFF, 0xF0, 0x00, 0x18, 0x00, 0x0C, 0x00,
    0x06, 0x00, 0x03, 0x00, 0x01, 0x80, 0x00, 0xC0, 0x00, 0x60, 0x00, 0x30,
    0x00, 0x18, 0x00, 0x0C, 0x00, 0x06, 0x00, 0x03, 0x00, 0x01, 0x80, 0x00,
    0xC0, 0x00, 0x40, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x04, 0x00, 0x10, 0x00,
    0x40, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x01, 0x00, 0x04, 0x00,
    0x10, 0x00, 0x40, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x01, 0x00,
    0x04, 0x00, 0x10, 0x00, 0x60, 0x01, 0x80, 0x06, 0x00, 0x18, 0x00, 0x90,
    0x02, 0x60, 0x10, 0xC1, 0x80, 0xFC, 0x00, 0x80, 0x32, 0x00, 0x88, 0x06,
    0x20, 0x10, 0x80, 0xC2, 0x06, 0x08, 0x18, 0x20, 0xC0, 0x82, 0x02, 0x18,
    0x08, 0xC0, 0x22, 0x00, 0x9C, 0x02, 0x58, 0x0B, 0x20, 0x38, 0xC0, 0xC1,
    0x83, 0x02, 0x08, 0x0C, 0x20, 0x10, 0x80, 0x62, 0x00, 0xC8, 0x01, 0x20,
    0x06, 0x80, 0x0A, 0x00, 0x30, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0xFF, 0xFF, 0x80, 0x00, 0x03,
    0x00, 0x00, 0x0F, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x3E, 0x00, 0x00, 0xF4,
    0x00, 0x01, 0x6C, 0x00, 0x06, 0xC8, 0x00, 0x09, 0x98, 0x00, 0x33, 0x10,
    0x00, 0x66, 0x30, 0x01, 0x8C, 0x60, 0x03, 0x18, 0x40, 0x0C, 0x30, 0xC0,
    0x18, 0x60, 0x80, 0x20, 0xC1, 0x80, 0xC1, 0x81, 0x01, 0x03, 0x03, 0x06,
    0x06, 0x02, 0x08, 0x0C, 0x06, 0x30, 0x18, 0x04, 0x40, 0x30, 0x0D, 0x80,
    0x60, 0x1B, 0x00, 0xC0, 0x1C, 0x01, 0x80, 0x38, 0x03, 0x00, 0x20, 0x04,
    0x80, 0x00, 0x38, 0x00, 0x07, 0x80, 0x00, 0xF8, 0x00, 0x1B, 0x00, 0x03,
    0x30, 0x00, 0x63, 0x00, 0x0C, 0x70, 0x01, 0x86, 0x00, 0x30, 0x60, 0x06,
    0x06, 0x00, 0xC0, 0xC0, 0x18, 0x0C, 0x03, 0x00, 0xC0, 0x60, 0x0C, 0x0C,
    0x01, 0x81, 0x80, 0x18, 0x30, 0x01, 0x86, 0x00, 0x18, 0xC0, 0x03, 0x18,
    0x00, 0x33, 0x00, 0x03, 0x60, 0x00, 0x3C, 0x00, 0x07, 0x80, 0x00, 0x70,
    0x00, 0x04, 0x00, 0x3F, 0x80, 0x00, 0x38, 0x0E, 0x00, 0x08, 0x00, 0x30,
    0x06, 0x00, 0x03, 0x01, 0x00, 0x00, 0x10, 0x40, 0x00, 0x03, 0x08, 0x00,
    0x00, 0x22, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x50, 0x00, 0x00, 0x06,
    0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x18, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x00, 0x60, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x28,
    0x00, 0x00, 0x09, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x43, 0x00, 0x00,
    0x18, 0x30, 0x00, 0x06, 0x03, 0x00, 0x01, 0x80, 0x10, 0x00, 0x60, 0x01,
    0xC0, 0x70, 0x00, 0x07, 0xF0, 0x00, 0xFF, 0xF0, 0x80, 0x0C, 0x80, 0x06,
    0x80, 0x02, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
    0x80, 0x01, 0x80, 0x02, 0x80, 0x06, 0x80, 0x0C, 0xFF, 0xF0, 0x80, 0x00,
    0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00,
    0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x3F,
    0x80, 0x00, 0x0E, 0x03, 0x80, 0x00, 0x80, 0x02, 0x00, 0x18, 0x00, 0x0C,
    0x01, 0x80, 0x00, 0x30, 0x08, 0x00, 0x00, 0xC0, 0x80, 0x00, 0x02, 0x08,
    0x00, 0x00, 0x08, 0x40, 0x00, 0x00, 0x44, 0x00, 0x00, 0x01, 0x20, 0x00,
    0x00, 0x09, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00,
    0x12, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x04, 0x80, 0x00, 0x00, 0x24,
    0x00, 0x00, 0x03, 0x10, 0x00, 0x00, 0x10, 0x80, 0xFC, 0x00, 0x82, 0x38,
    0x18, 0x08, 0x0F, 0x00, 0x20, 0xC0, 0x70, 0x00, 0x8C, 0x01, 0xC0, 0x06,
    0xC0, 0x03, 0x00, 0x1C, 0x00, 0x0E, 0x03, 0xC0, 0x00, 0x0F, 0xE1, 0x00,
    0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x01, 0xE0, 0xFF, 0xF0, 0x80, 0x0C, 0x80, 0x06, 0x80, 0x02, 0x80,
    0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80,
    0x02, 0x80, 0x06, 0x80, 0x0C, 0xFF, 0xF0, 0x80, 0x60, 0x80, 0x20, 0x80,
    0x30, 0x80, 0x10, 0x80, 0x18, 0x80, 0x08, 0x80, 0x0C, 0x80, 0x04, 0x80,
    0x06, 0x80, 0x02, 0x80, 0x03, 0x80, 0x01, 0x07, 0xF8, 0x0C, 0x07, 0x18,
    0x00, 0xD0, 0x00, 0x28, 0x00, 0x04, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00,
    0x40, 0x00, 0x38, 0x00, 0x0E, 0x00, 0x01, 0xE0, 0x00, 0x3C, 0x00, 0x07,
    0x80, 0x00, 0xF0, 0x00, 0x1C, 0x00, 0x03, 0x00, 0x00, 0xC0, 0x00, 0x20,
    0x00, 0x10, 0x00, 0x08, 0x00, 0x06, 0x00, 0x03, 0x80, 0x02, 0x60, 0x03,
    0x1E, 0x06, 0x01, 0xFC, 0x00, 0xFF, 0xFF, 0xE0, 0x08, 0x00, 0x01, 0x00,
    0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x02, 0x00,
    0x00, 0x40, 0x00, 0x08, 0x00, 0x01, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
    0x00, 0x80, 0x00, 0x10, 0x00, 0x02, 0x00, 0x00, 0x40, 0x00, 0x08, 0x00,
    0x01, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00,
    0x02, 0x00, 0x00, 0x40, 0x00, 0x08, 0x00, 0x80, 0x00, 0x60, 0x00, 0x18,
    0x00, 0x06, 0x00, 0x01, 0x80, 0x00, 0x60, 0x00, 0x18, 0x00, 0x06, 0x00,
    0x01, 0x80, 0x00, 0x60, 0x00, 0x18, 0x00, 0x06, 0x00, 0x01, 0x80, 0x00,
    0x60, 0x00, 0x18, 0x00, 0x06, 0x00, 0x01, 0x80, 0x00, 0x60, 0x00, 0x18,
    0x00, 0x06, 0x00, 0x01, 0x80, 0x00, 0x60, 0x00, 0x14, 0x00, 0x09, 0x80,
    0x02, 0x30, 0x01, 0x07, 0x01, 0x80, 0x7F, 0x80, 0xC0, 0x00, 0x07, 0x00,
    0x00, 0x34, 0x00, 0x00, 0x98, 0x00, 0x06, 0x20, 0x00, 0x18, 0xC0, 0x00,
    0x41, 0x00, 0x03, 0x06, 0x00, 0x08, 0x18, 0x00, 0x60, 0x20, 0x01, 0x80,
    0xC0, 0x04, 0x01, 0x00, 0x30, 0x06, 0x00, 0x80, 0x18, 0x06, 0x00, 0x20,
    0x10, 0x00, 0xC0, 0xC0, 0x01, 0x03, 0x00, 0x06, 0x08, 0x00, 0x08, 0x60,
    0x00, 0x31, 0x00, 0x00, 0xCC, 0x00, 0x01, 0x30, 0x00, 0x06, 0x80, 0x00,
    0x0E, 0x00, 0x00, 0x30, 0x00, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0x20, 0x00,
    0x0E, 0x00, 0x01, 0x80, 0x00, 0x50, 0x00, 0x1C, 0x00, 0x06, 0xC0, 0x00,
    0xB0, 0x00, 0x26, 0x00, 0x05, 0x80, 0x03, 0x10, 0x00, 0x64, 0x00, 0x18,
    0xC0, 0x02, 0x30, 0x00, 0x86, 0x00, 0x31, 0x80, 0x0C, 0x10, 0x01, 0x84,
    0x00, 0x60, 0xC0, 0x08, 0x30, 0x02, 0x02, 0x00, 0xC0, 0x80, 0x30, 0x10,
    0x06, 0x04, 0x01, 0x80, 0xC0, 0x20, 0x30, 0x08, 0x02, 0x03, 0x00, 0x80,
    0xC0, 0x18, 0x10, 0x06, 0x04, 0x00, 0xC0, 0x80, 0x30, 0x20, 0x02, 0x0C,
    0x00, 0x83, 0x00, 0x18, 0x40, 0x06, 0x10, 0x00, 0xC6, 0x00, 0x31, 0x80,
    0x02, 0x30, 0x00, 0x8C, 0x00, 0x19, 0x00, 0x06, 0x40, 0x00, 0x58, 0x00,
    0x16, 0x00, 0x02, 0xC0, 0x00, 0xB0, 0x00, 0x1C, 0x00, 0x07, 0x00, 0x00,
    0x60, 0x00, 0x18, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0x0F,
    0x00, 0x00, 0xC8, 0x00, 0x0C, 0x60, 0x00, 0xC1, 0x80, 0x04, 0x06, 0x00,
    0x60, 0x18, 0x06, 0x00, 0xC0, 0x60, 0x03, 0x02, 0x00, 0x0C, 0x30, 0x00,
    0x33, 0x00, 0x00, 0xB0, 0x00, 0x07, 0x00, 0x00, 0x38, 0x00, 0x03, 0x60,
    0x00, 0x33, 0x00, 0x01, 0x8C, 0x00, 0x18, 0x30, 0x01, 0x80, 0xC0, 0x18,
    0x03, 0x00, 0xC0, 0x18, 0x0C, 0x00, 0x60, 0xC0, 0x01, 0x8C, 0x00, 0x06,
    0x40, 0x00, 0x36, 0x00, 0x00, 0xC0, 0x80, 0x00, 0xE0, 0x00, 0xD0, 0x00,
    0x4C, 0x00, 0x62, 0x00, 0x21, 0x80, 0x30, 0x40, 0x10, 0x30, 0x18, 0x08,
    0x08, 0x02, 0x0C, 0x01, 0x8C, 0x00, 0x44, 0x00, 0x36, 0x00, 0x0A, 0x00,
    0x07, 0x00, 0x01, 0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0x20, 0x00, 0x10,
    0x00, 0x08, 0x00, 0x04, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x80, 0x00,
    0x40, 0x00, 0x7F, 0xFF, 0xE0, 0x00, 0x06, 0x00, 0x00, 0xC0, 0x00, 0x18,
    0x00, 0x01, 0x80, 0x00, 0x30, 0x00, 0x06, 0x00, 0x00, 0xC0, 0x00, 0x0C,
    0x00, 0x01, 0x80, 0x00, 0x30, 0x00, 0x03, 0x00, 0x00, 0x60, 0x00, 0x0C,
    0x00, 0x01, 0xC0, 0x00, 0x18, 0x00, 0x03, 0x00, 0x00, 0x60, 0x00, 0x06,
    0x00, 0x00, 0xC0, 0x00, 0x18, 0x00, 0x03, 0x80, 0x00, 0x30, 0x00, 0x06,
    0x00, 0x00, 0xC0, 0x00, 0x0F, 0xFF, 0xFF, 0x01, 0x00, 0x01, 0x00, 0x03,
    0x80, 0x02, 0xC0, 0x02, 0x40, 0x06, 0x60, 0x04, 0x20, 0x0C, 0x30, 0x08,
    0x10, 0x08, 0x10, 0x18, 0x18, 0x10, 0x08, 0x30, 0x0C, 0x20, 0x04, 0x60,
    0x04, 0x40, 0x06, 0x40, 0x02, 0xC0, 0x03, 0x80, 0x01, 0x80, 0x00, 0x40,
    0x00, 0x20, 0x00, 0x10, 0x00, 0x08, 0x00, 0x04, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x80, 0x00, 0x43, 0xF0, 0x26, 0x06, 0x14, 0x00, 0x8C, 0x00,
    0x24, 0x00, 0x0A, 0x00, 0x05, 0x00, 0x01, 0x80, 0x00, 0xC0, 0x00, 0x60,
    0x00, 0x30, 0x00, 0x18, 0x00, 0x0C, 0x00, 0x06, 0x00, 0x05, 0x00, 0x02,
    0xC0, 0x02, 0x70, 0x02, 0x26, 0x06, 0x10, 0xFC, 0x00, 0x03, 0xF0, 0x06,
    0x07, 0x04, 0x00, 0xC4, 0x00, 0x34, 0x00, 0x0A, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0x20, 0x00, 0x10, 0x00, 0x08, 0x00,
    0x02, 0x00, 0x01, 0x00, 0x02, 0x40, 0x03, 0x10, 0x03, 0x06, 0x06, 0x00,
    0xFC, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0x20, 0x00, 0x10, 0x00,
    0x08, 0x00, 0x04, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x81, 0xF8, 0x43,
    0x03, 0x22, 0x00, 0x72, 0x00, 0x1A, 0x00, 0x05, 0x00, 0x03, 0x00, 0x01,
    0x80, 0x00, 0xC0, 0x00, 0x60, 0x00, 0x30, 0x00, 0x18, 0x00, 0x0C, 0x00,
    0x05, 0x00, 0x02, 0x80, 0x01, 0x20, 0x01, 0x88, 0x01, 0xC3, 0x03, 0x20,
    0x7E, 0x10, 0x03, 0xF0, 0x03, 0x03, 0x01, 0x00, 0x60, 0x80, 0x0C, 0x60,
    0x01, 0x90, 0x00, 0x2C, 0x00, 0x0E, 0x00, 0x03, 0x80, 0x00, 0x7F, 0xFF,
    0xF8, 0x00, 0x02, 0x00, 0x00, 0xC0, 0x00, 0x10, 0x00, 0x06, 0x00, 0x08,
    0x80, 0x06, 0x18, 0x03, 0x03, 0x83, 0x80, 0x3F, 0x80, 0x03, 0xE0, 0x10,
    0x60, 0x80, 0xC4, 0x02, 0x10, 0x00, 0x40, 0x01, 0x00, 0x04, 0x00, 0xFF,
    0xE0, 0x40, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x01, 0x00, 0x04,
    0x00, 0x10, 0x00, 0x40, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x01,
    0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x01, 0x00, 0x00, 0x03, 0xF0, 0x86,
    0x06, 0x44, 0x00, 0xE4, 0x00, 0x34, 0x00, 0x0A, 0x00, 0x06, 0x00, 0x03,
    0x00, 0x01, 0x80, 0x00, 0xC0, 0x00, 0x60, 0x00, 0x30, 0x00, 0x18, 0x00,
    0x0A, 0x00, 0x05, 0x00, 0x02, 0x40, 0x03, 0x10, 0x03, 0x86, 0x07, 0x40,
    0xFE, 0x20, 0x00, 0x10, 0x00, 0x08, 0x00, 0x06, 0x00, 0x04, 0x80, 0x02,
    0x20, 0x02, 0x0C, 0x06, 0x01, 0xFC, 0x00, 0x80, 0x01, 0x00, 0x02, 0x00,
    0x04, 0x00, 0x08, 0x00, 0x10, 0x00, 0x20, 0x00, 0x40, 0x00, 0x80, 0x01,
    0x0F, 0x82, 0x60, 0xC5, 0x00, 0x4C, 0x00, 0x58, 0x00, 0xA0, 0x00, 0xC0,
    0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x18, 0x00, 0x30, 0x00,
    0x60, 0x00, 0xC0, 0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x10,
    0x08, 0x04, 0x92, 0x49, 0x24, 0x92, 0x49, 0x24, 0x90, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x20, 0x82, 0x08, 0x20, 0x82, 0x08, 0x20, 0x82, 0x08, 0x20,
    0x82, 0x08, 0x20, 0x82, 0x08, 0x20, 0x82, 0x08, 0x4E, 0x00, 0x80, 0x02,
    0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00,
    0x80, 0x02, 0x00, 0x68, 0x07, 0x20, 0x30, 0x81, 0x82, 0x0C, 0x08, 0xC0,
    0x27, 0x00, 0xB4, 0x03, 0x98, 0x0C, 0x30, 0x20, 0x40, 0x81, 0x82, 0x03,
    0x08, 0x06, 0x20, 0x18, 0x80, 0x32, 0x00, 0x68, 0x00, 0xA0, 0x03, 0xFF,
    0xFF, 0xFF, 0xF0, 0x8F, 0x81, 0xF0, 0xB0, 0x62, 0x0C, 0xC0, 0x34, 0x02,
    0xC0, 0x1C, 0x02, 0x80, 0x08, 0x01, 0x80, 0x08, 0x01, 0x80, 0x08, 0x01,
    0x80, 0x08, 0x01, 0x80, 0x08, 0x01, 0x80, 0x08, 0x01, 0x80, 0x08, 0x01,
    0x80, 0x08, 0x01, 0x80, 0x08, 0x01, 0x80, 0x08, 0x01, 0x80, 0x08, 0x01,
    0x80, 0x08, 0x01, 0x80, 0x08, 0x01, 0x80, 0x08, 0x01, 0x80, 0x08, 0x01,
    0x87, 0xC1, 0x30, 0x62, 0x80, 0x26, 0x00, 0x2C, 0x00, 0x50, 0x00, 0x60,
    0x00, 0xC0, 0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x18, 0x00,
    0x30, 0x00, 0x60, 0x00, 0xC0, 0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 0x08,
    0x01, 0xF8, 0x01, 0xC0, 0xC0, 0x40, 0x04, 0x10, 0x00, 0x44, 0x00, 0x04,
    0x80, 0x00, 0xA0, 0x00, 0x0C, 0x00, 0x01, 0x80, 0x00, 0x30, 0x00, 0x06,
    0x00, 0x00, 0xC0, 0x00, 0x18, 0x00, 0x02, 0x80, 0x00, 0x90, 0x00, 0x11,
    0x00, 0x04, 0x18, 0x03, 0x01, 0xC1, 0xC0, 0x0F, 0xE0, 0x00, 0x87, 0xE0,
    0x4C, 0x0C, 0x28, 0x01, 0x18, 0x00, 0x48, 0x00, 0x14, 0x00, 0x0A, 0x00,
    0x03, 0x00, 0x01, 0x80, 0x00, 0xC0, 0x00, 0x60, 0x00, 0x30, 0x00, 0x18,
    0x00, 0x0C, 0x00, 0x0A, 0x00, 0x05, 0x80, 0x04, 0xE0, 0x04, 0x5C, 0x0C,
    0x21, 0xF8, 0x10, 0x00, 0x08, 0x00, 0x04, 0x00, 0x02, 0x00, 0x01, 0x00,
    0x00, 0x80, 0x00, 0x40, 0x00, 0x20, 0x00, 0x00, 0x03, 0xF0, 0x86, 0x06,
    0x44, 0x00, 0xE4, 0x00, 0x34, 0x00, 0x0A, 0x00, 0x06, 0x00, 0x03, 0x00,
    0x01, 0x80, 0x00, 0xC0, 0x00, 0x60, 0x00, 0x30, 0x00, 0x18, 0x00, 0x0A,
    0x00, 0x05, 0x00, 0x02, 0x40, 0x03, 0x10, 0x03, 0x86, 0x07, 0x40, 0xFE,
    0x20, 0x00, 0x10, 0x00, 0x08, 0x00, 0x04, 0x00, 0x02, 0x00, 0x01, 0x00,
    0x00, 0x80, 0x00, 0x40, 0x00, 0x20, 0x8F, 0xD2, 0x07, 0x80, 0x60, 0x0C,
    0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01,
    0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x00, 0x1F, 0xC1, 0x03,
    0x90, 0x05, 0x00, 0x08, 0x00, 0x40, 0x03, 0x00, 0x0E, 0x00, 0x1C, 0x00,
    0x38, 0x00, 0x70, 0x00, 0xE0, 0x01, 0x80, 0x04, 0x00, 0x20, 0x01, 0x80,
    0x0E, 0x00, 0x9C, 0x08, 0x3F, 0x80, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02,
    0x00, 0x08, 0x00, 0x20, 0x0F, 0xFE, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00,
    0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00,
    0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x30, 0x00, 0x40, 0x00, 0xC2,
    0x01, 0xF4, 0x80, 0x03, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x18, 0x00, 0x30,
    0x00, 0x60, 0x00, 0xC0, 0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 0x0C, 0x00,
    0x18, 0x00, 0x30, 0x00, 0x50, 0x01, 0xA0, 0x03, 0x20, 0x0E, 0x30, 0x64,
    0x1F, 0x88, 0x80, 0x01, 0xC0, 0x03, 0x40, 0x02, 0x60, 0x02, 0x20, 0x06,
    0x20, 0x04, 0x30, 0x0C, 0x10, 0x08, 0x18, 0x18, 0x08, 0x10, 0x08, 0x10,
    0x0C, 0x30, 0x04, 0x20, 0x06, 0x60, 0x02, 0x40, 0x03, 0x40, 0x01, 0xC0,
    0x00, 0x80, 0x00, 0x80, 0x80, 0x04, 0x00, 0x78, 0x01, 0x80, 0x09, 0x00,
    0x38, 0x01, 0x20, 0x05, 0x00, 0x66, 0x01, 0xA0, 0x08, 0x40, 0x26, 0x01,
    0x08, 0x04, 0x40, 0x61, 0x81, 0x8C, 0x08, 0x10, 0x21, 0x81, 0x03, 0x0C,
    0x10, 0x60, 0x61, 0x83, 0x08, 0x04, 0x20, 0x23, 0x00, 0xCC, 0x04, 0x60,
    0x19, 0x00, 0xC8, 0x01, 0x20, 0x0B, 0x00, 0x3C, 0x01, 0x40, 0x03, 0x00,
    0x38, 0x00, 0x60, 0x03, 0x00, 0x0C, 0x00, 0x40, 0x00, 0x80, 0x03, 0x80,
    0x0D, 0x80, 0x31, 0x00, 0xC3, 0x01, 0x03, 0x06, 0x03, 0x18, 0x02, 0x60,
    0x02, 0x80, 0x06, 0x00, 0x0E, 0x00, 0x36, 0x00, 0xC4, 0x01, 0x0C, 0x06,
    0x0C, 0x18, 0x0C, 0x60, 0x08, 0x80, 0x1B, 0x00, 0x18, 0x00, 0x20, 0x00,
    0x4C, 0x00, 0x31, 0x00, 0x08, 0x60, 0x02, 0x08, 0x01, 0x82, 0x00, 0x40,
    0xC0, 0x30, 0x10, 0x08, 0x06, 0x06, 0x00, 0x81, 0x80, 0x20, 0x40, 0x0C,
    0x30, 0x01, 0x08, 0x00, 0x66, 0x00, 0x09, 0x00, 0x03, 0x40, 0x00, 0x70,
    0x00, 0x18, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x30, 0x00,
    0x08, 0x02, 0x06, 0x00, 0x43, 0x00, 0x0F, 0x80, 0x00, 0xFF, 0xFC, 0x00,
    0x20, 0x01, 0x80, 0x0C, 0x00, 0x60, 0x01, 0x80, 0x0C, 0x00, 0x60, 0x01,
    0x00, 0x0C, 0x00, 0x60, 0x01, 0x00, 0x0C, 0x00, 0x60, 0x03, 0x00, 0x0C,
    0x00, 0x60, 0x03, 0x00, 0x0F, 0xFF, 0xC0};

const GFXglyph AuraGlyphs[] PROGMEM = {
    {0, 5, 5, 6, 0, -6},         // 0x2E '.'
    {0, 0, 0, 0, 0, 0},          // 0x2F '/'
    {0, 0, 0, 0, 0, 0},          // 0x30 '0'
    {0, 0, 0, 0, 0, 0},          // 0x31 '1'
    {0, 0, 0, 0, 0, 0},          // 0x32 '2'
    {0, 0, 0, 0, 0, 0},          // 0x33 '3'
    {0, 0, 0, 0, 0, 0},          // 0x34 '4'
    {0, 0, 0, 0, 0, 0},          // 0x35 '5'
    {0, 0, 0, 0, 0, 0},          // 0x36 '6'
    {0, 0, 0, 0, 0, 0},          // 0x37 '7'
    {0, 0, 0, 0, 0, 0},          // 0x38 '8'
    {0, 0, 0, 0, 0, 0},          // 0x39 '9'
    {0, 0, 0, 0, 0, 0},          // 0x3A ':'
    {0, 0, 0, 0, 0, 0},          // 0x3B ';'
    {0, 0, 0, 0, 0, 0},          // 0x3C '<'
    {0, 0, 0, 0, 0, 0},          // 0x3D '='
    {0, 0, 0, 0, 0, 0},          // 0x3E '>'
    {0, 0, 0, 0, 0, 0},          // 0x3F '?'
    {0, 0, 0, 0, 0, 0},          // 0x40 '@'
    {4, 22, 26, 23, 0, -27},     // 0x41 'A'
    {76, 17, 26, 19, 0, -27},    // 0x42 'B'
    {132, 24, 27, 27, 0, -27},   // 0x43 'C'
    {213, 20, 26, 21, 0, -27},   // 0x44 'D'
    {278, 16, 26, 17, 0, -27},   // 0x45 'E'
    {330, 14, 26, 16, 0, -27},   // 0x46 'F'
    {376, 22, 27, 24, 0, -27},   // 0x47 'G'
    {451, 17, 26, 19, 0, -27},   // 0x48 'H'
    {507, 1, 26, 3, 0, -27},     // 0x49 'I'
    {511, 14, 27, 10, -6, -27},  // 0x4A 'J'
    {559, 14, 26, 15, 0, -27},   // 0x4B 'K'
    {605, 16, 26, 18, 0, -27},   // 0x4C 'L'
    {657, 23, 26, 25, 0, -27},   // 0x4D 'M'
    {732, 19, 26, 21, 0, -27},   // 0x4E 'N'
    {794, 27, 26, 28, 0, -27},   // 0x4F 'O'
    {882, 16, 26, 18, 0, -27},   // 0x50 'P'
    {934, 29, 31, 29, 0, -27},   // 0x51 'Q'
    {1047, 16, 26, 17, 0, -27},  // 0x52 'R'
    {1099, 17, 27, 19, 1, -27},  // 0x53 'S'
    {1157, 19, 26, 21, 0, -27},  // 0x54 'T'
    {1219, 18, 27, 19, 0, -27},  // 0x55 'U'
    {1280, 22, 26, 23, 0, -27},  // 0x56 'V'
    {1352, 37, 26, 39, 0, -27},  // 0x57 'W'
    {1473, 21, 26, 23, 0, -27},  // 0x58 'X'
    {1542, 17, 26, 19, 1, -27},  // 0x59 'Y'
    {1598, 20, 26, 21, 0, -27},  // 0x5A 'Z'
    {0, 0, 0, 0, 0, 0},          // 0x5B '['
    {0, 0, 0, 0, 0, 0},          // 0x5C '\'
    {0, 0, 0, 0, 0, 0},          // 0x5D ']'
    {0, 0, 0, 0, 0, 0},          // 0x5E '^'
    {0, 0, 0, 0, 0, 0},          // 0x5F '_'
    {0, 0, 0, 0, 0, 0},          // 0x60 '`'
    {1663, 16, 19, 17, 0, -20},  // 0x61 'a'
    {1701, 17, 28, 19, 0, -29},  // 0x62 'b'
    {1761, 17, 19, 19, 0, -20},  // 0x63 'c'
    {1802, 17, 28, 19, 0, -29},  // 0x64 'd'
    {1862, 18, 19, 20, 0, -20},  // 0x65 'e'
    {1905, 14, 27, 16, 1, -28},  // 0x66 'f'
    {1953, 17, 27, 19, 0, -20},  // 0x67 'g'
    {2011, 15, 28, 17, 0, -29},  // 0x68 'h'
    {2064, 3, 23, 4, 0, -24},    // 0x69 'i'
    {2074, 6, 31, 7, 0, -24},    // 0x6A 'j'
    {2098, 14, 28, 15, 0, -29},  // 0x6B 'k'
    {2147, 1, 28, 3, 0, -29},    // 0x6C 'l'
    {2151, 24, 19, 26, 0, -20},  // 0x6D 'm'
    {2208, 15, 19, 17, 0, -20},  // 0x6E 'n'
    {2244, 19, 19, 21, 0, -20},  // 0x6F 'o'
    {2290, 17, 27, 19, 0, -20},  // 0x70 'p'
    {2348, 17, 27, 19, 0, -20},  // 0x71 'q'
    {2406, 11, 19, 12, 0, -20},  // 0x72 'r'
    {2433, 13, 20, 14, 0, -20},  // 0x73 's'
    {2466, 14, 25, 14, 0, -26},  // 0x74 't'
    {2510, 15, 19, 17, 0, -20},  // 0x75 'u'
    {2546, 16, 19, 17, 0, -20},  // 0x76 'v'
    {2584, 27, 19, 28, 0, -20},  // 0x77 'w'
    {2649, 15, 19, 16, 0, -20},  // 0x78 'x'
    {2686, 18, 26, 20, -2, -20}, // 0x79 'y'
    {2745, 14, 19, 15, 0, -20}   // 0x7A 'z'
};

const GFXfont Aura PROGMEM = {
    (uint8_t *)AuraBitmaps,
    (GFXglyph *)AuraGlyphs, 0x2E, 0x7A, 42};