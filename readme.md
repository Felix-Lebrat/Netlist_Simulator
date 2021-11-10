# Netlist Simulator

Compilateur de netlist vers C++, programmé en C++
[github du projet](https://github.com/Felix-Lebrat/Netlist_Simulator)

## Compilation
#### Prérequis
bison, flex, g++

#### Makefile

```
make
```
compile le projet et créé l'executable build/netlist_simulator

## Utilisation
#### Compilation d'une netlist
Pour compiler une netlist, il suffit de passer le nom du fichier .net  
en paramètre de netlist_simulator.  
**Le fichier *skeleton.cpp* doit être dans le répertoire courant.**
```
build/netlist_simulator test/clock_div.net
```
compile la netlist test/clock_div.net. Deux fichiers sont créés : 
* out.cpp qui est le code C++ produit par netlist_simulator
* out qui est l'executable correspondant à la compilation de out.cpp avec g++
### Utilisation de l'executable produit

L'option *-s n* définit le nombre de cycle à n. Par défaut, n=+inf.  

Dans le cas où des primitives ROM sont présentes dans la netlist, les roms  
sont initialisées avec les fichiers dans le répertoire courant dont le nom  
est celui de la rom. Par exemple, la rom correspondant à l'instruction
```
ma_rom = ROM 8 1 00101010
```
sera initialisée en lisant le contenu du fichier "ma_rom". Par défaut le  
contenu de la rom est décrit avec une suite de caractères ascii '0' ou '1'  
(\[01\]\*). Si l'option *-h* est ajoutée, le format attendu est une suite de  
caractères ascii correspondants à des chiffres hexadécimaux (\[0-9A-Fa-f\]\*).

Les entrées sont demandées sous la forme d'un suite de caractères ascii '0' ou '1' sans espaces.