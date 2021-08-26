/*
* Giovanna Borges Bottino 170011267
* Felipe Boccardi Silva Agustini 180119818
*/
#include <stdio.h>
#include <stdlib.h>
#include <properties.h> /* informacoes para rodar */
#include <netinet/in.h> /* sockaddr_in */
#include <sys/socket.h> /* socket */

int main(int argc, char *argv[]){
    int server, client;
    int pdu; /* o tamanho da mensagem */

    struct sockaddr_in address, client_address; /* socket do servidor e cliente  */

    /* Verifica se o PDU foi enviado pelo argc  */
    if (argc<1) {
	  perror("SERVER: Digite PDU de enlace\n");
	  exit(0); 
    }
    
    /* Verifica se o PDU é um número */
    if (isdigit(argv[0]) == 0 ){
        perror("SERVER: O PDU de enlace deve ser um número\n");
	    exit(0); 
    }
    /* o tamanho da mensagem pdu*/
    pdu = atoi(argv[0]); 
    char message[pdu];

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
    address.sin_port = htons(atoi(SERVER_PORT));

    /* Conecta na porta */
    if (bind(server, (struct sockaddr *)&address, sizeof(address))<0){
        perror("SERVER: %s: nao pode fazer bind na porta %s \n", SERVER_HOST, SERVER_PORT);
        exit(0);
    }

    /*  numero maximo de conexões */
    listen(server, 5);

    printf("SERVER: Esperando por dados no IP: %s, porta UDP numero: %s\n", SERVER_HOST, SERVER_PORT);

    while(1){
        /* Aceitar conexoes direta entre o servidor e cliente */
        if ( client = accept(server, (struct sockaddr *) &client_address,  sizeof(client_address)) == 1 ){
            perror("SERVER: %s: nao pode dar accept em %s na porta %s\n", SERVER_HOST, CLIENT_HOST, CLIENT_PORT);
            exit(0);
        }

        /* Receber fila de mensagens*/

        /* imprime a mensagem recebida na tela do usuario */
        printf("SERVER: {UDP, IP_L: %s, Porta_L: %u", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
        printf("SERVER: IP_R: %s, Porta_R: %u} => %s\n",inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), message);
    }   
}