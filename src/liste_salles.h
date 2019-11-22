#pragma once
#include "salle.h"

#include <iostream>

static const long NB_MAX_SALLES = 100;

class OutOfRangeException : public std::exception {
  const char* what() const noexcept override { return "OutOfRangeException"; }
};

class ListeSalles {
 private:
  Salle* _salles[NB_MAX_SALLES];
  long _nbSalles = 0;

 public:
  ListeSalles();
  void ajouter(Salle* salle);
  void show() const;
  long nbSalles() const { return _nbSalles; }
  Salle* getSalle(int indice) const { return _salles[indice]; }
  Salle* getSalle_s(int indice) const {
    if (indice < 0 || indice >= NB_MAX_SALLES) {
      throw OutOfRangeException();
    }
    return _salles[indice];
  }
  Salle* chercherSalle(const std::string& nom) const;
  int chercherIndiceSalle(const std::string& nom) const;
  ListeSalles operator+(const ListeSalles& listeSalles) const;
};
