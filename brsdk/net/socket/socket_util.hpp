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
 * @file socket_util.hpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-07-25
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <errno.h>
#include <string>
#include <poll.h>

namespace brsdk {

namespace net {

#define BRSDK_SOCKADDR_STRLEN sizeof(((struct sockaddr_un*)(NULL))->sun_path)
#define BRSDK_SOCKADDR_LEN(addr) brsdk::net::sock_addr_len((brsdk::net::sock_addr_t*)addr)
#define BRSDK_SOCKADDR_STR(addr, buf) brsdk::net::sock_addr_str((brsdk::net::sock_addr_t*)addr, buf, sizeof(buf))
#define BRSDK_SOCKADDR_PRINT(addr) brsdk::net::sock_addr_print((brsdk::net::sock_addr_t*)addr)

///< 非法套接字
#define BRSDK_INVALID_SOCKET -1

///< poll状态
enum {
    poll_in = POLLIN,
    poll_out = POLLOUT,
    poll_err = POLLERR,
};

/**
 * @brief 网络地址
 * 
 */
typedef union {
    struct sockaddr sa;         ///< 通用地址头
    struct sockaddr_in sin;     ///< ipv4
    struct sockaddr_in6 sin6;   ///< ipv6
    struct sockaddr_un sun;     ///< unix
} sock_addr_t;

/**
 * @brief 网络错误码
 * 
 * @return int 
 */
static inline int socket_errno(void) {
    return errno;
}

///< 套接字错误码取反
static inline int socket_errno_negative() {
    int err = socket_errno();
    return err > 0 ? -err : -1;
}

/**
 * @brief poll
 * 
 * @param fds 
 * @param nfds 
 * @param timeout 
 * @return int 
 */
static inline int poll(struct pollfd *fds, nfds_t nfds, int timeout) {
    return ::poll(fds, nfds, timeout);
}

/**
 * @brief poll超时等待
 *
 * @param fd 描述符
 * @param how 方式，r-可读，w-可写
 * @param w 超时时间，单位ms
 *
 * @return 小于0异常，0超时，1正常
 */
int poll_wait(int fd, char how, time_t w);

/**
 * @brief 创建套接字
 *
 * @param type 传输类型
 * @param domain 地址类型
 * @param res 预留，标识协议
 *
 * @return int 套接字描述符，小于0异常
 */
static inline int sock_creat(int family, int type, int protocol) {
    return ::socket(family, type, protocol);
}

/**
 * @brief 创建套接字
 * @return int 套接字描述符，小于0异常
 */
static inline int sock_creat(int family, int type) { return sock_creat(family, type, 0); }

/**
 * @brief 创建tcp套接字
 *
 * @return int 套接字描述符，小于0异常
 */
static inline int sock_tcp_creat(int family = AF_INET) {
    return sock_creat(family, SOCK_STREAM, 0);
}

///< 非阻塞tcp套接字
static inline int sock_tcp_nonblock_creat(int family = AF_INET) {
    return sock_creat(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
}

/**
 * @brief 获取套接字错误码
 * 
 * @param sockfd 
 * @return int 
 */
int sock_get_error(int sockfd);

/**
 * @brief 创建udp套接字
 *
 * @return int 套接字描述符，小于0异常
 */
static inline int sock_udp_creat(int family = AF_INET) { return sock_creat(family, SOCK_DGRAM, 0); }

// 无名套接字对
int sock_pair(int family, int type, int protocol, int sv[2]);

/**
 * @brief 绑定
 *
 * @param fd 套接字描述符
 * @param addr 地址
 *
 * @return 小于0异常，0正常
 */
int sock_bind(int fd, const char* ip, int port);

///< 绑定unix地址
static inline int sock_unix_bind(int fd, const char* path) { return sock_bind(fd, path, -1); }

/**
 * @brief 监听套接字
 *
 * @param fd 套接字描述符
 * @param blocklog
 *
 * @return 小于0异常，0正常
 */
static inline int sock_listen(int fd, int blocklog = 5) { return ::listen(fd, blocklog); }

/**
 * @brief accept
 *
 * @param fd 服务器套接字
 * @param addr 客户端地址
 *
 * @return 小于0异常，accept得到的客户端套接字
 */
int sock_accept(int fd, sock_addr_t& addr);

/**
 * @brief 连接到服务器
 *
 * @param fd 描述符
 * @param addr 服务器地址
 * @param ms 使用poll等待，单位ms，-1时为阻塞
 *
 * @return
 */
int sock_connect(int fd, const sock_addr_t& addr, time_t ms = -1);

/**
 * @brief 关闭套接字
 *
 * @param fd 描述符
 * @param wait 适用于tcp的延迟关闭和reset
 */
void sock_close2(int fd, time_t wait = 0);

/**
 * @brief 关闭套接字
 *
 * @param fd 描述符
 */
void sock_close(int fd);

/**
 * @brief 关闭套接字
 *
 * @param fd 套接字描述符
 * @param how 方式，'r'关闭读端SHUT_RD，'w'-关闭写端SHUT_WR，'b'-关闭读写SHUT_RDWR
 */
void sock_shutdown(int fd, char how = 'b');

/**
 * @brief 数据发送
 * @details 只会进行一次数据写入
 *
 * @param fd 套接字描述符
 * @param data 数据
 * @param len 数据长度
 * @param w 超时时间，小于0阻塞，单位ms，使用poll来做超时
 *
 * @return 小于0异常，成功写的数据长度
 */
ssize_t sock_write(int fd, const void* data, size_t len, time_t w = -1);

/**
 * @brief 数据接收
 * @details 只会进行一次数据发送
 *
 * @param fd 套接字描述符
 * @param data 数据
 * @param len 数据长度
 * @param w 超时时间，小于0阻塞，单位ms，使用poll来做超时
 *
 * @return 小于0异常，成功读到数据长度
 */
ssize_t sock_read(int fd, void* data, size_t len, time_t w = -1);

/**
 * @brief 数据发送
 * @details 除非发送异常，否则会直到数据发送完才返回
 *
 * @param fd 套接字描述符
 * @param data 数据
 * @param len 数据长度
 * @param w 超时时间，小于0阻塞，单位ms，使用poll来做超时
 *
 * @return 小于0异常，成功写的数据长度
 */
ssize_t sock_writen(int fd, const void* data, size_t len, time_t w = -1);

/**
 * @brief 数据接收
 * @details 除非发送异常，否则会直到数据接收完才返回
 *
 * @param fd 套接字描述符
 * @param data 数据
 * @param len 数据长度
 * @param w 超时时间，小于0阻塞，单位ms，使用poll来做超时
 *
 * @return 小于0异常，成功读到数据长度
 */
ssize_t sock_readn(int fd, void* data, size_t len, time_t w = -1);

ssize_t sock_readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t sock_writev(int fd, const struct iovec *iov, int iovcnt);

// recv/send
ssize_t sock_send(int fd, const void* data, size_t len, int flags, time_t w = -1);
ssize_t sock_recv(int fd, void* data, size_t len, int flags, time_t w = -1);

// recvfrom/sendto，用于udp
ssize_t sock_sendto(int fd, const void* data, size_t len, const sock_addr_t& addr, time_t w = -1);
ssize_t sock_recvfrom(int fd, void* data, size_t len, sock_addr_t& addr, time_t w = -1);

// 地址重用
int sock_set_addr_reuse(int fd, bool en = true);

// 关闭延迟
int sock_set_nodelay(int fd, bool en = true);

// 设置keepalive
int sock_set_keepalive(int fd, bool en = true);

// 设置阻塞
int sock_set_nonblock(int fd, bool en = true);

// 设置接收超时
int sock_set_recv_timeout(int fd, time_t t);

// 设置发送超时
int sock_set_send_timeout(int fd, time_t t);

// 设置接收缓冲区
int sock_set_recv_buf_len(int fd, size_t len);

// 设置发送缓冲区
int sock_set_send_buf_len(int fd, size_t len);

// 地址族
int sock_family(int fd);

// 通过fd获取本地地址
int sock_get_name(int fd, sock_addr_t& addr);

// 通过fd获取对端地址
int sock_get_peer_name(int fd, sock_addr_t& addr);

// 是否是连接到自己
bool sock_is_self_connect(int sockfd);

// 地址长度
socklen_t sock_addr_len(const sock_addr_t* addr);

// ip地址转为网络字节序
int sock_resolver(const char* host, sock_addr_t* addr);

// 获取ipport字符串形式
const char* sock_addr_str(const sock_addr_t* addr, char* buf, int len);

// 获取ip地址
const char* sock_addr_ip(const sock_addr_t* addr, char* ip, int len);

// 获取端口
uint16_t sock_addr_port(const sock_addr_t* addr);

// 设置地址族
void sock_set_family(sock_addr_t* addr, int family);

// 设置ip
int sock_set_ip(sock_addr_t* addr, const char* host);

// 设置端口
void sock_set_port(sock_addr_t* addr, int port);

// 同时设置ip端口
int sock_set_ipport(sock_addr_t* addr, const char* host, int port);

// 设置unix域的路径
static inline void sock_set_path(sock_addr_t* addr, const char* path) {
    addr->sa.sa_family = AF_UNIX;
    memcpy(addr->sun.sun_path, path, strlen(path) < sizeof(addr->sun.sun_path) ? strlen(path) : sizeof(addr->sun.sun_path));
}

// 获取unix域路径
static inline void sock_get_path(const sock_addr_t* addr, char* path, size_t len) {
    memcpy(path, addr->sun.sun_path, strlen(path) < sizeof(addr->sun.sun_path) ? len : sizeof(addr->sun.sun_path));
}

// 打印地址
static inline void sock_addr_print(sock_addr_t* addr) {
    char buf[BRSDK_SOCKADDR_STRLEN] = {0};
    sock_addr_str(addr, buf, sizeof(buf));
    puts(buf);
}

// 创建套接字并绑定
static inline int sock_fast_bind(int port, const char *ip, int type) {
    sock_addr_t addr;
    memset(&addr, 0, sizeof(addr));

    int ret = sock_set_ipport(&addr, ip, port);
    if (ret != 0) {
        return ret;
    }

    int fd = sock_creat(addr.sa.sa_family, type, 0);
    if (fd < 0) {
        return fd;
    }

    if (sock_set_addr_reuse(fd) < 0) {
        sock_close(fd);
        return socket_errno_negative();
    }

    if (sock_bind(fd, ip, port) < 0) {
        sock_close(fd);
        return socket_errno_negative();
    }

    return fd;
}

// 创建绑定并监听
static inline int sock_fast_listen(int port, const char *ip, int type=SOCK_STREAM) {
    int fd = sock_fast_bind(port, ip, type);
    if (fd < 0) {
        return fd;
    }

    if (sock_listen(fd, 128) < 0) {
        sock_close(fd);
        return socket_errno_negative();
    }

    return fd;
}

} // namespace net

} // namespace brsdk
