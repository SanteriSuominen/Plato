#include "window.hpp"
#include "project_generator.hpp"
#include <iostream>
#include <string>

Window::Window()
    : main_box(Gtk::Orientation::VERTICAL, 10),
      project_name_box(Gtk::Orientation::HORIZONTAL, 8),
      project_name_label("Project name:"),
      options_box(Gtk::Orientation::VERTICAL, 6)
{
    set_title("Plato");
    set_default_size(900, 600);
    set_child(main_box);

    main_box.set_margin_top(10);
    main_box.set_margin_bottom(10);
    main_box.set_margin_start(10);
    main_box.set_margin_end(10);

    // File chooser
    file_chooser_widget.set_action(Gtk::FileChooser::Action::SELECT_FOLDER); // or SAVE
    file_chooser_widget.set_create_folders(true);
    file_chooser_widget.set_filter(Gtk::FileFilter::create());
    file_chooser_widget.set_hexpand(true);
    file_chooser_widget.set_vexpand(true);
    file_chooser_widget.set_halign(Gtk::Align::FILL);
    file_chooser_widget.set_valign(Gtk::Align::FILL);

    project_name_box.set_hexpand(true);
    project_name_box.set_halign(Gtk::Align::FILL);
    project_name_box.set_margin_start(18);
    project_name_box.set_visible(false);

    project_name_label.set_halign(Gtk::Align::START);

    project_name_entry.set_hexpand(true);
    project_name_entry.set_halign(Gtk::Align::FILL);
    project_name_entry.set_placeholder_text("my_project");

    project_name_box.append(project_name_label);
    project_name_box.append(project_name_entry);

    // Option checkboxes
    separate_src_include_button.set_label("Separate src/include");
    separate_src_include_button.set_hexpand(true);
    separate_src_include_button.set_halign(Gtk::Align::FILL);

    generate_makefile.set_label("Generate Makefile");
    generate_makefile.set_hexpand(true);
    generate_makefile.set_halign(Gtk::Align::FILL);

    create_documents.set_label("Create Documents");
    create_documents.set_hexpand(true);
    create_documents.set_halign(Gtk::Align::FILL);

    setup_git.set_label("Setup Git");
    setup_git.set_hexpand(true);
    setup_git.set_halign(Gtk::Align::FILL);
    setup_git.signal_toggled().connect(sigc::mem_fun(*this, &Window::toggle_setup_git));
    
    setup_gitignore.set_label("Setup .gitignore");
    setup_gitignore.set_hexpand(true);
    setup_gitignore.set_halign(Gtk::Align::FILL);
    
    add_subfolder.set_label("Add Subfolder with project name to path");
    add_subfolder.set_hexpand(true);
    add_subfolder.set_halign(Gtk::Align::FILL);
    add_subfolder.signal_toggled().connect(sigc::mem_fun(*this, &Window::toggle_add_subfolder));

    generate_makefile.set_active(true);
    create_documents.set_active(true);
    
    setup_gitignore.set_sensitive(false);
    setup_git.set_sensitive(false);

    options_expander.set_label("Options");
    options_expander.set_expanded(false);
    options_expander.set_hexpand(true);
    options_expander.set_halign(Gtk::Align::FILL);
    options_expander.set_child(options_box);

    options_box.append(create_documents);
    options_box.append(generate_makefile);
    options_box.append(separate_src_include_button);
    options_box.append(add_subfolder);
    options_box.append(project_name_box);
    options_box.append(setup_git);
    options_box.append(setup_gitignore);
    
    // Run button
    run_button.set_label("Create Project");
    run_button.set_hexpand(true);
    run_button.set_halign(Gtk::Align::FILL);
    run_button.signal_clicked().connect(sigc::mem_fun(*this, &Window::on_button_clicked));

    //build app
    main_box.append(file_chooser_widget);
    main_box.append(options_expander);
    main_box.append(run_button);
}
   
void Window::on_button_clicked()
{
    auto file = file_chooser_widget.get_file();
    if (!file) return;

    auto path = file->get_path();
    if (path.empty()) return;
    
    std::string project_name = project_name_entry.get_text();
    const bool has_project_name = (project_name.find_first_not_of(" \t\n\r") != std::string::npos);

    if (add_subfolder.get_active() && !has_project_name)
    {
        std::cerr << "Project name is required when add_subfolder is enabled.\n";
        return;
    }

    ProjectGenerator::ProjectRequest req{
        .root_path = path,
        .project_name = project_name,
        .options = {
            .separate_src_include = separate_src_include_button.get_active(),
            .generate_makefile    = generate_makefile.get_active(),
            .create_documents     = create_documents.get_active(),
            .setup_git            = setup_git.get_active(),
            .setup_gitignore      = setup_gitignore.get_active(),
            .add_subfolder        = add_subfolder.get_active(),
        }
    };

    ProjectGenerator generator;
    generator.generate_project(req);
}

void Window::toggle_setup_git()
{
    if (setup_git.get_active())
    {
        setup_gitignore.set_sensitive(true);
    }
    else
    {
        setup_gitignore.set_sensitive(false);
        setup_gitignore.set_active(false);
    }
}

void Window::toggle_add_subfolder()
{
    const bool enabled = add_subfolder.get_active();
    project_name_box.set_visible(enabled);
    if (!enabled)
    {
        project_name_entry.set_text("");
    }
}