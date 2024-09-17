#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>


const int MAX_SIZE = 10;

// Trainee Number: T091 - Stanley Nathanael Wijaya


struct Music{
	
	char musicTitle[101];
	double musicRating;
	char artistName[101];
	char genre[101];
	
	Music *next, *prev;
	
} *head[MAX_SIZE], *tail[MAX_SIZE];



struct Music* createNewMusic(char musicTitle[], double musicRating, char artistName[], char genre[]){
	
	struct Music* newMusic = (Music*) malloc(sizeof(Music));
	
	strcpy (newMusic->artistName, artistName);
	strcpy (newMusic->genre, genre);
	strcpy (newMusic->musicTitle, musicTitle);
	
	newMusic->musicRating = musicRating;
	
	newMusic->next = NULL;
	newMusic->prev = NULL;
	
	return newMusic;
	
}


int hash (char title[]){
	
	int key = 0;
	
	for (int i = 0; i < strlen(title); i++){
		key += title[i];
	}
	
	// Last Trainee Number Digit = 1, it's actually doesn't change anything
	
	return ((key * 1) % MAX_SIZE);
	
}


void push (char musicTitle[], double musicRating, char artistName[], char genre[]) {
	
	struct Music *node = createNewMusic (musicTitle, musicRating, artistName, genre);
	
	int index = hash(musicTitle);
	
	// Push One
	
	if (head[index] == NULL){
		head[index] = tail[index] = node;
	}
	
	// Push Head
	
	else if (head[index]->musicRating > node->musicRating){
		
		node->next = head[index];
		head[index]->prev = node;
		
		head[index] = node;
		
		node->prev = NULL;
		
	}
	
	// Push Tail
	
	else if (tail[index]->musicRating < node->musicRating){
		
		tail[index]->next = node;
		node->prev = tail[index];
		tail[index] = node;
		
		tail[index]->next = NULL;
		
	}
	
	// Push Mid
	
	else {
		
		struct Music* curr = head[index];
		
		while (curr != NULL && curr->musicRating < node->musicRating){
			curr = curr->next;
		}
		
		if (curr){
			node->prev = curr->prev;
			node->next = curr;
			curr->prev->next = node;
			curr->prev = node;
		}
		
		// Just prevent error handling, so if null then push tail again
		
		else {
			tail[index]->next = node;
			node->prev = tail[index];
			tail[index] = node;
			tail[index]->next = NULL;
		}
		
	}
	
}


void pop (char name[]){
	
	int index = hash(name);
	
	// Not found just a boundary
	
	if (head[index] == NULL && tail[index] == NULL){
		return;
	}
	
	// Pop 1
	
	else if (head[index] == tail[index] && strcmp (head[index]->musicTitle, name) == 0){
		free (head[index]);
		head[index] = tail[index] = NULL;
	}
	
	// Pop Head
	
	else if (strcmp (head[index]->musicTitle, name) == 0){
		
		head[index] = head[index]->next;
		free (head[index]->prev);
		head[index]->prev = NULL;
		
	}
	
	// Pop Tail
	
	else if (strcmp (tail[index]->musicTitle, name) == 0){
		
		tail[index] = tail[index]->prev;
		free (tail[index]->next);
		tail[index]->next = NULL;
		
	}
	
	// Pop Mid
	
	else {
		
		Music* curr = head[index];
		
		while (curr != NULL && strcmp(curr->musicTitle, name) != 0){
			curr = curr->next;
		}
		
		if (curr){
			Music *a = curr->prev;
			Music *del = curr;
			Music *b = curr->next;
			
			a->next = b;
			b->prev = a;
			
			free (del);
			
//			curr->prev->next = curr->next;
//			curr->next->prev = curr->prev;
//			
//			free (curr);
//			curr = NULL;
			
		}
		
	}
	
}


void printLogo();
void printExit();

void red();
void green();
void yellow();
void blue();
void magenta();
void cyan();
void white();
void reset();
void randomClr();


void printOnly();
void addMusic();
void viewCollection();
void searchMusic();
void removeMusic();


void deleteMusicByPosition(int position, char musicName[]);


int main(){
	
	srand(time(0));
	
	int action;
	
	do {
		
		system ("cls");
		
		printLogo();
		
		puts ("\n1. Add Music");
		puts ("2. View Music Collection");
		puts ("3. Search Music");
		puts ("4. Delete Music");
		puts ("5. Exit\n");
		
		printf (">> ");
		scanf ("%d", &action); getchar();
		
		if (action == 1) {
			addMusic();
		}
		
		else if (action == 2){
			viewCollection();
		}
		
		else if (action == 3){
			searchMusic();
		}
		
		else if (action == 4){
			removeMusic();
		}
		
		else if (action == 5){
			printExit();
		}
		
		else {
			printf ("\n\n[!] Input between 1 - 5!");
			getchar();
		}
		
	}
	
	while (action != 5);
	
	return 0;
	
}


void addMusic(){
	
	system ("cls");
	
	printLogo();
	
	printf ("Add Music\n");
	puts ("=============");
	
	char title[101];
	char genre[101];
	char artist[101];
	double rating;
	
	do {
		
		printf ("\nInsert music title [more than 5 characters]: ");
		scanf ("%[^\n]", title); getchar();
		
		if (strlen(title) > 5) break;
		
		else printf ("\nMusic title must be more than 5 characters!\n");
		
	}
	
	while (true);
	
	do {
		
		printf ("\nInsert artist name [minimum 6 character, maximum 20 character]: ");
		scanf ("%[^\n]", artist); getchar();
		
		if (strlen(artist) >= 6 && strlen (artist) <= 20) break;
		
		else printf ("\nArtist name must be in range of 6 until 20 characters!\n");
		
	}
	
	while (true);
	
	do {
		
		printf ("\nInsert genre of the music [Pop | Soul | Rock]: ");
		scanf ("%s", genre); getchar();
		
		if (strcmp(genre, "Pop") == 0 || strcmp(genre, "Soul") == 0 || strcmp(genre, "Rock") == 0) break;
		
		else printf ("\nGenre must be Soul, Pop, or Rock\n");
		
	}
	
	while (true);
	
	do {
		
		printf ("\nInsert rating of the music [minimum 1 maximum 5.0]: ");
		scanf ("%lf", &rating); getchar();
		
		if (rating >= 1 && rating <= 5) break;
		
		else printf ("\nInput Invalid!\n");
		
	}
	
	while (true);
	
	push (title, rating, artist, genre);
	
	printf ("\n\nNew music successfully added!\n");
	printf ("Press enter to continue...");
	getchar();
	
}


void printOnly() {
	
	for (int i = 0; i < 73; i++) printf ("=");
	puts("");
	
	printf ("| %-20s | %-20s | %-10s | %-10s |\n", "Title", "Artist Name", "Genre", "Rating");
	
	for (int i = 0; i < 73; i++) printf ("=");
	puts("");
	
	bool blank = true;
	
	for (int i = 0; i < MAX_SIZE; i++){
		
		Music *curr = head[i];
		
		while (curr) {
			printf("| %-20s | %-20s | %-10s | %-4.1lf / %-3.1lf |\n", curr->musicTitle, curr->artistName, curr->genre, curr->musicRating, 5.0);
			curr = curr->next;
			blank = false;
		}
		
	}
	
	if (blank){
		printf ("| %-69s |\n", "There's no data yet...");
	}
	
	for (int i = 0; i < 73; i++) printf ("=");
	puts("");
	
}


void viewCollection(){
	
	system ("cls");
	
	printLogo();
	
	printf ("View Music Collection\n");
	
	printOnly();
	
	printf ("\n\nPress enter to continue...");
	getchar();
	
}


void searchMusic(){
	
	// Check blank or not
	
	bool blank = true;
	bool notFound = true;
	
	for (int i = 0; i < MAX_SIZE; i++){
		
		Music *curr = head[i];
		
		while (curr) {
			curr = curr->next;
			blank = false;
			break;
		}
		
		if (!blank) break;
		
	}
	
	system ("cls");
	
	printLogo();
	
	if (blank){
		
		printf ("\n\nThere is no music at this moment...");
		printf ("\nPress enter to continue");
		getchar();
		return;
		
	}
	
	printf ("Search Music\n");
	puts ("================");
	
	char musicName[101];
	
	printf ("Insert music name you want to search [0 to go back]: ");
	scanf ("%[^\n]", musicName); getchar();
	
	if (strcmp (musicName, "0") == 0) return;
	
	// Print the data
	
	for (int i = 0; i < MAX_SIZE; i++){
		
		Music *curr = head[i];
		
		while (curr) {
			if (strcmp(curr->musicTitle, musicName) == 0) {
				notFound = false;
				break;
			}
			curr = curr->next;
		}
		
		if (!notFound) break;
		
	}
	
	if (notFound) {
		
		printf ("\n\nMusic with title \"%s\" not found!", musicName);
		
	}
	
	else {
		
		printf ("Music Found!\n\n");
		
		for (int i = 0; i < 73; i++) printf ("=");
		puts("");
		
		printf ("| %-20s | %-20s | %-10s | %-10s |\n", "Title", "Artist Name", "Genre", "Rating");
		
		for (int i = 0; i < 73; i++) printf ("=");
		puts("");
		
		bool blank = true;
		
		for (int i = 0; i < MAX_SIZE; i++){
			
			Music *curr = head[i];
			
			while (curr) {
				if (strcmp(curr->musicTitle, musicName) == 0) printf("| %-20s | %-20s | %-10s | %-4.1lf / %-3.1lf |\n", curr->musicTitle, curr->artistName, curr->genre, curr->musicRating, 5.0);
				curr = curr->next;
				blank = false;
			}
			
		}
		
		for (int i = 0; i < 73; i++) printf ("=");
		puts("");
		
	}
	
	printf ("\n\nPress enter to continue...");
	getchar();
	
}


void deleteMusicByPosition(int position, char musicName[]) {
	
    int counter = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
    	
        Music *prev = NULL;
        Music *curr = head[i];

        while (curr) {
        	
            if (strcmp(curr->musicTitle, musicName) == 0) {
                counter++;
                if (counter == position) {
                    
                    if (prev) {
                        prev->next = curr->next;
                    } 
					
					else {
                        head[i] = curr->next;
                    }

                    free(curr);
                    curr = NULL;
                    return;
                    
                }
            }
            
            prev = curr;
            curr = curr->next;
            
        }
    }

}



void removeMusic(){
	
	// Check blank or not
	
	bool blank = true;
	bool notFound = true;
	int howMany = 0;
	
	for (int i = 0; i < MAX_SIZE; i++){
		
		Music *curr = head[i];
		
		while (curr) {
			curr = curr->next;
			blank = false;
			break;
		}
		
		if (!blank) break;
		
	}
	
	system ("cls");
	
	printLogo();
	
	if (blank){
		
		printf ("\n\nThere is no music at this moment...");
		printf ("\nPress enter to continue");
		getchar();
		return;
		
	}
	
	printf ("\nRemove Music\n");
	
	printOnly();
	
	char musicName[101];
	
	printf ("\nInsert music title you want to delete [0 to go back]: ");
	scanf ("%[^\n]", musicName); getchar();
	
	if (strcmp (musicName, "0") == 0) return;
	
	// Found or not or found more than one
	
	for (int i = 0; i < MAX_SIZE; i++){
		
		Music *curr = head[i];
		
		while (curr) {
			if (strcmp(curr->musicTitle, musicName) == 0) {
				notFound = false;
				howMany++;
			}
			curr = curr->next;
		}
		
	}
	
	// Print the data
	
	if (notFound) {
		
		printf ("\n\nMusic with title \"%s\" not found!", musicName);
		
	}
	
	else if (!notFound && howMany == 1){
		
		pop (musicName);
		
		printf ("Successfully delete music with title \"%s\"\n", musicName);
		
	}
	
	else {
		
		int counter = 1;
		
		system ("cls");
		printLogo();
		
		printf ("\n%d Music Found!\n\n", howMany);
		
		for (int i = 0; i < 79; i++) printf ("=");
		puts("");
		
		printf ("| %-3s | %-20s | %-20s | %-10s | %-10s |\n", "No", "Title", "Artist Name", "Genre", "Rating");
		
		for (int i = 0; i < 79; i++) printf ("=");
		puts("");
		
		for (int i = 0; i < MAX_SIZE; i++){
		
			Music *curr = head[i];
			
			while (curr) {
				if (strcmp(curr->musicTitle, musicName) == 0) {
					printf("| %-3d | %-20s | %-20s | %-10s | %-4.1lf / %-3.1lf |\n", counter, curr->musicTitle, curr->artistName, curr->genre, curr->musicRating, 5.0);
					counter++;
				}
				curr = curr->next;
			}
			
		}
		
		for (int i = 0; i < 79; i++) printf ("=");
		puts("\n");
		
		int del;
		
		do {
			
			printf ("Select music number you want to delete [1 - %d]: ", counter-1);
			scanf ("%d", &del);
			getchar();
			
			if (del >= 1 && del <= counter-1) break;
			
			else printf ("Number must be between 1 - %d!\n\n", counter-1);
			
		}
		
		while (true);
		
		int position = 1;
		
		for (int i = 0; i < MAX_SIZE; i++){
		
			Music *curr = head[i];
			
			while (curr) {
				if (strcmp(curr->musicTitle, musicName) == 0) {
					if (position == del){
						deleteMusicByPosition(position, musicName);
					}
					position++;
				}
				curr = curr->next;
			}
			
		}
		
		printf ("\nSuccessfully delete music with title \"%s\"", musicName);
		
	}
	
	printf ("\n\nPress enter to continue...");
	getchar();
	
}


void red(){
	printf ("\033[1;31m");
}

void green(){
	printf ("\033[1;32m");
}

void yellow(){
	printf ("\033[1;33m");
}

void blue(){
	printf ("\033[1;34m");
}

void magenta(){
	printf ("\033[1;35m");
}

void cyan(){
	printf ("\033[1;36m");
}

void white(){
	printf ("\033[1;37m");
}

void reset(){
	printf ("\033[1;0m");
}

void randomClr(){
	
	int randColor = rand() % 7;
	
	if (randColor == 0) red();
	if (randColor == 1) green();
	if (randColor == 2) yellow();
	if (randColor == 3) blue();
	if (randColor == 4) magenta();
	if (randColor == 5) cyan();
	if (randColor == 6) white();
	
}

void printExit (){
	
	system("cls");
	
	white();
	printf ("  _______ _                 _        \n");
	printf (" |__   __| |               | |       \n");
	printf ("    | |  | |__   __ _ _ __ | | _____ \n");
	printf ("    | |  | '_ \\ / _` | '_ \\| |/ / __|\n");
	printf ("    | |  | | | | (_| | | | |   <\\__ \\\n");
	printf ("    |_|  |_| |_|\\__,_|_| |_|_|\\_\\___/\n");
	printf ("\n\n");
	
	char word[] = {"Program Made By: T091 - Stanley Nathanael Wijaya"}; Sleep (200);
	
	for (int i = 0; i < strlen(word); i++){
		randomClr();
		printf ("%c", word[i]);
		Sleep(50);
	}
	
	reset();
	
	puts("\n");
	
	char word2[] = {"Thanks for using this program"}; Sleep (300);
	
	for (int i = 0; i < strlen(word2); i++){
		randomClr();
		printf ("%c", word2[i]);
		Sleep(50);
	}
	
	Sleep (450);
	
	reset();
	
	system ("cls");
	
	printf ("                                                    ........::::........\n"); Sleep(100);
    printf ("                                             ............:::::::::::...........\n"); Sleep(100);
    printf ("                                          .......::--==================---::.......\n"); Sleep(100);
    printf ("                                      .....:::--==+++*####%%%%%%%%%%%%%%%%####*++====--::.....\n"); Sleep(100);
    printf ("                                    ....::--==+*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%#%%%%%%%%%%%%%%%%%%%%%%#*+==---:.....\n"); Sleep(100);
    printf ("                                  ...::--=+*##%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#*+=---:....\n"); Sleep(100);
    printf ("                                ....:-=+*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##*=---:....\n"); Sleep(100);
    printf ("                              ....:-=*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##%%%%%%%%%%%%%%%%%%%%%%%%%%%%#+=--:....\n"); Sleep(100);
    printf ("                            ....:-=*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%####%%%%##%%%%%%%%%%%%%%%%%%%%%%%%#+--::...\n"); Sleep(100);
    printf ("                           ..:.:-+#%%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##%%%%%%%%%%%%%%%%###%%#*+**%%#**####%%%%%%%%%%%%%%%%%%%%#+--:...\n"); Sleep(100);
    printf ("                          ..:::=*%%%%%%%%%%%%%%%%%%%%%%##%%%%%%%%%%%%**#%%###%%%%#**#%%*+=+=#*++**++#%%%%#%%%%%%%%%%%%%%%%*-:::...\n"); Sleep(100);
    printf ("                         ..:::+#%%%%%%%%%%%%%%%%%%%%%%%%########++#%%***#**+++#+=---++--==-=*%%%%%%%%%%%%%%%%%%%%%%%%#=:::...\n"); Sleep(100);
    printf ("                        ..::-*#%%%%%%%%%%%%%%%%%%%%%%%%%%*+**+*##==+*===*=+-=-+--:::=-:::-::*%%%%%%%%%%%%%%%%%%%%%%%%%%#+:::..\n"); Sleep(100);
    printf ("                       ..:::+#%%#%%%%%%%%%%%%%%%%%%%%%%#+==+==++--=+:--=--:::-:...... ..:-=*%%%%%%%%%%%%%%%%%%%%%%%%%%%%#+:-:.\n."); Sleep(100);
    printf ("                       .:::+#%%%%%%%%%%%%%%%%%%%%%%%%%%#*---=---=:::-.:.:.... ::--=+**#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#=:-...\n"); Sleep(100);
    printf ("                      ..:.=#%%%%%%%%%%%%%%%%%%%%%%%%%%%%#+::::...:   ..:-=+++*#%%%%###%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*-:-..\n"); Sleep(100);
    printf ("                      .:::*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%*-...:--=+*##%%%%%%%%%%%%#++##%%#**%%%%%%%%%%%%%%%%%%###%%%%%%#%%%%%%%%%%%%%%%%%%%%#+:-:..\n"); Sleep(100);
    printf ("                     ..:.=#%%%%%%%%%%%%%%%%%%%%%%#%%%%%%*::+***#%%%%%%###%%%%%%%%%%*==+*#+++%%###%%%%%%%%%%**#%%%%%%%%%%%%%%%%%%%%%%%%%%%%#*-:-..\n"); Sleep(100);
    printf ("                     ..:.+#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%+-=*+=+*###**#%%%%%%%%%%*-:==+===#*++%%####++*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*-:-..\n"); Sleep(100);
    printf ("                     ..::+#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*--==-==**#++*####%%+..::-:::+===#**++==+#%%%%%%%%%%%%%%%%%%%%%%%%%%%%#=:-:.\n"); Sleep(100);
    printf ("                     ...:+###############%%*:.:-:--+=+==*#**#%%*=--.. ..-:::+==-=:-=*###############=:::.\n"); Sleep(100);
    printf ("                     ...:+#################+..:..:--=:-=+==*#**#####*+=-:.:.:.:.:-=##############*=-::.\n"); Sleep(100);
    printf ("                     ...:=###################=-.  ..:..:-:-=+=+*###########*+=-...-*#############*--:..\n"); Sleep(100);
    printf ("                      ::.-+*######################*+=-:.....:-:-+***#############*-.+#############+:-:..\n");
    printf ("                      .:.:-*####################***#####*+=--:.=+++*****#***#****=-+############*=--:.\n");
    printf ("                       ..:-=*******#************++************++===**+=+*+++*++==-:+*********#**+--:..\n");
    printf ("                       .:.:-=*****#@@#******+++*===+===+==---+--:::--:::-:::-.:...+*********#@#=--:..\n");
    printf ("                        .:.--=+***%%@@%%*****+===+---=---=--:::-::...::.... . ..:-+**********#%%%%+=-:..\n");
    printf ("                         .:.--+*#%%%%@@@#****+----:::-.:.:.:...:.   ..::--==++++++++***#%%****##+==:..\n");
    printf ("                          ...-=+#@@@@@%%%%*+*+:.::....   ...::--===+++++++++++++++*++#@@%%+#%%*===:..\n");
    printf ("                           ...:==#%%@@@@@*+%%*  .:::--==+++++++++++++++++++++++++*@%%++%%@@%%##+==-:..\n");
    printf ("                             ..:-=+%%@@@#+%%@@++++++++++++++*#+++++++++++*+++++++%%@%%#%%%%@@%%+-==-..\n");
    printf ("                              ...:-=+%%@@@@@@%%++++++++++++*%%@#++++++++++@%%++++*%%@@@@@@%%#+==-:..\n");
    printf ("                                ..::-=+#%%@@@@%%+=+*@*====+#@@%%*=======+%%@@*+==*@@@@%%%%*+==-:..\n");
    printf ("                                  ..::--=+#%%@%%==+@@%%+==+%%@@@@*+++===+*%%@@%%+=#%%@@%%*+===-:..\n");
    printf ("                                    ...::--=+***#@@@*==*@@@@@@%%#%%+==*@@@@@##%%#*+===-::..\n");
    printf ("                                      ....:-----+*#%%%%***%%@@@@@%%@@*==+%%%%%%#*+====--::..\n");
    printf ("                                         ....::-------=++********+=====-------::..\n");
    printf ("                                              ....::---======--=====-----::...\n");
    printf ("                                                    ........::::........\n");

    puts ("\n                                  \"Inspired by passion, driven by purpose, together we"); Sleep(100);
    puts ("                                        shatter limits and redefine boundaries.\"\n"); Sleep(100);
	
}


void printLogo(){
	
	puts ("  _    _                                        _    _ _    _ ____");
	puts (" | |  | |                                      | |  | | |  | |  _ \\");
	puts (" | |__| | __ _ _ __ _ __ ___   ___  _ __  _   _| |__| | |  | | |_) |");
	puts (" |  __  |/ _` | '__| '_ ` _ \\ / _ \\| '_ \\| | | |  __  | |  | |  _ <");
	puts (" | |  | | (_| | |  | | | | | | (_) | | | | |_| | |  | | |__| | |_) |");
	puts (" |_|  |_|\\__,_|_|  |_| |_| |_|\\___/|_| |_|\\__, |_|  |_|\\____/|____/");
	puts ("                                           __/ |");
	puts ("                                          |___/");
	puts ("");
	
}


