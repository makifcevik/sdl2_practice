cmake_minimum_required(VERSION 3.25)

# 1. Project Info
project(sld2_practice VERSION 1.0.0 LANGUAGES CXX)

# 2. Enforce Standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Find Dependencies (Vcpkg handles the paths)
find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2_image CONFIG REQUIRED)

# 4. Enable Testing
enable_testing()

# --- COMPONENT 1: THE MAIN APP ---

add_subdirectory(apps)