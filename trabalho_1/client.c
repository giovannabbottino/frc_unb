/*
* Giovanna Borges Bottino 170011267
* Felipe Boccardi Silva Agustini 180119818
*/
#include <stdio.h> /* printf(), perror() */
#include <stdlib.h> 
#include "properties.h" /* informacoes para rodar */
#include <netinet/in.h> /* struct sockaddr_in */

int main(int argc, char *argv[]) {
    int client;
    struct sockaddr_in server_address, client_address; /* socket do servidor e cliente  */

    /* Criacao do socket TCP */
    if ((client = socket(AF_INET, SOCK_STREAM, 0)) == 0){ 
        /*
        * ARPA INTERNET PROTOCOLS -- IPv4
        * SOCK_STREAM orientado a conexão com transmissão de fluxos de bytes, sequencial e bidirecional
        * 0 - protocolo padrao para o tipo escolhido -- TCP
        */
        perror("CLIENT: Criação do socket falhou");
        exit(0);
    }

    /* Preenchendo informacoes sobre o servidor */
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_HOST); 
    server_address.sin_port = htons(SERVER_PORT);

    /* Preenchendo informacoes sobre o cliente */
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(CLIENT_HOST); 
    client_address.sin_port = htons(CLIENT_PORT);
}
