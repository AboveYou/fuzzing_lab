import sys

def calculate_sum(payload):
    checksum = 0
    for letter in payload:
        checksum += ord(letter)
    checksum = str(checksum % 100)
    if int(checksum) < 10:
        checksum = "0" + checksum
    return checksum

def main():
    print(f"********************")
    print(f"Calculating Checksum")
    print(f"********************")

    if len(sys.argv) < 2:
        print("usage: <string>")
        return
    payload = sys.argv[1]
    checksum = calculate_sum(payload)
    
    print(f"input:\t\t{payload}")
    print(f"checksum:\t{checksum}")
    print(f"send payload:\t{payload + checksum}")

if __name__ == "__main__":
    main()
