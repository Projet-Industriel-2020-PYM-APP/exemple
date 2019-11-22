#pragma once
#include "salle.h"
class SalleInfo : public Salle {
 private:
  long _nbPostesInstalles;

 public:
  SalleInfo(std::string nom, int longueur, int largeur, long nbPlaces,
            long nbPostesInstalles = 0);
  void show() const override;
};
