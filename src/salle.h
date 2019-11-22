#pragma once

#include <string>

class Salle {
 private:
  std::string _nom;
  int _longueur;
  int _largeur;
  long _nbPlaces;

 public:
  Salle(std::string nom, int longueur, int largeur, long nbPlaces)
      : _nom(nom),
        _longueur(longueur),
        _largeur(largeur),
        _nbPlaces(nbPlaces) {}
  virtual void show() const;
  std::string nom() const { return _nom; }
  int longueur() const { return _longueur; }
  int largeur() const { return _largeur; }
  long nbPlaces() const { return _nbPlaces; };
  bool operator<(const Salle &salle) const {
    return _nbPlaces < salle._nbPlaces;
  }
  bool operator==(const Salle &salle) const {
    return _nbPlaces == salle._nbPlaces;
  }
};