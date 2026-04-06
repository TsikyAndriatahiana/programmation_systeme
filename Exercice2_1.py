import os

def main():
    pid = os.fork()

    if pid == -1:
        print("Erreur de création du nouveau processus")

    elif pid == 0:
        print("je suis le fils")

    else:
        print("je suis le père")
main()