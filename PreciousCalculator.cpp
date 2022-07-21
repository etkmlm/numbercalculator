#include <iostream>
#include <locale>

using namespace std;

const string charset = "0123456789abcdef";

void to_lower(string* a)
{
    for (int i = 0; i < (long)a->length(); i++)
        (*a)[i] = tolower((*a)[i]);
}

long convert_decimal(string number, int sys)
{
    to_lower(&number);
    const string useset = charset.substr(0, sys);
    long decimal = 0;
    const long len = (long)number.length();
    for(long i = len - 1; i >= 0; i--)
    {
        long ix = len - i - 1;
        decimal += (long)pow(sys, ix) * (int)useset.find(number[i]);
    }
    return decimal;
}

string convert_other(long number, int sys)
{
    string converted;
    long n = 0;
    while (::pow(sys, n) < number)
        n++;
    if ((long)::pow(sys, n) != number)
        n--;
    long collect = 0;
    for(long i = n; i >= 0; i--)
    {
        const long pow = (long)::pow(sys, i);
        const long value = (number - collect) / pow;
        if (collect + value * pow > number)
            converted += '0';
        else
        {
            collect += pow * value;
            converted += charset[value];
        }
    }
    return converted;
}

string add_binary(string number)
{
    if (number[number.length() - 1] == '0')
    {
        number[number.length() - 1] = '1';
        return number;
    }

    for (int i = (int)number.length() - 1; i >= 0; i--)
    {
        if (number[i] == '1')
        {
            number[i] = '0';
            if (i == 0)
                return "1" + number;
        }
        else
        {
            number[i] = '1';
            break;
        }
    }

    return number;
}

string comp_one(string number){
    for (int i = 0; i < (int) number.length(); i++)
        number[i] = number[i] == '0' ? '1' : '0';
    return number;
}

string comp_two(string number)
{
    return add_binary(comp_one(number));
}

string gen_zero(int len)
{
    string gen;
    for (int i = 0; i < len; i++)
        gen += '0';
    return gen;
}

string comp_two_negative(string number)
{
    const long len = (long)number.length();
    long pow = 3;
    while (::pow(2, pow) < len)
        pow++;
    number = gen_zero((long)::pow(2, pow) - len) + number;
    return comp_two(number);
}

int main(int argc, char* argv[])
{
    while (true)
    {
        cout << "What do you want? (To convert decimal 0, others 1)" << endl;
        int input;
        cin >> input;
        if (input == 0)
        {
            cout << "Enter numbering system (2,8,16):  ";
            int sys;
            cin >> sys;
            if (sys != 2 && sys != 8 && sys != 16)
                continue;
            cout << endl << "Enter number to convert decimal:  ";
            string number;
            cin >> number;
            const long dec = convert_decimal(number, sys);
            cout << endl << "Decimal Number: " << dec << endl;
            if (sys == 2)
                cout << "2 Complement (Direct): " << comp_two(number) << endl << "2 Complement (Negative): " + comp_two_negative(number) << endl;
        }
        else
        {
            cout << "Enter a number: ";
            long number;
            cin >> number;
            string binary = convert_other(number, 2);
            cout << endl << "Binary: " << binary << endl << "Octal: " << convert_other(number, 8) << endl << "Decimal: " << number << endl << "Hexadecimal: " << convert_other(number, 16) << endl;
            cout << "2 Complement (Direct): " << comp_two(binary) << endl << "2 Complement (Negative): " + comp_two_negative(binary) << endl;
        }
    }
}

