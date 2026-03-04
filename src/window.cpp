#include "window.hpp"
#include <iostream>

Window::Window() : m_button("Click me") {
    set_title("Plato GTK App");
    set_default_size(500, 320);
    set_child(m_button);
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &Window::on_button_clicked));
}

void Window::on_button_clicked() {
    std::cout << "Button clicked!\n";
}