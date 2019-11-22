#include "salle.h"

#include <iostream>

void Salle::show() const {
  std::cout << "Salle " << _nom << std::endl
            << "Longueur : " << _longueur << std::endl
            << "Largeur : " << _largeur << std::endl
            << "Nb. de places : " << _nbPlaces << std::endl;
}