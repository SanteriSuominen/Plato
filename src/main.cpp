#include "window.hpp"
#include <gtkmm/application.h>

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("com.example.plato");
    return app->make_window_and_run<Window>(argc, argv);
}