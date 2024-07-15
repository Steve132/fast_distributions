
set(FD_DIR "${PROJECT_SOURCE_DIR}/include/fast_distributions")

add_library(fast_distributions
    INTERFACE
    ${FD_DIR}/src/fast_math.hpp
    ${FD_DIR}/src/entropy.hpp
    ${FD_DIR}/src/fast_sincos.hpp
    ${FD_DIR}/src/generate_base.hpp
    ${FD_DIR}/murmur_generator.hpp
    
    ${FD_DIR}/normal_distribution.hpp
    ${FD_DIR}/sphere_distribution.hpp
    ${FD_DIR}/uniform_distribution.hpp
    ${FD_DIR}/cone_distribution.hpp
)
    
target_compile_features(fast_distributions INTERFACE cxx_std_20)
target_include_directories(fast_distributions INTERFACE ${PROJECT_SOURCE_DIR}/include)

if(NOT MSVC)
target_compile_options(fast_distributions INTERFACE 
    -march=native -O3 -Wall -Wextra -Wpedantic 
    #-Werror
    )
endif()