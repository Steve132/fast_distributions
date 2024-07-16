#pragma once

#include<cstdlib>
#include<bit>
#include<cstdint>
#include<random>

namespace fast_distributions{
    struct murmur_generator{
    private:
        uint64_t seed;
        static constexpr inline uint64_t murmur64(uint64_t h){
            h ^= std::rotr(h,33);
            h *= 0xff51afd7ed558ccdL;
            h += 0x4952E2DB49391E25L;
            h ^= std::rotr(h,33);
            h *= 0xc4ceb9fe1a85ec53L;
            //h ^= std::rotr(h >>> 33;
            return h;
        }
    public:
        constexpr murmur_generator(uint64_t seed):seed(seed){}
        constexpr uint64_t operator()(){
            seed = murmur64(seed);
            return seed;
        }
        static constexpr uint64_t max() noexcept{
            return UINT64_MAX;
        }
        static constexpr uint64_t min() noexcept{
            return 0;
        }
        uint64_t get_state() const noexcept{
            return seed;
        }
        
   };
   using default_random_generator=std::independent_bits_engine<std::minstd_rand,64,uint64_t>;
}