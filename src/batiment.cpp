#include "batiment.h"

bool _checkSecante(int x1, int y1, int length1, int x2, int y2, int length2);

void Batiment::positionner(int indiceSalle, int x, int y) {
  Salle* salleAPositionner = _listeSalles.getSalle_s(indiceSalle);

  // 1. Checker chaque salle
  for (long i = 0; i < _listeSalles.nbSalles(); i++) {
    Salle* salleAChecker = _listeSalles.getSalle_s(i);

    if (_posSalle[i].estPositionne) {
      // 2. Checker les 4 cotés ne coupe pas un des cotes de APositionner

      bool casH1V1 =
          _checkSecante(x, y, salleAPositionner->longueur(), _posSalle[i].x,
                        _posSalle[i].y, salleAChecker->largeur());
      bool casH2V1 = _checkSecante(
          x, y + salleAPositionner->largeur(), salleAPositionner->longueur(),
          _posSalle[i].x, _posSalle[i].y, salleAChecker->largeur());

      bool casH1V2 = _checkSecante(x, y, salleAPositionner->longueur(),
                                   _posSalle[i].x + salleAChecker->longueur(),
                                   _posSalle[i].y, salleAChecker->largeur());
      bool casH2V2 = _checkSecante(x, y + salleAPositionner->largeur(),
                                   salleAPositionner->longueur(),
                                   _posSalle[i].x + salleAChecker->longueur(),
                                   _posSalle[i].y, salleAChecker->largeur());

      bool casV1H1 =
          _checkSecante(y, x, salleAPositionner->largeur(), _posSalle[i].y,
                        _posSalle[i].x, salleAChecker->longueur());
      bool casV1H2 = _checkSecante(y, x + salleAPositionner->longueur(),
                                   salleAPositionner->largeur(), _posSalle[i].y,
                                   _posSalle[i].x, salleAChecker->longueur());
      bool casV2H1 = _checkSecante(y, x, salleAPositionner->largeur(),
                                   _posSalle[i].y + salleAChecker->largeur(),
                                   _posSalle[i].x, salleAChecker->longueur());
      bool casV2H2 = _checkSecante(y, x + salleAPositionner->longueur(),
                                   salleAPositionner->largeur(),
                                   _posSalle[i].y + salleAChecker->largeur(),
                                   _posSalle[i].x, salleAChecker->longueur());
      // Haut
      if (casH1V1 || casH1V2 || casH2V1 || casH2V2 || casV1H1 || casV1H2 ||
          casV2H1 || casV2H2) {
        std::cout << "Salle incompatible" << std::endl;

        salleAPositionner->show();
        std::cout << "x : " << x << std::endl << "y : " << y << std::endl;

        salleAChecker->show();
        std::cout << "x : " << _posSalle[i].x << std::endl
                  << "y : " << _posSalle[i].y << std::endl;
        return;
      }
    }
  }

  // 3. Positionner
  _posSalle[indiceSalle].estPositionne = true;
  _posSalle[indiceSalle].x = x;
  _posSalle[indiceSalle].y = y;
}

bool _checkSecante(int x1, int y1, int length1, int x2, int y2, int length2) {
  if (y2 >= y1 && y2 <= y1 + length1) {
    if ((x1 <= x2 && x1 >= x2 + length2) || (x1 >= x2 && x1 <= x2 + length2)) {
      return true;
    }
  }
  return false;
}

void Batiment::positionner(const std::string& nom, int x, int y) {
  int indiceSalle = _listeSalles.chercherIndiceSalle(nom);

  positionner(indiceSalle, x, y);
}

void Batiment::show() const {
  for (long i = 0; i < _listeSalles.nbSalles(); i++) {
    _listeSalles.getSalle_s(i)->show();
    if (_posSalle[i].estPositionne) {
      std::cout << "La salle est positionné :" << std::endl
                << "x : " << _posSalle[i].x << std::endl
                << "y : " << _posSalle[i].y << std::endl;
    } else {
      std::cout << "La salle n'est pas positionné." << std::endl;
    }
    std::cout << std::endl;
  }
}