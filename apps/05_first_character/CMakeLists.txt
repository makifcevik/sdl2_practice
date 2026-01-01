add_executable(05_first_character main.cpp "color.h")
target_link_libraries(05_first_character PRIVATE
	SDL2::SDL2
	SDL2::SDL2main
)