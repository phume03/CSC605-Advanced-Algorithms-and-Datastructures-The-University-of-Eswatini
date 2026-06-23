# Performance Analysis and Implementation of Advanced Searching, Sorting, and Tree Algorithms #

![Dilbert Engineering Thought Algorithm](./Dilbert%20Engineering.png)

Given a list of elements {a1 , a2 ,…, an }, [sorting](https://www.britannica.com/technology/sorting-algorithm) is a procedure that rearranges the elements of the array such that for any two elements in the sorted list, ai and aj, ai < aj. It may be noted that an array with a single element is deemed to be sorted. The process is carried out to facilitate [searching](https://adacomputerscience.org/topics/searching). A sorted array is easy to search and maintain. Sorting can be classified in many ways. According to [Harsh Bhasin, in Algorithms Design & Analysis](https://www.google.com/books/edition/Algorithms/BEE7jgEACAAJ?hl=en), it can be: 

| Characteristic | Definition | Algorithms |
|:-----------------:|:------------|:------------|
|internal | Internal sorting refers to sorting data that can fit entirely in the main memory of a computer system. It involves manipulating the data within the main memory itself and does not require additional external storage devices. Internal sorting is commonly used when sorting relatively small datasets that can be easily accommodated in the memory. | Bubble Sort, Insertion Sort, Quick Sort |
| external | External sorting refers to the sorting of data that is too large to fit in the main memory of a computer system and must be stored on external storage devices, such as hard drives. It involves dividing the data into smaller chunks, sorting each chunk individually, and then merging the sorted chunks to obtain the final sorted result. External sorting is typically used when dealing with significantly large datasets that exceed the available memory capacity. | Merge Sort (large datasets >50GB, 8GB RAM) |
| in place | The in-place algorithms are those that don’t need any auxiliary data structure in order to transform the input data. Basically, it means that the algorithm doesn’t use extra space for input manipulation. It practically overrides the input with the output. However, a small constant extra space used for auxiliary variables is allowed. The complexity of this space is in most cases O(log n), although sometimes anything less than linear is allowed. | Sorting, Searching, Arrays & Strings, Linked Lists, Heap Algorithms |
| not in place | Out-of-place algorithms are algorithms that require extra memory proportional to the input size (usually O(n) or more) to produce the result. They create additional data structures instead of modifying the input in place. | Merge Sort, Counting Sort, Radix Sort, Bucket Sort, Most Functional Programming List Operations, String Reversal by Creating a New String. |
|linear | Linear algorithms are characterized by their linear growth in the number of inputs, making them efficient for problems with a small number of inputs. | Iterating through an array, finding the maximum element, simple search |
| quadratic | Quadratic algorithms, on the other hand, have a quadratic growth in the number of inputs, which can lead to significant increases in computational time as the size of the input increases. | bubble sort, nested iteration, pairwise comparisons, 
|classification on the basis of memory requirements| This looks at the auxiliary (extra) space an algorithm needs to run, excluding the input data itself.In-Place Algorithms: These require a constant amount of extra memory, typically $O(1)$. They modify the array directly. Out-of-Place Algorithms: These require extra memory proportional to the size of the input, typically $O(n)$, to hold temporary data. This one is repeated from above. | Examples of In-place Algorithms: Bubble Sort, Insertion Sort, Selection Sort, Heap Sort; Examples of Out-of-Place Algorithms: Merge Sort, Radix Sort |
|classification based on the number of comparisons| This measures how many times the algorithm has to compare two keys to determine their relative order. It directly affects the Time Complexity. Quadratic Comparisons $O(n^2)$: Algorithms that compare almost every element with every other element in the worst/average cases. Log-Linear Comparisons $O(n \log n)$: Highly efficient algorithms that minimize comparisons using divide-and-conquer or tree structures.| Examples of Quadratic Comparisons: Bubble Sort, Selection Sort, Insertion Sort; Examples of Log-Linear Comparisons: Merge Sort, Heap Sort, Quick Sort |
classification based on the number of swaps| Swapping or moving elements in memory can be expensive, especially if the data objects are large. **High Swap Count O(n^2):** Algorithms that constantly shuffle adjacent or distant elements. **Minimal/Optimized Swaps O(n):** Algorithms designed to minimize writes to memory. **No Swaps (Data Copying):** algorithms that do not "swap" elements; instead, reads from one array and writes sequentially into a temporary array. | Examples of High Swap Count: Bubble Sort, Examples of Minimal or optimized swaps: quick Sort; Selection Sort is famous for making at most O(n) swaps because it finds the absolute minimum before moving anything; Examples of No Swaps: Merge Sort |
|use of recursion| Recursive Algorithms: These solve the problem by breaking it down into smaller sub-problems of the same type, utilizing the system call stack. Iterative Algorithms: These rely strictly on loops (for, while) to sort the data, making them safer against stack overflow errors. | Examples of Recursive Algorithms: Merge Sort, Quick Sort.; Examples of Iterative Algorithms: Bubble Sort, Insertion Sort, Selection Sort.|
|adaptability| An algorithm is adaptive if its running time changes (improves) based on whether the input array is already partially or fully sorted.Adaptive: It recognizes pre-sorted data and terminates early, reducing its time complexity (often down to O(n)). Non-Adaptive: It performs the exact same number of operations and comparisons regardless of how well-ordered the initial data is. | Examples of Adaptive Algorithms: Insertion Sort, Optimized Bubble Sort. Examples of Non-Adaptive Algorithms: Selection Sort, Merge Sort, Heap Sort.|
|stable sort| A sorting algorithm is stable if it preserves the original relative order of equal elements (keys). This is crucial when sorting complex data objects by multiple criteria (e.g., sorting by "First Name", then by "Last Name"). Stable: Equal elements remain in their original relative positions. Unstable: Equal elements may have their relative order scrambled during the sorting process. | Examples of Stable Algorithms: Merge Sort, Insertion Sort, Bubble Sort. Examples of Unstable Algorithms: Quick Sort, Heap Sort, Selection Sort. |

<small>The data in the table was collected from various sources.</small>

[Ananya Levitin, in Introduction to the Design and Analysis of Algorithms](https://www.google.com/books/edition/Introduction_to_the_Design_Analysis_of_A/dQeqKQEACAAJ?hl=en) states that the searching problem deals with finding a given value, called a search key in a given set. There is no single algorithm that fits all situations.



## PART A: Algorithm Complexity and Analysis ##
### Task 1 -- Comparative Complexity Analysis ###
Given 4 algorithms, comprising of 2 search algorithms and 2 sorting algorithms, we have run simulations using randomly generated sets or inputs of 1,000; 10,000; and 100,000 elements and collected the running time for each algorithm given those sets as input. Then, we have tabulated the results of the executions.

The chosen algorithms are as follows:

#### SEARCHING: BINARY AND INTERPOLATION ####
##### Binary Search: ##### 

![Binary Search Illustration](./Task%201/BinarySearch.webp)

[Binary search](https://www.geeksforgeeks.org/dsa/binary-search/) is a searching algorithm that works by comparing a search key (let us call it "K"), with a given array's (let us call it "A" of size n) middle element (let us call the middle index m where m = n/2, and so the middle element is A[m]). If a match is found, the algorithm stops. 

Otherwise, the same operation is repeated recursively (or iteratively depending on your implementation); for the first half of the array if K < A[m]; and, for the second half of the array if K > A[m]. For this algorithm to work, the array A must be sorted in ascending order i.e. lowest value elements first and largest value element last.

We will be timing the execution time of the algorithm to represent efficiency. However, it is said that the standard way to analyze the efficiency of the binary search algorithm is to count the number of times the search key (K) is compared with any element of the array; initially and during the subsequent recursive calls.

Binary search is an optimal searching algorithm if the search operations are restricted to comparisons between keys. However, [interpolation search](https://www.geeksforgeeks.org/dsa/interpolation-search/) and [hashing search](#) are more efficient than binary search, with the latter not even requiring that the array to be searched be sorted.

Running Binary Search on some random positive integer arrays of different sizes we get the following results:

When K is in A:
| N | T (microseconds)|
|:---|:---:|
| 1,000 | 0 |
| 10,000 | 0 |
| 100,000 | 0 |

When K is not in A:
| N | T (microseconds) |
|:---|:---:|
| 1,000 | 0 | 
| 10,000 | 0 |
| 100,000 | 0 |

Running Binary Search on the same random positive integer arrays as above of different sizes, K randomly chosen in A, and the search procedure repeated 100000 times we get the following results:

When K random:
| N | T (microseconds) |
|:---|:---|
| 1,000 | 13,901 |
| 10,000 | 17,788 |
| 100,000 | 20,059 |



##### Interpolation Search: #####
Interpolation search is said to be a search algorithm that is similar to, if not a refinement of, binary search. It searches by considering some key (let us say "K") and an array (let us say "A") where the key could be found. It then uses a calculated guess as to where K is in A, rather than taking a first assumption of A[m] (the middle value). The guess could be the middle index, but we would assume it is not, and in fact, we can assume it is some index that is much more accurate than the middle value e.g. in some range, from the left 1/3 and or 2/3 from the right, of the total length or size of A. This cuts the problem possibly by more than half! 

For interpolation search to work, it makes the assumption that the data in A is evenly/uniformly distributed across a range; e.g. the data might all be real numbers (floating points or double) which are greater than or equal to zero and less than one, with any number within this range equally likely to occur. It also assumes that the data is sorted - suppose in ascending order (like binary search)!

In the worst case, interpolation search takes linear time. This worst case occurs only if the
assumption of uniform distribution is deeply wrong. On average, interpolation search takes time
in O(log (log n)).

Running Interpolation Search on some random positive integer arrays of different sizes we get the following results:

When K is in A:
| N | T (microseconds) |
|:---|:---:|
| 1,000 | 0 |
| 10,000 | 0 |
| 100,000 | 0 |

When K is not in A:
| N | T (microseconds) |
|:---|:---:|
| 1,000 | 0 |
| 10,000 | 0 |
| 100,000 | 0 |

Running Interpolation Search on the same random positive integer arrays as above of different sizes, K randomly chosen in A, and the search procedure repeated 100000 times we get the following results:

When K random:
| N | T (microseconds) |
|:---|:---|
| 1,000 | 8,997 |
| 10,000 | 10,190 |
| 100,000 | 9,691 |



#### SORTING: QUICK AND HEAP ####
##### Quick Sort: #####
This is a sorting algorithm that is classified under the divide and conquer group of algorithms. This is because quick sort sorts an array by picking an element in the array, known as a pivot. It then breaks down or divides the rest of the array into two, with one group to the left of the pivot and another to the right of the pivot. Specifically, all elements smaller than the pivot are to the left and all elements larger than the pivot are to the right. It repeats the divide process until any given pivot has no further partitions, thus the element under consideration is sorted. 

Finally, it merges this result with all previous results, known as combining the solutions. Thusly, the final array will be considered to be sorted. Another example of an algorithm in this class is merge sort. Quick sort can run in-place, which  as a  It sorts in-place, which means that only the original array datastructure is needed to perform the sorting operation. It is also a recursive algorithm, which means it can call itself during execution, since subsequent steps are repetitive. The alternative is running iteratively.

Quick Sort has an average case running time of O(n log n) and a worst case running time of O(n^2).

Running Quick Sort on integer inputs of different sizes we get the following results:

| N | T (microseconds) |
|:---|:---|
| 1,000 | 209 |
| 10,000 | 2,178 |
| 100,000 | 21,374 |



##### Heap Sort: #####
Anaya Levitin likes to describe the heapsort algorithm alongside its associated data structure, the heap. A heap is a tree datastructure, specifically, it is a binary tree with keys assigned to its nodes, one key per node. The heap maintains a structure property and a heap order property. By structure, we mean that a heap is a binary tree that is completely filled, with the exception of the bottom level. By heap order we mean that the key of the parent node is always greater than or equal to the keys of its children (descendants). One of the most important uses of the heap is in the implementation of priority queues.

![Heap Sort 00](./Task%201/Heap%20Sort%2000%20-%20heapify%20a%20tree%20with%20just%20three%20elements.png)

[Cormen et. al.](https://books.google.com/books/about/Introduction_To_Algorithms.html?id=NLngYyWFl_YC) expand on the definition of the heap to say that there are two types of heap, and those are the max-heap, and the min-heap.

![Heap Sort 01](./Task%201/Heap%20Sort%2001.png)

Heapsort is a sorting algorithm that makes use of priority queues ADT, or the heap datastructure. It is employed by constructing a max-heap for a given array that needs sorting, and then applying the maximum root-deletion operation to the heap. This takes advantage of the heap property which states that the root node of the heap is ALWAYS the greatest (max heap) element of the tree. By performing maximum deletes, and placing the deleted root node in the last index (decreasing heap size by 1) of the underlying array datastructure we essentially return the array elements sorted in a ascending order. 

![Heap Sort 02](./Task%201/Heap%20Sort%2002.png)

In his book, [Datastructures and Algorithm Analysis in Java](https://books.google.com/books/about/Data_Structures_and_Algorithm_Analysis_i.html?id=IZguAAAAQBAJ), Mark A. Weiss gives a different implementation of heapsort which uses a min-heap datastructure and a second array to store the values removed from the heap, which is not in-place.

![Heap Sort 03](./Task%201/Heap%20Sort%2003.png)

Heapsort is said to have a running time of O(n log n) in all cases.

Running Heap Sort on integer inputs of different sizes we get the following results:

| N | T (microseconds) |
|:---|:---|
| 1,000 | 215 |
| 10,000 2,884 |
|100,000 | 28,718 |

![Heap Sort 04](./Task%201/Heap%20Sort%2004.png)



## PART B: Searching and Sorting Algorithms ##
### Task 2 -- Algorithm Implementation and Optimization ###
#### SORTING: Counting Sort ####

![Counting Sort](./Task%202/Counting%20Sort.webp)

The counting sort algorithm was invented by [H. H. Seward in 1954](https://archivesspace.mit.edu/repositories/2/archival_objects/463314). Counting sort is a sorting algorithm that operates on an input array (lets say A) of positive integer values (0 to k). Rather than compare the array values against each other, counting sort builds up a frequency table (lets say B) for the values in the array A, having determined the array range, and then builds a cumulative frequency table array (C) using the frequency table B. Finally, the cumulative frequency table determines, for each element x in the array, the number of elements less than x. Thus, x can be placed directly into its position in the output array. Counting sort is also known as distribution counting because sums of frequencies are called a distribution in statistics. --- 

Counting sort has worst-case running time complexity of O(k+n).

Running Distribution Counting Sort on integer inputs of different sizes we get the following results:

N = 1,000 T=1006microseconds; N=10,000 T=1005microseconds; N=100,000 T=3014microseconds

| Algorithm/N | Worst Case |
|-------------|------------|
| Counting Sort | O(n+k) |
| Quick Sort | O(n log n) |



#### Exponential Search ####

![Exponential Search](./Task%202/Exponential-Search.webp)

Exponential search is also known by the names "doubling search", "galloping search", and "struzik search". It is considered to be an advanced, specialized algorithm. It is also classified as unbounded search domain algorithm, as its best application is on search domains who's limit (bound) is not known before the search is initialized e.g. an unknown size array. It works by purposefully considering the search domain as a limited space, for example for some array A of unknown size and the search key K, exponential search will purposefully consider the bound of n = 1, and begin to search for K in this space. If the search key is not found in this initial bound domain, the algorithm doubles the search domain i.e. n = n * 2, thus A [0... 2n - 1] and repeats the search process. Finally, if the key is still not found, doubling search will repeat the double process, searching for K until it is found or the space is exhausted. Remember the space is not infinite, maybe just arbitrarily large or unknown before hand.

Exponential search also assumes that the input array is sorted, even if the domain limit is large or unknown.

| Algorithm/N | Worst Case |
|-------------|------------|
| Exponential Search | O(log i-K); where i-K is index of K in the list |
| Binary Search | O(log n) |

Running Exponential Search on some random positive integer arrays of different sizes we get the following results:

When K is in A:
| N | T (microseconds) |
|:---|:---:|
| 1,000 | 0 |
| 10,000 | 0 |
| 100,000 | 0 |

When K is not in A:
| N | T (microseconds) |
|:---|:---:|
| 1,000 | 0 |
| 10,000 | 0 |
| 100,000 | 0 |

Running Exponential Search on the same random positive integer arrays as above of different sizes, K randomly chosen in A, and the search procedure repeated 100000 times we get the following results:

When K random:
| N | T (microseconds) |
|:---|:---|
| 1,000 | 17,781 |
| 10,000 | 21,686 |
| 100,000 | 23,671 |



## PART C: Tree Data Structures ##
According to [Aho et. al.](https://books.google.com/books/about/Data_Structures_and_Algorithms.html?id=AstQAAAAMAAJ) a tree is a special graph datastructure; remembering that a graph G is a collection of nodes called vertices V, that are connected or linked by edges E. Graphs have special properties, they can be directed (where the direction of traversal between nodes is significant or matters), undirected (where the direction of traversal between nodes is insignificant, or does not matter), weighted (the traversal path between any two nodes has an associated value/weight, which can also be considered a cost), cyclic (where there exists a path, or a consecutive set of vertices connecting nodes, through the graph that starts and ends at the same node), acyclic (where there exists no cycle in the graph), connected (where every node of the graph is connected to every other node by some path) or disconnected (where there exists some node, or collection of vertices, that are not connected to each other by an edge forming partitions). The tree is thus said to be an acyclic, connected, and undirected graph.

![Tree Data Structure](./Task%203/root.webp)

The top most (or primary) node in the tree is distinguished as a root. All nodes have a base parent-child relation in the tree; where the top node is the parent and subsequent nodes from it are known as its children. All nodes beyond the children of a given parent are known as its descendants (children are first descendants), and all nodes beyond the parent of a child node are known as ancestors (parents are first ancestors). Nodes that share a parent are known as siblings. A subtree is formed by considering some or any one child node from a given parent as a root node to all the descendants connected to it. Any node that has no child is considered a leaf node, as it is at the bottom most part of the tree.

In a tree, the longest path from a node to the leaf is considered the height. Thus the height of a tree is the longest path from the root node to a leaf. The depth is the number of edges from the root node to any given node in the tree. 

All the nodes of a tree can be systematically ordered, the three most important orderings are called; preorder, inorder and postorder. Such that, if we consider T to be a tree with root n, a left subtree T1, and a right subtree T2. 

The preorder traversal of the nodes of the T is: the root n of T, followed by the nodes of T1 in preorder, and then the nodes of T2 in preorder. 

The inorder traversal of the nodes of T is: the nodes of T1 in inorder, followed by root node n, and then the nodes of T2 inorder. 

Finally, the postorder traversal of the nodes of T is: the nodes of T1 in postorder, then followed by the nodes of T2 in postorder, and then the root node n of T.

Some common examples of trees are genealogies and organization charts, and less common examples (or industry specific) are use in analyzing electrical circuits, in the representation of mathematical formulas (such as remembering BODMASS rules for calculations), and in compilers and interpreters to represent the syntactic structure of source programs. 



### Task 3: Implementation and Application of Tree Structures ###
#### Option 1 - AVL TREE ####
An AVL (Adelson Velsky Landis) tree is a binary tree that is height balanced. A binary tree is a special kind of tree where by all nodes with ancestors have atleast one child and no node can have more than two children. Any node with no children is a leaf. For the binary tree (T) to be height balanced we must have that for each node x of T, the height of the left subtree (xL) and the height of the right subtree (xR) differ by at most 1 (i.e. -1, 0, or 1). Thus, in the implementation of an AVL tree from a binary tree, an extra attribute h is maintained in each node x of T. Where h is the height of node x.

To insert into an AVL tree, we ﬁrst place a node into the appropriate place in a binary tree, as a leaf node. After an insertion, the tree might no longer be height balanced. Speciﬁcally, the heights of the left and right children of some node might differ by |2| (xL - xR = -2 or +2). The balance requirement is enforced or met by performing a rotation transformation on the subtree rooted at the unbalanced node that is the closest to the newly inserted leaf; or simply, where the imbalance is recorded and if several, starting at the substree closest to the leaf. There are four types of rotation transformation that can be applied.

![AVL Tree RL Rotation 01](./Task%203/right_left_rotation_127.webp)

![AVL Tree RL Rotation 02](./Task%203/right_left_rotation_128.webp)

![AVL Tree RL Rotation 03](./Task%203/right_left_rotation_129.webp)

![AVL Tree RL Rotation 04](./Task%203/right_left_rotation_130.webp)

* There is the single right rotation (R-rotation). It is performed after a new key is binary inserted into the left subtree of the left child (LL or outside); where the balance was previously +1 prior to the insertion. It tries to move a left child node to the right of a binary node, or makes a root node a right node, while the previous left node is made the root. 

* There is the single left rotation (L-rotation). It is performed after a new key is binary inserted into the right subtree of the right child (RR or outside); where the balance was previously -1 prior to the insertion.

* There is the double left-right rotation (LR-rotation). This is a combination of the two rotations above (L-rotation on first left subtree and then R-rotation on the resultant subtree). It follows the binary insertion of a new key into the right subtree of the left child (RL or inside); where the balance was previously +1 prior to the insertion.

* Finally, there is the double right-left rotation (RL-rotation). It is performed after a new key is binary inserted into the left subtree of the right child (LR or inside); where the balance was previously -1 prior to the insertion.

After any rotation, the datastructure requirements must hold. 

The acronym AVL represents the last names of the two Russian scientists who invented the datastructure in [1962; G. M. Adelson-Velsky and E. M. Landis](https://www.mathnet.ru/php/archive.phtml?wshow=paper&jrnid=dan&paperid=26964&option_lang=eng). This is just an interesting tid-bit.



#### Option 4 - B-TREE ####
A B-tree or a balanced tree is a specialized tree data structure; it has the typical constraints on a graph for forming a tree. It is special because rather than any one parent in the tree being limited to atmost two children, parents here can have more than two children (from a few to thousands). This is known as the "branching factor" or "order". Visually, we say that a B-tree in utilization is "short and fat" (due to the increased branching factor), as compared to the more common binary tree which is "thin (growing outwards slowly, by branching by at most 2 at each level) and tall (height, or growing more downwards with insertions)". As there exists an even more specialized datastructure known as the B+ Tree, it is important to specify that every node in the B Tree carries its complete information in addition to the data identifying "key". The B+ Tree only carries data in the leafs, and internal nodes only carry key references.

![B Tree Order 5](./Task%203/BTree.png)

Formally, a B-tree T is a rooted tree with the following properties:

1. Every node x has the following attributes:
    a. n, the number of keys currently stored in node x
    b. c, the keys themselves, stored in nondecreasing order
    c. leaf, a boolean value that is TRUE if x is a leaf and FALSE if x is an internal node.

2. Each internal node x also contains n + 1 pointers to its children. Leaf nodes have no children, and so their child attributes are undeﬁned.

3. The keys, c, separate the ranges of keys stored in each subtree

4. All leaves have the same depth, which is the tree’s height h.

5. Nodes have lower and upper bounds on the number of keys they can contain. We express these bounds in terms of a ﬁxed integer t >= 2 called the minimum degree of the B-tree:
    a. Every node other than the root must have at least t - 1 keys. Every internal node other than the root thus has at least t children. If the tree is nonempty, the root must have at least one key.
    b. Every node may contain at most 2t - 1 keys. Therefore, an internal node may have at most 2t children. We say that a node is full if it contains exactly 2t - 1 keys.  
    
The simplest B-tree occurs when t = 2. Every internal node then has either 2, 3, or 4 children, and we have a 2-3-4 tree. In practice, however, much larger values of t yield B-trees with smaller height. A simpler B-Tree node is presented by Adam Drozdek in Data Structures and Algorithms in Java (p300, search on p304, p306 for insert, p309 for deleting). The insert and delete algorithm are as follows:

````
 BTreeInsert (K)
    find a leaf node to insert K;
    while (true)
        find a proper position in array keys for K;
        if node is not full
            insert K and increment keyTally;
            return;
        else split node into node1 and node2;// node1 = node, node2 is new;
            distribute keys and references evenly between node1 and node2 and
            initialize properly their keyTally’s;
            K = middle key;
            if node was the root
                create a new root as parent of node1 and node2;
                put K and references to node1 and node2 in the root, and set its keyTally to 1;
                return;
            else node = its parent;// and now process the node’s parent;
````

and the corresponding delete is:

````
 BTreeDelete(K)
    node = BTreeSearch(K,root);
    if (node != null)
        if node is not a leaf
            find a leaf with the closest predecessor S of K;
            copy S over K in node;
            node = the leaf containing S;
            delete S from node;
        else delete K from node;
        
        while (true)
            if node does not underflow
                return;
            else if there is a sibling of node with enough keys
                redistribute the keys between node and its sibling;
                return;
            else if node’s parent is the root
                if the parent has only one key
                    merge node,its sibling, and the parent to form a new root;
                else merge node and its sibling;
            
                return;
            else merge node and its sibling;
                node = its parent;
````

According to [Hubbard, J.](https://books.google.com/books/about/Data_Structures_with_Java.html?id=meJQAAAAMAAJ), to insert a record with key k using a B-tree index of order m, you have to apply the following algorithm:

 1. If the tree is empty, create a root node with two dummy leaves, insert k
 there, and return true (indicating that the insertion was successful).
 2. Let x be the root.
 3. Repeat steps 4–6 until x is a leaf node.
 4. Apply the binary search to node x for the key ki,
 , where ki–1 < k <= k (regarding k0 = –infinity  and km = infinity).
 5. If ki = k, return false (indicating that the insertion was unsuccessful because a record with key k already exists, and keys should be unique).
 6. Let x be the root of subtree Si
 7. Add the record to disk.
 8. Insert k (with the record’s disk address) into x between ki–1 and ki
 9. Add a dummy leaf node to x.
 10. If degree(x) = m, repeat steps 11–13 until degree(x) < m.
 11. Let kj be the middle key in node x.
 12. Let u and v be the left and right halves of x after removing kj from x.
 13. If x is the root, create a new root node containing kj
 with subtrees u and v.
 14. Otherwise, insert kj in x’s parent node and attach subtrees u and v.
 15. Return true.
 
 ![Hagar Money Pep-Talk](./Hagar%20Money.png)

 He goes on to say that the deletion algorithm for B-trees is similar to the insertion algorithm. All three algorithms run in time proportional to the height of the tree. But this is not our research consideration. Hubbard's approach differs from others and it was worth noting this, as it seems rather simple. 

* * * 



## Resources ##

* [Cpp](http://www.cplusplus.com/) \(included in source, accessed: 09/07/2018\)

* [IBM](http://www.ibm.com/) \(included in source\)

* [GNU](http://www.gnu.org/)

* [SGI](http://doc.sgi.com/)

* [Packt](https://packtpub.com/)

* [In-Place Algorithm](https://www.geeksforgeeks.org/dsa/in-place-algorithm/)

* [In-Place Sorting](https://www.baeldung.com/java-in-place-sorting)

* [In-Place Algorithms: Understanding in place algorithms](https://www.linkedin.com/pulse/understanding-in-place-algorithms-yashraj-singh-3a7xc)

* [In-place vs out-of-place algorithms](https://www.techiedelight.com/in-place-vs-out-of-place-algorithms/)

* [What are in-place and out-of-place algorithms?](https://www.educative.io/answers/what-are-in-place-and-out-of-place-algorithms)

* [In-place Versus Out-of-place Algorithms](https://www.bohrium.com/en/sciencepedia/feynman/data_structures_and_algorithms_undergraduate-in-place_versus_out-of-place_algorithms?encode__1526=214d4f07715-i96fLTYfSivqnCm%2FvT3T8ZX8TxfKWtScp91CAP9qZT%2Fu%2FWOFMTPSAgisIYiLPp2XjTXZXLTX_GTofTdTZlfikT%3D2XtT%3D9XgTkA9XaC8TX1T%2Fpz_xTK2Pc1TimcTOhvXVff1BtTPgEqTwwAOT_UOTzlA86fogNjoh%2FfYhtSZhuifOuJfTcDDOZXG9uTfTyDT)

* [Quadratic Programming Vs. Linear Programming](https://www.codingdeeply.com/quadratic-programming-vs-linear-programming/)

* [External Sorting vs Internal Sorting](https://www.baeldung.com/cs/sorting-external-vs-internal)

* [What is the Difference Between Internal and External Sorting](https://differencedigest.com/science/computers/what-is-the-difference-between-internal-and-external-sorting/)

* [Searching and sorting algorithms\- OCR](https://www.bbc.co.uk/bitesize/guides/zjdkw6f/revision/1)

* [Searching algorithms](https://adacomputerscience.org/topics/searching)