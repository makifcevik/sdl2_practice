add_executable(02_artist main.cpp)

target_link_libraries(02_artist PRIVATE
	SDL2::SDL2
	SDL2::SDL2main
)