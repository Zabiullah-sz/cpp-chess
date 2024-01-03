/*
Nom du fichier : ui_board.h
Description : creation de l'interface graphique du jeu d'echecs
Auteurs : Malaurie St-Amour-Bilodeau, Zabiullah Shair Zaie et Julie Labbe
Groupe : 03
Date de remise : 9 mai 2021
*/
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "pieces.hpp"
#include <QPixmap>

QT_BEGIN_NAMESPACE

class Ui_Plateau
{
public:
    Labels::Cavalier* cavalierB;
    Labels::Roi* roiN;
    Labels::Fou* fouB;
    Labels::Roi* roiB;
    Labels::Cavalier* cavalierN;
    Labels::Fou* fouN;
    QLabel* labelChoixPosition;
    QWidget* layoutWidget;
    QHBoxLayout* horizontalLayout;
    QPushButton* boutonPosition1;
    QPushButton* boutonPosition2;
    QPushButton* boutonPosition3;

    std::pair<int, int> determinerPositionPiece(Modele::Echecs& echecs, char piece, Modele::Couleur c)
    {
        int position = -1;
        switch (piece)
        {
        case 'r':
            position = echecs.trouverRoi(c)->getPosition();
            break;
        case 'f':
            position = echecs.trouverFou(c)->getPosition();
            break;
        case 'c':
            position = echecs.trouverCavalier(c)->getPosition();
            break;
        default:
            break;
        }
        return std::make_pair((position % 8) * 100, (position / 8) * 100);
    }

    void setupUi(QWidget* Plateau, Modele::Echecs& echecs)
    {
        if (Plateau->objectName().isEmpty())
            Plateau->setObjectName(QString::fromUtf8("Plateau"));
        Plateau->resize(812, 829);
        Plateau->setMouseTracking(true);

        cavalierB = new Labels::Cavalier(Plateau);
        cavalierB->setObjectName(QString::fromUtf8("cavalierB"));
        std::pair<int, int> posCB = determinerPositionPiece(echecs, 'c', Modele::blanc);
        cavalierB->setGeometry(QRect(posCB.first, posCB.second, 100, 100));
        cavalierB->setMouseTracking(true);
        cavalierB->setAlignment(Qt::AlignCenter);

        roiN = new Labels::Roi(Plateau);
        roiN->setObjectName(QString::fromUtf8("roiN"));
        std::pair<int, int> posRN = determinerPositionPiece(echecs, 'r', Modele::noir);
        roiN->setGeometry(QRect(posRN.first, posRN.second, 100, 100));
        roiN->setMouseTracking(true);
        roiN->setAlignment(Qt::AlignCenter);

        fouB = new Labels::Fou(Plateau);
        fouB->setObjectName(QString::fromUtf8("fouB"));
        std::pair<int, int> posFB = determinerPositionPiece(echecs, 'f', Modele::blanc);
        fouB->setGeometry(QRect(posFB.first, posFB.second, 100, 100));
        fouB->setMouseTracking(true);
        fouB->setAlignment(Qt::AlignCenter);

        roiB = new Labels::Roi(Plateau);
        roiB->setObjectName(QString::fromUtf8("roiB"));
        std::pair<int, int> posRB = determinerPositionPiece(echecs, 'r', Modele::blanc);
        roiB->setGeometry(QRect(posRB.first, posRB.second, 100, 100));
        roiB->setMouseTracking(true);
        roiB->setAlignment(Qt::AlignCenter);

        cavalierN = new Labels::Cavalier(Plateau);
        cavalierN->setObjectName(QString::fromUtf8("cavalierN"));
        std::pair<int, int> posCN = determinerPositionPiece(echecs, 'c', Modele::noir);
        cavalierN->setGeometry(QRect(posCN.first, posCN.second, 100, 100));
        cavalierN->setMouseTracking(true);
        cavalierN->setAlignment(Qt::AlignCenter);

        fouN = new Labels::Fou(Plateau);
        fouN->setObjectName(QString::fromUtf8("fouN"));
        std::pair<int, int> posFN = determinerPositionPiece(echecs, 'f', Modele::noir);
        fouN->setGeometry(QRect(posFN.first, posFN.second, 100, 100));
        fouN->setMouseTracking(true);
        fouN->setAlignment(Qt::AlignCenter);

        // Choix de debut de partie
        labelChoixPosition = new QLabel(Plateau);
        labelChoixPosition->setObjectName(QString::fromUtf8("labelChoixPosition"));
        labelChoixPosition->setGeometry(QRect(295, 820, 251, 20));
        layoutWidget = new QWidget(Plateau);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(260, 850, 295, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        boutonPosition1 = new QPushButton(layoutWidget);
        boutonPosition1->setObjectName(QString::fromUtf8("boutonPosition1"));

        horizontalLayout->addWidget(boutonPosition1);

        boutonPosition2 = new QPushButton(layoutWidget);
        boutonPosition2->setObjectName(QString::fromUtf8("boutonPosition2"));

        horizontalLayout->addWidget(boutonPosition2);

        boutonPosition3 = new QPushButton(layoutWidget);
        boutonPosition3->setObjectName(QString::fromUtf8("boutonPosition3"));

        horizontalLayout->addWidget(boutonPosition3);

        retranslateUi(Plateau);

        QMetaObject::connectSlotsByName(Plateau);
    } // setupUi

    void retranslateUi(QWidget* Plateau)
    {
        Plateau->setWindowTitle(QCoreApplication::translate("Jeu d'echecs", "Jeu d'echecs", nullptr));
        labelChoixPosition->setText(QCoreApplication::translate("Jeu d'echecs", "Veuillez choisir une position de d\303\251part:", nullptr));
        boutonPosition1->setText(QCoreApplication::translate("Jeu d'echecs", "Position 1", nullptr));
        boutonPosition2->setText(QCoreApplication::translate("Jeu d'echecs", "Position 2", nullptr));
        boutonPosition3->setText(QCoreApplication::translate("Jeu d'echecs", "Position 3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Plateau : public Ui_Plateau {};
} // namespace Ui

QT_END_NAMESPACE