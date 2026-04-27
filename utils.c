#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

int getSafeInt(int allowBack) {
    char buffer[20];
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) == 0) continue;
            if (allowBack && (strcmp(buffer, "0") == 0)) return -1;

            int isValid = 1;
            for (int i = 0; i < (int)strlen(buffer); i++) {
                if (buffer[i] < '0' || buffer[i] > '9') {
                    isValid = 0;
                    break;
                }
            }
            if (isValid) return atoi(buffer);
            printf("Invalid input! (Enter '0' to cancel): ");
        }
    }
}

float getSafeFloat() {
    char buffer[20];
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) == 0) continue;
            
            int dotCount = 0, isValid = 1;
            for (int i = 0; i < (int)strlen(buffer); i++) {
                if (buffer[i] == '.') dotCount++;
                else if (buffer[i] < '0' || buffer[i] > '9') { isValid = 0; break; }
            }
            if (isValid && dotCount <= 1) return atof(buffer);
            printf("Invalid marks! Try again: ");
        }
    }
}

int isValidName(char *name) {
    if (strlen(name) == 0) return 0;
    for (int i = 0; i < (int)strlen(name); i++) {
        if (!((name[i] >= 'a' && name[i] <= 'z') || 
              (name[i] >= 'A' && name[i] <= 'Z') || name[i] == ' ')) return 0;
    }
    return 1;
}

void capitalizeName(char *name) {
    if (name[0] >= 'a' && name[0] <= 'z') name[0] -= 32;
    for (int i = 0; name[i] != '\0'; i++) {
        if (name[i] == ' ' && name[i + 1] >= 'a' && name[i + 1] <= 'z') name[i + 1] -= 32;
    }
}