#include "ray.h"

Ray ray_make(Vector* pos, Vector* dir) {
    return (Ray) {*pos, *dir};
}