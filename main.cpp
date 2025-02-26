#include <iostream>
#include "lexer.h"
#include "auto.h"

int main(void) {
   string chaine("(1+34)*123");
   
   // Créer et lancer l'automate avec l'expression
   Automate automate(chaine);
   bool resultat = automate.run();
   
   if (resultat) {
      cout << "Expression analysée avec succès !" << endl;
   } else {
      cout << "Erreur d'analyse de l'expression." << endl;
   }
   
   // Pour vérification, aussi exécuter le code original du lexer
   cout << "\nTest du lexer seul:" << endl;
   Lexer l(chaine);

   Symbole * s;
   while(*(s=l.Consulter())!=FIN) {
      s->Affiche();
      cout<<endl;
      l.Avancer();
   }
   
   return 0;
}

