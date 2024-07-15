#pragma once
#include<cmath>
#include "src/entropy.hpp"
#include "src/murmur_generator.hpp"
#include <random>
#include "src/generate_base.hpp"
namespace fast_distributions{
    namespace {
        struct normal_base{

        struct ninty_nine_percentile{
            float lower,upper;
        };

        struct standard_params{
                float mean=0.0f;
                float std_dev=1.0f;
                constexpr standard_params()=default;
                constexpr standard_params(float m,float s) noexcept:mean(m),std_dev(s){}
                constexpr standard_params(const ninty_nine_percentile& p) noexcept;
        };
        };
    
        struct naive_normal: public normal_base,
            public detail::generate_base<naive_normal>
        {
            using param_type=normal_base::standard_params;
            template<class SEED>
            auto operator()(const SEED& s,const param_type& p=param_type{}) noexcept{
                std::normal_distribution<float> dist(p.mean,p.std_dev);
                murmur_generator gen(s);
                return dist(gen);
            }
        };

        inline constexpr normal_base::standard_params::standard_params(const ninty_nine_percentile& p) noexcept{
                    mean = (p.lower+p.upper)/2.0f;
                        constexpr const float factor=0.2149291864227931368220767205016131624932647215178411455591044964f;
                        //1/(1.8062902\cdot2.575829303548900760978576748603814117306)
                        std_dev = (p.upper-p.lower)*factor;
        }
    }

    using normal=naive_normal;
}