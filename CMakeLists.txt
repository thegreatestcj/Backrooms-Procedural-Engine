cmake_minimum_required(VERSION 3.21)

project(BackroomsProceduralEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Enable Qt5 with required modules
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets OpenGL)

# Enable Qt MOC/UIC/RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Include paths
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external
        ${CMAKE_SOURCE_DIR}/external/glad
        ${CMAKE_SOURCE_DIR}/external/imgui
        ${CMAKE_SOURCE_DIR}/external/imgui/backends
        ${CMAKE_SOURCE_DIR}/external/stb
        ${CMAKE_SOURCE_DIR}/gui              # 👈 Qt GUI headers
)

# Engine source files
file(GLOB_RECURSE SRC_FILES
        src/*.cpp
        include/core/*.h
        include/utilities/*.h
)

# GUI source files (Qt)
file(GLOB GUI_FILES
        gui/*.cpp
        gui/*.h
)

# ImGui core
file(GLOB IMGUI_CORE_FILES
        external/imgui/imgui.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imgui_demo.cpp
)

# ImGui backend (still linked in case you want hybrid UI)
set(IMGUI_BACKEND_FILES
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
)

# GLAD & STB
file(GLOB GLAD_FILES external/glad/*.c)
file(GLOB STB_FILES external/stb/*.cpp)

# Combine all sources
set(ALL_SOURCES
        ${SRC_FILES}
        ${GUI_FILES}
        ${IMGUI_CORE_FILES}
        ${IMGUI_BACKEND_FILES}
        ${GLAD_FILES}
        ${STB_FILES}
)

add_executable(${PROJECT_NAME}
        ${ALL_SOURCES}
)

# Set output dir
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/bin/Debug
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
)


# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::OpenGL
        glfw
)

# Debug define
target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:_DEBUG>
)
