#include "salle_info.h"

#include <iostream>

void SalleInfo::show() const {
  Salle::show();
  if (_nbPostesInstalles == 0) {
    std::cout << "Salle informatique sans postes fixes" << std::endl;

  } else {
    std::cout << "Salle informatique avec postes fixes" << std::endl
              << "Nb. de Postes Installés : " << _nbPostesInstalles
              << std::endl;
  }
}

SalleInfo::SalleInfo(std::string nom, int longueur, int largeur, long nbPlaces,
                     long nbPostesInstalles)
    : Salle(nom, longueur, largeur, nbPlaces),
      _nbPostesInstalles(nbPostesInstalles) {}