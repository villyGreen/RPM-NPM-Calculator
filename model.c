#include "smartCalc.h"

charactersSet set;
charactersSet validator(char * searhString, int point) {
    set.errors = IS_NORMAL;
    set.openBracket = 0;
    set.x = 0;
    set.closedBracket = 0;
    bool fraction = 0;
    int error = 0;
    bool onlyValues = false;
    
    if(point == 0) {
        set.errors = IS_EMPTY_FEEL;
    }
    if (searhString[0] == 'x' || searhString[0] == 'm' || searhString[0] == '+') {
        set.errors = IS_SYNTAX_ERROR;
    }
    if (searhString[point - 1] == 'x') {
        set.x = 1;
    }
    if (searhString[point - 1] == '+' || searhString[point - 1] == '-' || searhString[point - 1] == '*'
        || searhString[point] == '/' || searhString[point - 1] == '^' || searhString[point - 1] == '(')  {
        set.errors = IS_SYNTAX_ERROR;
    }
    for (int i = 0;i < point;i++) {
        onlyValues = isValue(searhString[i]);
        fraction = isFractionValue(searhString[i]);
        if (searhString[i] == ',') {
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
    if (point >= 1) {
        if ((searhString[0] == '/' || searhString[0] == '*' || searhString[0] == '^' || searhString[0] == ')')) {
            set.errors = IS_SYNTAX_ERROR;
        }
        int pointer = 1;
        for (int i = point; i > 0; i--) {
            if ((searhString[point - i] == '+' ||  searhString[point - i] == '-' || searhString[point - i] == '*' || searhString[point - i] == '/' || searhString[point - i] == '^' || searhString[point - i] == ',') && ((searhString[pointer] == '+' ||  searhString[pointer] == '-' || searhString[pointer] == '*' || searhString[pointer] == '/' || searhString[pointer] == '^' || searhString[pointer] == ','))) {
                set.errors = IS_SYNTAX_ERROR;
                break;
            }
            pointer++;
        }
        pointer = 1;
        for (int i = point; i > 0; i--) {
            if ((searhString[point - i] == ',') && (searhString[pointer] == '(' || searhString[pointer] == ')')) {
                set.errors = IS_SYNTAX_ERROR;
                break;
            }
            pointer++;
        }
        if (searhString[point - 1] == ',') {
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
            if ( searhString[point - i] == '(' && ((searhString[pointer] == '+'  || searhString[pointer] == '*' || searhString[pointer] == '/' || searhString[pointer] == '^' || searhString[pointer] == ','))) {
                set.errors = IS_SYNTAX_ERROR;
                break;
            }
            pointer++;
        }
        pointer = 1;
        for (int i = point; i > 0; i--) {
            if (searhString[point - i] == ',') {
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

double calculator (char * searchString, int point, charactersSet * set, double x_coordinate) {
    
    Stack_t stack_n;
    stack_n.size = 0;
    Stack_t stack_o;
    stack_o.size = 0;
    value_type item;
    char ch;
    bool res;
    char  value[500];
    int pointer = 0;
    double value_d;
    int matchValue = 0;
    int flag = 1;
    
    for (int i = 0; i < point; i++) {
        if (searchString[i] == 'x') {
            item.type = '0';
            item.value = x_coordinate;
            push(&stack_n, item);
        }
        while ((searchString[i] >= '0' && searchString[i] <= '9' || searchString[i] == '-' && flag == 1) || searchString[i] == ',') {
            ch = searchString[i];
            //                       if (ch == ',') {
            //                           ch = '.';
            //                       }
            value[pointer] = ch;
            flag = 0;
            matchValue = 1;
            pointer++;
            i++;
        }
        if (matchValue) {
            value[pointer + 1] = '\0';
            
            sscanf(value,"%lf",&value_d);
            item.type = '0';
            item.value = value_d;
            push(&stack_n, item);
            for (int i = 0; i < pointer;i++) {
                value[i] = '\0';
            }
            pointer = 0;
        }
        if (searchString[i] == 's' || searchString[i] == 'c' || searchString[i] == 'a' || searchString[i] == 'l' || searchString[i] == 't') {
            char func[4];
            size_t lenght = 0;
            for (int j = 0; j < 4;j++) {
                if (searchString[i] >= 97 && searchString[i] <= 122) {
                    func[j] = searchString[i];
                    lenght+=1;
                    i++;
                } else {
                    break;
                }
            }
            if(lenght == 3) {
                // sin
                if (func[0] == 's' && func[1] == 'i' && func[2] == 'n') {
                    item.type = 's';
                    item.value = 0;
                    push(&stack_o, item);
                }
                // cos
                if (func[0] == 'c' && func[1] == 'o' && func[2] == 's') {
                    item.type = 'c';
                    item.value = 0;
                    push(&stack_o, item);
                }
                // tan
                if (func[0] == 't' && func[1] == 'a' && func[2] == 'n') {
                    item.type = 't';
                    item.value = 0;
                    push(&stack_o, item);
                }
                // log
                if (func[0] == 'l' && func[1] == 'o' && func[2] == 'g') {
                    item.type = 'l';
                    item.value = 0;
                    push(&stack_o, item);
                }
            }
            if (lenght == 2) {
                // ln
                if (func[0] == 'l' && func[1] == 'n') {
                    item.type = 'L';
                    item.value = 0;
                    push(&stack_o, item);
                }
            }
            if (lenght == 4) {
                // acos
                if (func[0] == 'a' && func[1] == 'c' && func[2] == 'o' && func[3] == 's') {
                    item.type = 'C';
                    item.value = 0;
                    push(&stack_o, item);
                }
                // asin
                if (func[0] == 'a' && func[1] == 's' && func[2] == 'i' && func[3] == 'n') {
                    item.type = 'S';
                    item.value = 0;
                    push(&stack_o, item);
                }
                // atan
                if (func[0] == 'a' && func[1] == 't' && func[2] == 'a' && func[3] == 'n') {
                    item.type = 'T';
                    item.value = 0;
                    push(&stack_o, item);
                }
                // sqrt
                if (func[0] == 's' && func[1] == 'q' && func[2] == 'r' && func[3] == 't') {
                    item.type = 'Q';
                    item.value = 0;
                    push(&stack_o, item);
                }
            }
        }
        if (searchString[i] == '+' || searchString[i] == '-' && flag == 0 || searchString[i] == '*' || searchString[i] == '/' || searchString[i] == '^' || searchString[i] == 'm') {
            if (sizeOfStack(&stack_o) == 0) {
                ch = searchString[i];
                item.type = ch;
                item.value = 0;
                push(&stack_o, item);
            } else if (sizeOfStack(&stack_o) != 0 && getPriority(searchString[i]) > getPriority(peek(&stack_o).type)) {
                ch = searchString[i];
                item.type = ch;
                item.value = 0;
                push(&stack_o, item);
            } else {
                mathStackElements(&stack_n,&stack_o,item,set);
                ch = searchString[i];
                item.type = ch;
                item.value = 0;
                push(&stack_o, item);
            }
            if (searchString[i] == 'm') {
                i+=2;
            }
        }
        if (searchString[i] == '(') {
            ch = searchString[i];
            item.type = ch;
            item.value = 0;
            push(&stack_o, item);
        }
        if (searchString[i] == ')') {
            while (peek(&stack_o).type != '(') {
                bool res = mathStackElements(&stack_n,&stack_o,item,set);
                if (res == true) {
                    break;
                }
            }
            pop(&stack_o);
        }
        matchValue = 0;
    }
    while (sizeOfStack(&stack_o) != 0) {
        res =  mathStackElements(&stack_n,&stack_o,item,set);
        if (res == true) {
            break;
        }
    }
    //    g_print("resultat  =  %lf\n", peek(&stack_n).value);
    return  !res ? peek(&stack_n).value : 0.0;
}

bool mathStackElements(Stack_t *stack_n, Stack_t *stack_o,value_type  item,charactersSet * set) {
    double value_a,value_b,value_res;
    bool error = false;
    value_a = peek(stack_n).value;
    pop(stack_n);
    switch (peek(stack_o).type) {
        case '+':
            if (sizeOfStack(stack_n) == 0) {
                error = true;
                set->errors = IS_ERROR_VALUE;
                break;
            }
            value_b = peek(stack_n).value;
            value_res = value_b + value_a;
            item.type = '0';
            item.value = value_res;
            pop(stack_n);
            push(stack_n, item);
            pop(stack_o);
            break;
        case '-':
            if (sizeOfStack(stack_n) == 0) {
                error = true;
                set->errors = IS_ERROR_VALUE;
                break;
            }
            value_b = peek(stack_n).value;
            value_res = value_b - value_a;
            item.type = '0';
            item.value = value_res;
            pop(stack_n);
            push(stack_n, item);
            pop(stack_o);
            break;
        case '*':
            if (sizeOfStack(stack_n) == 0) {
                error = true;
                set->errors = IS_ERROR_VALUE;
                break;
            }
            value_b = peek(stack_n).value;
            value_res = value_b * value_a;
            item.type = '0';
            item.value = value_res;
            pop(stack_n);
            push(stack_n, item);
            pop(stack_o);
            break;
        case '/':
            if (sizeOfStack(stack_n) == 0) {
                error = true;
                set->errors = IS_ERROR_VALUE;
                break;
            }
            value_b = peek(stack_n).value;
            if (value_a != 0) {
                value_res = value_b / value_a;
                item.type = '0';
                item.value = value_res;
                pop(stack_n);
                push(stack_n, item);
                pop(stack_o);
            } else {
                error = true;
                set->errors = IS_ERROR_VALUE;
            }
            break;
        case 's':
            value_res = sin(value_a);
            item.type = '0';
            item.value = value_res;
            push(stack_n, item);
            pop(stack_o);
            break;
        case 'c':
            value_res = Cos(value_a);
            item.type = '0';
            item.value = value_res;
            push(stack_n, item);
            pop(stack_o);
            break;
        case 't':
            if (Cos(value_a) == 0) {
                error = true;
                set->errors = IS_ERROR_VALUE;
                break;
            }
            value_res = tan(value_a);
            item.type = '0';
            item.value = value_res;
            push(stack_n, item);
            pop(stack_o);
            break;
        case 'l':
            value_res = log10(value_a);
            item.type = '0';
            item.value = value_res;
            push(stack_n, item);
            pop(stack_o);
            break;
        case 'm':
            if (sizeOfStack(stack_n) == 0) {
                error = true;
                set->errors = IS_ERROR_VALUE;
                break;
            }
            value_b = peek(stack_n).value;
            value_res = fmod(value_b,value_a);
            item.type = '0';
            item.value = value_res;
            pop(stack_n);
            push(stack_n, item);
            pop(stack_o);
            break;
        case 'L':
            value_res = log(value_a);
            item.type = '0';
            item.value = value_res;
            push(stack_n, item);
            pop(stack_o);
            break;
        case 'C':
            if (value_a >= -1 && value_a <= 1) {
                value_res = acos(value_a);
                item.type = '0';
                item.value = value_res;
                push(stack_n, item);
                pop(stack_o);
            } else {
                error = true;
                set->errors = IS_ERROR_VALUE;
            }
            break;
        case 'S':
            if (value_a >= -1 && value_a <= 1) {
                value_res = asin(value_a);
                item.type = '0';
                item.value = value_res;
                push(stack_n, item);
                pop(stack_o);
            } else {
                error = true;
                set->errors = IS_ERROR_VALUE;
            }
            break;
        case 'T':
            value_res = atan(value_a);
            item.type = '0';
            item.value = value_res;
            push(stack_n, item);
            pop(stack_o);
            
            break;
        case 'Q':
            value_res = sqrt(value_a);
            item.type = '0';
            item.value = value_res;
            push(stack_n, item);
            pop(stack_o);
            break;
        case '^':
            if (sizeOfStack(stack_n) == 0) {
                error = true;
                set->errors = IS_ERROR_VALUE;
                break;
            }
            value_b = peek(stack_n).value;
            if (value_a != 0) {
                value_res = pow(value_b,value_a);
                item.type = '0';
                item.value = value_res;
                pop(stack_n);
                push(stack_n, item);
                pop(stack_o);
            } else {
                error = true;
                set->errors = IS_ERROR_VALUE;
            }
            break;
        default:
            break;
    }
    return error;
}

int getPriority(char ch) {
    int priority = 0;
    if (ch == 'c' || ch == 's' || ch == 't' || ch == 'l' || ch == 'S' || ch == 'C' || ch == 'Q' || ch == 'T' || ch == 'L' || ch == 'm') {
        priority = 4;
    }
    if (ch == '+' || ch == '-') {
        priority = 1;
    }
    if (ch == '*' || ch == '/') {
        priority = 2;
    }
    if (ch == '^' ) {
        priority = 3;
    }
    return priority;
}

void push(Stack_t *stack, value_type value) {
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

double Sin(double x) {
    return (round(sin(x) * 10000000) / 10000000);
}

double Cos(double x) {
    return (round(cos(x) * 10000000) / 10000000);
}
