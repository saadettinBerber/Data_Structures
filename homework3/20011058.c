#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct node{
	int id;
	struct node* next;
}Node;

typedef struct ders{
	Node *head;
	int name;
	struct ders* next;
	int count;
} Ders;

void printMatris(int **matris, int N);
void printCourse(int *p, int N);
void printAdjcencyList(Ders *head);
Node* createNode(int id);
Ders* makeAdjancyList(int **matris, int N);
int* hesaplama(Ders** dersler2, int N);
void input(int **matris, int N);

int main(){
	setlocale(LC_ALL, "Turkish");
	int i, N;
	printf("Kaç tane ders var. Giriniz:"); scanf("%d", &N);
	int **matris = (int**)calloc(N, sizeof(int*));
	for(i = 0; i < N; i++){
		matris[i] = (int*)calloc(N, sizeof(int));
	}
	printf("Hangi dersler birbirine baðlý ise belirtiniz. Eðer çýkmak isterseniz 0 giriniz\n");
	input(matris, N);
	
	printMatris(matris, N);
						
	Ders *dersler = makeAdjancyList(matris,N);
	printf("\tDersler ve Ön Þart Dersleri\n");
	printAdjcencyList(dersler);
	int counter = 1;
	int *p;
	printf("\tHer Dönem Alabileceði Dersler(Hepsinden Geçen Öðrencinin)\n");
	while(dersler){
		p = hesaplama(&dersler, N);
		printf("%d. dönem verdiði dersler: ", counter);
		printCourse(p, N);
		printf("\n");
		counter++;
	}
	printf("Buna göre öðrenci %d dönemde mezun olur ve son döneminde ", --counter);
	printCourse(p, N);
	printf("dersini/derslerini alýr.");
	return 0;
}

void printMatris(int **matris, int N){
	int i,j;
	printf("\tAdjaceny Matris\n");
	for(i = 0; i < N; i++){
		for(j = 0;  j < N;j++){
			printf("%d ", matris[i][j]);
		}
		printf("\n");
	}
}

Ders* makeAdjancyList(int **matris, int N){
	Ders *original;
	Ders *copyOriginal;
	int i, j;
	for(i = 0; i < N; i++){
		Ders *ders = (Ders*)malloc(sizeof(Ders));
		ders->count = 0;
		ders->next = NULL;
		ders->head = NULL;
		ders->name = i+1;
		for(j = 0; j < N; j++){
			if(matris[j][i] == 1){
				if(ders->head == NULL){
					ders->head = createNode(j+1);
					ders->count++;
				}
				else{
					Node* tmp = createNode(j+1);
					tmp->next = ders->head;
					ders->head = tmp;
					ders->count++;
				}
			}
		}
		if(i== 0){
			original = ders;
			copyOriginal = original;
		}
		else{
			copyOriginal->next = ders;
			copyOriginal = copyOriginal->next;
		}
		
	}
	return original;
}

Node* createNode(int id){
	Node* tmp = (Node*)malloc( sizeof(Node) );
	tmp->id = id;
	tmp->next = NULL;
	return tmp;
}

void printAdjcencyList(Ders *ders){
	while(ders != NULL){
		printf("%d. dersin baðlý olduðu dersler(%d) : ", ders->name, ders->count);
		Node* tmp = ders->head;
		while(tmp){
			printf("%d ", tmp->id);
			tmp = tmp->next;
		}
		printf("\n");
		ders = ders->next;
	}
}

int* hesaplama(Ders** dersler2, int N){
	Ders *dersler = *dersler2;
	Ders *tmp = dersler;
	int counter = 0;
	int *dizi = (int*)calloc( (N+1) ,sizeof(int));
	Ders* prev = NULL;
	while(tmp){
		if(tmp->count == 0){
			dizi[tmp->name] = tmp->name;
			if(prev == NULL){
				dersler = tmp->next;
				tmp = dersler;
			}
			else{
				prev->next = tmp->next;
				tmp = tmp->next;
			}
		}
		else{
			prev = tmp;
			tmp = tmp->next;
		}
		
	}
	tmp = dersler;
	while(tmp){
		Node* curr = tmp->head;
		Node* prev2 = NULL;
		while(curr){
			counter = checked(dizi, N, curr->id);
			if(counter > 0){
				if(prev2 == NULL){
					tmp->head = curr->next;
					curr = curr->next;
				}
				else{
					prev2->next = curr->next;
					curr = curr->next;
				}
				tmp->count--;
			}
			else{
				prev2 = curr;
				curr = curr->next;
			}
			
		}
		tmp = tmp->next;
	}
	(*dersler2) = dersler;
	return dizi;
}

int checked(int *dizi, int N, int id){
	int i;
	for(i = 1;i <= N; i++){
		if(dizi[i] == id){
			return id;
		}
	}
	return -1;
}

void printCourse(int *p, int N){
	int i;
	for(i = 0; i <= N; i++){
			if(p[i] != 0){
				printf("Course-%d ", p[i]);
			}
		}
}

void input(int **matris, int N){
	int i,j;
	do{
		printf("Dersi seçiniz: "); scanf("%d", &i);
		if(i<=N && i>=1){
			printf("Seçili olan ders hangi derse baðlý: "); scanf("%d", &j);
			if(i != j && j<=N && j>=1)
				matris[j-1][i-1] = 1;
			else if(i != 0)
				printf("sayýyý %d< <%d aralýðýnda girin.\n", 1, N);
		}
		else if(i != 0){
			printf("sayýyý %d< <%d aralýðýnda girin.\n", 1, N);
		}
		
	}while(i != 0);
}







