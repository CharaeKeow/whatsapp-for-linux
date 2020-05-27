#include "MainWindow.h"
#include <gtkmm/grid.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/main.h>


namespace
{
    constexpr auto const WHATSAPP_WEB_URI = "https://web.whatsapp.com/";
}


MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
    : Gtk::Window{cobject}
{
    set_default_size(1280, 720);

    auto const appIcon = Gdk::Pixbuf::create_from_file("icon.ico");
    set_icon(appIcon);

    Gtk::Grid* mainGrid = nullptr;
    refBuilder->get_widget("main_grid", mainGrid);
    mainGrid->attach(m_webView, 0, 1);
    m_webView.set_vexpand();

    Gtk::MenuItem* refreshMenuItem = nullptr;
    refBuilder->get_widget("refresh_menu_item", refreshMenuItem);
    refreshMenuItem->signal_activate().connect(sigc::mem_fun(this, &MainWindow::onRefresh));

    Gtk::MenuItem* quitMenuItem = nullptr;
    refBuilder->get_widget("quit_menu_item", quitMenuItem);
    quitMenuItem->signal_activate().connect(sigc::mem_fun(this, &MainWindow::onQuit));

    m_webView.loadUri(WHATSAPP_WEB_URI);

    maximize();
    show_all();
}

void MainWindow::onRefresh()
{
    m_webView.refresh();
}

void MainWindow::onQuit()
{
    // TODO Use something else since this is deprecated.
    Gtk::Main::quit();
}