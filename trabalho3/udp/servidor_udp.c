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
int tam_recebido;


void writeFile(int socket_desc, FILE *fp);

int main(void){

	char filename[100];
	// Passo 1 : Criando um socket UDP
	if ((socket_desc=socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
		perror("Nao foi possivel criar socket");
		return -1;
	}
	
	// Associando o socket a todos IPs locais e escolhendo um PORTA ESPECIFICA
	memset((char *) &addr_local, 0, sizeof(addr_local));
	addr_local.sin_family = AF_INET;
	addr_local.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_local.sin_port = htons(PORTA);

	if (bind(socket_desc, (struct sockaddr *)&addr_local, sizeof(addr_local)) < 0){
		perror("Erro ao fazer bind!");
		return -1;
	}
//		connect(socket_desc,(struct sockaddr *)&addr_remoto,slen);
		/*if(recv(socket_desc, &filename, 100, 0)<0){
			perror("Erro ao receber nome do arquivo");
			exit(0);
		}*/
        FILE *fp = fopen("teste.pdf", "wb");
        if (fp == NULL) 
        {
            perror("Can't open file");
            exit(1);
        }
        writeFile(socket_desc,fp);

	// Passo 2: Realizar a comunicação com os clientes - fica em loop
	/*while(1){
		printf("Aguardando requisição ...\n");
		512
		// processando pacote recebido
		if ( (tam_recebido = recvfrom(socket_desc, buf, MAX_MSG, 0, (struct sockaddr *)&addr_remoto, &slen)) > 0){
			buf[tam_recebido]='\0';
			printf("Pacote recebido de: %s:[%d]\nDados: %s\n\n", 
				inet_ntoa(addr_remoto.sin_addr), ntohs(addr_remoto.sin_port), buf);
			
			// respondendo ao addr_remoto
			if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
				perror("Erro ao enviar resposta!!!");
			}
		}
	}*/
	//Passo 3: Fechar socket
	fclose(fp);
	close(socket_desc);
	return 0;
}
void writeFile(int socket_desc, FILE *fp){
    ssize_t n;
	int sec =0;
	char buff[MAX_MSG];
	while( ((n = recv(socket_desc, &buff, MAX_MSG, 0)) > 0)){
			
			if(n==-1){
				perror("Erro ao receber\n");
				exit(1);
			}
			/*if(sec != (rec.seq)){ 
				printf("sec:%d e seq(struct):%d\n",sec,rec.seq);
				break;
			}*/
			printf("n: %d\n", (n));
			if(fwrite(buff,sizeof(char), n, fp) != n){
				perror("Erro ao escrever arquivo\n");
				exit(1);
			}
		memset(&buff, 0, MAX_MSG);
		//sendto(socket_desc, &rec, sizeof(int), 0, (struct sockaddr *)&addr_remoto, slen);
		}

	
	printf("Fora do while: %x", n);
}