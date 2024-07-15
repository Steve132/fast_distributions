
Fast Sphere=

x=u cos(v)
y=u sin(v)
z=sqrt(1-u^2)



Fast Ln

Exploit that x=(1+m)2^(e-127)
then you can do log2(x)=ln(1+m)=log2(x | exponent)+e-127

log2(x) centered at 1.5 from 1 to 2 is 
0.405465 + 0.666667 (x - 1.5) - 0.222222 (x - 1.5)^2 + 0.0987654 (x - 1.5)^3 - 0.0493827 (x - 1.5)^4 + 0.0263374 (x - 1.5)^5 - 0.0146319 (x - 1.5)^6 + 0.00836109 (x - 1.5)^7 - 0.00487731 (x - 1.5)^8 + 0.00289025 (x - 1.5)^9 - 0.00173415 (x - 1.5)^10 + 0.001051 (x - 1.5)^11 - 0.000642279 (x - 1.5)^12 + 0.000395249 (x - 1.5)^13 - 0.000244678 (x - 1.5)^14 + 0.000152244 (x - 1.5)^15 - 0.0000951524 (x - 1.5)^16 + 0.0000597035 (x - 1.5)^17 - 0.0000375911 (x - 1.5)^18 + O((x - 1.5)^19)
(Taylor series)
(converges when abs(x - 1.5)<3/2 ∨ x = 3)

no thats ln.  Scale the whole thing by 1/ln(2)

l_{a}\left(l_{m}\left(x\right)\right)+l_{e}\left(x\right)


if b=f(a)

then

D{f^-1}(b) D{f}(a)=1


//fixed point is a fraction of 2pi 
std::complex<float> cis_2pi(uint16_t xui){
    xui-= uint16_t(1) << (16-3);
    bool o2= xui & (uint16_t(1) << (15));
    bool o1= xui & (uint16_t(1) << (14));

    xui &= (uint16_t(1) << (16-2)-1);
    float x = float(xui) * float(1.0 / 65536.0);
    x-=1.0/8.0;
    float q=x*(2.0f*M_PI-40.0f*x*x);
    float u=sqrtf(1.0f-q*q);
    /*float s0=q*(o2 ? 1 : -1);
    float c0=u*(o2 ? 1 : -1)*(o1 ? 1 : -1);
    
    float s=(o1 ? s0 : c0);
    float c=(o1 ? c0 : s0);
    return std::complex<float>{c,s};*/

    /*float s0=q;
    float c0=(2.0*o1-1.0)*u;
    float s=s0*(o1)+(1.0-o1)*c0;
    float c=c0*(o1)+(1.0-o1)*s0;

    //float s=q*o1+(1.0-o1)*(2.0*o1-1.0)*u;
    
    //float s=q*o1+(1.0-o1)*(2.0*o1-1.0)*u;
    float s=q*o1+(2.0*o1-1.0)*u
            -o1*(2.0*o1-1.0)*u
            q*o1+
            2.0*o1*u-u
            -2.0*o1*o1*u
            +o1*u
        s=-u+q*o1
        +o1*u
    float c=o1(2.0*o1-1.0)u+q-o1*q;
    =2.0*o1*u-o1*u+q+o1*q
    =(q+u)*o1+q
    float s=(q+u)*o1-u;

    VERIFIED:

    s=( (u+q)*o1-u)*(2*o2-1)
    c=( (u-q)*o1+q)*(2*o2-1)

    but we have u+q = sqrt(1-q^2)+q = 1+q-q^2/2+q^3/8+...
    and u-q = sqrt(1-q^2)-q = 1-q-q^2/2-q^3/8+...
    so we can skip the sqrt too.
    especially because w=u-q and v=u+q allows us to compute
    guves us u=(v+w)/2 and q=(v-w)/2
    so with approximations for v and w
    we can say v*o1-u=v*o1-(v+w)/2
    or w*o1+q=w*o1+(v-w)/2
    Also we have w(x)=v(-x)

    So this is a good breakdown into evens and odds.
    v(x)*o1-v(x)/2-v(-x)/2
    v(-x)*o1+v(x)/2-v(-x)/2

    Even odd decomposition: 
    f(x)=fe1(x)+fo1(x^2)
    (multiplicative?)

    v(x)=1+2\ \pi\ x-20x^{2}-40x^{3}+54.5\cdot x^{4}+516.5x^{6}
    (v(x)+v(-x))/2=1-20x^{2}-40x^{3}+

    e(x)*b1+o(x)*b1-e(x)
    e(x)*b1-o(x)*b1+o(x)
    
    s=if(b1) o(x) else -e(x)
    c=if(b1) e(x) else o(x)

    s*=o2
    c*=o2


    if b1 then the even terms cancel and it's just odd,
    else it's just -e(x)
    in the first one.
    in the second one if b1 then the odd terms cancel 
    and it's just e(-x)=e(x) else it's just o(x)
    the taylor series for sin is made up only of odd parts.
    so yeah, the start is cosine
    all the even parts. 1+
    (1-x^2/2)(1-x^2/2)
    1-x^2/2+x^2


}





