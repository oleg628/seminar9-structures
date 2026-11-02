#include "structures.h"

#include <stdexcept>

namespace seminar9 {

namespace {
int checked_capacity(int capacity) {
    if (capacity <= 0) {
        throw std::invalid_argument("capacity must be positive");
    }
    return capacity;
}
}  // namespace

ArrayStack::ArrayStack(int capacity)
    : data_(static_cast<std::size_t>(checked_capacity(capacity)), 0), capacity_(capacity) {}

void ArrayStack::push(int value) {
    if (full()) {
        throw StructureError("stack overflow");
    }
    data_[static_cast<std::size_t>(size_)] = value;
    ++size_;
}

int ArrayStack::pop() {
    if (empty()) {
        throw StructureError("stack underflow");
    }
    --size_;
    return data_[static_cast<std::size_t>(size_)];
}

int ArrayStack::top() const {
    if (empty()) {
        throw StructureError("stack is empty");
    }
    return data_[static_cast<std::size_t>(size_ - 1)];
}

TwoStacks::TwoStacks(int capacity)
    : data_(static_cast<std::size_t>(checked_capacity(capacity) + 1), 0),
      capacity_(capacity),
      top1_(0),
      top2_(capacity + 1) {}

void TwoStacks::push_first(int value) {
    if (top1_ + 1 == top2_) {
        throw StructureError("two stacks overflow");
    }
    ++top1_;
    data_[static_cast<std::size_t>(top1_)] = value;
}

int TwoStacks::pop_first() {
    if (top1_ == 0) {
        throw StructureError("first stack underflow");
    }
    const int value = data_[static_cast<std::size_t>(top1_)];
    --top1_;
    return value;
}

void TwoStacks::push_second(int value) {
    if (top1_ + 1 == top2_) {
        throw StructureError("two stacks overflow");
    }
    --top2_;
    data_[static_cast<std::size_t>(top2_)] = value;
}

int TwoStacks::pop_second() {
    if (top2_ == capacity_ + 1) {
        throw StructureError("second stack underflow");
    }
    const int value = data_[static_cast<std::size_t>(top2_)];
    ++top2_;
    return value;
}

CircularQueue::CircularQueue(int capacity)
    : data_(static_cast<std::size_t>(checked_capacity(capacity)), 0), capacity_(capacity) {}

void CircularQueue::enqueue(int value) {
    if (full()) {
        throw StructureError("queue overflow");
    }
    data_[static_cast<std::size_t>(tail_)] = value;
    tail_ = (tail_ + 1) % capacity_;
    ++count_;
}

int CircularQueue::dequeue() {
    if (empty()) {
        throw StructureError("queue underflow");
    }
    const int value = data_[static_cast<std::size_t>(head_)];
    head_ = (head_ + 1) % capacity_;
    --count_;
    return value;
}

int CircularQueue::front() const {
    if (empty()) {
        throw StructureError("queue is empty");
    }
    return data_[static_cast<std::size_t>(head_)];
}

Deque::Deque(int capacity)
    : data_(static_cast<std::size_t>(checked_capacity(capacity)), 0), capacity_(capacity) {}

void Deque::push_front(int value) {
    if (full()) {
        throw StructureError("deque overflow");
    }
    head_ = (head_ - 1 + capacity_) % capacity_;
    data_[static_cast<std::size_t>(head_)] = value;
    ++count_;
}

void Deque::push_back(int value) {
    if (full()) {
        throw StructureError("deque overflow");
    }
    data_[static_cast<std::size_t>(tail_)] = value;
    tail_ = (tail_ + 1) % capacity_;
    ++count_;
}

int Deque::pop_front() {
    if (empty()) {
        throw StructureError("deque underflow");
    }
    const int value = data_[static_cast<std::size_t>(head_)];
    head_ = (head_ + 1) % capacity_;
    --count_;
    return value;
}

int Deque::pop_back() {
    if (empty()) {
        throw StructureError("deque underflow");
    }
    tail_ = (tail_ - 1 + capacity_) % capacity_;
    const int value = data_[static_cast<std::size_t>(tail_)];
    --count_;
    return value;
}

int Deque::front() const {
    if (empty()) {
        throw StructureError("deque is empty");
    }
    return data_[static_cast<std::size_t>(head_)];
}

int Deque::back() const {
    if (empty()) {
        throw StructureError("deque is empty");
    }
    const int index = (tail_ - 1 + capacity_) % capacity_;
    return data_[static_cast<std::size_t>(index)];
}

}  // namespace seminar9
