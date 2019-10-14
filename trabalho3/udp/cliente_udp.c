#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#define MAX_MSG 6000
#define PORTA 1234
struct sockaddr_in addr_local;
struct sockaddr_in addr_remoto;
int socket_desc;
socklen_t slen = sizeof(addr_remoto);
char buf[MAX_MSG];
char filename[100];
int tam_recebido;	
char *servidor = "127.0.0.1";
unsigned long size;
void sendfile(FILE *fp, int socket_desc);
int main(int argc, char *argv[]){


	// Passo 1 : Criando um socket UDP
	if ((socket_desc=socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
		perror("nao foi possivel criar socket");
		return -1;
	}

	// Associando o socket a todos IPs locais e escolhendo um PORTA QUALQUER
	memset((char *) &addr_local, 0, sizeof(addr_local));
	addr_local.sin_family = AF_INET;
	addr_local.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_local.sin_port = htons(0);
	if (bind(socket_desc, (struct sockaddr *)&addr_local, sizeof(addr_local)) < 0) {
		perror("Erro ao fazer bind!");
		return -1;
	}       

	// Definindo addr_remoto como o endereco de destino
	// Convertendo a string 127.0.0.1 para formato binario com inet_aton
	memset((char *) &addr_remoto, 0, sizeof(addr_remoto));
	addr_remoto.sin_family = AF_INET;
	addr_remoto.sin_port = htons(PORTA);
	if (inet_aton(servidor, &addr_remoto.sin_addr)==0) {
		fprintf(stderr, "inet_aton() falhou\n");
		return -1;
	}
	if(connect(socket_desc,(struct sockaddr *)&addr_remoto,slen)<0){
		printf("erro de conexão\n");
		return -1;
	}
	//strcpy(filename,argv[1]);

    FILE *fp = fopen("uCOS-III-TI-LM3S9B92-001.pdf","rb");

    if(fp == NULL){
        perror("Erro ao abrir o arquivo\n");
        return -1;
    }
	/*if(send(socket_desc, filename, strlen(filename), 0)<0){
		perror("Erro ao enviar nome do arquivo");
		exit(0);
	}*/
	sendfile(fp, socket_desc);
        // Passo 2: Realizar a comunicação com o servidor
	// Enviando mensagem para o servidor
	//printf("Enviando mensagem para o servidor: %s [%d]\n", servidor, PORTA);
	//sprintf(buf, "Ola, tudo bem?");
	/*if (sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)==-1) {
		perror("Erro ao enviar pacote!!!");
		return -1;
	}*/
	// Recebendo resposta do servidor
	/*if ((tam_recebido = recvfrom(socket_desc, buf, MAX_MSG, 0, (struct sockaddr *)&addr_remoto, &slen)) >=0 ){
		buf[tam_recebido] = '\0';
		printf("Mensagem recebida: %s \n", buf);
	}*/

	//Passo 3: Fechar socket8192
	fclose(fp);
	close(socket_desc);
	return 0;
}

void sendfile(FILE *fp, int socket_desc){
    ssize_t n,w;
	char line[MAX_MSG];
	int it=0;
    while((n = fread(&line,sizeof(char),MAX_MSG,fp))>0){
        if (n != MAX_MSG && ferror(fp))
        {
            perror("Read File Error");
            exit(1);
        }
		w = send(socket_desc, line, n, 0);
        if ((w)<0)
        {
            perror("Can't send file");
            exit(1);
        }
		printf("Dados enviados: %d e lidos: %d\n",w,n);
		usleep(1);
		memset(&line, 0, MAX_MSG);

	}
	//fim da transmissao

}


