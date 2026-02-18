This project has been created as part
of the 42 curriculum by mchiacha, fmoses

# Description
Minishell est notre propre implementation d'un shell, inspire de Bash (--posix). Ce projet nous a permis de comprendre en profondeur le fonctionnement interne d'un shell qu'on utilise souvent : la gestion des processus, des descripteurs de fichiers, des signaux, etc etc.

Notre shell est capable de :

Afficher un prompt interactif et executer des commandes;

Gerer l'historique des commandes;

Chercher et lancer des executables via la variable PATH;

Gerer les signaux (Ctrl+C, Ctrl+D);

Implémenter les redirections (<, >, >>, <<);

Gerer les pipes (|);

Gerer les variables d'environnement ($VAR et $?);

Interpreter les quotes simples et doubles;

Implementer les builtins : echo, cd, pwd, export, unset, env, exit;

# Instructions
- Compilation ->

make        # Compile notre projet
make clean  # Supprime les fichiers objets (.o)
make fclean # Supprime les fichiers objets (.o) et l'executable (minishell)
make re     # Recompile

# Utilisation
./minishell              # Lance notre shell

# Exemples
mchiacha@minishell> pwd
fmoses@minishell> exit 
fmoses@minishell> cd .. 
mchiacha@minishell> echo "Hello 42 from mchiacha and fmoses <3"

# Resources
https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
