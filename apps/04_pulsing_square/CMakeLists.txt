add_executable(04_pulsing_square main.cpp)

target_link_libraries(04_pulsing_square PRIVATE
	SDL2::SDL2
	SDL2::SDL2main
)