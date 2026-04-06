import os

def main():
    nom_fichier = input("Entrer le nom du fichier: ")

    os.execl("/usr/bin/emacs", "emacs", nom_fichier)

main()