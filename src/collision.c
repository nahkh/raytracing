#include "collision.h"

#include <math.h>

const Collision COLLISION_MISS = (Collision){0};

Vector calculate_hit_from_ray(Ray ray, double distance) {
  Vector temp = vector_scale(&(ray.dir), distance);
  return vector_add(&(ray.pos), &temp);
}

Collision collision_make(Vector hit, Vector normal, double distance) {
  return (Collision){1, distance, hit, normal};
}

Collision calculate_collision_plane(RenderablePlane plane, Ray ray) {
  float direction_normal;
  float t;

  direction_normal = vector_dot_product(&(ray.dir), &(plane.normal));
  if (direction_normal == 0.0) {
    return COLLISION_MISS;
  }
  t = (plane.distance_to_origin -
       vector_dot_product(&(ray.pos), &(plane.normal))) /
      direction_normal;
  if (t < MIN_COLLISION_DISTANCE) {
    return COLLISION_MISS;
  }

  return collision_make(calculate_hit_from_ray(ray, t), plane.normal, t);
}

Collision calculate_collision_sphere(RenderableSphere sphere, Ray ray) {
  Vector ray_to_sphere, hit_position, temp;
  double t;
  double d;
  double dt, t1, t2;

  ray_to_sphere = vector_subtract(&(sphere.position), &(ray.pos));
  t = vector_dot_product(&ray_to_sphere, &(ray.dir));
  temp = vector_scale(&(ray.dir), t);
  temp = vector_add(&(ray.pos), &temp);
  temp = vector_subtract(&temp, &(sphere.position));
  d = vector_length(&temp);
  if (d > sphere.radius) {
    return COLLISION_MISS;
  }

  dt = sqrt(sphere.radius * sphere.radius - d * d);
  t1 = t - dt;
  t2 = t + dt;
  if (t1 > MIN_COLLISION_DISTANCE) {
    hit_position = calculate_hit_from_ray(ray, t1);
    temp = vector_subtract(&(hit_position), &(sphere.position));
    return collision_make(hit_position, vector_normalize(&temp), t1);
  }
  if (t2 > MIN_COLLISION_DISTANCE) {
    hit_position = calculate_hit_from_ray(ray, t2);
    temp = vector_subtract(&(hit_position), &(sphere.position));
    return collision_make(hit_position, vector_normalize(&temp), t2);
  }

  return COLLISION_MISS;
}

Collision calculate_collision(Renderable renderable, Ray ray) {
  switch (renderable.type) {
    case RENDERABLE_PLANE:
      return calculate_collision_plane(renderable.as_plane, ray);
    case RENDERABLE_SPHERE:
      return calculate_collision_sphere(renderable.as_sphere, ray);
    default:
      // TODO Handle errors better
      return COLLISION_MISS;
  }
}