import mutator_v1 as mut1
import mutator_v2 as mut2
import mutator_v3 as mut3
import mutator_v4 as mut4
import sys

def cycle_fuzz(module):
    module.init(123)
    for i in range(10):
        print(module.fuzz(1, 2, 3))

def main():
    print(f"***************")
    print(f"Using Version {sys.argv[1]}")
    print(f"***************")

    match sys.argv[1]:
        case "1":
            cycle_fuzz(mut1)
        case "2":
            cycle_fuzz(mut2)
        case "3":
            cycle_fuzz(mut3)
        case "4":
            cycle_fuzz(mut4)
        case _:
            print("invalid version number!")

if __name__ == "__main__":
    main()
