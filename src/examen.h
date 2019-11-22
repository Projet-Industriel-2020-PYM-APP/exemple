#pragma once 

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

const int NB_MAX_SALLE = 100;

/*class MonException
{
	public:
		MonException(std::string message): m_message(message) {}
		void afficher(std::ostream& flux) const;
		
		friend std::ostream& operator<<(std::ostream& flux, MonException const& er);
	private:
		std::string m_message;
};*/

class Salle
{
	public:
		Salle(std::string nom, long longueur, long largeur, long nbPlaces): m_nom(nom), m_longueur(longueur), m_largeur(largeur), m_nbPlaces(nbPlaces) {}
		virtual void afficher() const;
		std::string getNom() const {return m_nom;}
		long getLongueur() const {return m_longueur;}
		long getLargeur() const {return m_largeur;}
		long getNbPlaces() const {return m_nbPlaces;}
		bool estEgala(Salle const& s) const;
		bool estInferieura(Salle const& s) const;
		bool estSuperieura(Salle const& s) const;
		
		friend bool operator==(Salle const& s1, Salle const& s2);
		friend bool operator!=(Salle const& s1, Salle const& s2);
		friend bool operator<(Salle const& s1, Salle const& s2);
		friend bool operator>=(Salle const& s1, Salle const& s2);
		friend bool operator>(Salle const& s1, Salle const& s2);
		friend bool operator<=(Salle const& s1, Salle const& s2);
		
	private:
		std::string m_nom;
		long m_longueur;
		long m_largeur;
		long m_nbPlaces;
};

class SalleCours: public Salle
{
	public:
		SalleCours(std::string nom, long longueur, long largeur, long nbPlaces, bool amphi): Salle(nom, longueur, largeur, nbPlaces), m_amphi(amphi) {}
		void afficher() const;
	private:
		bool m_amphi;
};

class SalleInfo: public Salle
{
	public:
		SalleInfo(std::string nom, long longueur, long largeur, long nbPlaces, long nbPostesInformatiques = 0): Salle(nom, longueur, largeur, nbPlaces), m_nbPostesInformatiques(nbPostesInformatiques) {}
		void afficher() const;
		
	private:
		long m_nbPostesInformatiques;
};

class ListeClasses
{
	public:
		ListeClasses(long nbSallesAjoutees = 0);
		void ajouter(Salle* salle);
		long getNbSalles() const {return m_nbSallesAjoutees + 1;}
		Salle* getSalle(long indice) const {return m_Salles[indice];}
		void afficher() const;
		Salle* chercherSalle(std::string const& nom) const;
		long chercherIndiceSalle(std::string const& nom) const;
		ListeClasses operator+(ListeClasses const& c) const;
		//Salle* getSalle_s(long indice) const;
		 
	private:
		Salle* m_Salles[NB_MAX_SALLE];
		long m_nbSallesAjoutees;
};

struct PosSalle
{
	bool m_estPositionnee;
	float m_x;
	float m_y;
};

class Batiment
{
	public:
		Batiment(ListeClasses const& liste);
		void positionner(int indiceSalle, long x, long y);
		void afficher() const;
		void positionner(std::string const& nom, long x, long y);
		
	private:
		ListeClasses m_liste;
		PosSalle m_tableau[NB_MAX_SALLE];
};

// maxime.agius@emse.fr A206

