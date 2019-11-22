#include <exception>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const int NB_MAX_SALLES = 100;

class Salle {
 public:
  Salle(string s = "", float la = 0, float lo = 0, int c = 0)
      : nom(s), largeur(la), longueur(lo), capacite(c) {}
  virtual void affichage() const {
    cout << nom << " : largeur = " << largeur << "m, longueur = " << longueur
         << "m, " << capacite << " places" << endl;
  }
  string getNom() const { return nom; }
  float getLargeur() const { return largeur; }
  float getLongueur() const { return longueur; }
  int getCapacite() const { return capacite; }
  bool operator==(Salle S) { return capacite == S.capacite; }
  bool operator<(Salle S) { return capacite < S.capacite; }

 private:
  string nom;
  float largeur;
  float longueur;
  int capacite;
};

class SalleCours : public Salle {
 public:
  SalleCours(string s = "", float la = 0, float lo = 0, int c = 0, bool a = 0)
      : Salle(s, la, lo, c), amphi(a) {}
  void affichage() const {
    cout << getNom();
    if (amphi)
      cout << " : amphi , ";
    else
      cout << " : salle normale , ";
    cout << "largeur = " << getLargeur() << "m, longueur = " << getLongueur()
         << "m, " << getCapacite() << " places" << endl;
  }

 private:
  bool amphi;
};

class SalleInfo : public Salle {
 public:
  SalleInfo(string s = "", float la = 0, float lo = 0, int c = 0, int n = 0)
      : Salle(s, la, lo, c), nbpostes(n) {}
  void affichage() const {
    cout << getNom();
    if (nbpostes != 0)
      cout << " : " << nbpostes << " postes fixes , ";
    else
      cout << " : ordinateurs portables , ";
    cout << "largeur = " << getLargeur() << "m, longueur = " << getLongueur()
         << "m, " << getCapacite() << " places" << endl;
  }

 private:
  int nbpostes;
};

class ListeSalles {
 public:
  ListeSalles() : nbsalles(0) {}
  void ajouter(Salle* salle);
  Salle* getSalle(int indice) const { return liste[indice]; }
  Salle* getSalle_s(int indice) const;
  int getNbsalles() const { return nbsalles; }
  void affichage() const {
    for (int i = 0; i < nbsalles; i++) liste[i]->affichage();
  }
  Salle* chercherSalle(const string& s) const;
  int chercherIndiceSalle(const string& s) const;
  ListeSalles operator+(const ListeSalles& L) const;

 private:
  Salle* liste[NB_MAX_SALLES];
  int nbsalles;
};

struct PosSalle {
  bool positionne;
  float x;
  float y;
};

class Batiment {
 public:
  Batiment(const ListeSalles& L2);
  void positionner(int indiceSalle, int x, int y);
  void positionner(const string& nom, int x, int y) {
    int i = L.chercherIndiceSalle(nom);
    positionner(i, x, y);
  }
  void affichage();

 private:
  ListeSalles L;
  PosSalle positions[NB_MAX_SALLES];
};

void lireFicSalle(const string& nomFic, ListeSalles* liste);

void ListeSalles::ajouter(Salle* salle) {
  if (nbsalles < NB_MAX_SALLES) {
    bool exist = false;
    for (int i = 0; i < nbsalles; i++) {
      if (liste[i]->getNom() == salle->getNom()) exist = true;
    }
    if (!exist) {
      liste[nbsalles] = salle;
      nbsalles++;
    }
  }
}

Salle* ListeSalles::chercherSalle(const string& s) const {
  for (int i = 0; i < nbsalles; i++) {
    if (liste[i]->getNom() == s) return liste[i];
  }
  return NULL;
}

int ListeSalles::chercherIndiceSalle(const string& s) const {
  for (int i = 0; i < nbsalles; i++) {
    if (liste[i]->getNom() == s) return i;
  }
  return -1;
}

ListeSalles ListeSalles::operator+(const ListeSalles& L) const {
  ListeSalles* L2 = new ListeSalles;
  int compteur = 0;
  for (int i = 0; i < nbsalles; i++) {
    L2->ajouter(liste[i]);
    compteur++;
  }
  for (int j = 0; j < L.nbsalles && compteur < NB_MAX_SALLES; j++) {
    if (L2->chercherIndiceSalle(L.liste[j]->getNom()) == -1) {
      L2->ajouter(L.liste[j]);
      compteur++;
    }
  }
  return *L2;
}

Salle* ListeSalles::getSalle_s(int indice) const {
  if (indice < 0 || indice >= nbsalles) throw exception();
  return liste[indice];
}

Batiment::Batiment(const ListeSalles& L2) : L(L2) {
  int taille = L2.getNbsalles();
  for (int i = 0; i < taille; i++) {
    PosSalle* p;
    p->positionne = false;
    positions[i] = *p;
  }
}

void Batiment::affichage() {
  int taille = L.getNbsalles();
  for (int i = 0; i < taille; i++) {
    Salle* s = L.getSalle_s(i);
    s->affichage();
    if (positions[i].positionne)
      cout << "   position:" << positions[i].x << " , " << positions[i].y
           << endl;
  }
}

void lireFicSalle(const string& nomFic, ListeSalles* liste) {
  int i = 0;
  ifstream input(nomFic);
  if (input) {
    while (!input.eof() && i < NB_MAX_SALLES) {
      string type, nom;
      float longueur, largeur;
      int capacite;
      Salle* S;
      input >> type >> nom >> longueur >> largeur >> capacite;

      if (type == "SALLE_COURS")
        S = new SalleCours(nom, largeur, longueur, capacite, 0);
      else if (type == "SALLE_INFO") {
        int nbpostes;
        input >> nbpostes;
        S = new SalleInfo(nom, largeur, longueur, capacite, nbpostes);
      } else
        S = new SalleCours(nom, largeur, longueur, capacite, 1);

      (*liste).ajouter(S);
      i++;
    }
  }
}

void Batiment::positionner(int indiceSalle, int x, int y) {
  int taille = L.getNbsalles();
  bool probleme = false;
  for (int i = 0; i < taille; i++) {
    if (positions[i].positionne) {
        }
  }
  if (!probleme) {
    positions[indiceSalle].x = x;
    positions[indiceSalle].y = y;
    positions[indiceSalle].positionne = true;
  }
}

int main(void) {
  ListeSalles L;
  lireFicSalle("Salles.txt", &L);
  L.affichage();
  return 0;
}