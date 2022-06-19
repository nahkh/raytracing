#include <stdlib.h>
#include <stdio.h>
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

void* scene_thread_calculate_colors(void* params) {
	unsigned int x, y;
	RenderingThreadInput* input = (RenderingThreadInput*) params;
    while(input->state != STOPPING) {
        if (input->state == RENDERING) {
            for (x = input->thread_num; x < input->camera->width; x+=input->thread_count) {
                for (y = 0; y < input->camera->height; ++y) {
                    input->pixels[x + y * input->camera->width] = color_to_color255(render_color(input->scene, camera_get_ray(input->camera, x, y), 5));
                }
            }
            input->state = IDLE;    
        }
    }

	return NULL;
}

RenderingThreadPool* start_rendering_threads(size_t thread_count, Scene* scene, Camera* camera, Color255* pixels) {
    RenderingThreadPool* thread_pool;
    volatile unsigned int i;

    thread_pool = (RenderingThreadPool *) malloc(sizeof(RenderingThreadPool));
    thread_pool->thread_count = thread_count;
    thread_pool->threads = (RenderingThreadInput *) malloc(sizeof(RenderingThreadInput) * thread_count);

    for (i = 0; i < thread_count; ++i) {
        thread_pool->threads[i].camera = camera;
        thread_pool->threads[i].scene = scene;
        thread_pool->threads[i].state = IDLE;
        thread_pool->threads[i].pixels = pixels;
        thread_pool->threads[i].thread_count = thread_count;
        thread_pool->threads[i].thread_num = i;
        if (pthread_create(&(thread_pool->threads[i].thread_id), NULL, scene_thread_calculate_colors, (void*)&(thread_pool->threads[i]))) {
            printf("Could not initialize thread");
            exit(1);
        }
    }

    return thread_pool;
}

void start_render(RenderingThreadPool* thread_pool) {
    size_t i;

    for (i = 0; i < thread_pool->thread_count; ++i) {
        thread_pool->threads[i].state = RENDERING;
    }

    for (i = 0; i < thread_pool->thread_count; ++i) {
        while(thread_pool->threads[i].state == RENDERING);
    }
}

void stop_rendering_threads(RenderingThreadPool* thread_pool) {
    size_t i;

    for (i = 0; i < thread_pool->thread_count; ++i) {
        thread_pool->threads[i].state = STOPPING;
    }
    for (i = 0; i < thread_pool->thread_count; ++i) {
        pthread_join(thread_pool->threads[i].thread_id, NULL);
    }
    free(thread_pool->threads);
    free(thread_pool);
}
