import os
import time
import random

def main():
    debut = int(time.time())

    pid_fils1 = os.fork()

    if pid_fils1 == 0:
        random.seed(int(time.time()) ^ os.getpid())
        t1 = random.randint(1, 10)
        print(f"je suis le fils1 dort pendant {t1} sec")
        time.sleep(t1)
        os._exit(0)

    pid_fils2 = os.fork()

    if pid_fils2 == 0:
        random.seed(int(time.time()) ^ os.getpid())
        t2 = random.randint(1, 10)
        print(f"je suis le fils2 dort pendant {t2} sec")
        time.sleep(t2)
        os._exit(0)

    os.wait()
    os.wait()

    fin = int(time.time())
    print(f"total= {fin - debut} sec")

main()