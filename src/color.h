#ifndef _color_h_
#define _color_h_


struct Color {
    double r;
    double g;
    double b;
};

typedef struct Color Color;

struct Color255 {
    int r;
    int g;
    int b;
};

typedef struct Color255 Color255;

Color color_make(double, double, double);

Color color_make_from_rgb(int, int, int);

Color color_add(const Color, const Color);

Color color_multiply_scalar(const Color, const double);

Color color_multiply_color(const Color, const Color);

Color color_blend(const Color, const Color, double alpha);

Color255 color_to_color255(const Color);

void color_print(const Color);

#endif