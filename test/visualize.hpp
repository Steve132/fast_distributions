#pragma once
#include<array>
#include<cstdlib>
#include<vector>

namespace visualize{

    using v1=float;
    using v2=std::array<float,2>;
    using v3=std::array<float,3>;

    void scatter(const char* name,const std::vector<v2>& points);
    void scatter(const char* name,const std::vector<v3>& points);

    void histogram(const std::vector<float>& values,size_t resolution=100);
}