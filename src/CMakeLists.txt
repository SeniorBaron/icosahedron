
add_executable(icosahedron WIN32
    main.cpp
    animation.cpp
    camera.cpp
    shader.cpp
    utils.cpp
)

target_link_libraries(
    icosahedron PRIVATE
        glad
        glfw
        glm::glm
)

install(TARGETS icosahedron DESTINATION .)
install(
    FILES $<TARGET_PDB_FILE:icosahedron> 
    DESTINATION .
    CONFIGURATIONS Debug
    OPTIONAL
)

install(
    DIRECTORY shaders
    DESTINATION .
)


