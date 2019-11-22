#include "salle_cours.h"

#include <iostream>

SalleCours::SalleCours(std::string nom, int longueur, int largeur,
                       long nbPlaces, bool estAmphi)
    : Salle(nom, longueur, largeur, nbPlaces), _estAmphi(estAmphi) {}

void SalleCours::show() const {
  Salle::show();
  if (_estAmphi) {
    std::cout << "Salle de cours classique" << std::endl;

  } else {
    std::cout << "Salle Amphithéâtre" << std::endl;
  }
}