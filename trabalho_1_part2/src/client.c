/*
* Giovanna Borges Bottino 170011267
* Felipe Boccardi Silva Agustini 180119818
*/

#include <properties.h> /* informacoes para rodar */

void response_client(char * receive_message, int client){
    if (send(client, receive_message, sizeof(receive_message) + 1, 0) < 0){
        perror("[CLIENT] Não foi possivel responder a mensagem");
    }
}

void finalizar(int socket){
    if(send(socket, "exit", sizeof("exit"), 0) < 0){
        perror("[CLIENT] Falha no envio");
    } else{
        printf("[CLIENT] Mensagem enviada foi: exit\n");
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    int client;
    struct sockaddr_in server_address; /* socket do servidor */
    int pdu; /* o tamanho da mensagem */
    char server_message[2000];
    pid_t process_id; /*Process Identification*/

    /* Criacao do socket TCP */
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == 0){ 
        /*
        * ARPA INTERNET PROTOCOLS -- IPv4
        * SOCK_STREAM orientado a conexão com transmissão de fluxos de bytes, sequencial e bidirecional
        * 0 - protocolo padrao para o tipo escolhido -- TCP
        */
        perror("[CLIENT] Criação do socket falhou");
        finalizar(client);
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

    /* Verifica se o PDU foi enviado pelo argc  */
    if (argc<2) {
	  perror("[CLIENT] Digite PDU de enlace");
	  finalizar(client);       
    }
    printf("[CLIENT] Verifica se o PDU foi enviado pelo argc\n");
    
    /* Verifica se o PDU é um número */
    if (!isdigit(*argv[1])){
        perror("[CLIENT] O PDU de enlace deve ser um número");
	    finalizar(client); 
    }
    printf("[CLIENT] Verifica se o PDU é um número\n");
    /* o tamanho da mensagem pdu*/
    pdu = atoi(argv[1]); 
    char send_message[pdu];
    char receive_message[pdu];

    /* Enviar pdu para o server  */
    int counter=0;
    while(strcmp(server_message, argv[1])){
        if(send(client, argv[1], 10, 0) < 0){
            perror("[CLIENT] Falha no envio da PDU");
            /* Receber confirmação da pdu  */
        } else{
            printf("[CLIENT] Mandei o PDU:%s\n", argv[1]);
        }

        bzero(server_message, 2000); /* apaga a informacao*/
        if(recv(client, server_message, sizeof(server_message), 0) < 0){
            perror("[CLIENT] Falha ao receber resposta");
        }
        
        printf("[CLIENT] Resposta do server: %s\n",server_message);

        counter++;
        if(counter>=3){
            perror("[CLIENT] Falha no envio da PDU para SERVER. PDU será 200");
            pdu=200;
            break;
        }
    }

    printf("[CLIENT] Conectado no IP: %s, porta TCP numero: %d\n", HOST, PORT);
    /*Fork para criar um novo processo*/
    process_id=fork();
    if(process_id==0){
        /* Receber a mensagem */
        while(1){
            bzero(receive_message, pdu); /* apaga a informacao*/
            if (recv(client, receive_message, pdu, 0) < 0){
                perror("[CLIENT] Não foi possivel receber a mensagem");
            } else{
                printf("[CLIENT] Recebida a mensagem: %s\n", receive_message);
                
                /* para responder */
                if (!strcmp(receive_message, "de erro\n")){ 
                    /* para dar erro */
                    char texto[100];
                    strcpy(texto, "não é sua mensagem :p\n");
                    response_client(texto, client);
                } else{
                    response_client(receive_message, client);
                }
            }
        }
    } else{
        
        /* envia a mensagem */
        while (1){
            bzero(send_message, pdu); /* apaga a informacao*/
            
            /* Menu de interação */
            printf("[CLIENT] Esperando por mensagem:\n");
            fgets(send_message, sizeof(send_message), stdin);
            
            /* Verifica se mensagem foi enviada */
            int counter=0;
            do {
                bzero(server_message, 2000); /* apaga a informacao*/
                if(send(client, send_message, sizeof(send_message), 0) < 0){
                    perror("[CLIENT] Falha no envio");
                } else{
                    printf("[CLIENT] Mensagem enviada foi: %s\n", send_message);
                }
                
                if(recv(client, server_message, sizeof(server_message), 0) < 0){
                    perror("[CLIENT] Falha ao receber resposta");
                }
                
                printf("[CLIENT] Resposta do server: %s\n",server_message);

                /* para dar erro */
                /* envie: de erro */
                if (strcmp(server_message, send_message)){
                    counter++;
                } 
                if (counter>=3){
                    perror("[CLIENT] Mensagem não pode ser enviada");
                    printf("[CLIENT] Mensagem cancelada foi: %s\n", send_message);
                    break;
                }
            }while(strcmp(server_message, send_message));
        }
    }
}
