/*
* Giovanna Borges Bottino 170011267
* Felipe Boccardi Silva Agustini 180119818
*/

#include <properties.h> /* informacoes para rodar */

int main(int argc, char *argv[]) {
    int client;
    struct sockaddr_in server_address; /* socket do servidor e cliente  */
    int pdu; /* o tamanho da mensagem */

    /* Verifica se o PDU foi enviado pelo argc  */
    if (argc<2) {
	  perror("[CLIENT] Digite PDU de enlace");
	  exit(0); 
    }
    printf("[CLIENT] Verifica se o PDU foi enviado pelo argc\n");
    
    /* Verifica se o PDU é um número */
    if (!isdigit(*argv[1])){
        perror("[CLIENT] O PDU de enlace deve ser um número");
	    exit(0); 
    }
    printf("[CLIENT] Verifica se o PDU é um número\n");
    /* o tamanho da mensagem pdu*/
    pdu = atoi(argv[1]); 
    char message[pdu];

    /* Criacao do socket TCP */
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == 0){ 
        /*
        * ARPA INTERNET PROTOCOLS -- IPv4
        * SOCK_STREAM orientado a conexão com transmissão de fluxos de bytes, sequencial e bidirecional
        * 0 - protocolo padrao para o tipo escolhido -- TCP
        */
        perror("[CLIENT] Criação do socket falhou");
        exit(0);
    }
    printf("[CLIENT] Criacao do socket TCP\n");

    /* Preenchendo informacoes sobre o cliente */
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(HOST); 
    server_address.sin_port = htons(PORT);

    /* Inicia a conexão no socket */
    if (connect(client, (struct sockaddr *)&server_address, sizeof(server_address))<0){
        perror("[CLIENT] Não pode conectar no Socket");
        exit(0);
    }
    printf("[CLIENT] Inicia a conexão no socket\n");

    /* Enviar pdu para o server  */
    if(send(client, argv[1], 10, 0) < 0){
        perror("[CLIENT] Falha no envio");
        /* Receber confirmação da pdu  */
    } else{
        printf("[CLIENT] Mandei o PDU:%s\n", argv[1]);
    }

    printf("[CLIENT] Conectado no IP: %s, porta TCP numero: %d\n", HOST, PORT);
    while (1){
        bzero(message, pdu); /* apaga a informacao*/
        
        /* Menu de interação */
        printf("[CLIENT] Esperando por mensagem:\n");
        fgets(message, sizeof(message), stdin);
        
        /* Verifica se mensagem foi enviada */
        if(send(client, message, sizeof(message), 0) < 0){
            perror("[CLIENT] Falha no envio");
        } else{
            printf("[CLIENT] Mensagem enviada foi: %s\n", message);
        }
        /* para caso exit */
        if (!strcmp(message, "exit\n")) {
            exit(0);
        }
    }
}
