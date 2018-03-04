//
//  FinalProject.c
//  Final Project (Craps Game)
//
//  Created by Ryan Kelley on 4/13/17.
//  Last Modified on 5/3/17.
//  Copyright © 2017 Ryan Kelley. All rights reserved.
//  Lets user play a game of craps with multiple menu features.
//
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#define FILE_NAME "players.txt"
#define MAX_PLAYERS 10
 
/* Player structure to store player info */
typedef struct {
  char name[64];
  int balance;
  int gain;
} Player;
 
/* Functions */
int LoadPlayerData(Player *players);
void PushPlayerData(Player *players, int *totalPlayers);
void PrintPlayerData(Player *players, int *totalPlayers);
int GetPlayerIndex(Player *players, int  *totalPlayers);
void TopBalance(Player *players, int *totalPlayers);
void PrintTopFive(Player *players, int *totalPlayers, int type);
void HandleMenu(Player *players, int *totalPlayers);
void PlayGame(Player *players, int *totalPlayers);
void sSort(Player *players, int type);
 
 
int main(void) {
 
  Player players[10];
  int totalPlayers;
 
  /* Load player data from players.txt */
  totalPlayers = LoadPlayerData(players);
  printf("Loaded %d players\n", totalPlayers);
 
  /* Display and process menu choice to user */
  HandleMenu(players, &totalPlayers);
 
  return 0;
}
 
/* Initiates the game */
void PlayGame(Player *players, int *totalPlayers) {
  int playerIndex = GetPlayerIndex(players, totalPlayers);
  getchar();
  srand(time(NULL));
  for (;;) {
    /* Get initial dice roll from user */
    printf("\nPress any key to roll the dice.\n");
    getchar();
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    int diceSum = dice1 + dice2;
    printf("You rolled %d and %d for a total of %d.\n", dice1, dice2, diceSum);
   
    switch(diceSum) {
      /* If the user won */
      case 7:
      case 11:
        players[playerIndex].balance += 10;
        players[playerIndex].gain += 10;
        printf("You win the game. Your current balance is %d.\n", players[playerIndex].balance);
        break;
      /* If the user lost */
      case 2:
      case 3:
      case 12:
        players[playerIndex].balance -= 1;
        players[playerIndex].gain -= 1;
        printf("The house wins. Your current balance is %d.\n", players[playerIndex].balance);
        break;
      /* User didn't win or lose */
      case 4:
      case 5:
      case 6:
      case 8:
      case 9:
      case 10: {
        int point = diceSum;
        for (;;) {
         
 
          printf("Press enter to roll the dice.\n");
          getchar();
          dice1 = rand() % 6 + 1;
          dice2 = rand() % 6 + 1;
          diceSum = dice1 + dice2;
          printf("You rolled %d and %d for a total of %d.\n", dice1, dice2, diceSum);
         
          /* The user lost */
          if (diceSum == 7) {
            players[playerIndex].balance -= 1;
            players[playerIndex].gain -= 1;
            printf("The house wins. "
                   "Your current balance is %d.\n", players[playerIndex].balance);
            break;
         
          /* The user won */
          } else if (diceSum == point) {
            players[playerIndex].balance += 10;
            players[playerIndex].gain += 10;
            printf("You win the game. Your current balance is %d.\n", players[playerIndex].balance);
            break;
          }
        }
        break;
      }
    }
   
    printf("Would you like to play again (y/n)? ");
    char again = getchar(); getchar();
   
    /* Continue game if yes */
    if (again == 'y') continue;
    else break;
 
  }
 
  HandleMenu(players, totalPlayers);
 
}
 
/* Loads data from players.txt into *p */
int LoadPlayerData(Player *players) {
  FILE *fp = fopen(FILE_NAME, "r");
  int playerIndex = 0;
 
  for (;;) {
   
    // Scan contents from players.txt into *p
    if (fscanf(fp, "%s\t%d\t%d", players[playerIndex].name, &players[playerIndex].balance, &players[playerIndex].gain) != 3) {
      if (feof(fp)) {
        fclose(fp);
        break;
      }
    }
    playerIndex++;
  }
 
  fclose(fp);
  return playerIndex;
}
 
/* Writes data from players into players.txt */
void PushPlayerData(Player *players, int *totalPlayers) {
  FILE *fp = fopen(FILE_NAME, "w+b");
 
  // Write contents of players into players.txt
  for (int playerIndex = 0; playerIndex < *totalPlayers; playerIndex++) {
   
    fprintf(fp, "%s\t%d\t%d\r\n", players[playerIndex].name,
            players[playerIndex].balance, players[playerIndex].gain);
 
  }
 
  fclose(fp);
 
}
 
/* Prints top 5 players by given type */
void PrintTopFive(Player *players, int *totalPlayers, int type) {
 
  /* Sort players by type */
  sSort(players, type);
 
  if (type == 0) {
   
    printf("__________ Top 5 By Balance _________\n");
   
    /* Print from end of array to 5 from end */
    for (int i = *totalPlayers - 1; i >= *totalPlayers - 5; i--) {
     
      printf("%s\t%d\n", players[i].name, players[i].balance);
   
    }
  } else {
   
    printf("\n___________ Top 5 By Gain ___________\n\n");
   
    for (int j = *totalPlayers - 1; j >= *totalPlayers - 5; j--) {
     
      printf("%s\t%d\n", players[j].name, players[j].gain);
   
    }
 
  }
  
  printf("_____________________________________\n\n");
 
}
 
/* Selection sort */
void sSort(Player *players, int type){
  int min, indexA, indexB;
 
  for( indexA = 0; indexA < MAX_PLAYERS; indexA++){
   
    min = indexA;
   
    for(indexB = indexA+1; indexB < MAX_PLAYERS; indexB++){
     
      /* Check type to sort by */
      if (type == 0) {
       
       
        if(players[indexB].balance < players[min].balance)
          min = indexB;
     
      }
     
      else {
       
        if(players[indexB].gain < players[min].gain) {
         
          min = indexB;
       
        }
     
      }
    }
   
    // Swap players[indexA] and players[min] */
    Player temp = players[indexA];
    players[indexA] = players[min];
    players[min] = temp;
 
  }
}
 
/* Prints the contents of players.txt */
void PrintPlayerData(Player *players, int *totalPlayers) {
 
  /* Sort players by balance */
  sSort(players, 0);
 
  printf("\nPlayer Name\tBalance\tGain\n"
         "____________________________\n");
 
 
  for (int playerIndex = 0; playerIndex < *totalPlayers; playerIndex++) {
   
    printf("%s\t\t%d\t%d\n", players[playerIndex].name,
           players[playerIndex].balance, players[playerIndex].gain);
 
  }
 
  printf("___________________________\n\n");
 
}
 
/* Gets the index in players such that players[index].name is that name */
int GetPlayerIndex(Player *players, int *totalPlayers) {
 
  char playerName[64];
 
  for(;;) {
   
    printf("Enter your name: ");
    scanf("%s", playerName);
   
    for (int playerIndex = 0; playerIndex < *totalPlayers; playerIndex++) {
     
      if (strcmp(playerName, players[playerIndex].name) == 0) {
       
        return playerIndex;
     
      }
   
    }
   
    printf("The name \"%s\" was not found, please enter a name from the list below.\n\n", playerName);
   
    for (int knownPlayer = 0; knownPlayer < *totalPlayers; knownPlayer++) {
     
      printf("%s\n", players[knownPlayer].name);
   
    }
   
    printf("\n");
 
  }
}
 
/* Prompts user for name and sets their balance to entered balance */
void TopBalance(Player *players, int *totalPlayers) {
  int bal, playerIndex;
  playerIndex = GetPlayerIndex(players, totalPlayers);
  printf("Enter the balance: ");
  scanf("%d", &bal); getchar();
  players[playerIndex].balance += bal;
  printf("Balance for %s updated to %d!\n", players[playerIndex].name, players[playerIndex].balance);
}
 
/* Displays the game menu, then executes function based on input */
void HandleMenu(Player *players, int *totalPlayers) {
  char keyPressed;
  for (;;) {
    /* Print menu to the screen */
    printf(
    "\n############# Craps Game Menu ############\n"
    "# 0) Top up your balance                 #\n"
    "# 1) Play Game                           #\n"
    "# 2) Top 5 Players by Balance            #\n"
    "# 3) Top 5 Winners by Gain               #\n"
    "# 4) Show Player Information             #\n"
    "# 5) Exit                                #\n"
    "##########################################\n"
    "Please type a number from 0 to 5 to select menu item:\n"
    );
 
    keyPressed = getchar(); getchar(); // Get user input (0-5)
 
    // Validate the input from the user...
    if( keyPressed == '5' ) {
     
      PushPlayerData(players, totalPlayers);
      exit(1);
   
    } else if ( keyPressed < '0' || keyPressed > '5' ) {
     
      printf("\n[Err] Invalid Input... Try again.\n");
      continue; // Unknown input... we can safely loop back around
   
    } else {
    /* Do appropriate action */
      switch(keyPressed) {
        case '0': {
          TopBalance(players, totalPlayers);
          break;
        }
        case '1':
          PlayGame(players, totalPlayers);
          break;
        case '2':
          PrintTopFive(players, totalPlayers, 0);
          break;
        case '3':
          PrintTopFive(players, totalPlayers, 1);
          break;
        case '4':
          PrintPlayerData(players, totalPlayers);
          break;
        default:
          puts("[Err] An un-expected error occured.");
          exit(1);
      }
    }
 
    printf("Press enter to go back to the menu...");
    getchar();
 
  }
}
