#pragma once

#include<cmath>
#include "normal_distribution.hpp"
#include<cstdlib>
#include<cstdint>
#include<array>
#include "src/generate_base.hpp"

namespace fast_distributions{
    namespace detail{


        template<unsigned int N>
        struct hyperball_base{

            struct ninety_nine_percentile{

                std::array<float,N> center={};
                float radius=1.0f;
            };
            struct param_type{
                std::array<float,N> center={};
                float std_dev=1.0f;
                constexpr param_type()=default;
                constexpr param_type(float s,const std::array<float,N>& ar={}) noexcept:
                    center(ar),
                    std_dev(s)
                {}

                constexpr param_type(const ninety_nine_percentile& p) noexcept{
                    normal_base::standard_params params(
                        normal_base::ninty_nine_percentile{-p.radius,p.radius});
                    std_dev=params.std_dev;
                    center=p.center;
                }
            };
        };

        template<unsigned int D>
        struct gaussian_hyperball: 
            public hyperball_base<D>,
            public detail::generate_base<gaussian_hyperball<D>>{
        private:
            using normal_distribution=fast_distributions::normal;
        public:
            using param_type=std::array<normal_distribution::param_type,D>;
            template<class SEED>
            auto operator()(const SEED& s,const param_type& p={}) noexcept{
                std::array<float,D> res;
                normal_distribution dist;
                murmur_generator gen(s);
                for(unsigned int i=0;i<D;i++){
                    res[i]=dist(gen(),p[i]);
                }
                return res;
            }
        };

        template<unsigned int N>
        struct hypersphere_base{
            struct param_type{
                std::array<float,N> center={};
                float radius=1.0f;
            };
        };

        template<unsigned int N>
        struct gaussian_hypersphere:
            public hypersphere_base<N>,
            public detail::generate_base<gaussian_hypersphere<N>>{
        private:
            using hyperball_distribution=gaussian_hyperball<N>;
        public:
            using param_type=typename hypersphere_base<N>::param_type;
            template<class SEED>
            auto operator()(const SEED& s,const param_type& p={}) noexcept{
                hyperball_distribution dist;
                std::array<float,N> res;
                float sum=0.0f;
                typename hyperball_distribution::param_type pa;
                res=dist(s,pa);
                for(unsigned int i=0;i<N;i++){
                    sum+=res[i]*res[i];
                }
                sum=std::sqrt(sum);
                for(unsigned int i=0;i<N;i++){
                    res[i]=p.radius*res[i]/sum+p.center[i];
                }
                return res;
            }
        };
    }

    template<unsigned int N>
    using gaussian_hyperball=detail::gaussian_hyperball<N>;

    using gaussian_ball=gaussian_hyperball<3>;
    using gaussian_circle=gaussian_hyperball<2>;

    template<unsigned int N>
    using hypersphere=detail::gaussian_hypersphere<N>;

    using sphere=detail::gaussian_hypersphere<3>;
    using circle=detail::gaussian_hypersphere<2>;
}