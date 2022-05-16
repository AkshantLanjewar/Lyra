project(LyraEngine)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

add_library(${PROJECT_NAME} src/Polaris.cpp 
                            src/vk/instance.cpp
                            src/vk/device.cpp
                            src/vk/presentation.cpp
                            src/window/window.cpp)
add_library(lyra::engine ALIAS ${PROJECT_NAME})

target_link_directories(${PROJECT_NAME} PUBLIC ../lib/vulkan/lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include ../lib/vulkan/include ../lib/glfw/include)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} vulkan-1.lib)