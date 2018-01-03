/* Lenny Harrison - Modular Exponentiation Program - 2017

Purpose: The program generates random 16-bit binary numbers that will be
         converted to decimal. Using Modular Exponentiation, the program then
		 determines if the number converted is ACTUALLY prime verus a hand method
		 where the the number is prime. 

Pre-Conditions: The program generates a random 16-bit binary number

Post-Conditions: The program returns the number and whether it is prime or ACTUALLY prime */


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

int bintodec(string str) //Function for Binary to Decimal
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != '0' && str[i] != '1')
        {
            return -1;
        }
    }
    int total = 0; //Accumulator
    for (int i = 0; i <str.size(); i++) //For loop to read size
    {
        if (str[i] == '1') //Place 1 for binary
        {
            total += pow(2, i); //Binary placement
        }
    }
    return total;
}

string RandomBinary(int n) // Function to generate random binary numbers
{
    string bits = "01"; // Initialize as string and then convert to integer for easy indexing
    string result = "";
    for (int i = 0; i < n - 1; i++)
    {
        int bit = rand() % 2;
        result += bits[bit];
    }
    result += "1";

    return result; // return result
}

int modexp(int base, int exponent, int m)
{
    vector<int> results;
    results.push_back(base % m);

    int index = 0;
    for (int i = 2; i <= exponent; i *= 2)
    {
        results.push_back(results[index] * results[index] % m);
        index++;
    }

    unsigned long long result = 1;
    for (int i = results.size() - 1; i >= 0; i--)
    {
        if (exponent - pow(2, i) >= 0)
        {
            result *= results[i];
            exponent -= pow(2, i);
        }
    }

    return result % m;
}

bool isPrime(string num)
{
    unsigned long long n = bintodec(num);
    if (modexp(3, n - 1, n) ==  1 % n)
        return true;
    else
        return false;
}

bool isActuallyPrime(string num)
{
    unsigned long long n = bintodec(num);
    for (int i = 2; i < sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

//Main Program
int main()
{
    srand(unsigned int(time(NULL)));
    vector<string> nums;

    for (int i = 0; i < 100; i++)
    {
        nums.push_back(RandomBinary(16));
    }

    for (int i = 0; i < 100; i++)
    {
        if (isPrime(nums[i]))
        {
            cout << nums[i] << " (" << bintodec(nums[i]) << ") is prime." << endl;
        }

        if (isActuallyPrime(nums[i]))
        {
            cout << nums[i] << " (" << bintodec(nums[i]) << ") is ACTUALLY prime." << endl;
        }
    }

    system("PAUSE");
    return 0;
}
