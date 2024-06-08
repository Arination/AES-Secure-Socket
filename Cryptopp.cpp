#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    using namespace CryptoPP;

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(cout));

    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());

    while (true)
    {
        SecByteBlock iv(AES::BLOCKSIZE); // Generate a new IV for each iteration
        prng.GenerateBlock(iv, iv.size());
        SecByteBlock key(AES::BLOCKSIZE); // Generate a new key for each iteration
        prng.GenerateBlock(key, key.size());

        string plain;
        string cipher, recovered;

        cout << "Enter plain text (or type 'exit' to quit): ";
        getline(cin, plain);

        if (plain == "exit") {
            break;
        }

        // Encryption
        try
        {
            CBC_Mode< AES >::Encryption e;
            e.SetKeyWithIV(key, key.size(), iv);

            StringSource s(plain, true,
                new StreamTransformationFilter(e,
                    new StringSink(cipher)
                ) // StreamTransformationFilter
            ); // StringSource
        }
        catch (const Exception& e)
        {
            cerr << e.what() << endl;
            continue;
        }

        cout << "key: ";
        encoder.Put(key, key.size());
        encoder.MessageEnd();
        cout << endl;

        cout << "iv: ";
        encoder.Put(iv, iv.size());
        encoder.MessageEnd();
        cout << endl;

        cout << "cipher text: ";
        encoder.Put((const byte*)&cipher[0], cipher.size());
        encoder.MessageEnd();
        cout << endl;

        // Decryption
        try
        {
            CBC_Mode< AES >::Decryption d;
            d.SetKeyWithIV(key, key.size(), iv);

            StringSource s(cipher, true,
                new StreamTransformationFilter(d,
                    new StringSink(recovered)
                ) // StreamTransformationFilter
            ); // StringSource

            cout << "recovered text: " << recovered << endl;
        }
        catch (const Exception& e)
        {
            cerr << e.what() << endl;
            continue;
        }

        cout << endl; // Print an empty line for better readability
    }

    return 0;
}
