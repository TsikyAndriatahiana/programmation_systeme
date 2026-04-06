import os

def main():
    quitter = True

    while quitter == True:

        nom_fichier = input("Entrer le nom du fichier: ")

        pid = os.fork()

        if pid == -1:
            print("Problème dans fork()")

        elif pid == 0:
            os.execl("/usr/bin/emacs", "emacs", nom_fichier)

        verif = input("tapez Q si vous voulez quitter:")

        if verif == 'Q' or verif == 'q':
            quitter = False

        os.wait()

main()