cmake_minimum_required(VERSION 3.25)
project(RT_OneWeekend)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xpreprocessor -fopenmp -lomp -Wunused-command-line-argument")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES arm64)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

#find_package(OpenMP REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(spdlog REQUIRED)

add_executable(RT_OneWeekend main.cpp Ray.cpp Ray.h Hittable.h Sphere.cpp Sphere.h Hittable_List.cpp Hittable_List.h Utility.h Camera.cpp
        Interval.cpp
        Interval.h
        Camera.cpp
        Camera.h
        Material.cpp
        Material.h
        Timer.cpp
        Timer.h
        Image_Render.h
        Image_Render.cpp
        BVH.cpp
        BVH.h
        AABB.cpp
        AABB.h
        Texture.cpp
        Texture.h
)

target_link_libraries(RT_OneWeekend Eigen3::Eigen spdlog::spdlog)
