#include <iostream>

class AffineCipher {
public:
    void Encrypt(int a, int b, std::string text);
    void Decrypt(int a, int b, std::string text);
    int Modulo(int x, int y);
    int ModInverse(int a, int m);

private:
    std::string message;
};

int AffineCipher::Modulo(int x, int y) {
    int r = x % y;
    return r < 0 ? r + y : r;
}

int AffineCipher::ModInverse(int a, int m) {
    a %= m;

    for (int inv = 1; inv < m; inv++) {
        if ((a * inv) % m == 1)
            return inv;
    }
    return 0;
}

void AffineCipher::Encrypt(int a, int b, std::string text) {
    this->message = "";
    int p, c;

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            if (text[i] >= 'A' && text[i] <= 'Z') {
                p = (int(text[i] - 65));
                c = this->Modulo(((a * p) + b), 26);
                this->message += char(c + 65);
            }
            else if (text[i] >= 'a' && text[i] <= 'z') {
                p = (int(text[i] - 97));
                c = this->Modulo(((a * p) + b), 26);
                this->message += char(c + 97);
            }
        }
        else {
            this->message += text[i];
        }
    }
    std::cout << this->message << std::endl;
}

void AffineCipher::Decrypt(int a, int b, std::string text) {
    int a1 = this->ModInverse(a, 26);
    int b1 = b * -a1;

    this->Encrypt(a1, b1, text);
}


int main()
{
    AffineCipher Cipher;
    std::string input;
    int a, b, enc;
    
    std::cout << "Enter text to be encrypted/decrypted" << std::endl;
    std::getline(std::cin, input);
    
    std::cout << "Enter 1 (Encrypt) or 0 (Decrypt), followed with key a b, ex. 1 1 2: ";
    std::cin >> enc >> a >> b;

    if (enc) {
        std::cout << "Encrypted message: " << std::endl;
        Cipher.Encrypt(a, b, input);
    }
    else {
        std::cout << "Decrypted message: " << std::endl;
        Cipher.Decrypt(a, b, input);
    }
    
    return 0;
}