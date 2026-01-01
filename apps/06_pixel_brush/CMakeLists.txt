add_executable(06_pixel_brush main.cpp "main.h")
target_link_libraries(06_pixel_brush PRIVATE
	SDL2::SDL2
	SDL2::SDL2main
)