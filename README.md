# File Encryption Tool Using RSA (C)

This project is a file encryption and decryption tool implemented in C using the core ideas
behind the RSA public-key cryptosystem. The program supports key generation, file encryption
and file decryption through separate executables.

The focus of this project was to understand the low-level mechanics of RSA, modular arithmetic
and binary exponentiation, as well as to work close to the system level without relying on
external cryptography libraries.

## Key Features
- RSA key pair generation (public & private keys)
- File-based encryption and decryption
- Binary exponentiation for efficient modular power computation
- Clear separation of responsibilities across multiple C programs
- End-to-end encryption workflow (keygen → encrypt → decrypt)

## Technical Notes
For simplicity, the public exponent `e` is fixed to 7.  
However, the implementation of binary exponentiation makes the system extensible to larger
exponent values with minor modifications.

## How to Build

Compile each component separately:

**Key generation**

gcc generate-key.c -o generate-key

**Encryption**

gcc encrypt.c -o encrypt

**Decryption**

gcc decrypt.c -o decrypt

## Usage

1. Generate RSA keys:

./generate-key

2. Encrypt a file:

./encrypt <your-file>

3. Decrypt the encrypted file:

./decrypt encrypted-<your-file>

The decrypted output is saved with an added `decrypted_` prefix, allowing direct comparison
with the original file.

## Possible Improvements
- Support for configurable public exponent values
- Improved handling of large integers and data type consistency
- Padding schemes and security hardening for real-world usage

## Disclaimer
This project is intended for educational purposes and cryptography learning.
It is not designed for production-grade security.
