/*
* Giovanna Borges Bottino 170011267
* Felipe Boccardi Silva Agustini 180119818
*/
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h> /* sockaddr_in */
#include <sys/socket.h> /* socket */

#define MSG_SIZE_TEXT 250  /* tamanho do texto das mensagens  */
#define MSG_SIZEMAX 260    /* MSG_SIZE_TEXT + sizeof(int) */

typedef struct Message{
    long int mtype; /* tipo da mensagem */
    struct sockaddr_in adress; /* endereco do cliente  */
    char msg[MSG_SIZE_TEXT];
}Message;

int main(int argc, char *argv[]){
    int server_d, message_id;
    struct Message message;

    struct sockaddr_in address; /* endereco do servidor  */

    /* Verifica se o IP e Porta foram enviados pelo argc  */
    if (argc<3) {
	  perror("SERVER: Digite IP e Porta para este servidor\n");
	  exit(EXIT_FAILURE); 
    }

    /* Criacao do socket UDP */
    if ((server_d = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("SERVER: Criação do socket falhou");
        exit(EXIT_FAILURE);
    }
    
    /* Preenchendo informacoes sobre o servidor */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(argv[1]); 
    address.sin_port = htons(atoi(argv[2]));

    /* Conecta na porta */
    if (bind(server_d, (struct sockaddr *)&address, sizeof(address))<0){
        perror("SERVER: %s: nao pode fazer bind na porta %s \n", argv[0], argv[2]);
        exit(EXIT_FAILURE);
    }

    /* Criacao da fila de mensagens */
    

    printf("SERVER: %s: esperando por dados no IP: %s, porta UDP numero: %s\n", argv[0], argv[1], argv[2]);

    while(1){
        /* Receber fila de mensagens*/

        /* imprime a mensagem recebida na tela do usuario */
        printf("SERVER: {UDP, IP_L: %s, Porta_L: %u", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
        printf("SERVER: IP_R: %s, Porta_R: %u} => %s\n",inet_ntoa(message.adress.sin_addr), ntohs(message.adress.sin_port), message.msg);

    }   
}