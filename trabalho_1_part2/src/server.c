/*
* Giovanna Borges Bottino 170011267
* Felipe Boccardi Silva Agustini 180119818
*/
#include <properties.h>

void response_server(char * receive_message, int client){
    if (send(client, receive_message, sizeof(receive_message) + 1, 0) < 0){
        perror("[SERVER] Não foi possivel responder a mensagem");
    }
}

int main(int argc, char *argv[]){
    int server, client;
    int pdu = -1; /* o tamanho da mensagem */
    socklen_t client_size;
    char client_message[2000];
    pid_t process_id; /*Process Identification*/

    struct sockaddr_in server_address, client_address; /* socket do servidor e cliente  */

    /* Criacao do socket TCP */
    server = socket(AF_INET, SOCK_STREAM, 0);
    if ( server == 0){ 
        /*
        * ARPA INTERNET PROTOCOLS -- IPv4
        * SOCK_STREAM orientado a conexão com transmissão de fluxos de bytes, sequencial e bidirecional
        * 0 - protocolo padrao para o tipo escolhido -- TCP
        */
        perror("[SERVER] Criação do socket falhou");
        exit(0);
    }
    printf("[SERVER] Criacao do socket TCP\n");
    
    /* Preenchendo informacoes sobre o servidor */
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(HOST); 
    server_address.sin_port = htons(PORT);

    /* Conecta na porta */
    if (bind(server, (struct sockaddr *)&server_address, sizeof(server_address))<0){
        perror("[SERVER] Não pode fazer bind na porta PORT");
        exit(0);
    }
    printf("[SERVER] Conecta na porta\n");

    /*  numero maximo de conexões */
    listen(server, 5);
    printf("[SERVER] Escutando\n");
    
    /* Aceita conexoes direta entre o servidor e cliente */
    client_size = sizeof(client_address);
    client = accept(server, (struct sockaddr *) &client_address, &client_size);
    if ( client == -1 ){
        perror("[SERVER] Não pode dar accept na PORT");
        exit(0);
    } 
    printf("[SERVER] Aceita conexoes direta\n");

    /* Recebe PDU */
    char pdu_message[9];
    int counter=0;
    while (pdu < 0){
        if (recv(client, pdu_message, 10, 0) < 0){
            perror("[SERVER] Não foi possivel receber o PDU");
        } else{
            pdu = atoi(pdu_message);
            printf("[SERVER] Recebido o PDU do CLIENT: %d\n", pdu);
        }

        /* para sair */
        if (!strcmp(pdu_message, "exit")){ 
            perror("[SERVER] Erro no PDU do CLIENT");
            return 1;
        }

        /* para responder */
        response_server(pdu_message, client);
        counter++;
        if(counter>=3){
            perror("[SERVER] Não foi possivel receber o PDU. PDU será 200");
            pdu = 200;
        }
    }
    char receive_message[pdu];
    char send_message[pdu];

    printf("[SERVER] Esperando por dados no IP: %s, porta TCP numero: %d\n", HOST, PORT);

    /*Fork para criar um novo processo*/
    process_id=fork();
    if(process_id==0){
        /* Receber a mensagem */
        while(1){
            bzero(receive_message, pdu); /* apaga a informacao*/
            if (recv(client, receive_message, pdu, 0) < 0){
                perror("[SERVER] Não foi possivel receber a mensagem");
            } else{
                printf("[SERVER] Recebida a mensagem: %s\n", receive_message);
                
                /* para responder */
                if (!strcmp(receive_message, "de erro\n")){ 
                    /* para dar erro */
                    char texto[100];
                    strcpy(texto, "não é sua mensagem :p\n");
                    response_server(texto, client);
                } else{
                    response_server(receive_message, client);
                }
            }
        }
    } else{
        
        /* envia a mensagem */
        while(1){
            bzero(send_message, pdu); /* apaga a informacao*/
            
            /* Menu de interação */
            printf("[SERVER] Esperando por mensagem:\n");
            fgets(send_message, sizeof(send_message), stdin);
            
            /* Verifica se mensagem foi enviada */
            int counter=0;
            do {
                bzero(client_message, 2000); /* apaga a informacao*/
                if(send(client, send_message, sizeof(send_message), 0) < 0){
                    perror("[SERVER] Falha no envio");
                } else{
                    printf("[SERVER] Mensagem enviada foi: %s\n", send_message);
                }
                
                if(recv(client, client_message, sizeof(client_message), 0) < 0){
                    perror("[SERVER] Falha ao receber resposta");
                }
                
                printf("[SERVER] Resposta do server: %s\n",client_message);

                /* para dar erro */
                /* envie: de erro */
                if (strcmp(client_message, send_message)){
                    counter++;
                } 
                if (counter>=3){
                    perror("[SERVER] Mensagem não pode ser enviada");
                    printf("[SERVER] Mensagem cancelada foi: %s\n", send_message);
                    break;
                }
            }while(strcmp(client_message, send_message));
        }
    }   
}