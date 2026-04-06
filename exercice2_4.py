import os

pid_fils = 0  

def main():
    global pid_fils

    print("je suis le père")

    for i in range(5):
        pid_fils = os.fork()

        if pid_fils == 0:
            print(f"je suis le fils {i}")
            break

main()