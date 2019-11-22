#include "liste_salles.h"

ListeSalles::ListeSalles() {
  for (long i = 0; i < NB_MAX_SALLES; i++) {
    _salles[i] = nullptr;
  }
}

void ListeSalles::ajouter(Salle* salle) {
  if (_nbSalles >= NB_MAX_SALLES) {
    std::cout << "===La liste est plein===" << std::endl;
    return;
  }
  // Check
  for (long i = 0; i < _nbSalles; i++) {
    if (_salles[i]->nom() == salle->nom()) {
      std::cout << "===Une salle n'a pas pu être rajouté===" << std::endl;
      salle->show();
      std::cout << "===Fin===" << std::endl;
      return;  // Escape
    }
  }

  // Add
  _salles[_nbSalles] = salle;
  _nbSalles++;
}

void ListeSalles::show() const {
  for (long i = 0; i < _nbSalles; i++) {
    std::cout << std::endl;
    _salles[i]->show();
  }
}

Salle* ListeSalles::chercherSalle(const std::string& nom) const {
  for (long i = 0; i < _nbSalles; i++) {
    if (_salles[i]->nom() == nom) {
      return _salles[i];
    }
  }
  return nullptr;
}
int ListeSalles::chercherIndiceSalle(const std::string& nom) const {
  for (long i = 0; i < _nbSalles; i++) {
    if (_salles[i]->nom() == nom) {
      return i;
    }
  }
  return -1;
}

ListeSalles ListeSalles::operator+(const ListeSalles& listeSalles) const {
  // Dupes position in [listeSalles]
  int dupes[NB_MAX_SALLES];
  long nbDupes = 0;

  // Look for dupes
  for (long i = 0; i < _nbSalles; i++) {
    int pos = chercherIndiceSalle(_salles[i]->nom());
    if (pos != -1) {
      dupes[nbDupes] = pos;
      nbDupes++;
    }
  }

  // Construct
  ListeSalles newListeSalles;
  // 1. Add self
  for (long i = 0; i < _nbSalles; i++) {
    newListeSalles.ajouter(_salles[i]);
  }
  // 2. Add second without dupes
  for (long i = 0; i < listeSalles._nbSalles; i++) {
    bool skip = false;

    // Check for dupe
    for (long dupesCheckIdx = 0; dupesCheckIdx < nbDupes; dupesCheckIdx++) {
      if (dupes[dupesCheckIdx] == i) {
        skip = true;
        break;
      }
    }

    // End iteration if dupe
    if (skip) continue;

    newListeSalles.ajouter(_salles[i]);
  }

  return newListeSalles;
}