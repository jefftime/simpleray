cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(simpleray VERSION 0.1.0 LANGUAGES C)
add_executable(simpleray
  "src/camera.c"
  "src/image.c"
  "src/main.c"
  "src/math.c"
  "src/ray.c"
  "src/scene.c"
  "src/sphere.c"
  "src/vector.c"
  )
target_link_libraries(simpleray
  "m"
  )
target_compile_options(simpleray
  PRIVATE "-std=c89"
  PRIVATE "-pedantic-errors"
  PRIVATE "-Wall"
  PRIVATE "-Wconversion"
  )
