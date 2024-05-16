#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>

typedef struct tree{
	int data;
	struct tree *left ,*right;
}Tree;


int pop(int *stack, int *top);
void push(int *stack , int data, int *top);
void printBottomUp(int *stack ,int *top);

Tree* insert(Tree *node, int data);
Tree* find(Tree *root, int data);
void inorder(Tree *t);
void visit(Tree *t);
Tree* createTree(char data);
Tree* deleteTree(Tree *t, int data);
Tree* findMin(Tree *t);
void print(int **arr, int n);

int main(){
	srand(time(NULL));
	setlocale(LC_ALL, "Turkish");
	int N;
	int M;
	int i, random, k, p, cont;
	Tree *tmp, *root;
	int **arr = (int**)calloc( 2 ,sizeof(int*));
	
	do{
		printf("Ka� tane farkl� meyve olmas�n� istersiniz? (M)\n");scanf("%d", &M);
		printf("\nHangi say� aral���nda meyve de�eri �retilsin? (1-N)\n");scanf("%d", &N);
	}while(N < M);
	
	for(i = 0; i < M; i++){
		arr[i] = (int*)calloc( M ,sizeof(int));
	}//Random olarak �retti�im say�y� bir yerde saklamam gerekiyor.
	
	int *stack = (int*)calloc( M+1 ,sizeof(int)); // Kovaya d��en meyve de�erlerini sakl�yoruz
	stack[0] = M; // Dizinin ilk g�z�n� stack verimin boyutunu tutuyorum
	int top = 0; 

	for(i = 0; i < M; i++){
		do{
			random = rand() % N + 1;
			tmp = find(root, random);
		}while(tmp != NULL); // Buradaki do-while d�ng�s� BST a�ac�mda daha �nce var olan veriyi ekleyemedi�im i�in kontrol etmem gerek.
		arr[0][i] = random; // �lk sat�rda maksimum meyve de�erlerini sakl�yorum.
		arr[1][i] = random;//ikinci sat�rda maksimum meyve de�erlerinin g�c�n� sakl�yorum.
		root = insert(root, random);
	}
	printf("Tutunma g�c�: \n"); print(arr, M); // Ekleni� s�ras�na g�re yazd�r�yorum
	printf("Inorder Gezinim: "); inorder(root);
	
	while(root != NULL){ // BST a�ac�mda veri kalmayana kadar oyunun devam etmesi gerek.
	cont = 0;	
	do{
		if(cont)
			printf("\nL�tfen var olan maksimum meyve de�erini(M) giriniz...\n");
		printf("\nMaksimum meyve de�erini(k) giriniz: \n"); scanf("%d", &k);
		printf("At���n g�c�n�(p) giriniz: \n"); scanf("%d", &p);
		tmp = find(root, k);
		cont = 1;
	}while(tmp == NULL); // Kullan�c�dan bilgi al�yoruz
	i = 0;
	cont = 1;
	while(i < M && cont){
		if(arr[0][i] == tmp->data && cont){ //Maksimum meyve de�erinin g�c�n� d���r�yoruz burada
			arr[1][i] -= p;
			cont = 0;
		}
		i++;
	}
	
	if(arr[1][i - 1] <= 0){
		root = deleteTree(root, tmp->data); // G�c� bitmi� meyveleri a�a�tan siliyoruz.
		push(stack, tmp->data, &top); // Art�k stack yap�ma atmam gerek. A�a�tan silindi�i i�in.
	}
	
	
	printf("Tutunma g�c�: \n"); print(arr, M);
	printf("Inorder Gezinim: "); inorder(root);printf("\n"); // Son durumlar� yaz�yoruz
	
	}
	
	printf("Kova: ");printBottomUp(stack , &top); // Oyun bittikten sonra ilk at�l�� s�ras�na g�re ekrana yazd�r�l�yor.
	return 0;
}

Tree* insert(Tree *node, int data){
	if(node == NULL) return createTree(data);
	
	if(data < node->data){
		node->left = insert(node->left, data);
	}
	else if(data > node->data)
		node->right = insert(node->right, data);
		
	return node;
}

Tree* find(Tree *root, int data){
	if(root != NULL && data > root->data)
		return find(root->right, data);
	else if(root != NULL && data < root->data)
		return find(root->left, data);
	else
		return root; 
}

void inorder(Tree *t){
	if(t == NULL) return;
	inorder(t->left);
	visit(t);
	inorder(t->right);
}

void visit(Tree *t){
	printf("%d ", t->data);
}

Tree* createTree(char data){
	Tree *T = (Tree*)malloc(sizeof(Tree));
	T->data = data;
	T->left = NULL;
	T->right = NULL;
	return T;
}

Tree* deleteTree(Tree *t, int data){
	if(t == NULL) return NULL;
	if(data < t->data)
		t->left = deleteTree(t->left, data);
	else if(data > t->data)
		t->right = deleteTree(t->right, data);
	else if(t->left != NULL && t->right != NULL){
		t->data = findMin(t->right)->data;
		t->right = deleteTree(t->right, t->data);
	}
	else
		t = (t->left != NULL) ? t->left : t->right;
	return t;
}

Tree* findMin(Tree *t){
	if(t && t->left)
		return findMin(t->left);
	else
		return t;
}

void print(int **arr, int n){
	int i, j;
	for(i = 0; i <= n; i++){
		if(arr[1][i] > 0)
			printf("%d de�erinde meyve: %d \n", arr[0][i], arr[1][i]);
	}
	printf("\n");
}

void push(int *stack , int data, int *top){ // Stack dolu degilse eleman� pushlar
	if( (*top) < stack[0]){
		(*top) += 1;
		stack[ (*top) ] = data;
	}
	else
		printf("FULL\n");
}

int pop(int *stack, int *top){ // Stackten eleman cekecegimiz zaman kullaniriz.
	int data;
	if(stack){
		data = stack[ (*top) ];
		(*top) -=1;
		return data;
	}
	
	printf("EMPTY\n");
	
	return -1;
	
}

void printBottomUp(int *stack ,int *top){
	int i;
	if( (*top) <= 0) return;
	i = pop(stack, top);
	printBottomUp(stack, top);
	printf("%d ", i);
}

