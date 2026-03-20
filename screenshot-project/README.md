Projeto: Captura de Tela em C

Este projeto contém duas implementações simples para capturar a tela em C:

- `src/screenshot_x11.c` — Exemplo para sistemas Linux com X11 (gera `tela.ppm`).
- `src/screenshot_windows.c` — Exemplo para Windows usando WinAPI/GDI (gera `tela.bmp`).

Como compilar

Linux (X11):

```
cd screenshot-project
make
./screenshot    # gera tela.ppm
```

Windows (MSVC):

Abra o Visual Studio Developer Command Prompt e compile:

```
cl /W4 /Ox src\screenshot_windows.c user32.lib gdi32.lib
screenshot_windows.exe
```

Windows (MinGW):

```
gcc -O2 -Wall -o screenshot_windows.exe src/screenshot_windows.c -lgdi32 -luser32
screenshot_windows.exe
```

Observações
- O exemplo X11 grava em formato PPM (P6) para manter o exemplo sem dependências.
- O exemplo Windows grava em BMP usando GDI.

Licença: exemplo didático — use conforme desejar.
