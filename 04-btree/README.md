# HW#4: B-tree

* **Due data: 11:59pm, 11/13/2023**
* TA: Byeongwook Kim (rlaquddnr904@snu.ac.kr)

## Goals

* Get to implement an extreme data structure that is used widely today.

* Implement a insert function that inserts an item to the B-tree without affecting
  the invariants of the tree (e.g., balance, utilization, etc.)
  
  
### Table of contents

1. [B-tree](#B-tree)
2. [Types](#Types)
3. [Insertion](#Insertion)
4. [Submission and Grading](#Submission-and-Grading)
5. [Tips](#Tips)

## B-tree

### Brief history

In the class, you learned Binary Search Trees (BSTs). In theory, the time-
complexity is close to optimal, but in reality they are not that good. Why?

The underpinning of such suboptimal performance of BSTs is related to
the _memory hierarchy_. To be more specific, not all memory locations
are accessed equally fast. Some are accessed fast (_fast_ memory,
e.g., a CPU cache), while the others are accessed slow (_slow_ memory,
e.g., DRAM). In BST, every time you visit the node, you perform the
comparison operation. Based on the comparison result, you visit the
next node, either the left or the right node, which involves to fetch
the next node from _slow_ memory. This memory access per every node
visit may severely downgrade the performance. 

However, in the B-tree, you will be able to load many keys at once
from _slow_ memory, and perform multiple comparisons while the keys
are loaded in the _fast_ memory. Thus, compared to BST, B-tree does
not need to access _slow_ memory per comparison/visit, because
multiple comparison/visit operations can be performed with a single
_slow_ memory access (followed by multiple _fast_ memory
accesses). The detailed memory hierarchy mechanism is beyond the scope
of this course, and you will learn more in the computer architecture
class!

### Definitions

So what defines a B-tree? B-tree has a special parameter `B`, which determines
the minimum/maximum number of keys that can be held per node. In particular,
given `B`, a node should hold `B-1` to `2*B-1` keys and `K+1` children, where
`K` is the number of keys in that node. One exception is that the root node is allowed
to have smaller number of keys (even a single key is okay).  Note that the
nodes in a B-tree are _perfectly_ balanced, 
which means that the path to every leaf node has
the same length.

## Types

We will take a look at the types:

``` c++
enum class NodeType { LEAF, INTERNAL };

template<typename T, size_t B = 6>
struct BTreeNode;

template<typename T, size_t B = 6>
struct BTree {
    BTreeNode<T, B>* root = nullptr;

    ~BTree() { if (root) delete root; }

    bool insert(const T&);
    bool remove(const T&);
};

template<typename T, size_t B>
struct BTreeNode {
    NodeType type;
    size_t n;
    std::array<T, 2 * B - 1> keys;
    std::array<BTreeNode *, 2 * B> edges;

    BTreeNode();
    BTreeNode(const T& t);

    bool insert(const T& t);
    size_t get_index(const T& t);

    static std::pair<BTreeNode*, size_t> search(BTreeNode<T, B>*, const T& t);
    static void split_child(BTreeNode<T, B>&, size_t);
};
```

A `BTree` has a pointer to a `BTreeNode`. A `BTreeNode` has two
arrays, `keys` and `edges` (holding references to children
nodes). Note that a node does not have a pointer to its parent
node. In fact, they don't have to. An example B-tree, where B=2 looks
like:

```
root: ------+
            |
            v
            [   4    |    7    |    11    ]
           /         |         |           \
          v          v         v            v
[ 1 | 2 | 3 ]    [ 5 | 6 ]   [ 10 ]    [ 13 | 14 | 16 ]
```

In this example, the root node has three keys (i.e., K=3) and 4
children. There are four leaf nodes, where each leaf node has a
different number of keys---from 1 to 3. All the leaf nodes have the
same depth, meaning that the tree is perfectly balanced.

## Insertion

The strategy for insertion is simple. Insert at the root. If a node that you
encounter on the way to the leaf is full ? (i.e., `2*B-1` keys) Then split.

### Inserting a partially full leaf node (`K < 2*B-1`)

If a leaf node that you end up is partially full, then you are
lucky. Just insert the key to a proper position (Note that keys in a
node should be sorted). You can implament and use `get_index()`
function to find the right position in a node, with a given
key. For example:

```
n: --> [ 14 | 25 | 31 | 43 ]
       0    1    2    3

get_index(n, 27) --> 2
get_index(n, 11) --> 0
get_index(n, 45) --> 3
```

### Inserting a full leaf node (`K == 2*B-1`)

If a leaf node is full, there is no room for new item, therefore you should find
a room for a new node. How? By splitting a node. This is possible only if a
direct parent to that node is partially full.

```
            [   4    |    7    ]
           /         |          \
          v          v           v
[ 1 | 2 | 3 ]    [ 5 | 6 ]   [ 13 | 14 | 18 ]*

```

If we are inserting 16 to this B-tree, it will end up in the `*` node, which is
a full leaf node. To make a room for this node, we split this tree by pulling up the
middle item to the parent:

```
            [   4    |    7    |    14    ]
           /         |         |           \
          v          v         v            v
[ 1 | 2 | 3 ]    [ 5 | 6 ]   [ 13 ]       [ 18 ]*

```

Finally, you can insert 16 to the node `*`.

```
            [   4    |    7    |    14    ]
           /         |         |           \
          v          v         v            v
[ 1 | 2 | 3 ]    [ 5 | 6 ]   [ 13 ]    [ 16 | 18 ]

```

### Ensuring the nodes are not full

In order to split a child node, the parent should never be full. Otherwise there
will be no room for a pulled-up key. Thus, on your search path, if a node is full,
you should split it before advancing to next level.

Here are the list of functions that are relevant to insertion. You only need to
fill in the following functions to pass the insertion test.

* `BTreeNode::insert`
* `BTreeNode::get_index`
* `BTreeNode::split_child`

## Deletion

Next, you will implement the deletion function. The relevant functions are:

* `BTreeNode::remove`
* `BTreeNode::try_borrow_from_sibling` (Implement this only if necessary)
* `BTreeNode::borrow_from_right`
* `BTreeNode::borrow_from_left`
* `BTreeNode::merge_children`

In the following, we outline two operations that are crucial to B-tree
deletion: borrowing and merging. It's your job to come up with a fully
functioning deletion algorithm based on these operations.

### Borrowing

Recall B-tree invariant: Each node should contain at least B-1 keys. Borrowing
allows a node to borrow a key from its sibling to prevent underflow.

Given a B-tree (B=2), suppose we want to delete 13.
```
            [   4    |    7    |    14    ]
           /         |         |           \
          v          v         v            v
[ 1 | 2 | 3 ]    [ 5 | 6 ]   [ 13 ]    [ 16 | 18 ]
```
Unfortunately, the node only has 1 key, hence removing 13 from the tree will
violate the B-tree invariant. Hopefully, it has siblings that have enough
keys. Before deleting 13, it can borrow a key from its sibling.
```
            [   4    |    7    |    16    ]
           /         |         |           \
          v          v         v            v
[ 1 | 2 | 3 ]    [ 5 | 6 ]   [ 13 | 14 ]   [ 18 ]
```
The key 16 is moved to its parent, and the key 14 is moved to the target
child that contains the target key (13). Now we can safely remove the key 
from the B-tree.
```
            [   4    |    7    |    16    ]
           /         |         |           \
          v          v         v            v
[ 1 | 2 | 3 ]    [ 5 | 6 ]   [ 13 ]         [ 18 ]
```

### Merging

We saw that borrowing allows to move key around the neighboring siblings 
to maintain the B-tree invariant. However, what if there is no neighboring
sibling with spare keys? In such cases, we leverage merging operation to
merge two siblings.

Suppose we want to remove 13 in the given B-tree. As you can see, the node
with key 13 has no neighboring sibling with enough keys.
```
            [   4    |    7    |    16    ]
           /         |         |           \
          v          v         v            v
[ 1 | 2 | 3 ]      [ 5 ]     [ 13 ]         [ 18 ]
```
Merging takes two neighboring siblings, both with B-1 keys, and a parent key
in the middle (in this case, the 16) and merges them into one full node with
2*B-1 keys:
```
            [   4    |    7    ]
           /         |          \ 
          v          v          v
[ 1 | 2 | 3 ]      [ 5 ]     [ 13 | 16 | 18 ]
```
Finally, we can safely remove 13 from the merged node:
```
            [   4    |    7    ]
           /         |          \ 
          v          v          v
[ 1 | 2 | 3 ]      [ 5 ]     [ 16 | 18 ]
```

## WARNING: The keys and the edges should always start from 0. Don't leave empty spaces in the beginning of the keys or edges!
Compact each node after you process it. For example, consider your are
trying to delete 3 in the given node (note B = 3, hence each node can hold
up to 5 keys):
```
[ 1 | 2 | 3 | 4 | - ]
```

After deleting 3, the node should look like:
```
[ 1 | 2 | 4 | - | - ]
```

Note 4 is moved to left.

## Submission and Grading

### Testing your own programs

In `04-btree` directory, you run the following commands to compile your own
implementation.

```
$ pwd
/xxx/xxx/xxx/04-btree
$ mkdir build
$ cd build
$ cmake ../
$ make
$ ls tests/btree_test
./test/btree_test
$ ./tests/btree_test
[...]
```

If you've all done correctly, the output will look like:


```
===============================================================================
All tests passed (XX assertions in XX test cases)

```

and you are ready to submit!

### Testing deletion

```
$ ./tests/btree_delete_test
[...]
```

If you've all done correctly, the output will look like:


```
===============================================================================
All tests passed (XX assertions in XX test cases)

```

### Submission

Prepare your submission with following commands:

```
$ pwd
04-btree
$ ./prepare-submit.sh
[*] Remove tar file...
[*] Compress files...
./include/btree.hpp
[*] Successfully Compressed!
[*] Done! You are ready to submit
```

Upload `assign4.tar.gz` to the submission server. The address of the submission
server isn't changed since last assignment.

### Grading

You will get a _full_ credit, if all tests in `btree_test` and `btree_delete_test`
pass, *AND* valgrind finds no memory leaks *AND* valgrind reports no memory errors.

## Tips

We provide print function (i.e., `operator<<`) for `BTree` type. 
For example, you can print a B-tree by:

``` c++
#include <iostream>
#include <vector>
#include <random>

#include "btree.hpp"

int main(int argc, char *argv[]) {
    BTree<int, 2> btree;
    std::vector<int> xs;

    for (auto i = 1; i <= 20; i++)
        xs.emplace_back(i);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(xs.begin(), xs.end(), g);

    for (auto i : xs)
        btree.insert(i);

    std::cout << btree << '\n';

    return 0;
}
```

This would print, for example:
``` text
[10|14] 
[2|4|7] [12] [18] 
[1] [3] [5|6] [8|9] [11] [13] [15|16|17] [19|20] 
```
