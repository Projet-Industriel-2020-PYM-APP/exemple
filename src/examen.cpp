#include "examen.h"
using namespace std;

/*void MonException::afficher(std::ostream& flux) const
{
	flux << m_message << endl << endl;
}

ostream& operator<<(ostream& flux, MonException const& er)
{
	er.afficher(flux);
	return flux;
}*/

void Salle::afficher() const
{
	cout << "Nom de la classe : " << m_nom << endl;
	cout << "Longueur : " << m_longueur << endl;
	cout << "Largeur : " << m_largeur << endl;
	cout << "Nombre de places : " << m_nbPlaces << endl << endl;
}

bool Salle::estEgala(Salle const& s) const
{
	return ((m_nom == s.m_nom) && (m_longueur == s.m_longueur) && (m_largeur == s.m_largeur) && (m_nbPlaces == s.m_nbPlaces));
}

bool Salle::estInferieura(Salle const& s) const
{
	return (((m_longueur == s.m_longueur) && (m_largeur < s.m_largeur)) || ((m_largeur == s.m_largeur) && (m_longueur < s.m_longueur)));
}

bool Salle::estSuperieura(Salle const& s) const
{
	return (((m_longueur == s.m_longueur) && (m_largeur > s.m_largeur)) || ((m_largeur == s.m_largeur) && (m_longueur > s.m_longueur)));
}

bool operator==(Salle const& s1, Salle const& s2)
{
	return s1.estEgala(s2);
}

bool operator!=(Salle const& s1, Salle const& s2)
{
	return !s1.estEgala(s2);
}

bool operator<(Salle const& s1, Salle const& s2)
{
	return s1.estInferieura(s2);
}

bool operator>=(Salle const& s1, Salle const& s2)
{
	return !s1.estInferieura(s2);
}

bool operator>(Salle const& s1, Salle const& s2)
{
	return s1.estSuperieura(s2);
}

bool operator<=(Salle const& s1, Salle const& s2)
{
	return !s1.estSuperieura(s2);
}

void SalleCours::afficher() const
{
	if(m_amphi)
		cout << "Il s'agit d'une salle d'amphi" << endl;
	else
		cout << "Il s'agit d'une salle de cours classique" << endl;
	Salle::afficher();
}

void SalleInfo::afficher() const
{
	if(m_nbPostesInformatiques)
	{
		cout << "Il s'agit d'une salle avec des postes fixes et il y a " << m_nbPostesInformatiques << " ordinateurs fixes" << endl; 
	}
	else
	{
		cout << "Il s'agit d'une salle reservee aux ordinateurs portables" << endl;
	}
	Salle::afficher();
}

ListeClasses::ListeClasses(long nbSallesAjoutees): m_nbSallesAjoutees(nbSallesAjoutees)
{
	for (int i(0); i < m_nbSallesAjoutees; i++)
		m_Salles[i] = new Salle("Salle vide", 0, 0, 0);
}

void ListeClasses::ajouter(Salle* salle)
{
	if (m_nbSallesAjoutees < NB_MAX_SALLE && chercherSalle(salle->getNom()) == 0)
	{
		m_Salles[m_nbSallesAjoutees] = salle;
		m_nbSallesAjoutees++;
	}	
}

void ListeClasses::afficher() const
{
	for (int i(0); i < m_nbSallesAjoutees; i++)
		m_Salles[i]->afficher();
}

Salle* ListeClasses::chercherSalle(std::string const& nom) const
{
	for (int i(0); i < m_nbSallesAjoutees; i++)
	{
		if (m_Salles[i]->getNom() == nom)
			return m_Salles[i];
	}		
	
	return 0;
}

long ListeClasses::chercherIndiceSalle(std::string const& nom) const
{
	for (int i(0); i < m_nbSallesAjoutees; i++)
	{
		if (m_Salles[i]->getNom() == nom)
			return i;
	}		
	
	return -1;
}

ListeClasses ListeClasses::operator+(ListeClasses const& c) const
{
	ListeClasses resultat;
	
	for (int i(0); i < m_nbSallesAjoutees; i++)
		resultat.ajouter(m_Salles[i]);
	
	for (int i(0); i < c.m_nbSallesAjoutees; i++)
		resultat.ajouter(c.m_Salles[i]);
	
	return resultat;
}

/*Salle* ListeClasses::getSalle_s(long indice) const
{
	if ((indice < 0) && (indice > m_nbSallesAjoutees))
	{
		ostringstream flux;
		flux << "L'entier " << indice << "ne peut pas etre un indice"; 
		throw MonException(flux.str());
	}
	else
	{
		return m_Salles[indice];
	}
}*/

Batiment::Batiment(ListeClasses const& liste)
{
	for (int i(0); i < liste.getNbSalles(); i++)
	{
		m_liste.ajouter(liste.getSalle(i));
		m_tableau[i].m_estPositionnee = false;
		m_tableau[i].m_x = 0.0;
		m_tableau[i].m_y = 0.0;
	}
}

void Batiment::positionner(int indiceSalle, long x, long y)
{
	if(m_tableau[indiceSalle].m_estPositionnee)
		cout << "Salle deja positionnee" << endl << endl;
	else if (m_liste.getSalle(indiceSalle) == 0)
		cout << "salle inexistante" << endl << endl;
	else
	{
		m_tableau[indiceSalle].m_estPositionnee = true;
		m_tableau[indiceSalle].m_x = x;
		m_tableau[indiceSalle].m_y = y;
	}
}

void Batiment::afficher() const
{
	for (int i(0); i < m_liste.getNbSalles(); i++)
	{
		Salle* temp = m_liste.getSalle(i);
		temp->afficher();
		if (m_tableau[i].m_estPositionnee)
		{
			cout << "Coordonnees de la salle : (" << m_tableau[i].m_x << "," << m_tableau[i].m_y << endl << endl;
		}
	}
}

void Batiment::positionner(string const& nom, long x, long y)
{
	if(m_tableau[m_liste.chercherIndiceSalle(nom)].m_estPositionnee)
		cout << "Salle deja positionnee" << endl << endl;
	else if (m_liste.chercherSalle(nom) == 0)
		cout << "salle inexistante" << endl << endl;
	else
	{
		m_tableau[m_liste.chercherIndiceSalle(nom)].m_estPositionnee = true;
		m_tableau[m_liste.chercherIndiceSalle(nom)].m_x = x;
		m_tableau[m_liste.chercherIndiceSalle(nom)].m_y = y;
	}
}







