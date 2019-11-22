#include "examen.h"
using namespace std;


void lireFichier(string const& fichierSource, ListeClasses* liste);

int main()
{
	/*Salle s1("E001", 15, 12, 35);
	s1.afficher();
		
	cout << s1.getNom() << endl;
	cout << s1.getLongueur() << endl;
	cout << s1.getLargeur() << endl;
	cout << s1.getNbPlaces() << endl << endl;
		
	Salle s2("E002", 15, 12, 35);
	Salle s3("E001", 15, 12, 35);
		
	if(s1 == s2)
		cout << "salle egale" << endl << endl;
	else
		cout << "salle differente" << endl << endl;
		
	if(s1 == s3)
		cout << "salle egale" << endl << endl;
	else
		cout << "salle differente" << endl << endl;
		
	if(s1 <= s2)
		cout << "salle egale" << endl << endl;
	else
			cout << "salle differente" << endl << endl;
		
	if(s1 < s2)
		cout << "salle egale" << endl << endl;
	else
		cout << "salle differente" << endl << endl;
			
	cout << "///////////////////////////////Heritage//////////////////////" << endl << endl;

	SalleCours sC("C004", 17, 15, 39, true);
	SalleCours sC2("C005", 17, 15, 39, false);
	SalleInfo sI("A001", 14, 4, 7);	
	SalleInfo sI2("A002", 4, 44, 75, 7);	
	
	Salle* sP1(&sC);
	Salle* sP2(&sI);
	Salle* sP3(&sI2);
	Salle* sP4(&sC2);
	
	sP1->afficher();
	sP2->afficher();
	sP3->afficher();
	sP4->afficher();
	
	cout << "/////////////////////Liste chainee////////////////////////////" << endl << endl;

	cout << "///////////////////Liste" << endl << endl;
	
	ListeClasses lc;
	lc.ajouter(sP1);
	lc.ajouter(sP2);
	lc.ajouter(sP3);
	lc.ajouter(sP4);
	lc.ajouter(&s1);
	lc.ajouter(&s2);
	lc.ajouter(&s3);
	
	cout << lc.getNbSalles() << endl << endl;
	
	Salle* sP5 = lc.getSalle(0);
	sP5->afficher();
	
	lc.afficher();
	
	Salle* sP6 = lc.chercherSalle("C004");
	sP6->afficher();
	
	Salle* sP7 = lc.chercherSalle("A102");
	if(sP7 == 0)
		cout << "Pas de salle" << endl << endl;
	
	cout << lc.chercherIndiceSalle("C004") << endl;
	cout << lc.chercherIndiceSalle("A102") << endl;
	
	cout << "///////////////////Liste2" << endl << endl;
	
	ListeClasses lc2;
	lc2.ajouter(sP1);
	lc2.ajouter(sP2);
	lc2.ajouter(sP3);
	lc2.ajouter(sP4);
	lc2.ajouter(&s1);
	lc2.ajouter(&s2);
	lc2.ajouter(&s3);
	
	cout << lc2.getNbSalles() << endl << endl;
	
	Salle* sP8 = lc2.getSalle(0);
	sP8->afficher();
	
	lc2.afficher();
	
	Salle* sP9 = lc2.chercherSalle("C004");
	sP9->afficher();
	
	Salle* sP10 = lc.chercherSalle("A102");
	if(sP10 == 0)
		cout << "Pas de salle" << endl << endl;
	
	cout << lc2.chercherIndiceSalle("C004") << endl;
	cout << lc2.chercherIndiceSalle("A102") << endl;
	
	cout << "/////////////////concatenation" << endl << endl;
	
	ListeClasses lc3 = lc + lc2;
	lc3.afficher();*/

	ListeClasses lc4;
	lireFichier("Salle.txt", &lc4);
	lc4.afficher();

	/*Batiment b(lc4);
	b.positionner(0, 3.1, 4.7);
	b.positionner("E106", 2.2, 7.6);
	b.afficher();*/

	return 0;
}

void lireFichier(string const& fichierSource, ListeClasses* liste)
{
	
	ifstream input(fichierSource.c_str());
	if(input)
	{
		while(!input.eof())
		{
			bool amphi;
			string nom, typeSalle; 
			long longueur, largeur, capacite, nbPostes;
			
			input >> typeSalle;
			
			if (typeSalle == "AMPHI")
				amphi = true;
			else
				amphi = false;
			
			input >> nom >> longueur >> largeur >> capacite;
			
			if (typeSalle == "SALLE_INFO")
				input >> nbPostes;
				
			if(!input.eof())
			{
			
				if (typeSalle == "SALLE_INFO")
					liste->ajouter(new SalleInfo(nom, longueur, largeur, capacite, nbPostes)); 
				else
					liste->ajouter(new SalleCours(nom, longueur, largeur, capacite, amphi));
			}
		}
	}
	else
	{
		cout << "Fichier inexistant" << endl;
	}
}
