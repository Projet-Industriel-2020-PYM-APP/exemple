#include "Salle.hpp"


const void Salle::afficher()
{
	cout<<"Salle "<<s_nom<<" : "<<endl;
	cout<<"  dimensions : "<<s_largeur<<" X "<<s_longueur<<endl;
	cout<<"  capacite : "<<s_capacite<<endl;
}


const void SalleCours::afficher()
{
	Salle::afficher();
	if (s_amphi) 
	{
		cout<<"  Cette salle est un amphi"<<endl;
	}
}

const void SalleInfo::afficher()
{
	Salle::afficher();
	if (s_postes) 
	{
		cout<<"  Cette salle contient "<<s_postes<<" de travail"<<endl;
	}
	else
	{
		cout<<"  Cette salle est destinee aux ordinateurs portables"<<endl;
	}
}

void ListeSalles::ajouter(Salle* salle)
{
	bool existe = 0;
	for (int i=0; i<l_compteur; i++)
	{
		if (salle->getNom()==l_tableau[i]->getNom())
		{
			existe = 1;
		}
	}
	if (!existe)
	{
		l_compteur++;
		l_tableau[l_compteur] = salle;
	}
}
	
	
		
		
		
		