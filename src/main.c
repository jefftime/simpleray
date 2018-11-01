#include "camera.h"
#include "image.h"
#include "math.h"
#include "scene.h"
#include "vector.h"
#include <darray/darray.h>
#include <stdio.h>
#include <math.h>

typedef unsigned char color[3];

#define WIDTH 432
#define HEIGHT 240

void initialize_scene(struct scene *scene) {
  struct sphere tmp;
  struct ray light;

  dapush(scene->spheres, (vector_set(tmp.pos, 0, 0, -10),
                          tmp.radius = 1.0f,
                          tmp.color[0] = 255,
                          tmp.color[1] = 0,
                          tmp.color[2] = 0,
                          tmp));
  dapush(scene->spheres, (vector_set(tmp.pos, 3, 0, -10),
                          tmp.radius = 1.0f,
                          tmp.color[0] = 255,
                          tmp.color[1] = 255,
                          tmp.color[2] = 255,
                          tmp));
  dapush(scene->spheres, (vector_set(tmp.pos, -3, 0, -10),
                          tmp.radius = 1.0f,
                          tmp.color[0] = 255,
                          tmp.color[1] = 255,
                          tmp.color[2] = 255,
                          tmp));
  dapush(scene->lights, (vector_set(light.pos, 0, 0, 0),
                         vector_set(light.dir, -1, -1, -1),
                         vector_normalize(light.dir, light.dir),
                         light));
}

void trace(struct ray *r,
           struct scene *scene,
           struct camera *camera,
           color result,
           unsigned int depth) {
  unsigned int i;

  result[0] = 128;
  result[1] = 128;
  result[2] = 128;
  for (i = 0; i < dalen(scene->spheres); ++i) {
    float hit;

    if (sphere_ray_intersect(&scene->spheres[i], r, &hit)) {
      unsigned int j;

      for (j = 0; j < dalen(scene->lights); ++j) {
        unsigned int k;
        struct ray second;
        vector second_pos, second_dir, outward, delta;

        vector_set(second_pos,
                   r->pos[0] + (hit * r->dir[0]),
                   r->pos[1] + (hit * r->dir[1]),
                   r->pos[2] + (hit * r->dir[2]));
        vector_negate(second_dir, scene->lights[j].dir);
        ray_init(&second, second_pos, second_dir);
        vector_sub(outward, second.pos, scene->spheres[i].pos);
        vector_normalize(outward, outward);
        vector_mulf(delta, 0.001f, outward);
        vector_add(second.pos, second.pos, delta);
        for (k = 0; k < dalen(scene->spheres); ++k) {
          float shadow_hit;

          if (sphere_ray_intersect(&scene->spheres[i], &second, &shadow_hit)) {
            result[0] = 0;
            result[1] = 0;
            result[2] = 0;
          } else {
            float light_value;

            vector_normalize(outward, outward);
            light_value = (float) fabs(vector_dot(outward, second.dir));
            result[0] = (unsigned char) ((float) scene->spheres[i].color[0] * light_value);
            result[1] = (unsigned char) ((float) scene->spheres[i].color[1] * light_value);
            result[2] = (unsigned char) ((float) scene->spheres[i].color[2] * light_value);
          }
        }
      }
      break;
    }
  }
}

void render(struct image *image,
            struct scene *scene,
            struct camera *camera,
            unsigned int depth) {
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

      dx = (float) tan(camera->fovx / 2.0) * ((float) x - half_w) / half_w;
      dy = (float) tan(camera->fovy / 2.0) * (half_h - (float) y) / half_h;
      vector_set(tmp, dx, dy, 0.0);
      vector_add(r_dir, camera->eye.dir, tmp);
      vector_normalize(r_dir, r_dir);
      ray_init(&r, camera->eye.pos, r_dir);
      trace(&r, scene, camera, result, depth);
      image_set(image, x, y, result[0], result[1], result[2]);
    }
  }
}

void setup_camera(struct camera *out_camera) {
  float fovy, fovx;
  struct ray camera_eye;
  vector camera_pos, camera_dir;

  vector_set(camera_pos, 0, 0, 0);
  vector_set(camera_dir, 0, 0, -1);
  ray_init(&camera_eye, camera_pos, camera_dir);
  fovx = 60.0;
  fovy = (float) HEIGHT * fovx / (float) WIDTH;
  camera_init(out_camera, &camera_eye, to_rads(fovx), to_rads(fovy));
}

int main(int argc, char **argv) {
#define MAX_BOUNCE 10

  struct image image;
  struct scene scene;
  struct camera camera;

  image_init(&image, WIDTH, HEIGHT);
  scene_init(&scene);
  setup_camera(&camera);
  initialize_scene(&scene);
  render(&image, &scene, &camera, MAX_BOUNCE);
  image_write_bmp(&image, "result.bmp");
  image_deinit(&image);
  scene_deinit(&scene);
  ray_deinit(&ray);
  camera_deinit(&camera);
  return 0;

#undef MAX_BOUNCE
}
