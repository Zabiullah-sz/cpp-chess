/*
Nom du fichier : pieces.hpp
Description : classes qui permettent de recevoir des evenements lorsqu'on appuie sur une piece
Auteurs : Malaurie St-Amour-Bilodeau, Zabiullah Shair Zaie et Julie Labbe
Groupe : 03
Date de remise : 9 mai 2021
*/
#ifndef PIECES_H
#define PIECES_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>

namespace Labels
{
    class Cavalier : public QLabel
    {
        Q_OBJECT
    public:
        explicit Cavalier(QWidget* parent = nullptr);

        void mousePressEvent(QMouseEvent* ev);

    signals:
        void Mouse_Pressed();

    public slots:

    };

    class Fou : public QLabel
    {
        Q_OBJECT
    public:
        explicit Fou(QWidget* parent = nullptr);

        void mousePressEvent(QMouseEvent* ev);

    signals:
        void Mouse_Pressed();

    public slots:

    };

    class Roi : public QLabel
    {
        Q_OBJECT
    public:
        explicit Roi(QWidget* parent = nullptr);

        void mousePressEvent(QMouseEvent* ev);

    signals:
        void Mouse_Pressed();

    public slots:

    };
}
#endif // PIECES_H
