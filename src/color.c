#include "color.h"
#include <math.h>
#include <stdio.h>

int clamp(int a) {
    if (a < 0) {
        return 0;
    }
    if (a > 255) {
        return 255;
    }
    return a;
}

Color color_make_from_rgb(int r, int g, int b) {
    return (Color) {((double) r) / 255.0, ((double) g) / 255.0, ((double) b) / 255.0};
}

Color color_make(double r, double g, double b) {
    return (Color) {r, g, b};
}

Color color_add(const Color a, const Color b) {
    return color_make(a.r + b.r, a.g + b.g, a.b + b.b);
}

Color color_multiply_scalar(const Color a, double alpha) {
    return color_make(a.r * alpha, a.g * alpha, a.b * alpha);
}

Color color_multiply_color(const Color a, const Color b) {
    return color_make(a.r * b.r, a.g * b.g, a.b * b.b);
}

Color color_blend(const Color a, const Color b, double alpha) {
    if (alpha < 0.0) {
        alpha = 0.0;
    }
    if (alpha > 1.0) {
        alpha = 1.0;
    }
    // This is not the correct way of blending between colors. It does not correct for brightness.
    return color_add(color_multiply_scalar(a, 1.0 - alpha), color_multiply_scalar(b, alpha));
}

int color_value_to_255(double value) {
    return clamp((int) (255.0 * (1.0 - exp(-value))));
}

Color255 color_to_color255(const Color color) {
    return (Color255) {color_value_to_255(color.r), color_value_to_255(color.g), color_value_to_255(color.b)};
}

void color_print(const Color color) {
    printf("Color(%.3f, %.3f, %.3f)\n", color.r, color.g, color.b);
}
