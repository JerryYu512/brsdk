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
 * @file brsdk.hpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-07-11
 * 
 * @copyright MIT License
 * 
 */

/**
 * @mainpage aru基础库
 * <table>
 * <tr><th>Project <td>ars
 * <tr><th>Author  <td>wotsen
 * <tr><th>Email   <td>astralrovers@outlook.com
 * </table>
 * @section 介绍
 * 一个C++基础库，包含时间、文件、网络、线程、协程、加密、宏、锁等基础功能，帮助更方便地构建应用程序。
 * 
 * @section 支持的模块
 * -# 宏定义
 * -# 日志
 * -# 时间
 * -# 文件
 * 
 * @section 简单使用
 * 编译如下：
 * @code
 * g++ demo.cpp -o demo -laru -lssl -lcrypto -lglog -lpthread -lc
 * @endcode
 * 
 * @section 更新记录
 * <table>
 * <tr><th>Date       <th>Version   <th>Author <th>Email <th>Description </tr>
 * <tr><td>2021/04/21 <td>1.0.0     <td>wotsen <td>astralrovers@outlook.com <td>initialize </tr>
 * -# 新建工程;
 * -# 由原来的arsdk库改造而来，更加规范开发;
 * -# 增加编译方式；\n
 *      支持blade-build
 * </tr>
 * </table>
 */
#pragma once
#include <stdint.h>

namespace brsdk {

#define BRSDK_MODULE_TABLE(XX) \
    XX(SDK_CRYPTO, "brsdk-crypto") \
    XX(SDK_MEMORY_SLAB, "brsdk-memory-slab")

/**
 * @brief 获取版本号
 * 
 * @return int 1.0.0 ==> 0x1 00 00
 */
int version(void);

/**
 * @brief 版本号，字符串形式
 * 
 * @return const char* 
 */
const char *version_string(void);

/**
 * @brief 构建版本
 * 
 * @return uint64_t 年月日时分秒
 */
uint64_t version_build(void);

/**
 * @brief 编译时间
 * 
 * @return const char* 
 */
const char *build_time(void);

/**
 * @brief 获取版本模式，debug, realease
 * 
 * @return const char* 
 */
const char *version_mode(void);

/**
 * @brief 是否是debug版本
 * 
 * @return true 是
 * @return false 否
 */
bool debug_version(void);

/**
 * @brief 获取logo
 * 
 * @return const char* 
 */
const char* brsdk_logo(void);

/**
 * @brief 编译时所在系统架构
 * 
 * @return const char* 
 */
const char *compile_arch(void);

/**
 * @brief 编译时所在平台
 * 
 * @return const char* 
 */
const char *compile_plat(void);

/**
 * @brief 使用的处理器
 * 
 * @return const char* 
 */
const char *compile_processor(void);

/**
 * @brief 平台版本
 * 
 * @return const char* 
 */
const char *compile_plat_version(void);

/**
 * @brief 系统
 * 
 * @return const char* 
 */
const char *compile_os(void);

/**
 * @brief 编译器
 * 
 * @return const char* 
 */
const char *compiler_tool(void);

/**
 * @brief 编译用户
 * 
 * @return const char* 
 */
const char *compile_author(void);

/**
 * @brief 作者
 * 
 * @return const char* 
 */
const char *lib_author(void);

} // namespace brsdk
