#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

typedef void(*pointGenerico)(float[][30],char[][30], int n);

int menu() {
	int op;
	
	printf("\n\n\nMENU\n\n");
	printf("1 - Qual cidade com maior número de vizinhos?\n");
	printf("2 - Qual cidade com menor número de vizinhos?\n");
	printf("3 - Qual cidade possui o vizinho mais distante\n");
	printf("4 - Qual cidade possui o vizinho mais perto?\n");
	printf("5 - Qual a distância entre duas cidades?\n");
	printf("0 - Sair\n");
	do {
		printf("Escolha sua opção: ");
		scanf("%d", &op);

		if (op < 0 || op > 7){
			printf("Opção inválida!!");
		}

	} while(op < 0 || op > 7);
	return op;
}


//MANIPULAÇÃO DE ARQUIVO
FILE * abrirArquivo(char * nomeArq, char * modo) {
    FILE * arq;
    arq = fopen( nomeArq, modo );
    if ( arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
        exit(-1);
    }
    return arq;
}


void carregarCidades(FILE * arq, char city[][30]) { //Retira as informações do arquivo e aloca na matriz 
     int i;
	 char total[30]; 
		
	 fscanf(arq, " %30[^\n]s" , total);

     for ( i=0; i<30; i++) { 

		fscanf(arq, " %30[^\n]s" , city[i]);
    }
}


void matriz(FILE * arquivo, float d[][30]){
	int i, j;
     for (i = 0; i < 30; i++) {
        for (j = 0; j < 30; j++) {
            if (fscanf(arquivo, "%f;", &d[i][j]) != 1){
				printf("erro");
			}
		}
     }

}

//FUNÇÕES
void imprimir_1_2(char vet[][30], int c, int res, int q){
	printf("\n||QUESTÃO %d||\n ",q);
	printf("\nCidade:%s | Quantidade:%d\n\n", vet[c], res);	
	system("pause");
}


void imprimir_3_4(char vet[][30], int c, int v, float d, int q){
	printf("\n||QUESTÃO %d||\n ",q);
	printf ("\nCidade:%s | Vizinho:%s | Distância:%.2f\n\n", vet[c], vet[v], d);
	system("pause");
}


void maior(float d[][30], char c[][30], int quest){
	int i, j, viz = 0, res = 15, cont;
		
		for(i=0; i<30; i++){
			for(j=0; j<30; j++){
				
				if(d[i][j]!=0){
					viz++;    //soma a quantidade vizinhos
				}
			}
			
			if ((quest == 1) && (viz > res)){ //Condição questão 1
				res = viz; //Guarda a quantidade de vizinhos 
				cont = i;    //Guarda o índice da cidade
			} 
                else if ((quest == 2) && (viz < res)){ //Condição questão 2
                    res = viz; 
                    cont = i;
                }
			viz = 0;
		}
	imprimir_1_2(c, cont, res, quest);
}


void distante(float d[][30], char c[][30], int quest){
	int i,j, city, vizinho;
	float dist = 0;
	
		for(i=0; i<30; i++){
			for(j=1; j<30; j++){

				if((quest == 3) && (d[i][j] > 0)){ //Questão 3
					if(d[i][j] > dist){
						city = i;
						vizinho = j;
						dist = d[i][j];
					}                
				} else if((quest == 4) && (d[i][j] > 0)){ //Questão 4
					city = i;
					vizinho = j;
					dist = d[i][j];
				}
			}
		}
	imprimir_3_4(c,city,vizinho,dist, quest);
}


void adjacencia(float d[][30], char c[][30], int quest){
	int i, city, vizinho;

    for ( i=0; i<10; i++) { 
        printf("\n%s\t\t", c[i]);
		printf("%s\t\t",c[i+10]);
		printf("%s",c[i+20]);
    }

	printf("\n\nEscolha uma cidade:");
	scanf("%d", &city);
	while ((city < 0) || (city > 29)){
		printf("\nCidade não existente. Digite um número válido:\n");
		scanf("%d", &city);
	}

	printf("\nEscolha a cidade vizinha:");
	scanf("%d", &vizinho);
	while ((vizinho < 0) || (vizinho > 29) || (vizinho == city)){
		
		printf("\nCidade não existente. Digite um número válido:\n");
		scanf("%d", &vizinho);
	}

	printf("\n||QUESTÃO %d||\n ", quest);
    if(d[city][vizinho] == 0){
		printf("\nEssas cidades não são vizinhas!");
	} else{	
		printf("\nA distância entre a cidade escolhida (%s) e sua vizinha (%s) é:%.2f", c[city], c[vizinho], d[city][vizinho]);
		}
	
	printf("\n\nPressione qualquer tecla para continuar...");
	getch();	
}

void ativarFuncao(float dist[][30], char matriz[][30],int n,pointGenerico funcao){
	funcao(dist,matriz,n);
}


//FUNÇÃO PRINCIPALLLL
int main() {
	SetConsoleOutputCP(65001);
    char cidades[30][30];
    float dist[30][30];
    int op;
	
    FILE * arquivo;

	arquivo = abrirArquivo("entrada_30_cidades.txt", "r");
	carregarCidades(arquivo, cidades);
	matriz(arquivo, dist);
    fclose(arquivo);
	
    do {
		op = menu();
		switch ( op ) {
			case 0:
				break;
			case 1:
				//1. Qual cidade possui o maior número de vizinhos? Informar cidade e quantidade de vizinhos
				ativarFuncao(dist, cidades, op, maior);
				break;
			case 2:
				//2. Qual cidade possui o menor número de vizinhos? Informar cidade e quantidade de vizinhos.
				ativarFuncao(dist, cidades, op, maior);
				break;
			case 3:
				//3. Qual cidade possui o vizinho mais distante? Informar cidade, vizinho e distancia.
				ativarFuncao(dist, cidades, op, distante);
				break;
			case 4:
				//4. Qual cidade possui o vizinho mais próximo? Informar cidade, vizinho e distância.
				ativarFuncao(dist, cidades, op, distante);
				break;
			case 5:
				//5. Dado os nomes de duas cidades pertencentes a matriz de adjacência, qual a distância entre elas?
				//adjacencia(dist, cidades);
				ativarFuncao(dist, cidades, op, adjacencia);
				break;
			default:
				printf ("\n\nOpçãoo inválida!\n\n");
		}
	} while (op != 0);

    return 0;
}