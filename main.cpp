#include <iostream>
#include <string>
#include "lexer.h"
#include "auto.h"

// Variable globale pour le mode verbose
bool verbose = false;

int main(int argc, char* argv[]) {
   string chaine;
   bool expressionFournie = false;
   
   // Analyser les arguments de la ligne de commande
   for (int i = 1; i < argc; i++) {
      string arg = argv[i];
      if (arg == "-v" || arg == "--verbose") {
         verbose = true;
      } else if (!expressionFournie) {
         chaine = arg;
         expressionFournie = true;
      }
   }
   
   // Si aucune expression n'a été fournie, utiliser l'expression par défaut
   if (!expressionFournie) {
      chaine = "(1+2)*8";
      cout << "Aucune expression fournie. Utilisation de l'expression par défaut: " << chaine << endl;
      cout << "Usage: ./program [-v] \"expression\"" << endl;
      cout << "  -v, --verbose  : Affiche les détails de l'analyse" << endl;
      cout << "Note: L'expression doit être entre guillemets pour éviter les erreurs avec les caractères spéciaux comme (, ), *" << endl;
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
   //automate.afficherEnfants();
   automate.AffciherArbre();
   return 0;
}

