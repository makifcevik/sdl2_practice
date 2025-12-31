add_executable(01_skeleton main.cpp)

target_link_libraries(01_skeleton PRIVATE 
    SDL2::SDL2 
    SDL2::SDL2main      
)