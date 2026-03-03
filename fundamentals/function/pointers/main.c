#include <stdio.h>

// Function to print "Hello, <name>!"
void hello_world(const char* name) {
    printf("Hello, %s!\n", name);
}

// Function that takes a function pointer and an argument to pass to the function
void execute_function(void (*func)(const char*), const char* arg) {
    // Call the function passed as an argument with the provided argument
    func(arg);
}

int main() {
    // Pass the hello_world function and a name to execute_function
    execute_function(hello_world, "World");

    return 0;
}
