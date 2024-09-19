# Simple Garbage Collector in C

This project demonstrates a basic implementation of a simple garbage collector in C. The garbage collector manually manages dynamically allocated memory, tracking each allocation and freeing it when no longer needed.

## Features
- Custom memory allocation (`gc_malloc`) that tracks allocated memory.
- Custom memory freeing (`gc_free`) to free individual allocations.
- Full garbage collection (`gc_collect`) that frees all tracked memory blocks.

## How It Works
The project uses a linked list (`MemBlock`) to keep track of all allocated memory. The `gc_malloc` function allocates memory and stores a reference to the memory block in the list. The `gc_free` function frees a specific memory block and removes it from the list. Finally, the `gc_collect` function simulates a garbage collector, freeing all remaining allocated memory.

## Project Structure
```plaintext
.
├── main.c      # The main code with garbage collector logic
└── README.md   # Project documentation
```

## Functions

### `gc_malloc(size_t size)`
Allocates memory of the specified size and tracks it. This is a wrapper around `malloc`.

### `gc_free(void *ptr)`
Frees the specified memory block and removes it from the tracked list.

### `gc_collect()`
Frees all allocated memory blocks. It acts as a simple garbage collector that cleans up all memory still being tracked.

## Usage

### 1. Compile the Program
Use `gcc` to compile the project:
```bash
gcc main.c -o simple_gc
```

### 2. Run the Program
```bash
./simple_gc
```

### Example Output
The program will allocate memory for an array of integers and a string, print the contents, and then free the memory using the garbage collector.

### Expected output:
```bash
arr[0] = 0
arr[1] = 2
arr[2] = 4
arr[3] = 6
arr[4] = 8
arr[5] = 10
arr[6] = 12
arr[7] = 14
arr[8] = 16
arr[9] = 18
```

## Next steps

- Adding reference counting.
- Automatically invoking `gc_collect` at specific intervals or based on memory usage.

## Limitations
- This garbage collector is manually triggered. It does not automatically detect when memory is no longer in use.
- It does not handle cyclic references or advanced memory management patterns.