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
 * @file crc16.hpp
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
#include <stddef.h>
#include <string.h>

namespace brsdk {

namespace crypto {

/**
 * @brief 计算crc16
 * 
 * @param s 数据
 * @param n 长度
 * @param crc 前次的crc值，主要用于校验大文件时需要分段
 * @return uint16_t crc16值
 */
uint16_t crc16(const void* s, size_t n, uint16_t crc);

/**
 * @brief 一次性校验少量数据
 * 
 * @param s 数据指针
 * @param n 长度
 * @return uint16_t crc16值
 */
static inline uint16_t crc16(const void* s, size_t n) {
    return crc16(s, n, 0);
}

/**
 * @brief 字符串crc16
 * 
 * @param s 字符串
 * @return uint16_t crc16值
 */
static inline uint16_t crc16(const char* s) {
    return crc16(s, strlen(s));
}

/**
 * @brief 类似字符串string的校验
 * 
 * @tparam S 数据类型
 * @param s 数据
 * @return uint16_t 结果
 */
template<typename S>
inline uint16_t crc16(const S& s) {
    return crc16(s.data(), s.size());
}

} // namespace crypto

} // namespace brsdk
