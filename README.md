# External Merge Sort (Senior C++ Challenge)

This project is a high-performance implementation of an external sorting algorithm designed to handle datasets larger than available RAM.

## 🎯 The Challenge
The goal is to sort a **1GB text file** containing `double` format numbers (one per line) under the following constraints:
*   **RAM Limit:** Maximum **100MB**.
*   **Performance:** Must complete within **25-30 minutes** (2GHz single-core baseline).
*   **Data:** Handling scientific notation (e.g., `8.33891e+307`).

## 🧠 Engineering Approach
To solve this, I implemented a classic **Two-Phase External Merge Sort**:

1.  **Phase 1: Divide & Conquer (Split-Sort)**
    *   The 1GB file is read in chunks that fit into the 100MB RAM limit.
    *   Each chunk is sorted in-memory using `std::sort` and flushed to disk as a temporary binary file.
    *   *Optimization:* Using binary format for temporary files reduces I/O overhead and avoids repetitive string-to-double parsing.

2.  **Phase 2: Multi-way Merge**
    *   The algorithm opens all temporary chunks simultaneously.
    *   A **Min-Heap (Priority Queue)** is used to efficiently pick the smallest element among the current headers of all chunks.
    *   The smallest element is written to the output file, and the next element from the corresponding chunk is loaded.

## 🛠 Features
*   **File Generator:** Includes a utility to generate 1GB test files with random `double` values.
*   **Memory Efficiency:** Strictly stays under the 100MB threshold by controlling buffer sizes.
*   **Robust Parsing:** Correctly handles various `double` formats, including scientific notation.

## 🚀 Execution
The program accepts command-line arguments as required:
```bash
./External_MergeSort <unsorted_file> <sorted_file>
```
## 💎 Senior-Level Optimizations (How I hit the target)

To meet the 25-minute target on a single core, several low-level optimizations were applied:

### 1. High-Performance I/O
*   **Custom Buffering:** Instead of relying on default `std::ifstream` behavior, I use large intermediate buffers to minimize the number of system calls (`read`/`write`).
*   **Zero-Copy Mentality:** Data is moved directly from the input buffer to the sorting vector to avoid redundant allocations.

### 2. Fast String-to-Double Conversion
Standard `atof` or `sscanf` are slow due to locale-dependency. This implementation uses **`std::from_chars`** (C++17), which:
*   Is up to 10x faster than `stringstream`.
*   Is non-allocating and non-throwing.

### 3. Binary Intermediate Storage
Writing 1GB of text back and forth is expensive. 
*   **Text (Input) → Binary (Chunks) → Text (Output)**
*   Binary chunks are fixed-size, making them extremely fast to read during the Merge phase without further parsing.

### 4. Memory Management Strategy
With a 100MB hard limit:
*   **Buffer Calculation:** `(100MB - Binary_Heap_Size) / 2` is allocated for the active reading buffer to ensure no swapping occurs.
*   **In-place sorting:** We sort the vector of doubles directly, which is cache-friendly and has minimal overhead.

## 🛠 Building and Running

### Prerequisites
*   C++17 compatible compiler (MSVC 2022+, GCC 11+, or Clang)
*   CMake 3.15+

### Build
```powershell
cmake -B build
cmake --build build --config Release
```

## Run Generator & Sorter
```powershell
 1. Generate 1GB test file:
./build/External_MergeSort_Generator input.txt 100000000

2. Sort the file:
./build/External_MergeSort input.txt sorted.txt
```

## Developed as a demonstration of efficient data processing under strict resource constraints.


---
