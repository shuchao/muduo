// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_POLLER_EPOLLPOLLER_H
#define MUDUO_NET_POLLER_EPOLLPOLLER_H

#include <muduo/net/Poller.h>

#include <vector>

struct epoll_event;

namespace muduo
{
namespace net
{

///
/// IO Multiplexing with epoll(4).
///
class EPollPoller : public Poller
{
 public:
  EPollPoller(EventLoop* loop);
  virtual ~EPollPoller();

  virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels);
  virtual void updateChannel(Channel* channel);
  virtual void removeChannel(Channel* channel);

 private:
  static const int kInitEventListSize = 16;

  void fillActiveChannels(int numEvents,
                          ChannelList* activeChannels) const;
  void update(int operation, Channel* channel);

  typedef std::vector<struct epoll_event> EventList;	

	//chaoshu:
   /*typedef union epoll_data {
        void *ptr;
         int fd;
         __uint32_t u32;
         __uint64_t u64;
     } epoll_data_t;//保存触发事件的某个文件描述符相关的数据

     struct epoll_event {
         __uint32_t events;      // epoll event
         epoll_data_t data;      // User data variable
     };
*/

  int epollfd_;
  EventList events_;
};

}
}
#endif  // MUDUO_NET_POLLER_EPOLLPOLLER_H
