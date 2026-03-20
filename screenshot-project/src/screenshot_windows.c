#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void screenshot(const char* filename) {
    HDC hdcScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
    HGDIOBJ oldObj = SelectObject(hdcMem, hBitmap);

    BitBlt(hdcMem, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY);

    BITMAPINFOHEADER bih;
    ZeroMemory(&bih, sizeof(bih));
    bih.biSize = sizeof(bih);
    bih.biWidth = width;
    bih.biHeight = -height; /* top-down */
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_RGB;

    DWORD rowSize = ((width * 3 + 3) & ~3);
    DWORD imgSize = rowSize * height;

    BITMAPFILEHEADER bfh;
    ZeroMemory(&bfh, sizeof(bfh));
    bfh.bfType = 0x4D42; /* 'BM' */
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bfh.bfSize = bfh.bfOffBits + imgSize;

    BYTE* pixels = (BYTE*)malloc(imgSize);
    if (!pixels) { fprintf(stderr, "malloc failed\n"); goto cleanup; }

    if (!GetDIBits(hdcMem, hBitmap, 0, height, pixels, (BITMAPINFO*)&bih, DIB_RGB_COLORS)) {
        fprintf(stderr, "GetDIBits failed\n");
        free(pixels);
        goto cleanup;
    }

    FILE* f = fopen(filename, "wb");
    if (f) {
        fwrite(&bfh, sizeof(bfh), 1, f);
        fwrite(&bih, sizeof(bih), 1, f);
        fwrite(pixels, imgSize, 1, f);
        fclose(f);
    } else {
        fprintf(stderr, "Failed to open output file\n");
    }

    free(pixels);

cleanup:
    SelectObject(hdcMem, oldObj);
    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);
}

int main() {
    screenshot("tela.bmp");
    return 0;
}
