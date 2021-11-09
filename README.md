# Photo_Encryption

Utilizing a Fibonacci Linear Feedback Shift Register, encrypt a photo by changing the binary representation of each pixel
Using the same password will decrypt the photo back to original

## Installation

All above files must be downloaded

Current system works only within Linux environment.

SFML libraries must be appropriately installed: https://www.sfml-dev.org/tutorials/2.5/start-linux.php

## Utilizing Makefile

Photos must be stored as .png for proper decryption.
```bash
$ make
```
#### Encrypting
```bash
$ ./PhotoEncrypt photo.png photo_encrypted.png my_password
```
#### Decrypting
```bash
$ ./PhotoEncrypt photo_encrypted.png photo_decrypt.png my_password
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Version

(latest) v1 : Sep 2021
