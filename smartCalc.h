#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <stdio.h>
#include <cairo.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <gtk/gtk.h>
#include <string.h>

#define NMAX 100

#define STACK_MAX_SIZE 1000
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101


typedef enum {
    IS_NORMAL = 0,
    IS_EMPTY_FEEL = 1,
    IS_SYNTAX_ERROR = 2,
    IS_ERROR_VALUE = 3
} error_List;

typedef struct {
    int openBracket;
    int closedBracket;
    bool signReverse;
    int dot;
    int x;
    error_List errors;
} charactersSet;

typedef struct {
    char type;
    double value;
} value_type;

typedef struct Stack_tag {
    value_type data[STACK_MAX_SIZE];
    size_t size;
} Stack_t;


// Model
charactersSet validator(char * searhString, int point);
double calculator (char * searchString, int point, charactersSet * set);
bool isValue(char  ch);
bool isFractionValue(char ch);
void push(Stack_t *stack, value_type value);
value_type pop(Stack_t *stack);
value_type peek(const Stack_t *stack);
size_t stackIsEmpty(const Stack_t *stack);
size_t sizeOfStack(const Stack_t * stack);
bool mathStackElements(Stack_t *stack_n, Stack_t *stack_o,value_type  item,charactersSet * set);
int getPriority(char ch);

// View
void init(int argc, char *argv[]);
void createNumButtons(GtkWidget ** buttons);
void setupConstraints(int x_anchor, int y_anchor, GtkWidget * button, GtkWidget * fixed);
void createFunctionButtons(GtkWidget ** buttons);
void createSignButtons(GtkWidget ** buttons);
char * fillSearchString(char ch);
void setupNumberButtonsTarget(GtkWidget * button);
void buttonNumberClicked(GtkWidget * button);
void updateLabel(GtkWidget * label, char * text);
void clearAllSearchString();
void fillString(const char * input, int *point);
void setupSpecButtonssTargets(GtkWidget * button);
void setupSignButtonsTargets(GtkWidget * button);
void specButtonClicked(GtkWidget * button);
void buttonSignClicked(GtkWidget * button);
void equalButtonClicked();
void setGraph(GtkWidget * button);
void myCSS(void);
void drawGraph();
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data);
    static void do_drawing(cairo_t *cr);

#endif  // SRC_S21_SMARTCALC_H_
