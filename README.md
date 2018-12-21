# Simple-Blockchain
Reference: uses the sha256 secure hashing algorithm from https://github.com/okdshin/PicoSHA2/blob/master/picosha2.h
Project Description: A simple implementation of a blockchain using linked lists. Transactions on the chain are verified through use of a nonce that is generated randomly. Proof of work is done with checking that the nonce ends with a number 0-4 and verification is by storing the hash of the previous transaction in the next node. Each node is rehashed and the new hash is compared to the stored hash to verify that nodes on the chain were not changed.
