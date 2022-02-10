#include "smartCalc.h"

charactersSet set;

charactersSet validator(char * searhString, int point) {
    set.errors = IS_NORMAL;
    set.openBracket = 0;
    set.closedBracket = 0;
    bool fraction = 0;
    int error = 0;
    bool onlyValues = false;
    if(point == 0) {
        set.errors = IS_EMPTY_FEEL;
    }
    if (searhString[point - 1] == '+' || searhString[point - 1] == '-' || searhString[point - 1] == '*'
     || searhString[point] == '/' || searhString[point - 1] == '^' || searhString[point - 1] == '(')  {
         set.errors = IS_SYNTAX_ERROR;
     } 
    for (int i = 0;i < point;i++) {
        onlyValues = isValue(searhString[i]);
        fraction = isFractionValue(searhString[i]);
        if (searhString[i] == '.') {
        }
        if (!onlyValues) {
            break;
        }
    }
    if (onlyValues) {
        set.errors = IS_SYNTAX_ERROR;
    }

    if (fraction) {
        set.errors = IS_SYNTAX_ERROR;
    }
    if (point >= 2) {
        if ((searhString[0] == '/' || searhString[0] == '*' || searhString[0] == '^' || searhString[0] == ')')) {
            set.errors = IS_SYNTAX_ERROR;
        }
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
        pointer = 1;
        for (int i = point; i > 0; i--) {
            if (searhString[point - i] == '.') {
                if (point - i == 0) {
                    set.errors = IS_SYNTAX_ERROR;
                    break;
                }
                if (isValue(searhString[((point - i) - 1)]) && isValue(searhString[pointer])) {
                } else {
                    set.errors = IS_SYNTAX_ERROR;
                    break;
                }
            }
            pointer++;
        }
    } else {
        set.errors = IS_SYNTAX_ERROR;
    }
    return set;
}

bool isValue(char  ch) {
    bool isValue = false;
    if (ch >= 48 && ch <= 57 ) {
        isValue = true;
    }
    return isValue;
}

bool isFractionValue(char ch) {
    bool isValue = false;
    if ((ch >= 48 && ch <= 57) || ch == 46) {
        isValue = true;
    }
    return isValue;
}

double calculator (char * searchString, int point, charactersSet set) {

/*
    PRIOROTY:
    1 - -+
    2 - /*
    3 func ^


621 + ( 100 * 20 / 1 * 2 - 6) * 5

5
3994       
            *     
        621 +

12  
234 *     _________
*/

return 0.0;
}