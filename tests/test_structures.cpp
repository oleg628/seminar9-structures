#include "structures.h"

#include <deque>
#include <queue>
#include <random>

#include <gtest/gtest.h>

namespace {

using seminar9::ArrayStack;
using seminar9::CircularQueue;
using seminar9::Deque;
using seminar9::StructureError;
using seminar9::TwoStacks;

TEST(ArrayStackTest, RepeatsSeminarSequence) {
    ArrayStack stack(6);
    stack.push(4);
    stack.push(1);
    stack.push(3);
    EXPECT_EQ(stack.pop(), 3);
    stack.push(8);
    EXPECT_EQ(stack.pop(), 8);
    EXPECT_EQ(stack.top(), 1);
    EXPECT_EQ(stack.size(), 2);
    EXPECT_FALSE(stack.empty());
}

TEST(ArrayStackTest, DetectsUnderflowAndOverflow) {
    ArrayStack stack(2);
    EXPECT_THROW(stack.pop(), StructureError);
    EXPECT_THROW(stack.top(), StructureError);
    stack.push(1);
    stack.push(2);
    EXPECT_TRUE(stack.full());
    EXPECT_THROW(stack.push(3), StructureError);
    EXPECT_EQ(stack.pop(), 2);
    EXPECT_EQ(stack.pop(), 1);
    EXPECT_TRUE(stack.empty());
}

TEST(TwoStacksTest, InterleavedOperationsKeepIndependentValues) {
    TwoStacks stacks(6);
    stacks.push_first(1);
    stacks.push_second(10);
    stacks.push_first(2);
    stacks.push_second(9);

    EXPECT_EQ(stacks.first_size(), 2);
    EXPECT_EQ(stacks.second_size(), 2);
    EXPECT_EQ(stacks.pop_first(), 2);
    EXPECT_EQ(stacks.pop_second(), 9);
    EXPECT_EQ(stacks.pop_first(), 1);
    EXPECT_EQ(stacks.pop_second(), 10);
    EXPECT_THROW(stacks.pop_first(), StructureError);
    EXPECT_THROW(stacks.pop_second(), StructureError);
}

TEST(TwoStacksTest, UsesAllCapacityWithoutFixedPartition) {
    TwoStacks stacks(4);
    stacks.push_first(1);
    stacks.push_first(2);
    stacks.push_first(3);
    stacks.push_second(4);
    EXPECT_TRUE(stacks.full());

    EXPECT_THROW(stacks.push_first(5), StructureError);
    EXPECT_THROW(stacks.push_second(6), StructureError);

    EXPECT_EQ(stacks.pop_first(), 3);
    stacks.push_first(5);
    EXPECT_EQ(stacks.pop_first(), 5);
    EXPECT_EQ(stacks.pop_second(), 4);
    EXPECT_EQ(stacks.pop_first(), 2);
    EXPECT_EQ(stacks.pop_first(), 1);
}

TEST(TwoStacksTest, OverflowOnlyWhenTotalIsCapacity) {
    TwoStacks stacks(3);
    stacks.push_first(1);
    stacks.push_second(2);
    EXPECT_FALSE(stacks.full());
    stacks.push_first(3);
    EXPECT_TRUE(stacks.full());
    EXPECT_THROW(stacks.push_second(4), StructureError);
}

TEST(CircularQueueTest, RepeatsSeminarSequence) {
    CircularQueue queue(6);
    queue.enqueue(4);
    queue.enqueue(1);
    queue.enqueue(3);
    EXPECT_EQ(queue.dequeue(), 4);
    queue.enqueue(8);
    EXPECT_EQ(queue.dequeue(), 1);
    EXPECT_EQ(queue.front(), 3);
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.dequeue(), 3);
    EXPECT_EQ(queue.dequeue(), 8);
    EXPECT_TRUE(queue.empty());
}

TEST(CircularQueueTest, WrapsAroundArrayEnd) {
    CircularQueue queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    EXPECT_EQ(queue.dequeue(), 1);
    queue.enqueue(4);
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.dequeue(), 2);
    EXPECT_EQ(queue.dequeue(), 3);
    EXPECT_EQ(queue.dequeue(), 4);
}

TEST(CircularQueueTest, DetectsUnderflowAndOverflow) {
    CircularQueue queue(2);
    EXPECT_THROW(queue.dequeue(), StructureError);
    EXPECT_THROW(queue.front(), StructureError);
    queue.enqueue(1);
    queue.enqueue(2);
    EXPECT_TRUE(queue.full());
    EXPECT_THROW(queue.enqueue(3), StructureError);
    EXPECT_EQ(queue.dequeue(), 1);
    EXPECT_FALSE(queue.full());
    queue.enqueue(3);
    EXPECT_EQ(queue.dequeue(), 2);
    EXPECT_EQ(queue.dequeue(), 3);
}

TEST(DequeTest, OperationsFromBothEnds) {
    Deque deque(6);
    deque.push_back(5);
    deque.push_front(3);
    deque.push_back(7);

    EXPECT_EQ(deque.front(), 3);
    EXPECT_EQ(deque.back(), 7);
    EXPECT_EQ(deque.pop_front(), 3);
    EXPECT_EQ(deque.pop_back(), 7);
    EXPECT_EQ(deque.front(), 5);
    EXPECT_EQ(deque.size(), 1);
}

TEST(DequeTest, WrapsAroundBothEnds) {
    Deque deque(3);
    deque.push_front(1);
    deque.push_back(2);
    deque.push_front(0);
    EXPECT_TRUE(deque.full());
    EXPECT_EQ(deque.front(), 0);
    EXPECT_EQ(deque.back(), 2);
    EXPECT_EQ(deque.pop_back(), 2);
    EXPECT_EQ(deque.pop_front(), 0);
    EXPECT_EQ(deque.pop_front(), 1);
    EXPECT_TRUE(deque.empty());
}

TEST(DequeTest, DetectsUnderflowAndOverflow) {
    Deque deque(2);
    EXPECT_THROW(deque.pop_front(), StructureError);
    EXPECT_THROW(deque.pop_back(), StructureError);
    EXPECT_THROW(deque.front(), StructureError);
    deque.push_back(1);
    deque.push_front(2);
    EXPECT_TRUE(deque.full());
    EXPECT_THROW(deque.push_front(3), StructureError);
    EXPECT_THROW(deque.push_back(4), StructureError);
    EXPECT_EQ(deque.pop_back(), 1);
    EXPECT_EQ(deque.pop_front(), 2);
    EXPECT_TRUE(deque.empty());
}

TEST(ModelTest, DequeMatchesStdDeque) {
    Deque actual(7);
    std::deque<int> expected;
    std::mt19937 rng(42U);

    for (int step = 0; step < 500; ++step) {
        const int operation = static_cast<int>(rng() % 4U);
        if (operation == 0) {
            const int value = static_cast<int>(rng() % 100U);
            if (!actual.full()) {
                actual.push_back(value);
                expected.push_back(value);
            }
        } else if (operation == 1) {
            const int value = static_cast<int>(rng() % 100U);
            if (!actual.full()) {
                actual.push_front(value);
                expected.push_front(value);
            }
        } else if (operation == 2) {
            if (!expected.empty()) {
                EXPECT_EQ(actual.pop_front(), expected.front());
                expected.pop_front();
            } else {
                EXPECT_THROW(actual.pop_front(), StructureError);
            }
        } else {
            if (!expected.empty()) {
                EXPECT_EQ(actual.pop_back(), expected.back());
                expected.pop_back();
            } else {
                EXPECT_THROW(actual.pop_back(), StructureError);
            }
        }
        ASSERT_EQ(actual.size(), expected.size());
        if (!expected.empty()) {
            EXPECT_EQ(actual.front(), expected.front());
            EXPECT_EQ(actual.back(), expected.back());
        }
    }
}

TEST(ModelTest, QueueMatchesStdQueue) {
    CircularQueue actual(7);
    std::queue<int> expected;
    std::mt19937 rng(7U);

    for (int step = 0; step < 500; ++step) {
        const int operation = static_cast<int>(rng() % 3U);
        if (operation < 2) {
            const int value = static_cast<int>(rng() % 100U);
            if (!actual.full()) {
                actual.enqueue(value);
                expected.push(value);
            }
        } else if (!expected.empty()) {
            EXPECT_EQ(actual.dequeue(), expected.front());
            expected.pop();
        } else {
            EXPECT_THROW(actual.dequeue(), StructureError);
        }
        ASSERT_EQ(actual.size(), expected.size());
        if (!expected.empty()) {
            EXPECT_EQ(actual.front(), expected.front());
        }
    }
}

TEST(CapacityTest, RejectsNonPositiveCapacity) {
    EXPECT_THROW(ArrayStack(0), std::invalid_argument);
    EXPECT_THROW(TwoStacks(-1), std::invalid_argument);
    EXPECT_THROW(CircularQueue(0), std::invalid_argument);
    EXPECT_THROW(Deque(-5), std::invalid_argument);
}

}  // namespace
