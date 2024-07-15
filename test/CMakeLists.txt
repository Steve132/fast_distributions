
add_executable(default_disassembly_test 
    default_disassembly_test.cpp
)
target_link_libraries(default_disassembly_test PRIVATE
    fast_distributions
)

target_generate_disassembly(default_disassembly_test)