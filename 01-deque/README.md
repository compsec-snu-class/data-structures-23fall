# HW#1: Deque

* **Due date: Oct 3rd, 2023, 11:59PM**

## Goals

* Get familiar with C++ programming by implementing simple data structures
  like (expandable) arrays and linked lists.
 
* Get to know how unit testing works and how the rest of the assignments
  will be graded.

* Write a simple algorithm on top of the data structures that you wrote.
  Learn how to separate the interfaces (deque) from the implementations
  (array or linked list).

### Table of contents

1. [Deque API](#Deque-API)
2. [Array Deque](#Array-Deque)
3. [List Deque](#List-Deque)
4. [Palindrome](#Palindrome)
5. [Submission and Grading](#Submission-and-Grading)

## Deque API

According to [cppreference.com](https://en.cppreference.com/w/cpp/container/deque):
> std::deque (double-ended queue) is an indexed sequence container that allows
> fast insertion and deletion at both its beginning and its end.

Here are the common interfaces for a deque defined in `deque.hpp`:
* `void push_front(const T&)`: Add an item to the front
* `void push_back(const T&)`: Add an item to the back
* `std::optional<T> remove_front()`: Remove an item (if exists) from the front
* `std::optional<T> remove_back()`: Remove an item (if exists) from the back
* `bool empty()`: Return `true` if a deque has no element
* `size_t size()`: Return the number of items in the deque
* `T& operator[](size_t i)`: Get the reference to the `i`-th item. You should be
                             able to modify the value of the item with the
                             returned reference.

Note these APIs don't impose any restrictions to the underlying implementation.
In the following, we dive into specific deque implementations, namely with
arrays and linked lists.

Note that `std::optional<T>` return type is used to represent a value
that may or may not be present. It is added to C++17 and has been
widely adopted by different languages.
If you are not familiar with this, you can simply assign 
a value of `T` to store a value, or assign `std::nullopt` to represent that
there is no value. Just like `nullptr`, it can be tested whether it has a value,
using `if (!opt)`. If a value exists, that value can be retrieved with `value()`
method. For further information, please refer to [here](https://en.cppreference.com/w/cpp/utility/optional).

## Array Deque Implementation

An array deque stores the items in a circular queue. If you push an item to
the front, you decrease the front (don't forget to take the modulus) and place
the item at the index pointed by `front`. For example, say you are given an
array deque:

```
size: 3
capapciry: 8
front: 3 
back: 7
arr: -----+
          |
          v 
+---+---+---+---+---+---+---+---+
|   |   |   |   | 2 | 3 | 4 |   |
+---+---+---+---+---+---+---+---+
0   1   2   3   4   5   6   7
```

If you call `push_front(5)`, the result will be:


```
size: 3 -> 4
capapciry: 8
front: 3 -> 2
back: 7
arr: -----+
          |
          v 
+---+---+---+---+---+---+---+---+
|   |   |   | 5 | 2 | 3 | 4 |   |
+---+---+---+---+---+---+---+---+
0   1   2   3   4   5   6   7
```

`push_back()` can be implemented in a way similar to `push_front()`. How about
`remove_[front/back]()`? Just do the reverse and keep everything looks reasonable.

Wait! What if the buffer is full? Especially when `front == back`? In
that case, you should _double_ the size of your buffer and copy the items
in your original buffer. (In C++, it is often more faster to _move_ items
than simply copying them. But we won't go in to too much details. It is just
okay to copy them for now.)

If you look at the code, you will find out that the type of `arr` is
`std::unique_ptr<T[]>`. For those who haven't seen this _smart_
pointer before, it is used to represent an exclusive ownership over an
object, which avoids to have an explicit (and easy-to-forget)
destructor. In particular, a unique pointer instructs the compiler
that it is the only owner of that object, so the object is destroyed
automatically once the unique pointer is gone from the scope. Methods
like `std::make_unique` or `.reset()` will come in handy when you
initialize an object or update a unique pointer, respectively. For
further information, please refer to this
[link](https://en.cppreference.com/w/cpp/memory/unique_ptr)).

### Getting started

In `deque.hpp`, there are several member functions of `ArrayDeque`, whose body
is left as `TODO`. Your job is to implement _all_ of them and pass all the tests
that are provided by `tests/deque_tests.cpp`. These test cases (and probably
some more private test cases) will be used to grade your submissions. (See
submissions and grading for further information.)

## Linked-List Deque Implementation

Another deque implementation that we will implement uses a linked
list, especially, a doubly-linked and circular one. The linked list is
widely used to store data which dynamically grow or shrink. In the
linked list, each node in a list hold _pointers_ to its successor
(i.e., a next node) and its predecessor (i.e., a previous node).


To make writing the code more easier and clear, we have the deque create a
dummy node, when initialized. This dummy node is pointed by the `sentinel`
pointer. Initially, the successor and the predecessor pointer of this dummy node
both points to itself:

```
size: 0
sentinel: --+
            |
            v
            +---+
      +====>| / |=====+
      | +---|   |<--+ |
      | |   +---+   | |
      | +-----------+ |
      +===============+

==>: next
-->: prev
```
 
Every time you push an item to this list, you will have make `sentinel->next`
or `sentinel->prev`  to point a new node, and update the relevant pointers of
neighboring nodes.

For example, given a list deque like this:

```
size: 3
sentinel: --+
            |
            v
            +---+   +---+   +---+   +---+
      +====>| / |==>| 2 |==>| 3 |==>| 4 |====+
      | +---|   |<--|   |<--|   |<--|   |<-+ |
      | |   +---+   +---+   +---+   +---+  | |
      | +----------------------------------+ |
      +======================================+

==>: next
-->: prev
```

After you `push_back(5)`:

```
size: 3 -> 4
sentinel: --+
            |
            v
            +---+   +---+   +---+   +---+   +---+
      +====>| / |==>| 2 |==>| 3 |==>| 4 |==>| 5 |====+
      | +---|   |<--|   |<--|   |<--|   |<--|   |<-+ |
      | |   +---+   +---+   +---+   +---+   +---+  | |
      | +------------------------------------------+ |
      +==============================================+

==>: next
-->: prev
```

Well, good C++ programmers would use `shared_ptr` and `weak_ptr` (both
of which are different types of smart pointers and are used to
represent _sharing_ of the objects) for `next`, `prev` and `sentinel`,
but we won't force you to use it for this assignment (we may in
upcoming assignments? stay tuned!)

Be careful and don't forget to _deallocate_ these nodes in the destructor.

### Getting started

In `deque.hpp`, there are several member functions of `ListDeque`, whose body
is left as `TODO`. Your job is to implement _all_ of them and pass all the tests
that are provided by `tests/deque_tests.cpp`. These test cases (and probably
some more private test cases) will be used to grade your submissions. (See
submissions and grading for further information.)

## Application: Palindrome

By far we described how to build deques in two ways---using an array
or a linked-list. The deque is a powerful primitive to build either a
stack or a queue, and many interesting applications can be implemented
based on these.  In the rest of this homework, we will implement a
simple algorithm which makes a use of a stack: the palindrome tester.

From the Wikipedia:

> A palindrome is a word, number, phrase, or other sequence of characters which
> reads the same backward as forward, such as madam, racecar.

You simply push each character in a string to a stack, and later pop them to
make a string. If two string matches? Then it is a palindrome!

The palindrome tester should be implemented in `palindrome/include/palindrome.hpp`.

## Submission and Grading

### Testing your own programs

In `01-deque` directory, you run the following commands to compile your own
implementation.

```
$ pwd
/xxx/xxx/xxx/01-deque
$ mkdir build
$ cd build
$ cmake ../
$ make
$ ls tests/deque_test
./test/deque_test
$ valgrind ./tests/deque_test
[...]
$ valgrind ./tests/palindrome_test
[...]
```

If you've all done correctly, the output will look like:

```
===============================================================================
All tests passed (XX assertions in XX test cases)

```

If your code pass all tests **without memory leaks**, then you will get the perfect score!


### Submission

Before submit your assignment, you should run the following commands.

```
$ pwd
/xxx/xxx/xxx/01-deque
$ ./prepare-submit.sh
[*] Remove tar file...
[*] Compress files...
./include/deque.hpp
./palindrome/include/palindrome.hpp
[*] Successfully Compressed!
[*] Done! You are ready to submit
```

and you are ready to submit!


### References

1. cppreference.com. std::deque--[Link](https://en.cppreference.com/w/cpp/container/deque)

2. cppreference.com. std::unique_ptr--[Link](https://en.cppreference.com/w/cpp/memory/unique_ptr)

4. cppreference.com. std::optional--[Link](https://en.cppreference.com/w/cpp/utility/optional)

3. Deques, In UW CSE 332, Winter 2020--[Link](https://courses.cs.washington.edu/courses/cse332/20wi/homework/deque/)
