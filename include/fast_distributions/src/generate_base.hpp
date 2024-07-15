#pragma once

namespace fast_distributions{
    

    namespace detail{
        template<typename Distribution>
        struct generate_base{
        public:
            template<class ...Args>
            inline static auto generate(Args&&... args) noexcept{
                Distribution dist;
                return dist(std::forward<Args>(args)...);
            }
            
            #ifdef __cpp_static_call_operator
            template<class Args...>
            inline static auto operator()(Args&&... args) noexcept{
                return generate(std::forward<Args>(args)...);
            }
            #endif
        };
    }
}