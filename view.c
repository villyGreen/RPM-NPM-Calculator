#include "smartCalc.h"

char searchString[5000];
GtkWidget *mainLabel;
GtkWidget *window;
GtkWidget *fixed;
GtkWidget *darea;
GtkWidget * fix;
GtkWidget * numberButtons[12];
GtkWidget * specButtons[10];
GtkWidget * signButtons[7];
GtkWidget * equalButton;
GtkWidget * graphButton;
GtkWidget * clearButton;
GtkWidget * modButton;
GtkWidget *windowGraph;
int point = 0;

struct {
    int count;
    double coordx[1000];
    double coordy[1000];
} glob;

void init(int argc, char *argv[]) {
    // 11,104492391
    // 1,4474840516
    int startY = 260;
    int startX = 10;
    int specX = 169;
    int specY = 224;
    int signX = 350;
    int signY = 224;
    
    // MARK: - Window
    gtk_init(&argc, &argv);
    myCSS();
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(GTK_WIDGET(window),580,270);
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
        if (i == 2) {
            g_signal_connect(G_OBJECT(numberButtons[2]), "clicked", G_CALLBACK(xButtonPressed), NULL);
            setupConstraints(startX,startY,numberButtons[i],fixed);
        } else {
            setupNumberButtonsTarget(numberButtons[i]);
            setupConstraints(startX,startY,numberButtons[i],fixed);
            startX += 53;
        }
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
    for (int i = 0; i < 7; i++) {
        gtk_widget_set_size_request(signButtons[i], 30, 30);
        
        if (i%3 == 0) {
            signY -= 36;
            signX = 358;
        }
        setupSignButtonsTargets(signButtons[i]);
        setupConstraints(signX,signY,signButtons[i],fixed);
        signX += 53;
    }
    modButton = gtk_button_new_with_label("mod");
    gtk_fixed_put (GTK_FIXED (fixed), modButton, 411, 116);
    gtk_widget_set_size_request(modButton, 60, 30);
    g_signal_connect(G_OBJECT(modButton), "clicked", G_CALLBACK(modButtonClicked), NULL);
    
    
    // MARK: - equalButton
    equalButton = gtk_button_new_with_label("=");
    gtk_fixed_put (GTK_FIXED (fixed), equalButton, 169, 224);
    gtk_widget_set_size_request(equalButton, 400, 30);
    g_signal_connect(G_OBJECT(equalButton), "clicked", G_CALLBACK(equalButtonClicked), NULL);
    
    // MARK: - clearButton
    clearButton = gtk_button_new_with_label("AC");
    gtk_fixed_put (GTK_FIXED (fixed), clearButton, 474, 116);
    gtk_widget_set_size_request(clearButton, 95, 30);
    g_signal_connect(G_OBJECT(clearButton), "clicked", G_CALLBACK(clearAllSearchString), NULL);
    gtk_widget_set_name(clearButton, "clearButton");
    
    
    // MARK: - graphButton
    graphButton = gtk_button_new_with_label("f(x)");
    gtk_fixed_put (GTK_FIXED (fixed), graphButton, 516, 152);
    gtk_widget_set_size_request(graphButton, 53, 70);
    g_signal_connect(G_OBJECT(graphButton), "clicked", G_CALLBACK(setGraph), NULL);
    gtk_widget_set_name(graphButton, "graphButton");
    
    // MARK: - Label
    mainLabel = gtk_label_new(" ");
    gtk_label_set_xalign ((GtkLabel*)mainLabel, 0.02);
    gtk_fixed_put (GTK_FIXED (fixed), mainLabel, 10, 12);
    gtk_widget_set_size_request(mainLabel, 558, 95);
    gtk_widget_set_name(mainLabel, "mainLabel");
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_widget_set_sensitive(graphButton,false);
    gtk_main();
}


// MARK: - Create buttons
void createNumButtons(GtkWidget ** buttons) {
    char * numbers[12] = {"0",",","x","1","2","3","4","5","6","7","8","9"};
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
    char * sign[7] = {"(",")","+","-","*","/","^"};
    GtkWidget * button;
    for (int i = 0;i < 7;i++) {
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
    double res = 0;
    size_t lenght = 0;
    char * res_string;
    set = validator(searchString, point);
    if (set.errors == IS_EMPTY_FEEL || set.errors == IS_SYNTAX_ERROR) {
        gtk_label_set_label((GtkLabel*)mainLabel, "Ошибка");
    } else {
        res = calculator(searchString,point,&set,0);
        if (set.errors == IS_ERROR_VALUE) {
            gtk_label_set_label((GtkLabel*)mainLabel, "Ошибка");
        } else {
            sprintf(res_string,"%lf",res);
            strcat(searchString, " = ");
            strcat(searchString, res_string);
            updateLabel(mainLabel,searchString);
        }
    }
}

void modButtonClicked(GtkWidget * button) {
    const  char * value = (gtk_button_get_label((GtkButton*)button));
    fillString(value, &point);
    updateLabel(mainLabel, searchString);
}


void xButtonPressed(GtkWidget * button) {
    gtk_widget_set_sensitive(graphButton,true);
    gtk_widget_set_sensitive(equalButton,false);
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
        value[size + 1] = '\0';
    } else {
        size_t size = strlen((gtk_button_get_label((GtkButton*)button)));
        for (int i = 0;i < size;i++) {
            value[i] = (gtk_button_get_label((GtkButton*)button))[i];
        }
        value[size] = '\0';
    }
    fillString(value,&point);
    updateLabel(mainLabel, searchString);
}

void buttonNumberClicked(GtkWidget * button) {
    
    const char * value = (gtk_button_get_label((GtkButton*)button));
    fillString(value, &point);
    updateLabel(mainLabel, searchString);
}

void setGraph(GtkWidget * button) {
    charactersSet set;
    
    for (int i = 0;i < 1000;i++) {
        glob.coordy[i] = calculator(searchString,point,&set,i);
        glob.coordx[i] = i;
            g_print(" x = %lf\n",glob.coordx[i]);
            g_print(" y = %lf\n",glob.coordy[i]);
    }
        drawGraph();
}

void specButtonClicked(GtkWidget * button) {
    char value[1000];
    char num = ' ';
    if (point != 0) {
        num = searchString[point - 1];
    }
    if ((num >= '0' && num <= '9') || num == ')' || num == 'x') {
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
    
    char * ch = gtk_button_get_label((GtkButton*)button);
    
    if ( ch[0] == '(') {
        char value[1000];
        char num = ' ';
        if (point != 0) {
            num = searchString[point - 1];
        }
        
        if ((num >= '0' && num <= '9') || num == ')' || num == 'x') {
            value[0] = '*';
            size_t size = strlen((gtk_button_get_label((GtkButton*)button)));
            for (int i = 0;i < size;i++) {
                value[i + 1] = (gtk_button_get_label((GtkButton*)button))[i];
                value[size + 1] = '\0';
            }
            fillString(value, &point);
            updateLabel(mainLabel, searchString);
        } else {
            const char * value = (gtk_button_get_label((GtkButton*)button));
            fillString(value, &point);
            updateLabel(mainLabel, searchString);
        }
    } else {
        const char * value = (gtk_button_get_label((GtkButton*)button));
        fillString(value, &point);
        updateLabel(mainLabel, searchString);
    }
}

// MARK: - Work with string
void updateLabel(GtkWidget * label, char * text) {
    gtk_label_set_label((GtkLabel*)label, text);
}

void clearAllSearchString()  {
    size_t lenght = strlen(searchString);
    for (int i = lenght; i >= 0;i--) {
        searchString[i] = '\0';
    }
    point = 0;
    updateLabel(mainLabel,searchString);
    gtk_widget_set_sensitive(equalButton,true);
    gtk_widget_set_sensitive(graphButton,false);
}

void fillString(const char * input, int *point) {
    for (int i = 0;i < strlen(input);i++) {
        searchString[*point] = input[i];
        *point+= 1;
    }
}

// MARK: CSS
void myCSS(void){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    const gchar *myCssFile = "mystyle.css";
    GError *error = 0;
    
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}

// Graph

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
                              gpointer user_data)
{
    do_drawing(cr);
    do_drawing_graph(cr);
    return FALSE;
}


static void do_drawing_graph(cairo_t *cr) {
    cairo_set_source_rgb(cr, 4, 0, 0);
    cairo_set_line_width(cr, 1.3);
    cairo_move_to(cr, glob.coordx[500], 375);
    double y = 0.5;
    for (int i = 1; i < 1000;i++) {
        cairo_line_to(cr, glob.coordx[i],y);
        y+= 0.5;
    }

    glob.count = 0;
    
    cairo_stroke(cr);
}

static void do_drawing(cairo_t *cr)
{
    g_print("draw\n");
    
    
    cairo_move_to(cr, 500, 0);
    cairo_line_to(cr, 500,800 );
    
    cairo_move_to(cr, 500, 0);
    cairo_line_to(cr, 490,10 );
    cairo_move_to(cr, 500, 0);
    cairo_line_to(cr, 510,10 );
    cairo_move_to(cr, 513, 10);
    cairo_show_text(cr, "Y");
    
    cairo_move_to(cr, 0, 375);
    cairo_line_to(cr, 1000,375 );
    cairo_move_to(cr, 1000, 375);
    cairo_line_to(cr, 990,365 );
    cairo_move_to(cr, 1000, 375);
    cairo_line_to(cr, 990,385 );
    
    cairo_move_to(cr, 1000, 385);
    cairo_show_text(cr, "X");
    
    cairo_move_to(cr, 504, 387);
    cairo_show_text(cr, "0");
    glob.count = 0;
    
    cairo_stroke(cr);
}

void drawGraph() {
    GtkWidget *scalePlusButton;
    GtkWidget *scaleMinusButton;
    
    
    glob.count = 0;
    windowGraph = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(windowGraph), "Graph");
    gtk_window_set_modal(GTK_WINDOW(windowGraph), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(windowGraph), 1120, 800);
    gtk_window_set_position(GTK_WINDOW(windowGraph), GTK_WIN_POS_CENTER);
    gtk_widget_set_name(windowGraph, "windowGraph");
    
    fix = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(windowGraph), fix);
    
    
    darea = gtk_drawing_area_new();
    gtk_fixed_put (GTK_FIXED (fix), darea, 0, 0);
    gtk_widget_set_size_request(darea, 1020, 800);
    
    g_signal_connect(G_OBJECT(darea), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    
    
    scalePlusButton = gtk_button_new_with_label("Scale +");
    gtk_fixed_put (GTK_FIXED (fix), scalePlusButton, 1015, 320);
    gtk_widget_set_size_request(scalePlusButton, 50, 50);
    
    scaleMinusButton = gtk_button_new_with_label("Scale -");
    gtk_fixed_put (GTK_FIXED (fix), scaleMinusButton, 1017, 380);
    gtk_widget_set_size_request(scaleMinusButton, 50, 50);
    
    gtk_widget_set_name(scalePlusButton, "scalePlusButton");
    gtk_widget_set_name(scaleMinusButton, "scaleMinusButton");
    
    gtk_widget_show_all(windowGraph);
    
    gtk_main();
}
