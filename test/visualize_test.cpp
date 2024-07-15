#include "visualize.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <fast_distributions/uniform_distribution.hpp>
#include <fast_distributions/sphere_distribution.hpp>
#include <fast_distributions/murmur_generator.hpp>
#include <fast_distributions/cone_distribution.hpp>

template<class F>
auto gen(F&& f,size_t N){
    auto f0=f(0);
    std::vector<decltype(f0)> res(N);
    res[0] = f0;
    for(size_t i = 1; i < N; i++){
        res[i] = f(i);
    }
    return res;
}

template<class F>
void test_distribution(const char* name,F&& d){
    fast_distributions::murmur_generator m(0);

    std::vector<visualize::v3> v=gen(
        [&m,&d](uint64_t){
            return d(m());
        },
        1000
    );
    visualize::scatter(name,v);
}



int main() {
    //test_distribution("uniform cube",fast_distributions::uniform_cube::generate<uint64_t>);
    test_distribution("sphere",fast_distributions::sphere::generate<uint64_t>);

    
    return 0;
}