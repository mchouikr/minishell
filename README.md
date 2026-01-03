# minishell

Un mini shell ecrit en C pour le projet 42. L'objectif est de reproduire les
comportements essentiels d'un shell POSIX: parsing, expansions, pipes,
redirections et commandes internes.

Janvier 2026 : Ajout d'un dockerfile pour faciliter la compilation et l'execution sur tous
les systèmes grace à un environnement Debian standardise.

## Fonctionnalites
- Prompt interactif avec historique (readline).
- Execution de commandes externes via PATH.
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Expansion des variables d'environnement (`$VAR`) et du statut (`$?`).
- Gestion des quotes simples et doubles.
- Pipes (`|`) entre plusieurs commandes.
- Redirections: entree (`<`), sortie (`>`), append (`>>`), heredoc (`<<`).
- Gestion des signaux en mode interactif.

## Compilation
```
make
```

Autres cibles utiles:
```
make clean
make fclean
make re
make valgrind
make docker-build
make docker-shell
make docker-make
```

## Valgrind
La cible `make valgrind` lance `./minishell` avec:
```
--leak-check=full --show-leak-kinds=all --track-origins=yes
```
Surcharge possible:
```
make valgrind VALGRIND_FLAGS="--leak-check=full --track-origins=yes"
```

## Docker (Debian)
```
docker build -t minishell .
docker run --rm -it -v "$PWD":/workspace minishell
```

Note: a la sortie du conteneur, un `make fclean` est lance automatiquement.
Pour le desactiver: `-e MSH_AUTO_FCLEAN=0`.

Equivalents via Makefile:
```
make docker-build
make docker-shell
make docker-make
```

Puis, dans le conteneur:
```
make
./minishell
```

## Utilisation
```
./minishell
```

Exemples:
```
echo "Hello" | cat -e
echo $HOME
cat << EOF
texte
EOF
```

Quitter:
- `exit`
- `Ctrl+D`

## Structure
- `includes/` : headers du projet.
- `srcs/` : sources (parsing, exec, builtins, signals).
- `libft/` : bibliotheque utilitaire.

## Dependances
- `readline` (utilisee pour le prompt et l'historique).

## Auteurs
- Eric Delplancq (edelplan) - github: [erdelp]
- Mabrouk Chouikri (mchouikr)

100/100 Obtenus le 28 Novembre 2024