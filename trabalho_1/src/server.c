/*
* Giovanna Borges Bottino 170011267
* Felipe Boccardi Silva Agustini 180119818
*/
#include <properties.h>

void response_server(char * message, int client){
    if (send(client, message, sizeof(message) + 1, 0) < 0){
        perror("[SERVER] Não foi possivel responder a mensagem");
    }
}


int main(int argc, char *argv[]){
    int server, client;
    int pdu = -1; /* o tamanho da mensagem */
    socklen_t client_size;

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

        /* para responder */
        response_server(pdu_message, client);
        counter++;
        if(counter>=3){
            perror("[SERVER] Não foi possivel receber o PDU. PDU será 200");
            pdu = 200;
        }
    }
    char message[pdu];

    printf("[SERVER] Esperando por dados no IP: %s, porta TCP numero: %d\n", HOST, PORT);

    while(1){
        bzero(message, pdu); /* apaga a informacao*/
        
        /* Receber a mensagem */
        if (recv(client, message, pdu, 0) < 0){
            perror("[SERVER] Não foi possivel receber a mensagem");
        } else{
            /* para sair */
            if (!strcmp(message, "exit\n")){ 
                exit(0);
            }
            printf("[SERVER] Recebida a mensagem: %s\n", message);
            
            /* para responder */
            if (!strcmp(message, "de erro\n")){ 
                /* para dar erro */
                char texto[100];
                strcpy(texto, "não é sua mensagem :p\n");
                response_server(texto, client);
            } else{
                response_server(message, client);
            }
        }
    }   
}