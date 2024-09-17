#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>


struct Product {
	
	char productID[6];
	char name[101];
	long long int price;
	char color[21];
	int quantity;
	char size[5];
	
};


Product productList [100] = {};
int productSize = 0;
bool noData = false;

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

void addProduct();
void viewProduct();
void updateProduct();
void removeProduct();

void rewriteProduct ();
void readFile ();
void viewOnly ();
void swap (Product *a, Product *b);
void sort (int sorted);

int main(){
	
	srand(time(0));
	
	int action;
	
	do {
		
		system ("cls");
		
		printLogo();
		
		puts ("\n1. Add Product");
		puts ("2. View Product");
		puts ("3. Update Product");
		puts ("4. Remove Product");
		puts ("0. Exit\n");
		
		printf (">> ");
		scanf ("%d", &action); getchar();
		
		if (action == 1) {
			addProduct();
		}
		
		else if (action == 2){
			viewProduct();
		}
		
		else if (action == 3){
			updateProduct();
		}
		
		else if (action == 4){
			removeProduct();
		}
		
		else if (action == 0){
			printExit();
		}
		
		else {
			printf ("\n\n[!] Input between 0 - 4!");
			getchar();
		}
		
	}
	
	while (action != 0);
	
	return 0;
	
}

void addProduct() {
	
	system ("cls");
	
	char name[101];
	
	do {
		
		printf ("Input product name [10 - 20 characters]: ");
		scanf ("%[^\n]", name);
		getchar();
		
		if (strlen(name) >= 10 && strlen (name) <= 20) break;
		
		// There is no condition to check if the product name is unique or not
		
	}
	
	while (true);
	
	long long int price;
	
	do {
		
		printf ("Input product price [50000 - 100000]: ");
		scanf ("%lld", &price);
		getchar();
		
		if (price >= 50000 && price <= 100000) break;
		
	}
	
	while (true);
	
	char color[21];
	
	do {
		
		printf ("Input product color [Black | White | Brown]: ");
		scanf ("%[^\n]", color);
		getchar();
		
		if (strcmp (color, "Black") == 0 || strcmp (color, "White") == 0 || strcmp (color, "Brown") == 0) break;
		
	}
	
	while (true);
	
	int quantity;
	
	do {
		
		printf ("Input product quantity [10 - 99]: ");
		scanf ("%d", &quantity);
		getchar();
		
		if (quantity >= 10 && quantity <= 99) break;
		
	}
	
	while (true);
	
	char size[5];
	
	do {
		
		printf ("Input product size [S | M | L | XL]: ");
		scanf ("%[^\n]", size);
		getchar();
		
		if (strcmp (size, "S") == 0 || strcmp (size, "M") == 0 || strcmp (size, "L") == 0 || strcmp (size, "XL") == 0) break;
		
	}
	
	while (true);
	
	char id[6] = {"BR"};
	
	for (int i = 2; i < 5; i++){
		id[i] = rand() % 10 + '0';
	}
	
	strcpy(productList[productSize].productID, id);
	strcpy(productList[productSize].name, name);
	productList[productSize].price = price;
	strcpy(productList[productSize].color, color);
	productList[productSize].quantity = quantity;
	strcpy(productList[productSize].size, size);
	
	productSize++;
	
	FILE *fptr = fopen("products.txt", "a+");

	if (fptr == NULL) return;
	
	fprintf(fptr, "%s#%s#%lld#%s#%d#%s\n", id, name, price, color, quantity, size);
	
	fclose(fptr);
	
	productSize++;
	
	printf ("\n\nProduct Successfully Added\n\n");
	printf ("Press enter to continue...");
	getchar();
	
	return;
	
}

void readFile (){
	int line = 0;
	
	FILE *input = fopen("products.txt", "a+");
	
	if (input == NULL) return;
	
	while (!feof(input)){
		fscanf (input, "%[^#]#%[^#]#%lld#%[^#]#%d#%[^\n]\n", productList[line].productID, productList[line].name, &productList[line].price, productList[line].color, &productList[line].quantity, productList[line].size);
		++line;
	}
	
	productSize = line;
	
	// Bug Catcher
	
	if (productList[line-1].price == 0) {
		productSize--;
	}
	
	return;
	
}

void viewProduct() {
	
	readFile();
	
	int action;
	
	int sorted = 0;
	
	do {
		
		system ("cls");
		
//		printf ("%d\n", productSize);
		
		if (sorted == 1) puts ("Sorted by: ID\n");
		else if (sorted == 2) puts ("Sorted by: Name\n");
		else if (sorted == 3) puts ("Sorted by: Color\n");
		else if (sorted == 4) puts ("Sorted by: Quantity\n");
		else if (sorted == 5) puts ("Sorted by: Size\n");
		// Bonus sorted by price
		else if (sorted == 6) puts ("Sorted by: Price\n");
	
		for (int i = 0; i < 74; i++) printf ("=");
		puts("");
		
		printf ("| %-7s | %-22s | %-5s | %-4s | %-10s | %-7s |\n", "ID", "Product Name", "Color", "Size", "Quantity", "Price");
		
		for (int i = 0; i < 74; i++) printf ("=");
		puts("");
		
		if (productSize == 0){
			printf ("| %-70s |\n", "There's no product yet!");
			for (int i = 0; i < 74; i++) printf ("=");
			puts("\n");
			printf ("Press enter to continue...");
			getchar();
			return;
		}
		
		else {
			for (int i = 0; i < productSize; i++){
				printf ("| %-7s | %-22s | %-5s | %-4s | %-10d | %-7lld |\n", productList[i].productID, productList[i].name, productList[i].color, productList[i].size, productList[i].quantity, productList[i].price);
			}
		}
			
		for (int i = 0; i < 74; i++) printf ("=");
		puts("");
		
		puts ("");
		
		puts ("Sort by:");
		puts ("[1] ID");
		puts ("[2] Name");
		puts ("[3] Color");
		puts ("[4] Quantity");
		puts ("[5] Size");
		puts ("[6] Price");
		puts ("[0] Back");
		
		printf ("\n>> ");
		scanf ("%d", &action);
		getchar();
		
		if (action == 1) {
			sorted = 1;
			sort (sorted);
		}
		
		else if (action == 2) {
			sorted = 2;
			sort (sorted);
		}
		
		else if (action == 3){
			sorted = 3;
			sort (sorted);
		}
		
		else if (action == 4){
			sorted = 4;
			sort (sorted);
		}
		
		else if (action == 5){
			sorted = 5;
			sort (sorted);
		}
		
		else if (action == 6){
			sorted = 6;
			sort (sorted);
		}
		
	}
	
	while (action != 0);
	
	// So the sorted array of struct changed
	
	rewriteProduct();
	
	return;
	
}

void swap(Product *a, Product *b) {
	Product temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort (int sorted) {
	
	for(int i=0;i<productSize-1;i++){
		for(int j=0;j<productSize-i-1;j++){
			
			if (sorted == 1){
				if(strcmp (productList[j].productID, productList[j+1].productID) > 0){
					swap(&productList[j], &productList[j+1]);
				}
			}
			
			else if (sorted == 2){
				if(strcmp (productList[j].name, productList[j+1].name) > 0){
					swap(&productList[j], &productList[j+1]);
				}
			}
			
			else if (sorted == 3){
				if(strcmp (productList[j].color, productList[j+1].color) > 0){
					swap(&productList[j], &productList[j+1]);
				}
			}
			
			else if (sorted == 4){
				if(productList[j].quantity > productList[j+1].quantity){
					swap(&productList[j], &productList[j+1]);
				}
			}
			
			else if (sorted == 5){
				if(strcmp (productList[j].size, productList[j+1].size) > 0){
					swap(&productList[j], &productList[j+1]);
				}
			}
			
			else if (sorted == 6){
				if(productList[j].price > productList[j+1].price){
					swap(&productList[j], &productList[j+1]);
				}
			}
			
		}
	}
	
}

void viewOnly () {
	
	noData = false;
	
	for (int i = 0; i < 74; i++) printf ("=");
	puts("");
	
	printf ("| %-7s | %-22s | %-5s | %-4s | %-10s | %-7s |\n", "ID", "Product Name", "Color", "Size", "Quantity", "Price");
	
	for (int i = 0; i < 74; i++) printf ("=");
	puts("");
	
	if (productSize == 0){
		printf ("| %-70s |\n", "There's no product yet!");
		noData= true;
	}
	
	else {
		for (int i = 0; i < productSize; i++){
			printf ("| %-7s | %-22s | %-5s | %-4s | %-10d | %-7lld |\n", productList[i].productID, productList[i].name, productList[i].color, productList[i].size, productList[i].quantity, productList[i].price);
		}
	}
		
	for (int i = 0; i < 74; i++) printf ("=");
	puts("");
	
}

void updateProduct() {
	
	readFile ();
	
	char id[6];
	bool flag = false;
	noData = false;
	
	do {
		
		system ("cls");
		
		viewOnly();
		
		if (noData){
			printf ("\n\nPress enter to continue...");
			getchar();
			return;
		}
		
		puts ("");
		
		printf ("Input product ID to update: ");
		scanf ("%[^\n]", id); getchar();
		
		int index = -1;
		
		for (int i = 0; i < productSize; i++){
			if (strcmp(productList[i].productID, id) == 0) {
				index = i;
				flag = true;
				break;
			}
		}
		
		if (flag){
			
			printf ("\n\nProduct Found!\n");
			
			char name[101];
	
			do {
				
				printf ("Input product name [10 - 20 characters]: ");
				scanf ("%[^\n]", name);
				getchar();
				
				if (strlen(name) >= 10 && strlen (name) <= 20) break;
				
			}
			
			while (true);
			
			long long int price;
			
			do {
				
				printf ("Input product price [50000 - 100000]: ");
				scanf ("%lld", &price);
				getchar();
				
				if (price >= 50000 && price <= 100000) break;
				
			}
			
			while (true);
			
			char color[21];
			
			do {
				
				printf ("Input product color [Black | White | Brown]: ");
				scanf ("%[^\n]", color);
				getchar();
				
				if (strcmp (color, "Black") == 0 || strcmp (color, "White") == 0 || strcmp (color, "Brown") == 0) break;
				
			}
			
			while (true);
			
			int quantity;
			
			do {
				
				printf ("Input product quantity [10 - 99]: ");
				scanf ("%d", &quantity);
				getchar();
				
				if (quantity >= 10 && quantity <= 99) break;
				
			}
			
			while (true);
			
			char size[5];
			
			do {
				
				printf ("Input product size [S | M | L | XL]: ");
				scanf ("%[^\n]", size);
				getchar();
				
				if (strcmp (size, "S") == 0 || strcmp (size, "M") == 0 || strcmp (size, "L") == 0 || strcmp (size, "XL") == 0) break;
				
			}
			
			while (true);
			
			strcpy(productList[index].name, name);
			productList[index].price = price;
			strcpy(productList[index].color, color);
			productList[index].quantity = quantity;
			strcpy(productList[index].size, size);
			
			rewriteProduct ();
			
			printf ("Product with ID %s updated successfully!\n\n", id);
			
			printf ("Press [ENTER] to continue..."); 

			getchar();
			
		}
		
		else {
			printf ("Product with ID %s not found!\n\n", id);
			printf ("Press [ENTER] to continue..."); 
			getchar();
			// There is break in the example
			flag = !flag;
		}
		
	}
	
	while (!flag);
	
}

void rewriteProduct () {
	
	FILE *fptr = fopen("products.txt", "w+");
	
	if(fptr==NULL) return;
	
	for(int i=0;i<productSize;i++){
		fprintf(fptr, "%s#%s#%lld#%s#%d#%s\n", productList[i].productID, productList[i].name, productList[i].price, productList[i].color, productList[i].quantity, productList[i].size);
	}
	
	fclose(fptr);
	
	return;
	
}

void removeProduct() {
	
	char id[6];
	bool flag = false;
	noData = false;
	
	do {
		
		system ("cls");
		
		readFile ();
		viewOnly();
		
		if (noData){
			printf ("\n\nPress enter to continue...");
			getchar();
			return;
		}
		
		puts ("");
		
		printf ("Input product ID to delete: ");
		scanf ("%[^\n]", id); getchar();
		
		for (int i = 0; i < productSize; i++){
			if (strcmp(productList[i].productID, id) == 0) {
				
				flag = true;
				
				for(int j=i; j < productSize-1; j++){
					productList[j] = productList[j+1];
				}
				
				break;
				
			}
		}
		
		if (flag){
			
//			free (productList[productSize-1].name);
//			free (productList[productSize-1].color);
//			free (productList[productSize-1].price);
//			free (productList[productSize-1].productID);
//			free (productList[productSize-1].quantity);
//			free (productList[productSize-1].size);
			
//			free(productList[productSize-1].productID);
//			free(productList[productSize-1].name);
//			free(productList[productSize-1].color);
//			free (productList[productSize-1].size);
//
//			free (productList[productSize-1]);
//			productList[productSize-1] = NULL;

			productSize--;
			
			strcpy(productList[productSize].productID, "");
			strcpy(productList[productSize].name, "");
			productList[productSize].price = 0;
			strcpy(productList[productSize].color, "");
			productList[productSize].quantity = 0;
			strcpy(productList[productSize].size, "");
			
			rewriteProduct ();
			
			printf ("\n\nProduct successfully deleted!\n\n");
			printf ("Press [ENTER] to continue...");
			getchar();
			flag = true;
			
		}
		
		else {
			
			printf ("\n\nProduct not found!\n\n");
			printf ("Press [ENTER] to continue...");
			getchar();
			flag = true;
			
		}
		
	}
	
	while (!flag);
	
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
	
	puts ("/$$$$$$$                    /$$$$$$  /$$$$$$  /$$       /$$");
	puts ("| $$__  $$                  |_  $$_/ /$$__  $$| $$      | $$");
	puts ("| $$  \\ $$  /$$$$$$   /$$$$$$ | $$  | $$  \\__/| $$$$$$$ | $$   /$$  /$$$$$$");
	puts ("| $$$$$$$  /$$__  $$ /$$__  $$| $$  |  $$$$$$ | $$__  $$| $$  /$$/ |____  $$");
	puts ("| $$__  $$| $$$$$$$$| $$  \\__/| $$   \\____  $$| $$  \\ $$| $$$$$$/   /$$$$$$$");
	puts ("| $$  \\ $$| $$_____/| $$      | $$   /$$  \\ $$| $$  | $$| $$_  $$  /$$__  $$");
	puts ("| $$$$$$$/|  $$$$$$$| $$     /$$$$$$|  $$$$$$/| $$  | $$| $$ \\  $$|  $$$$$$$");
	puts ("|_______/  \\_______/|__/    |______/ \\______/ |__/  |__/|__/  \\__/ \\_______/");
	puts ("");
	
}


/*


ARCHIEVED


//	char id[6];
//	char name[101];
//	long long int price;
//	char color[21];
//	int quantity;
//	char size[5];
	
//	while (!feof(input)){
//		 fscanf (input, "%[^#]#%[^#]#%lld#%[^#]#%d#%[^\n]\n", id, name, &price, color, &quantity, size);
//		 printf ("| %-7s | %-22s | %-5s | %-4s | %-10d | %-7lld |\n", id, name, color, size, quantity, price);
//	}



*/

