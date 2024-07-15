#pragma once
#include <cstdint>

template<unsigned int Bits,class T=uint32_t>
struct ientropy{
    T data;
    static constexpr const unsigned int bits=Bits;
    static constexpr const unsigned int mask=(1<<Bits)-1;

    ientropy():data(0){}
    ientropy(const ientropy&)=default;
    ientropy(ientropy&&)=default;
    ientropy& operator=(const ientropy&)=default;
    ientropy& operator=(ientropy&&)=default;
    
    template<class M>
    operator M() const{
        return static_cast<M>(data);
    }
    template<class M>
    ientropy(const M& d):data(d){}

    template<class M>
    ientropy& operator=(const M& d){
        data=d;
        return *this;
    }
};

/*
template<typename T, unsigned int N>
struct entropy_set: public std::array<,N> {
    
};
*/




