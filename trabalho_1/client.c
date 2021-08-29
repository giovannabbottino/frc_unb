/*
* Giovanna Borges Bottino 170011267
* Felipe Boccardi Silva Agustini 180119818
*/
#include <stdio.h> /* printf(), perror() */
#include <stdlib.h> 
#include <string.h>
#include "properties.h" /* informacoes para rodar */
#include <netinet/in.h> /* struct sockaddr_in */
#include <sys/socket.h> /* connect() send() */
#include <arpa/inet.h>  /* htons(), inet_addr() */
#include <sys/types.h> /* AF_INET, SOCK_STREAM */
#include <ctype.h> /* isdigit*/

int main(int argc, char *argv[]) {
    int client;
    struct sockaddr_in server_address, client_address; /* socket do servidor e cliente  */
    int pdu; /* o tamanho da mensagem */

    /* Verifica se o PDU foi enviado pelo argc  */
    if (argc<2) {
	  perror("CLIENT: Digite PDU de enlace");
	  exit(0); 
    }
    
    /* Verifica se o PDU é um número */
    if (!isdigit(*argv[1])){
        perror("CLIENT: O PDU de enlace deve ser um número");
	    exit(0); 
    }
    /* o tamanho da mensagem pdu*/
    pdu = atoi(argv[1]); 
    char message[pdu];

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

    /* Inicia a conexão no socket */
    if (connect(client, (struct sockaddr *)&client_address, sizeof(client_address))<0){
        perror("CLIENT: Não pode conectar no Socket");
        exit(0);
    }

    /* Enviar pdu para o server  */
    char pdu_size = pdu +'0\0';
    send(client, (void *)pdu_size, sizeof (pdu_size), 0);

    printf("CLIENT: Conectado no IP: %s, porta TCP numero: %d\n", CLIENT_HOST, CLIENT_PORT);
    while (1){
        printf("CLIENT: Esperando por mensagem:\n");

        fgets(message, sizeof(message), stdin);
        message[strlen(message)-1] = '\0';
        send(client, message, sizeof (message), 0);
        if (!strcmp (message, "exit")) {
            exit (0);
        }

    }

}
