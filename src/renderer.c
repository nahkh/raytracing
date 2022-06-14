#include "renderer.h"
#include "collision.h"

Vector vector_reflect(Vector* direction, Vector* normal) {
    Vector temp = vector_scale(normal, vector_dot_product(direction, normal) * -2.0);

    return vector_add(direction, &temp);
}

Ray calculate_reflection(Vector* collision_point, Vector* original_dir, Vector* normal) {
    Vector temp = vector_reflect(original_dir, normal);

    return ray_make(collision_point, &temp);
}

int calculate_hit(Scene *scene, Ray ray) {
    unsigned int i;
    Collision collision;

    for (i = 0; i < scene->renderable_count; ++i) {
        collision = calculate_collision(scene->renderables[i], ray);
        if (collision.hit) {
            return 1;
        }
    }
    return 0;
}

Color render_color(Scene* scene, Ray ray, int reflections) {
    Renderable best_hit;
	Collision best_collision;
	Collision collision;
	unsigned int i;
    Ray ray_to_light;
    double alpha;
    Vector direction_to_light;

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
        Color light_color = color_make(0, 0, 0);

        for (i = 0; i < scene->light_source_count; ++i) {
            if (scene->light_sources[i].has_direction) {
                direction_to_light = get_direction_to(scene->light_sources[i], best_collision.pos);
                ray_to_light = ray_make(&(best_collision.pos), &direction_to_light);
                if (!calculate_hit(scene, ray_to_light)) {
                    alpha = vector_dot_product(&(ray_to_light.dir), &(best_collision.normal));
                    if (alpha > 0.0) {
                        light_color = color_add(light_color, color_multiply_scalar(scene->light_sources[i].color, alpha));
                    }
                }
            } else {
                // omnidirectional light
                light_color = color_add(light_color, scene->light_sources[i].color);
            }
        }
        color = color_multiply_color(color, light_color);
        if (best_hit.reflectivity > 0.0 && reflections > 0) {
            Ray reflected_ray = calculate_reflection(&(best_collision.pos), &(ray.dir), &(best_collision.normal));
            Color reflected_color = render_color(scene, reflected_ray, reflections - 1);
            color = color_blend(color, reflected_color, best_hit.reflectivity);
        }
        return color;
    } else {
        return color_make(0, 0, 40);
    }
}


