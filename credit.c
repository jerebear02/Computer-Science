#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");

    int sum = 0;
    int digit_count = 0;
    int first_digit = 0;
    int first_two_digits = 0;

    long temp = number;
    bool second = false;

    // Luhn’s Algorithm
    while (temp > 0)
    {
        int digit = temp % 10;

        if (second)
        {
            int doubled = digit * 2;
            sum += (doubled / 10) + (doubled % 10);
        }
        else
        {
            sum += digit;
        }

        second = !second;
        temp /= 10;
        digit_count++;
    }

    // Get first digit(s)
    temp = number;
    while (temp >= 10)
    {
        temp /= 10;
    }
    first_digit = temp;

    temp = number;
    while (temp >= 100)
    {
        temp /= 10;
    }
    first_two_digits = temp;

    // Check validity
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (digit_count == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (digit_count == 16 && (first_two_digits >= 51 && first_two_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((digit_count == 13 || digit_count == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
