#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

// Candle Stick using Double Linked List in C

struct CandleStick {
	
	int closePrice;
	int openPrice;
	int highestPrice;
	int lowestPrice;
	
	bool profit;
	
	CandleStick *next, *prev;
	
	
} *candleHead = NULL, *candleTail = NULL;


struct CandleStick* createCandleStick (int closePrice, int openPrice, int highestPrice, int lowestPrice, bool profit){
	
	
	struct CandleStick* newCandle = (CandleStick*) malloc (sizeof (struct CandleStick));
	
	newCandle->closePrice = closePrice;
	newCandle->openPrice = openPrice;
	newCandle->highestPrice = highestPrice;
	newCandle->lowestPrice = lowestPrice;
	
	newCandle->profit = profit;
	
	newCandle->next = NULL;
	newCandle->prev = NULL;
	
	return newCandle;
	
}


// Priority Queue Double Linked List in C


struct History {
	
	long long int value;
	int position;
	int profit;
	int loss;
	long long int reward;
	
	History *next, *prev;
	
} *historyHead = NULL, *historyTail = NULL, *historyCurr = NULL;


struct History *createNewHistory (long long int value, int position, int profit, int loss, long long int reward) {
	
	struct History* temp = (struct History*) malloc (sizeof(struct History));
	
	temp->value = value;
	temp->position = position;
	temp->profit = profit;
	temp->loss = loss;
    temp->reward = reward;
    
    temp->next = NULL;
    temp->prev = NULL;
  
    return temp;
    
}

// Hash Table Chaining in C

// Because of modulo 26, so the max account is also 26

const int MAX_ACC = 26;

struct Account {
	
	long long int currency;
	char username[101];
	char password[101];
	char email[101];
	
	History *accHistoryHead, *accHistoryTail;
	
	Account *next, *prev;
	
} *accHead[MAX_ACC] = {NULL}, *accTail[MAX_ACC] = {NULL}, *accCurr = NULL;


struct Account* createNewAcc (char username[], char email[], char password[], long long int currency){
	
	Account *newNode = (Account*) malloc(sizeof(Account));
	
	strcpy (newNode->username, username);
	strcpy (newNode->email, email);
	strcpy (newNode->password, password);
	
	newNode->currency = currency;
	
	newNode->accHistoryHead = NULL;
	newNode->accHistoryTail = NULL;
	
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
	
}

// Global Account

Account activeAccount;

// Default Function

void printLogo();
void printExit();

void orange();
void purple();
void grey();
void red();
void green();
void yellow();
void blue();
void magenta();
void cyan();
void white();
void reset();
void randomClr();

void stayScreen();
void fullScreen();
void gotoxy (int x, int y);

// Trading Function

void registerAcc ();
void login();
void menuPage ();

void printTrading();
void tradingGuide ();
void trading ();
void tradingHistory ();
void accLogout();

// History Function

void pushHistory(Account *account, long long int value, int position, int profit, int loss, long long int reward);
void popHistory (History *node);
void popAllHistory();

// Hash Table Function

int searchUser (char name[]);
int hash (char name[]);
Account *getHash(char name[]);

// Candle Stick and Trading Function

void printCandle();
void printCandleValue();
void startTrading();
void pushCandle(int close, int open, int highest, int lowest, bool profit);
void createCandleValue();
void newDay ();
void previousDay ();
void nextDay ();
void longTrade ();
void shortTrade ();
void tradingMechanism ();

// Global Variable

bool tradeOpened = false;
bool tradeActive = false;
bool tradeCategory;

int positionLine, takeProfitLine, sellLossLine;
long long int tradingValue;


int main(){
	
	srand(time(0));
	
	fullScreen();
	
	int action;
	
	do {
		
		system ("cls");
		
		printLogo();
		
		puts ("\n1. Log in to Trade");
		puts ("2. Register Account");
		puts ("3. Exit Application");
		
		printf (">> ");
		scanf ("%d", &action); getchar();
		
		if (action == 1) {
			login();
		}
		
		else if (action == 2){
			registerAcc();
		}
		
		else if (action == 3){
			printExit();
		}
		
	}
	
	while (action != 3);
	
	return 0;
	
}

void printTrading(){
	
	system ("cls");
	
	for (int i = 0; i < 100; i++) printf ("#");
	puts ("");
	
	int position = 330;
	
	for (int i = position; i >= 10; i -= 10){
		
		printf ("#");
		
		grey();
		
		if (tradeOpened){
			if (i == positionLine) white();
			else if (i == takeProfitLine) green();
			else if (i == sellLossLine) red();
		}
		
		for (int j = 0; j < 92; j++){
			printf ("-");
		}
		
		reset();
		
		printf ("# %-3d #\n", i);
		
	}
	
	for (int i = 0; i < 100; i++) printf ("#");
	puts ("");
	
	for (int i = 0; i < 3; i++){
		
		printf ("# ");
		
		if (i == 0){
			randomClr();
		
			printf ("Welcome to METAFI, ");
			
			reset();
			
			printf ("%-20s #\n", activeAccount.username);
		}
		
		else if (i == 1){
			printf ("1. New Day    3. Next   5. Short        #\n");
		}
		
		else if (i == 2){
			printf ("2. Previous   4. Long   6. Logout");
			purple();
			printf ("  >>   ");
			reset();
			printf ("#\n");
		}
		
		reset();
		
	}
	
	for (int i = 0; i < 100; i++) printf ("#");
	puts ("");
	
	gotoxy (48, 35);
	printf ("Value   :       ");
	printf ("TP :         #");
	
	gotoxy (48, 36);
	printf ("Position:       ");
	printf ("SL :         #");
	
	gotoxy (77, 37);
	printf ("#");
	
	gotoxy (99, 35);
	printf ("#");
	
	gotoxy (82, 36);
	printf (" $ %lld         #", activeAccount.currency);
	
	gotoxy (99, 37);
	printf ("#");
	
}


void createCandleValue() {
	
	// Random 20 first candle
	
	int openPrice = 0, closePrice = 0, highestPrice = 0, lowestPrice = 0;
	bool profit = false;
	
	// No explanation about the boundaries, but the position maximum is from 10 - 330
	
	openPrice = (rand() % 33 + 1) * 10;
	
	for (int i = 0; i < 20; i++){
		
		closePrice = openPrice;
		
		int closeEqual = rand() % 10 + 1;
		
		if (closeEqual == 1){
			closePrice = openPrice;
		}
		
		else {
			
			int higher = rand() % 2 + 1;
			int diff = (rand() % 6 + 1) * 10;
			
			if (higher == 1){
				// Prevent boundaries
				closePrice += diff;
                if (closePrice > 330) closePrice = 330;
			}
			
			else {
				// Prevent negative
				closePrice -= diff;
                if (closePrice < 10) closePrice = 10;
			}
			
		}
		
		if (closePrice > openPrice){
			int random = rand() % 10 + 1;
            highestPrice = closePrice;
            lowestPrice = openPrice;

            if (random > 3) {
                int add = (rand() % 4 + 1) * 10;
                highestPrice += add;
                if (highestPrice > 330) highestPrice = 330;

                lowestPrice -= add;
                if (lowestPrice < 10) lowestPrice = 10;
            }
		}
		
		else if (closePrice < openPrice){
			int random = rand() % 10 + 1;
            highestPrice = openPrice;
            lowestPrice = closePrice;

            if (random > 3) {
                int add = (rand() % 4 + 1) * 10;
                highestPrice += add;
                if (highestPrice > 330) highestPrice = 330;

                lowestPrice -= add;
                if (lowestPrice < 10) lowestPrice = 10;
            }
		}
		
		else {
			
			// If closePrice == openPrice there is no explanation in the guidebook
			
			// Just my assumption based on the .exe example
			
//			if (closePrice < openPrice) highestPrice = openPrice;
//			else highestPrice = closePrice;
			
			highestPrice = openPrice;
            lowestPrice = openPrice;
			
		}
		
		if (closePrice < openPrice) profit = false;
		else profit = true; // Equal or higher
		
		// push
		
		pushCandle (closePrice, openPrice, highestPrice, lowestPrice, profit);
		
		openPrice = closePrice;
		
	}
	
}

// Only print value

void printCandleValue() {
	
	gotoxy (100, 100);
	
//	printf ("HELLO WORLD");
	
	CandleStick *curr = candleHead;
	
	while (curr){
		
		printf ("Close Price: %d\n", curr->closePrice);
		printf ("Open Price: %d\n", curr->openPrice);
		printf ("Highest Price: %d\n", curr->highestPrice);
		printf ("Lowest Price: %d\n\n", curr->lowestPrice);
		printf ("Profit: %d\n\n", curr->profit);
		
		curr = curr->next;
		
	}
	
}


void printCandle (){
	
	CandleStick *curr = candleHead;
	
	int counter = 1;
	
	while (curr){
		
		if (curr->profit == true) {
			
			green();
			
			if (curr->highestPrice > curr->closePrice) {
				for (int i = curr->highestPrice; i > curr->closePrice; i -= 10){
					gotoxy (counter, i/10);
					printf ("%c", 179);
				}
			}
			
			if (curr->lowestPrice < curr->openPrice) {
				for (int i = curr->openPrice; i > curr->lowestPrice; i -= 10){
					gotoxy (counter, i/10);
					printf ("%c", 179);
				}
			}
			
			// Prevent no candle stick's body
			
			for (int i = curr->closePrice; i >= curr->openPrice; i -= 10){
				gotoxy (counter, i/10);
				printf ("%c", 219);
			}

		}

		else {
			
			red();
			
			if (curr->highestPrice > curr->openPrice) {
				for (int i = curr->highestPrice; i > curr->openPrice; i -= 10){
					gotoxy (counter, i/10);
					printf ("%c", 179);
				}
			}
			
			for (int i = curr->openPrice; i > curr->closePrice; i -= 10){
				gotoxy (counter, i/10);
				printf ("%c", 219);
			}
			
			if (curr->lowestPrice < curr->closePrice) {
				for (int i = curr->closePrice; i > curr->lowestPrice; i -= 10){
					gotoxy (counter, i/10);
					printf ("%c", 179);
				}
			}
			
		}
		
		reset();
		
		counter++;
		
		// Prevent Boundaries version 2: but the user cannot see the new day...
		
//		if (counter >= 93) {
//			break;
//		}
		
		curr = curr->next;
		
	}
	
	// Prevent Boundaries version 1, but user cannot use previous function
	
	if (counter >= 94) {
		for (int i = counter; i >= 94; i--){
			nextDay();
		}
	}
	
	gotoxy (41, 37);
	
	if (tradeOpened) tradingMechanism();
	
}


void trading(){
	
	if (activeAccount.currency <= 0){
		
		printf ("\n\n\nYour currency is %lld\n", activeAccount.currency);
		printf ("You cannot trading again!\n\n");
		printf ("Press enter to continue..."); getchar();
		
		return;
		
	}
	
	int action;
	char ch;
	
	int len = 0;
	
	gotoxy(41, 37);
	
	do {
		
		ch = getch();
		
		if (ch >= '0' && ch <= '9') {
			
			if (len == 1){
				printf ("\b \b");
				action = ch - '0';
            	printf("%d", action);
			}
			else {
				len++;
	            action = ch - '0';
	            printf("%d", action);
			}
			
        }
        
        else if (ch == 8){
        	if (len != 0){
        		printf ("\b \b");
        		len--;
			}
		}
        
        else if (ch == 13){
        	
        	if (action == 6) break;
        	
        	else if (action == 1) newDay ();
        	else if (action == 2) previousDay ();
        	else if (action == 3) nextDay ();
        	else if (action == 4) longTrade ();
        	else if (action == 5) shortTrade ();
        	
		}
		
	}
	
	while (true);
	
}


void startTrading() {
	
//	stayScreen();
	system ("cls");
	
	printTrading();
	printCandle();
//	printCandleValue();

	gotoxy (41, 37);
	
}


void newDay(){
	
	int openPrice = 0, closePrice = 0, highestPrice = 0, lowestPrice = 0;
	bool profit = false;
	
	// Get the last candlestick
	
	openPrice = candleTail->closePrice;
		
	closePrice = openPrice;
	
	int closeEqual = rand() % 10 + 1;
		
	if (closeEqual == 1){
		closePrice = openPrice;
	}
	
	else {
		
		int higher = rand() % 2 + 1;
		int diff = (rand() % 6 + 1) * 10;
		
		if (higher == 1){
			// Prevent boundaries
			closePrice += diff;
            if (closePrice > 330) closePrice = 330;
		}
		
		else {
			// Prevent negative
			closePrice -= diff;
            if (closePrice < 10) closePrice = 10;
		}
		
	}
	
	if (closePrice > openPrice){
		int random = rand() % 10 + 1;
        highestPrice = closePrice;
        lowestPrice = openPrice;

        if (random > 3) {
            int add = (rand() % 4 + 1) * 10;
            highestPrice += add;
            if (highestPrice > 330) highestPrice = 330;

            lowestPrice -= add;
            if (lowestPrice < 10) lowestPrice = 10;
        }
	}
	
	else if (closePrice < openPrice){
		int random = rand() % 10 + 1;
        highestPrice = openPrice;
        lowestPrice = closePrice;

        if (random > 3) {
            int add = (rand() % 4 + 1) * 10;
            highestPrice += add;
            if (highestPrice > 330) highestPrice = 330;

            lowestPrice -= add;
            if (lowestPrice < 10) lowestPrice = 10;
        }
	}
	
	else {
		
//		if (closePrice < openPrice) highestPrice = openPrice;
//		else highestPrice = closePrice;

		highestPrice = openPrice;
        lowestPrice = openPrice;
		
	}
	
	if (closePrice < openPrice) profit = false;
	else profit = true;
	
	// Push Tail
	
	pushCandle (closePrice, openPrice, highestPrice, lowestPrice, profit);
	
	startTrading();
	
}


void previousDay (){
	
	if (candleHead->prev != NULL) candleHead = candleHead->prev;
	
	startTrading();
	
}


void nextDay (){
	
	if (candleHead->next != NULL) candleHead = candleHead->next;
	
	startTrading();
	
}


void longTrade (){
	
	long long int value;
	int position, takeProfit, sellLoss;
	
	bool inputValid = false;
	
	if (!tradeOpened){
		
		// Value
		
		do {
			
			gotoxy (58, 35);
			
			scanf ("%lld", &value);
			
			if (value >= 10 && value <= activeAccount.currency){
				break;
			}
			
			else {
				gotoxy (42, 37);
				printf ("Value = (10 - %lld)", activeAccount.currency);
			}
			
		}
		
		while (true);
		
		// Position
		
		do {
			
			gotoxy (58, 36);
			
			scanf ("%d", &position);
			
			if (position >= 20 && position <= 320 && position % 10 == 0){
				break;
			}
			
			else {
				gotoxy (42, 37);
				printf ("Position (20 - 320) % 10");
			}
			
		}
		
		while (true);
		
		// Take Profit
		
		do {
			
			gotoxy (70, 35);
			
			scanf ("%d", &takeProfit);
			
			if (takeProfit >= 10 && takeProfit <= 330 && takeProfit % 10 == 0 && takeProfit > position){
				break;
			}
			
			else {
				gotoxy (44, 37);
				printf ("Profit > position");
			}
			
		}
		
		while (true);
		
		// Sell Loss
		
		do {
			
			gotoxy (70, 36);
			
			scanf ("%d", &sellLoss);
			
			if (sellLoss >= 10 && sellLoss <= 330 && sellLoss % 10 == 0 && sellLoss < position){
				break;
			}
			
			else {
				gotoxy (44, 37);
				printf ("Sell Loss < position");
			}
			
		}
		
		while (true);
		
		inputValid = true;

	}
	
	else {
		
		gotoxy (42, 37);
		
		printf ("A Position Already Open!");
		getchar();
		
		startTrading();
		
		return;
		
	}
	
	if (inputValid){
		
		tradeOpened = true;
		
//		positionLine = (340-position)/10;
//		takeProfitLine = (340-takeProfit)/10;
//		sellLossLine = (340-sellLoss)/10;
	
		tradingValue = value;
		positionLine = position;
		takeProfitLine = takeProfit;
		sellLossLine = sellLoss;
		tradeCategory = true;
		
		startTrading();
		
	}
	
}


void shortTrade (){
	
	long long int value;
	int position, takeProfit, sellLoss;
	
	bool inputValid = false;
	
	if (!tradeOpened){
		
		// Value
		
		do {
			
			gotoxy (58, 35);
			
			scanf ("%lld", &value);
			
			if (value >= 10 && value <= activeAccount.currency){
				break;
			}
			
			else {
				gotoxy (42, 37);
				printf ("Value = (10 - %lld)", activeAccount.currency);
			}
			
		}
		
		while (true);
		
		// Position
		
		do {
			
			gotoxy (58, 36);
			
			scanf ("%d", &position);
			
			if (position >= 20 && position <= 320 && position % 10 == 0){
				break;
			}
			
			else {
				gotoxy (42, 37);
				printf ("Position (20 - 320) % 10");
			}
			
		}
		
		while (true);
		
		// Take Profit
		
		do {
			
			gotoxy (70, 35);
			
			scanf ("%d", &takeProfit);
			
			if (takeProfit >= 10 && takeProfit <= 330 && takeProfit % 10 == 0 && takeProfit < position){
				break;
			}
			
			else {
				gotoxy (44, 37);
				printf ("Profit < Position");
			}
			
		}
		
		while (true);
		
		// Sell Loss
		
		do {
			
			gotoxy (70, 36);
			
			scanf ("%d", &sellLoss);
			
			if (sellLoss >= 10 && sellLoss <= 330 && sellLoss % 10 == 0 && sellLoss > position){
				break;
			}
			
			else {
				gotoxy (44, 37);
				printf ("Sell Loss > Position");
			}
			
		}
		
		while (true);
		
		inputValid = true;

	}
	
	else {
		
		gotoxy (42, 37);
		
		printf ("A Position Already Open!");
		getchar();
		
		startTrading();
		
		return;
		
	}
	
	if (inputValid){
		
		tradeOpened = true;
		
//		positionLine = (340-position)/10;
//		takeProfitLine = (340-takeProfit)/10;
//		sellLossLine = (340-sellLoss)/10;
	
		tradingValue = value;
		positionLine = position;
		takeProfitLine = takeProfit;
		sellLossLine = sellLoss;
		tradeCategory = false;
		
		startTrading();
		
	}
	
}


void tradingMechanism () {
	
	CandleStick* curr = candleTail;
	
	// Trade is active?
	
//	if (curr->closePrice == positionLine){
//		tradeActive = true;
//	}
	
	if (!tradeActive){
		if (curr->profit == true){
			for (int i = curr->closePrice; i >= curr->openPrice; i -= 10){
				if (i == positionLine) {
					tradeActive = true;
					break;
				}
			}
		}
		
		else {
			for (int i = curr->openPrice; i >= curr->closePrice; i -= 10){
				if (i == positionLine) {
					tradeActive = true;
					break;
				}
			}
		}
	}
	
	if (tradeActive){
		// My analysis in the .exe example, because guidebook doesn't provide detail explanation about this
		if (curr->profit == true) {
			if (tradeCategory == true){
				int add = abs (curr->prev->closePrice - curr->closePrice);
				activeAccount.currency += add;
			}
			else {
				int minus = abs (curr->prev->closePrice - curr->closePrice);
				activeAccount.currency -= minus;
			}
			
		}
		else {
			if (tradeCategory == false){
				int add = abs (curr->prev->closePrice - curr->closePrice);
				activeAccount.currency += add;
			}
			else {
				int minus = abs (curr->prev->closePrice - curr->closePrice);
				activeAccount.currency -= minus;
			}
		}
	}
	
	// Candle stick crossed the take profit price or stop loss price ?
	
	if (tradeActive){
		
		if (curr->highestPrice >= takeProfitLine || curr->highestPrice >= sellLossLine || curr->lowestPrice <= takeProfitLine || curr->lowestPrice <= sellLossLine){
			
			// Trade stopped
			tradeActive = false;
			tradeOpened = false;
			
			long long int reward = (tradingValue * abs (curr->closePrice - positionLine)) / 100;
	
			bool negative = false;
			
			if (tradeCategory == true){
				if (curr->profit == true) activeAccount.currency += reward;
				else {
					activeAccount.currency -= reward;
					negative = true;
				}
			}
			
			else {
				if (curr->profit == true) {
					activeAccount.currency -= reward;
					negative = true;
				}
				else activeAccount.currency += reward;
			}
			
			if (negative){
				pushHistory (&activeAccount, tradingValue, positionLine, takeProfitLine, sellLossLine, reward*-1);
			}
			
			else {
				pushHistory (&activeAccount, tradingValue, positionLine, takeProfitLine, sellLossLine, reward);
			}
			
			accLogout();
			
		}
		
	}
	
}


void pushCandle(int close, int open, int highest, int lowest, bool profit) {
	
	CandleStick *candle = createCandleStick (close, open, highest, lowest, profit);
	
	if (candleHead == NULL){
		candleHead = candleTail = candle;
		candle->next = candle->prev = NULL;
	}
	
	// pushTail
	
	else {
		candle->prev = candleTail;
		candleTail->next = candle;
		candle->next = NULL;
		candleTail = candle;
	}
	
}


void tradingHistory(){
	
	system ("cls");
	
	// activeAccount.accHistory
	
	if (activeAccount.accHistoryHead == NULL){
		yellow();
		printf ("No Trade History\n");
		white();
		printf ("Press enter to continue...");
		getchar();
		reset();
	}
	
	else {
		
		printf ("Username: %s\n", activeAccount.username);
		
		for (int i = 0; i < 20; i++) printf ("-");
		puts("");

		int num = 1;
		
		History* historyCurr = activeAccount.accHistoryHead;
		
		while (historyCurr != NULL){
			
			printf ("No: %d\n", num);
			printf ("Value: %lld\n", historyCurr->value);
			printf ("Position: %d\n", historyCurr->position);
			printf ("Take Profit: %d\n", historyCurr->profit);
			printf ("Stop Loss: %d\n", historyCurr->loss);
			
			if (historyCurr->reward > 0) green();
			else if (historyCurr->reward < 0) red();
			printf ("Reward: %lld\n", historyCurr->reward);
			reset();
			
			puts ("");
			
			historyCurr = historyCurr->next;
			num++;
			
		}
		
		puts ("");
		printf ("Press enter to continue...");
		getchar();
		
	}
	
	return;
	
}


void menuPage () {
	
	int action;
	
	do {
		
		system ("cls");
		
		printf ("Welcome %s\n\n", activeAccount.username);
		
		printf ("Currency: %lld\n\n", activeAccount.currency);
		
		puts ("MetaFi - User's Menu");
		puts ("---------------------");
		puts ("1. Start Trade");
		puts ("2. Trade History");
		puts ("3. Guide");
		puts ("4. Log Out");
		
		printf (">> ");
		scanf ("%d", &action);
		getchar();
		
		if (action == 1) {
			if (candleHead == NULL) createCandleValue();
			startTrading();
			trading();
		}
		else if (action == 2) tradingHistory();
		else if (action == 3) tradingGuide();
		else if (action == 4) accLogout();
		else {
			printf ("\n\n[!] Input should between 1 - 4!");
			getchar();
		}
		
	}
	
	while (action != 4);
	
}

void pushAcc (char username[], char email[], char password[], long long int currency) {
	
	Account *node = createNewAcc (username, email, password, currency);
	int index = hash(username);
	
	// Push Head
	
	if (accHead[index] == NULL){
		accHead[index] = accTail[index] = node;
	}
	
	// Push Tail
	
	else {
		
		accTail[index]->next = node;
		node->prev = accTail[index];
		accTail[index] = node;
		
		accTail[index]->next = NULL;
		
	}
	
}


void pushHistory(Account *account, long long int value, int position, int profit, int loss, long long int reward) {
	
    History* node = createNewHistory(value, position, profit, loss, reward);

    if (account->accHistoryHead == NULL) {
        account->accHistoryHead = node;
        node->prev = node->next = NULL;
        return;
    }

    History* current = account->accHistoryHead;
    while (current != NULL && current->reward >= reward) {
        current = current->next;
    }

    if (current == account->accHistoryHead) {
        node->next = account->accHistoryHead;
        node->prev = NULL;
        account->accHistoryHead->prev = node;
        account->accHistoryHead = node;
    } 
	
	else if (current == NULL) {
        History* tail = account->accHistoryHead;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
        node->prev = tail;
        node->next = NULL;
    } 
	
	else {
        History* previous = current->prev;
        previous->next = node;
        node->prev = previous;
        node->next = current;
        current->prev = node;
    }
    
}


void login(){
	
	system ("cls");
	
	char email[101];
	
	char username[101];
	long long int currency;
	char compare[101];
	char passCompare[101];
	
	bool check = false, check2 = true;
	
//	FILE *input = fopen ("user.txt", "r");
	
	do {
		
		FILE *input = fopen ("user.txt", "r");
		
		check = false, check2 = true;
		
		system ("cls");
		
		printf ("Email (0 To Exit): ");
		scanf ("%[^\n]", email); getchar();
		
		if (strcmp (email, "0") == 0) return;
		
		if (strlen(email) < 1) check = true;
		
		while (!feof(input)){
			fscanf (input, "%[^#]#%[^#]#%[^#]#%lld\n", username, compare, passCompare, &currency);
			if (strcmp(compare, email) == 0) {
				check2 = false;
				break;
			}
		}
		
		if (check) {
			red();
			printf ("Email Invalid!");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (check2){
			red();
			printf ("Email not registered!");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		fclose (input);

	}
	
	while (check || check2);
	
	char password[101];
	
	bool flag = true;
	
	do {
		
		flag = true;
		
		system ("cls");
		
		printf ("Password (0 To Exit): ");
		
		char *getpass(const char *prompt);
		
		char c;
	    int passIndex = 0;
	    
	    while (true){
	    	
	    	c = getch();
	    	if (c == '\n' || c == '\r' || c == 13) break;
	    	else if ((c == 8 || c == 127)){
	    		if ((passIndex-1) == -1) {
	    			continue;
				}
	    		passIndex--;
	    		printf ("\b \b");
			}
			else {
				password[passIndex] = c;
		        printf("*");
		        passIndex++;
			}
			
	    }
	    
	    password[passIndex] = '\0';
		
		if (strcmp (password, "0") == 0) return;
		
		if (strcmp (password, passCompare) == 0) {
			flag = false;
		}
		
		if (flag){
			red();
			printf ("\nPassword Invalid!");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}

	}
	
	while (flag);
	
//	printf ("Helooooo\n\n\n");
	
	// Valid
	
	int found = searchUser (username);
	
	if (found != -1){
		
		// Data found in the hash table
		
		Account *temp = getHash(username);
        activeAccount = *temp;
		
//		if (activeAccount.accHistoryHead == NULL) {
//            activeAccount.accHistoryHead = activeAccount.accHistoryTail = NULL;
//        }
		
	}
	
	else {
		
		// Data not found in the hash table
		pushAcc (username, email, password, currency);
		Account *temp = getHash (username);
		activeAccount = *temp;
		
//		activeAccount.accHistoryHead = activeAccount.accHistoryTail = NULL;
		
	}
	
//	fclose (input);
	
//	getchar();

	if (candleHead == NULL){
		createCandleValue();
	}
	
	menuPage();
	
	return;
	
}

Account *getHash(char name[]) {
	
    int index = hash(name);
    
    if (accHead[index] == NULL && accTail[index] == NULL) {
        return NULL;
    }
	
	else {

        Account *curr = accHead[index];
        
        while (curr != NULL) {
            if (strcmp(curr->username, name) == 0) {
                return curr;
            }
            curr = curr->next;
        }
        
        return NULL;
        
    }
}

void accLogout() {
	
	// Delete Account
	
//	activeAccount.accHistoryHead = NULL;
//    activeAccount.accHistoryTail = NULL;
//    strcpy(activeAccount.username, "");
//    strcpy(activeAccount.email, "");
//    strcpy(activeAccount.password, "");
//    activeAccount.currency = 0;

	// Rewrite File
	
	FILE *input = fopen ("user.txt", "r");
	FILE *edit = fopen ("temp.txt", "w+");
	
	char username[101][101];
	char email[101][101];
	char password[101][101];
	long long int currency[101];
	
	int index = 0;
	
	while (!feof(input)){
		fscanf (input, "%[^#]#%[^#]#%[^#]#%lld\n", username[index], email[index], password[index], &currency[index]);
		index++;
	}
	
	for (int i = 0; i < index; i++){
		
		if (strcmp (activeAccount.username, username[i]) == 0) fprintf (edit, "%s#%s#%s#%lld\n", username[i], email[i], password[i], activeAccount.currency);
		else fprintf (edit, "%s#%s#%s#%lld\n", username[i], email[i], password[i], currency[i]);
		
	}
	
    fclose(input);
    fclose(edit);

    remove("user.txt");

    rename("temp.txt", "user.txt");
	
}


// FINISH CODE


int hash (char name[]) {
	
	int key = 0;
	
	for (int i = 0; i < strlen(name); i++){
		key += (name[i] + '0');
	}
	
	return (key % MAX_ACC);
	
}


int searchUser (char name[]){
	
	int index = hash(name);
	
	if (accHead[index] == NULL && accTail[index] == NULL){
		return -1;
	}
	
	else {
		Account *curr = accHead[index];
        while (curr != NULL) {
            if (strcmp(curr->username, name) == 0) {
                return 0;
            }
            curr = curr->next;
        }
        return -1;
	}
	
	return -1;
	
}

void registerAcc () {
	
	system ("cls");
	
	char username[101];
	
	bool check = true, check2 = false, check3 = true, check4 = false;
	
	do {
		
		check = true, check2 = false, check3 = true, check4 = false;
		
		system ("cls");
		
		printf ("Username (0 To Exit): ");
		scanf ("%[^\n]", username); getchar();
		
		if (strcmp (username, "0") == 0) return;
		
		if (strlen(username) >= 1 && strlen(username) <= 20) check = false;
		
		for (int i = 0; i < strlen(username); i++){
			if (username[i] < '0' || (username[i] > '9' && username[i] <= '@') || (username[i] > 'Z' && username[i] <= 96) || username[i] > 'z') {
				check2 = true;
				break;
			}
		}
		
		FILE *input = fopen ("user.txt", "r");
		
		while (!feof(input)){
			char temp[101];
			char buffer[101];
			fscanf (input, "%[^#]#%[^\n]\n", temp, buffer);
			if (strcmp(temp, username) == 0) check4 = true;
		}
		
		if (check) {
			red();
			printf ("Username Characters between 1 - 20!");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (check2){
			red();
			printf ("Username Invalid!");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (check4){
			red();
			printf ("Username Taken!");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}

	}
	
	while (check || check2 || check4);
	
	char email[101];
	bool flag = true, flag2 = true, flag3 = true, flag4 = true, flag5 = true, flag6 = false, flag7 = false, flag8 = false, flag9 = true;
	
	do {
		
		flag = true, flag2 = true, flag3 = true, flag4 = true, flag5 = true, flag6 = false, flag7 = false, flag8 = false, flag9 = true;
		
		int count = 0;
		
		system ("cls");
		
		printf ("Email (0 To Exit): ");
		scanf ("%[^\n]", email); getchar();
		
		if (strcmp (email, "0") == 0) return;
		
		int index = -1;
		
		for (int i = 0; i < strlen(email); i++){
			if (email[i] == '@') {
				count++;
				index = i;
			}
			if (email[i] == '#') flag6 = true;
			if (email[i] == ' ') flag8 = true;
		}
		
		if (count == 1) flag = false;
		
		if (email[index+1] != '.') flag9 = false;
		
		if (email[strlen(email)-4] == '.') flag2 = false;
		if (email[strlen(email)-3] == 'c') flag3 = false;
		if (email[strlen(email)-2] == 'o') flag4 = false;
		if (email[strlen(email)-1] == 'm') flag5 = false;
		
		FILE *input = fopen ("user.txt", "r");
		
		while (!feof(input)){
			char temp[101];
			char buffer[101];
			char compare[101];
			fscanf (input, "%[^#]#%[^#]#%[^\n]\n", temp, compare, buffer);
			if (strcmp(compare, email) == 0) flag7 = true;
		}
		
		if (flag){
			red();
			printf ("Email should only has 1 @ character");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (flag2 || flag3 || flag4 || flag5) {
			red();
			printf ("Email should ended with  '.com'\n");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (flag6){
			red();
			printf ("Email cannot contains # character");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (flag8){
			red();
			printf ("Email cannot contains SPACE character");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (flag7){
			red();
			printf ("Email Must be Unique!");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (flag9){
			red();
			printf ("Email should has a domain!");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		fclose(input);
		
	}
	
	while (flag || flag2 || flag3 || flag4 || flag5 || flag6 || flag7 || flag8 || flag9);
	
	char password[101];
	
	bool checker1 = false, checker2 = true, checker3 = false;
	
	do {
		
		checker1 = false, checker2 = true, checker3 = false;
		
		system ("cls");
		
		printf ("Password (0 To Exit): ");
		
		char *getpass(const char *prompt);
		
		char c;
	    int passIndex = 0;
	    
	    while (true){
	    	
	    	c = getch();
	    	if (c == '\n' || c == '\r' || c == 13) break;
	    	else if ((c == 8 || c == 127)){
	    		if ((passIndex-1) == -1) {
	    			continue;
				}
	    		passIndex--;
	    		printf ("\b \b");
			}
			else {
				password[passIndex] = c;
		        printf("*");
		        passIndex++;
			}
			
	    }
	    
	    password[passIndex] = '\0';
		
		if (strcmp (password, "0") == 0) return;
		
		if (strlen(password) < 8 || strlen (password) > 36) checker1 = true;
		
		int num = 0, karakter = 0;
		
		for (int i = 0; i < strlen(password); i++){
			if (password[i] >= '0' && password[i] <= '9') num++;
			if (password[i] >= 'a' && password[i] <= 'z') karakter++;
			if (password[i] >= 'A' && password[i] <= 'Z') karakter++;
			if (password[i] < '0' || (password[i] > '9' && password[i] <= '@') || (password[i] > 'Z' && password[i] <= 96) || password[i] > 'z') {
				checker3 = true;
			}
		}
		
		if (karakter >= 1 && num >= 1) checker2 = false;
		
		if (checker1){
			red();
			printf ("Password should be 8 - 36 characters!");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (checker2){
			red();
			printf ("Password should contains at least one number and one alphabet!");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (checker3){
			red();
			printf ("Password invalid!");
			reset();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
	}
	
	while (checker1 || checker2 || checker3);
	
	FILE *writing = fopen ("user.txt", "a");
	
	fprintf (writing, "%s#%s#%s#%lld\n", username, email, password, 10000);
	
	fclose (writing);
	
	system ("cls");
	printf ("Data inputted...");
	getchar();
	
	return;
	
}


void popHistory (History *node){
	
	// Pop One
	
	if (historyHead == historyTail){
		free (historyHead);
		historyHead = historyTail = NULL;
	}
	
	else {
		
		historyHead = historyHead->next;
		free (historyHead->prev);
		historyHead->prev = NULL;
		
	}
	
}


void tradingGuide (){
	
	system ("cls");
	
	blue ();
	puts ("What Is Forex?");
	white();
	puts ("\"Forex\", short for foreign exchange, is a global decentralized marketplace for trading currencies.");
	puts ("In forex trading, participants buy one currency by selling another currency simultaneously, with the aim of profiting from fluctuations in exchange rates.");
	puts ("It is one of the largest and most liquid financial markets in the world, operating 24 hours a day, five days a week.\n");
	
	yellow();
	puts ("What Is Candle Stick?");
	white();
	puts ("\"Canlde Stick\" in charts are a type of financial chart used to represent price movements in trading markets, including forex.");
	puts ("They visually display the open, high, low, and close prices for a specific period.");
	puts ("if the close price is higher than the open price, the candle color will be green");
	puts ("then if the close price is less than the open price, the candle color will be red.");
	puts ("shadow or tick is the highest and the lowest price of a candle.\n");
	
	magenta();
	puts ("What Is Position?");
	white();
	puts ("\"Position\" in forex trading refers to where we want to enter the market at certain price point\n");
	
	green();
	puts ("What Is Long?");
	white();
	puts ("\"Long\" in forex trading refers to a trading position where a trader buys a currency pair");
	puts ("with the expectation that its value will increase over time.\n");
	
	red();
	puts ("What Is Short?");
	white();
	puts ("\"Short\" in forex trading refers to a trading position where a trader sells a currency pair");
	puts ("with the expectation that its value will decrease over time.\n");
	
	green();
	puts ("What is Take Profit?");
	white();
	puts ("\"Take Profit\" in forex trading refers to where we will leave the market at the specified price point");
	puts ("our position will automatically closed after the market price hit our take profit price\n");
	
	red();
	puts ("What Is Stop Loss?");
	white();
	puts ("\"Stop Loss\" in forex trading refers to where we will leave the market at the specified price point");
	puts ("it's used to make sure that we don't loss all of our money and many more");
	puts ("same like take profit, our position will automatically closed after the market price hit our take profit price");
	puts ("");

	printf ("Press Enter To Continue...");
	getchar();
	
	reset();
	
	return;
	
}


void popAllHistory (){
	while (historyHead != NULL){
		popHistory (historyHead);
	}
}


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
	
	printf ("_____ ______   _______  _________  ________  ________ ___\n");
	printf ("|\\   _ \\  _   \\|\\  ___ \\|\\___   ___\\\\   __  \\|\\  _____\\\\  \\\n");
	printf ("\\ \\  \\\\\\__\\ \\  \\ \\   __/\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\__/\\ \\  \\\n");
	printf (" \\ \\  \\\\|__| \\  \\ \\  \\_|/__  \\ \\  \\ \\ \\   __  \\ \\   __\\\\ \\  \\\n");
	printf ("  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\  \\ \\  \\ \\ \\  \\ \\  \\ \\  \\_| \\ \\  \\\n");
	printf ("   \\ \\__\\    \\ \\__\\ \\_______\\  \\ \\__\\ \\ \\__\\ \\__\\ \\__\\   \\ \\__\\\n");
	printf ("    \\|__|     \\|__|\\|_______|   \\|__|  \\|__|\\|__|\\|__|    \\|__|\n");
	
}


void fullScreen() {
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void orange(){
    printf ("\033[1;38;5;208m");
}

void purple(){
    printf ("\033[1;38;5;165m");
}

void grey(){
    printf ("\033[1;30m");
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
	
	int randColor = rand() % 10;
	
	if (randColor == 0) red();
	if (randColor == 1) green();
	if (randColor == 2) yellow();
	if (randColor == 3) blue();
	if (randColor == 4) magenta();
	if (randColor == 5) cyan();
	if (randColor == 6) white();
	if (randColor == 7) grey();
	if (randColor == 8) orange();
	if (randColor == 9) purple();
	
}


void stayScreen() {
	COORD cursorPosition; cursorPosition.X = 0; cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}


/*


ARCHIEVED




*/

