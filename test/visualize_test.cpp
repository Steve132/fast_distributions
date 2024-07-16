#include "visualize.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <fast_distributions/uniform_distribution.hpp>
#include <fast_distributions/sphere_distribution.hpp>
#include <fast_distributions/generators.hpp>
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
    fast_distributions::default_random_generator m(0);

    std::vector<visualize::v3> v=gen(
        [&m,&d](uint64_t){
            return d(m());
        },
        1000
    );
    visualize::scatter(name,v);
}

std::array<float,3> bloodcone(uint64_t s){
    namespace fd=fast_distributions;

    auto gen_bloodcone=[](auto& seed){
        fd::default_random_generator g(seed);
        using tip=fd::gaussian_hyperball<2>;
        tip::ninety_nine_percentile tip_params{};
        tip_params.radius=.2; //cone max slope 
        auto  xy=tip::generate(g(),tip_params);
        using length=fd::normal;
        length::standard_params p;
        p.mean=1.2;
        p.std_dev=0.05;
        auto z=fd::normal::generate(g(),p);
        return std::array<float,3>{xy[0]*z,xy[1]*z,z};
    };

    //auto entropy=rand(); //or any other method of generating an int.
    auto v=gen_bloodcone(s); 
//v is now an eigen vector3 with mean z 1.2 and a gaussian shotgun distribution with only a 1% chance of a slope with |slope| bigger than .2
    return v;
}
int main() {
    //test_distribution("uniform cube",fast_distributions::uniform_cube::generate<uint64_t>);
    //test_distribution("sphere",fast_distributions::sphere::generate<uint64_t>);
    //test_distribution("ball",fast_distributions::gaussian_ball::generate<uint64_t>);
    test_distribution("bloodcone",bloodcone);
    
    
    return 0;
}