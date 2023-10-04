# HW#2: Binary Search Tree (BST)

* **Due date: 11:59pm, 10/16/2023**
* TA: Sangyun Kim (sangyun.kim@snu.ac.kr)

## Goals

* Get familiar with C++ programming by implementing simple data structures like BST.

* Get to know what is `std::unique_ptr` and how to use it.

* Learn how to implement the simple and easy binary tree before B-tree assignment.


### Table of contents
1. [BST](#BST)
2. [Types](#Types)
3. [Insertion](#Insertion)
4. [Search](#Search)
5. [Deletion](#Deletion)
6. [Submission and Grading](#Submission-and-Grading)

## BST

### Definitions

> A BST is a binary tree where nodes are ordered in the following way:
>
> 1) each node contains one element (also known as data)
>
> 2) the elements in the left subtree are less than the element in its parent node
>
> 3) the elements in the right subtree are greater than the element in its parent node
>
> 4) duplicate elements are not allowed.

## Types

We will take a look at the types:

```c++
template <typename T>
class TreeNode
{
    public:
        T element;
        std::unique_ptr<TreeNode<T>> left;
        std::unique_ptr<TreeNode<T>> right;

        TreeNode<T>(const T& e)
            :element{e}, left{nullptr}, right{nullptr} {}

        ~TreeNode() {}

};


template <typename T>
class BST 
{
    public:
        std::unique_ptr<TreeNode<T>> root = nullptr;

        ~BST() {}

        bool insert(const T& key);
        bool search(const T& key);
        bool remove(const T& key);

    private:
        bool insert(std::unique_ptr<TreeNode<T>>& t, const T& key);
        bool search(std::unique_ptr<TreeNode<T>>& t, const T& key);
        bool remove(std::unique_ptr<TreeNode<T>>& t, const T& key);

        T find_rightmost_key(std::unique_ptr<TreeNode<T>>& t); 
};


```

A `BST` provides all necessary operations for BST and it also has a
pointer to a root node. Then `TreeNode` implements each node, which
has two pointers (one for left and the other for the right children)

![](http://cslibrary.stanford.edu/110/binarytree.gif)

This figure is from http://cslibrary.stanford.edu/110/BinaryTrees.html

Note that a node does not have a pointer to its parent node, and
in this assignement, we will use [std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr) for every pointer pointing `TreeNode`.

Your goal is to fill in all of the `TODO` regions.

## Insertion

The strategy for insertion is simple. 
We start at the root and recursively go down the tree searching for a location to insert a new node.
The property of BST should be always preserved even after the node insertion.

In this assignment, 
if the new node is sucessfully inserted, the function `insert(const T&
key)` returns true, otherwise returns false.


### Insertion Example

Suppose you are given a BST like below. If you attempt to insert a new
node "8" into the tree:

```
    5                  5
   / \    insert(8)   / \  
  3   9      ==>     3   9
                        /   
                       8
```


## Search

Searching in a BST always starts at the root.
We compare a data stored at the root with the element we are searching for (hereafter call this as **KEY**). 
If the element of root is the same with **KEY**, we are done.
If the element of root is smaller than **KEY**, we move on to the left child. Otherwise, move on to the right. 
The recursive structure of a BST yields a recursive algorithm.

In this assignment, 
if **KEY** exists in BST, the function `search(const T& key)` returns true, otherwise returns false.

## Deletion

Deletion is somewhat more tricky than insertion. 

There are several cases to be considered:
A node to be deleted (let us call it as **KEY**)
1) is a leaf;
2) has only one child;
3) has two children.
4) is not in a tree;

In this assignment, 
if the node is sucessfully deleted, the function `remove(const T& key)` returns true, otherwise returns false.


### Deletion Example

Given a BST, we try to delete a node "8" in the tree:

#### case 1: is a leaf;
```
    5                  5
   / \    remove(8)   / \  
  3   9      ==>     3   9
     /   
    8
```
The node "8" is a leaf node, so just delete that node.

#### case 2: has only one child;

Given a BST, we try to delete a node "9" in the tree:

```
    5                  5
   / \    remove(9)   / \  
  3   9      ==>     3   8
     /   
    8
```
The node "9" has only one child, 
so the procedure of deletion is identical to deleting a node from a linked list - we just bypass that node being deleted.


#### case 3: has two children.

Given a BST, we try to delete the node "5" in the tree:

```
    5                  4 
   / \    remove(5)   / \  
  3   9      ==>     3   9
 / \                /   
1   4              1   
```

The node "5" has two children, so we first find the max element from its left subtree 
(let us call it as **L_subtree**). In this case, the node "4" is max.

We then replace the node "5" with the maximum value, "4".
Then delete the node "4" in **L_subtree**.


#### case 4: is not in a tree;

In this case, do nothing :)


## Submission and Grading

### Testing your own programs

In `02-BST` directory, you run the following commands to compile your implementation.

```
$ pwd
/xxx/xxx/xxx/02-BST
$ mkdir build
$ cd build
$ cmake ../
$ make
$ ls tests/BST_test
./test/BST_test
$ ./tests/BST_test
[...]
```

If you've all done correctly, the output should be like this:

```
===============================================================================
All tests passed (XX assertions in XX test cases)

```

### Submission

Before submitting your assignment, you should run the following commands.

```shell
$ pwd
/xxx/xxx/xxx/02-BST
$ ./prepare-submit.sh
[*] Remove tar file...
[*] Compress files...
./include/BST.hpp
[*] Successfully Compressed!
[*] Done! You are ready to submit
```

Please submit the file "assign2.tar.gz" to the submit server.

Submit Server : http://kayle.snu.ac.kr:47474/

## References
1. cppreference.com. std::unique_ptr--[Link](https://en.cppreference.com/w/cpp/memory/unique_ptr)
2. cs.cmu.edu. BST--[Link](https://www.cs.cmu.edu/~adamchik/15-121/lectures/Trees/trees.html)
