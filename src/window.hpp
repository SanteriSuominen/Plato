
#pragma once

#include <gtkmm.h>

class Window : public Gtk::Window {
public:
    Window();

private:
    Gtk::Button m_button;

    void on_button_clicked();
};