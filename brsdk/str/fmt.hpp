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
 * @file fmt.hpp
 * @brief
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-07-11
 *
 * @copyright MIT License
 *
 */
#pragma once
#include <inttypes.h>
#include <string.h>
#include <map>
#include <sstream>
#include <string>
#include <assert.h>
#include <vector>

namespace brsdk {

namespace str {

/**
 * @brief 格式化，类似printf
 * 
 */
class Fmt
{
public:
    /**
     * @brief 简单格式化数字
     * 
     * @tparam T 数字类型，需要是算术类型
     * @param fmt 格式
     * @param val 值
     */
    template <typename T>
    Fmt(const char* fmt, T val) {
        static_assert(std::is_arithmetic<T>::value == true, "Must be arithmetic type");

        length_ = snprintf(buf_, sizeof buf_, fmt, val);
        assert(static_cast<size_t>(length_) < sizeof buf_);
    }

    // 获取格式化结果
    const char* data() const { return buf_; }

    // 格式化结果字符串长度
    int length() const { return length_; }

    // printf，结果返回为string
    static std::string format(const char* fmt, ...);

    /// 字符串转bool值
    /// 1,y,Y,on,true,enable,yes
    static bool getboolean(const char* str);
    
    /**
     * @brief 取bool值的字符串
     * 
     * @tparam T 
     * @param v 
     * @return const char* 
     */
    template <typename T>
    static const char* boolean(T v) {
        return v ? "true" : "false";
    }

private:
    char buf_[32];
    int length_;
};

// 实例化
template Fmt::Fmt(const char* fmt, char);

template Fmt::Fmt(const char* fmt, short);
template Fmt::Fmt(const char* fmt, unsigned short);
template Fmt::Fmt(const char* fmt, int);
template Fmt::Fmt(const char* fmt, unsigned int);
template Fmt::Fmt(const char* fmt, long);
template Fmt::Fmt(const char* fmt, unsigned long);
template Fmt::Fmt(const char* fmt, long long);
template Fmt::Fmt(const char* fmt, unsigned long long);

template Fmt::Fmt(const char* fmt, float);
template Fmt::Fmt(const char* fmt, double);

/**
 * @brief 字符串转到值
 * 
 * @param s 字符串
 */
bool to_bool(const char* s);
int32_t to_int32(const char* s);
int64_t to_int64(const char* s);
uint32_t to_uint32(const char* s);
uint64_t to_uint64(const char* s);
double to_double(const char* s);

inline bool to_bool(const std::string& s)     { return to_bool(s.c_str()); }
inline int32_t to_int32(const std::string& s)   { return to_int32(s.c_str()); }
inline int64_t to_int64(const std::string& s)   { return to_int64(s.c_str()); }
inline uint32_t to_uint32(const std::string& s) { return to_uint32(s.c_str()); }
inline uint64_t to_uint64(const std::string& s) { return to_uint64(s.c_str()); }
inline double to_double(const std::string& s) { return to_double(s.c_str()); }

/**
 * @brief 转换数字为国际数字计数单位(k, M, G, T, P, E)
 * 
 * @param n 数字
 * @return std::string 字符串
 */
std::string formatSI(int64_t n);

/**
 * @brief 转换数字为国际电工委员会数字计数单位(Ki, Mi, Gi, Ti, Pi, Ei)
 * 
 * @param n 数字
 * @return std::string 字符串
 */
std::string formatIEC(int64_t n);

}  // namespace str

}  // namespace brsdk
