#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct node {
	int data;
	struct node *next; 
	struct node *prev;
}Node;

Node* random(Node * head, int M, int N);
void print(Node *head, int M);
int control(Node* lock, Node* lock2, Node* lock3, int *repetated_number, int* location_number);
void hesapla(int *location_number, int M);
void result(Node* lock, int *location_number, int number);

int main(){
	setlocale(LC_ALL, "Turkish");
	
	int N; // Linked Listenin data deðer aralýðý
	int M; //Linked Listenin uzunluðu
	int i;
	int cont;
	
	
	srand(time(0));
	while(1){
		system("cls");
	do{
		
	Node *lock = NULL; //Kasalarýn çarklarýnýn head kýsmý
	Node *lock2 = NULL;
	Node *lock3 = NULL;
	do{
		printf("Sýrasýyla N ve M deðerlerini girer misiniz?\n");
		scanf("%d %d", &N, &M);	
	}while(N <= M);
	
	int *repetated_number = (int*)malloc( (N+1) * sizeof(int)); // Kasa listeleri oluþtururken iþe yarayacak
	int * location_number = (int*)malloc( 4 * sizeof(int)); // Ortak sayi  nerede onu tutuyor
	
	
	for(i = 0; i <= N; i++){ //
		repetated_number[i] = 0;
	}
	for(i = 0; i < 4; i++){
		location_number[i] = 0;
	}
	printf("N=%d, M=%d olmak üzere, üç çarkýn üzerindeki sayýlar þu þekildedir: \n",N,M);
	lock = random(lock, M, N);
	lock2 = random(lock2, M, N);
	lock3 = random(lock3, M, N);
	
	print(lock, 1);
	print(lock2, 2);
	print(lock3, 3);
	
	cont = control(lock, lock2, lock3, repetated_number, location_number);
	if(cont > 0){
		hesapla(location_number, M);
		printf("Çarklarýn son hali\n");
		print(lock, 1);
		result(lock2, location_number, 2);
		result(lock3, location_number, 3);
	}
	else{
		system("cls");
		printf("Hata oluþtu tekrar girer misiniz\n");
	}
		
	
	}while(cont <= 0);
	
	
	
		
	
	printf("\n");
	
	

	system("pause");
}
	
	return 0;
}



Node* random(Node * head, int M, int N){
	int i, random;
	Node *current = (Node*)malloc(sizeof(Node));
	int number[N];
	for(i = 0; i < N; i++){
		number[i] = i + 1;
	}
	for(i = 0; i < M; i++){
		Node *tmp = (Node*)malloc(sizeof(Node));
		do{//Ayný zincirde birden fazla ayný sayý olamaz.
			random = ( rand() % N ) + 1;
		}while(number[random] == -1);
		number[random] = -1;
		
		if(head == NULL){
			current->data = random;
			current->next = NULL;
			current->prev = NULL;
			head = current;
		}
		else{
			tmp->data = random;
			current->next = tmp;
			tmp->prev = current;
			tmp->next = NULL;
			current = current->next;
		}
	}
	current->next = head;
	head->prev = current;
	
	return head;
	
}

void print(Node *head, int M){
	Node *tmp = head;
	printf("%d. çark: ", M);
	do{
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}while(tmp != head);
	printf("\n");
}

int control(Node* lock, Node* lock2, Node* lock3, int *repetated_number, int* location_number){
	Node* current_node = lock;
	int flag = 0; int flag2 = 0;
	int i = 1;
	do{
		repetated_number[current_node->data]++;
		current_node = current_node->next;
	}while(current_node != lock);
	
	current_node = lock2;
	do{
		repetated_number[current_node->data]++;
		current_node = current_node->next;
	}while(current_node != lock2);
	
	current_node = lock3;
	do{
		repetated_number[current_node->data]++;
		if(repetated_number[current_node->data] == 3 && flag == 0)
			flag = current_node->data;
		else if(repetated_number[current_node->data] == 3){
			return 0;
		}
			
		current_node = current_node->next;
		
	}while(current_node != lock3);
	
	if(flag == 0){
		return 0;	
	}
	
	current_node = lock;
	Node* current_node2 = lock2;
	Node* current_node3 = lock3;
	do{
		if(current_node->data == flag){
			location_number[1] = i;
			flag2++;
		}
		else if(current_node2->data == flag){
			location_number[2] = i;
			flag2++;
		}
		else if(current_node3->data == flag){
			location_number[3] = i;
			flag2++;
		}
		current_node = current_node->next;
		current_node2 = current_node2->next;
		current_node3 = current_node3->next;
		i++;
			
	}while(current_node != lock);
	
	if(flag2 != 3){
		return 0;
	}
		
		
	printf("Ortak sayi: %d\n", flag);
	for(i = 1; i <= 3 ; i++){
		printf("%d. carktaki konumu: %d\n", i, location_number[i]);
	}
	
	return flag;
	
}

void hesapla(int *location_number, int M){
	int i, a, b;
	int min, tmp;
	for(i = 2; i <= 3; i++){
		min = (location_number[1] - location_number[i]);
		if(min > 0){
			tmp = -(M - location_number[1] + location_number[i]);
		}
		else{
			tmp = (M - location_number[i] + location_number[1]);
		}
		a = abs(min); b = abs(tmp);
		if(b < a)
			min = tmp;
		
			
		location_number[i] = min;
		
			
	}
	
	for(i = 2; i <= 3;i++ ){
		a = abs(location_number[i]);
		if( a == M/2 && M % 2 == 0)
			printf("%d.çark Saat yönünde %d adým çevrilmeli (Not: Saatin ters yönünde de %d adým çevrilebilir.)\n", i, M/2, M/2);
		else if(location_number[i] > 0)
			printf("%d.çark Saat yönünde %d adým çevrilmeli\n", i, location_number[i] );
		else
			printf("%d.çark Saatin ters yönünde %d adým çevrilmeli\n", i, -location_number[i] );
	}
	printf("\n");
	
}

void result(Node* lock, int *location_number, int number){
	int i;
	Node *current;
	int size = abs(location_number[number]);
	for(i = 0; i < size;i++){
		
		if(location_number[number] > 0)
			lock = lock->prev;
		else
			lock = lock->next;
	}
	
	current = lock;
	printf("%d. çark: ", number);
	do{
		printf("%d ", current->data);
		current = current->next;
	}while(current != lock);
	printf("\n");
}
