import sys
FILENAME = "flag.txt"
SEQUENCE = bytes([0x13, 0x37])
SEQUENCE_LENGTH = 2

def handle_input():
    # Get input from the user as a string (you may want to specify the format expected, e.g., hex)
    user_input = input("> ")

    # Convert the input string to bytes
    try:
        buffer = bytes.fromhex(user_input.strip())
    except ValueError:
        print("ERROR: am I getting hacked?", file=sys.stderr)
        return

    # Check if received data matches the byte sequence
    if len(buffer) >= SEQUENCE_LENGTH and buffer[:SEQUENCE_LENGTH] == SEQUENCE:
        try:
            # Open the file and print its contents
            with open(FILENAME, "rb") as file:
                while chunk := file.read(256):
                    print(chunk.decode(errors='ignore'), end='')  # Decode and print the file content
        except FileNotFoundError:
            print("Failed to open file", file=sys.stderr)
    else:
        print("ERROR: am I getting hackd?", flush=True)

if __name__ == "__main__":
    handle_input()

