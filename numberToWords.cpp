/*
 *
 * ENUNCIADO
 * ===================================================
 * Realizar un programa C++ que lea un numero real
 * (correspondiente a un monto) y convertir este monto a
 * palabra.
 *
 * El # tiene mascara 999,999,999.99
 * Solo llevar a palabras la parte entera del numero
 *
 * Integrantes:
 * Jorge Saldivar - 1105996
 * Victor Jimenez - 1106003
 *
 * Fecha de entrega: 23/06/2022
 *
 **/

#include <iostream>
using namespace std;

// NUMBERS DICTIONARY
string oneDigit[9] = {"Uno", "Dos", "Tres", "Cuatro", "Cinco", "Seis", "Siete", "Ocho", "Nueve"};
string twoDigits[10] = {"Diez", "Once", "Doce", "Trece", "Catorce", "Quince", "Dieciséis ", "Diecisiete", "Dieciocho", "Diecinueve"};
string tensDigits[9] = {"", "Veinte", "Treinta", "Cuarenta", "Cincuenta", "Sesenta", "Setenta", "Ochenta", "Noventa"};
string threeDigits[9] = {"Ciento", "Doscientos", "Trecientos", "Cuatrocientos", "Quinientos", "Seiscientos", "Setecientos", "Ochocientos", "Novecientos"};

// parse from number to words numbers of three digits
string parseNumberToWords(int number, string suffix)
{
    if (number == 0)
        return "";

    if (number == 100)
        return "Cien " + suffix + " ";

    string result;

    // three digits divider
    if (number > 99 && number <= 999)
    {
        int numIndex = number / 100;
        result += threeDigits[numIndex - 1];
        number % 100 == 0 ? result = suffix + " " : result += " " + parseNumberToWords(number % 100, suffix);
        return result;
    }
        // two digits divider
    else if (number > 19 && number <= 99)
    {
        int numIndex = number / 10;
        result += tensDigits[numIndex - 1] + " ";
        number % 10 == 0 ? result += suffix + " " : result += " y " + parseNumberToWords(number % 10, suffix);
        return result;
    }
        // range from 10 to 19 divider
    else if (number >= 10 && number < 20)
    {
        return twoDigits[number - 10] + " " + suffix + " ";
    }
        // one digit divider
    else if (number < 10)
    {
        if (!suffix.empty() && oneDigit[number - 1] == "Uno")
        {
            return suffix == "Millones" ? "Un Millon " : suffix + " ";
        }
        return oneDigit[number - 1] + " " + suffix + " ";
    }
    else
    {
        // Return nothing if not valid number passed
        return "";
    }
}

// Methods to concat three digits number and return the full number as one
string numberToWords(double _number)
{
    // comment the code below to print "Cero" and remove character validation
    if (_number <= 0)
    {
        cout << "Invalid number" << endl;
        return "";
    }

    // returns "Cero" when 0 passed as number alone
    if (_number == 0)
        return "Cero";

    string result;

    // getting cents as integer
    double cents = (_number - int(_number)) * 100;

    // getting number without decimals
    int number = int(_number);

    // validate number length to check if it's over the limit
    int length = to_string(number).length();
    if (length > 9)
    {
        cout << "Number too large" << endl;
        return "";
    }

    // return millions
    result += parseNumberToWords((number / 1000000) % 100000, "Millones");

    // return thousands
    result += parseNumberToWords((number / 1000) % 1000, "Mil");

    // return hundreds
    result += parseNumberToWords(number % 1000, "");

    // return cents
    result += "con " + to_string(int(cents)) + "/100 centavos";

    return result;
}

int main()
{
    double insertedNumber;
    cout << "Enter a number: ";
    cin >> insertedNumber;
    cout << numberToWords(insertedNumber) << endl;
    return 0;
}

#pragma clang diagnostic pop