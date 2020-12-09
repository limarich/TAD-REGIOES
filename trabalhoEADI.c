#include<stdio.h>
#include<stdlib.h>
#include<locale.h>


typedef struct {
	char regiao[50];
	int casos;
	int obtos;
	float incidencia;
	float letalidade;
	float mortalidade
}INF; // dados analizados
typedef struct nodo {
	INF inf;
	struct nodo* prox;
}NODO;
typedef NODO*LISTA_REGIAO;
//
void cria_lista(LISTA_REGIAO*);
void inicializa(LISTA_REGIAO*);
void ins(LISTA_REGIAO*l, INF i, int pos);
int tam(LISTA_REGIAO l);
LISTA_REGIAO buscar (int posicao, LISTA_REGIAO p);
void retirar(LISTA_REGIAO* ,int);
void destroi(LISTA_REGIAO);
void registra(LISTA_REGIAO);
void menu(LISTA_REGIAO*);
void imprimir(INF);
INF cadastro();
char* maior(INF, INF, int); // retorna o nome do maior
void percorrer(LISTA_REGIAO *);// melhor passar o local na memoria pq se não vai gerar uma copia e dps percorrer td
void troca(LISTA_REGIAO* , LISTA_REGIAO*);
double media(LISTA_REGIAO, int);//apresentando problema 
float somamedia(LISTA_REGIAO, int, int);

int main() {
	INF inf;
	setlocale(LC_ALL,"Portuguese");
	LISTA_REGIAO l;
	cria_lista(&l);
	inicializa(&l);
	do{
	    menu(&l);
	}while(1);
	return 0;
}
//
void cria_lista(LISTA_REGIAO*l) {
	*l = NULL; 
}
void inicializa(LISTA_REGIAO *p){
	INF val;
	FILE *dados;
	dados = fopen("BaseDados.txt", "r");
	if (!dados){
		printf ("Erro com a base de dados");
		exit(6);
	}
	
	while (!feof(dados)){ 
		fscanf(dados,"%s %d %d %f %f %f",&val.regiao, &val.casos, &val.obtos, &val.incidencia, &val.letalidade, &val.mortalidade);
		ins(p, val,1);//insere na primeira posição
	}
}
void ins(LISTA_REGIAO*l, INF i, int pos) {
	LISTA_REGIAO novo;
	if(pos < 1 || pos > tam(*l)+1) {
		printf("\nErro, você está tentando inserir algum dado em uma posição inválida\nDICA: No Brasil  só existem 5 regiões políticas");
		exit(1);
	}
	novo = (LISTA_REGIAO) malloc(sizeof(NODO));
	if(!novo) {
		printf("\nErro, não foi possível reservar memória suficiente\n");
		exit(2);
	}
	novo->inf = i;
	if(pos == 1) {
		novo->prox = *l;
		*l = novo;
	}
	else {
		LISTA_REGIAO aux;
		for(aux = *l;pos > 1; pos--, aux = aux->prox);
		novo->prox = aux->prox;
		aux->prox = novo;
	}
}
int tam(LISTA_REGIAO l) {
	int cont;
	for(cont = 0; l != NULL; l = l->prox, cont++);
	return cont;
}
LISTA_REGIAO buscar (int posicao, LISTA_REGIAO p){
	if (posicao < 1 || posicao > tam(p)){
		printf("\n Posição inválida");
		exit(4);
	}
	posicao--;
	for(;posicao > 0; posicao--, p = p->prox);	
   return p;
}
void retirar(LISTA_REGIAO *p, int posicao) {
	if(posicao < 1 || posicao > tam(*p)) {
		printf("\nErro, posição inválida\n");
		exit(5);
	}
	if(posicao == 1) {
		LISTA_REGIAO aux;
		aux = *p;
		*p = aux->prox;
		free(aux);
	}
	else {
		retirar(&((*p)->prox), posicao-1);
	}
}
void menu(LISTA_REGIAO* l){
	int op=0, i = 1, j;
	LISTA_REGIAO aux, aux2;
	system("cls");
	printf ("\nDigite a opção que deseja:\n");
	printf("(1)-Imprimir todos os dados cadastrados\n(2)-Imprimir os dados de uma região\n(3)-Apagar os dados de uma região\n");
	printf("(4)-Inserir nova região\n(5)-Atualizar dados\n(6)-Comparar duas regiões\n");
	printf("(7)-Trocar a posição de elementos\n(8)-Verificar o tamanho\n(9)-Verificar a média de algum campo\n(10)-Verificar o total de algum campo\n(0)-Fim da execussão\n");
	printf("\n\nOpção: ( )\b\b");
	scanf("%d",&op);
	
	switch (op) {
		case 0:
			system("cls");
			printf("\n\n\tSerá gerado um relatório final atualizado em txt na pasta localizada desse executável");
			printf("\n\tNome do aquivo: \t\tRELATORIO.TXT\n\n");
			registra(*l);
			destroi(*l);
			exit(0);
			break;
		case 1:
			aux = *l;
			printf("%s","_______________________________________________________________________________________________________________\n");
			printf("|| %-20s | %-8s | %-8s | %-18s | %-18s | %-19s ||\n", "REGIÃO", "N° CASOS", "N° OBTOS", "TAXA DE INCIDENCIA", "TAXA DE LETALIDADE", "TAXA DE MORTALIDADE");
			printf("%s","||____________________________________________________________________________________________________________||\n");
			while(aux) {
				imprimir(aux->inf);
				aux = aux->prox;
			}
			break;
		case 2:
 	          percorrer(l);
 	          printf("\n\nEscolha uma opção:  ");
			  scanf("%d", &i);
  			printf("%s","_______________________________________________________________________________________________________________\n");
			printf("|| %-20s | %-8s | %-8s | %-18s | %-18s | %-19s ||\n", "REGIÃO", "N° CASOS", "N° OBTOS", "TAXA DE INCIDENCIA", "TAXA DE LETALIDADE", "TAXA DE MORTALIDADE");
			printf("%s","||____________________________________________________________________________________________________________||\n");
	        imprimir((buscar(i,*l))->inf);
			 break;
        case 3:
              percorrer(l);
		      printf("\nQual dessas deve ser apagada?\n");
			  scanf("%d", &i);
			  printf("\nTem certeza? [SIM(1)][NÃO(2)]\n");
			  scanf("%d", &op);
			  if(op == 1) {
			  	retirar(l,i);
			  }
               break;
	    case 4:
			  printf("\nDeseja inserir novos dados? [SIM(1)][NÃO(2)]\n");
			  scanf("%d", &op);
			  if(op == 1) {
			  	ins(l,cadastro(), 1);
			  }
			  break;
        case 5: 
 	          percorrer(l);
 	          printf("\n\nEscolha uma opção:  ");
		      scanf("%d", &i);
		      printf("\nDeseja realmente atualizar novos dados? [SIM(1)][NÃO(2)]\n");
			  scanf("%d", &op);
			  if(op == 1) {
			  	aux = *l;
				  while(i > 1) {
				  	aux = aux->prox;
				  }
	 	          aux->inf = cadastro();
				  printf("%s", aux->inf.regiao);
			  }
            break;
            case 6:
            	percorrer(l);
            	printf("Escolha duas opções:\n");
            	scanf("%d %d", &i, &j);
            	aux = buscar(i, *l);
				aux2 = buscar(j, *l);
				printf("\nInsira qual campo será comparado:\n\ncasos[1]\nobtos[2]\nincidencia[3]\nletalidade[4]\nmortalidade[5]");
				scanf("%d",&op);
				printf("\n%s\n", maior(aux->inf, aux2->inf, op+1)); 
            break;
            case 7:
            	percorrer(l);
            	printf("\nEscolha 2 opções:\n");
            	scanf("%d", &op);
            	scanf("%d", &i);
            	aux = buscar(op, *l);
            	aux2 = buscar(i, *l);
				troca(&aux, &aux2);
            	break;
 			case 8:
			 	 printf("\nForam armazenados: %d regiões\n", tam(*l)); 
			 break;	   
	 		case 9:
	 			/*printf("\nInsira qual campo será avaliado :\n\ncasos[1]\nobtos[2]\nincidencia[3]\nletalidade[4]\nmortalidade[5]\n");
				scanf("%d",&op);
				printf("\nA média do campo selecionado é: %f\n", somamedia(*l, op, 1));*/
				printf("\t EM MANUNTENÇÂO :-/\n");
	 			break;
 			case 10:
 				printf("\nInsira qual campo será avaliado :\n\ncasos[1]\nobtos[2]\nincidencia[3]\nletalidade[4]\nmortalidade[5]\n");
				scanf("%d",&op);
 				if(op > 0 && op < 3) {
 					printf("Total: %d", (int)somamedia(*l, op, 2));
				 }
			 	else {
			 		printf("Total: %f", (float)somamedia(*l, op, 2));//erro!!!!!!!!!!!!!!
				 } //a pessoa ainda pode digitar errado
 			break;
    	default:
    		printf("Por favor insira uma opção válida\n");
    		break;
	}
	system("pause");
}
void destroi(LISTA_REGIAO l) {
	LISTA_REGIAO aux;
	while(l) {
		aux = l;
		l = l->prox;
		free(aux);
	}
	free(l);
}
void registra(LISTA_REGIAO l) {
	FILE*registro;
	registro = fopen("RELATORIO.txt", "w");
	fprintf (registro,"\n\t\t\t\t\t\tRelatório Atualizado\n");
	
	fprintf(registro,"_______________________________________________________________________________________________________________\n");
	fprintf(registro, "|| %-20s | %-8s | %-8s | %-18s | %-18s | %-19s ||\n", "REGIÃO", "N° CASOS", "N° OBTOS", "TAXA DE INCIDENCIA", "TAXA DE LETALIDADE", "TAXA DE MORTALIDADE");
	fprintf(registro,"||____________________________________________________________________________________________________________||\n");
	while(l) {
		fprintf(registro, "|| %-20s | %8d | %8d | %18.2f | %18.2f | %19.2f ||\n", l->inf.regiao, l->inf.casos, l->inf.obtos, l->inf.incidencia, l->inf.letalidade,l->inf.mortalidade);
		l = l->prox;
	}
	fprintf(registro,"----------------------------------------------------------------------------------------------------------------");
	fclose(registro);
}
void imprimir(INF inf) {
	printf("|| %-20s | %-8d | %-8d | %-18f | %-18f | %-19f ||\n", inf.regiao, inf.casos, inf.obtos, inf.incidencia, inf.letalidade, inf.mortalidade);
	printf("%s","||____________________________________________________________________________________________________________||\n");
}
INF cadastro() {
	INF novo; 
	printf("\nInsira os valores a seguir:\n\n");
	printf("REGIÃO:  ");
	setbuf(stdin, NULL);
	scanf("%[^\n]",novo.regiao);
	printf("\nN° de casos:  ");
	scanf("%d", &novo.casos);
	printf("\nN° de obtos:  ");
	scanf("%d", &novo.obtos);
	printf("\ntaxa de incidencia:  ");
	scanf("%f", &novo.incidencia);
	printf("\ntaxa de letalidade:  ");
	scanf("%f", &novo.letalidade);
	printf("\ntaxa de mortalidade:  ");
	scanf("%f", &novo.mortalidade);
	return (novo);
}
char* maior(INF d1, INF d2, int op) { //dados 1, dado 2, posição a ser comparada
	char* aux;
	if(op < 2 || op > 6) {
		printf("\nVocê está tentando consultar um dado inválido ou inexistente\n"); 
	}
	switch (op) {
		   case 2:
				if(d1.casos > d2.casos) return d1.regiao;
				else if(d2.casos > d1.casos) return d2.regiao;
				else return "os campos dessas regiões são idênticos";
		   break;
		   case 3: 
				if(d1.obtos > d2.obtos) return d1.regiao;
				else if(d2.casos > d1.casos) return d2.regiao;
				else return "os campos dessas regiões são idênticos";
		   break;
		   case 4: 
				if(d1.incidencia > d2.incidencia) return d1.regiao;
				else if(d2.casos > d1.casos) return d2.regiao;
				else return "os campos dessas regiões são idênticos";
		   break;
		   case 5: 
				if(d1.letalidade > d2.letalidade)return d1.regiao;
				else if(d2.casos > d1.casos) return d2.regiao;
				else return "os campos dessas regiões são idênticos";

		   break;
		   case 6: 
				if(d1.mortalidade > d2.mortalidade) return d1.regiao;
				else if(d2.casos > d1.casos) return d2.regiao;
				else return "os campos dessas regiões são idênticos";
				
		   break;
	}
}
void percorrer(LISTA_REGIAO *p) {
	LISTA_REGIAO aux = *p;
	int i = 1;
	printf("Regiões cadastradas:\n\n");
			  while(aux) {
                  printf("%s[%d]\n", aux->inf.regiao, i++);
                  aux = aux->prox;
		      }
}
void troca(LISTA_REGIAO* r1, LISTA_REGIAO* r2) {
	INF aux;
	aux = (*r1)->inf;
	(*r1)->inf = (*r2)->inf;
	(*r2)->inf = aux;
}

float somamedia(LISTA_REGIAO l, int op, int operacao) {
	union {
		int v1;
		float v2;
	}val;   
	//optei por usar um union para explorar mais os recursos que linder apresentou e para poder lidar com os dois tipos de dados 
	int cont = 0;
	val.v1 = 0;
	val.v2 = 0;
	switch (op) {
			case 1:
		    while(l) {
			    val.v1+=l->inf.casos;
			    l = l->prox;
   		 	cont++;
		   }	 
			break;
			case 2:
			while(l) {
			    val.v1+=l->inf.obtos;
			    l = l->prox;
   			 cont++;
		   }
			break;
			case 3:
			while(l) {
			    val.v2+=l->inf.incidencia;
			    l = l->prox;
			cont++;
		   }
			break;
			case 4: 
				while(l) {
					printf("\nvalor: %f\n", val.v2);
					printf("\nvalor de cont %d\n",cont);
				val.v2+=l->inf.letalidade;
				l = l->prox;
			cont++;
			printf("Total: %f", val.v2/cont);
		    }
			break; 
			case 5:
				while(l) {
				val.v2+=l->inf.mortalidade;
				l = l->prox;
				cont++;
			}
			break;
	}
	if(operacao == 1) {
		if(op == 1 || 2) return( (float) (val.v1)/cont);
		else return(val.v2/cont);
	}
	else if(operacao == 2){
	    if(op == 1 || 2) return((float)val.v1);
		else return(val.v2);
	}
}
