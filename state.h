#pragma once

#include <string>
#include "symbole.h"
using namespace std;

class Automate;

class State {
    public:
        State(string nom);
        virtual ~State();
        virtual void afficher();
        virtual bool transition(Automate & automate, Symbole * s) = 0;
        
    protected:
        string nom;
};

// Classes d'états spécifiques
class E0 : public State {
    public:
        E0() : State("E0") { }
        ~E0() { }
        bool transition(Automate & automate, Symbole * s);
        void afficher();
};

class E1 : public State {
    public:
        E1() : State("E1") { }
        ~E1() { }
        bool transition(Automate & automate, Symbole * s);
        void afficher();
};

// Continuer pour les états E2 à E9
class E2 : public State {
    public:
        E2() : State("E2") { }
        ~E2() { }
        bool transition(Automate & automate, Symbole * s);
        void afficher();
};

// ...et ainsi de suite pour tous les états

// Ajouter les classes manquantes
class E3 : public State {
    public:
        E3() : State("E3") { }
        ~E3() { }
        bool transition(Automate & automate, Symbole * s);
        void afficher();
};

class E4 : public State {
    public:
        E4() : State("E4") { }
        ~E4() { }
        bool transition(Automate & automate, Symbole * s);
        void afficher();
};

class E5 : public State {
    public:
        E5() : State("E5") { }
        ~E5() { }
        bool transition(Automate & automate, Symbole * s);
        void afficher();
};

class E6 : public State {
    public:
        E6() : State("E6") { }
        ~E6() { }
        bool transition(Automate & automate, Symbole * s);
        void afficher();
};

class E7 : public State {
    public:
        E7() : State("E7") { }
        ~E7() { }
        bool transition(Automate & automate, Symbole * s);
        void afficher();
};

class E8 : public State {
    public:
        E8() : State("E8") { }
        ~E8() { }
        bool transition(Automate & automate, Symbole * s);
        void afficher();
};

class E9 : public State {
    public:
        E9() : State("E9") { }
        ~E9() { }
        bool transition(Automate & automate, Symbole * s);
        void afficher();
};