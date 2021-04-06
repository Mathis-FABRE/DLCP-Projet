![](https://github.com/Amu-DevCommeLesPros-2021/DevCommeLesPros-2021-Projet/workflows/Run%20tests/badge.svg)

<!-- TOC ignore:true -->
# DevCommeLesPros-2021-Projet

Modèle de départ pour le projet de programmation à effectuer en groupe de deux ou trois étudiants.
Vous n'êtes pas dans l'obligation de garder exactment les mêmes équipes que pour les exercices précédents.

<!-- TOC ignore:true -->
# Table des matières

<!-- TOC -->

- [Objectif](#objectif)
- [Spécifications fonctionelles](#sp%C3%A9cifications-fonctionelles)
    - [Fonctionalités pour un restaurateur](#fonctionalit%C3%A9s-pour-un-restaurateur)
    - [Fonctionalités pour un livreur](#fonctionalit%C3%A9s-pour-un-livreur)
    - [Fonctionalités pour un client](#fonctionalit%C3%A9s-pour-un-client)
- [Spécifications de conception](#sp%C3%A9cifications-de-conception)
    - [Interface](#interface)
    - [Base de données](#base-de-donn%C3%A9es)
        - [Table des restaurants](#table-des-restaurants)
        - [Table d'items de menus](#table-ditems-de-menus)
        - [Table des livreurs](#table-des-livreurs)
        - [Table des clients](#table-des-clients)
    - [Journal](#journal)
    - [Langage de programmation, paramètres de compilateur et proscriptions](#langage-de-programmation-param%C3%A8tres-de-compilateur-et-proscriptions)
- [Instructions de travail](#instructions-de-travail)
    - [Modules/Bibliothèques](#modulesbiblioth%C3%A8ques)
    - [Tests](#tests)
        - [Tests unitaires et tests d'intégration](#tests-unitaires-et-tests-dint%C3%A9gration)
        - [Intégration continue](#int%C3%A9gration-continue)
    - [Documentation](#documentation)
        - [Documentation pour les utilisateurs](#documentation-pour-les-utilisateurs)
        - [Documentation pour les ingénieurs](#documentation-pour-les-ing%C3%A9nieurs)
    - [Phases de développement](#phases-de-d%C3%A9veloppement)
        - [Pré-alpha](#pr%C3%A9-alpha)
        - [Alpha](#alpha)
        - [Beta](#beta)
        - [Livraison](#livraison)
        - [Support et fonctionalités additionelles](#support-et-fonctionalit%C3%A9s-additionelles)
- [Évaluation](#%C3%A9valuation)
    - [La base de code](#la-base-de-code)
    - [L'application](#lapplication)
    - [La méthode de développement](#la-m%C3%A9thode-de-d%C3%A9veloppement)
- [Les extras](#les-extras)

<!-- /TOC -->
# Objectif

Le service [UberEats](https://www.ubereats.com) est un service de livraison de repas à domicile.
Cette platforme met en lien des restaurateurs, des livreurs et des clients.
Vous avez à créer un programme qui simule cette plateforme.

Cette application n'est pas un site web.
C'est un programme lancé à l'invite de commandes qui utilisent des fichiers locaux comme base de données.
Son utilisation ne se fera que par l'invite de commandes.

# Spécifications fonctionelles

Sur cette platforme, on distingue trois profils d'utilisateur avec des besoins et des fonctionalités qui leurs sont propres : les restaurateurs, les livreurs et les clients.

## Fonctionalités pour un restaurateur

À un restaurant correspond un type de cuisine : fast-food, sushi, sandwicherie, etc.
Chaque restaurant a son menu composé de plusieurs items.
Certains items peuvent se retrouver sur des menus de différents restaurants.

Au fils des commandes des clients, un montant est crédité dans le compte.

- [ ] Créer un compte
    - [ ] Nom (du restaurant)
    - [ ] Code postal
    - [ ] Téléphone
    - [ ] Type de cuisine
- [ ] Supprimer un compte
    - [ ] Supprime les références à ce restaurant dans les items
- [ ] Modifier le menu
    - [ ] Ajouter un nouvel item au menu
        - [ ] Nom
        - [ ] Ingrédients principaux
        - [ ] Prix
    - [ ] Ajouter un item au menu parmi la liste des items existants
    - [ ] Supprimer un item
- [ ] Solde
    - [ ] Voir le solde courant

## Fonctionalités pour un livreur

Un livreur n'a pas un rayon d'action infini.
Chaque livreur a une liste de code postaux dans lesquels il peut se déplacer.
Un livreur peut travailler à son propre compte ou travailler exclusivement pour un restaurant en particulier.
Si un livreur travaille pour un restaurateur exclusivement, il est attendu qu'il peut se déplacer dans le code postal du restaurant en question.

Au fils des commandes des clients, un montant est crédité dans le compte.

- [ ] Créer un compte
    - [ ] Nom
    - [ ] Code postaux de déplacement
    - [ ] Téléphone
    - [ ] Exclusivité restaurateur
- [ ] Supprimer un compte
- [ ] Modifier son profil
    - [ ] Code postaux de déplacement
    - [ ] Téléphone
    - [ ] Exclusivité restaurateur
- [ ] Solde
    - [ ] Voir le solde courant

## Fonctionalités pour un client

Un client informe son profil à la création de son compte.
Son solde de départ sera de zéro.
Il peut par la suite ajouter de l'argent à son solde.
Ce solde sera débité au moment de passer une commande.

En tant que client, je ne peux me faire livrer d'un resturant seulement s'il existe un livreur qui peut se déplacer dans le code postal du restaurant en question et mon propre code postal.
Par exemple, si j'habite dans le 13009, je peux me faire livrer d'un restaurant dans le 13001 uniquement s'il existe un livreur qui peut se déplacer à la fois dans le 13009 et le 13001.

- [ ] Créer un compte
    - [ ] Nom
    - [ ] Code postal
    - [ ] Téléphone
- [ ] Supprimer un compte
- [ ] Modifier son profil
    - [ ] Code postal
    - [ ] Téléphone
- [ ] Solde
    - [ ] Confirmer le solde courant
    - [ ] Créditer un montant
- [ ] Voir la liste des restaurants
    - [ ] Restreindre la liste...
        - [ ] À qui peut me livrer
        - [ ] À un type de cuisine
        - [ ] À une combinaison de ces paramètres
- [ ] Commande 
    - [ ] Voir la liste des items
        - [ ] Restreindre la liste...
            - [ ] À qui peut me livrer
            - [ ] À un type de cuisine
            - [ ] À un seul restaurant
            - [ ] Aux items moins chers que mon solde disponible
            - [ ] À une combinaison de ces paramètres
    - [ ] Ajouter un item
    - [ ] Enlever un item
    - [ ] Passer la commande
        - [ ] Débite le solde du client
        - [ ] Crédite les soldes du restaurant et du livreur

# Spécifications de conception

## Interface

Ce programme sera lancé à l'invite de commandes.
L'utilisateur naviguera les divers fonctionalités grâce à une arborescence de menu affichée à l'écran. Quelques exemples :

```
*** Bienvenu sur LuminEats, la livraison à vitesse luminique ***

* Menu Principal *

Vous êtes :
1. Un·e restaurateur·trice
2. Un·e livreur·se
3. Un·e client·e

Votre choix ('q' pour quitter) :
```

```
* Menu Restaurateur *

Vous voulez :
1. Vous connecter à votre compte
2. Créer un nouveau compte

Votre choix ('q' pour quitter, 'p' pour menu précédent) : 
```

```
* Menu Restaurateur *

Vous voulez :
1. Supprimer votre compte
2. Modifier votre menu (ajouter/modifier/supprimer)
3. Confirmer votre solde

Votre choix ('q' pour quitter, 'p' pour menu précédent) : 
```

## Base de données

La base de données sera constituée de plusieurs fichiers `.csv`.
Un fichier par table.
Les tables de la base de données suivent le même format que la table utilisée dans l'exercice 4 ([docteurs.txt](https://github.com/Amu-DevCommeLesPros-2021/DevCommeLesPros-2021-Exo4/blob/master/test/docteurs.txt)) où les champs sont séparés par des virgules.
Si un champ contient plusieurs valeurs, celles-ci sont séparées par des points-virgules.
Ce format standard s'appelle [«Comma-separated values»](https://fr.wikipedia.org/wiki/Comma-separated_values) (valeurs séparées par des virgules).
En général, l'extension de ces fichiers est `.csv` plutôt que `.txt`.
Les applications de tableurs, Excel par exemple, peuvent utiliser ce format de fichier.

L'application doit pouvoir utiliser une base de données existante.
Les informations dans la base de données persistent entre les utilisations de l'application.
C'est-à-dire qu'elle n'est pas remise à zéro à chaque fois que lancez l'application.
Si je crée un ouveau compte client et que je quitte l'application, je doit pouvoir relancer l'application et y retrouver mon compte client déjà créé.

Chaque tuple dans une table est assigné une clé primaire avec un numéro unique dans cette table.
Certains attributs peuvent être des clés étrangères.
Quelques exemples :

### Table des restaurants

L'attribut `menu` est une liste de clés primaires `id` de la table des items.

```
id,nom,code postal,telephone,type,menu,solde
1,Chez Michel,13001,04 13 13 13 13,Provencal,1;4;5,50
2,Le Veg,13005,04 10 11 12 13,Vegetarien,2;3;4,24
3,Joe's International House of Pancakes,13010,04 22 33 44 55,Americain,6;7,44
```

### Table d'items de menus

```
id,nom,ingredients,prix
1,bouillabaise,poissons de roche;pommes de terre,25
2,taco,haricots;salsa;lime;tortilla,4
3,houmous,pois chiche;tahini;ail;citron,6
4,ratatouille,aubergine;courgette;poivron;tomate,15
5,salade nicoise,oeuf;thon;olive;huile,10
6,pancakes aux myrtilles,farine;lait;oeuf;myrtille,8
7,petit-dej du champion,oeufs;toast;bacon;pomme de terre,12
```

### Table des livreurs

Si le livreur travaille exclusivement pour un restaurant en particuler, l'attribut `restaurant` est une clé primaire `id` de la table des resturants.
Si le livreur travaille à son propre compte, l'attribut `restaurant` sera `0`.

```
id,nom,telephone,deplacements,restaurant,solde
1,Francois Pignon,06 00 00 00 00,13001;13002;13003,1,20
2,Donald Duck,06 01 02 03 04,13001;13004;13005;13006;13009;13010,0,25
3,Mickey Mouse,06 11 22 33 44,13008;13009;13010;13011,0,0
```

### Table des clients

```
id,nom,code postal,telephone,solde
1,Francoise Perrin,13005,04 10 20 30 40,0
2,Daffy Duck,13010,06 90 91 92 93,50
3,Quentin Tarantino,13008,06 99 88 77 66,15
```

> Est-ce qu'on doit «commit»er les fichiers de la base de données ?

Il vous sera probablement bénéfique, en effet, d'avoir une certaine base de données de départ.
Ne perdez pas trop temps à la remplir.
C'est amusant à faire mais les noms de restaurant rigolos ne valent pas plus de points.

Par la suite, quand vous testez votre application, si la base de données est modifiée par les tests, elle ne devrait pas être «commit»ée.
Il est préférable de toujours tester à partir du même point.

## Journal

Le programme devra produire un [journal](https://thierryseegers.github.io/DevCommeLesPros-CoursMagistral/#d%C3%A9boguer-par-journal) de toute les opérations exécutées.
Les informations dans le journal persistent entre les utilisations de l'application.
C'est-à-dire que le fichier servant de journal n'est pas remis à zéro quand vous lancez l'application.

## Langage de programmation, paramètres de compilateur et proscriptions

Le projet peut être écrit en C ou en C++.

Utilisez les options `-Wall -Wextra -Werror` du compilateur.
Ces options nous évitent bien des maux de tête car elles soulignent des erreurs qui peuvent facilement devenir fatales.

Comme pour les [exercices précédents](https://github.com/Amu-DevCommeLesPros-2021/DevCommeLesPros-2021-Exo1#pourquoi-pas-de-goto-ou-de-boucles-infinies-), gardez vous d'utiliser `goto` et d'avoir des boucles «infinies». La fonction [exit()](https://en.cppreference.com/w/c/program/exit) est également proscrite pour vous forcer à éviter de programmer des «culs-de-sac».

# Instructions de travail

Suivez les instructions de départ et les instructions de travail de l'exercice 4 avec deux exceptions :
1. Vous pouvez travailler en groupe de deux ou trois personnes.
1. La personne qui approuve et fusionne un «Pull Request» ne doit pas être la personne qui a ouvert le «Pull Request».
C'est-à-dire que si Alice pousse sa branche vers GitHub et ouvre un «Pull Request» pour demander de la fusionner à la branche `master`, ce doit être Bob ou Charlie qui approuvera et fusionnera.
Il incombe à Bob ou Charlie de confirmer que les tests ont bien passés sur la machine virtuelle de GitHub.

## Modules/Bibliothèques

Vous serez tentés d'essayer d'écrire ce programme de façon monolithique avec un gros fichier `main.c` qui fait tout.
Résistez à cette tentation !
La collaboration entre vous serait très difficile.

Travaillez ensemble pour déterminez de quels bibliothèques vous aurez besoin ainsi que leurs responsabilités (manipulation des base de données, fonctionalités entreprise/employé/chercheur, interface/menus, documentation, journal, etc.).
Déterminez aussi quels sont les dépendances entre les bibliothèques et quelles sont les fonctions requises des bibliothèques.
Ensuite vous pourez travaillez plus individuellement aux tâches que vous vous serez assignées sachant qui a besoin de quoi.

> Mais si mon module doit appeller une fonction d'une autre module qui n'existe pas encore ?

Rappellez-vous des exercices précédents où vous aviez à implémenter des fonctions «vides».
Ces fonctions ou méthodes s'appellent des [bouchons](https://fr.wikipedia.org/wiki/Bouchon_(informatique)) (ou «[stub](https://en.wikipedia.org/wiki/Method_stub)» en anglais).
Ces bouchons servent justement à deux choses :

1. Faire en sorte qu'un module `A` qui dépend de la fonction d'un module `B` puisse être développé et compilé _comme si_ la fonction était implémentée. 
Bien sûr, au début la fonction retourne une fausse valeur mais on peut continuer le développement du module `A` quand même en faisant semblant.
2. On peut écrire des tests avant même que la fonction soit implémentée. 
Connaissant la prototype d'une fonction et ses responsabilités, on peut écrire des tests qui en vérifient le bon fonctionnement.
Écrire des tests à l'avance est d'ailleurs une très bonne aide pour comprendre à quoi l'implémentation d'une fonction doit répondre : cas généraux, cas spéciaux, cas d'erreurs, etc.

Écrivez une première version de vos bibliothèques avec des fonctions bouchons et publiez-la sur votre dépôt.
Vos coéquipiers pourront dès lors écrire leur code en appellant ces fonctions.
Même si elle ne font rien, au moins le code compilera.
Écrivez ensuite les tests de vos fonctions et publiez-les.
Finalement, implémentez vos fonctions et publiez-les.

## Tests

Sans tests, vous n'aurez pas confiance ni en votre code ni en votre programme.
En plus du programme qui sera votre application, écrivez en parallèle un autre programme.
Un programme de tests qui rassemblera tout les tests que vous écrirez pour confirmer que vos bibliothèques opèrent correctement.
C'est ce programme de test qui sera lancé par la cible `check` du `makefile`.
Référez-vous à [l'exercice 2](https://github.com/Amu-DevCommeLesPros-2021/DevCommeLesPros-2021-Exo2) pour un projet qui contient deux programmes, un programme de test (`test/main.c`) et une application (`bin/main.c`).

> Vous avez mis `false` pour la cible `check` dans le makefile. Du coup, ça nous a fait un échec sur GitHub dès le premier «Pull Request».

Je sais.
C'est pour vous aider à bien faire les choses.
`false` est littéralement un programme qui ne fait que retourner un code d'erreur.
Remplacez `false` par autre chose tout de suite.
(Vous êtes tenté de le changer pour `true` ?
Créez plutôt immédiatement votre programme de test même s'il est vide ne consiste qu'en un simple `return 0;`.)

> Mais si mon module dépend d'une fonction d'une autre module qui n'est pas encore implémentée ?

Écrivez quand même vos tests quitte à les laisser commentés temporairement !
N'attendez pas que vos coéquipier·ère·s aient tout terminé pour commencer à travailler sur votre module.
Vous perdriez un temps précieux.

### Tests unitaires et tests d'intégration

Durant la première phase de développement, les tests que vous écrirez seront plutôt des test unitaires.
C'est-à-dire des tests qui testent les fonctionalités des divers modules en isolation.

Une fois que votre application commence à se tenir debout vous pourrez commencer à le tester dans son ensemble, à le lancer à l'invite de commandes et l'utiliser comme un utilisateur lambda le ferait.

### Intégration continue

Tout comme pour les exercices 3 et 4, ce projet est configuré [1] de telle sorte qu'en ouvrant un «Pull Request», GitHub lance une machine virtuelle Ubuntu qui clone votre dépôt et exécute la commande `make check` à l'invite de commande.
De ce fait, assurez-vous que la cible `check` de votre `makefile` dépende de votre programme de test et le lance.

Si la vérification du service d'intégration continu venait à échouer, il vous incombe d'apporter les modifications nécessaires à votre branche (toujours en faisant `add`, `commit` et `push`) pour rectifier la situation.
Essentiellement, je vous demande de travailler comme pour les exercices 3 et 4 en suivant leurs [instructions de travail](https://github.com/thierryseegers/DevCommeLesPros-2021-Exo4#instructions-de-travail). 
Seulement, cette fois-ci, c'est vous qui écrirez les tests.

[1] Curieux de savoir comment ?
Ouvrez le fichier `.github/workflows/test-master.yml`.
Pour en savoir plus, cliquez [ici](https://help.github.com/en/actions/configuring-and-managing-workflows/configuring-a-workflow).

## Documentation

### Documentation pour les utilisateurs

Modifiez ce `README` que vous lisez présentement et écrivez le manuel d'instructions de votre programme.
Décrivez-y les fonctionalités implémentés ainsi que, peut-être, les erreurs de manipulation à ne pas commettre.
Ce sera le «[tuto](https://fr.wikipedia.org/wiki/Tutoriel)» de votre programme.

Ici, vous pouvez laisser parler votre créativité.
Comment aimeriez-_vous_ qu'on vous apprenne à utiliser ce programme ?
Si vous vous sentez des âmes de comédiens, faites un tuto vidéo !

### Documentation pour les ingénieurs

Votre code doit être bien documenté pour vous-même et vos coéquipier·ère·s.
La documentation des fonctions dans les fichiers d'en-tête sert de moyen de communication entre l'auteur·trice de la fonction et ceux qui auront à l'appeller.
La documentation du code à l'intérieur des fonctions sert à qui que ce soit qui aura à entretenir la fonction et à la déboguer.

Un diagramme UML représentant graphiquement les dépendances entre les divers modules est aussi un excellent outil de communication entre les programmeurs. (Un outil gratuit pour créer des diagrammes UML se trouve [ici](https://app.diagrams.net/)).

## Phases de développement

L'évolution de votre travail suivra les [stades de développement d'un projet](https://thierryseegers.github.io/DevCommeLesPros-CoursMagistral/#stades-de-d%C3%A9veloppement).
Vous devrez qualifier les transitions entre ces étapes dans votre dépôt en utilisant des [tag](https://git-scm.com/book/en/v2/Git-Basics-Tagging)s sur votre branche `master`. 
Un tag est un commit qui ne contient qu'une courte description.
Cette description devra suivre les règles décrites [ici](https://semver.org/lang/fr/).

Pour taguer votre dépôt, faites à l'invite de commandes : `$ git tag -a [la-version] -m "Message pour ce tag."`. Par exemple : `$ git tag -a 1.0.0-alpha -m "Tout les modules sont à peu près finis. L'application peut être utilisée et est prête à être testée sérieusement."`

Les tags doivent être «poussés» comme des commits.
Après avoir créé un nouveau tag, faites à l'invite de commandes: `$ git push origin --tags`.

### Pré-alpha

C'est la première phase de développement.
Dès le départ votre projet est en phase pré-alpha.
Vous pouvez, d'emblée après avoir créé votre nouveau dépôt, le taguer avec `1.0.0-alpha+pre`.

Temps estimé de la phase pré-alpha : quatre à cinq semaines.

### Alpha

Lorsque vos modules sont suffisament implémentés pour que l'application puisse être lancée et utlisée, vous entrez dans la phase alpha.
Il se peut que toutes les fonctionalités ne soient pas toutes implémentées mais il y en a suffisament pour voir si les divers modules interagissent bien entre eux.
À ce stade, il peut rester encore quelques fonctions bouchons.
Taguez votre dépôt `1.0.0-alpha`.

Temps estimé de la phase alpha : une à deux semaines.

### Beta

Quand toutes les fonctionalités sont implémentées mais qu'il reste encore des bogues, vous entrez dans la phase beta.
Taguez votre dépôt `1.0.0-beta`.

À ce stade, testez exhaustivement votre application.
À chaque nouveau bogue découvert, écrivez un nouveau test.
Demandez à vos «compétiteurs» de tester votre application.
Ils seront impitoyables... et c'est ce qu'on veut !

C'est aussi le bon moment de produire la documentation pour l'utilisateur car votre interface est figée et vous savez quelles fonctionalités sont présentes.

Temps estimé de la phase beta : une à deux semaines.

### Livraison

Votre application est complétée et tout fonctionne pour le mieux.
Félicitations !
Cela vous vaut de taguer votre dépôt `1.0.0` et de publier une «release» officielle.
Suivez [ces instructions](https://help.github.com/en/github/administering-a-repository/managing-releases-in-a-repository).

Vous croyez avoir terminé ?
Pas tout à fait...

### Support et fonctionalités additionelles

Vous avez déjà officiellement tagué votre dépôt `1.0.0` mais vous venez de découvrir un ou deux nouveaux bogues ?
Qu'à cela ne tienne, continuez avec `1.0.n` si vous les réparez.

# Évaluation

La date d'évaluation est le *vendredi 31 mai à midi*. Le code écrit passé cette date ne sera pas considéré.

Votre travail sera évalué sur les points suivants.

## La base de code

- Organisation du code en bibliothèques.
- Organisation du code en fonctions.
- Exhaustivité des tests.
- Documentation du code, inclus le `makefile`.

## L'application

- Convivialité de l'interface.
- Fonctionalités implémentées.
- Bogues présents.
- Documentation de l'application.

## La méthode de développement

- Travail régulier, bien réparti dans le temps. (Ne faites pas tout à la dernière minute.)
- Bonne utilisation du service d'intégration continu.
- Respect des instructions de travail.

Vous avez tout bon ?
Ça vaut 18 sur 20.
Comment gagner d'autres points ?
Continuez de lire...

# Les extras

Chacun de ces extras vaut 1 point sur 20.
Il vous permettront donc d'atteindre 19 ou 20 sur 20.

*Ne tentez ces extras que si vous avez atteint l'objectif principal !
Ils ne valent aucuns points si votre programme ne répond pas aux exigences de base décrites dans les [spécifications fonctionnelles](#sp%C3%A9cifications-fonctionelles).*

À chaque extra correctement implémenté, incrémentez la version mineure de votre programme («1.1.0» pour le premier extra, «1.2.0» pour le deuxième extra) comme décrit dans la section [Phases de développement](#Phases-de-d%C3%A9veloppement).

Voici une liste d'extras à envisager.
Je les ai mis dans un ordre qui, selon moi, est du plus facile au plus difficile.

1. Un utilisateur, que ce soit un restaurant ou une personne, s'authentifie avec un mot de passe.
Ne conservez pas le mot de passe en clair dans la table, utilisez une [fonction de hachage](https://fr.wikipedia.org/wiki/Fonction_de_hachage_cryptographique).
1. Plusieurs restaurants peuvent vouloir offrir un même item mais à des prix différents.
Dans ce cas, le prix n'est pas fixe par item mais varie de restaurant en restaurant.
1. Un restaurant peut offrir à un·e client·e fidèle une réduction de prix.
Par exemple, après trois achats, un rabais de 5% pour les prochains achats.
Cette réduction ne s'applique que pour ce client et ce restaurant en particulier.
Un client peux bénéficier de plusieurs réductions dans divers restaurants.
1. Donnez le choix de la langue d'affichage du programme.
Par exemple, l'utilisateur du programme peut choisir un affichage en anglais.
Le programme mémorise la préférence de langage pour chaque utilisateur.
1. Compressez toute la base de données par un codage de Huffman.
Les fichiers `.csv` sur le disque sont compressés.
Ils sont décompressés en mémoire, modifiés au fil des opérations et au moment de quitter le programme ils sont recompressés et écrits sur le disque.
Les fichiers décompressés n'apparaissent *jamais* sur le disque, ni pendant, ni après l'utilisation du programme. 
1. Utilisez une [véritable base de données SQL](https://sqlite.org/cintro.html) plutôt que des fichers `.csv` (cet extra n'est pas compatible avec l'extra précédent).

Vous avez une autre idée d'extra ?
Faites-la approuver par votre «[client](thierry.seegers@univ-amu.fr)» au préalable.
