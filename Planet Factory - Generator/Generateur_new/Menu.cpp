#include "Menu.hpp"

Menu::Menu(QWidget *parent) : QWidget(parent)
{
    setGeometry(50,330,100,210);
    show();

    _save = new QPushButton(this);
    _save->setGeometry(0, 0, 100, 25);
    _load = new QPushButton(this);
    _load->setGeometry(0, 35, 100, 25);
    _launch = new QPushButton(this);
    _launch->setGeometry(0, 70, 100, 25);
    _reset = new QPushButton(this);
    _reset->setGeometry(0, 105, 100, 25);
    _facebook = new QPushButton(this);
    _facebook->setGeometry(13, 180, 32, 32);
    _twitter = new QPushButton(this);
    _twitter->setGeometry(55, 180, 32, 32);

    _save->setObjectName("menu_save");
    _load->setObjectName("menu_load");
    _launch->setObjectName("menu_launch");
    _reset->setObjectName("menu_reset");
    _facebook->setObjectName("menu_facebook");
    _twitter->setObjectName("menu_twitter");

    QObject::connect(_facebook, SIGNAL(clicked()), this, SLOT(linkFacebook()));
    QObject::connect(_twitter, SIGNAL(clicked()), this, SLOT(linkTwitter()));
}

Menu::~Menu()
{
}

void Menu::linkFacebook()
{
    QDesktopServices::openUrl(QUrl("https://www.facebook.com/planetfactoryeip?ref=hl"));
}

void Menu::linkTwitter()
{
    QDesktopServices::openUrl(QUrl("https://www.twitter.com/"));
}
