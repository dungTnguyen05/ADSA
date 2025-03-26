#include <iostream>
#include <string>

std::string add(std::string I1, std::string I2, int base) {
    if (I1.length() < I2.length()) {
        return add(I2, I1, base);
    }

    for (int i = 0; i < I1.length() - I2.length(); i++) {
        I2 = "0" + I2;
    }

    std::string res = "";
    int sum = 0, carry = 0;

    for (int i = I1.length() - 1; i >= 0; i--) {
        sum = (I1[i] - '0') + (I2[i] - '0') + carry;
        carry = sum/base;
        sum %= base;
        res = char(sum + '0') + res;
    }

    if (carry > 0) {
        res = char(carry + '0') + res;
    }

    return res;
}

std::string sub(std::string I1, std::string I2, int base) {
    if (I1.length() < I2.length()) {
        return sub(I2, I1, base);
    }

    for (int i = 0; i < I1.length() - I2.length(); i++) {
        I2 = "0" + I2;
    }

    std::string res = "";
    int diff = 0, borrow = 0;

    for (int i = I1.length() - 1; i >= 0; i--) {
        diff = (I1[i] - '0') - (I2[i] - '0') - borrow;

        if (diff < 0) {
            diff += base;
            borrow = 1;
        }

        else {
            borrow = 0;
        }

        res = char(diff + '0') + res;
    }

    while (res.length() > 1 && res[0] == '0') {
        res.erase(0, 1);
    }

    return res;
}

int main() {

}