import sys

def main():
    if len(sys.argv) != 3:
        print(f"Usage : {sys.argv[0]} argument1 argument2")
        return

    entier1 = int(sys.argv[1])
    entier2 = int(sys.argv[2])

    resultat = entier1 + entier2

    print("le resultat des sommes:")
    print(f"{entier1} + {entier2} = {resultat}")

if __name__=="__main__":
  main()