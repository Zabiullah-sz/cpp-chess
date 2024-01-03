/*
Nom du fichier : echecs.cpp
Description : methodes des classes de echecs.hpp
Auteurs : Malaurie St-Amour-Bilodeau, Zabiullah Shair Zaie et Julie Labbe
Groupe : 03
Date de remise : 9 mai 2021
*/

#include "echecs.hpp"
#include <QDebug>

using namespace std;

namespace Modele
{
    /***Fonctions globales***/

    int signe(int valeur)
    {
        if (valeur >= 0) return 1;
        else return -1;
    }

    // Creer un roi, seulement deux rois sont crees
    Roi* creerRoi(int position, Couleur couleur)
    {
        try
        {
            return new Roi{ position, couleur };
        }
        catch (logic_error& r)
        {
            cout << "Deux rois maximum : " << r.what() << "\n";
        }
    }

    /*****Classe Echecs******/

    // Verifier si la position entree en parametre est deja occupee
    bool Echecs::estCaseLibre(int position)
    {
        if (echiquier[position] == nullptr) return true;
        else return false;
    }
    
    // Verifier si la mise a jour du vecteur a produit un changement
    bool Echecs::mettreAJourVecteur(int positionPiece, int positionDesiree)
    {
        vector<Piece*> ancienEchiquier = echiquier;
        if (echiquier[positionPiece] == nullptr) return false;
        echiquier[positionPiece]->deplacer(*this, positionDesiree, *trouverRoi(echiquier[positionPiece]->getCouleur()));

        // Le booleen indique si le deplacement s'est effectue ou non
        bool changement = echiquier != ancienEchiquier;

        if (changement) tourBlanc = !tourBlanc;
        return changement;
    }

    // Les 3 methodes suivantes sont pour reperer les pieces dans l'echiquier
    //[
    Roi* Echecs::trouverRoi(Couleur c)
    {
        for (int i = 0; i < TAILLE; i++)
        {
            if (dynamic_cast<Roi*>(echiquier[i]) != nullptr && echiquier[i]->getCouleur() == c)
                return dynamic_cast<Roi*>(echiquier[i]);
        }
        return nullptr;
    }

    Fou* Echecs::trouverFou(Couleur c)
    {
        for (int i = 0; i < TAILLE; i++)
        {
            if (dynamic_cast<Fou*>(echiquier[i]) != nullptr && echiquier[i]->getCouleur() == c)
                return dynamic_cast<Fou*>(echiquier[i]);
        }
        return nullptr;
    }

    Cavalier* Echecs::trouverCavalier(Couleur c)
    {
        for (int i = 0; i < TAILLE; i++)
        {
            if (dynamic_cast<Cavalier*>(echiquier[i]) != nullptr && echiquier[i]->getCouleur() == c)
                return dynamic_cast<Cavalier*>(echiquier[i]);
        }
        return nullptr;
    }
    //]

    /*****Classe Piece******/

    // Changer la position de la piece
    void Piece::deplacer(Echecs& echecs, int nouvellePosition, Roi& roi)
    {
        bool valide = true;

        // Verifier si le roi est en echecs
        for (Piece* piece : echecs.echiquier)
            if (piece != nullptr && roi.estEnEchec(echecs, *piece))
                valide = false;

        // Verifier que le deplacement permet que le roi ne soit plus en echecs
        int tempPos = position;
        Echecs temp;
        temp.echiquier = echecs.echiquier;
        temp.echiquier[position] = nullptr;
        position = nouvellePosition;
        temp.echiquier[nouvellePosition] = this;

        for (Piece* piece : echecs.echiquier)
        {
            if (piece != nullptr && roi.estEnEchec(temp, *piece))
            {
                valide = false;
                cout << "Le roi est en echec. ";
                break;
            }
            else valide = true;
        }

        position = tempPos;

        if (echecs.tourBlanc & (couleur == noir) | (!echecs.tourBlanc) & (couleur == blanc))
        {
            valide = false;
            cout << "C'est le tour de l'équipe adverse.\n";
        }
        else if (valide && estMouvementValide(echecs, nouvellePosition))
        {
            if (capturePossible(echecs, nouvellePosition)) delete echecs.echiquier[nouvellePosition];
            echecs.echiquier[position] = nullptr;
            position = nouvellePosition;
            echecs.echiquier[nouvellePosition] = this;
        }
        else cout << "Le mouvement n'est pas valide." << endl;
    }

    // Verifier que les pieces restent dans les limites du plateau
    bool Piece::estDansEchiquier(int nouvellePosition)
    {
        return !((nouvellePosition < LIMITE_INFERIEURE) | (nouvellePosition > LIMITE_SUPERIEURE));
    }

    // Verifier que la piece sur la case nouvelle position est de l'equipe adverse
    bool Piece::capturePossible(Echecs& echecs, int nouvellePosition)
    {
        return !(echecs.estCaseLibre(nouvellePosition)) &&
            echecs.echiquier[nouvellePosition]->getCouleur() != echecs.echiquier[position]->getCouleur();
    }

    /*****Classe Cavalier******/

    // Verifier que le cavalier se deplace en L
    bool Cavalier::estMouvementValide(Echecs& echecs, int nouvellePosition)
    {
        // La piece peut seulement capturer une piece de l'equipe adverse.
        if (!(Piece::capturePossible(echecs, nouvellePosition)) & !echecs.estCaseLibre(nouvellePosition)) return false;

        int deplacement = nouvellePosition - position;
        deplacement = abs(deplacement);

        bool estMouvementEnL = ((abs(deplacement) == deplacementsEnL[0]) || (abs(deplacement) == deplacementsEnL[1]) ||
            (abs(deplacement) == deplacementsEnL[2]) || (abs(deplacement) == deplacementsEnL[3]));

        bool changementLigne = ((nouvellePosition / VERTICAL) != (position / VERTICAL));

        //vérifier que les pieces ne sortent pas de l'échiquier
        bool estDansEchiquier = Piece::estDansEchiquier(nouvellePosition);
        //if (position == nouvellePosition) return false;

        return (estMouvementEnL & estDansEchiquier & changementLigne);
    }

    /*****Classe Fou******/

    // Verifier que le fou se deplace en diagonale
    bool Fou::estMouvementValide(Echecs& echecs, int nouvellePosition)
    {
        // La piece peut seulement capturer une piece de l'equipe adverse.
        if (!(Piece::capturePossible(echecs, nouvellePosition)) & !echecs.estCaseLibre(nouvellePosition)) return false;

        //la verification en diagonale est faite en mouvement 2D
        int nouvelleLigne = (nouvellePosition) / TAILLE_COTE;
        int nouvelleColonne = (nouvellePosition) % TAILLE_COTE;

        int ligne = (position) / TAILLE_COTE;
        int colonne = (position) % TAILLE_COTE;

        int deplacementLigne = nouvelleLigne - ligne;
        int deplacementColonne = nouvelleColonne - colonne;

        bool estDiagonal = (abs(deplacementLigne) == abs(deplacementColonne));

        // verifier que les pieces ne sortent pas de l'echiquier
        bool estDansEchiquier = Piece::estDansEchiquier(nouvellePosition);

        if (!estDiagonal | !estDansEchiquier | (nouvellePosition == position)) return false;

        // verifier qu'il n'y a pas de pieces sur son chemin
        int deplacement = nouvellePosition - position;

        int ajout;
        if (abs(deplacement) % DIAGONAL1 == 0) ajout = DIAGONAL1 * signe(deplacement);
        else ajout = DIAGONAL2 * signe(deplacement);

        for (int i = position + ajout; i != nouvellePosition; i += ajout)
            if (!(echecs.estCaseLibre(i))) return false;
        return true;
    }

    /*****Classe Roi******/

    // Verifier que le roi se deplace d'une case
    bool Roi::estMouvementValide(Echecs& echecs, int nouvellePosition)
    {
        // La piece peut seulement capturer une piece de l'equipe adverse.
        if (!(Piece::capturePossible(echecs, nouvellePosition)) & !echecs.estCaseLibre(nouvellePosition)) return false;

        if (position == nouvellePosition)
            return false;

        // verifier que les pieces ne sortent pas de l'echiquier
        bool estDansEchiquier = Piece::estDansEchiquier(nouvellePosition);

        int deplacement = abs(nouvellePosition - position);
        return (((deplacement == HORIZONTAL) | (deplacement == VERTICAL) | (deplacement == DIAGONAL1) | (deplacement == DIAGONAL2)) & estDansEchiquier);
    }

    // Verifier si le roi est en échec
    bool Roi::estEnEchec(Echecs& echecs, Piece& piece)
    {
        if (couleur != piece.getCouleur())
            return piece.estMouvementValide(echecs, position);
        else
            return false;
    }
}