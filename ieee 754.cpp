#include <iostream>

#include <string>

#include <cmath>

using namespace std;

int main() {
    cout << "  Standard representations" << endl;
    cout << "  s - sign; e - exponants; i - implicit;m - mantissa" << endl;
    cout << "  s.hhhhhhhhhhhh.i.mmmmm - any number " << endl;
    cout << "  0.000000000000.0.00000 - Zero" << endl;
    cout << "  0.000000000001.1.00000 - Minimal absolute value(close to 1*2^-2046)" << endl;
    cout << "  0.111111111110.1.11111 - Max positive(1.96875*2^2047)" << endl;
    cout << "  1.111111111110.1.11111 - Min negative(-1.96875*2^2047)" << endl;
    cout << "  0.011111111111.1.00000 - One or +1,0E0" << endl;
    cout << "  0.111111111111.1.00000 - Positive infinity" << endl;
    cout << "  1.111111111111.1.00000 - Negative infinity" << endl;
    cout << "  1.000000000000.0.11001 - Not normalized" << endl;
    cout << "  0.111111111111.1.11011 - Not a number(1.84375*2^2048)" << endl;
    double value;
    int rem;
    int e;
    unsigned long long binary = 0;
    unsigned long long multiplicator = 1;
    cout << "Enter value: " << endl;
    if (!(cin >> value)) {
        cout << "Wrong input" << endl;
        return 0;
    }
    if (value == 0) {
        cout << "0.000000000000.0.00000" << endl;
        return 0;
    }
    if (value > (1.96875 * pow(2, 2047)) || value < -1.96875 * pow(2, 2047) || fabs(value) < 1 * pow(2, -2046)) {
        cout << "Wrong input" << endl;
        return 0;
    }
    int modintvalue = fabs(value);
    double fraction = fabs(value) - modintvalue;
    while (modintvalue > 0) {
        rem = modintvalue % 2;
        modintvalue /= 2;
        binary += rem * multiplicator;
        multiplicator *= 10;
    }
    string int_binary = to_string(binary);
    string fraction_binary = "";
    while (fraction > 0) {
        double temp = fraction * 2;
        int inttemp = temp;
        if (inttemp == 0) fraction_binary += "0";
        else fraction_binary += "1";

        fraction = temp - inttemp;
    }
    string full = int_binary + fraction_binary;
    if (binary == 0) {
        for (int i = 0; i < fraction_binary.length(); ++i) {
            if (fraction_binary[i] == '1') {
                e = -(i + 1);
                break;
            }
        }
    } else e = int_binary.length() - 1;
    double bias = pow(2, 11) - 1;
    int E = e + bias;
    binary = 0;
    multiplicator = 1;
    while (E > 0) {
        rem = E % 2;
        E /= 2;
        binary += rem * multiplicator;
        multiplicator *= 10;
    }
    string E_binary = to_string(binary);
    string E_format = "000000000000";
    string mantisa_format = "00000";
    int i = E_binary.length() - 1;
    for (int j = E_format.length() - 1; j > -1; j--) {
        E_format[j] = E_binary[i];
        if (i == 0) break;
        i--;

    }
    int flag;
    if (e >= 0) {
        for (int j = 0; j < min(mantisa_format.length(), full.length()); ++j) {
            if (j == min(mantisa_format.length() - 1, full.length() - 1)) break;
            mantisa_format[j] = full[j + 1];

        }
    } else {
        for (int j = 0; j < fraction_binary.length(); ++j) {
            if (fraction_binary[j] == '1') {
                flag = j;
                break;
            } else flag = 0;
        }
        for (int t = 0; t < min(fraction_binary.length() - 1, mantisa_format.length()); ++t) {
            mantisa_format[t] = fraction_binary[flag + 1];
            flag++;
        }
    }
    string sign = "0";
    if (value < 0) {
        sign = "1";
    }
    int implicit = 1;

    cout << sign << "." << E_format << "." << "1" << "." << mantisa_format << endl;
}