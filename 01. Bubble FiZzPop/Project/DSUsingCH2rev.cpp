#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>


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
void playGame();
void printTutorial();
void gotoxy(int x, int y);
void printLeaderBoard();
void bubbleSort(char username[][101], int score[], int n);


int main(){
	
	srand(time(0));
	
	printLogo();
	
	puts ("Welcome to Bubble FizzPop!\n");
	
	printf ("Press enter to continue...");
	getchar();
	
	int action;
	
	do {
		
		system ("cls");
		
		printLogo();
		
		puts ("\n1. Play");
		puts ("2. How to Play");
		puts ("3. Leaderboard");
		puts ("4. Exit");
		
		printf ("\n>> ");
		scanf ("%d", &action); getchar();
		
		if (action == 1) {
			playGame();
		}
		
		else if (action == 2){
			printTutorial();
		}
		
		else if (action == 3){
			printLeaderBoard();
		}
		
		else if (action == 4){
			printExit();
		}
		
		else {
			printf ("\n[!] Input must be between 1 and 3");
			getchar();
		}
		
	}
	
	while (action != 4);
	
	return 0;
	
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

void playGame(){
	
	system ("cls");
	
	char username[101];
	
	do {
		printf ("Input your username: ");
		scanf ("%[^\n]", username); getchar();
		if (strlen(username) >= 1) break;
	}
	
	while (true);
	
	system ("cls");
	
	// Play Game
	
	char matrix[19][19];
	int balls = 0;
	
	// Asumsi maksimal row = 15
	
	for (int i = 0; i < 7; i++){
		
		for (int j = 0; j < 18; j++){
			
			int digit = rand() % 3 + 1;
			
			matrix[i][j] = digit + '0';
			++balls;
			
		}

	}
	
	for (int i = 7; i < 18; i++){
		for (int j = 0; j < 18; j++){
			matrix[i][j] = ' ';	
		}
	}
	
	for (int z = 7; z < 18; z++){
		if (z == 16) matrix[z][9] = '^';
		else if (z == 17) matrix [z][9] = 'A';
		else matrix[z][9] = '.';
	}
	
	int shooter = 9;
	int ballsRow = 6;
	int shot = 10;
	
	long long int score = 0;
	bool gameOver = false;
	bool win = true;
	
	do {
		
		system ("cls");
		
		// Print Game
		
		int column = -1;
			
		for (int i = 16; i >= 0; i--){
			if (matrix[i][shooter] == '1' || matrix[i][shooter] == '2' || matrix[i][shooter] == '3'){
				column = i;
				break;
			}
		}
		
		for (int z = column+1; z < 18; z++){
			if (z == 16) matrix[z][shooter] = '^';
			else if (z == 17) matrix [z][shooter] = 'A';
			else matrix[z][shooter] = '.';
		}
		
		for (int i = 0; i < 20; i++){
			printf ("#");
		}
		
		puts("");
		
		for (int a = 0; a < 18; a++){
		
			reset();
			
			printf ("#");
			
			for (int b = 0; b < 18; b++){
				
				if (matrix[a][b] == '1'){
					red();
				}
				
				else if (matrix[a][b] == '2'){
					green();
				}
				
				else if (matrix[a][b] == '3'){
					yellow();
				}
				
				printf ("%c", matrix[a][b]);
				
				reset();
				
			}
			
			puts("#");
			
		}
		
		for (int i = 0; i < 20; i++){
			printf ("#");
		}
		
		// Print Details
		
		gotoxy (22, 7);
		printf ("Score: %lld\n\n", score);
		gotoxy (22, 9);
		printf ("Remaining Balls: %d\n", balls);
		
		gotoxy(0, 21);
		
		// Action
		
		char action = '0';
		
		action = getch();
		
		if (action == 'a'){
			
			// Left
			
			if (shooter <= 0) continue;
			
			int column = -1, columnPrev = -1;
			
//			for (int i = 0; i < 18; i++){
//				if (matrix[i][shooter-1] != '1' && matrix[i][shooter-1] != '2' && matrix[i][shooter-1] != '3'){
//					column = i;
//					break;
//				}
//			}
			
			// Change idea to check (before from zero index, revise to from shooter position index)
			
			for (int i = 16; i >= 0; i--){
				if (matrix[i][shooter-1] == '1' || matrix[i][shooter-1] == '2' || matrix[i][shooter-1] == '3'){
					column = i;
					break;
				}
			}
			
			for (int i = 16; i >= 0; i--){
				if (matrix[i][shooter] == '1' || matrix[i][shooter] == '2' || matrix[i][shooter] == '3'){
					columnPrev = i;
					break;
				}
			}
			
			for (int z = column+1; z < 18; z++){
				if (z == 16) matrix[z][shooter-1] = '^';
				else if (z == 17) matrix [z][shooter-1] = 'A';
				else matrix[z][shooter-1] = '.';
			}
			
			for (int z = columnPrev+1; z < 18; z++){
				matrix[z][shooter] = ' ';
			}
			
//			printf ("%d\n", columnPrev);
//			getchar();
			
			shooter--;
			
		}
		
		else if (action == 'd'){
			
			// Right
			
			if (shooter >= 17) continue;
			
			int column = -1, columnPrev  = -1;
			
			for (int i = 16; i >= 0; i--){
				if (matrix[i][shooter+1] == '1' || matrix[i][shooter+1] == '2' || matrix[i][shooter+1] == '3'){
					column = i;
					break;
				}
			}
			
			for (int i = 16; i >= 0; i--){
				if (matrix[i][shooter] == '1' || matrix[i][shooter] == '2' || matrix[i][shooter] == '3'){
					columnPrev = i;
					break;
				}
			}
			
			for (int z = column+1; z < 18; z++){
				if (z == 16) matrix[z][shooter+1] = '^';
				else if (z == 17) matrix [z][shooter+1] = 'A';
				else matrix[z][shooter+1] = '.';
			}
			
			for (int z = columnPrev+1; z < 18; z++){
				matrix[z][shooter] = ' ';
			}
			
			shooter++;
			
		}
		
		else if (action == ' '){
			
			// Shoot
			
			int row = -1;
			
//			for (int i = 0; i < 18; i++){
//				if (matrix[i][shooter] != '1' && matrix[i][shooter] != '2' && matrix[i][shooter] != '3'){
//					row = i;
//					break;
//				}
//			}
			
			// Revised
			
			for (int i = 16; i >= 0; i--){
				if (matrix[i][shooter] == '1' || matrix[i][shooter] == '2' || matrix[i][shooter] == '3'){
					row = i;
					break;
				}
				
				// Animation 
				
//				gotoxy (i, shooter);
//				matrix[i][shooter] = 'A';
//				Sleep(100);
				
			}
			
			for (int a = row; a < row+3; a++){
				for (int b = shooter-1; b < shooter+2; b++){
					
					if (matrix[a][b] == '1'){
						matrix[a][b]  = ' ';
						score += 10;
						balls--;
					}
					
					else if (matrix[a][b] == '2'){
						matrix[a][b]  = '1';
						// Contoh mendapatkan 1 poin, asumsi (2-1), based on PDF Guide +2 points
						score += 2;
					}
					
					else if (matrix[a][b]  == '3'){
						matrix[a][b]  = '2';
						// Contoh mendapatkan 2 poin, asumsi (3-1), based on PDF Guide +3 points
						score += 3;
					}

				}
				puts("");
			}
			
			shot--;
			
			// Rows checker
		
			for (int i = 0; i < 18; i++){
				
				bool flag = false;
				for (int j = 0; j < 18; j++){
					if (matrix[i][j] != ' ') {
						flag = true;
						break;
					}
				}
				
				if (!flag) {
					ballsRow = i;
					break;
				}
				
			}
			
			// New Layer Condition
			
			if (shot == 0){
				
				shot = 10;
				
				for (int a = ballsRow+1; a > 0; a--){
					for (int b = 0; b < 18; b++){
						matrix[a][b] = matrix[a-1][b];
					}
				}
				
				for (int z = 0; z < 18; z++){
					int digit = rand() % 3 + 1;
					matrix[0][z] = digit + '0';
					++balls;
				}
				
				ballsRow++;
				
			}
			
//			getchar();
			
		}
		
		else if (action == 13){
			break;
		}
		
		// Losing Condition
		
		for (int i = 0; i < 18; i++){
			if (matrix[15][i] == '1' || matrix[15][i] == '2' || matrix[15][i] == '3') {
				
				printf ("The game is over!\n\n");
				printf ("You got %lld score\n", score);
				printf ("Press enter to continue...");
				getchar();
				gameOver = true;
				break;
				
			}
		}
		
		// Winning Condition
		
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if (matrix[i][j] != ' ') {
					win = false;
					break;
				}
			}
			if (!win) break;
		}
		
		if (win){
			printf ("\nCongratz, You Win the Game with %lld Score!\n\n", score);
			printf ("Press enter to continue...");
			getchar();
		}
		
		if (gameOver) break;
		if (win) break;
		
	}
	
	while (true);

	FILE *input = fopen("data.txt", "a");
	
	fprintf (input, "%s#%lld\n", username, score);
	
	fclose (input);
	
}

void printTutorial(){
	
	int page = 1;
	char c;
	
	do {
		
		system ("cls");
		
		printLogo();
		puts("");
		
		if (page == 1){
			
			puts ("			Page 1-3                D ->                    Enter : Exit Tutorial\n");
			puts ("Welcome to Bubble FizzPop! Your mission is to clear the game board");
			puts ("by strategically shooting balls to destroy designated targets.\n");

			puts ("All you have to do is destroy the specified number of balls to win the game.");
			puts ("Be strategic and efficient in your shots to survive!\n");
			
		}
		
		else if (page == 2){
			
			puts ("<- A			Page 2-3                D ->                    Enter : Exit Tutorial\n");
			
			puts ("Controls\n");
			puts ("--------");
			puts ("1. Use A and D keys to move your aiming cursor.");
			puts ("2. Press the spacebar to shoot a ball towards the targeted position.\n");
			
		}
		
		else if (page == 3){
			
			puts ("<- A			Page 3-3                D ->                    Enter : Exit Tutorial\n");
			
			puts ("Gameplay\n");
			puts ("-----------");
	
			puts ("1. Launch the game and observe the game board filled with various colored balls.");
			puts ("2. Navigate your aiming cursor using the arrow keys to position it over the desired target.");
			puts ("3. Press the spacebar to shoot a ball towards the selected location.");
			puts ("4. The numbers on the ball represents the amount of shots needed for it to be destroyed");
			puts ("5. A new wave of balls will emerge after some time\n");
			
		}
		
		c = getch();
		
		if (c == 'd'){
			if (page == 3) continue;
			else page++;
		}
		
		else if (c == 'a'){
			if (page == 1) continue;
			else page--;
		}
		
	}
	
	while (c != 13);
	
}

void bubbleSort(char username[][101], int score[], int n) {
	
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
        	
            if (score[j] < score[j + 1]) {
                
                int tempScore = score[j];
                score[j] = score[j + 1];
                score[j + 1] = tempScore;
                
                char tempUsername[101];
                strcpy(tempUsername, username[j]);
                strcpy(username[j], username[j + 1]);
                strcpy(username[j + 1], tempUsername);
            }
        }
    }
    
}

void printLeaderBoard(){
	
	// Just a Bonus show top 10 highest score save in the "data.txt" file
	
	system ("cls");
	
	FILE *input = fopen ("data.txt", "r");
	
	char username[101][101];
	int score[101];
	
	int index = 0;
	
	while (!feof(input)){
		fscanf (input, "%[^#]#%d\n", username[index], &score[index]);
		index++;
	}
	
	bubbleSort (username, score, index);
	
	for (int a = 0; a < 38; a++){
		printf ("=");
	}
	
	puts("");
	
	printf ("| %-3s | %-15s | %-10s |\n", "No.", "Username", "Score");
	
	for (int a = 0; a < 38; a++){
		printf ("=");
	}
	
	puts("");
	
	for (int i = 0; i < 10; i++){
		printf ("| %-3d | %-15s | %-10d |\n", i+1, username[i], score[i]);
	}
	
	for (int a = 0; a < 38; a++){
		printf ("=");
	}
	
	puts("");
	
	printf ("\nPress enter to continue...");
	
	getchar();
	
	fclose (input);
	
	return;

}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printExit (){
	
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
	
	randomClr();
	
	puts (" ____  _     ____  ____  _     _____   _____ _  ____  ____  ____  ____  ____");
	puts ("/  __\\/ \\ /\\/  _ \\/  _ \\/ \\   /  __/  /    // \\/_   \\/_   \\/  __\\/  _ \\/  __\\");
	puts ("| | //| | ||| | //| | //| |   |  \\    |  __\\| | /   / /   /|  \\/|| / \\||  \\/|");
	puts ("| |_\\\\| \\_/|| |_\\\\| |_\\\\| |_/\\|  /_   | |   | |/   /_/   /_|  __/| \\_/||  __/");
	puts ("\\____/\\____/\\____/\\____/\\____/\\____\\  \\_/   \\_/\\____/\\____/\\_/   \\____/\\_/");
	
	puts("\n");
	
	reset();
	
}


