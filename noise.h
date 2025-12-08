
#ifndef NOISE_H
#define NOISE_H

#include <stdint.h>
#include <rand.h>

#define NOISE_SIZE 1024U

extern const uint8_t perlin_noise0[];
extern const uint8_t perlin_noise1[];
extern const uint8_t perlin_noise2[];
extern const uint8_t perlin_noise3[];
extern const uint8_t perlin_noise4[];
extern const uint8_t perlin_noise5[];
extern const uint8_t perlin_noise6[];
extern const uint8_t voronoi_noise0[];
extern const uint8_t voronoi_noise1[];
extern const uint8_t voronoi_noise2[];
extern const uint8_t voronoi_noise3[];
extern const uint8_t voronoi_noise4[];
extern const uint8_t voronoi_noise5[];
extern const uint8_t voronoi_noise6[];

const uint8_t *get_perlin_noise(uint8_t selector) {
  switch (selector % 4) {
  case 0:
    return perlin_noise0;
  case 1:
    return perlin_noise1;
  case 2:
    return perlin_noise2;
  case 3:
    return perlin_noise3;
  case 4:
    return perlin_noise4;
  case 5:
    return perlin_noise5;
  case 6:
    return perlin_noise6;
  }
}


const uint8_t *get_voronoi_noise(uint8_t selector) {
  switch (selector % 4) {
  case 0:
    return voronoi_noise0;
  case 1:
    return voronoi_noise1;
  case 2:
    return voronoi_noise2;
  case 3:
    return voronoi_noise3;
  case 4:
    return voronoi_noise4;
  case 5:
    return voronoi_noise5;
  case 6:
    return voronoi_noise6;
  }
}

const uint8_t *get_random_noise(uint8_t selector) {
  switch (rand() % 2) {
  case 0:
    return get_perlin_noise(selector);
  case 1:
    return get_voronoi_noise(selector);
  }    
}  

#endif
