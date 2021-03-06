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
 * @file bounde_blocking_queue.h
 * @brief
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-04
 *
 * @copyright MIT License
 *
 */
#pragma once
#include "circular_buffer.h"
#include "brsdk/lock/condition.hpp"
#include "brsdk/lock/mutex.hpp"

namespace brsdk {

namespace ds {

/**
 * @brief 固定长度的阻塞队列
 * 
 * @tparam T 队列类型
 * @tparam ssize 队列最大容量
 */
template <typename T, size_t ssize=512>
class BoundedBlockingQueue : noncopyable {
public:
    explicit BoundedBlockingQueue()
        : mutex_(), notEmpty_(mutex_), notFull_(mutex_) {}

    // 插入队列
    void put(T& x) {
        MutexLockGuard lock(mutex_);
        while (queue_.full()) {
            notFull_.wait();
        }
        assert(!queue_.full());
        queue_.push_back(x);
        notEmpty_.notify();
    }

    // 插入队列
    void put(T&& x) {
        MutexLockGuard lock(mutex_);
        while (queue_.full()) {
            notFull_.wait();
        }
        assert(!queue_.full());
        queue_.push_back(std::move(x));
        notEmpty_.notify();
    }

    // 出队
    T take() {
        MutexLockGuard lock(mutex_);
        while (queue_.empty()) {
            notEmpty_.wait();
        }
        assert(!queue_.empty());
        T front(std::move(queue_.front()));
        queue_.pop_front();
        notFull_.notify();
        return front;
    }

    // 是否为空
    bool empty() const {
        MutexLockGuard lock(mutex_);
        return queue_.empty();
    }

    // 是否满
    bool full() const {
        MutexLockGuard lock(mutex_);
        return queue_.full();
    }

    // 当前大小
    size_t size() const {
        MutexLockGuard lock(mutex_);
        return queue_.size();
    }

    // 容量
    size_t capacity() const {
        MutexLockGuard lock(mutex_);
        return queue_.max_size();
    }

private:
    mutable MutexLock mutex_;               ///< 锁
    Condition notEmpty_ GUARDED_BY(mutex_); ///< 不为空标记
    Condition notFull_ GUARDED_BY(mutex_);  ///< 不满标记
    jm::circular_buffer<T, ssize> queue_ GUARDED_BY(mutex_);    ///< 队列
};

}  // namespace ds

}  // namespace brsdk
