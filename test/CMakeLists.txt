

add_subdirectory(deps)

add_executable(visualize_test
    visualize_test.cpp
    visualize.hpp
    visualize.cpp
)

target_link_libraries(visualize_test PRIVATE
    fast_distributions
    CImg
)


add_executable(default_disassembly_test 
    default_disassembly_test.cpp
)
target_link_libraries(default_disassembly_test PRIVATE
    fast_distributions
)

target_generate_disassembly(default_disassembly_test)