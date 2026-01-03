add_executable(07_bouncing_image main.cpp)
target_link_libraries(07_bouncing_image PRIVATE
	SDL2::SDL2
	SDL2::SDL2main
)

# Copy images directory next to the executable binary
file(COPY "${CMAKE_SOURCE_DIR}/images" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")