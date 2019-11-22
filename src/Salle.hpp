#pragma once

#include <iostream>
#include <string>

const int NB_MAX_SALLES = 100;

using namespace std;

class Salle
{
	public : 
		Salle(string nom, int longueur, int largeur, int capacite):s_nom(nom), s_longueur(longueur), s_largeur(largeur), s_capacite(capacite) {}
		virtual const void afficher();
		const string getNom(){return s_nom;}
		const int getLongueur(){return s_longueur;}
		const int getLargeur(){return s_largeur;}
		const int getCapacite(){return s_capacite;}
		const bool operator< (const Salle& b){return (s_capacite<b.s_capacite);}
		const bool operator> (const Salle& b){return (s_capacite>b.s_capacite);}
		const bool operator== (const Salle& b){return (s_capacite==b.s_capacite);}
		 
	private :
		string s_nom;
		int s_longueur;
		int s_largeur;
		int s_capacite;
		
};

class SalleCours: public Salle
{
	public :
		SalleCours (string nom, int longueur, int largeur, int capacite, bool amphi): Salle(nom, longueur, largeur, capacite), s_amphi(amphi) {}
		const void afficher();
	
	
	private :
		bool s_amphi;
};

class SalleInfo: public Salle
{
	public :
		SalleInfo (string nom, int longueur, int largeur, int capacite, int postes = 0): Salle(nom, longueur, largeur, capacite), s_postes(postes) {}
		const void afficher();
	
	
	private :
		int s_postes;
};

class ListeSalles
{
	public :
		ListeSalles():l_compteur(0){}
		void ajouter(Salle* salle);
		
	
	private :
		Salle* l_tableau[NB_MAX_SALLES];
		int l_compteur;
		
};
		
	
	
	