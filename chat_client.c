#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

#define PORTA 20032
#define TAMMAX 250
#define ERRO -1

int sock;

void *receber_msgs(void *arg) {
    char msg[TAMMAX];
    int bytes;
    while ((bytes = recv(sock, msg, TAMMAX, 0)) > 0) {
        msg[bytes] = '\0';
        printf("\n[Outro usuário]: %s", msg);
        printf("Você: ");
        fflush(stdout);
    }
    printf("\nConexão encerrada pelo servidor.\n");
    exit(0);
}

int main(int argc, char **argv) {
    struct sockaddr_in servidor;
    pthread_t thread_receber;
    char msg[TAMMAX];

    if (argc < 2) {
        printf("Use: %s <IP do servidor>\n", argv[0]);
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == ERRO) {
        perror("Socket");
        exit(1);
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PORTA);
    servidor.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) == ERRO) {
        perror("Connect");
        exit(1);
    }

    printf("Conectado ao servidor %s\n", argv[1]);
    pthread_create(&thread_receber, NULL, receber_msgs, NULL);

    while (1) {
        printf("Você: ");
        fgets(msg, TAMMAX, stdin);
        send(sock, msg, strlen(msg), 0);
    }

    close(sock);
    return 0;
}
