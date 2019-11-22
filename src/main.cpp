#include "batiment.h"
#include "liste_salles.h"
#include "salle_cours.h"
#include "salle_info.h"

#include <fstream>

constexpr char FILENAME[] = "salles.txt";

void lireFicSalle(const std::string& nomFic, ListeSalles* liste);

int main() {
  ListeSalles listeSalles;
  lireFicSalle(FILENAME, &listeSalles);
  listeSalles.show();

  Batiment batiment(listeSalles);
  batiment.positionner(0, 0, 0);
  batiment.positionner(1, 0, 20);
  return 0;
}

void lireFicSalle(const std::string& nomFic, ListeSalles* liste) {
  std::ifstream fileStream(nomFic);
  std::cout << "Parsing " << nomFic << std::endl;

  if (fileStream.is_open()) {
    while (true) {
      // Data
      int longueur, largeur;
      long nbPlaces;
      std::string nom;

      // Parse
      std::string type;
      fileStream >> type >> nom >> longueur >> largeur >> nbPlaces;
      if (fileStream.fail()) break;
      if (type == "SALLE_COURS") {
        auto newSalle = new SalleCours(nom, longueur, largeur, nbPlaces, false);
        liste->ajouter(newSalle);
      } else if (type == "AMPHI") {
        auto newSalle = new SalleCours(nom, longueur, largeur, nbPlaces, true);
        liste->ajouter(newSalle);
      } else if (type == "SALLE_INFO") {
        long nbPostesInstalles;
        fileStream >> nbPostesInstalles;
        auto newSalle =
            new SalleInfo(nom, longueur, largeur, nbPlaces, nbPostesInstalles);
        liste->ajouter(newSalle);
      } else {
        std::cout << "Error : one line escaped." << std::endl;
      }
    }
  } else {
    std::cout << "Error" << std::endl;
  }
}