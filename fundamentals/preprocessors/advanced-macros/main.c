#include <math.h>
#include <stdio.h>

#define STR(x) #x
#define XSTR(x) STR(x)

#define CAT(a, b) a##b

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

#define SWAP(T, a, b)            \
    do {                         \
        T _swap_tmp_ = (a);      \
        (a) = (b);               \
        (b) = _swap_tmp_;        \
    } while (0)

#define LOG_INFO(fmt, ...) \
    fprintf(stderr, "[INFO] %s:%d: " fmt "\n", __FILE__, __LINE__, __VA_ARGS__)

static inline int abs_int(int x)
{
    return x < 0 ? -x : x;
}

static inline long abs_long(long x)
{
    return x < 0 ? -x : x;
}

static inline float abs_float(float x)
{
    return fabsf(x);
}

static inline double abs_double(double x)
{
    return fabs(x);
}

#define ABS(x) _Generic((x), int: abs_int, long: abs_long, float: abs_float, double: abs_double)(x)

#define COLOR_TABLE(X) \
    X(RED, 31)         \
    X(GREEN, 32)       \
    X(BLUE, 34)

enum Color {
#define X(name, code) COLOR_##name,
    COLOR_TABLE(X)
#undef X
        COLOR_COUNT
};

static const char *color_to_string(enum Color color)
{
    switch (color) {
#define X(name, code) case COLOR_##name: return #name;
        COLOR_TABLE(X)
#undef X
    default:
        return "UNKNOWN";
    }
}

static int color_to_ansi(enum Color color)
{
    switch (color) {
#define X(name, code) case COLOR_##name: return code;
        COLOR_TABLE(X)
#undef X
    default:
        return 0;
    }
}

int main(void)
{
    _Static_assert(sizeof(int) >= 2, "int must be at least 16 bits");

    puts("=== Advanced C Macros Tutorial ===");

    puts("\n1) Stringification (#) and expanded stringification:");
#define VERSION 3.7
    printf("STR(VERSION)  -> %s\n", STR(VERSION));
    printf("XSTR(VERSION) -> %s\n", XSTR(VERSION));
#undef VERSION

    puts("\n2) Token pasting (##):");
    int CAT(total_, bytes) = 1024;
    printf("total_bytes = %d\n", total_bytes);

    puts("\n3) Safe statement macro (do { ... } while (0)):");
    int a = 10;
    int b = 20;
    printf("Before SWAP: a=%d, b=%d\n", a, b);
    SWAP(int, a, b);
    printf("After  SWAP: a=%d, b=%d\n", a, b);

    puts("\n4) Variadic macro for logging:");
    LOG_INFO("a=%d b=%d", a, b);

    puts("\n5) Generic macro with _Generic (C11):");
    printf("ABS(-42)      = %d\n", ABS(-42));
    printf("ABS(-42L)     = %ld\n", ABS(-42L));
    printf("ABS(-3.14f)   = %.2f\n", ABS(-3.14f));
    printf("ABS(-2.71828) = %.5f\n", ABS(-2.71828));

    puts("\n6) X-Macro table (single source of truth):");
    for (int i = 0; i < COLOR_COUNT; ++i) {
        enum Color color = (enum Color)i;
        printf("%-5s -> ANSI code %d\n", color_to_string(color), color_to_ansi(color));
    }

    puts("\n7) Utility macro for static array size:");
    int nums[] = {1, 2, 3, 4, 5};
    printf("ARRAY_LEN(nums) = %zu\n", ARRAY_LEN(nums));

    return 0;
}
