#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void handleInsert(LinkedList*);
void handleRemove(LinkedList*);
void handleCurrentCal(LinkedList*, int);
void handleVoltage(LinkedList*, int);
void handlePrint(LinkedList*);
void handleQuit(LinkedList*);

int main(void) {
    LinkedList circuit;
    initList(&circuit);
    char command = '\0';
    printf("Welcome to our circuit simulator\n");
    // Enter the source voltage!
    printf("What is the source of the voltage?\n");
    int voltage;
    readInputNumber(&voltage);
   
    while (command != 'Q') {
        command = getCommand();
    
        switch (command) {
        case 'I':
            handleInsert(&circuit);
            break;
        case 'R':
            handleRemove(&circuit);
            break;
        case 'C':
            handleCurrentCal(&circuit, voltage);
            break;
        case 'V':
            handleVoltage(&circuit, voltage);
            break;
        case 'P':
            handlePrint(&circuit);
            break;
        case 'Q':
            handleQuit(&circuit);
            break;
        }
    }
     return 0;
}

void handleInsert(LinkedList* circuit) {
    int resistance = 0;
    printf("What's the value of the resistor: ");
    readInputNumber(&resistance);
    printf("What's the label of the resistor: ");
    char labelName[STRING_MAX];
    readInputString(labelName, STRING_MAX);

    Node *newNode = (Node*)malloc(sizeof(Node));

    if (newNode != NULL) { // assiging the values and the name of the respective node
        newNode -> value = resistance;
        newNode -> next = NULL;
        strcpy(newNode -> name, labelName); 

    }

    Node *temp = circuit -> head; // this might be problematic
    Node *previous = NULL;

    if (circuit -> head == NULL) {
        circuit -> head = newNode;
    }

    else {
        while ( (temp) != NULL && (strcmp((temp)-> name, labelName) <= 0) ) {
            if ((temp) != NULL && (strcmp((temp)-> name, labelName) == 0) ) {
                printf("A resistor with %s label already exists.\n", labelName);
                return;
            }
            previous = temp;
            temp = temp -> next;
        }


        if (previous != NULL) {
            previous -> next = newNode;
            newNode -> next = temp;
        }
        else {
            newNode -> next = circuit -> head;
            circuit -> head = newNode;
        }
    }

}

void handleRemove(LinkedList* circuit) {
    Node *current = circuit -> head; // idk if this first line is right LMAOOOOO HELP CLAIRE LOLLL
    Node *previous = NULL;

    char labelName[STRING_MAX];
    printf("What's the label of the resistor you want to remove: ");
    readInputString(labelName, STRING_MAX);

    if(circuit -> head == NULL) {
        return;
    }
    
    while(current != NULL && strcmp(current -> name, labelName) != 0) {
        previous = current;
        current = current -> next;
    }

    if (current == NULL) { //checks to see if there is actually a node to remove
        printf("The resistor with %s label does not exist. \n", labelName);
        return;
    }

    if (previous == NULL) { //this is the case where the first node si removed and there is no previous node
        circuit -> head = current -> next;
    }
    else {
        previous -> next = current -> next;
    }

    free(current);

}

void handleCurrentCal(LinkedList* circuit, int voltage) {  // first calc the total resistance and then volatage/(the total resistance)
    double totResistance = 0;
    double calCurrent = 0;

    Node *current = circuit -> head; 

    while (current != NULL) {
        totResistance += current -> value;
        current = current -> next;
    }

    calCurrent = (double) voltage / totResistance;
    printf("The current in the circuit is %.6lfA\n", calCurrent);
    

}

void handleVoltage(LinkedList* circuit, int voltage) {
    double totResistance = 0;
    double calCurrent = 0;
    double calVoltage = 0;
    

    char labelName[STRING_MAX];
    printf("What's the label of the resistor you want to find the voltage across: ");
    readInputString(labelName, STRING_MAX);

    Node *current = circuit -> head; 
    Node *nameResistor = NULL;

    while (current != NULL) {
        if (strcmp(current -> name, labelName) == 0) {
            nameResistor = current; 
        }
        totResistance += current -> value;
        current = current -> next;
    }
    if (nameResistor == NULL) {
        printf("The resistor with %s label does not exist. \n", labelName);
        return;
    }
    else {
        calCurrent = (double) voltage / totResistance;
        calVoltage = calCurrent * (nameResistor -> value);
        printf("Voltage across resistor is %.6lfV\n", calVoltage);
    }


}

void handlePrint(LinkedList* circuit) {
    Node *current = circuit -> head;
    while(current != NULL) {
        printf("%s  %d Ohms\n", current -> name, current -> value);
        current = current -> next; 
    }

}

void handleQuit(LinkedList* circuit) {
    printf("Removing all resistors in the circuit... \n");
    handlePrint(circuit);

    Node *current = circuit -> head;
    Node *temp = NULL;

    while (current != NULL) {
       temp = current;
       current = current -> next;
       free(temp); 
    }

    circuit-> head = NULL;

}
