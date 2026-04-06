import os

SIZECAR = 100

def main():
    tube1 = os.pipe()
    tube2 = os.pipe()

    pid_fils = os.fork()

    if pid_fils == -1:
        print("Erreur dans fork")
        return

    if pid_fils == 0:
        # ---------------- pipe1 ----------------
        caractereW = input("saisissez un mot\n")

        os.close(tube1[0])
        os.write(tube1[1], caractereW.encode())

        # ---------------- pipe2 ----------------
        os.close(tube2[1])

        resultat = os.read(tube2[0], 1024)
        resultat = int(resultat.decode())

        if resultat == 1:
            print("le mot existe dans le fichier")
        else:
            print("le mot n'existe pas dans le fichier")

    else:
        # ---------------- pipe1 ----------------
        os.close(tube1[1])

        caractereR = os.read(tube1[0], 1024).decode()

        compt = 0

        try:
            with open("fichier.txt", "r") as mot:
                for ligne in mot:
                    if ligne.strip() == caractereR:
                        compt = 1
                        break
        except FileNotFoundError:
            print("fichier.txt introuvable")
            os._exit(1)

        # ---------------- pipe2 ----------------
        os.close(tube2[0])
        os.write(tube2[1], str(compt).encode())

main()