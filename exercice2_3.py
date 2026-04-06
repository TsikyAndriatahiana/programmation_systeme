import os

def main():
    for i in range(5):
        pid_fils = os.fork()

        if pid_fils == -1:
            print("Erreur de création du processus")

        elif pid_fils == 0:
            print(f"je suis le fils {i}")
            break

main()