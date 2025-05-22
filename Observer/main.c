#include <stdio.h>
#include <stdlib.h>

#define MAX_OBSERVERS 10

typedef void (*ObserverCallback)(int);

// Subject structure
typedef struct {
    int value;
    ObserverCallback observers[MAX_OBSERVERS];
    int observer_count;
} Subject;

// Function to register an observer
void register_observer(Subject *subject, ObserverCallback observer) {
    if (subject->observer_count < MAX_OBSERVERS) {
        subject->observers[subject->observer_count++] = observer;
    }
}

// Function to notify all observers
void notify_observers(Subject *subject) {
    for (int i = 0; i < subject->observer_count; i++) {
        subject->observers[i](subject->value);
    }
}

// Function to set a new value and notify observers
void set_value(Subject *subject, int new_value) {
    subject->value = new_value;
    notify_observers(subject);
}

// Example observer functions
void observer1(int new_value) {
    printf("Observer 1: Value changed to %d\n", new_value);
}

void observer2(int new_value) {
    printf("Observer 2: Value changed to %d\n", new_value);
}

int main() {
    Subject subject = {0, {NULL}, 0};

    // Register observers
    register_observer(&subject, observer1);
    register_observer(&subject, observer2);

    // Change the value and notify observers
    set_value(&subject, 42);
    set_value(&subject, 100);

    return 0;
}