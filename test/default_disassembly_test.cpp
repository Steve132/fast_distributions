
#include<iostream>
#include<cstdlib>
#include<vector>

#include <fast_distributions/sphere_distribution.hpp>

template<class F>
auto gen(F&& f,size_t N){
    auto f0=f();
    std::vector<decltype(f0)> res(N);
    res[0] = f0;
    for(size_t i = 1; i < N; i++){
        res[i] = f();
    }
    return res;
}


int main(){
    std::size_t N=1000;
    auto data = gen(
        [](){
            return fast_distributions::sphere::generate(302);
        },
        N
    );
    for(size_t i=0;i<N;i++){
        std::cout<<
        data[i][0] << "," << data[i][1] << "," << data[i][2] 
        <<std::endl;
    }
    return 0;
}