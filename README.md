adb-middleware
==============

ADB middleware for kingroot application debug

Applicatif surcouche pour ADB de kingroot.
Renommer adb.exe en old-adb.exe dans le dossier tools de kingRoot
copier l'exécutable compilé adb.exe dans le dossier tools de kingRoot
Editez C:\Users\<user>\adb-log.ini et ajoutez le chemin complet vers l'utilitaire adb (C:\...\old-adb.exe)
Lancez KingRoot et rootez votre tablette

le nouvel utilitaire journalisera les commandes passées à adb et exécutera la commande adb
Le journal est dans C:\Users\<user>\adb.log