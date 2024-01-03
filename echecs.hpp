/*
Nom du fichier : echecs.hpp
Description : declaration des classes Piece, Cavalier, Fou et Roi
Auteurs : Malaurie St-Amour-Bilodeau, Zabiullah Shair Zaie et Julie Labbe
Groupe : 03
Date de remise : 9 mai 2021
*/
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <vector>
#include <stdexcept>

namespace Modele
{
    class Piece;
    class Cavalier;
    class Fou;
    class Roi;

    enum Couleur { blanc, noir };

    /**Constantes globales**/
    const int TAILLE = 64;
    const int TAILLE_COTE = 8;
    const int NOMBRE_MAX_ROIS = 2;
    const int LIMITE_INFERIEURE = 0;
    const int LIMITE_SUPERIEURE = 63;
    const int deplacementsEnL[4] = { 6, 10, 15, 17 };
    const int HORIZONTAL = 1;
    const int VERTICAL = 8;
    const int DIAGONAL1 = 9;
    const int DIAGONAL2 = 7;
    const int nPosDifferentes = 3;
    const int posCB[nPosDifferentes] = { 1, 0, 7 };
    const int posCN[nPosDifferentes] = { 57, 56, 56 };
    const int posFB[nPosDifferentes] = { 2, 1, 6 };
    const int posFN[nPosDifferentes] = { 58, 57, 57 };
    const int posRB[nPosDifferentes] = { 3, 2, 5 };
    const int posRN[nPosDifferentes] = { 59, 58, 58 };

    // Fonctions globales
    int signe(int valeur);
    Roi* creerRoi(int position, Couleur couleur);

    /*********Echecs**********/
    class Echecs
    {
    public:
        std::vector<Piece*> echiquier; // attribut qui contient la position des pieces sur le plateau
        bool tourBlanc; // attribut qui s'assure que la bonne equipe joue

        Echecs()
        {
            std::vector <Piece*> nouvelEchiquier(TAILLE, nullptr);
            echiquier = nouvelEchiquier;
            tourBlanc = true;
        };

        void afficherEchiquier() const;
        bool estCaseLibre(int position);

        bool mettreAJourVecteur(int positionPiece, int positionDesiree);
        Roi* trouverRoi(Couleur c);
        Fou* trouverFou(Couleur c);
        Cavalier* trouverCavalier(Couleur c);
    };


    /*********Piece**********/
    class Piece
    {
    public:
        Piece() = default;
        Piece(int pos, Couleur c) : position(pos), couleur(c) {}
        virtual ~Piece() {};

        void deplacer(Echecs& echecs, int nouvellePosition, Roi& roi);
        bool estDansEchiquier(int nouvellePosition);
        bool capturePossible(Echecs& echecs, int nouvellePosition);
        virtual bool estMouvementValide(Echecs& echecs, int nouvellePosition) = 0;

        int getPosition() const { return position; }
        void setPosition(int nouvellePosition) { position = nouvellePosition; };
        Couleur getCouleur() const { return couleur; }

    protected:
        int position = 0;
        Couleur couleur;
    };


    /*********Cavalier**********/
    class Cavalier : public Piece
    {
    public:
        // herite du constructeur de la classe de base
        using Piece::Piece;
        bool estMouvementValide(Echecs& echecs, int nouvellePosition) override;
    };


    /*********Fou**********/
    class Fou : public Piece
    {
    public:
        // herite du constructeur de la classe de base
        using Piece::Piece;
        bool estMouvementValide(Echecs& echecs, int nouvellePosition) override;
    };

    /*********Roi**********/
    class Roi : public Piece
    {
    public:
        Roi() { verificationCompteur(); }
        Roi(int pos, Couleur c) : Piece::Piece(pos, c) { verificationCompteur(); }
        ~Roi() { compteur--; }
        bool estMouvementValide(Echecs& echecs, int nouvellePosition) override;
        bool estEnEchec(Echecs& echecs, Piece& piece);
        static int getCompteur() { return compteur; }

    private:
        static inline int compteur = 0;
        void verificationCompteur() // Cette methode permet de s'assurer qu'il n'y a pas plus de 2 rois
        {
            compteur++;
            if (compteur > NOMBRE_MAX_ROIS)
            {
                compteur--;
                throw std::logic_error("Il y a trop de rois.");
            }
        }
    };
}