# fprintf(stderr, ...) vs simple printf(...)

1 - Separation of concerns: Using stderr for error messages helps to separate error output from regular program output. This can be valuable for debugging and troubleshooting, as it makes it easier to identify and filter out error messages in the program's output.

2 - Redirection: By convention, stderr is often left unbuffered, which means that error messages are immediately displayed on the console without delay. This can be important for critical error messages that need immediate attention. On the other hand, stdout is typically buffered, which means that its output may be delayed or buffered until certain conditions are met.

3 - Redirecting output: When users want to redirect the output of a program to a file, they often want to exclude error messages from that file and only capture regular program output. By convention, error messages are sent to stderr, making it easier to redirect only the stdout stream if needed.

In summary, while the output from fprintf(stderr, ...) and printf(...) may appear similar to the user, conventionally using stderr for error messages serves important purposes in terms of separation of concerns, immediate display, and ease of output redirection.