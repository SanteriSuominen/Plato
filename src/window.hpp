#pragma once
#include <gtkmm.h>

class Window : public Gtk::Window 
{
public:
    Window();
    
private:
    Gtk::Box main_box;
    Gtk::Box project_name_box;
    Gtk::Label project_name_label;
    Gtk::Entry project_name_entry;
    Gtk::Expander options_expander;
    Gtk::Box options_box;
    Gtk::Button run_button;

    Gtk::CheckButton separate_src_include_button;
    Gtk::CheckButton generate_makefile;
    Gtk::CheckButton create_documents;
    Gtk::CheckButton setup_git;
    Gtk::CheckButton setup_gitignore;
    Gtk::CheckButton add_subfolder;

    Gtk::FileChooserWidget file_chooser_widget;

    void on_button_clicked();
    void toggle_setup_git();
    void toggle_add_subfolder();
};