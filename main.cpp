#include <iostream>
#include <string>

std::string add(std::string I1, std::string I2, int base) {
    if (I1.length() < I2.length()) {
        return add(I2, I1, base);
    }

    int length_diff = I1.length() - I2.length();

    for (int i = 0; i < length_diff; i++) {
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

    int length_diff = I1.length() - I2.length();

    for (int i = 0; i < length_diff; i++) {
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

std::string karatsuba(std::string I1, std::string I2, int base) {
    if (I1.length() == 1 && I2.length() == 1) {
        int product = (I1[0] - '0') * (I2[0] - '0');
        return std::to_string(product);
    }

    if (I1.length() < I2.length()) {
        return karatsuba(I2, I1, base);
    }

    int length_diff = I1.length() - I2.length();

    for (int i = 0; i < length_diff; i++) {
        I2 = "0" + I2;
    }

    int n = I1.length();
    int half = (n + 1)/2;

    std::string a1 = I1.substr(0, half);
    std::string a0 = I1.substr(half);
    std::string b1 = I2.substr(0, half);
    std::string b0 = I2.substr(half);

    std::string p2 = karatsuba(a1, b1, base);
    std::string p1 = karatsuba(add(a1, a0, base), add(b1, b0, base), base);
    std::string p0 = karatsuba(a0, b0, base);

    std::string p3 = sub(p1, add(p2, p0, base), base);

    for (int i = 0; i < n - half; i++) {
        p2 += "00";
        p3 += "0";
    }

    std::string res = add(add(p2, p3, base), p0, base);

    while (res.length() > 1 && res[0] == '0') {
        res.erase(0, 1);
    }

    return res;
}

int main() {
    std::string I1, I2;
    int base;

    std::cin >> I1 >> I2 >> base;
    std::cout << add(I1, I2, base) << " " << karatsuba(I1, I2, base) << " " << 0;
}