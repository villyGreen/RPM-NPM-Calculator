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
    
    Stack_t stack_n;
    Stack_t Stack_o;
    value_type item;
    char ch;
    char  value[500];
    int pointer = 0;
    for (int i = 0; i < point; i++) {
        if (searchString[i] >= '0' && searchString[i] <= '9') {
            value[pointer] = searchString[i];
            pointer++;
        }
        if (searchString[i] == '+' || searchString[i] == '-' || searchString[i] == '*' || searchString[i] == '/' || ) {
            ch = searchString[i];
        }
    }
    
    double value_d = atof(value);
    item.type = '0';
    item.value = value_d;
    g_print("%f\n",value_d);
    
    return 0.0;
}

void push(Stack_t *stack, const value_type value) {
    if (stack->size >= STACK_MAX_SIZE) {
        exit(STACK_OVERFLOW);
    }
    stack->data[stack->size] = value;
    stack->size++;
}

value_type pop(Stack_t *stack) {
    if (stack->size == 0) {
        exit(STACK_UNDERFLOW);
    }
    stack->size--;
    return stack->data[stack->size];
}

value_type peek(const Stack_t *stack) {
    if (stack->size <= 0) {
        exit(STACK_UNDERFLOW);
    }
    return stack->data[stack->size - 1];
}
size_t stackIsEmpty(const Stack_t *stack) {
    return stack->size == 0 ? 1 : 0;
}

size_t sizeOfStack(const Stack_t * stack) {
    return stack->size;
}
