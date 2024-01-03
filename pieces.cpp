/*
Nom du fichier : pieces.cpp
Description : methodes des classes de pieces.hpp
Auteurs : Malaurie St-Amour-Bilodeau, Zabiullah Shair Zaie et Julie Labbe
Groupe : 03
Date de remise : 9 mai 2021
*/
#include "pieces.hpp"

namespace Labels
{
    Cavalier::Cavalier(QWidget* parent) : QLabel(parent) {}

    void Cavalier::mousePressEvent(QMouseEvent* ev)
    {
        emit Mouse_Pressed();
    }

    Fou::Fou(QWidget* parent) : QLabel(parent) {}

    void Fou::mousePressEvent(QMouseEvent* ev)
    {
        emit Mouse_Pressed();
    }

    Roi::Roi(QWidget* parent) : QLabel(parent) {}

    void Roi::mousePressEvent(QMouseEvent* ev)
    {
        emit Mouse_Pressed();
    }
}