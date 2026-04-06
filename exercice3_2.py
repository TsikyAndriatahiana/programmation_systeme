import sys
import os

def main():
    if len(sys.argv) != 2:
        print(f"Usage : {sys.argv[0]} repertoire_R")
        return

    print(sys.argv[1])

    repertoire_courant = os.getenv("PWD")  # récupération du répertoire courant

    commande = f"cp -r {repertoire_courant} {sys.argv[1]}"

    os.system(commande)  # exécution de la commande

if __name__ == "__main__":
    main()