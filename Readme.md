Pour compiler le programme : 
```make```

Pour clean les .o : 
```make fclean``` ou ```make clean```

Pour lancer le programme : 

./program "expression"

-v | --verbose pour verbose = true

exemple : ```./program "((45+4*)47"``` 
donne : 

```
Expression à analyser: ((45+4*)47
Erreur : symbole inattendu dans l'état E5 - CLOSEPAR
Erreur d'analyse syntaxique : symbole non attendu dans ce contexte
Erreur d'analyse de l'expression.
```

exemple : ```./program "(45+4)*47"```
donne : 
```
cramara@Laptop:~/4IF/GL/Analyseur_syntaxique$ ./program "(45+4)*47"
Expression à analyser: (45+4)*47
Résultat de l'évaluation : 2303
Expression analysée avec succès !
```