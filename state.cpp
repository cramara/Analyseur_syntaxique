#include "state.h"
#include "auto.h"
#include <iostream>

State::State(string nom) : nom(nom) {
}

State::~State() {
}

void State::afficher() {
    cout << nom;
}

// Implémentation des transitions pour E0
bool E0::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case INT:
            automate.decalage(s, new E3());
            break;
        case OPENPAR:
            automate.decalage(s, new E2());
            break;
        case E:
            automate.transition(new E1());
            break;
        default:
            return false;
    }
    return true;
}

void E0::afficher() {
    cout << "E0";
}

// Implémentation pour E1
bool E1::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case PLUS:
            automate.decalage(s, new E4());
            break;
        case MULT:
            automate.decalage(s, new E5());
            break;
        case FIN:
            // Accepter uniquement si la pile ne contient qu'un symbole (l'expression complète)
            return automate.pileSymboles.size() == 1;
        default:
            return false;
    }
    return true;
}

void E1::afficher() {
    cout << "E1";
}

// Continuer pour tous les autres états selon la table

bool E2::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case INT:
            automate.decalage(s, new E3());
            break;
        case OPENPAR:
            automate.decalage(s, new E2());
            break;
        case E:
            automate.transition(new E6());
            break;
        default:
            return false;
    }
    return true;
}

void E2::afficher() {
    cout << "E2";
}

bool E3::transition(Automate & automate, Symbole * s) {
    // Réduction par la règle 5 (E -> val)
    switch(*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            automate.reduire5();
            break;
        default:
            return false;
    }
    return true;
}

void E3::afficher() {
    cout << "E3";
}

bool E4::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case INT:
            automate.decalage(s, new E3());
            break;
        case OPENPAR:
            automate.decalage(s, new E2());
            break;
        case E:
            automate.transition(new E7()); ///faire une transition vers E7 sans consommer le symbole E
            break;
        default:
            return false;
    }
    return true;
}

void E4::afficher() {
    cout << "E4";
}

bool E5::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case INT:
            automate.decalage(s, new E3());
            break;
        case OPENPAR:
            automate.decalage(s, new E2());
            break;
        case E:
            automate.transition(new E8());
            break;
            
    }
    return true;
}

void E5::afficher() {
    cout << "E5";
}

bool E6::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case PLUS:
            automate.decalage(s, new E4());
            break;
        case MULT:
            automate.decalage(s, new E5());
            break;
        case CLOSEPAR:
            automate.decalage(s, new E9());
            break;
        default:
            return false;
    }
    return true;
}

void E6::afficher() {
    cout << "E6";
}

bool E7::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case PLUS:
            automate.reduire2();
            break;
        case MULT:
            automate.decalage(s, new E5());
            break;
        case CLOSEPAR:
            automate.reduire2();
            break;
        case FIN:
            automate.reduire2();
            break;
        default:
            return false;
    }
    return true;
}

void E7::afficher() {
    cout << "E7";
}

bool E8::transition(Automate & automate, Symbole * s) {
    switch(*s) {
            case PLUS:
            case MULT:
            case CLOSEPAR:
            case FIN:
                automate.reduire3();
                break;
            default:
            return false;
    }
    return true;
}   

void E8::afficher() {
    cout << "E8";
}

bool E9::transition(Automate & automate, Symbole * s) {
    switch(*s) {
            case PLUS:
            case MULT:
            case CLOSEPAR:
            case FIN:
                automate.reduire4();
                break;
            default:
            return false;
    }
    return true;
}  

void E9::afficher() {
    cout << "E9";
}
