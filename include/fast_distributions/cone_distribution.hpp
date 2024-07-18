#pragma once

#include "src/generate_base.hpp"
#include "generators.hpp"

namespace fast_distributions{
    namespace detail{
        struct cone_base{
            struct param_type{
                float x;
                float y;
            };
        };
    }
}