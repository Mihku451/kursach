#pragma once
#include <iostream> // äëÿ ôóíêöèè cout();
#include <stdlib.h> // äëÿ ôóíêöèè system();
#include <cstdio> // äëÿ ôóíêöèè remove();
#include <cstring> // äëÿ ôóíêöèè strcpy_s();

using namespace std;

class ClassCrypt
{
public:
    string  path_openssl;
    string db_filename;
    string secure_db_filename;
    char password[20];

    ClassCrypt() {
        path_openssl = "C:\\Program Files\\OpenSSL-Win64\\bin\\openssl.exe";
        db_filename = "dataBinary.txt";
        secure_db_filename = "secure_dataBinary.txt";
        strcpy_s(password, "password1");
    }

    //https://www.shellhacks.com/encrypt-decrypt-file-password-openssl/
    //ENCRYPT(interactive) :
    //openssl enc -aes-256-cbc -d -in file.txt.enc -out file.txt -iter 29 -k PASS
    //
    //DECRYPT(interactive) :
    //openssl enc -aes-256-cbc -d -in file.txt.enc -out file.txt -iter 29 -k PASS
    //
    //ENCRYPT(non-interactive) :
    //openssl enc -aes-256-cbc -in file.txt.enc -out file.txt -iter 29 -pass pass:mysecret
    //
    //DECRYPT(non-interactive) :
    //openssl enc -aes-256-cbc -d -in file.txt.enc -out file.txt -iter 29 -pass pass:mysecret
    //https://zalinux.ru/?p=4244 -iter 29

    void Crypt()
    {
        string command = path_openssl + " enc -aes-256-cbc -in " + db_filename + " -out " \
            + secure_db_filename + " -iter 29 -pass pass:" + password;
        cout << endl << command << endl;
        system(command.c_str());
        if (remove(db_filename.c_str()) != 0)
        {
            cout << "[!] Îøèáêà óäàëåíèÿ ÍÅçàøèôðîâàííîé áàçû äàííûõ!" << endl;
        }
    }
    void Decrypt()
    {
        string command = path_openssl + " enc -aes-256-cbc -d -in " + secure_db_filename + " -out " + \
            db_filename + " -iter 29 -pass pass:" + password;
        cout << endl << command << endl;
        system(command.c_str());
        if (remove(secure_db_filename.c_str()) != 0) {
            cout << "[!] Îøèáêà óäàëåíèÿ çàøèôðîâàííîé áàçû äàííûõ!" << endl;
        }
    }
};