#include "smartCalc.h"

charactersSet set;

charactersSet validator(char * searhString, int point) {
    set.errors = IS_NORMAL;
    set.openBracket = 0;
    set.closedBracket = 0;
    int error = 0;
    if(point == 0) {
        set.errors = IS_EMPTY_FEEL;
    }
    if (point >= 2) {
        int pointer = 1;
        for (int i = point; i > 0; i--) {
            
            if ((searhString[point - i] == '+' ||  searhString[point - i] == '-' || searhString[point - i] == '*' || searhString[point - i] == '/' || searhString[point - i] == '^' || searhString[point - i] == '.') && ((searhString[pointer] == '+' ||  searhString[pointer] == '-' || searhString[pointer] == '*' || searhString[pointer] == '/' || searhString[pointer] == '^' || searhString[pointer] == '.'))) {
                set.errors = IS_SYNTAX_ERROR;
                break;
            }
            pointer++;
        }
        pointer = 1;
        for (int i = point; i > 0; i--) {
            if ((searhString[point - i] == '.') && (searhString[pointer] == '(' || searhString[pointer] == ')')) {
                set.errors = IS_SYNTAX_ERROR;
                break;
            }
            pointer++;
        }
        if (searhString[point - 1] == '.') {
            set.errors = IS_SYNTAX_ERROR;
        }
        
        for (int i = 0; i < point; i++) {
            if (searhString[i] == '(') {
                set.openBracket += 1;
            }
            if (searhString[i] == ')') {
                set.closedBracket += 1;
            }
        }
        if (set.openBracket != set.closedBracket) {
            set.errors = IS_SYNTAX_ERROR;
        }
        pointer = 1;
        for (int i = point; i > 0; i--) {
            if (searhString[point - i] == '(' && searhString[pointer] == ')') {
                set.errors = IS_SYNTAX_ERROR;
            }
            pointer++;
        }
        pointer = 1;
        for (int i = point; i > 0; i--) {
            if ( searhString[point - i] == '(' && ((searhString[pointer] == '+' ||  searhString[pointer] == '-' || searhString[pointer] == '*' || searhString[pointer] == '/' || searhString[pointer] == '^' || searhString[pointer] == '.'))) {
                set.errors = IS_SYNTAX_ERROR;
                break;
            }
            pointer++;
        }
    } else {
        set.errors = IS_SYNTAX_ERROR;
    }
    g_print("error  =  %d\n",set.errors);
    return set;
} 
