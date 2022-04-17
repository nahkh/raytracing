#include "renderer.h"
#include "collision.h"

Color render_color(Scene* scene, Ray ray) {
    Renderable best_hit;
	Collision best_collision;
	Collision collision;
	unsigned int i;

    best_collision = COLLISION_MISS;
   
    for (i = 0; i < scene->renderable_count; ++i) {
        collision = calculate_collision(scene->renderables[i], ray);
        if (collision.hit && (!best_collision.hit || collision.distance < best_collision.distance)) {
            best_collision = collision;
            best_hit = scene->renderables[i];
        }
    }

    if (best_collision.hit) {
        Color color = renderable_get_color_at(best_hit, best_collision.pos);
        double alpha = -vector_dot_product(scene->light_direction, best_collision.normal);
        if (alpha > 0.0) {
            return color_make(alpha * color.r, alpha * color.g, alpha * color.b);
        } else {
            return color_make(0, 0, 0);
        }
    } else {
        return color_make(0, 0, 40);
    }

}