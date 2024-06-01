cmake_minimum_required(VERSION 3.5)
project(camera_test)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
  add_link_options("-Wl,-z,relro,-z,now,-z,defs")
endif()

# run with "ASAN_OPTIONS=fast_unwind_on_malloc=0" to print stack with more details
# ASAN_OPTIONS=alloc_dealloc_mismatch=0:new_delete_type_mismatch=0:fast_unwind_on_malloc=0 <exec>
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -fsanitize=address \
    -fsanitize=bool \
    -fsanitize=bounds \
    -fsanitize=enum \
    -fsanitize=float-cast-overflow \
    -fsanitize=float-divide-by-zero \
    -fsanitize=nonnull-attribute \
    -fsanitize=returns-nonnull-attribute \
    -fsanitize=signed-integer-overflow \
    -fsanitize=undefined \
    -fsanitize=vla-bound \
    -fno-sanitize=alignment \
    -fsanitize=leak \
    -fsanitize=object-size \
")

find_package(PkgConfig REQUIRED)

pkg_check_modules(libcamera REQUIRED libcamera)

add_executable(camera_test CameraNode.cpp)

target_include_directories(camera_test PUBLIC ${libcamera_INCLUDE_DIRS})
target_link_libraries(camera_test ${libcamera_LINK_LIBRARIES})

install(TARGETS camera_test DESTINATION bin)
