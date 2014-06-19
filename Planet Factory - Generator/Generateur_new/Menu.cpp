#include "Menu.h"

Menu::Menu(QWidget *parent) : QWidget(parent)
{
    _save = new QPushButton(this);
    _save->setGeometry(0, 0, 100, 25);
    _save->setStyleSheet("QPushButton { background-image: url(:/res/save_button.png); border: none }");
    _load = new QPushButton(this);
    _load->setGeometry(0, 35, 100, 25);
    _load->setStyleSheet("QPushButton { background-image: url(:/res/load_button.png); border: none }");
    _launch = new QPushButton(this);
    _launch->setGeometry(0, 70, 100, 25);
    _launch->setStyleSheet("QPushButton { background-image: url(:/res/launch_button.png); border: none }");
    _reset = new QPushButton(this);
    _reset->setGeometry(0, 105, 100, 25);
    _reset->setStyleSheet("QPushButton { background-image: url(:/res/reset_button.png); border: none }");
    _facebook = new QPushButton(this);
    _facebook->setGeometry(13, 180, 32, 32);
    _facebook->setStyleSheet("QPushButton { background-image: url(:/res/facebook.png); border: none }");
    _twitter = new QPushButton(this);
    _twitter->setGeometry(55, 180, 32, 32);
    _twitter->setStyleSheet("QPushButton { background-image: url(:/res/twitter.png); border: none }");

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
