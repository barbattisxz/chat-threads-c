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
#define ERRO -1
#define TAMMAX 250
#define MAX_CLIENTES 10

int clientes[MAX_CLIENTES];
int num_clientes = 0;
pthread_mutex_t lock; // para sincronizar o acesso à lista de clientes

void *conexao_cliente(void *arg) {
    int cliente_sock = *(int *)arg;
    char msg[TAMMAX];
    int bytes;

    while ((bytes = recv(cliente_sock, msg, TAMMAX, 0)) > 0) {
        msg[bytes] = '\0';
        printf("Mensagem recebida: %s", msg);

        // retransmite para todos os clientes conectados
        pthread_mutex_lock(&lock);
        for (int i = 0; i < num_clientes; i++) {
            if (clientes[i] != cliente_sock) {
                send(clientes[i], msg, strlen(msg), 0);
            }
        }
        pthread_mutex_unlock(&lock);
    }

    // se sair do loop, cliente desconectou
    close(cliente_sock);
    pthread_mutex_lock(&lock);
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i] == cliente_sock) {
            for (int j = i; j < num_clientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            num_clientes--;
            break;
        }
    }
    pthread_mutex_unlock(&lock);

    printf("Cliente desconectado.\n");
    pthread_exit(NULL);
}

int main() {
    struct sockaddr_in local, remoto;
    int sock, novoSock, tamStruct;

    pthread_t tid;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == ERRO) {
        perror("Socket");
        exit(1);
    }

    local.sin_family = AF_INET;
    local.sin_port = htons(PORTA);
    local.sin_addr.s_addr = INADDR_ANY;
    bzero(&(local.sin_zero), 8);

    if (bind(sock, (struct sockaddr *)&local, sizeof(local)) == ERRO) {
        perror("Bind");
        exit(1);
    }

    listen(sock, 5);
    printf("Servidor aguardando conexões na porta %d...\n", PORTA);

    pthread_mutex_init(&lock, NULL);

    while (1) {
        tamStruct = sizeof(remoto);
        novoSock = accept(sock, (struct sockaddr *)&remoto, (socklen_t *)&tamStruct);
        if (novoSock == ERRO) {
            perror("Accept");
            continue;
        }

        pthread_mutex_lock(&lock);
        if (num_clientes < MAX_CLIENTES) {
            clientes[num_clientes++] = novoSock;
            pthread_create(&tid, NULL, conexao_cliente, (void *)&clientes[num_clientes - 1]);
            printf("Novo cliente conectado: %s\n", inet_ntoa(remoto.sin_addr));
        } else {
            printf("Servidor cheio! Conexão recusada.\n");
            close(novoSock);
        }
        pthread_mutex_unlock(&lock);
    }

    close(sock);
    return 0;
}
