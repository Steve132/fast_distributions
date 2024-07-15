#pragma once

#include "murmur_generator.hpp"
#include "src/generate_base.hpp"
#include<random>

namespace fast_distributions{
    namespace detail{
        struct uniform_base{
            struct standard_params{
                float lower=0.0f;
                float upper=1.0f;
                constexpr standard_params()=default;
                constexpr standard_params(float l,float u) noexcept:lower(l),upper(u){}
            };
        };
        struct naive_uniform: public uniform_base,
            public detail::generate_base<naive_uniform>
        {
            using param_type=uniform_base::standard_params;
            template<class SEED>
            auto operator()(const SEED& s,const param_type& p=param_type{}) noexcept{
                murmur_generator gen(s);
                std::uniform_real_distribution<float> dist(p.lower,p.upper);
                return dist(gen);
            }
        };
    }
    using uniform=detail::naive_uniform;


    template<unsigned int N>
    struct uniform_hyperbox:
            public detail::generate_base<uniform_hyperbox<N>>
    {
        struct param_type{
            std::array<float,N> lower;
            std::array<float,N> upper;
            constexpr param_type(){
                for(unsigned int i=0;i<N;i++){
                    lower[i]=0.0f;
                    upper[i]=1.0f;
                }
            }
            constexpr param_type(const std::array<float,N>& l,const std::array<float,N>& u) noexcept:
                lower(l),
                upper(u)
            {}
        };
        template<class SEED>
        auto operator()(const SEED& s,const param_type& p=param_type{}) noexcept{
            murmur_generator gen(s);
            uniform dist;
            std::array<float,N> res;
            for(unsigned int i=0;i<N;i++){
                res[i]=dist(gen(),detail::uniform_base::standard_params{p.lower[i],p.upper[i]});
            }
            return res;
        }
    };

    using uniform_square=uniform_hyperbox<2>;
    using uniform_cube=uniform_hyperbox<3>;
}