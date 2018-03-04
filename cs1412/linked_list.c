//
//  Lab_11
//
//  Created by Ryan Kelley on 4/19/17.
//  Copyright © 2017 Ryan Kelley. All rights reserved.
//  Section 504 Yuanlin Zhang / Pushkar Ogale
//  Uses linked list to keep track of incoming/outgoing customers
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
  char name[64];
  struct Node *next;
} *head, *tail;

typedef struct Node node;

void DisplayMenu(void);
void CallCustomer(void);
void AddCustomer(const char *customerName);

int main(void) {
  DisplayMenu();
  return 0;
}

/* Inserts new node with name customerName at end of list */
void AddCustomer(const char *customerName) {
  
  node *temp = (node*)malloc(sizeof(node));

  strcpy(temp->name, customerName);
  printf("\n\n%s was added to the list!\n\n\n", temp->name);
  
  temp->next = NULL;
  
  if (head == NULL) {
    head = temp;
    tail = temp;
    return;
  }
  
  tail->next = temp;
  tail = temp;

}

/* Removed the first node of the list */
void CallCustomer(void) {
  
    // If the address of head doesn't point anywhere
  if (head == NULL) puts("\n\nNo one is in line!\n\n");
  else {
    
    node *temp = (node*)malloc(sizeof(node));
    temp = head;
    printf("\n\n%s was removed from the list!\n\n\n", head->name);
    
    if (head == tail) {
      head = NULL;
      tail = NULL;
    } else head = head->next;

    free(temp);
  }
  
}

void DisplayMenu(void) {
  char keyPressed;
  for (;;) {
    // Print menu to the screen
    printf(
    "#######################\n"
    "# 0. Call a customer  #\n"
    "# 1. Add a customer   #\n"
    "# 2. Quit             #\n"
    "#######################\n"
    "Please type a number from 0 to 2 to select menu item:\n");
    
    keyPressed = getchar(); // Get user input (0-4)
    getchar();
    // Validate the input from the user...
    if( keyPressed == '2' ) {
      puts("\n\nExiting program!\n\n");
      return;
    } else if ( keyPressed < '0' || keyPressed > '2' ) {
      printf("\n[Err] Invalid Input... Try again.\n");
      continue; // Unknown input... we can safely loop back around
    } else {
    // Print the corresponding menu item
      switch(keyPressed) {
        case '0':
          CallCustomer();
          break;
        case '1': {
          char CustomerName[64];
          printf("Enter the name of the customer: ");
          scanf("%s", CustomerName);
          AddCustomer(CustomerName);
          getchar();
          break;
        }
        default:
          puts("[Err] An un-expected error occured.");
          exit(1);
      }
    }
  }
}
