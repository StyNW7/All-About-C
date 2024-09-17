#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const int SIZE = 10;

struct Movie {
	
	char id[11];
	char name[101];
	char description[101];
	long long int price;
	char email[101];
	
	Movie *next, *prev;
	
} *head[SIZE] = {NULL}, *tail[SIZE] = {NULL};


struct Movie* createNewNode(char id[], char name[], char desc[], long long int price, char email[]){
	
	struct Movie* node = (Movie*) malloc (sizeof(Movie));
	
	node->price = price;
	strcpy (node->description, desc);
	strcpy (node->id, id);
	strcpy (node->name, name);
	strcpy (node->email, email);
	
	node->next = NULL;
	node->prev = NULL;
	
	return node;
	
}


int hash (char id[]){
	
	int key = 0;
	
	for (int i = 2; i < 5; i++){
		key += (id[i] - '0');
	}
	
	return (key % SIZE);
	
}


void push (char id[], char name[], char desc[], long long int price, char email[]){
	
	struct Movie* node = createNewNode (id, name, desc, price, email);
	
	int index = hash(id);
	
	// Sorted alphabetical order ascendingly? by index or by id? I do both
	
	if (head[index] == NULL){
		head[index] = tail[index] = node;
	}
	
	else if (strcmp(head[index]->id, id) > 0){
		head[index]->prev = node;
		node->next = head[index];
		head[index] = node;
	}
	
	else if (strcmp(tail[index]->id, id) < 0){
		tail[index]->next = node;
		node->prev = tail[index];
		tail[index] = node;
	}
	
	else {
		
		struct Movie *curr = head[index];
		
		while (curr && strcmp(curr->id, id) < 0){
			curr = curr->next;
		}
		
		node->prev = curr->prev;
		node->next = curr;
		
		curr->prev->next = node;
		curr->prev = node;
		
	}
	
}

void viewOnly();
void printLogo();
void updateMovie();
void viewAll();
void insertMovie();
void printExit();


int main(){
	
	srand(time(0));
	
	int action;
	
	do {
		
		system ("cls");
		
		printLogo();
		
		puts ("1. Insert New Movie");
		puts ("2. View All Movies");
		puts ("3. Update Movie Price");
		puts ("4. Exit");
		
		printf ("\n>> ");
		scanf ("%d", &action);
		getchar();
		
		if (action == 1){
			insertMovie();
		}
		
		else if (action == 2){
			viewAll();
		}
		
		else if (action == 3) {
			updateMovie();
		}
		
		else if (action == 4){
			printExit();
		}
		
	}
	
	while (action != 4);
	
	return 0;
	
}

void insertMovie(){
	
	system ("cls");
	
	char name[101];
	char description[101];
	char email[101];
	long long int price;
	
	bool check = true, check2 = false;
	
	do {
		
		int space = 0;
		
		printf ("Input movie name [contains at least 2 words and unique]: ");
		scanf ("%[^\n]", name); getchar();
		
		for (int i = 0; i < strlen(name); i++){
			if (name[i] == ' ' && name[i+1] != ' ') space++;
		}
		
		if (space >= 1) check = false;
		
		// Unique name
		
		for (int i = 0; i < SIZE; i++){
		
			struct Movie *curr = head[i];
			
			while (curr){
				if (strcmp(curr->name, name) == 0) {
					check2 = true;
					break;
				}
				curr = curr->next;
			}
			
			if (check2) break;
			
		}
		
		if (check || check2) printf ("Invalid Input!\n\n");
		
	}
	
	while (check || check2);
	
	do {
		
		printf ("Input movie description [max. 50 characters, must not be empty]: ");
		scanf ("%[^\n]", description); getchar();
		
		if (strlen(description) != 0 && strlen(description) <= 50) break;
		else printf ("Invalid Input!\n\n");
		
	}
	
	while (true);
	
	do {
		
		printf ("Input movie price [50000 - 250000 (inclusive)]: ");
		scanf ("%lld", &price); getchar();
		
		if (price >= 50000 && price <= 250000) break;
		else printf ("Invalid Input!\n\n");
		
	}
	
	while (true);
	
	bool flag = true, flag2 = false, flag3 = false, flag4 = true;
	
	do {
		
		flag = true, flag2 = false, flag3 = false, flag4 = true;
		int index = -1;
		int dot = -1;
		
		printf ("Input producer email [must be in email format]: ");
		scanf ("%[^\n]", email); getchar();
		
		// I think the guide book is incorrect about this "Email must contain ‘.’ and the index must be after ‘@’"
		// Because there is no domain, however because it's written in the guide so I will follow it
		
		for (int i = 0; i < strlen(email); i++){
			
			if (email[i] == '@') {
				flag = false;
				index = i;
			}
			
			if (email[i] == '.') dot = i;
			
		}
		
		if (email[0] == '@') flag2 = true;
		if (email[strlen(email)-1] == '.') flag3 = true;
		
		// Follow guidebook
		
//		if (email[index+1] == '.') flag4 = false;
		
		// If the email must have a domain
		
		if (email[index+1] != '.' && strlen(email-1) != index && dot > index) flag4 = false;
		
		if (flag || flag2 || flag3 || flag4) printf ("Invalid Input!\n\n");
		
	}
	
	while (flag || flag2 || flag3 || flag4);
	
	char id[6] = "";
	
	for (int i = 0; i < 2; i++){
		if (name[i] >= 'a' && name[i] <= 'z'){
			id[i] = (name[i] - 32);
		}
		else id[i] = name[i];
	}
	
	for (int i = 2; i < 5; i++){
		int temp = rand() % 10;
		id[i] = (temp + 48);
	}
	
	push (id, name, description, price, email);
	
	printf ("\n\nSuccessfully inserted new movie!\n\n");
	printf ("Press enter to continue...");
	getchar();
	
}

void viewOnly(){
	
	for (int i = 0; i < 109; i++) printf ("=");
	puts ("");
	
	printf ("| %-5s | %-20s | %-40s | %-8s | %-20s |", "ID", "Name", "Description", "Price", "Producer Email");
	puts ("");
	
	for (int i = 0; i < 109; i++) printf ("=");
	puts ("");
	
	for (int i = 0; i < SIZE; i++){
		
		struct Movie *curr = head[i];
		
		while (curr){
			printf ("| %-5s | %-20s | %-40s | %-8d | %-20s |\n", curr->id, curr->name, curr->description, curr->price, curr->email);
			curr = curr->next;
		}
		
	}
	
	for (int i = 0; i < 109; i++) printf ("=");
	puts ("");
	puts ("");
	
}

void viewAll() {
	
	system ("cls");
	
	bool blank = true;
	
	for (int i = 0; i < SIZE; i++){
		
		struct Movie *curr = head[i];
		
		if (curr) blank = false;
		
		if (!blank) break;
		
	}
	
	if (blank){
		printf ("There is no movie yet!\n");
		printf ("Press enter to continue...");
		getchar();
		return;
	}
	
	// There is data
	
	viewOnly();
	
	printf ("Press enter to continue...");
	getchar();
	
}

void updateMovie() {
	
	system ("cls");
	
	// There is no movie yet
	
	bool blank = true;
	
	for (int i = 0; i < SIZE; i++){
		
		struct Movie *curr = head[i];
		
		if (curr) blank = false;
		
		if (!blank) break;
		
	}
	
	if (blank){
		printf ("There is no movie yet!\n");
		printf ("Press enter to continue...");
		getchar();
		return;
	}
	
	// Else
	
	viewOnly();
	
	puts("");
	
	char id[10];
	long long int price;
	
	do {
		
		bool flag = true;
		
		printf ("Input movie ID to update: ");
		scanf ("%s", id); getchar();
		
		for (int i = 0; i < SIZE; i++){
		
			struct Movie *curr = head[i];
			
			while (curr){
				if (strcmp(curr->id, id) == 0) {
					flag = false;
					break;
				}
				curr = curr->next;
			}
			
			if (!flag) break;
			
		}
		
		if (!flag) break;
		
	}
	
	while (true);
	
	do {
		
		printf ("Input movie price [50000 - 250000 (inclusive)]: ");
		scanf ("%lld", &price); getchar();
		
		if (price >= 50000 && price <= 250000) break;
		else printf ("Invalid Input!\n\n");
		
	}
	
	while (true);
	
	// Update Price
	
	bool check = true;
	
	for (int i = 0; i < SIZE; i++){
		
		struct Movie *curr = head[i];
		
		while (curr){
			if (strcmp(curr->id, id) == 0) {
				check = false;
				curr->price = price;
				break;
			}
			curr = curr->next;
		}
		
		if (!check) break;
		
	}
	
	printf ("\n\nPress enter to continue...");
	getchar();
	
}

void printExit(){
	
	system ("cls");
	
	printf ("Thanks for using this program :)\n\n");
	
	printf ("Made By: T091 - Stanley Nathanael Wijaya\n");
	
}

void printLogo(){
	
	puts ("   ___ _     __       __");
	puts ("  / __(_) /\\ \\ \\___  / / _ __ ___   __ _");
	puts (" / /  | |/  \\/ / _ \\/ / | '_ ` _ \\ / _` |");
	puts ("/ /___| / /\\  /  __/ /__| | | | | | (_| |");	
	puts ("\\____/|_\\_\\ \\/ \\___\\____/_| |_| |_|\\__,_|");
	puts ("");
	puts ("");
	
}

