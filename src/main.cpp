#include "structures.h"

#include <iostream>

namespace {

void print_stack() {
    seminar9::ArrayStack stack(6);
    stack.push(4);
    stack.push(1);
    stack.push(3);
    const int first_pop = stack.pop();
    stack.push(8);
    const int second_pop = stack.pop();
    std::cout << "Стек: POP -> " << first_pop << ", затем POP -> " << second_pop
              << "; top = " << stack.top() << ", size = " << stack.size() << "\n";
}

void print_two_stacks() {
    seminar9::TwoStacks stacks(10);
    stacks.push_first(2);
    stacks.push_first(7);
    stacks.push_first(1);
    stacks.push_second(9);
    stacks.push_second(5);
    stacks.push_second(4);
    std::cout << "Два стека: first_size = " << stacks.first_size()
              << ", second_size = " << stacks.second_size() << ", free cells = "
              << (stacks.capacity() - stacks.first_size() - stacks.second_size()) << "\n";
}

void print_queue() {
    seminar9::CircularQueue queue(6);
    queue.enqueue(4);
    queue.enqueue(1);
    queue.enqueue(3);
    const int first = queue.dequeue();
    queue.enqueue(8);
    const int second = queue.dequeue();
    std::cout << "Очередь: DEQUEUE -> " << first << ", затем -> " << second
              << "; front = " << queue.front() << ", size = " << queue.size() << "\n";
}

void print_deque() {
    seminar9::Deque deque(6);
    deque.push_back(5);
    deque.push_front(3);
    deque.push_back(7);
    const int front = deque.pop_front();
    const int back = deque.pop_back();
    std::cout << "Дек: POP-FRONT -> " << front << ", POP-BACK -> " << back
              << "; front = " << deque.front() << ", size = " << deque.size() << "\n";
}

}  // namespace

int main() {
    try {
        print_stack();
        print_two_stacks();
        print_queue();
        print_deque();
    } catch (const seminar9::StructureError& error) {
        std::cerr << "Ошибка структуры данных: " << error.what() << "\n";
        return 1;
    }
    return 0;
}
