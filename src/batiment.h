#pragma once
#include "liste_salles.h"

struct PosSalle {
  bool estPositionne = false;
  int x;
  int y;
};

class Batiment {
 private:
  ListeSalles _listeSalles;
  PosSalle _posSalle[NB_MAX_SALLES];

 public:
  Batiment(ListeSalles& listeSalles) : _listeSalles(listeSalles) {}
  void positionner(int indiceSalle, int x, int y);
  void positionner(const std::string& nom, int x, int y);
  void show() const;
};
