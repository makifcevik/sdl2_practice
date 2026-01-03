add_executable(08_delta_time main.cpp)
target_link_libraries(08_delta_time PRIVATE
	SDL2::SDL2
	SDL2::SDL2main
	SDL2_image::SDL2_image
)

# Copy images directory next to the executable binary
file(COPY "${CMAKE_SOURCE_DIR}/images" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")