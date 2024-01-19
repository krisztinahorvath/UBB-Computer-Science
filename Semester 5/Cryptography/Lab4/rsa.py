import random

def check_valid_alphabet(text):
    return all(ch == '_' or (ch.isalpha() and ch.isupper()) for ch in text)

def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False

    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6

    return True

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

def mod_pow(base, exp, mod):
    result = 1
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exp //= 2
    return result

def mod_inverse(a, m):
    for x in range(1, m):
        if (a * x) % m == 1:
            return x
    return 0

def blocks_to_numbers(letters):
    num = 0

    for letter in letters:
        uppercase_letter = letter.upper()

        if uppercase_letter == '_':
            num = num * 27
        else:
            num = num * 27 + (ord(uppercase_letter) - ord('A') + 1)

    return num

def numbers_to_blocks(number, block_size):
    text = ""

    for i in range(block_size - 1, -1, -1):
        coefficient = number // (27 ** i)
        number %= 27 ** i

        if coefficient > 0:
            text += chr(ord('A') + coefficient - 1)
        else:
            text += '_'

    return text

def encrypt(n, e, plaintext):
    block_size = 2
    encrypted_text = ""

    for i in range(0, len(plaintext), block_size):
        block = plaintext[i:i + block_size]
        numerical_block = blocks_to_numbers(block)

        # Encrypt (m^e mod n)
        encrypted_block_numerical = mod_pow(numerical_block, e, n)
        encrypted_text += numbers_to_blocks(encrypted_block_numerical, 3)

    return encrypted_text

def decrypt(n, d, ciphertext):
    block_size = 3
    decrypted_text = ""

    for i in range(0, len(ciphertext), block_size):
        block = ciphertext[i:i + block_size]
        numerical_block = blocks_to_numbers(block)

        # c^d mod n
        decrypted_block_numerical = mod_pow(numerical_block, d, n)
        decrypted_text += numbers_to_blocks(decrypted_block_numerical, 2)

    return decrypted_text

def choose_public_exponent_e(phi):
    e = random.randint(2, phi - 1)
    while gcd(e, phi) != 1:
        e = random.randint(2, phi - 1)

    return e

def main():
    print("RSA Algorithm: ")
    p_input = input("p: ")
    while not p_input.isdigit() or not is_prime(int(p_input)):
        print("Invalid p, please enter a prime number :)")
        p_input = input("p: ")
    p = int(p_input)

    q_input = input("q: ")
    while not q_input.isdigit() or not is_prime(int(q_input)) or int(q_input) == p:
        print("Invalid q, please enter a prime number that is different from p :)")
        q_input = input("q: ")
    q = int(q_input)

    n = p * q
    phi = (p - 1) * (q - 1)

    e = choose_public_exponent_e(phi)

    d = mod_inverse(e, phi)

    print(f"Public Key: (n, e) = ({n}, {e})")
    print(f"Private Key (d) = {d}")
    print(f"φ(n) = {phi}")

    while True:
        print("\nMenu:")
        print("0 - exit")
        print("1 - encrypt")
        print("2 - decrypt")
        choice = input("cmd: ")

        if choice == "0":
            break

        if choice == "1":
            plaintext = input("Enter plaintext: ")
            while not check_valid_alphabet(plaintext):
                print("Invalid plaintext, the only accepted characters are A-Z and _")
                plaintext = input("Enter plaintext: ")

            while len(plaintext) % 2 != 0:
                plaintext += '_'

            for i in range(0, len(plaintext), 2):
                block = plaintext[i:i + 2]
                numerical_block = blocks_to_numbers(block)
                print(f"{block} -> {numerical_block}")

            encrypted_text = encrypt(n, e, plaintext)
            print("\nEncryption:")
            for i in range(0, len(encrypted_text), 3):
                block = encrypted_text[i:i + 3]
                numerical_block = blocks_to_numbers(block)
                print(f"c{(i // 3) + 1} = b{(i // 3) + 1}^e % n = {numerical_block} -> {block}")

            print("\nCiphertext:", encrypted_text)

        elif choice == "2":
            ciphertext = input("Enter ciphertext: ")
            while not check_valid_alphabet(ciphertext):
                print("Invalid ciphertext, the only accepted characters are A-Z and _")
                ciphertext = input("Enter ciphertext: ")

            while len(ciphertext) % 3 != 0:
                ciphertext += '_'

            for i in range(0, len(ciphertext), 3):
                block = ciphertext[i:i + 3]
                numerical_block = blocks_to_numbers(block)
                print(f"{block} -> {numerical_block}")

            decrypted_text = decrypt(n, d, ciphertext)
            print("\nDecryption:")
            for i in range(0, len(decrypted_text), 2):
                block = decrypted_text[i:i + 2]
                numerical_block = blocks_to_numbers(block)
                print(f"d{(i // 2) + 1} = c{(i // 2) + 1}^d % n = {numerical_block} ->  {block}")

            print("\nPlaintext:", decrypted_text)

        else:
            print("Invalid command!")


if __name__ == "__main__":
    main()
