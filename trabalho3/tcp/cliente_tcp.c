#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG 8192
#define PORTA 4321
void sendfile(FILE *fp, int socket_desc);
int main(int argc , char *argv[]){
	// variaveis
	int socket_desc;
	struct sockaddr_in servidor;
	char *mensagem;
//	char resposta_servidor[MAX_MSG];
	int tamanho;
	char *ipservidor = "127.0.0.1";
    //Nome do Arquivo

    /*char *filename = basename("pi"); 
    if (filename == NULL)
    {
        perror("Can't get filename");
        exit(1);
    }    */
    // Arquivo
    FILE *fp = fopen("/run/media/natanael/Data/Torrent/How.I.Met.Your.Mother.S05E04.HDTV.XviD-2HD.[VTV].avi","rb");

    if(fp == NULL){
        perror("Erro ao abrir o arquivo\n");
        return -1;
    }

        //Passo 1: Criar o socket 
	// AF_INET = ARPA INTERNET PROTOCOLS
	// SOCK_STREAM = TCP
	// 0 = protocolo IP
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
     
	if (socket_desc == -1){
		printf("Nao foi possivel criar socket\n");
		return -1;	
	}
	/*if( send(socket_desc , filename , strlen(filename) , 0) < 0){
		printf("Erro ao enviar mensagem\n");
		return -1;
	}*/
	/* Informacoes para conectar no servidor */
	// IP do servidor
	// familia ARPANET
	// Porta - hton = host to network short (2bytes)
	servidor.sin_addr.s_addr = inet_addr(ipservidor);
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(PORTA);

	//Conectar no servidor
	if (connect(socket_desc , (struct sockaddr *)&servidor , sizeof(servidor)) < 0){
		printf("Nao foi possivel conectar\n");
		return -1;
	}
	printf("Conectado no servidor!!!\n");
	/*****************************************/


	/*******COMUNICAO - TROCA DE MENSAGENS **************/
    sendfile(fp,socket_desc);
	//Passo 3: Realizar a comunição com o servidor segundo um protocolo.


	//Envia mensagem para o servidor
/* 	mensagem = "Ola, tudo bem?";
	printf("Enviando: %s\n", mensagem);
	if( send(socket_desc , mensagem , strlen(mensagem) , 0) < 0){
		printf("Erro ao enviar mensagem\n");
		return -1;
	}

	//Recebendo resposta do servidor (echo)
	if( (tamanho = recv(socket_desc, resposta_servidor, MAX_MSG , 0)) < 0){
		printf("Falha ao receber resposta\n");
		return -1;
	}
	printf("Resposta: ");
	resposta_servidor[tamanho] = '\0';
	puts(resposta_servidor); */

	/*****************************************/
        //Passo 4: Encerrar conexão
    fclose(fp);
	close(socket_desc);

	printf("Cliente finalizado com sucesso!\n");
	return 0;
}

void sendfile(FILE *fp, int socket_desc){
    int n;
    char line[MAX_MSG];
    while((n = fread(&line,sizeof(char),MAX_MSG,fp))>0){
				printf("n:%x\n", n);

        if (n != 1024 && ferror(fp))
        {
            perror("Read File Error");
            exit(1);
        }
        if (send(socket_desc, line, n, 0) == -1)
        {
            perror("Can't send file");
            exit(1);
        }
        //memset(line, 0, sizeof(char));

    }
}
