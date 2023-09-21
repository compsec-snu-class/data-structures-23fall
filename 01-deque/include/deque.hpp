#ifndef _DEQUE_H
#define _DEQUE_H

#include <string>
#include <iostream>
#include <type_traits>
#include <optional>
#include <iostream>
#include <memory>
#include <cassert>

/* NOTE: Deque, ArrayDeque, ListDeque Declaration modification is not allowed.
 * Fill in the TODO sections in the following code. */
template <typename T>
class Deque {
public:
    virtual ~Deque() = default;

    /* NOTE: We won't implement push functions that take rvalue references. */
    virtual void push_front(const T&) = 0;
    virtual void push_back(const T&) = 0;

    /* NOTE: Unlike STL implementations which have separate `front` and
       pop_front` functions, we have one unified method for removing an elem. */
    virtual std::optional<T> remove_front() = 0;
    virtual std::optional<T> remove_back() = 0;

    virtual bool empty() = 0;
    virtual size_t size() = 0;

    virtual T& operator[](size_t) = 0;
};

template <typename T>
class ArrayDeque : public Deque<T> {
public:
    ArrayDeque();
    ~ArrayDeque() = default;

    void push_front(const T&) override;
    void push_back(const T&) override;

    std::optional<T> remove_front() override;
    std::optional<T> remove_back() override;

    bool empty() override;
    size_t size() override;
    size_t capacity();

    T& operator[](size_t) override;

private:
    std::unique_ptr<T[]> arr;
    size_t front;
    size_t back;
    size_t size_;
    size_t capacity_;

    void resize();
};

template <typename T>
ArrayDeque<T>::ArrayDeque() :
    front{63 /* You can change this */},
    back{0 /* You can change this */},
    size_{0}, capacity_{64} {
    arr = std::make_unique<T[]>(capacity_);
}

template <typename T>
void ArrayDeque<T>::push_front(const T& item) {
    // TODO
}

template <typename T>
void ArrayDeque<T>::push_back(const T& item) {
    // TODO
}

template <typename T>
std::optional<T> ArrayDeque<T>::remove_front() {
    // TODO
    return std::nullopt;
}

template <typename T>
std::optional<T> ArrayDeque<T>::remove_back() {
    // TODO
    return std::nullopt;
}

template <typename T>
void ArrayDeque<T>::resize() {
    // TODO
}

template <typename T>
bool ArrayDeque<T>::empty() {
    // TODO
    return false;
}

template <typename T>
size_t ArrayDeque<T>::size() {
    // TODO
    return 0;
}

template <typename T>
size_t ArrayDeque<T>::capacity() {
    // TODO
    return 0;
}

template <typename T>
T& ArrayDeque<T>::operator[](size_t idx) {
    // TODO
    return *new T{};
}

template<typename T>
struct ListNode {
    std::optional<T> value;
    ListNode* prev;
    ListNode* next;

    ListNode() : value(std::nullopt), prev(this), next(this) {}
    ListNode(const T& t) : value(t), prev(this), next(this) {}

    ListNode(const ListNode&) = delete;
};

template<typename T>
class ListDeque : public Deque<T> {
public:
    ListDeque();
    ~ListDeque();

    void push_front(const T&) override;
    void push_back(const T&) override;

    std::optional<T> remove_front() override;
    std::optional<T> remove_back() override;

    bool empty() override;
    size_t size() override;

    T& operator[](size_t) override;

    size_t size_ = 0;
    ListNode<T>* sentinel = nullptr;
};

template<typename T>
ListDeque<T>::ListDeque() : sentinel(new ListNode<T>{}), size_(0) {}

template<typename T>
void ListDeque<T>::push_front(const T& t) {
    // TODO
}

template<typename T>
void ListDeque<T>::push_back(const T& t) {
    // TODO
}

template<typename T>
std::optional<T> ListDeque<T>::remove_front() {
    // TODO
    return std::nullopt;
}

template<typename T>
std::optional<T> ListDeque<T>::remove_back() {
    // TODO
    return std::nullopt;
}

template<typename T>
bool ListDeque<T>::empty() {
    // TODO
    return false;
}

template<typename T>
size_t ListDeque<T>::size() {
    // TODO
    return 0;
}

template<typename T>
T& ListDeque<T>::operator[](size_t idx) {
    // TODO
    return *new T{};
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const ListNode<T>& n) {
    if (n.value)
        os << n.value.value();

    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const ListDeque<T>& l) {
    auto np = l.sentinel->next;
    while (np != l.sentinel) {
        os << *np << ' ';
        np = np->next;
    }

    return os;
}

template<typename T>
ListDeque<T>::~ListDeque() {
    // TODO
}

#endif // _DEQUE_H
