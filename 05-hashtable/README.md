# HW#5: Hash Table

* **Due date: 11:59pm, 11/27/2023**
* TA: Hyokyung Kim (hyokyung0808@snu.ac.kr)

## Goals

* Learn how to implement hash tables

* Understand two open addressing mechanisms, linear probing and quadratic probing

### Table of contents
1. [Hash Table](#HashTable)
2. [Provided Classes](#Classes)
3. [Basic operations](#BasicOperations)
4. [Open addressing](#OpenAddressing)
5. [Dynamically Enlarging Table](#EnlargingTable)
6. [Submission and Grading](#Submission-and-Grading)

## Hash Table

### Definitions

A hash table is an array-based data structure, mapping keys to
values. A hash table uses a hash function to determine which position
within the array should store the key/value information. Since
multiple keys may map to the same position, it is possible that two
different keys hashed into the same value, resulting in collisions.
In order to address collisions, typical approaches are leveraging open
addressing mechanisms. Particularly for this assignment, we will be
implementing two open addressing mechanisms, linear probing and
quadratic probing.

### Homework Requirements

This homework asks you to develop a hash table supporting following
features.

* Basic operations: insertion, lookup, and remove (see #BasicOperations)
* Open addressing: linear probing, quadratic probing (see #OpenAddressing)
* Dynamically Enlarging Table (see #EnlargingTable)

There are `TODO` marks in `include/hash_slot.hpp` and
`include/hash_table.hpp`, and fill up all such places with your own
implementation. Note that some `TODO` marked functions return a
constant value (such as zero), but these are just to avoid
complitation errors and you will need to accordingly modify the return
statement as well.

## Provided Classes

Two major classes are provided to implement hash tables: `HashTable`
and `HashSlot`. Another important class would be `DefaultHashFunc`,
implementing hash functions.

### Template Types

Most of classes in this assignment are based on templates, and most
classes use the following type convention.

* `typename K` denotes the type of the key.
* `typename V` denotes the type of the value.

Note that while the design of our hash table is very generic (i.e., it
can handle general types of keys and values as well as custom-designed
hash functions), our tests do not fully utilize such a generic
feature. Specifically, our current test mostly utilize `int` type for
`K`, and `std::string` type for `V`. 

### Class HashTable

`HashTable` is a class template (see `hash_table.hpp`), which provides
common interfaces for a hash table. 

* `int HashTable::get(const K &key, V &value)`: It first identifies
    the slot with `key`, and returns the value within the key through
    the reference parameter `value`. It returns -1 if it failed to
    find the slot with `key`. Otherwise, it returns the number of
    probes that have been performed to locate the corresponding slot
    (which has the same `key`).

* `int HashTable::put(const K &key, const V &value)`: It stores the
  pair `key` and `value` into the hash table. It returns -1 1) if it
  failed to insert or 2) if the same key already exists in the hash
  table. Othewrise, it returns the number of probes that have been
  preformed to locate the corresponding slot (which has the same
  `key`). Note that if you had to enlarge the table, `put()` returns
  the number of probes that have been performed before enlarging the
  table.
  
* `int HashTable::remove(const K &key)`: It removes the slot with
  `key` from the hash table. It returns -1 if it failed to
  remove. Othewrise, it returns the number of probes that have been
  preformed to locate the corresponding slot (which has the same
  `key`).

* `unsigned long HashTable::get_pos(const K key)`: This returns the
  initial position index for `key` within the base array. If the
  provided hash function is `hash()` and the table size is `M`, its
  return value would be `hash(key) % M`.

* `virtual unsigned long HashTable::get_next_pos(unsigned long pos,
  unsigned long step) = 0`: This returns the next position index to
  access the base array. Note that this is a pure virtual function in
  `HashTable` such that the linear probing and quadratic probing can
  implement its own probing behavior. Thus, its actual implementation
  should be done in either `LinearProbeHashTable::get_next_pos()` or
  `QuadProbeHashTable::get_next_pos()`.

* `void HashTable::enlarge_table()`: Our hash table requires that its
  table size is doubled if its load factor is greater than 0.5. You
  will need to implement such a dynamic grow feature in this
  `HashTable::enlarge_table()` function. You will also accordingly
  check the load factor after every `HashTable::put()` operation,
  which invokes `HashTable::enlarge_table()` if needed.

* `int HashTable::get_table_size()`: It returns the total size of the
  current base array. The size here should be the number of
  slots that it can hold.

* `int HashTable::get_size()`: It returns the number of active slots,
  which stores the key/value pairs.

* `double HashTable::get_load_factor()`: It returns the load
  factor. Its return value would be the same as
  `get_size()/get_table_size()` while considering the floating type
  conversion.

### Class HashSlot

`HashSlot` is a class template (see `hash_slot.hpp`), which 1) stores
a pair of `key` and `value` and 2) provides necessarily interfaces.
Note that `HashTable` maintains a dynamically allocated array of
`HashSlot` using the pointer variable `HashSlot<K, V> *table` .

You will also need to maintain two flags per slot, `_empty` and
`_removed`: `_empty` represents that the corresponding `HashSlot` is
empty and can be used to store a new `key`/`value` pair. `_removed`
represents that the corresponding `HashSlot` is removed so when
searching for a certain key, this removed `HashSlot` should be used as
a condition to stop the search.

### Class DefaultHashFunc

`DefaultHashFunc` implements a default hash function. Note that the
current integer hash function is a simple identify function (i.e.,
return the key as it is) and the current string hash function sums up
all the character values.

While such a use of hash functions are not ideal (we discussed in
class that using such a naive hash function is not the best), you
don't need to update this hash function for this assignement.

## Open addressing 

You will need to implement a collision resolution method with open
addressing, particularly two mechanisms: linear probing (to be
implemented by `LinearProbeHashTable` and quadratic probing (to be
implemented by `QuadProbeHashTable`).

### Linear Probing

The behavior of linear probing can be formally represented as:

* `position(k, M, i) = (hash(k) + i) % M`

`position(k, M, i)` returns the position within the base table with
the size of `M` for the given key `k` at `i`th trial (i.e., all previous
trials had collisions). You will need to implement this feature in
`LinearProbeHashTable::get_next_pos()`.

### Quadratic Probing

The behavior of quadratic probing can be formally represented as:

* `position(k, M, i) = (hash(k) + 0.5*i + 0.5*i*i) % M`

It would be good to have a look at the lecture slide, page 12 of
`7G-Quadratic_probing.pdf` to easily implement this function. You will
need to implement this feature in
`QuadProbeHashTable::get_next_pos()`.

### Notes on the number of probes

It is important to note that `the number of probes` (which is returned
by `HashTable::get()`, `HashTable::put()`, and `HashTable::remove()`)
is the number of trials, which is starting from `1`.  That is, if the
key is immediately found in `HashTable::get()` with `position(k, M,
0)`, it should return 1. If it performed the extra probe and thus used
`position(k, M, 1)`, it should return 2.

This can be clarified by looking at `probe_test()` in
`tests/hashtable_test.cpp`, which checks the return value of
`HashTable::put()` operations. If your implementation is correct, you
should be able to pass this test.

## Dynamically Enlarging Table

In the beginning, our hash table is assumed to allocate 64 `HashSlot`
(see `HashTable::HashTable()` as well as `INITIAL_TABLE_SIZE`).  As
the hash table stores more and more key/value pairs, we require that
its table size is doubled if its load factor is greater than 0.5. In
other words, the load factor of your hash table should always be less
than (or equal to) 0.5. This requires you to dynamically allocate the
array of `HashSlot`, where its reference should be maintained by the
member variable of `HashTable`, `HashSlot<K, V> *table`.

You will need to implement such a dynamically growing feature in
`HashTable::enlarge_table()`. You will also accordingly check the load
factor after every `HashTable::put()` operation, which invokes
`HashTable::enlarge_table()` if needed.

## Submission and Grading

### Testing your own programs

In `06-hashtable` directory, you run the following commands to compile your own implementation.

```
$ pwd
/xxx/xxx/xxx/06-hashtable
$ mkdir build
$ cd build
$ cmake ../
$ make
$ ls tests/hashtable_test
./tests/hashtable_test
$ ./tests/hashtable_test
[...]
```

If you've all done correctly, the output will look like:

```
===============================================================================
All tests passed (XX assertions in XX test cases)

```

and you are ready to submit!

### Submission

Prepare your submission with following commands:

```
$ pwd
06-hashtable
$ ./prepare-submit.sh
[*] Remove tar file...
[*] Compress files...
./include/hash_slot.hpp
./include/hash_table.hpp
[*] Successfully Compressed!
[*] Done! You are ready to submit
```

Upload `assign6.tar.gz` to the submission server. The address of the
submission server isn't changed since the last assignment.

### Grading

We will perform the auto-testing to grade your code. Note that
provided tests will not be a complete set of tests for grading, and we
may run an extra set of tests to further check robustness and
correctness of your implementation. That says, while passing the
provided tests would be a good sign, that won't necessarily mean that
you will get the full mark. So please try to extend the provided tests
to thoroughly check your code

You will get a _full_ credit, if all tests pass,
*AND* valgrind finds no memory leaks *AND* valgrind reports no memory errors.

