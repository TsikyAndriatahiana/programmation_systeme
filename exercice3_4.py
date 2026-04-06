import os

def main():
    quitter = True

    while quitter != False:
        repertoire = input("Entrer le nom du repertoire: ")

        repertoire_courant = os.getenv("PWD")

        commande = f"cp -r {repertoire_courant} {repertoire}"

        os.system(commande)

        verif = input("tapez Q si vous voulez quitter:")

        if verif == 'Q' or verif == 'q':
            quitter = True

main()