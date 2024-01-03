/*
Nom du fichier : main.cpp
Description : main pour le jeu d'echecs
Auteurs : Malaurie St-Amour-Bilodeau, Zabiullah Shair Zaie et Julie Labbe
Groupe : 03
Date de remise : 9 mai 2021
*/
#include "echecs.hpp"
#include "plateau.hpp"

#include <QApplication>

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette ent�te si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif


void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par d�faut.

	// cdbg.setTee(&clog);  // D�commenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du d�bogueur.

	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un r�sultat de test.
#endif
//NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main apr�s l'appel � cette fonction puisqu'il ex�cute uniquement les tests Google Test dans l'appel ci-dessus.
}

int main(int argc, char* argv[])
{
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	QApplication app(argc, argv);
	initialiserBibliothequeCours(argc, argv);

	Modele::Echecs echecs;
	int posQt = 0;

	// Placer les pieces dans l'echiquier selon la position 0
	echecs.echiquier[Modele::posCB[posQt]] = new Modele::Cavalier(Modele::posCB[posQt], Modele::blanc);
	echecs.echiquier[Modele::posCN[posQt]] = new Modele::Cavalier(Modele::posCN[posQt], Modele::noir);
	echecs.echiquier[Modele::posFB[posQt]] = new Modele::Fou(Modele::posFB[posQt], Modele::blanc);
	echecs.echiquier[Modele::posFN[posQt]] = new Modele::Fou(Modele::posFN[posQt], Modele::noir);
	echecs.echiquier[Modele::posRB[posQt]] = Modele::creerRoi(Modele::posRB[posQt], Modele::blanc);
	echecs.echiquier[Modele::posRN[posQt]] = Modele::creerRoi(Modele::posRN[posQt], Modele::noir);

	Vue::Plateau p(echecs);
	p.show();

	return app.exec();
}
