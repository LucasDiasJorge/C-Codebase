#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>

void screenshot(const char* filename) {
    Display* display = XOpenDisplay(NULL);
    if (!display) { fprintf(stderr, "Unable to open display\n"); return; }
    Window root = DefaultRootWindow(display);

    XWindowAttributes attrs;
    XGetWindowAttributes(display, root, &attrs);
    int width  = attrs.width;
    int height = attrs.height;

    XImage* img = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);
    if (!img) { fprintf(stderr, "XGetImage failed\n"); XCloseDisplay(display); return; }

    FILE* f = fopen(filename, "wb");
    if (!f) { fprintf(stderr, "Failed to open output file\n"); XDestroyImage(img); XCloseDisplay(display); return; }

    fprintf(f, "P6\n%d %d\n255\n", width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned long pixel = XGetPixel(img, x, y);
            unsigned char r = (pixel >> 16) & 0xFF;
            unsigned char g = (pixel >> 8) & 0xFF;
            unsigned char b = pixel & 0xFF;
            fwrite(&r, 1, 1, f);
            fwrite(&g, 1, 1, f);
            fwrite(&b, 1, 1, f);
        }
    }

    fclose(f);
    XDestroyImage(img);
    XCloseDisplay(display);
}

int main() {
    screenshot("tela.ppm");
    return 0;
}
