#include "color.h"

int clamp(int a) {
    if (a < 0) {
        return 0;
    }
    if (a > 255) {
        return 255;
    }
    return a;
}

Color color_make(int r, int g, int b) {
    return (Color) {clamp(r), clamp(g), clamp(b)};
}

Color color_add(const Color a, const Color b) {
    return color_make(a.r + b.r, a.g + b.g, a.b + b.b);
}

Color color_multiply(const Color a, double alpha) {
    return color_make(a.r * alpha, a.g * alpha, a.b * alpha);
}

Color color_blend(const Color a, const Color b, double alpha) {
    if (alpha < 0.0) {
        alpha = 0.0;
    }
    if (alpha > 1.0) {
        alpha = 1.0;
    }
    // This is not the correct way of blending between colors. It does not correct for brightness.
    return color_add(color_multiply(a, alpha), color_multiply(b, 1.0 - alpha));
}