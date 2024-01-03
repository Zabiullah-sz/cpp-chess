/*
Nom du fichier : plateau.cpp
Description : methodes de la classe Plateau
Auteurs : Malaurie St-Amour-Bilodeau, Zabiullah Shair Zaie et Julie Labbe
Groupe : 03
Date de remise : 9 mai 2021
*/

#include "plateau.hpp"
#include "ui_board.h"
#include "echecs.hpp"
#include "pieces.hpp"
#include <QDebug>
#include <QApplication>
#include <QTextEdit>


namespace Vue
{
    // Initialise le plateau et connecte les signaux et slots
    Plateau::Plateau(Modele::Echecs e, QWidget* parent)
        : QGraphicsView(parent),
        ui(new Ui::Plateau),
        echecs(e)
    {
        ui->setupUi(this, echecs);

        // Mettre les images sur les labels
        //[
        QPixmap pixRB("../ProjetTestQt/roiB.png");
        ui->roiB->setPixmap(pixRB.scaled(100, 100, Qt::KeepAspectRatio));
        ui->roiB->setScaledContents(true);

        QPixmap pixRN("../ProjetTestQt/roiN.png");
        ui->roiN->setPixmap(pixRN.scaled(100, 100, Qt::KeepAspectRatio));
        ui->roiN->setScaledContents(true);

        QPixmap pixCB("../ProjetTestQt/cavalierB.png");
        ui->cavalierB->setPixmap(pixCB.scaled(100, 100, Qt::KeepAspectRatio));
        ui->cavalierB->setScaledContents(true);

        QPixmap pixCN("../ProjetTestQt/cavalierN.png");
        ui->cavalierN->setPixmap(pixCN.scaled(100, 100, Qt::KeepAspectRatio));
        ui->cavalierN->setScaledContents(true);
        
        QPixmap pixFB("../ProjetTestQt/fouB.png");
        ui->fouB->setPixmap(pixFB.scaled(100, 100, Qt::KeepAspectRatio));
        ui->fouB->setScaledContents(true);
        
        QPixmap pixFN("../ProjetTestQt/fouN.png");
        ui->fouN->setPixmap(pixFN.scaled(100, 100, Qt::KeepAspectRatio));
        ui->fouN->setScaledContents(true);
        //]

        connect(ui->cavalierN, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed_NCavalier()));
        connect(ui->cavalierB, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed_BCavalier()));

        connect(ui->fouN, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed_NFou()));
        connect(ui->fouB, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed_BFou()));

        connect(ui->roiN, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed_NRoi()));
        connect(ui->roiB, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed_BRoi()));

        setFixedSize(805, 905);
        scene = new QGraphicsScene();
        scene->setSceneRect(0, 0, 800, 900);
        setScene(scene);
        dessinerEchiquier();
    }

    Plateau::~Plateau()
    {
        // Detruit les pieces dans le vecteur
        for (auto piece : echecs.echiquier) if (piece != nullptr) delete piece;
        delete ui;
        delete scene;
    }

    // Dessine la grille de l'echiquier
    void Plateau::dessinerEchiquier()
    {
        QBrush lightGrayBrush(QColorConstants::Svg::sandybrown, Qt::SolidPattern);
        QBrush blackBrush(QColorConstants::Svg::sienna, Qt::SolidPattern);
        QPen blackPen(Qt::black);

        int counter = 0;
        int x; //colonne
        int y; //ligne
        for (x = 0; x <= 7; x++) {
            counter++;
            for (y = 0; y <= 7; y++) {

                if (counter % 2 == 0) {
                    if (y % 2 == 0) scene->addRect(x * 100, y * 100, 100, 100, blackPen, blackBrush);
                    else scene->addRect(x * 100, y * 100, 100, 100, blackPen, lightGrayBrush);
                }

                //alterner les conditions
                else {
                    if (y % 2 == 0) scene->addRect(x * 100, y * 100, 100, 100, blackPen, lightGrayBrush);
                    else scene->addRect(x * 100, y * 100, 100, 100, blackPen, blackBrush);
                }
            }
        }
    }

    // Initialise le vecteur et l'interface graphique selon des positions predeterminees
    void Plateau::demarrerPartie(int posQt)
    {
        // On enleve les pieces du vecteur
        Modele::Roi* RB = echecs.trouverRoi(Modele::blanc);
        echecs.echiquier[RB->getPosition()] = nullptr;
        Modele::Roi* RN = echecs.trouverRoi(Modele::noir);
        echecs.echiquier[RN->getPosition()] = nullptr;
        
        Modele::Cavalier* CB = echecs.trouverCavalier(Modele::blanc);
        if (CB != nullptr) echecs.echiquier[CB->getPosition()] = nullptr;
        Modele::Cavalier* CN = echecs.trouverCavalier(Modele::noir);
        if (CN != nullptr) echecs.echiquier[CN->getPosition()] = nullptr;

        Modele::Fou* FB = echecs.trouverFou(Modele::blanc);
        if (FB != nullptr) echecs.echiquier[FB->getPosition()] = nullptr;
        Modele::Fou* FN = echecs.trouverFou(Modele::noir);
        if (FN != nullptr) echecs.echiquier[FN->getPosition()] = nullptr;
        
        // On remet le roi dans le vecteur, on change son attribut de position, on met son label au bon endroit
        echecs.echiquier[Modele::posRB[posQt]] = RB;
        RB->setPosition(Modele::posRB[posQt]);
        ui->roiB->move((Modele::posRB[posQt] % 8) * 100, (Modele::posRB[posQt] / 8) * 100);
        echecs.echiquier[Modele::posRN[posQt]] = RN;
        RN->setPosition(Modele::posRN[posQt]);
        ui->roiN->move((Modele::posRN[posQt] % 8) * 100, (Modele::posRN[posQt] / 8) * 100);

        // S'il existe deja une piece de ce type sur le board, on change son attribut de position, sinon on cree une nouvelle piece a la bonne position
        // On ajoute la piece au vecteur et on deplace son label au bon endroit
        if (CB != nullptr) CB->setPosition(Modele::posCB[posQt]);
        else
        {
            Modele::Cavalier* nouveauCavalierBlanc = new Modele::Cavalier(Modele::posCB[posQt], Modele::blanc);
            CB = nouveauCavalierBlanc;
            QPixmap pixCB("../ProjetTestQt/cavalierB.png");
            ui->cavalierB->setPixmap(pixCB.scaled(100, 100, Qt::KeepAspectRatio));
            ui->cavalierB->setScaledContents(true);
            ui->cavalierB->raise();
        }
        echecs.echiquier[Modele::posCB[posQt]] = CB;
        ui->cavalierB->move((Modele::posCB[posQt] % 8) * 100, (Modele::posCB[posQt] / 8) * 100);

        if (CN != nullptr) CN->setPosition(Modele::posCN[posQt]);
        else
        {
            Modele::Cavalier* nouveauCavalierNoir = new Modele::Cavalier(Modele::posCN[posQt], Modele::noir);
            CN = nouveauCavalierNoir;
            QPixmap pixCN("../ProjetTestQt/cavalierN.png");
            ui->cavalierN->setPixmap(pixCN.scaled(100, 100, Qt::KeepAspectRatio));
            ui->cavalierN->setScaledContents(true);
            ui->cavalierN->raise();
        }
        echecs.echiquier[Modele::posCN[posQt]] = CN;
        ui->cavalierN->move((Modele::posCN[posQt] % 8) * 100, (Modele::posCN[posQt] / 8) * 100);

        if (FB != nullptr) FB->setPosition(Modele::posFB[posQt]);
        else
        {
            Modele::Fou* nouveauFouBlanc = new Modele::Fou(Modele::posFB[posQt], Modele::blanc);
            FB = nouveauFouBlanc;
            QPixmap pixFB("../ProjetTestQt/fouB.png");
            ui->fouB->setPixmap(pixFB.scaled(100, 100, Qt::KeepAspectRatio));
            ui->fouB->setScaledContents(true);
            ui->fouB->raise();
        }
        echecs.echiquier[Modele::posFB[posQt]] = FB;
        ui->fouB->move((Modele::posFB[posQt] % 8) * 100, (Modele::posFB[posQt] / 8) * 100);

        if (FN != nullptr) FN->setPosition(Modele::posFN[posQt]);
        else
        {
            Modele::Fou* nouveauFouNoir = new Modele::Fou(Modele::posFN[posQt], Modele::noir);
            FN = nouveauFouNoir;
            QPixmap pixFN("../ProjetTestQt/fouN.png");
            ui->fouN->setPixmap(pixFN.scaled(100, 100, Qt::KeepAspectRatio));
            ui->fouN->setScaledContents(true);
            ui->fouN->raise();
        }
        echecs.echiquier[Modele::posFN[posQt]] = FN;
        ui->fouN->move((Modele::posFN[posQt] % 8) * 100, (Modele::posFN[posQt] / 8) * 100);

        // On reset le premier tour aux blancs
        echecs.tourBlanc = true;
    }


    //Deplacer la piece selectionnee a la position desiree si le deplacement est valide
    void Plateau::mousePressEvent(QMouseEvent* ev)
    {
        dessinerEchiquier();
        x = ev->x();                            // position de curseur
        y = ev->y();
        x -= x % 100;                           // rendre les positions divisible de 10
        y -= y % 100;

        if (pieceADeplacer != nullptr && y < 800)
        {
            int positionDesiree = (x / 100) + ((y * 8) / 100);          // conversion de la position de 2D en 1D
            int positionInitiale = (pieceADeplacer->pos().x() / 100) + ((pieceADeplacer->pos().y() * 8) / 100);

            if (echecs.mettreAJourVecteur(positionInitiale, positionDesiree))   // verifier le modele permet le deplacement
            {
                pieceADeplacer->move(x, y);
            }
            else {
                scene->addRect(x, y, 100, 100, QPen(Qt::black), QBrush(Qt::red));   // case rouge en cas de deplacement non-valide
            }
            pieceADeplacer = nullptr;                                           // deselectionner la piece
        }
    }

    // Selectionner le cavalier noir si aucune piece est selectionnee, sinon deplacer la piece selectionnee a la position desiree en capturant la piece adverse
    void Plateau::Mouse_Pressed_NCavalier()
    {
        dessinerEchiquier();

        QLabel* piece = ui->cavalierN;                          // piece a capturer
        x = piece->pos().x();
        y = piece->pos().y();

        if (pieceADeplacer == piece) {                              // la deuxime clique sur une meme piece doit le deselectionner
            pieceADeplacer = nullptr;
        }
        
        else if (pieceADeplacer != nullptr && y < 800)               // capturer la piece si une piece est deja selectionner
        {
            int positionDesiree = (x / 100) + ((y * 8) / 100);
            int positionInitiale = (pieceADeplacer->pos().x() / 100) + ((pieceADeplacer->pos().y() * 8) / 100);

            if (echecs.mettreAJourVecteur(positionInitiale, positionDesiree))
            {
                QLabel* child = dynamic_cast<QLabel*>(childAt(x, y));   // trouver la position de la piece a capturer
                child->clear();                                         // enlever l'image de la piece capturer
                child->lower();
                pieceADeplacer->move(x, y);
            }
            pieceADeplacer = nullptr;                                   // deselectionner la piece
        }

        else {
            pieceADeplacer = ui->cavalierN;                     //sélectionner la piece s'il n'y a pas de piece déjà selectionnee
            scene->addRect(x, y, 100, 100, QPen(Qt::black), QBrush(Qt::green));
        }
    }

    // Selectionner le cavalier blanc si aucune piece est selectionnee, sinon deplacer la piece selectionnee a la position desiree en capturant la piece adverse
    void Plateau::Mouse_Pressed_BCavalier()
    {
        dessinerEchiquier();

        QLabel* piece = ui->cavalierB;
        x = piece->pos().x();
        y = piece->pos().y();


        if (pieceADeplacer == piece) {
            pieceADeplacer = nullptr;
            dessinerEchiquier();
        }

        else if (pieceADeplacer != nullptr && y < 800)
        {
            int positionDesiree = (x / 100) + ((y * 8) / 100);
            int positionInitiale = (pieceADeplacer->pos().x() / 100) + ((pieceADeplacer->pos().y() * 8) / 100);

            if (echecs.mettreAJourVecteur(positionInitiale, positionDesiree))
            {
                QLabel* child = dynamic_cast<QLabel*>(childAt(x, y));
                child->clear();
                child->lower();
                pieceADeplacer->move(x, y);
            }
            pieceADeplacer = nullptr;
        }
        else {
            pieceADeplacer = ui->cavalierB;
            scene->addRect(x, y, 100, 100, QPen(Qt::black), QBrush(Qt::green));
        }
    }

    // Selectionner le fou noir si aucune piece est selectionnee, sinon deplacer la piece selectionnee a la position desiree en capturant la piece adverse
    void Plateau::Mouse_Pressed_NFou()
    {
        dessinerEchiquier();

        QLabel* piece = ui->fouN;
        x = piece->pos().x();
        y = piece->pos().y();


        if (pieceADeplacer == piece) {
            pieceADeplacer = nullptr;
            dessinerEchiquier();
        }


        else if (pieceADeplacer != nullptr && y < 800)
        {
            int positionDesiree = (x / 100) + ((y * 8) / 100);
            int positionInitiale = (pieceADeplacer->pos().x() / 100) + ((pieceADeplacer->pos().y() * 8) / 100);

            if (echecs.mettreAJourVecteur(positionInitiale, positionDesiree))
            {
                QLabel* child = dynamic_cast<QLabel*>(childAt(x, y));
                child->clear();
                child->lower();
                pieceADeplacer->move(x, y);
            }
            pieceADeplacer = nullptr;
        }
        else
        {
            pieceADeplacer = ui->fouN;
            scene->addRect(x, y, 100, 100, QPen(Qt::black), QBrush(Qt::green));
        }
    }

    // Selectionner le fou blanc si aucune piece est selectionnee, sinon deplacer la piece selectionnee a la position desiree en capturant la piece adverse
    void Plateau::Mouse_Pressed_BFou()
    {
        dessinerEchiquier();

        QLabel* piece = ui->fouB;
        x = piece->pos().x();
        y = piece->pos().y();


        if (pieceADeplacer == piece) {
            pieceADeplacer = nullptr;
            dessinerEchiquier();
        }

        else if (pieceADeplacer != nullptr && y < 800)
        {
            int positionDesiree = (x / 100) + ((y * 8) / 100);
            int positionInitiale = (pieceADeplacer->pos().x() / 100) + ((pieceADeplacer->pos().y() * 8) / 100);

            if (echecs.mettreAJourVecteur(positionInitiale, positionDesiree))
            {
                QLabel* child = dynamic_cast<QLabel*>(childAt(x, y));
                child->clear();
                child->lower();
                pieceADeplacer->move(x, y);
            }
            pieceADeplacer = nullptr;
        }
        else {
            pieceADeplacer = ui->fouB;
            scene->addRect(x, y, 100, 100, QPen(Qt::black), QBrush(Qt::green));
        }
    }

    // Selectionner le roi noir si aucune piece est selectionnee, sinon deplacer la piece selectionnee a la position desiree en capturant la piece adverse
    void Plateau::Mouse_Pressed_NRoi()
    {
        dessinerEchiquier();

        QLabel* piece = ui->roiN;
        x = piece->pos().x();
        y = piece->pos().y();


        if (pieceADeplacer == piece) {
            pieceADeplacer = nullptr;
            dessinerEchiquier();
        }


        else if (pieceADeplacer != nullptr && y < 800)
        {
            int positionDesiree = (x / 100) + ((y * 8) / 100);
            int positionInitiale = (pieceADeplacer->pos().x() / 100) + ((pieceADeplacer->pos().y() * 8) / 100);

            if (echecs.mettreAJourVecteur(positionInitiale, positionDesiree))
            {
                QLabel* child = dynamic_cast<QLabel*>(childAt(x, y));
                child->clear();
                child->lower();
                pieceADeplacer->move(x, y);
            }
            pieceADeplacer = nullptr;
        }
        else {
            pieceADeplacer = ui->roiN;
            scene->addRect(x, y, 100, 100, QPen(Qt::black), QBrush(Qt::green));
        }
    }

    // Selectionner le roi blanc si aucune piece est selectionnee, sinon deplacer la piece selectionnee a la position desiree en capturant la piece adverse
    void Plateau::Mouse_Pressed_BRoi()
    {
        dessinerEchiquier();

        QLabel* piece = ui->roiB;
        x = piece->pos().x();
        y = piece->pos().y();


        if (pieceADeplacer == piece) {
            pieceADeplacer = nullptr;
            dessinerEchiquier();
        }

        else if (pieceADeplacer != nullptr && y < 800)
        {
            int positionDesiree = (x / 100) + ((y * 8) / 100);
            int positionInitiale = (pieceADeplacer->pos().x() / 100) + ((pieceADeplacer->pos().y() * 8) / 100);

            if (echecs.mettreAJourVecteur(positionInitiale, positionDesiree))
            {
                QLabel* child = dynamic_cast<QLabel*>(childAt(x, y));
                child->clear();
                child->lower();
                pieceADeplacer->move(x, y);
            }
            pieceADeplacer = nullptr;
        }
        else {
            pieceADeplacer = ui->roiB;
            scene->addRect(x, y, 100, 100, QPen(Qt::black), QBrush(Qt::green));
        }
    }

    // Initialise une partie selon la premiere liste de positions des pieces
    void Plateau::on_boutonPosition1_clicked()
    {
        demarrerPartie(0);
    }

    // Initialise une partie selon la deuxieme liste de positions des pieces
    void Plateau::on_boutonPosition2_clicked()
    {
        demarrerPartie(1);
    }

    // Initialise une partie selon la troisieme liste de positions des pieces
    void Plateau::on_boutonPosition3_clicked()
    {
        demarrerPartie(2);
    }
}
