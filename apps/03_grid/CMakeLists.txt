add_executable(03_grid main.cpp)

target_link_libraries(03_grid PRIVATE
	SDL2::SDL2
	SDL2::SDL2main
)