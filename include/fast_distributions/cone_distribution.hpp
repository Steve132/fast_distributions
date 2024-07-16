#pragma once

#include "src/generate_base.hpp"
#include "generators.hpp"

namespace fast_distributions{
    namespace detail{
        struct cone_base{
            struct params_type{
                
            };
        };
        struct naive_uniform: public uniform_base,
            public detail::generate_base<naive_uniform>
        {
            using param_type=uniform_base::standard_params;
            template<class SEED>
            auto operator()(const SEED& s,const param_type& p=param_type{}) noexcept{
                default_random_generator gen(s);
                std::uniform_real_distribution<float> dist(p.lower,p.upper);
                return dist(gen);
            }
        };
    }
    using uniform=detail::naive_uniform;