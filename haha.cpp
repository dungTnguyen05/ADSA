#include <iostream>
#include <string>

std::string school_method_add(std::string l1, std::string l2, int base) {
    if (l1.length() < l2.length()) {
        return school_method_add(l2, l1, base);
    }
    
    for (int i = 0; i < (l1.length() - l2.length()); i++) {
        l2 = "0" + l2;
    }

    std::string sum = "";
    int curr = 0, carry = 0;

    for (int i = l1.length() - 1; i >= 0; i--) {
        curr = (l1[i] - '0') + (l2[i] - '0') + carry;
        carry = (int)(curr/base);
        curr = curr % base;
        sum = (char)(curr + '0') + sum;
    }

    if (carry > 0) {
        sum = (char)(carry + '0') + sum;
    }

    return sum;
}

int main() {
    std::string l1, l2;
    int b;
    std::cin >> l1;
    std::cin >> l2;
    std::cin >> b;

    std::cout << school_method_add(l1, l2, b);
}