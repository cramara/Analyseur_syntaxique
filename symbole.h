#pragma once

#include <string>
using namespace std;

enum Identificateurs { OPENPAR, CLOSEPAR, PLUS, MULT, INT, FIN, ERREUR, E };

const string Etiquettes[] = { "OPENPAR", "CLOSEPAR", "PLUS", "MULT", "INT", "FIN", "ERREUR", "E" };

class Symbole {
   public:
      Symbole(int i) : ident(i), id(GenerateID()) {  }
      virtual ~Symbole() { }
      operator int() const { return ident; }
      virtual void Affiche();
      int getId() const { return id; }
      string getEtiquette() const { return Etiquettes[ident]; }
   protected:
   static int GenerateID()
   {
      static int counter = 0;
      return counter++;
   }
      int ident;
      int id;
};

class Entier : public Symbole {
   public:
      Entier(int v) : Symbole(INT), valeur(v) { }
      ~Entier() { }
      virtual void Affiche();
      int Valeur() const { return valeur; }
   protected:
      int valeur;
};

class Expression : public Symbole {
   public:
      Expression(int v) : Symbole(E), valeur(v) { }
      ~Expression() { }
      virtual void Affiche();
      int Valeur() const { return valeur; }
   protected:
      int valeur;
};


