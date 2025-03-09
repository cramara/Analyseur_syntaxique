#pragma once
#include <set>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include "state.h"
#include "symbole.h"

class Lexer;

class Automate {
    public:
        Automate(string expression, bool verbose = false);
        ~Automate();
        
        bool run();
        void decalage(Symbole * s, State * e);
        void reduction(int n, Symbole * s);
        void transition(State * e);
        void afficherEnfants();
        // Méthodes de réduction pour chaque règle
        void reduire2();  // E -> E + E
        void reduire3();  // E -> E * E
        void reduire4();  // E -> ( E )
        void reduire5();  // E -> val
        
        // Méthode pour afficher les piles
        void afficherPiles() const;
        
        // Nouvelle méthode pour corriger des erreurs courantes
        bool corrigerErreur(Symbole * s);
        
        // Méthode pour compter les parenthèses
        int compterParenthesesOuvrantes() const;
        int compterParenthesesFermantes() const;
        void AffciherArbre()const;
        vector<State*> pileEtats;
        vector<Symbole*> pileSymboles;
        
    protected:        
        string expression;
        Lexer * lexer;
        bool verbose;
        bool correctionEffectuee; // Pour suivre si une correction a été faite
        unordered_map<int,string> symboles;
        unordered_map<int, vector<int>> graph;

};

