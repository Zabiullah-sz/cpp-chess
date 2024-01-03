/*
Nom du fichier : board.hpp
Description : declaration de la classe Plateau
Auteurs : Malaurie St-Amour-Bilodeau, Zabiullah Shair Zaie et Julie Labbe
Groupe : 03
Date de remise : 22 avril 2021
*/

#ifndef PLATEAU_H
#define PLATEAU_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>
#include <QMouseEvent>
#include "echecs.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Plateau; }
QT_END_NAMESPACE

//using namespace Modele;

namespace Vue
{

    class Plateau : public QGraphicsView
    {
        Q_OBJECT

    public:
        Plateau(Modele::Echecs e, QWidget* parent = 0);
        ~Plateau();

        void dessinerEchiquier();
        void demarrerPartie(int posQt);
        void mousePressEvent(QMouseEvent* ev);

        int x = 9, y = 9;
        QLabel* pieceADeplacer;

    private slots:
        void Mouse_Pressed_NCavalier();
        void Mouse_Pressed_BCavalier();

        void Mouse_Pressed_NFou();
        void Mouse_Pressed_BFou();

        void Mouse_Pressed_NRoi();
        void Mouse_Pressed_BRoi();

        void on_boutonPosition1_clicked();
        void on_boutonPosition2_clicked();
        void on_boutonPosition3_clicked();

    private:
        Ui::Plateau* ui;
        QGraphicsScene* scene;
        Modele::Echecs echecs;
    };
}
#endif // PLATEAU_H