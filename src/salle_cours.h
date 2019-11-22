#pragma once
#include "salle.h"

class SalleCours : public Salle {
 private:
  bool _estAmphi;

 public:
  SalleCours(std::string nom, int longueur, int largeur, long nbPlaces,
             bool estAmphi);
  void show() const override;
};
