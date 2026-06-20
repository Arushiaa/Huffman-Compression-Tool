# Huffman Compression Tool

A lossless file compression utility implemented in C++ using Huffman Coding.

## Features

* Compress text files using Huffman Coding
* Decompress encoded files back to the original text
* Interactive command-line interface
* Frequency analysis using maps
* Huffman tree construction using priority queues
* Compression statistics
* Metadata storage for tree reconstruction

## Technologies Used

* C++
* STL
* Priority Queue (Min Heap)
* Binary Trees
* Maps
* File Handling

## How It Works

1. Read input text file
2. Calculate character frequencies
3. Build Huffman Tree
4. Generate Huffman Codes
5. Encode text into binary representation
6. Store metadata and encoded data
7. Reconstruct tree and decode data

## Compilation

```bash
g++ huffman_tree.cpp -o huffman
```

## Run

```bash
./huffman
```

## Sample Menu

```text
===== HUFFMAN COMPRESSION TOOL =====

1. Encode File
2. Decode File
3. Exit
```

## Concepts Demonstrated

* Data Structures
* Greedy Algorithms
* Trees
* Priority Queues
* Recursion
* File I/O
* Memory Management
