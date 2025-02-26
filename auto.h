#pragma once

#include <string>
#include <vector>
#include "state.h"
#include "symbole.h"

class Lexer;

class Automate {
    public:
        Automate(string expression);
        ~Automate();
        
        bool run();
        void decalage(Symbole * s, State * e);
        void reduction(int n, Symbole * s);
        void transition(State * e);
        
        // Méthodes de réduction pour chaque règle
        void reduire2();  // E -> E + E
        void reduire3();  // E -> E * E
        void reduire4();  // E -> ( E )
        void reduire5();  // E -> val
        
        // Méthode pour afficher les piles
        void afficherPiles() const;
        
    protected:
        vector<State*> pileEtats;
        vector<Symbole*> pileSymboles;
        string expression;
        Lexer * lexer;
};
