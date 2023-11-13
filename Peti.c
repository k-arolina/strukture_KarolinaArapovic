#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50
#define MAX_LENGTH 1024

//5. Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna
//rezultat.Stog je potrebno realizirati preko vezane liste.

struct _stackElement;
typedef struct _stackElement* Position;
typedef struct _stackElement {
    double number;
    Position next;
} StackElement;


int calculatePostfixFromFile(Position P, char* file, double* result);
int readFile(char* file, char* buffer);
int parseStringIntoPostfix(Position P, char* buffer, double* result);
int checkStackAndExtractResult(Position P, double* result);
Position createStackElement(double number);
int push(Position P, Position newElement);
int print(Position current);
int pop(Position P, double* result);
int popAndPerformOperation(Position P, char sign, double* result);

int main() {
    StackElement head = { .number = 0, .next = NULL };
    double result = 0;

    if (calculatePostfixFromFile(&head, "postfix.txt", &result) == EXIT_SUCCESS) {
        printf("The result is: %lf\n", result);
    }

    return EXIT_SUCCESS;
}

int calculatePostfixFromFile(Position P,char* file, double* result) {
    char buffer[MAX_LENGTH] = { 0 };
    int status = 0;
    /*FILE* filePointer = NULL;
    filePointer = fopen(file, "r");
    if (!filePointer) {
        perror("Can't open file!\n");
        return NULL;
    }

    fgets(buffer, MAX_LENGTH, filePointer);
    printf("|%s|\n", buffer);
    */
    if (readFile(file, buffer) != EXIT_SUCCESS || !buffer) {
        return EXIT_FAILURE;
    }

    status = parseStringIntoPostfix(P, buffer, result);
    if (status != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
   /* fclose(filePointer);*/
    return EXIT_SUCCESS;
}

int readFile(char* file, char* buffer) {
    FILE* filePointer = NULL;
    filePointer = fopen(file, "r");
    if (!filePointer) {
        perror("Can't open file!\n");
        return NULL;
    }

    fgets(buffer, MAX_LENGTH, filePointer);
    printf("|%s|\n", buffer);

    fclose(filePointer);

    return EXIT_SUCCESS;
}

int parseStringIntoPostfix(Position P, char* buffer, double* result)
{
    char* currentBuffer = buffer;
    int status = 0;
    int numBytes = 0;
    char sign = 0;
    double number = 0.0;
    Position newStackElement = NULL;

    while (strlen(currentBuffer) > 0) {
        status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
        if (status != 1) {
            sscanf(currentBuffer, " %c %n", &sign, &numBytes);
            status = popAndPerformOperation(P, sign, result);

            if (status != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }

            number = *result;
        }

        newStackElement = createStackElement(number);
        if (!newStackElement) {
            return EXIT_FAILURE;
        }

        currentBuffer += numBytes;
        printf("|%s| <-->", currentBuffer);
        push(P, newStackElement);
    }

    return checkStackAndExtractResult(P, result);
}

int checkStackAndExtractResult(Position P, double* result) {
    int status = EXIT_SUCCESS;

    status = pop(P, result);

    if (status != EXIT_SUCCESS) {
        return status;
    }

    if (P->next) {
        system("cls"); 
        printf("Invalid postfix, please check the file!\r\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

Position createStackElement(double number)
{
    Position newElement = NULL;

    newElement = (Position)malloc(sizeof(StackElement));
    if (!newElement) {
        printf("Can't allocate memory!\n");
        return NULL;
    }

    newElement->number = number;
    newElement->next = NULL;

    return newElement;
}

int push(Position P, Position newElement) {
    newElement->next = P->next;
    P->next = newElement;

    print(P->next);

    return EXIT_SUCCESS;
}

int print(Position current) {
    
    while (current) {
        printf(" %lf", current->number);
        current = current->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int pop(Position P, double* result) {
    Position toDelete = NULL;

    toDelete = P->next;
    if (!toDelete) {
        printf("Stack is empty!\n");
        return -1;
    }

    P->next = toDelete->next;
    *result = toDelete->number;
    free(toDelete);

    return EXIT_SUCCESS;
}

int popAndPerformOperation(Position P, char sign, double* result) {
    double operand1 = 0;
    double operand2 = 0;
    int status1 = 0;
    int status2 = 0;

    status1 = pop(P, &operand1);
    if (status1 != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    status2 = pop(P, &operand2);
    if (status2 != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    switch (sign) {
    case '+':
        *result = operand2 + operand1;
        break;
    case '-':
        *result = operand2 - operand1;
        break;
    case '*':
        *result = operand2 * operand1;
        break;
    case '/':
        *result = operand2 / operand1;
        break;
    default:
        printf("Error!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}