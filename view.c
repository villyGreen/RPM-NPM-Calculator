#include "smartCalc.h"

char searchString[5000];
GtkWidget *mainLabel;
GtkWidget *window;
GtkWidget *fixed;
GtkWidget * numberButtons[12];
GtkWidget * specButtons[9];
GtkWidget * signButtons[8];
GtkWidget * equalButton;
GtkWidget * clearButton;
int point = 0;

void init(int argc, char *argv[]) {
    int startY = 260;
    int startX = 10;
    int specX = 169;
    int specY = 224;
    int signX = 350;
    int signY = 224;
    
    // MARK: - Window
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(GTK_WIDGET(window),600,270);
    gtk_window_set_title(GTK_WINDOW(window), "Smart Calc");
    
    // MARK: - Fixed
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    
    // MARK: - Numbers buttons
    createNumButtons(numberButtons);
    for (int i = 0; i < 12; i++) {
        gtk_widget_set_size_request(numberButtons[i], 30, 30);
        if (i%3 == 0) {
            startY -= 36;
            startX = 10;
        }
        setupNumberButtonsTarget(numberButtons[i]);
        setupConstraints(startX,startY,numberButtons[i],fixed);
        startX += 53;
    }
    // MARK: - functions buttons
    createFunctionButtons(specButtons);
    for (int i = 0; i < 9; i++) {
        gtk_widget_set_size_request(specButtons[i], 60, 30);
        
        if (i%3 == 0) {
            specY -= 36;
            specX = 169;
        }
        setupSpecButtonssTargets(specButtons[i]);
        setupConstraints(specX,specY,specButtons[i],fixed);
        specX += 63;
    }
    // MARK: - sign buttons
    createSignButtons(signButtons);
    for (int i = 0; i < 8; i++) {
        gtk_widget_set_size_request(signButtons[i], 30, 30);
        
        if (i%3 == 0) {
            signY -= 36;
            signX = 358;
        }
        setupSignButtonsTargets(signButtons[i]);
        setupConstraints(signX,signY,signButtons[i],fixed);
        signX += 53;
    }
    // MARK: - equalButton
    equalButton = gtk_button_new_with_label("=");
    gtk_fixed_put (GTK_FIXED (fixed), equalButton, 169, 224);
    gtk_widget_set_size_request(equalButton, 400, 30);
    g_signal_connect(G_OBJECT(equalButton), "clicked", G_CALLBACK(equalButtonClicked), NULL);
    
    // MARK: - clearButton
    clearButton = gtk_button_new_with_label("AC");
    gtk_fixed_put (GTK_FIXED (fixed), clearButton, 472, 116);
    gtk_widget_set_size_request(clearButton, 95, 30);
    g_signal_connect(G_OBJECT(clearButton), "clicked", G_CALLBACK(clearAllSearchString), NULL);
    
    // MARK: - Label
    mainLabel = gtk_label_new(" ");
    gtk_label_set_xalign (mainLabel, 0.0);
    gtk_fixed_put (GTK_FIXED (fixed), mainLabel, 20, 50);
    gtk_widget_set_size_request(mainLabel, 514, 50);
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
}


// MARK: - Create buttons
void createNumButtons(GtkWidget ** buttons) {
    char * numbers[12] = {"0","."," ","1","2","3","4","5","6","7","8","9"};
    GtkWidget * button;
    for (int i = 0;i < 12;i++) {
        button = gtk_button_new_with_label(numbers[i]);
        buttons[i] = button;
    }
}

void createFunctionButtons(GtkWidget ** buttons) {
    char * specButtons[9] = {"acos","asin","atan","cos","sin","tan","sqrt","ln","log"};
    GtkWidget * button;
    for (int i = 0;i < 9;i++) {
        button = gtk_button_new_with_label(specButtons[i]);
        buttons[i] = button;
    }
}

void createSignButtons(GtkWidget ** buttons) {
    char * sign[8] = {"(",")","+","-","*","/","^","mod"};
    GtkWidget * button;
    for (int i = 0;i < 8;i++) {
        button = gtk_button_new_with_label(sign[i]);
        buttons[i] = button;
    }
}

// MARK: - Setup Constraints
void setupConstraints(int x_anchor, int y_anchor, GtkWidget * button, GtkWidget * fixed) {
    gtk_fixed_put (GTK_FIXED (fixed), button, x_anchor, y_anchor);
}


// MARK: - Set targets for buttons
void setupNumberButtonsTarget(GtkWidget * button) {  
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(buttonNumberClicked), NULL);
}

void setupSpecButtonssTargets(GtkWidget * button) {
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(specButtonClicked), NULL);
}

void setupSignButtonsTargets(GtkWidget * button) {
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(buttonSignClicked), NULL);
}


// MARK: - Action for targets

void equalButtonClicked() {
    charactersSet set;
    set = validator(searchString, point);
    if (set.errors == IS_EMPTY_FEEL || set.errors == IS_SYNTAX_ERROR) {
        gtk_label_set_label(mainLabel, "Ошибка");
//        clearAllSearchString();
    }
}

void buttonNumberClicked(GtkWidget * button) {
    
    char * value = (gtk_button_get_label((GtkButton*)button));
    fillString(value, &point);
    updateLabel(mainLabel, searchString);
}

void specButtonClicked(GtkWidget * button) {
    char value[1000];
    char num = ' ';
    if (point != 0) {
        num = searchString[point - 1];
    }
    if ((num >= '0' && num <= '9') || num == ')') {
        value[0] = '*';
        size_t size = strlen((gtk_button_get_label((GtkButton*)button)));
        for (int i = 0;i < size;i++) {
            value[i + 1] = (gtk_button_get_label((GtkButton*)button))[i];
        }
        value[size + 1] = '(';
        value[size + 2] = '\0';
    } else {
        size_t size = strlen((gtk_button_get_label((GtkButton*)button)));
        for (int i = 0;i < size;i++) {
            value[i] = (gtk_button_get_label((GtkButton*)button))[i];
        }
        value[size ] = '(';
        value[size + 1] = '\0';
        
    }
    
    fillString(value,&point);
    updateLabel(mainLabel, searchString);
}

void buttonSignClicked(GtkWidget * button) {
    char * value = (gtk_button_get_label((GtkButton*)button));
    fillString(value, &point);
    updateLabel(mainLabel, searchString);
}

// MARK: - Work with string
void updateLabel(GtkWidget * label, char * text) {
    gtk_label_set_label((GtkLabel*)label, text);
}

void clearAllSearchString()  {
    for (int i = 0; i < point;i++) {
        searchString[i] = '\0';
    }
    point = 0;
    updateLabel(mainLabel,searchString);
}

char * fillString(char * input, int *point) {
    for (int i = 0;i < strlen(input);i++) {
        searchString[*point] = input[i];
        *point+= 1;
    }
}
