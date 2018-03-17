#include "camera.h"
#include "image.h"
#include "math.h"
#include "scene.h"
#include "vector.h"
#include <stdio.h>
#include <math.h>

typedef unsigned char color[3];

#define WIDTH 432
#define HEIGHT 240

void initialize_scene(struct scene *scene) {
  struct sphere tmp;

  vector_set(tmp.pos, 0.0, 0.0, -10.0);
  tmp.radius = 1.0;
  scene_add(scene, &tmp);
  vector_set(tmp.pos, 3.0, 0.0, -10.0);
  tmp.radius = 1.0;
  scene_add(scene, &tmp);
  vector_set(tmp.pos, -3.0, 0.0, -10.0);
  tmp.radius = 1.0;
  scene_add(scene, &tmp);
}

void trace(struct ray *r,
           struct scene *scene,
           struct camera *camera,
           color result) {
  unsigned int i;

  result[0] = 128;
  result[1] = 128;
  result[2] = 128;
  for (i = 0; i < scene->n_spheres; ++i) {
    float hit;

    if (sphere_ray_intersect(&scene->spheres[i], r, &hit)) {
      unsigned int j;

      result[0] = 0;
      result[1] = 255;
      result[2] = 0;
      for (j = 0; j < scene->n_lights; ++j) {
        unsigned int k;
        struct ray second;
        vector second_pos, second_dir, outward, delta;

        vector_set(second_pos,
                   r->pos[0] + (r->dir[0] * hit),
                   r->pos[1] + (r->dir[1] * hit),
                   r->pos[2] + (r->dir[2] * hit));
        vector_set(second_dir,
                   -scene->lights[j].dir[0],
                   -scene->lights[j].dir[1],
                   -scene->lights[j].dir[2]);
        ray_init(&second, second_pos, second_dir);
        vector_set(outward,
                   second.pos[0] - scene->spheres[i].pos[0],
                   second.pos[1] - scene->spheres[i].pos[1],
                   second.pos[2] - scene->spheres[i].pos[2]);
        vector_normalize(outward);
        vector_set(delta,
                   outward[0] * 0.001f,
                   outward[1] * 0.001f,
                   outward[2] * 0.001f);
        vector_set(second.pos,
                   second.pos[0] + delta[0],
                   second.pos[1] + delta[1],
                   second.pos[2] + delta[2]);
        for (k = 0; k < scene->n_spheres; ++k) {
          float shadow_hit;
          if (sphere_ray_intersect(&scene->spheres[k], r, &shadow_hit)) {
            result[0] = 0;
            result[1] = 0;
            result[2] = 0;
          } else {
            result[0] = 255;
            result[1] = 255;
            result[2] = 255;
          }
        }
      }
    }
  }
}

void render(struct image *image, struct scene *scene, struct camera *camera) {
  unsigned int y;

  for (y = 0; y < HEIGHT; ++y) {
    unsigned int x;

    for (x = 0; x < WIDTH; ++x) {
      float half_w = (float) WIDTH / 2.0f;
      float half_h = (float) HEIGHT / 2.0f;
      float dx, dy;
      struct ray r;
      vector tmp, r_dir;
      color result;

      dx = (float) tan(camera->fovx / 2.0) * (float) (x - half_w) / half_w;
      dy = (float) tan(camera->fovy / 2.0) * (float) (half_h - y) / half_h;
      vector_set(tmp, dx, dy, 0.0);
      vector_add(r_dir, camera->eye.dir, tmp);
      vector_normalize(r_dir);
      ray_init(&r, camera->eye.pos, r_dir);
      trace(&r, scene, camera, result);
      image_set(image, x, y, result[0], result[1], result[2]);
    }
  }
}

int main(int argc, char **argv) {
  float fovx, fovy;
  struct image image;
  struct scene scene;
  struct camera camera;
  struct ray camera_eye;
  vector camera_pos, camera_dir;

  image_init(&image, WIDTH, HEIGHT);
  scene_init(&scene);
  vector_set(camera_pos, 0, 0, 0);
  vector_set(camera_dir, 0, 0, -1);
  ray_init(&camera_eye, camera_pos, camera_dir);
  fovx = 60.0;
  fovy = (float) HEIGHT * fovx / (float) WIDTH;
  camera_init(&camera, &camera_eye, to_rads(fovx), to_rads(fovy));
  initialize_scene(&scene);
  render(&image, &scene, &camera);
  image_write_ppm(&image, "something.ppm");
  image_deinit(&image);
  scene_deinit(&scene);
  ray_deinit(&ray);
  camera_deinit(&camera);
  return 0;
}
