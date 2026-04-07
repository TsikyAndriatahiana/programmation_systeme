import os
import sys

def main():
    perevfils_r, perevfils_w = os.pipe()
    filsvpere_r, filsvpere_w = os.pipe()

    nom_fic = "monFichier"

    fils = os.fork()

    if fils == 0:
        # ===== FILS =====
        mot = input("veuillez entrer le mot à chercher : ")

        os.close(filsvpere_r)
        os.close(perevfils_w)

        os.dup2(filsvpere_w, 1)  # STDOUT
        os.dup2(perevfils_r, 0)  # STDIN

        os.close(filsvpere_w)
        os.close(perevfils_r)

        print(mot, end='', flush=True)

        try:
            x = int(input())
        except:
            x = 0

        if x == 0:
            print("on a pas trouver le mot dans le fichier")
            os._exit(3)
        else:
            print("la recherche a reussi")
            os._exit(3)

    elif fils > 0:
        # ===== PERE =====
        os.close(filsvpere_w)
        os.close(perevfils_r)

        os.dup2(filsvpere_r, 0)  # STDIN
        os.dup2(perevfils_w, 1)  # STDOUT

        os.close(filsvpere_r)
        os.close(perevfils_w)

        try:
            recuperer = input()
        except:
            recuperer = ""

        print(f"recuperer vaut : {recuperer}")

        trouver = 0

        try:
            with open(nom_fic, "r") as ptr:
                for ligne in ptr:
                    mots = ligne.split()
                    for chaine in mots:
                        if chaine == recuperer:
                            trouver = 1
                            break
                    if trouver:
                        break
        except:
            pass

        print(trouver, end='', flush=True)

if __name__ == "__main__":
    main()