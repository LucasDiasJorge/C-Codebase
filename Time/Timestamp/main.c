#include <stdio.h>
#include <time.h>

int main() {
    struct tm time_components = {0};
    time_t timestamp;
    char time_str[100];

    // Assigning time components
    time_components.tm_year = 2024 - 1900; // Year - 1900
    time_components.tm_mon = 1; // Month (0 - 11)
    time_components.tm_mday = 7; // Day of the month (1 - 31)
    time_components.tm_hour = 12; // Hour (0 - 23)
    time_components.tm_min = 30; // Minute (0 - 59)
    time_components.tm_sec = 0; // Second (0 - 60)

    // Convert time components to timestamp
    timestamp = mktime(&time_components);

    // Format timestamp into a string
    strftime(time_str, sizeof(time_str), "%c", &time_components);
    printf("Given date and time: %s\n", time_str);

    return 0;
}