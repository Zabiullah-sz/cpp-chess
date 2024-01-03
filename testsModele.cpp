/*
Nom du fichier : testsModele.cpp
Description : tests du modele pour le jeu d'echecs
Auteurs : Malaurie St-Amour-Bilodeau, Zabiullah Shair Zaie et Julie Labbe
Groupe : 03
Date de remise : 9 mai 2021
*/
#include "echecs.hpp"
using namespace Modele;

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

// Verifier les deplacements des pieces
TEST(Echecs, deplacements) {
	Echecs echecs;

	Roi* roiN = creerRoi(59, noir);
	Roi* roiB = creerRoi(3, blanc);
	Fou* fouN = new Fou(58, noir);
	Fou* fouB = new Fou(2, blanc);
	Cavalier* cavalierN = new Cavalier(57, noir);
	Cavalier* cavalierB = new Cavalier(1, blanc);

	echecs.echiquier[roiN->getPosition()] = roiN;
	echecs.echiquier[roiB->getPosition()] = roiB;
	echecs.echiquier[fouN->getPosition()] = fouN;
	echecs.echiquier[fouB->getPosition()] = fouB;
	echecs.echiquier[cavalierN->getPosition()] = cavalierN;
	echecs.echiquier[cavalierB->getPosition()] = cavalierB;

	EXPECT_EQ(echecs.mettreAJourVecteur(roiN->getPosition(), 60), false); // Commencer avec la mauvaise couleur
	EXPECT_EQ(echecs.mettreAJourVecteur(fouB->getPosition(), 11), true); // déplacement du fou valide
	EXPECT_EQ(echecs.mettreAJourVecteur(cavalierN->getPosition(), 51), true); // déplacement du cavalier valide
	EXPECT_EQ(echecs.mettreAJourVecteur(roiB->getPosition(), 4), true); // déplacement du roi valide
	EXPECT_EQ(echecs.mettreAJourVecteur(0, 2), false); // déplacer une pièce qui n'existe pas
	EXPECT_EQ(echecs.mettreAJourVecteur(cavalierN->getPosition(), 52), false); // déplacement invalide du cavalier
	for (auto piece : echecs.echiquier) if (piece != nullptr) delete piece;
}

// Verifier que les pieces sont retirees du plateau lorsqu'elles sont capturees
TEST(Echecs, capturePiece) {
	Echecs echecs;

	Roi* roiN = creerRoi(59, noir);
	Roi* roiB = creerRoi(3, blanc);
	Fou* fouN = new Fou(7, noir);
	Fou* fouB = new Fou(56, blanc);

	echecs.echiquier[roiN->getPosition()] = roiN;
	echecs.echiquier[roiB->getPosition()] = roiB;
	echecs.echiquier[fouN->getPosition()] = fouN;
	echecs.echiquier[fouB->getPosition()] = fouB;

	echecs.mettreAJourVecteur(fouB->getPosition(), fouN->getPosition());

	int nPieces = 0;
	for (auto piece : echecs.echiquier)
		if (piece != nullptr)
		{
			nPieces++;
			delete piece;
		}

	EXPECT_EQ(nPieces, 3);
}

// Verifier qu'il faut empecher la mise en echecs pour continuer la partie
TEST(Echecs, roiEnEchec) {
	Echecs echecs;

	Roi* roiN = creerRoi(61, noir);
	Roi* roiB = creerRoi(0, blanc);
	Fou* fouN = new Fou(18, noir);
	Fou* fouB = new Fou(2, blanc);

	echecs.echiquier[roiN->getPosition()] = roiN;
	echecs.echiquier[roiB->getPosition()] = roiB;
	echecs.echiquier[fouN->getPosition()] = fouN;
	echecs.echiquier[fouB->getPosition()] = fouB;

	EXPECT_EQ(echecs.mettreAJourVecteur(fouB->getPosition(), 11), false);
	EXPECT_EQ(echecs.mettreAJourVecteur(fouB->getPosition(), 9), true);
	for (auto piece : echecs.echiquier) if (piece != nullptr) delete piece;
}

// Verifier qu'il ne peut pas y avoir plus de 2 rois
TEST(Echecs, 3Rois) {
	Roi* roiN = creerRoi(61, noir);
	Roi* roiB = creerRoi(0, blanc);
	Roi* roi3 = creerRoi(1, noir);
	EXPECT_EQ(Roi::getCompteur(), 2);
	delete roiN;
	delete roiB;
}

// Verifier qu'il est possible de trouver les pieces dans le plateau lorsqu'elles existent
TEST(Echecs, trouverPieces) {
	Echecs echecs;

	Roi* roiN = creerRoi(1, noir);
	Fou* fouN = new Fou(3, noir);
	Cavalier* cavalierN = new Cavalier(5, noir);

	echecs.echiquier[roiN->getPosition()] = roiN;
	echecs.echiquier[fouN->getPosition()] = fouN;
	echecs.echiquier[cavalierN->getPosition()] = cavalierN;

	EXPECT_EQ(echecs.trouverCavalier(noir)->getPosition(), 5);
	EXPECT_EQ(echecs.trouverCavalier(blanc), nullptr);
	EXPECT_EQ(echecs.trouverFou(noir)->getPosition(), 3);
	EXPECT_EQ(echecs.trouverFou(blanc), nullptr);
	EXPECT_EQ(echecs.trouverRoi(noir)->getPosition(), 1);
	EXPECT_EQ(echecs.trouverRoi(blanc), nullptr);
	for (auto piece : echecs.echiquier) if (piece != nullptr) delete piece;
}

#endif