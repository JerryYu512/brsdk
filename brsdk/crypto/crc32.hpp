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
 * @file crc32.hpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-07-11
 * 
 * @copyright MIT License
 * 
 */
#pragma once

namespace brsdk {

namespace crypto {

/**
 * @brief 计算crc32
 * 
 * @param crc 上次校验码
 * @param buffer 数据
 * @param size 数据长度
 * @return unsigned int 结果
 */
unsigned int crc32(unsigned int crc, const unsigned char *buffer, unsigned int size);

/// 使用msb计算crc

/**
 * @brief msb初始化
 * 
 */
void crc32_msb_init(void);

/**
 * @brief msb crc32计算
 * 
 * @param crc 上次的crc
 * @param buffer 数据
 * @param size 数据长度
 * @return unsigned int crc32
 */
unsigned int crc32_msb(unsigned int crc, const unsigned char *buffer, unsigned int size);

/// 使用lsb计算crc

/**
 * @brief lsb初始化
 * 
 */
void crc32_lsb_init(void);

/**
 * @brief lsb crc32计算
 * 
 * @param crc 上次的crc
 * @param buffer 数据
 * @param size 数据长度
 * @return unsigned int crc32
 */
unsigned int crc32_lsb(unsigned int crc, const unsigned char *buffer, unsigned int size);

} // namespace crypto
} // namespace brsdk
