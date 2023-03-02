#include <iostream>
#include <string>
#include <cmath>
using namespace std;
unsigned long long to_binary(int value){
int rem;
unsigned long long binary = 0;
unsigned long long multiplicator = 1;
while (value > 0){
rem = value % 2;
value /= 2;
binary += rem * multiplicator;
multiplicator *= 10;
}
return binary;
}
string fraction_to_binary(double fraction){
string fraction_binary = "";
while (fraction > 0)
{
double temp = fraction * 2;
int inttemp = temp;
if (inttemp == 0)
fraction_binary += "0";
else
fraction_binary += "1";
fraction = temp - inttemp;
}
return fraction_binary;
}
int
main ()
{ // output 10 standard
cout << " Standard representations" << endl;
cout << " s - sign; e - exponants; i - implicit;m - mantissa" << endl;
cout << " s.hhhhhhhhhhhh.i.mmmmm - any number " << endl;
cout << " 0.000000000000.0.00000 - Zero" << endl;
cout << " 0.000000000001.1.00000 - Minimal absolute value(close to "
"1*2^-2046)"
<< endl;
cout << " 0.111111111110.1.11111 - Max positive(1.96875*2^2047)" << endl;
cout << " 1.111111111110.1.11111 - Min negative(-1.96875*2^2047)" << endl;
cout << " 0.011111111111.1.00000 - One or +1,0E0" << endl;
cout << " 0.111111111111.1.00000 - Positive infinity" << endl;
cout << " 1.111111111111.1.00000 - Negative infinity" << endl;
cout << " 1.000000000000.0.11001 - Not normalized" << endl;
cout << " 0.111111111111.1.11011 - Not a number(1.84375*2^2048)" << endl;
double value;
string x_num;
cout << "Enter value: "<< endl;
cout << "Please, enter your x value: ";
cin >> x_num;
bool is_number = true;
int countofdots=0;
for (char c: x_num) {
if(countofdots>1){
cout << "Argument is not a number!" << endl;
return 0;
}
if (!isdigit(c) && c != '.') {
is_number = false;
break;
}
if(c == '.'){
countofdots++;
}
}
if (!is_number) {
cout << "Argument is not a number!" << endl;
return 0;
}
value = stod(x_num);
cout << "Entered number: " << value << endl;
if (value == 0)
{
cout << "0.000000000000.0.00000" << endl;
return 0;
}
//Convert the integer part of the input number to binary
int modintvalue = fabs (value);
double fraction = fabs (value) - modintvalue;
unsigned long long binary = to_binary(modintvalue);
string int_binary = to_string (binary);
cout << "Binary integer: " << int_binary << endl;
//Convert the fractional part of the number to binary.
// Write the binary representation of the number together. Write the mantissa with an implicit
string fraction_binary = fraction_to_binary(fraction);
string mantisa = int_binary + fraction_binary;
cout << "Mantisa with implicit: " << mantisa<<endl;
//Find how many bits the point has moved after normalization and write it to the variable exp.
int exp;
if (binary == 0)
{
for (int i = 0; i < fraction_binary.length (); ++i)
{
if (fraction_binary[i] == '1')
{
exp = -(i + 1);
break;
}
}
}
else
exp = int_binary.length () - 1;
cout << "Number of bits by which point shifted: " << abs (exp) << endl;
//Find the characteristic by adding exp + bias (bias is calculated using the formula 2^((number of bits of
the characteristic)-1) -1;
double bias = pow (2, 11) - 1;
int E = exp + bias;
//Convert the characteristic to binary.
binary = to_binary(E);
string E_binary = to_string (binary);
cout << "Binary characteristic : " << E_binary << endl;
// Fill the specified number of bits of the characteristic (12) with the obtained value
string E_format = "000000000000";
string mantisa_format = "00000";
int i = E_binary.length () - 1;
for (int j = E_format.length () - 1; j > -1; j--)
{
E_format[j] = E_binary[i];
if (i == 0)
break;
i--;
}
cout << "Formated characteristic : " << E_format << endl;
//If we shifted the point to the left, the mantissa is filled after the first unit of the integer part,
// if to the right, it is filled after the first unit of the fractional part.
int flag;
if (exp >= 0)
{
for (int j = 0; j < min (mantisa_format.length(), mantisa.length ());
++j)
{
if (j == min (mantisa_format.length () , mantisa.length () - 1))
break;
mantisa_format[j] = mantisa[j + 1];
}
}
else
{
for (int j = 0; j < fraction_binary.length (); ++j)
{
if (fraction_binary[j] == '1')
{
flag = j;
break;
}
else
flag = 0;
}
for (int t = 0;
t < min (fraction_binary.length () - 1, mantisa_format.length ());
++t)
{
mantisa_format[t] = fraction_binary[flag + 1];
flag++;
}
}
cout<<"Formated mantisa: "<<mantisa_format<<endl;
// calculating sign bit
string sign = "0";
if (value < 0)
{
sign = "1";
}
int implicit = 1;
cout << "Sign: " << sign << endl;
cout << sign << "." << E_format << "." << "1" << "." << mantisa_format << endl;
}
