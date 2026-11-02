/**
 * @file structures.h
 * @brief Стек, очередь и дек на массиве для семинара 9.
 */
#ifndef SEMINAR9_STRUCTURES_H_
#define SEMINAR9_STRUCTURES_H_

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace seminar9 {

/// Ошибка нарушения границ структуры данных.
class StructureError : public std::runtime_error {
   public:
    explicit StructureError(const char* message) : std::runtime_error(message) {}
};

/**
 * @brief Стек на массиве с операциями PUSH/POP за O(1).
 */
class ArrayStack {
   public:
    explicit ArrayStack(int capacity);

    void push(int value);
    int pop();
    int top() const;

    bool empty() const {
        return size_ == 0;
    }
    bool full() const {
        return size_ == capacity_;
    }
    int size() const {
        return size_;
    }
    int capacity() const {
        return capacity_;
    }

   private:
    std::vector<int> data_;
    int capacity_{0};
    int size_{0};
};

/**
 * @brief Два стека в одном массиве A[1..n].
 *
 * Первый стек растёт от начала массива, второй — от конца. Переполнение
 * возникает только тогда, когда суммарно заняты все n клеток.
 */
class TwoStacks {
   public:
    explicit TwoStacks(int capacity);

    void push_first(int value);
    int pop_first();
    void push_second(int value);
    int pop_second();

    int first_size() const {
        return top1_;
    }
    int second_size() const {
        return capacity_ - top2_ + 1;
    }
    int capacity() const {
        return capacity_;
    }
    bool full() const {
        return top1_ + 1 == top2_;
    }

   private:
    std::vector<int> data_;
    int capacity_{0};
    int top1_{0};
    int top2_{0};
};

/**
 * @brief Циклическая очередь Q[1..n] с проверкой underflow/overflow.
 */
class CircularQueue {
   public:
    explicit CircularQueue(int capacity);

    void enqueue(int value);
    int dequeue();
    int front() const;

    bool empty() const {
        return count_ == 0;
    }
    bool full() const {
        return count_ == capacity_;
    }
    int size() const {
        return count_;
    }
    int capacity() const {
        return capacity_;
    }

   private:
    std::vector<int> data_;
    int capacity_{0};
    int head_{0};
    int tail_{0};
    int count_{0};
};

/**
 * @brief Дек на циклическом массиве: вставка и удаление с обоих концов.
 */
class Deque {
   public:
    explicit Deque(int capacity);

    void push_front(int value);
    void push_back(int value);
    int pop_front();
    int pop_back();
    int front() const;
    int back() const;

    bool empty() const {
        return count_ == 0;
    }
    bool full() const {
        return count_ == capacity_;
    }
    int size() const {
        return count_;
    }
    int capacity() const {
        return capacity_;
    }

   private:
    std::vector<int> data_;
    int capacity_{0};
    int head_{0};
    int tail_{0};
    int count_{0};
};

}  // namespace seminar9

#endif  // SEMINAR9_STRUCTURES_H_
