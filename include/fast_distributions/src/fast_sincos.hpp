#pragma once

#include <cmath>
#include <limits>
#include <type_traits>
#include <utility>
#include <complex>

namespace fast_particles{
    #if defined(FAST_PARTICLES_NAIVE_SINCOS1)
    std::complex<float> cis_2pi(float x){
        return std::exp(std::complex<float>(0, x));
    }
    #elif defined(FAST_PARTICLES_NAIVE_SINCOS2)
    std::complex<float> cis_2pi(float x){
        return std::complex<float>(std::cos(x), std::sin(x));
    }
#else

template<unsigned int P=2>
std::complex<float> cis2pi(uint16_t xrs_u16,float xrs){

    float x=xrs;
    float x2=xrs*xrs;
    /*
    ('sin(x)/x', 1, (array([  6.28149858, -40.259923  ]), 0.0014937272002920683))
    ('sin(x)/x', 2, (array([  6.28317902, -41.33326069,  79.98268939]), 5.564806488248649e-06))
    ('sin(x)/x', 3, (array([  6.28318529, -41.34167099,  81.59425679, -75.4858131 ]), 1.2028823090725497e-08))
    ('sin(x)/x', 4, (array([  6.28318531, -41.34170217,  81.60521197, -76.6987031 ,  41.50246079]), 1.697651151786995e-11))
    ('sin(x)/x', 5, (array([  6.28318531, -41.34170224,  81.6052492 , -76.70583794,  42.05584867, -14.92433044]), 1.6708233460317903e-14))
    ('sin(x)/x', 6, (array([  6.28318531, -41.34170224,  81.60524927, -76.70585931,  42.05862719, -15.08997661,   3.68718996]), 2.951424072579891e-15))
    ('cos(x)', 1, (array([  0.99866653, -18.8825693 ]), 0.0011791217661938954))
    ('cos(x)', 2, (array([  0.99999303, -19.72983732,  63.1364902 ]), 6.171257912528369e-06))
    ('cos(x)', 3, (array([  0.99999998, -19.73916415,  64.92368312, -83.71211213]), 1.7179031617836854e-08))
    ('cos(x)', 4, (array([  1.        , -19.73920868,  64.93932882, -85.44430699,  59.27194444]), 2.965866403511356e-11))
    ('cos(x)', 5, (array([  1.        , -19.7392088 ,  64.93939387, -85.45677184,  60.23873562, -26.07341343]), 3.480933771800264e-14))
    ('cos(x)', 6, (array([  1.        , -19.7392088 ,  64.93939402, -85.45681707,  60.24461659, -26.42401701,   7.80423707]), 2.792489564392842e-16))
    
    static constexpr const float c0=1.0;
    static constexpr const float c1=-19.7392088;
    static constexpr const float c2=64.93939402;
    static constexpr const float c3=-85.45681707;
    static constexpr const float c4=60.24461659;
    static constexpr const float c5=-26.42401701;
    static constexpr const float c6=7.80423707;*/

    
    float y=x2;
    if constexpr(P==1){

    }
    else if constexpr(P==2){
        //1+
        /*
            (c0+c1y)+
            (c2+c3y)y2+
            ((c4+c5y)+
            (c6+c7y)y2)y3
        */
        float q00=c0+c1*y;
        float q01=c2+c3*y;
        float q10=c4+c5*y;
        float q11=c6+c7*y;
        float y2=y*y;
        float r0=q00+q01*y2;
        float r1=q10+q11*y2;
        float y4=y2*y2;
        float q=r0+r1*y4;
    }

    if constexpr(P>=1){
        q+=x;
    }

}






#endif
}