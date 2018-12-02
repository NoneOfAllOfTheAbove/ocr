#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "../OCR.h"


//Global Variables.

int enableDebugMode = 0;
int enablePostprocessing = 0;
int enableFilters = 0;

GtkWidget *label; //Need it as G.V in order to change text.
GtkWidget *box2; //In order to get 50/50 on boxA and boxB size.
GtkWidget *boxA;
GtkWidget *boxB;
GtkWidget *image;
GtkWidget *overlay;
GtkWidget *window;

char *filename;
GdkPixbuf *pixbuf;

int extractText_clicked = 0;

gboolean file_isImage(gchar *file_path)
{   //Returns whether the image is of the following extension
    return (
        g_str_has_suffix(file_path, ".jpg") ||
        g_str_has_suffix(file_path, ".png") ||
        g_str_has_suffix(file_path, ".jpeg")||
        g_str_has_suffix(file_path, ".bmp")
        );
}

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
        if(filename != NULL && file_isImage(filename))  
        {
            gtk_image_clear(GTK_IMAGE(image));
            gtk_label_set_markup(GTK_LABEL(label), "");
            g_print("Reload image.\n");
        }
        //Creating the path.
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        //Print path is here.
        g_print("%s\n", filename);
        
        if (file_isImage(filename))
        {   
            gtk_box_pack_start(GTK_BOX(boxA), overlay, TRUE, TRUE, 0);

            GtkAllocation allocation;
            gtk_widget_get_allocation(boxA, &allocation);
            int desired_width = allocation.width; 
            int desired_height = allocation.height;

            //Load Image 
            image = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size(filename, desired_width, desired_height, NULL));
            
            gtk_overlay_add_overlay (GTK_OVERLAY(overlay), image);
            gtk_widget_set_halign (image, GTK_ALIGN_CENTER);
            gtk_widget_set_valign (image, GTK_ALIGN_CENTER);
            
            //Display Image
            gtk_widget_show_all(overlay);

            pixbuf = gdk_pixbuf_new_from_file(filename, NULL);
            
        }
    }
    else
    {
        g_print("You pressed Cancel\n");
    }
    gtk_widget_destroy(dialog);
    gtk_widget_queue_resize(window);
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
        filename = gtk_file_chooser_get_filename (chooser);

        OCR_ExportAsTextFile(filename);
        //Print path is here.
        g_print("%s\n", filename);
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
static void postprocessing_activated()
{
    g_print("Option -> Postprocessing.\n");
    if(enablePostprocessing)
    {
        enablePostprocessing = 0;
    } 
    else
    {
        enablePostprocessing = 1;
    }
}

static void filters_activated()
{
    g_print("Option -> Filters.\n");
    if (enableFilters)
    {
        enableFilters = 0;
    }
    else
    {
        enableFilters = 1;
    }
}

static void debugMode_activated()
{
    g_print("Debug -> Debug Mode activated.\n");
    if (enableDebugMode)
    {
        enableDebugMode = 0;
    }
    else
    {
        enableDebugMode = 1;
    }
}

/*------------------Help's GCallback------------------*/
static void helpAbout_activated()
{
    g_app_info_launch_default_for_uri("https://github.com/NoneOfAllOfTheAbove/OCR", NULL, NULL);
}

/*------------------------------------|FOR THEO|------------------------------------*/

static void extractText_activated(GtkWidget *extractTextButton)
{   
    //Can't click on "extractText_activated" if image is not loaded.
    if(image != NULL)
    {
        (void)extractTextButton;

        g_print("Extract text activated.\n");
        char *o = OCR_Start(filename, enableDebugMode, enableFilters, enablePostprocessing);
        gtk_label_set_markup(GTK_LABEL(label), o);
        
        //Label to the left.
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_widget_set_valign (label, GTK_ALIGN_START);

        //Clear current image and add another one.
        gtk_image_clear(GTK_IMAGE(image));
        
        GtkAllocation allocation;
        gtk_widget_get_allocation(boxA, &allocation);
        int boxA_width = allocation.width; 

        // pixbuf = gdk_pixbuf_new_from_file_at_size("resources/lastDebugScreenshot.png", boxA_width, boxA_height, NULL);
        image = gtk_image_new_from_pixbuf(pixbuf);

        gtk_overlay_add_overlay (GTK_OVERLAY(overlay), image);
        gtk_widget_set_halign (image, GTK_ALIGN_CENTER);
        gtk_widget_set_valign (image, GTK_ALIGN_CENTER);
        
        //set_spacing only after clicking on extractText_Button;
        extractText_clicked = 1;
        gtk_box_set_spacing(GTK_BOX(box2), -boxA_width/2);
        gtk_box_set_homogeneous(GTK_BOX(box2), TRUE);

        gtk_widget_queue_resize(window);
        gtk_widget_show_all(window);
    }
}   

void on_window_size_allocate()
{   

    GtkAllocation allocation;
    gtk_widget_get_allocation(
        boxA,
        &allocation);
    int desired_width = allocation.width;
    int desired_height = allocation.height;
    
    float r_box = (float)desired_height/desired_width;
    float r_image = (float)gdk_pixbuf_get_height(pixbuf)/
        gdk_pixbuf_get_width(pixbuf);


    gtk_widget_get_allocation(boxA, &allocation);
    int boxA_width = allocation.width; 
    

    if (r_box > r_image)
    {
        desired_width -= 4;
        desired_height = (int)(desired_width * r_image);
    }
    else
    {
        desired_height -= 4;
        desired_width = (int)(desired_height / r_image);
    }
     
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), gdk_pixbuf_scale_simple(pixbuf,
        desired_width, desired_height, GDK_INTERP_BILINEAR));
    
    if (extractText_clicked)
        gtk_box_set_spacing(GTK_BOX(box2), -boxA_width/2);

    gtk_widget_queue_resize(window);

}

gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{   //Function for shortcuts.   
    (void) widget;
    (void) user_data;
    
    switch(event->keyval)
    { 
        case GDK_KEY_q:
            if(event->state & GDK_CONTROL_MASK)
                {   //Ctrl + q => quit gui.
                    gtk_main_quit();        
                }
            break;
        case GDK_KEY_o:
            if(event->state & GDK_CONTROL_MASK)
                {   //Ctrl + o => open file chooser.
                    loadImage_activated(NULL, window);
                }
            break;
         case GDK_KEY_e:
            if(event->state & GDK_CONTROL_MASK)
                {   //Ctrl + e => open file chooser.
                    exportText_activated(NULL, window);
                }
            break;
         case GDK_KEY_KP_Enter:
            //Enter => extractText button runs.
            extractText_activated(NULL);
            break;
        default:
            return FALSE;
    }
    return FALSE;
}

//For me, keep int main(). But when have to push, replace int main() -> int StartGUI().
int StartGUI(int argc, char *argv[])
{   
    GtkWidget *mainBox;

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
    GtkWidget *optionMenu_postprocessing;
    GtkWidget *optionMenu_filters;
    GtkWidget *optionMenu_debugMode;

    /*For "Help" set*/
    GtkWidget *help;
    GtkWidget *helpMenu;
    GtkWidget *helpMenu_about;

    /*For "Run" button*/
    GtkWidget *extractTextButton;


    /*--------------------STEP 1: Initialisation of window--------------------*/ 

    gtk_init(&argc, &argv);
    int width = 800;
    int height = 500;
    /*Create a window of size width and height entitled "OCR"*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
    gtk_window_set_resizable (GTK_WINDOW(window), TRUE);
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
            => optionMenu_postprocessing: "Basic segmentation" (GtkMenuItem type)
    |
    => debug: "Debug" (GtkMenuItem)
        |
        => debugMenu (GtkMenu)
            |
            =>optionMenu_debugMode: "Debug Mode" (GtkMenuItem)
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

    optionMenu_debugMode = gtk_check_menu_item_new_with_label("Enable debug mode");
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(optionMenu_debugMode), FALSE);
    gtk_menu_shell_append(GTK_MENU_SHELL(optionMenu), optionMenu_debugMode);
    g_signal_connect(G_OBJECT(optionMenu_debugMode), "activate", G_CALLBACK(debugMode_activated), NULL);

    optionMenu_filters = gtk_check_menu_item_new_with_label("Enable noise cancellation and contrast enhancement");
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(optionMenu_filters), FALSE);
    gtk_menu_shell_append(GTK_MENU_SHELL(optionMenu), optionMenu_filters);
    g_signal_connect(G_OBJECT(optionMenu_filters), "activate", G_CALLBACK(filters_activated), NULL);

    optionMenu_postprocessing = gtk_check_menu_item_new_with_label("Enable postprocessing (spell check)");
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(optionMenu_postprocessing), FALSE);
    gtk_menu_shell_append(GTK_MENU_SHELL(optionMenu), optionMenu_postprocessing);
    g_signal_connect(G_OBJECT(optionMenu_postprocessing), "activate", G_CALLBACK(postprocessing_activated), NULL);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(option), optionMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), option);

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


    /*-------------------- STEP 3: Creation of button Extract Text --------------------*/ 
    
    extractTextButton = gtk_button_new_with_label("Extract text");
    //For Run button
    g_signal_connect(G_OBJECT(extractTextButton), "clicked", G_CALLBACK(extractText_activated), NULL);
    
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
        |        |        |    
        |  (A)   |  (B)   |
        |        |        |
        -------------------

    (3): contains the "Run" button.
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
    
    overlay = gtk_overlay_new();
                            /*-----------------------ADD SEPARATOR-------------------------*/
    //Add Separator between box A and B
    GtkWidget *separator;
    separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(box2),separator, FALSE, FALSE, 0);

    
                         //-----------------------Add "label" to "boxB"-----------------------

    label = gtk_label_new(NULL);
    
    gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
    //Put Text at the left side of the box.
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    //Can select and copy "label" from GUI.
    gtk_label_set_selectable(GTK_LABEL(label), TRUE);
    //Enable us to wrapped the text in multiple line.
    gtk_label_set_line_wrap (GTK_LABEL (label), TRUE);
    gtk_box_pack_start(GTK_BOX(boxB), label, FALSE, FALSE, 0);

                         //-----------------------Add "boxB" to "box2"-----------------------
    gtk_box_pack_start(GTK_BOX(box2),boxB, TRUE, TRUE, 0);
    
                         //-----------------------Add "box2" to "mainBox"-----------------------
    gtk_box_pack_start(GTK_BOX(mainBox), box2, TRUE, TRUE, 0);
    
    /*--------------------------------------------CASE 3--------------------------------------------*/
    //Add "run" to case (3) of "mainBox"
    gtk_box_pack_end(GTK_BOX(mainBox), extractTextButton, FALSE, FALSE, 0);


    /*-------------------- Step 5: Show window --------------------*/ 
    //Add mainBox to the container window.
    gtk_container_add(GTK_CONTAINER(window), mainBox);  


    //Enable us to resize window.
    g_signal_connect(G_OBJECT(window),"size-allocate", G_CALLBACK(on_window_size_allocate), NULL);
    //Enable us to quit the program.
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //Enable us to have shortcuts.
    g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (on_key_press), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
