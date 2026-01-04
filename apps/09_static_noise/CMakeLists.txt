add_executable(09_static_noise main.cpp)
target_link_libraries(09_static_noise PRIVATE
	SDL2::SDL2
	SDL2::SDL2main
)