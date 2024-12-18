#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>

struct Data {
	
	char location[51];
	char city[51];
	long long int price;
	int bathroom;
	int room;
	int carPark;
	char type[21];
	char furnish[21];
	
};

Data data[9999];

int counter = 0;

void readFile();
void gotoxy(int x, int y);
void printLogo();
void printTitle();
void anotherTitle();
void checker(int action);
void exitLogo();
void fullScreen();
void display();
void exportData();
void search();
void sort();
int printMenu();
int randomColor();
void mergeSort (struct data[], int l, int r, int sortType, char column[]);
void sortingAsc (struct data[], int l, int m, int r, char column[]);
void swap (Data dataX, Data dataY);
void bubbleSortAsc (Data data[], int size, char column[]);

void red();
void green();
void yellow();
void blue();
void magenta();
void cyan();
void white();
void reset();
void randomClr();


int main(){
	
	srand(time(0));
	readFile();
	
	fullScreen();
	printLogo();
	
	int action;
	
	do {

		action = printMenu();
		
		checker(action);
		
	}
	
	while (action != 17);
	
	return 0;
}


void checker(int action) {
	
	switch (action) {
	
		case 13:
			display();
			break;
		case 14:
			search();
			break;
		case 15:
			sort();
			break;
		case 16:
			exportData();
			break;
		case 17:
			exitLogo();
			break;
	
	}
	
}

int printMenu(){
	
	int y = 13;
	
	do {
		
		system("cls");
		
		printTitle();
		
		printf ("What do you want to do?\n");
		printf ("1. Display data\n");
		printf ("2. Search data\n");
		printf ("3. Sort data\n");
		printf ("4. Export data\n");
		printf ("5. Exit\n\n");
		printf (">> ");
		printf ("Alt + Enter to escape the full screen");
		
		if (y == 13){
			gotoxy (21, y);
			printf ("<");
		}
		
		else if (y == 14){
			gotoxy (20, y);
			printf ("<");
		}
		
		else if (y == 15){
			gotoxy (19, y);
			printf ("<");
		}
		
		else if (y == 16){
			gotoxy (19, y);
			printf ("<");
		}
		
		else if (y == 17){
			gotoxy (15, y);
			printf ("<");
		}
		
		gotoxy (0, 22);
		char c = getch();
		
		if (c == 72) {
			if (y > 13) y--;
			else y = 17;
		}
		else if (c == 80){
			if (y < 17) y++;
			else y = 13;
		} 
		else if (c == 13) break;
		
	}
	
	while (1);

	return y;
	
}

void readFile(){
	
	FILE *input = fopen("file.csv", "r");

    char temp[101];
    fscanf(input, "%[^\n]\n", temp);

    while (fscanf(input, "%[^,],%[^,],%lld,%d,%d,%d,%[^,],%[^\n]\n",
                                   data[counter].location, data[counter].city, &data[counter].price,
                                   &data[counter].room, &data[counter].bathroom, &data[counter].carPark,
                                   data[counter].type, data[counter].furnish) == 8) {
        counter++;
    }

    fclose(input);
	
}

void display(){
	
	system("cls");

    int row;
    printf("Please input the number of rows: ");
    scanf("%d", &row);
    getchar();
	
	if (row > counter) row = counter;
	
	puts("");
    printf("====================================================================================================================================\n");
    printf("| No.  | Location                   | City         | Price          | Rooms   | Bathroom | Carpark   | Type          | Furnish     |\n");
    printf("|==================================================================================================================================|\n");

    for (int x = 0; x < row; x++) {
    	randomClr();
        printf("| %-4d | %-26s | %-12s | %-14lld | %-7d | %-8d | %-9d | %-13s | %-11s |\n", x+1,
               data[x].location, data[x].city, data[x].price, data[x].room, data[x].bathroom,
               data[x].carPark, data[x].type, data[x].furnish);
    }
    
    reset();

    printf("|==================================================================================================================================|\n");

    printf("\nPress enter to continue...");
    getchar();
	
}


void search(){
	
	system("cls");

    char header[21];
    
    do {
    	
    	printf("Please input the column: ");
	    scanf("%s", header);
	    getchar();
	    
		if (strcmpi (header, "Location") != 0 && strcmpi (header, "City") != 0 && strcmpi (header, "Price") != 0 &&
		strcmpi (header, "Rooms") != 0 && strcmpi (header, "Bathroom") != 0 && strcmpi (header, "Carpark") != 0 && strcmpi (header, "Type") != 0
		&& strcmpi (header, "Furnish") != 0) {
			printf ("\nInvalid input! Try again!\n");
		}
		    
	}
	
	while (strcmpi (header, "Location") != 0 && strcmpi (header, "City") != 0 && strcmpi (header, "Price") != 0 &&
	strcmpi (header, "Rooms") != 0 && strcmpi (header, "Bathroom") != 0 && strcmpi (header, "Carpark") != 0 && strcmpi (header, "Type") != 0
	&& strcmpi (header, "Furnish") != 0);
	
	char find[31];
	printf("What do you want to search: ");
	scanf ("%[^\n]", find);
	getchar();
	
	int row = 0;

    printf("====================================================================================================================================\n");
    printf("| No.  | Location                   | City         | Price          | Rooms   | Bathroom | Carpark   | Type          | Furnish     |\n");
    printf("|==================================================================================================================================|\n");

    for (int x = 0; x < counter; x++) {
    	
    	if (strcmpi (header, "Location") == 0){
    		if (strcmpi (find, data[x].location) == 0){
    			randomClr();
		    	printf("| %-4d | %-26s | %-12s | %-14lld | %-7d | %-8d | %-9d | %-13s | %-11s |\n", row+1,
	               data[x].location, data[x].city, data[x].price, data[x].room, data[x].bathroom,
	               data[x].carPark, data[x].type, data[x].furnish);
	            row++;
			}
		}
		
		else if (strcmpi (header, "City") == 0){
			if (strcmpi (find, data[x].city) == 0){
				randomClr();
	    		printf("| %-4d | %-26s | %-12s | %-14lld | %-7d | %-8d | %-9d | %-13s | %-11s |\n", row+1,
	               data[x].location, data[x].city, data[x].price, data[x].room, data[x].bathroom,
	               data[x].carPark, data[x].type, data[x].furnish);
	            row++;
			}
		}
		
		else if (strcmpi (header, "Price") == 0){
			if (atoi(find) == data[x].price){
				randomClr();
	    		printf("| %-4d | %-26s | %-12s | %-14lld | %-7d | %-8d | %-9d | %-13s | %-11s |\n", row+1,
	               data[x].location, data[x].city, data[x].price, data[x].room, data[x].bathroom,
	               data[x].carPark, data[x].type, data[x].furnish);
	            row++;
			}
		}
		
		else if (strcmpi (header, "Rooms") == 0){
			if (atoi(find) == data[x].room){
				randomClr();
	    		printf("| %-4d | %-26s | %-12s | %-14lld | %-7d | %-8d | %-9d | %-13s | %-11s |\n", row+1,
	               data[x].location, data[x].city, data[x].price, data[x].room, data[x].bathroom,
	               data[x].carPark, data[x].type, data[x].furnish);
	            row++;
			}
		}
		
		else if (strcmpi (header, "Bathroom") == 0){
			if (atoi(find) == data[x].bathroom){
				randomClr();
	    		printf("| %-4d | %-26s | %-12s | %-14lld | %-7d | %-8d | %-9d | %-13s | %-11s |\n", row+1,
	               data[x].location, data[x].city, data[x].price, data[x].room, data[x].bathroom,
	               data[x].carPark, data[x].type, data[x].furnish);
	            row++;
			}
		}
		
		else if (strcmpi (header, "Carpark") == 0){
			if (atoi(find) == data[x].carPark){
				randomClr();
	    		printf("| %-4d | %-26s | %-12s | %-14lld | %-7d | %-8d | %-9d | %-13s | %-11s |\n", row+1,
	               data[x].location, data[x].city, data[x].price, data[x].room, data[x].bathroom,
	               data[x].carPark, data[x].type, data[x].furnish);
	            row++;
			}
		}
		
		else if (strcmpi (header, "Type") == 0){
			if (strcmpi (find, data[x].type) == 0){
				randomClr();
	    		printf("| %-4d | %-26s | %-12s | %-14lld | %-7d | %-8d | %-9d | %-13s | %-11s |\n", row+1,
	               data[x].location, data[x].city, data[x].price, data[x].room, data[x].bathroom,
	               data[x].carPark, data[x].type, data[x].furnish);
	            row++;
			}
		}
		
		else if (strcmpi (header, "Furnish") == 0 ){
			if (strcmpi (find, data[x].furnish) == 0){
				randomClr();
	    		printf("| %-4d | %-26s | %-12s | %-14lld | %-7d | %-8d | %-9d | %-13s | %-11s |\n", row+1,
	               data[x].location, data[x].city, data[x].price, data[x].room, data[x].bathroom,
	               data[x].carPark, data[x].type, data[x].furnish);
	            row++;
			}
		}
               
    }
    
    if (row == 0){
    	randomClr();
    	printf("| Data not found!                                                                                                                  |\n");
	}
	
	reset();

    printf("|==================================================================================================================================|\n");
	
	printf ("\n%d / %d data found\n", row, counter);
	
    printf("\nPress enter to continue...");
    getchar();
	
}

void sortingAsc (Data data[], int l, int m, int r, char column[]){
	
	int n1 = m - l + 1;
	int n2 = r - m;
	
	Data L[n1], R[n2];
	
	for (int i = 0; i < n1; i++) L[i] = data[l + i];
	
	for (int j = 0; j < n2; j++) R[j] = data[m + 1 + j];
	
	int k = l;
	int i = 0, j = 0;
	
	while (i < n1 && j < n2){
		
		if (strcmpi (column, "Location") == 0){
    		if (strcmpi (L[i].location, R[j].location) < 0){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "City") == 0){
			if (strcmpi (L[i].city, R[j].city) < 0){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Price") == 0){
			if (L[i].price <= R[j].price){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Rooms") == 0){
			if (L[i].room <= R[j].room){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Bathroom") == 0){
			if (L[i].bathroom <= R[j].bathroom){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Carpark") == 0){
			if (L[i].carPark <= R[j].carPark){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Type") == 0){
			if (strcmpi (L[i].type, R[j].type) < 0){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Furnish") == 0 ){
			if (strcmpi (L[i].furnish, R[j].furnish) < 0){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		k++;
		
	}
	
	while (i < n1){
		data[k] = L[i];
		i++;
		k++;
	}
	
	while (j < n2){
		data[k] = R[j];
		j++;
		k++;
	}
	
}


void sortingDesc (Data data[], int l, int m, int r, char column[]){
	
	int n1 = m - l + 1;
	int n2 = r - m;
	
	Data L[n1], R[n2];
	
	for (int i = 0; i < n1; i++) L[i] = data[l + i];
	
	for (int j = 0; j < n2; j++) R[j] = data[m + 1 + j];
	
	int k = l;
	int i = 0, j = 0;
	
	while (i < n1 && j < n2){
		
		if (strcmpi (column, "Location") == 0){
    		if (strcmpi (L[i].location, R[j].location) > 0){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "City") == 0){
			if (strcmpi (L[i].city, R[j].city) > 0){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Price") == 0){
			if (L[i].price > R[j].price){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Rooms") == 0){
			if (L[i].room > R[j].room){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Bathroom") == 0){
			if (L[i].bathroom > R[j].bathroom){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Carpark") == 0){
			if (L[i].carPark > R[j].carPark){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Type") == 0){
			if (strcmpi (L[i].type, R[j].type) > 0){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		else if (strcmpi (column, "Furnish") == 0 ){
			if (strcmpi (L[i].furnish, R[j].furnish) > 0){
		    	data[k] = L[i];
		    	i++;
			}
			else {
				data[k] = R[j];
		    	j++;
			}
		}
		
		k++;
		
	}
	
	while (i < n1){
		data[k] = L[i];
		i++;
		k++;
	}
	
	while (j < n2){
		data[k] = R[j];
		j++;
		k++;
	}
	
}


void mergeSort (Data data[], int l, int r, int sortType, char column[]){
	
	if (l < r){
		
		int m = l + (r - l) / 2;
		
		mergeSort (data, l, m, sortType, column);
		mergeSort (data, m+1, r, sortType, column);
		
		if (sortType == 1) sortingAsc (data, l, m, r, column);
		else sortingDesc (data, l, m, r, column);
		
	}
	
}


void sort(){
	
	// Sorting asumption --> Sort the data globally
	
	system("cls");

    char header[21];
    
    do {
    	
    	printf("Please input the column: ");
	    scanf("%s", header);
	    getchar();
	    
		if (strcmpi (header, "Location") != 0 && strcmpi (header, "City") != 0 && strcmpi (header, "Price") != 0 &&
		strcmpi (header, "Rooms") != 0 && strcmpi (header, "Bathroom") != 0 && strcmpi (header, "Carpark") != 0 && strcmpi (header, "Type") != 0
		&& strcmpi (header, "Furnish") != 0) {
			printf ("\nInvalid input! Try again!\n");
		}
		    
	}
	
	while (strcmpi (header, "Location") != 0 && strcmpi (header, "City") != 0 && strcmpi (header, "Price") != 0 &&
	strcmpi (header, "Rooms") != 0 && strcmpi (header, "Bathroom") != 0 && strcmpi (header, "Carpark") != 0 && strcmpi (header, "Type") != 0
	&& strcmpi (header, "Furnish") != 0);
	
	char find[31];
	
	do {
		
		printf("Sort ascendingly or descendingly? [asc | desc]: ");
		scanf ("%s", find);
		getchar();
		
		if (strcmpi (find, "asc") != 0 && strcmpi (find, "desc") != 0) printf ("\nInvalid input! Try again!\n");
		
	}
	
	while (strcmpi (find, "asc") != 0 && strcmpi (find, "desc") != 0);
	
	if (strcmpi (find, "asc") == 0){
		mergeSort (data, 0, counter-1, 1, header);
	}
	
	else {
		mergeSort (data, 0, counter-1, 2, header);
	}
	
	int row = 0;

    puts("");
    printf("====================================================================================================================================\n");
    printf("| No.  | Location                   | City         | Price          | Rooms   | Bathroom | Carpark   | Type          | Furnish     |\n");
    printf("|==================================================================================================================================|\n");

    for (int x = 0; x < 10; x++) {
    	randomClr();
        printf("| %-4d | %-26s | %-12s | %-14lld | %-7d | %-8d | %-9d | %-13s | %-11s |\n", x+1,
               data[x].location, data[x].city, data[x].price, data[x].room, data[x].bathroom,
               data[x].carPark, data[x].type, data[x].furnish);
        row++;
    }
    
    reset();

    printf("|==================================================================================================================================|\n");
	
	printf ("\n%d / %d data found\n", row, counter);
	
    printf("\nPress enter to continue...");
    getchar();
	
}


void exportData(){
	
	system ("cls");
	
	char fileName[101];
	bool flag = false;

	do {
		
		printf ("Input the file name: ");
		scanf ("%s", fileName); getchar();
		
		for (int a = 0; a < strlen(fileName); a++){
			if (fileName[a] > 122 || (fileName[a] < 65 && fileName[a] > 57) || (fileName[a] > 90 && fileName[a] < 95) ||
			(fileName[a] > 95 && fileName[a] < 97) || fileName[a] < 48){
				printf ("Invalid characters deteced!\n\n");
				flag = true;
				break;
			}
			else flag = false;
		}
		
	}
	
	while (flag);
	
	int length = strlen (fileName);
	
	strcat(fileName, ".csv");
	
	FILE *exportFile = fopen (fileName, "w");
	
	fprintf (exportFile, "Location,Location2,Price,Rooms,Bathroom,CarParks,Type,Furnish\n");
	
	for (int x = 0; x < counter; x++){
		fprintf (exportFile, "%s,%s,%lld,%d,%d,%d,%s,%s\n", data[x].location, data[x].city, data[x].price, 
		data[x].room, data[x].bathroom, data[x].carPark, data[x].type, data[x].furnish);
	}
	
	fclose (exportFile);
	
	printf ("Data successfuly written to file %s file!\n\n", fileName);
	
	printf ("Press enter to continue..."); getchar();
	
}


void fullScreen() {
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void exitLogo() {
	
	system("cls");
	
	white();
	printf ("  _______ _                 _        \n");
	printf (" |__   __| |               | |       \n");
	printf ("    | |  | |__   __ _ _ __ | | _____ \n");
	printf ("    | |  | '_ \\ / _` | '_ \\| |/ / __|\n");
	printf ("    | |  | | | | (_| | | | |   <\\__ \\\n");
	printf ("    |_|  |_| |_|\\__,_|_| |_|_|\\_\\___/\n");
	printf ("\n\n");
	
	char word[] = {"Love youu :)"};
	
	for (int i = 0; i < strlen(word); i++){
		randomClr();
		printf ("%c", word[i]);
		Sleep(100);
	}
	
	reset();
	
	puts("");
	
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


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printLogo(){
	gotoxy(45, 0);
	printf ("  ______    __                          __                     \n"); Sleep(100);
	gotoxy(45, 1);
	printf (" /      \  /  |                        /  |                    \n"); Sleep(100);
	gotoxy(45, 2);
	printf ("/$$$$$$  |_$$ |_     ______   _______  $$ |  ______   __    __ \n"); Sleep(100);
	gotoxy(45, 3);
	printf ("$$ \__$$// $$   |   /      \ /       \ $$ | /      \ /  |  /  |\n"); Sleep(100);
	gotoxy(45, 4);
	printf ("$$      \$$$$$$/    $$$$$$  |$$$$$$$  |$$ |/$$$$$$  |$$ |  $$ |\n"); Sleep(100);
	gotoxy(45, 5);
	printf (" $$$$$$  | $$ | __  /    $$ |$$ |  $$ |$$ |$$    $$ |$$ |  $$ |\n"); Sleep(100);
	gotoxy(45, 6);
	printf ("/  \__$$ | $$ |/  |/$$$$$$$ |$$ |  $$ |$$ |$$$$$$$$/ $$ \__$$ |\n"); Sleep(100);
	gotoxy(45, 7);
	printf ("$$    $$/  $$  $$/ $$    $$ |$$ |  $$ |$$ |$$       |$$    $$ |\n"); Sleep(100);
	gotoxy(45, 8);
	printf (" $$$$$$/    $$$$/   $$$$$$$/ $$/   $$/ $$/  $$$$$$$/  $$$$$$$ |\n"); Sleep(100);
	gotoxy(45, 9);
	printf ("                                                     /  \__$$ |\n"); Sleep(100);
	gotoxy(45, 10);
	printf ("                                                     $$    $$/ \n"); Sleep(100);
	gotoxy(45, 11);
	printf ("                                                      $$$$$$/  \n"); Sleep(1500);
	gotoxy(45, 12);
}

void printTitle(){
	printf (" .----------------.  .----------------.  .----------------.  .----------------. \n");
	printf ("| .--------------. || .--------------. || .--------------. || .--------------. |\n");
	printf ("| |  ________    | || |      __      | || |  _________   | || |      __      | |\n");
	printf ("| | |_   ___ `.  | || |     /  \\     | || | |  _   _  |  | || |     /  \\     | |\n");
	printf ("| |   | |   `. \\ | || |    / /\\ \\    | || | |_/ | | \\_|  | || |    / /\\ \\    | |\n");
	printf ("| |   | |    | | | || |   / ____ \\   | || |     | |      | || |   / ____ \\   | |\n");
	printf ("| |  _| |___.' / | || | _/ /    \\ \\_ | || |    _| |_     | || | _/ /    \\ \\_ | |\n");
	printf ("| | |________.'  | || ||____|  |____|| || |   |_____|    | || ||____|  |____|| |\n");
	printf ("| |              | || |              | || |              | || |              | |\n");
	printf ("| '--------------' || '--------------' || '--------------' || '--------------' |\n");
	printf (" '----------------'  '----------------'  '----------------'  '----------------' \n");
	printf ("\n");
}

void anotherTitle(){
	printf ("_______                                   \n");
	printf ("\  ___ `'.                                \n");
	printf (" ' |--.\  \                               \n");
	printf (" | |    \  '               .|             \n");
	printf (" | |     |  '    __      .' |_     __     \n");
	printf (" | |     |  | .:--.'.  .'     | .:--.'.   \n");
	printf (" | |     ' .'/ |   \ |'--.  .-'/ |   \ |  \n");
	printf (" | |___.' /' `" "__ | |  |  |"  " __ | |  \n");
	printf ("/_______.'/   .'.''| |   |  |   .'.''| |  \n");
	printf ("\_______|/   / /   | |_  |  '.'/ /   | |_ \n");
	printf ("             \ \._,\ '/  |   / \ \._,\ '/ \n");
	printf ("\n\n");
}

