cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
project(simpleray VERSION 0.1.0 LANGUAGES C)
add_subdirectory("lib")
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
add_dependencies(simpleray darray)
target_include_directories(simpleray
  PRIVATE "${CMAKE_SOURCE_DIR}/lib/darray/include"
  )
target_link_libraries(simpleray darray)
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries(simpleray
    "m"
    )
  target_compile_options(simpleray
    PRIVATE "-std=c89"
    PRIVATE "-pedantic-errors"
    PRIVATE "-Wall"
    PRIVATE "-Wconversion"
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(COMPILE_FLAGS
    CMAKE_C_FLAGS
    CMAKE_C_FLAGS_DEBUG
    CMAKE_C_FLAGS_RELEASE
    )
  foreach(flag ${COMPILE_FLAGS})
    string(REPLACE "/MDd" "" ${flag} "${${flag}}")
    string(REPLACE "/MD" "" ${flag} "${${flag}}")
  endforeach()
  target_compile_definitions(simpleray
    PRIVATE _CRT_SECURE_NO_WARNINGS
    )
  target_compile_options(simpleray
    PRIVATE /MTd
    )
endif()
