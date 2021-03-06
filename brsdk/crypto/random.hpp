/**
 * MIT License
 *
 * Copyright © 2021 <wotsen>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the “Software”), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * @file random.hpp
 * @brief
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-07-11
 *
 * @copyright MIT License
 *
 */

#pragma once

#include <stdint.h>
#include <random>   // std::default_random_engine, std::uniform_int_distribution
#include <utility>  // std::forward

namespace brsdk {
namespace crypto {

/**
 * @brief leveldb中的随机数实现
 *
 */
class Random {
public:
    Random() : Random(1u) {}

    explicit Random(uint32_t seed) : _seed(seed & 0x7fffffffu) {
        if (_seed == 0 || _seed == 2147483647L) _seed = 1;
    }

    uint32_t next() {
        static const uint32_t M = 2147483647L;  // 2^31-1
        static const uint64_t A = 16385;        // 2^14+1

        // Computing _seed * A % M.
        uint64_t p = _seed * A;
        _seed = static_cast<uint32_t>((p >> 31) + (p & M));
        if (_seed > M) _seed -= M;

        return _seed;
    }

private:
    uint32_t _seed; // 随机种子
};

////////////////////////////////////////////////////////////////
/// Simple way of generating random numbers
////////////////////////////////////////////////////////////////

/// 使用标准库来实现简单的随机数
template <class Engine = std::default_random_engine,
          class Distribution = std::uniform_int_distribution<>>
class DefRandom : public Distribution {
    using base_t = Distribution;

public:
    using engine_type = Engine;
    using distribution_type = Distribution;
    using result_type = typename distribution_type::result_type;
    using param_type = typename distribution_type::param_type;

private:
    engine_type engine_;

public:
    template <typename... T>
    DefRandom(T&&... args) : base_t(std::forward<T>(args)...), engine_(std::random_device{}()) {}

    result_type operator()(void) { return base_t::operator()(engine_); }

    result_type operator()(const param_type& parm) { return base_t::operator()(engine_, parm); }
};

}  // namespace crypto
}  // namespace brsdk
