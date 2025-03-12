#include <iostream>
#include <string>
#include <algorithm>
#include "lexer.h"
#include "auto.h"

// Variables globales pour les modes
bool verbose = false;
bool afficherArbre = false;
bool afficherAide = false;

void afficherAideMessage() {
   cout << "Usage: ./program [options] \"expression\"" << endl;
   cout << "Options:" << endl;
   cout << "  -h, --help     : Affiche ce message d'aide" << endl;
   cout << "  -v, --verbose  : Affiche les détails de l'analyse" << endl;
   cout << "  -t, --tree     : Affiche l'arbre syntaxique" << endl;
   cout << "Note: L'expression doit être entre guillemets pour éviter les erreurs avec les caractères spéciaux comme (, ), *" << endl;
   cout << "Exemple: ./program -t \"(1+2)*3\"" << endl;
   cout << "Attention: L'expression ne doit pas contenir de retours à la ligne." << endl;
}

// Fonction pour vérifier si l'expression contient des retours à la ligne
bool exprValide(const string& expr) {
   // Recherche de caractères de retour à la ligne
   if (expr.find('\n') != string::npos || expr.find('\r') != string::npos) {
      cout << "Erreur: L'expression contient des retours à la ligne, ce qui n'est pas autorisé." << endl;
      return false;
   }
   return true;
}

int main(int argc, char* argv[]) {
   string chaine;
   bool expressionFournie = false;
   
   // Analyser les arguments de la ligne de commande
   for (int i = 1; i < argc; i++) {
      string arg = argv[i];
      if (arg == "-v" || arg == "--verbose") {
         verbose = true;
      } else if (arg == "-h" || arg == "--help") {
         afficherAide = true;
      } else if (arg == "-t" || arg == "--tree") {
         afficherArbre = true;
      } else if (!expressionFournie) {
         chaine = arg;
         expressionFournie = true;
      }
   }
   
   // Si l'aide est demandée, l'afficher et quitter
   if (afficherAide) {
      afficherAideMessage();
      return 0;
   }
   
   // Si aucune expression n'a été fournie, utiliser l'expression par défaut
   if (!expressionFournie) {
      chaine = "(1+2)*8";
      cout << "Aucune expression fournie. Utilisation de l'expression par défaut: " << chaine << endl;
      afficherAideMessage();
   }
   
   // Vérifier si l'expression contient des retours à la ligne
   if (!exprValide(chaine)) {
      return 1; // Quitter avec un code d'erreur
   }
   
   cout << "Expression à analyser: " << chaine << endl;
   
   // Créer et lancer l'automate avec l'expression
   Automate automate(chaine, verbose);
   bool resultat = automate.run();
   
   if (resultat) {
      cout << "Expression analysée avec succès !" << endl;
   } else {
      cout << "Erreur d'analyse de l'expression." << endl;
   }
   
   // Pour vérification, exécuter le code original du lexer seulement en mode verbose
   if (verbose) {
      cout << "\nTest du lexer seul:" << endl;
      Lexer l(chaine);

      Symbole * s;
      while(*(s=l.Consulter())!=FIN) {
         s->Affiche();
         cout<<endl;
         l.Avancer();
      }
   }
   
   // Afficher l'arbre syntaxique si l'option -t est fournie ou en mode verbose
   if (afficherArbre || verbose) {
      automate.AffciherArbre();
   }
   
   return 0;
}

