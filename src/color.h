#ifndef _color_h_
#define _color_h_


struct Color {
    int r;
    int g;
    int b;
};

typedef struct Color Color;

Color color_make(int, int, int);

Color color_blend(const Color, const Color, double alpha);

#endif