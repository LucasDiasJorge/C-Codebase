#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

int configure_serial_port(int fd) {
    struct termios tty;
    memset(&tty, 0, sizeof tty);

    // Obter as configurações da porta serial
    if (tcgetattr(fd, &tty) != 0) {
        printf("Error %d from tcgetattr: %s\n", errno, strerror(errno));
        return -1;
    }

    // Configurar velocidade de baud, modo, paridade e outros parâmetros
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8 bits de dados
    tty.c_iflag &= ~IGNBRK;                         // Desativar ignição de break
    tty.c_lflag = 0;                                // Desativar modos canônicos, eco e outros
    tty.c_oflag = 0;                                // Desativar pós-processamento de saída
    tty.c_cc[VMIN]  = 1;                            // Leitura bloqueante até que pelo menos 1 caractere seja recebido
    tty.c_cc[VTIME] = 0;                            // Sem temporizador entre caracteres

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // Desativar controle de fluxo por software
    tty.c_cflag |= (CLOCAL | CREAD);                // Ativar recepção
    tty.c_cflag &= ~(PARENB | PARODD);              // Desativar paridade
    tty.c_cflag &= ~CSTOPB;                         // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;                        // Desativar controle de fluxo por hardware

    // Aplicar configurações
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error %d from tcsetattr: %s\n", errno, strerror(errno));
        return -1;
    }

    return 0;
}

int main() {
    const char *portname = "/dev/ttyS1"; // Substitua pelo nome correto da porta serial
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);

    if (fd < 0) {
        printf("Error %d opening %s: %s\n", errno, portname, strerror(errno));
        return 1;
    }

    if (configure_serial_port(fd) != 0) {
        close(fd);
        return 1;
    }

    char buf[100];
    while (1) {
        int n = read(fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("Received: %s\n", buf);
        } else if (n < 0) {
            printf("Error reading: %s\n", strerror(errno));
            break;
        }
    }

    close(fd);
    return 0;
}
