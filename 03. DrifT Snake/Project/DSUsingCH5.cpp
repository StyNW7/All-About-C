#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>

// Map

const int HEIGHT = 16;
const int WIDTH = 31;


char town[HEIGHT][WIDTH] = {
    "##############################",
    "#             ###            #",
    "#    #######  ###  #######   #",
    "#    #                #      #",
    "#    #   #########    #      #",
    "#    #   #       #    #      #",
    "#    #   #       #    #      #",
    "                              ", // Left: 7, 0 ... Right: 7, 29
    "#    #   #       #    #      #",
    "#    #   #       #    #      #",
    "#    #   #########    #      #",
    "#    #                #      #",
    "#    #######  ###  #######   #",
    "#             ###            #",
    "##############################"
};


char plaza[HEIGHT][WIDTH] = {
    "##############################",
    "#      #     ###     #       #",
    "#      #     ###     #       #",
    "#      #             #       #",
    "#      #     #####   #       #",
    "#      #         #   #       #",
    "#      #         #   #       #",
    "                              ",
    "#      #         #   #       #",
    "#      #         #   #       #",
    "#      #     #####   #       #",
    "#      #             #       #",
    "#      #     ###     #       #",
    "#      #     ###     #       #",
    "##############################"
};


char garden[HEIGHT][WIDTH] = {
    "##############################",
    "#            ####            #",
    "#  #     #          #     #  #",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "                              ",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "#  #     #          #     #  #",
    "#            ####            #",
    "##############################"
};


// Circular Double Linked List


struct gameMap {
	
	char currentMap[HEIGHT][WIDTH];
	
	struct gameMap *next, *prev;
	
	int mapCategory;
	
} *mapHead = NULL, *mapTail = NULL;


struct gameMap* createMapNode (char mapData[HEIGHT][WIDTH], int category) {
	
    struct gameMap* newNode = (struct gameMap*) malloc (sizeof(struct gameMap));
	
	// Because of 2D array
    memcpy(newNode->currentMap, mapData, sizeof(char) * HEIGHT * WIDTH);
    
    newNode->mapCategory = category;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    return newNode;
    
}


// Queue using Double Linked List for the snake


struct SnakeNode {
	
    int x, y;
    struct SnakeNode *prev, *next;
    
};


struct Snake {
	
    struct SnakeNode *head;
    struct SnakeNode *tail;
    
    int horizontalSpeed;
    int verticalSpeed;
    
};


struct SnakeNode* createSnakeNode (int x, int y) {
	
    struct SnakeNode* newNode = (struct SnakeNode*)malloc(sizeof(struct SnakeNode));

    newNode->x = x;
    newNode->y = y;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    return newNode;
    
}


struct Snake* createSnake (int headX, int headY) {
	
    struct Snake* newSnake = (struct Snake*)malloc(sizeof(struct Snake));
    
    if (newSnake != NULL) {
        newSnake->head = createSnakeNode(headX, headY);
    }
    
    return newSnake;
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

void playGame();
void printMap();
void gotoxy(int x, int y);

void insertAllMap ();
void initializeSnake (struct Snake *snake, int startX, int startY);
void insertMapNode(char mapData[HEIGHT][WIDTH], int category);
void updateMap(struct Snake* snake);
void moveSnake(struct Snake* snake);
void inputChecker(struct Snake* snake);
void clearTail(struct Snake* snake);

void resetAll(struct Snake* snake);
void clearSnake(struct Snake* snake);
void deleteAllMaps();

// Global Variable

int score = 1;

bool gameOver = false;
bool foodExist = false;
int foodPosX = 0;
int foodPosY = 0;


int main(){
	
	srand(time(0));
	
	int action;
	
	do {
		
		system ("cls");
		
		printLogo();
		
		puts ("\n1. Play");
		puts ("2. Exit\n");
		
		printf (">> ");
		scanf ("%d", &action); getchar();
		
		if (action == 1) {
			playGame();
		}
		
		else if (action == 2){
			printExit();
		}
		
		else {
			printf ("\n\n[!] Input between 1- 2!");
			getchar();
		}
		
	}
	
	while (action != 2);
	
	return 0;
	
}


void printMap() {
	
	system ("cls");
	
	printf ("Score: %d\n\n", score);
    
    struct gameMap* curr = mapHead;
    
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s\n", curr->currentMap[i]);
    }
    
    printf("\n");
    printf ("Input: ");
	
}


void clearSnake(struct Snake* snake) {
	
    struct SnakeNode* current = snake->head;
    
    while (current != NULL) {
        struct SnakeNode* temp = current;
        current = current->next;
        free(temp);
    }
    
    snake->head = snake->tail = NULL;
    
}


void deleteAllMaps() {
	
    struct gameMap* current = mapHead;
    
    while (current != NULL) {
        struct gameMap* temp = current;
        current = current->next;
        free(temp);
        temp = NULL;
    }
    
    mapHead = mapTail = NULL;
    
}


void resetAll(struct Snake* snake) {
	
	clearSnake(snake);
	deleteAllMaps();
	
	foodExist = false;
	gameOver = false;
	
}


void playGame() {
	
	// Testing map fixing after game over
	
//	if (mapHead != NULL){
//		struct gameMap* curr = mapHead;
//	
//		// Reset map when play again to the town
//	    
//	    if (curr->mapCategory == 2){
//	    	// Back to the town
//	    	mapHead = mapHead->prev;
//		}
//		
//		else if (curr->mapCategory == 3){
//			// Next to the town
//	    	mapHead = mapHead->next;
//		}
//	}
	
	score = 1;
	gameOver = false;
	foodExist = false;
	
	// Insert all map to the CDLL, Initialize Snake and insert to the map
	
	struct Snake snake;
	
	if (mapHead == NULL) insertAllMap ();
	
    initializeSnake (&snake, WIDTH / 2 - 1, HEIGHT / 2 - 1);
    updateMap(&snake);
	
	do {
		
		system ("cls");
		printMap();
		inputChecker(&snake);
		if (gameOver) break;
		updateMap(&snake);
		
//		printf ("\n\n\n%d, %d\n", snake.head->x, snake.head->y);
//		getchar();
		
	}
	
	while (!gameOver);
	
	// Actually doesn't need to clear the snake, because it becomes new every play the game
	
//	resetAll (&snake);
	
//	clearSnake (&snake);

	// We can delete the maps but because this is circular, so if the map getting push again, the program runs the same,
	// But actually, there is 6 maps etc in the struct
	
//	deleteAllMaps();
	
	system ("cls");
	
	printf ("Game Over!\n\n");
	printf ("Score: %d\n\n", score);
	printf ("Press [ENTER] to continue...");
	
	getchar();
	
}


void inputChecker(struct Snake* snake){
	
	char key = getch();
	
    switch (key) {
        case 'w':
            if (snake->verticalSpeed != 1) {
                snake->horizontalSpeed = 0;
                snake->verticalSpeed = -1;
                moveSnake(snake);
            }
            break;
            
        case 'a':
            if (snake->horizontalSpeed != 1) {
                snake->horizontalSpeed = -1;
                snake->verticalSpeed = 0;
                moveSnake(snake);
            }
            break;
            
        case 's':
            if (snake->verticalSpeed != -1) {
                snake->horizontalSpeed = 0;
                snake->verticalSpeed = 1;
                moveSnake(snake);
            }
            break;
            
        case 'd':
            if (snake->horizontalSpeed != -1) {
                snake->horizontalSpeed = 1;
                snake->verticalSpeed = 0;
                moveSnake(snake);
            }
            break;
            
        default:
            break;
            
    }
	
}


void moveSnake(struct Snake* snake) {
    
    struct SnakeNode* newHead = createSnakeNode(snake->head->x + snake->horizontalSpeed, snake->head->y + snake->verticalSpeed);
    
    newHead->next = snake->head;
    snake->head->prev = newHead;
    snake->head = newHead;
    
    // Snake eats food
    
	struct gameMap *curr = mapHead;

    if (curr->currentMap[snake->head->y][snake->head->x] == '*') {
        score++;
        foodExist = false;
    }
    
    else {
    	
        if (snake->tail != NULL) {
        	
	        struct SnakeNode* tail = snake->tail;
	        snake->tail = tail->prev;
	        
	        if (snake->tail != NULL) {
	            snake->tail->next = NULL;
	        }
	        
	        free(tail);
	        
	    }
	    
    }

	// Snake dies because it crash the boundaries

    if (curr->currentMap[snake->head->y][snake->head->x] == '#') {
        gameOver = true;
    }
    
    // Snake dies because it crash it own body
    
    if (curr->currentMap[snake->head->y][snake->head->x] == '.'){
    	gameOver = true;
	}
    
    // Change map
    
    if (snake->head->y == 7 && snake->head->x == 29){
    	mapHead = mapHead->next;
    	foodExist = 0;
    	clearTail(snake);
    	snake->head->y = 7;
    	snake->head->x = 0;
	}
	
	else if (snake->head->y == 7 && snake->head->x == 0){
		mapHead = mapHead->prev;
		foodExist = 0;
		clearTail(snake);
		snake->head->y = 7;
    	snake->head->x = 29;
	}
    
}


void clearTail(struct Snake* snake) {
	
	struct SnakeNode* curr = snake->head;
	
	while (curr != NULL){
		curr->x = -1;
		curr->y = -1;
		curr = curr->next;
	}
	
}


void updateMap(struct Snake* snake) {

    struct SnakeNode* currentNode = snake->head;
    
    struct gameMap *currMap = mapHead;
    
    // Map Reset
    
    if (currMap->mapCategory == 1){
    	for (int i = 0; i < HEIGHT; i++) {
	        for (int j = 0; j < WIDTH; j++) {
	            currMap->currentMap[i][j] = town[i][j];
	        }
	    }
	}
	
	else if (currMap->mapCategory == 2){
    	for (int i = 0; i < HEIGHT; i++) {
	        for (int j = 0; j < WIDTH; j++) {
	            currMap->currentMap[i][j] = plaza[i][j];
	        }
	    }
	}
	
	else if (currMap->mapCategory == 3){
    	for (int i = 0; i < HEIGHT; i++) {
	        for (int j = 0; j < WIDTH; j++) {
	            currMap->currentMap[i][j] = garden[i][j];
	        }
	    }
	}
	
	// Random food
	
	if (foodExist == 0){
		foodExist = true;
		while (true){
			int randX = rand() % 15 + 1;
			int randY = rand() % 30 + 1;
			if (currMap->currentMap[randX][randY] == ' '){
				currMap->currentMap[randX][randY] = '*';
				foodPosX = randX;
				foodPosY = randY;
				break;
			}
		}
	}
	
	// Update food after map deleted
	
	currMap->currentMap[foodPosX][foodPosY] = '*';
    
    // Update snake position
    
    currMap = mapHead;
    
    currMap->currentMap[currentNode->y][currentNode->x] = 'o';
    
    currentNode = currentNode->next;
    
    while (currentNode != NULL) {
    	// Body of the snake
        currMap->currentMap[currentNode->y][currentNode->x] = '.';
        currentNode = currentNode->next;
    }
    
}


// Start the game


void initializeSnake (struct Snake *snake, int startX, int startY) {
    
    snake->head = createSnakeNode(startX, startY);
    
    snake->tail = createSnakeNode(startX - 1, startY);
    
    snake->head->next = snake->tail;
    snake->tail->prev = snake->head;
    snake->horizontalSpeed = 1;
    snake->verticalSpeed = 0;
    
}


void insertAllMap () {

    insertMapNode(town, 1);
    insertMapNode(plaza, 2);
    insertMapNode(garden, 3);
	
}


void insertMapNode(char mapData[HEIGHT][WIDTH], int category) {
	
    struct gameMap* newNode = createMapNode(mapData, category);
    
    if (mapHead == NULL) {
        mapHead = mapTail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } 
	
	// Push Tail
	
	else {
        mapTail->next = newNode;
        newNode->prev = mapTail;
        newNode->next = mapHead;
        mapHead->prev = newNode;
        mapTail = newNode;
    }
    
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

	puts (" ____       _  __ _____   ____              _");
	puts ("|  _ \\ _ __(_)/ _|_   _| / ___| _ __   __ _| | _____");
	puts ("| | | | '__| | |_  | |   \\___ \\| '_ \ / _` | |/ / _ \\");
	puts ("| |_| | |  | |  _| | |    ___) | | | | (_| |   <  __/");
	puts ("|____/|_|  |_|_|   |_|   |____/|_| |_|\\__,_|_|\\_\\___|");
	puts ("");
	
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

