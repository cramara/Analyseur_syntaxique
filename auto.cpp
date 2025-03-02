#include "auto.h"
#include "lexer.h"
#include <iostream>

Automate::Automate(string expression, bool verbose) : expression(expression), verbose(verbose), correctionEffectuee(false) {
    lexer = new Lexer(expression);
    // Initialisation de l'automate avec l'état E0
    pileEtats.push_back(new E0());
}

Automate::~Automate() {
    // Libérer la mémoire
    delete lexer;
    
    for (State* etat : pileEtats) {
        delete etat;
    }
    
    for (Symbole* symbole : pileSymboles) {
        delete symbole;
    }
}

bool Automate::run() {
    Symbole * s;
    bool continue_analyse = true;
    
    while(continue_analyse) {
        s = lexer->Consulter();
        
        // Afficher l'état actuel des piles seulement en mode verbose
        if (verbose) {
            cout << "\n--- État actuel de l'analyseur ---" << endl;
            afficherPiles();
            cout << "Symbole courant: ";
            s->Affiche();
            cout << endl;
        }
        
        // Appliquer les transitions selon l'état courant
        continue_analyse = pileEtats.back()->transition(*this, s);
        
        // Si l'analyse ne peut pas continuer, essayer de corriger l'erreur
        if (!continue_analyse) {
            continue_analyse = corrigerErreur(s);
            
            // Si la correction n'est pas possible ou a échoué
            if (!continue_analyse && *s != FIN) {
                cout << "Erreur d'analyse syntaxique : symbole non attendu dans ce contexte" << endl;
                return false;
            }
        }
        
        // Ne pas terminer immédiatement si on voit FIN - continuer jusqu'à ce que la pile soit réduite à un seul élément
        if (*s == FIN && pileSymboles.size() == 1 && *pileSymboles[0] == E) {
            if (verbose) {
                cout << "\n--- État final ---" << endl;
                afficherPiles();
                cout << "Analyse syntaxique réussie" << endl;
            }
            
            // Afficher si une correction a été effectuée
            if (correctionEffectuee) {
                cout << "Note: L'expression a été corrigée automatiquement." << endl;
            }
            
            // Afficher le résultat final (même sans mode verbose)
            Entier* resultat = static_cast<Entier*>(pileSymboles[0]);
            cout << "Résultat de l'évaluation : " << resultat->Valeur() << endl;
            
            return true;
        }
    }
    
    return false;
}

void Automate::decalage(Symbole * s, State * e) {
    pileSymboles.push_back(s);
    pileEtats.push_back(e);
    lexer->Avancer();
    
    if (verbose) {
        cout << "Décalage de :" << endl;
        cout << "Symbole: ";
        s->Affiche();
        cout << endl;
        cout << "Etat: ";
        e->afficher();
        cout << endl;
    }
}

void Automate::transition(State * e) {
    pileEtats.push_back(e);
    if (verbose) {
        cout << "Transition vers l'état : ";
        e->afficher();
        cout << endl;
    }
}

void Automate::reduction(int n, Symbole * s) {
    if (verbose) {
        cout << "Réduction de " << n << " symboles" << endl;
    }
    
    // Réduction de n symboles et états
    for (int i = 0; i < n; i++) {
        delete pileEtats.back();
        pileEtats.pop_back();
        
        delete pileSymboles.back();
        pileSymboles.pop_back();
    }
    
    // Ajouter le nouveau symbole à la pile
    pileSymboles.push_back(s);
    
    // Appliquer la transition à partir de l'état actuel avec le symbole E
    pileEtats.back()->transition(*this, s);
}

// Implémentation des règles de réduction
void Automate::reduire2() {
    // Règle 2 : E -> E + E
    Entier* e1 = static_cast<Entier*>(pileSymboles[pileSymboles.size()-3]);
    Entier* e2 = static_cast<Entier*>(pileSymboles[pileSymboles.size()-1]);
    
    // Créer un nouveau symbole qui représente la valeur calculée
    Expression* resultat = new Expression(e1->Valeur() + e2->Valeur());
    
    if (verbose) {
        cout << "Réduction par la règle 2 : E -> E + E (" << e1->Valeur() << " + " << e2->Valeur() << " = " << resultat->Valeur() << ")" << endl;
    }
    
    // Réduire 3 symboles (E + E) vers un symbole E
    reduction(3, resultat);
}

void Automate::reduire3() {
    // Règle 3 : E -> E * E
    Entier* e1 = static_cast<Entier*>(pileSymboles[pileSymboles.size()-3]);
    Entier* e2 = static_cast<Entier*>(pileSymboles[pileSymboles.size()-1]);
    
    // Créer un nouveau symbole qui représente la valeur calculée
    Expression* resultat = new Expression(e1->Valeur() * e2->Valeur());
    
    if (verbose) {
        cout << "Réduction par la règle 3 : E -> E * E (" << e1->Valeur() << " * " << e2->Valeur() << " = " << resultat->Valeur() << ")" << endl;
    }
    
    // Réduire 3 symboles (E * E) vers un symbole E
    reduction(3, resultat);
}

void Automate::reduire4() {
    // Règle 4 : E -> ( E )
    // Récupérer la valeur de l'expression entre parenthèses
    Entier* e = static_cast<Entier*>(pileSymboles[pileSymboles.size()-2]);
    
    // Créer un nouveau symbole E avec la même valeur
    Expression* resultat = new Expression(e->Valeur());
    
    if (verbose) {
        cout << "Réduction par la règle 4 : E -> ( E ) (valeur = " << resultat->Valeur() << ")" << endl;
    }
    
    // Réduire 3 symboles (( E )) vers un symbole E
    reduction(3, resultat);
}

void Automate::reduire5() {
    // Règle 5 : E -> val
    Entier* e = static_cast<Entier*>(pileSymboles.back());
    
    // Créer un nouveau symbole E avec la valeur de l'entier
    Expression* resultat = new Expression(e->Valeur());
    
    if (verbose) {
        cout << "Réduction par la règle 5 : E -> val (valeur = " << resultat->Valeur() << ")" << endl;
    }
    
    // Réduire 1 symbole (val) vers un symbole E
    reduction(1, resultat);
}

void Automate::afficherPiles() const {
    // Afficher la pile des états
    cout << "Pile des états: ";
    for (State* etat : pileEtats) {
        cout << "[";
        etat->afficher();
        cout << "] ";
    }
    cout << endl;
    
    // Afficher la pile des symboles
    cout << "Pile des symboles: ";
    for (Symbole* symbole : pileSymboles) {
        cout << "[";
        symbole->Affiche();
        cout << "] ";
    }
    cout << endl;
}

// Nouvelle méthode pour corriger les erreurs courantes
bool Automate::corrigerErreur(Symbole * s) {
    // Cas 1: Parenthèse fermante manquante à la fin
    if (*s == FIN) {
        // Vérifier si le dernier symbole est un opérateur
        if (!pileSymboles.empty()) {
            Symbole* dernierSymbole = pileSymboles.back();
            if (*dernierSymbole == PLUS || *dernierSymbole == MULT) {
                cout << "Correction: Opérateur en fin d'expression ignoré" << endl;
                
                // Supprimer l'opérateur de la pile
                delete pileSymboles.back();
                pileSymboles.pop_back();
                
                // Supprimer l'état correspondant
                delete pileEtats.back();
                pileEtats.pop_back();
                
                correctionEffectuee = true;
                return true;
            }
        }
        
        int diff = compterParenthesesOuvrantes() - compterParenthesesFermantes();
        
        // S'il manque des parenthèses fermantes
        if (diff > 0) {
            if (verbose) {
                cout << "Correction: Ajout de " << diff << " parenthèse(s) fermante(s) manquante(s)" << endl;
            }
            
            // Ajouter virtuellement une parenthèse fermante
            Symbole* closepar = new Symbole(CLOSEPAR);
            
            // Essayer de continuer l'analyse avec cette parenthèse
            bool resultat = pileEtats.back()->transition(*this, closepar);
            
            if (resultat) {
                correctionEffectuee = true;
                return true; // La correction a réussi
            } else {
                delete closepar; // Nettoyer si la transition a échoué
            }
        }
    }
    
    // Cas 2: Parenthèse fermante sans parenthèse ouvrante correspondante
    if (*s == CLOSEPAR) {
        int diff = compterParenthesesOuvrantes() - compterParenthesesFermantes();
        
        // Si nous avons déjà autant ou plus de parenthèses fermantes que d'ouvrantes
        if (diff <= 0) {
            if (verbose) {
                cout << "Correction: Ignorer la parenthèse fermante excédentaire" << endl;
            }
            
            // Sauter cette parenthèse et passer au symbole suivant
            lexer->Avancer();
            correctionEffectuee = true;
            
            // Indiquer que l'analyse doit continuer
            return true;
        }
    }
    
    // Cas 3: Opérateurs consécutifs (++, **, +*, *+)
    if (*s == PLUS || *s == MULT) {
        // Cas 3a: Opérateur en début d'expression (pile vide)
        if (pileSymboles.empty()) {
            cout << "Correction: Opérateur en début d'expression ignoré" << endl;
            
            // Sauter cet opérateur et passer au symbole suivant
            lexer->Avancer();
            correctionEffectuee = true;
            
            // Indiquer que l'analyse doit continuer
            return true;
        }
        
        // Cas 3b: Opérateurs consécutifs
        Symbole* dernierSymbole = pileSymboles.back();
        if (*dernierSymbole == PLUS || *dernierSymbole == MULT) {
            // Opérateurs consécutifs détectés
            cout << "Correction: Opérateurs consécutifs détectés. Ignorer le second opérateur ";
            s->Affiche();
            cout << endl;
            
            // Sauter cet opérateur et passer au symbole suivant
            lexer->Avancer();
            correctionEffectuee = true;
            
            // Indiquer que l'analyse doit continuer
            return true;
        }
    }
    
    // Aucune correction n'a pu être appliquée
    return false;
}

// Méthodes pour compter les parenthèses
int Automate::compterParenthesesOuvrantes() const {
    int count = 0;
    for (Symbole* s : pileSymboles) {
        if (*s == OPENPAR) count++;
    }
    return count;
}

int Automate::compterParenthesesFermantes() const {
    int count = 0;
    for (Symbole* s : pileSymboles) {
        if (*s == CLOSEPAR) count++;
    }
    return count;
}
