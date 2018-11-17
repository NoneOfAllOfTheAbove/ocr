#include <gtk/gtk.h>


//Gloabal Variable.
GtkWidget *label; //Need it as G.V in order to change text.
GtkWidget *box2; //In order to get 50/50 on boxA and boxB size.

/*------------------File's GCallback------------------*/

static void loadImage_activated (GtkWidget *fileMenu_loadImage, gpointer window)
{   

    /*We have to put the first parameter even if we are not using. This is to respect
    convention. If we don't put it, it will show a warning explaining that we are trying
    to cast GTKMenuItem to GTKWindow. 

    To counter that, we do the following thing : (void)name_of_variable.
    */
    (void)fileMenu_loadImage;

    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Chosse a file", 
                                        GTK_WINDOW(window), 
                                        GTK_FILE_CHOOSER_ACTION_OPEN, 
                                        ("_Cancel"), 
                                        GTK_RESPONSE_CANCEL, 
                                        ("_Open the image"),
                                        GTK_RESPONSE_ACCEPT, 
                                        NULL);

   
    gint res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {   
        //Creating the path.
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        //Print path is here.
        g_print("%s\n", filename);

        g_free (filename);
    }
    else
    {
        g_print("You pressed Cancel\n");
    }
    gtk_widget_destroy(dialog);
}

static void exportText_activated(GtkWidget *fileMenu_exportMenu_text, gpointer window)
{   
    /*Check if it overwrites a file when we choose an already existing name
    for our Text File.
    */

    (void)fileMenu_exportMenu_text;
    GtkWidget *dialog;
    GtkFileChooser *chooser;

    dialog = gtk_file_chooser_dialog_new ("Save File",
                                        GTK_WINDOW(window),
                                        GTK_FILE_CHOOSER_ACTION_SAVE,
                                        ("_Cancel"),
                                        GTK_RESPONSE_CANCEL,
                                        ("_Save"),
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);
    
    chooser = GTK_FILE_CHOOSER (dialog);
    gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
    gint res = gtk_dialog_run (GTK_DIALOG (dialog));

    if (res == GTK_RESPONSE_ACCEPT)
    {   
         //Creating the path.
        char *filename;
        filename = gtk_file_chooser_get_filename (chooser);
        //Print path is here.
        g_print("%s\n", filename);
        g_free (filename);
    }
    else
    {
        g_print("You pressed Cancel\n");
    }
    
    gtk_widget_destroy (dialog);
}

static void quit_activated()
{
    g_print("File -> Quit activated.\n");
    gtk_main_quit();
}

/*------------------Option's GCallback------------------*/
static void basicSeg_activated()
{
    g_print("Option -> Basic segmentation activated.\n");
}

/*------------------Debug's GCallback------------------*/
static void debugMode_activated()
{
    g_print("Debug -> Debug Mode activated.\n");
}

static void loadNNdata_activated()
{
    g_print("Debug -> Load NN data activated.\n");
}

static void exportNNdata_activated()
{
    g_print("Debug -> Export NN data activated.\n");
}

/*------------------Help's GCallback------------------*/
static void helpAbout_activated()
{
    g_print("Help -> About activated.\n");
}

/*------------------------------------|FOR THEO|------------------------------------*/

/*------------------Run's GCallback------------------*/ 
// This is the Run"s GCallback and at the same time write function.
//-> When clicked on run, text displays in the text area.
static void runButton_activated(GtkWidget *runButton, gpointer *window)
{   
    (void)window;
    (void)runButton;
    g_print("Run activated.\n");
    gtk_label_set_text(GTK_LABEL (label), "Si tu ne comprends pas, ou ne maîtrises pas, la notion de coefficient binomial,\
    inutile de chercher à calculer toi-même les nombres de Catalan, que tu découvris dans cette obscure revue américaine d'algèbre,\
    croyant qu'il s'agissait de “nombres catalans” (l'anglais Catalan numbers est équivoque), avant de faire le chemin historique et de\
    découvrir qu'ils auraient tout aussi bien pu se nommer suite d'Euler, entiers de Seger, ou nombres de Ming Antu.\
    Des textes en 16.796 signes ? Un roman de 58.786 mots ? Tu n'y penses pas !"); 

    gtk_box_set_homogeneous(GTK_BOX(box2), TRUE);   
    gtk_box_set_spacing(GTK_BOX(box2), -340); //If this line is removed. In the text area, there will be blank space at the left of TextArea.
}

/*------------------Draw function------------------*/
//Enable you to draw.
static void drawFunction (GtkWidget *widget, cairo_t *cr, gpointer window)
{   
    (void)window;
    guint width, height;
    GdkRGBA color;
    GtkStyleContext *context;

    context = gtk_widget_get_style_context (widget);

    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);

    gtk_render_background (context, cr, 0, 0, width, height);

    cairo_arc (cr,
                width / 2.0, height / 2.0,
                MIN (width, height) / 2.0,
                0, 2 * G_PI);

    gtk_style_context_get_color (context,
                                gtk_style_context_get_state (context),
                                &color);
    gdk_cairo_set_source_rgba (cr, &color);

    cairo_fill (cr);
}

//For me, keep int main(). But when have to push, replace int main() -> int StartGUI().
int main (int argc, char *argv[])
{   
    //size of the window
    gint width;
    gint height;

    GtkWidget *window;
    GtkWidget *mainBox;
    //GtkWidget *box2; Set as global variable at the begining of our file.
    GtkWidget *boxA;
    GtkWidget *boxB;

    /*Menu Bar*/
    GtkWidget *menuBar;
    
    /*For "File" set*/
    GtkWidget *file;
    GtkWidget *fileMenu; 
    GtkWidget *fileMenu_loadImage;
    GtkWidget *fileMenu_quit;
    GtkWidget *fileMenu_export;
    GtkWidget *fileMenu_exportMenu;
    GtkWidget *fileMenu_exportMenu_text;
     
    /*For "Option" set*/
    GtkWidget *option;
    GtkWidget *optionMenu;
    GtkWidget *optionMenu_basicSeg;

    /*For "Debug" set*/
    GtkWidget *debug;
    GtkWidget *debugMenu;
    GtkWidget *debugMenu_debugMode;
    GtkWidget *debugMenu_loadNN;
    GtkWidget *debugMenu_exportNN;

    /*For "Help" set*/
    GtkWidget *help;
    GtkWidget *helpMenu;
    GtkWidget *helpMenu_about;
    
    //For writing in boxB of case(2) of mainBox
    //GtkWidget *label; It is declared as Global variable.

    /*For "Run" button*/
    GtkWidget *runButton;


    /*--------------------STEP 1: Initialisation of window--------------------*/ 

    gtk_init(&argc, &argv);
    width = 1400;
    height = 800;
    /*Create a window of size width and height entitled "OCR"*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "OCR");

    /*--------------------STEP 2: Creation of the Menu bar--------------------*/ 

    /*It will looks like this:

    menuBar (GtkMenuBar)
    |
    => file: "File" (GtlMenuItem)
        |
        =>fileMenu (GtkMenu that contains GtkMenuItem)
            |
            =>fileMenu_loadImage: "Load Image" (GtkMenuItem)
            |
            =>fileMenu_export (GtkMenuItem type)
            |        |
            |        => fileMenu_exportMenu (GtkMenu type)
            |               |
            |               => fileMenu_exportMenu_text: "Text"
            |
            =>fileMenu_quit: "Quit" (GtkMenuItem)
    |
    => option: "Options" (GtkMenuItem)
        |
        => optionMenu (GtkMenu)
            |
            => optionMenu_basicSeg: "Basic segmentation" (GtkMenuItem type)
    |
    => debug: "Debug" (GtkMenuItem)
        |
        => debugMenu (GtkMenu)
            |
            =>debugMenu_debugMode: "Debug Mode" (GtkMenuItem)
            |
            =>debugMenu_loadNN: "Load NN data" (GtkMenuItem)
            |
            =>debugMenu_exportNN: "Export NN data" (GtkMenuItem)
    
    |
    => help: "Help" (GtkMenuItem)
        |
        => helpMenu (GtkMenu)
            |
            => helpMenu_about: "About" (GtkMenuItem)
    */
    
    //Initialisation of the menu bar
    menuBar = gtk_menu_bar_new();

    //----------------------------------For "File" set----------------------------------
    fileMenu = gtk_menu_new();
    fileMenu_exportMenu = gtk_menu_new();

    file = gtk_menu_item_new_with_label("File");
    fileMenu_loadImage = gtk_menu_item_new_with_label("Load Image");
    fileMenu_quit = gtk_menu_item_new_with_label("Quit");
    fileMenu_export = gtk_menu_item_new_with_label("Export");
    fileMenu_exportMenu_text = gtk_menu_item_new_with_label("Text");
    

    /*Add "fileMenu_exportMenu_test" to "fileMenu_exportMenu"*/
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu_exportMenu), fileMenu_exportMenu_text);

    /*Add "fileMenu_exportMenu" to "fileMenu_export"*/
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMenu_export), fileMenu_exportMenu);

    /*Add "fileMenu_loadImage", "fileMenu_export" and "fileMenu_quit" to fileMenu*/
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), fileMenu_loadImage);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), fileMenu_export);
    //add separator to "fileMenu" 
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), gtk_separator_menu_item_new());
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), fileMenu_quit);


    /*Add filemenu to file*/
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), fileMenu);
   
    /*Add file to menubar*/
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), file);

    /*Connects GCallback function*/

    //For Loading Image
    g_signal_connect(G_OBJECT(fileMenu_loadImage), "activate", G_CALLBACK(loadImage_activated), window);
    //For Export -> Test
    g_signal_connect(G_OBJECT(fileMenu_exportMenu_text), "activate", G_CALLBACK(exportText_activated), window);
    //For Quit
    g_signal_connect(G_OBJECT(fileMenu_quit), "activate", G_CALLBACK(quit_activated), NULL);



    //----------------------------------For "Option" set----------------------------------
    
    optionMenu = gtk_menu_new();

    option = gtk_menu_item_new_with_label("Options");
    
    //In order to have the "tick" feature.
    optionMenu_basicSeg = gtk_check_menu_item_new_with_label("Handle sticked characters");
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(optionMenu_basicSeg), FALSE);

    /*Add "optionMenu_basicSeg" to optionMenu */
    gtk_menu_shell_append(GTK_MENU_SHELL(optionMenu), optionMenu_basicSeg);


    /*Add "optionMenu" to "option"*/
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(option), optionMenu);
                
    /*Add "option" to menuBar*/                 
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), option);

    //Connects GCallback function.
    //For Basic segmentation.
    g_signal_connect(G_OBJECT(optionMenu_basicSeg), "activate", G_CALLBACK(basicSeg_activated), NULL);


    //----------------------------------For "Debug" set----------------------------------
    
    debugMenu = gtk_menu_new();

    debug = gtk_menu_item_new_with_label("Debug");
    
    //In order to have the "tick feature"
    debugMenu_debugMode = gtk_check_menu_item_new_with_label("Debug Mode");
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(debugMenu_debugMode), FALSE);
    
    debugMenu_loadNN = gtk_menu_item_new_with_label("Load NN data");
    debugMenu_exportNN = gtk_menu_item_new_with_label("Export NN data");

    /*Add "debugMenu_debugMode", "debugMenu_loadNN " and "debugMenu_exportNN"
     to debugMenu */
    gtk_menu_shell_append(GTK_MENU_SHELL(debugMenu), debugMenu_debugMode);
    //add separator to "debugMenu" 
    gtk_menu_shell_append(GTK_MENU_SHELL(debugMenu), gtk_separator_menu_item_new());
    gtk_menu_shell_append(GTK_MENU_SHELL(debugMenu), debugMenu_loadNN);
    gtk_menu_shell_append(GTK_MENU_SHELL(debugMenu), debugMenu_exportNN);

    /*Add "debugMenu" to "debug"*/
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(debug), debugMenu);

    /*Add "debug" to "menuBar"*/
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), debug);

    //Connects GCallback function.
    //For Debug Mode
    g_signal_connect(G_OBJECT(debugMenu_debugMode), "activate", G_CALLBACK(debugMode_activated), NULL);
    //For Load NN data
    g_signal_connect(G_OBJECT(debugMenu_loadNN), "activate", G_CALLBACK(loadNNdata_activated), NULL);
    //For Export NN data
    g_signal_connect(G_OBJECT(debugMenu_exportNN), "activate", G_CALLBACK(exportNNdata_activated), NULL);

    //----------------------------------For "About" set----------------------------------
    
    helpMenu = gtk_menu_new();

    help = gtk_menu_item_new_with_label("Help");
    helpMenu_about = gtk_menu_item_new_with_label("About");

    /*Add "helpMenu_about" to "helpMenu"*/
    gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), helpMenu_about);
    
    /*Add "helpMenu" to "help"*/
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpMenu);

    /*Add "help" to "menuBar"*/
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), help);

    //Connects GCallback function.
    //For About.
    g_signal_connect(G_OBJECT(helpMenu_about), "activate", G_CALLBACK(helpAbout_activated), NULL);


    /*-------------------- STEP 3: Creation of button Run --------------------*/ 
    
    runButton = gtk_button_new_with_label("Extract text");
    //For Run button
    g_signal_connect(G_OBJECT(runButton), "clicked", G_CALLBACK(runButton_activated), NULL);
    
    /*-------------------- STEP 4: Creation of mainBox --------------------*/ 
    /*
    mainBox will be seperate in 3 cases like this:

    -----------------
    |      (1)      |
    |               |
    -----------------
    |      (2)      |
    |               |
    -----------------
    |      (3)      |                  
    |               |
    -----------------

    (1): contains the menuBar.
    (2): contains a box that will be seperate in 2.
    |   
    |  
    =>  -------------------
        |       (A)       |    
        |-----------------|
        |       (B)       |
        -------------------

    (3): contain the "Run" button.
    */

    mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    
    /*--------------------------------------------CASE 1--------------------------------------------*/
    //Add "menuBar" to case (1) of "mainBox"
    gtk_box_pack_start(GTK_BOX(mainBox), menuBar, FALSE, FALSE, 0);
    
    /*--------------------------------------------CASE 2--------------------------------------------*/
    //Add "boxA" and "boxB" to "box2". "box2" will later be add to case(2) of "mainBox"
    box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    boxA = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    boxB = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

                        
                                //-----------------------ADD "boxA" TO "box2"-----------------------

    gtk_box_pack_start(GTK_BOX(box2),boxA, TRUE, TRUE, 0);
    //gtk_drag_dest_set(boxA,GTK_DEST_DEFAULT_ALL,) => For drag and drop.

    /*--------Create an "overlay" in order to put "drawing area" on top of "image"--------*/
    
    //Create an "overlay" and put in "boxA"
    GtkWidget *overlay = gtk_overlay_new();
    gtk_box_pack_start(GTK_BOX(boxA), overlay, TRUE, TRUE, 0);
    
    //Creation of "image"
    GtkWidget *image;
    //width*heigth = 700*700.
    image = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("/home/sphird/Images/GUI_OCR.jpg"
                                                                        ,800
                                                                        ,800
                                                                        ,NULL));
    
    //The 3 lines is to add "image" in "overlay" and control their display.
    gtk_overlay_add_overlay (GTK_OVERLAY(overlay), image);
    gtk_widget_set_halign (image, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (image, GTK_ALIGN_CENTER);
  
    //Creation of drawing_area and its callBack Function.
    GtkWidget *drawing_area = gtk_drawing_area_new ();
    gtk_widget_set_size_request (drawing_area, 100, 100);
    g_signal_connect_after(G_OBJECT (drawing_area), "draw",
                    G_CALLBACK (drawFunction), NULL);
        
    //The 3 lines is to add "drawing_area" in "overlay" and control their display.
    gtk_overlay_add_overlay (GTK_OVERLAY(overlay), drawing_area);
    gtk_widget_set_halign (drawing_area, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (drawing_area, GTK_ALIGN_CENTER);
  

                            /*-----------------------ADD SEPARATOR-------------------------*/
    //Add Separator between box A and B
    GtkWidget *separator;
    separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(box2),separator, FALSE, FALSE, 0);

    //Add "boxB" to "box2"
    gtk_box_pack_start(GTK_BOX(box2),boxB, TRUE, TRUE, 0);

    /*Add "label" to "boxB"*/
    label = gtk_label_new(NULL);
    
    gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
    //Put Text at the left side of the box.
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    //Can select and copy "label" from GUI.
    gtk_label_set_selectable(GTK_LABEL(label), TRUE);
    //Enable us to wrapped the text in multiple line.
    gtk_label_set_line_wrap (GTK_LABEL (label), TRUE);
    gtk_label_set_max_width_chars (GTK_LABEL (label), 0);
    

                            //-----------------------Add "label" to "boxB-----------------------
    
    gtk_box_pack_start(GTK_BOX(boxB), label, FALSE, FALSE, 0);

    //Add "box2" to case (2) of "mainBox"
    gtk_box_pack_start(GTK_BOX(mainBox), box2, TRUE, TRUE, 0);
    
    /*--------------------------------------------CASE 3--------------------------------------------*/
    //Add "run" to case (3) of "mainBox"
    gtk_box_pack_end(GTK_BOX(mainBox), runButton, FALSE, FALSE, 0);


    /*-------------------- Step 5: Show window --------------------*/ 
    //Add mainBox to the container window.
    gtk_container_add(GTK_CONTAINER(window), mainBox);

    //Enable us to quit the program.
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
