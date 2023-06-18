import subprocess
import random
import string

def execute_binary(command):
    # write input to file
    with open("../corpus/v4/input.txt", "w") as f:
        f.write(f"{command} A")

    # run the binary
    res = subprocess.run(['../target/server_v4.out', '../corpus/v4/input.txt'], stdout=subprocess.PIPE)
    return res.stdout

def main():
    ret = b"invalid command"
    random_pool = string.ascii_uppercase

    while b"invalid command" in ret:
        command = "H"
        for i in range(3):
            command += random.choice(random_pool)
        print(f"using: {command}")
        ret = execute_binary(command)
    
    print(f"\nfound: {command}")


if "__main__" == __name__:
    main()
