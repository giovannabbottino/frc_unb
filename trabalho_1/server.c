/*
* Giovanna Borges Bottino 170011267
* Felipe Boccardi Silva Agustini 180119818
*/
#include <stdio.h> /* printf(), perror() */
#include <stdlib.h> 
#include "properties.h" /* informacoes para rodar */
#include <ctype.h> /* isdigit*/
#include <sys/types.h> /* AF_INET, SOCK_STREAM */
#include <sys/socket.h> /* socket(), connect() */
#include <netinet/in.h> /* struct sockaddr_in */
#include <arpa/inet.h>  /* htons(), inet_addr() */

int main(int argc, char *argv[]){
    int server, client;
    int pdu; /* o tamanho da mensagem */
    socklen_t cliente_size;

    struct sockaddr_in address, client_address; /* socket do servidor e cliente  */

    printf("SERVER: Verifica se o PDU foi enviado pelo argc\n");
    /* Verifica se o PDU foi enviado pelo argc  */
    if (argc<2) {
	  perror("SERVER: Digite PDU de enlace");
	  exit(0); 
    }
    
    printf("SERVER: Verifica se o PDU é um número\n");
    /* Verifica se o PDU é um número */
    if (!isdigit(*argv[1])){
        perror("SERVER: O PDU de enlace deve ser um número");
	    exit(0); 
    }
    /* o tamanho da mensagem pdu*/
    pdu = atoi(argv[1]); 
    char message[pdu];
    printf("SERVER: PDU: %d\n", pdu);

    /* Criacao do socket UDP */
    if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0){ 
        /*
        * ARPA INTERNET PROTOCOLS -- IPv4
        * SOCK_STREAM orientado a conexão com transmissão de fluxos de bytes, sequencial e bidirecional
        * 0 - protocolo padrao para o tipo escolhido -- TCP
        */
        perror("SERVER: Criação do socket falhou");
        exit(0);
    }
    
    /* Preenchendo informacoes sobre o servidor */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(SERVER_HOST); 
    address.sin_port = htons(SERVER_PORT);

    /* Conecta na porta */
    if (bind(server, (struct sockaddr *)&address, sizeof(address))<0){
        perror("SERVER: Não pode fazer bind na porta SERVER_PORT");
        exit(0);
    }

    /*  numero maximo de conexões */
    listen(server, 5);

    printf("SERVER: Esperando por dados no IP: %s, porta UDP numero: %d\n", SERVER_HOST, SERVER_PORT);

    while(1){
        /* Aceita conexoes direta entre o servidor e cliente */
        cliente_size = sizeof(client_address);
        if ( client = accept(server, (struct sockaddr *) &client_address, &cliente_size) == 1 ){
            perror("SERVER: Não pode dar accept na CLIENT_PORT");
            exit(0);
        }

        /* Receber fila de mensagens*/

        /* imprime a mensagem recebida na tela do usuario */
        printf("SERVER: {UDP, IP_L: %s, Porta_L: %u", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
        printf("SERVER: IP_R: %s, Porta_R: %u} => %s\n",inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), message);
    }   
}