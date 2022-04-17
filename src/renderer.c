#include "renderer.h"
#include "collision.h"

Vector vector_reflect(Vector direction, Vector normal) {
    return vector_add(direction, vector_scale(normal, vector_dot_product(direction, normal) * -2.0));
}

Ray calculate_reflection(Vector collision_point, Vector original_dir, Vector normal) {
    return ray_make(collision_point, vector_reflect(original_dir, normal));
}

Color render_color(Scene* scene, Ray ray, int reflections) {
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
            color = color_make(alpha * color.r, alpha * color.g, alpha * color.b);
        } else {
            color = color_make(0, 0, 0);
        }
        if (best_hit.reflectivity > 0.0 && reflections > 0) {
            Ray reflected_ray = calculate_reflection(best_collision.pos, ray.dir, best_collision.normal);
            Color reflected_color = render_color(scene, reflected_ray, reflections - 1);
            color = color_blend(color, reflected_color, best_hit.reflectivity);
        }
        return color;
    } else {
        return color_make(0, 0, 40);
    }
}
