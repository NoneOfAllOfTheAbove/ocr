#include <gtk/gtk.h>

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

/*------------------Run's GCallback------------------*/
static void runButton_activated()
{
    g_print("Run activated.\n");
}

/*------------------------------------|FOR THEO|------------------------------------*/

/*------------------Write function------------------*/

static const gchar* writeFunction()
{
    const gchar* text = "Si tu ne comprends pas, ou ne maîtrises pas, la notion de coefficient binomial,\
    inutile de chercher à calculer toi-même les nombres de Catalan, que tu découvris dans cette obscure revue américaine d'algèbre,\
    croyant qu'il s'agissait de “nombres catalans” (l'anglais Catalan numbers est équivoque), avant de faire le chemin historique et de\
    découvrir qu'ils auraient tout aussi bien pu se nommer suite d'Euler, entiers de Seger, ou nombres de Ming Antu.\
    Des textes en 16.796 signes ? Un roman de 58.786 mots ? Tu n'y penses pas !";
    return text;
}

/*------------------Draw function------------------*/

gboolean drawFunction ()
{   
    /*FILL ME*/
    return TRUE;
}

//For me, keep int main(). But when have to push, replace int main() -> int StartGUI().
int StartGUI (int argc, char *argv[])
{

    GtkWidget *window;
    GtkWidget *mainBox;
    GtkWidget *box2;
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
    GtkWidget *label;

    /*For "Run" button*/
    GtkWidget *runButton;


    /*--------------------STEP 1: Initialisation of window--------------------*/ 

    gtk_init(&argc, &argv);

    /*Create a window of size 400x250 entitled "OCR"*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 250);
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
    optionMenu_basicSeg = gtk_check_menu_item_new_with_label("Basic segmentation");
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
    
    runButton = gtk_button_new_with_label("Run");
    //For Run button.
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
    
    /*----------------------CASE 1----------------------*/
    //Add "menuBar" to case (1) of "mainBox"
    gtk_box_pack_start(GTK_BOX(mainBox), menuBar, FALSE, FALSE, 0);
    
    /*----------------------CASE 2----------------------*/
    //Add "boxA" and "boxB" to case (2) of "mainBox". Case (2) will be called "box2"
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    boxA = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    boxB = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //Add "boxA" to "box2"
    gtk_box_pack_start(GTK_BOX(box2),boxA, TRUE, TRUE, 0);

    /*----------------------TEST----------------------*/
    /*
    GtkWidget *drawing_area = gtk_drawing_area_new ();
    gtk_widget_set_size_request (drawing_area, 100, 100);
    gtk_box_pack_start(GTK_BOX(boxA),drawing_area, TRUE, TRUE, 0);
    g_signal_connect (G_OBJECT (drawing_area), "draw",
                    G_CALLBACK (draw_callback), NULL);
    */
    /*------------------------------------------------*/
    //Add Separator between box A and B
    GtkWidget *separator;
    separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(box2),separator, FALSE, TRUE, 0);

    //Add "boxB" to "box2"
    gtk_box_pack_start(GTK_BOX(box2),boxB, TRUE, TRUE, 0);

    /*Add "label" to "boxB"*/
    label = gtk_label_new(writeFunction());
    gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
    g_object_set (label, "margin", 0, NULL);
    //Can select and copy from GUI.
    gtk_label_set_selectable(GTK_LABEL(label), TRUE);

    //Enable us to wrapped the text in multiple line.
    gtk_label_set_line_wrap (GTK_LABEL (label), TRUE);
    gtk_label_set_max_width_chars (GTK_LABEL (label), 30);

    //Add "label" to "boxB"
    gtk_box_pack_start(GTK_BOX(boxB), label, FALSE, FALSE, 0);

    //Add "box2" to case (2) of "mainBox"
    gtk_box_pack_start(GTK_BOX(mainBox), box2, TRUE, TRUE, 0);

    /*----------------------CASE 3----------------------*/
    //Add "run" to case (3) of "mainBox"
    gtk_box_pack_end(GTK_BOX(mainBox), runButton, FALSE, FALSE, 0);

    //Add mainBox to the container window.
    gtk_container_add(GTK_CONTAINER(window), mainBox);


    /*-------------------- Step 5: Show window --------------------*/ 
    
    //Enable us to quit the program.
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}