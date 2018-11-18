#include <stdio.h>
#include <stdlib.h>
#include <cstring>

//Code by: David Woodward
//euid:		dww0085
//assignment: exam 1

int main() {
	
	char trans1[52];
	char space;
	for (int i=0; i < 52; i++){
	  scanf("%c", &trans1[i]);
	  scanf("%c", &space);
	}
	int numOfWords;
	while(scanf("%d", &numOfWords) != EOF) {
	  printf("%d\n", numOfWords);
	
	  char *words[numOfWords];
	  char *enWords[numOfWords];

	  //for loop for each word in sentance
	  for (int i=0; i < numOfWords; i++) {
	    words[i] = (char*)malloc(10*sizeof(char));
	    enWords[i] = (char*)malloc(10*sizeof(char));
	    scanf("%s", words[i]);
	    strcpy(enWords[i], words[i]);

	    //encrypy - char by char
	    char *address;
	    for (int j=0; j < strlen(words[i]); j++) {
	      address = strchr(trans1, words[i][j]);
	      enWords[i][j] = *(address+26*sizeof(*address));
	    }
	   
	   printf("%s ", enWords[i]);
	  }

	  printf("\n");
	  for (int i=0; i < numOfWords; i++) {
	    free(words[i]);
	    free(enWords[i]);
	  }
	}














































/*

	char input[15];
	bankAccount account;
	int accountNum, error;

	while(true) {
	
	printf("bank> ");
	scanf("%s", input);

	//conditions for each operation
	if (!strcmp(input, "deposit")){

	  int depAmount;
	  scanf("%d %d", &accountNum, &depAmount);
	  account.deposit(accountNum, depAmount);
	  printf("DEPOSIT SELECTED\n");

	} else if (!strcmp(input, "withdraw")){

	  int withAmount;
	  scanf("%d %d", &accountNum, &withAmount);
	  error = account.withdraw(accountNum, withAmount);
	  printf("WITHDRAW SELECTED\n");
	  if (error == 1){
	   printf("ERROR: Not enough funds");
	  }

	} else if (!strcmp(input, "balance")) {

	  scanf("%d", &accountNum);
	  int tempBal = account.balance(accountNum);
	  printf("BALANCE SELECTED\n");
	  printf("Balance: %d\n", tempBal);

	} else if (!strcmp(input, "transfer")) {

	  int value, account2;
	  scanf("%d %d %d", &accountNum, &account2, &value);
	  error = account.transfer(accountNum, account2, value);
	  printf("TRANSFER SELECTED\n");
	  if (error == 1){
	  printf("ERROR: Not enough funds\n");
	  }

	} else if (!strcmp(input, "quit")) {
	  
	  break;

	} else {

	  printf("ERROR: invalid input\n");
	}
	printf("\n");
    }
*/
    return 0;
}
