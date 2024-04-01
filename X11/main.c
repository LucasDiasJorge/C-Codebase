#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    Display *display;
    Window window;
    XEvent event;

    // Abre a conexão com o servidor X
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Erro ao abrir a conexão com o servidor X\n");
        exit(1);
    }

    // Cria uma janela
    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 200, 100, 0, 0, 0);
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    // Loop de eventos
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Redesenha a janela
            // (neste exemplo, não fazemos nada)
        }
        if (event.type == KeyPress)
            break;
    }

    // Fecha a conexão com o servidor X
    XCloseDisplay(display);
    return 0;
}
