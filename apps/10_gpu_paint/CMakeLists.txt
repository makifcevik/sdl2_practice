add_executable(10_gpu_paint main.cpp)
target_link_libraries(10_gpu_paint PRIVATE
	SDL2::SDL2
	SDL2::SDL2main
)