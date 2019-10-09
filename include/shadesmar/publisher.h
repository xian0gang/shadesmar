//
// Created by squadrick on 7/30/19.
//

#ifndef shadesmar_PUBLISHER_H
#define shadesmar_PUBLISHER_H

#include <cstdint>

#include <cstring>
#include <memory>
#include <string>

#include <iostream>

#include <shadesmar/memory.h>

namespace shm {
template <typename msgT, uint32_t queue_size>
class Publisher {
 public:
  explicit Publisher(std::string topic_name) : topic_name_(topic_name) {
    mem_ = std::make_shared<Memory<queue_size>>(topic_name);
  }

  bool publish(std::shared_ptr<msgT> msg) { return publish(msg.get()); }

  bool publish(msgT &msg) { return publish(&msg); }

  bool publish(msgT *msg) {
    bool success = mem_->write(msg, sizeof(msgT));
    return success;
  }

 private:
  std::string topic_name_;

  std::shared_ptr<Memory<queue_size>> mem_;
};
}  // namespace shm
#endif  // shadesmar_PUBLISHER_H
