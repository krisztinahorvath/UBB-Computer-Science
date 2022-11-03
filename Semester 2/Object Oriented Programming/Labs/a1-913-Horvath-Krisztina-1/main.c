#include <stdio.h>

int prime_decomposition(int  n, int p)
{
    /**
     * Exponent of a prime number p from the decomposition in prime factors of a given number
     * Input: n, p - non-zero natural numbers, p - prime number
     * Output: return power - the power at which p appears in n */
    int power = 0;
    while(n % p == 0)
    {
        n/=p;
        power++;
    }
    return power;
}

int relatively_prime(int a, int b)
{
    /**
     * Verifies if two integers, a and b, are relatively prime
     * Input: a, b - integer numbers
     * Output: return 1 - if a and b are relatively prime
     *                0 - otherwise
     * */
    if(a <= 0 || b <= 0)
        return 0;

    if(a > b)
    {
        int aux = a;
        a = b;
        b = aux;
    }

    for(int d = 2; d <= b; d++)
        if(a % d == 0 && b % d == 0)
            return 0;

    return 1;
}

void subsequence(int n, int v[], int* start_max, int* len_max) {
    /**
     * Finds the longest subsequence of consecutive relatively prime numbers.
     * Input: n - integer number
     *        v - vector of numbers
     *        start_max - the starting index of the longest subsequence in the vector
     *        len_max - the subsequences length
     * Output: start_max, len_max - the starting index of the longest subsequence, respectively its length
     *                              (if there are more sequences with the maximum length, the first one is chosen)
     *                             - if such and index doesn't exist, both vars are -1
     * */
    *start_max = -1;  /// init the vars
    *len_max = 0;
    int len = 0;  /// length of current subsequence
    int start = -1;  /// the starting index of the current subsequence in the vector
    for (int i = 0; i < n - 1; i++) {
        int prime_nrs = relatively_prime(v[i], v[i + 1]);
        if (prime_nrs == 1) {
            if (start == -1) {
                len = 1;
                start = i;
            } else { len++; }
        } else {
            if (start != -1)
                if (len > *len_max) {
                    *len_max = len + 1;  /// correct number
                    *start_max = start;
                }
            start = -1;
            len = 0;
        }
    }
    if (start != -1) {/// verifying if the longest sequence is the last one, the for doesn't cover that case
        if (len > *len_max) {
            *len_max = len + 1;
            *start_max = start;
        }
        }
    if (*start_max == -1) { /// if no such subsequence is found
        *len_max = -1;
        *start_max = -1;
    }
}

void read(int* n,int v[])
{
    /**
     * Reads numbers from the keyboard until 0.
     * Input: n, v[] - integer number, respectively vector
     * Output: n - the number of read numbers
     *        v[] - the vector that holds the read numbers
     */
    printf("\nPlease introduce numbers until 0 is written!\n");
    int nr;
    printf(" Number: ");
    scanf("%d", &nr);
    while(nr)
    {
        printf("Number: ");
        v[*n]=nr;
        *n = *n + 1;
        scanf("%d", &nr);
    }
}

void print_list(int n, int v[])
{
    /**
     *Prints vector v[] of n positions
     * Input: n - integer number
     *        v[] - vector of integers
     * Output: writing on the screen
     * */
    for(int i = 0; i < n; i++)
        printf(" %d", v[i]);

}

void print_menu()
{
    /**
     Print out the menu of the application!
     void function doesn't return anything
     */
    printf("\n\nMenu:\n"
           "\t1 - read list of numbers\n"
           "\t2 - requirement a\n"
           "\t3 - requirement b\n"
           "\t4 - exit\n"
           "\t5 - lab work\n");
}

void print_subsequence_numbers(int start, int len, int v[])
{
    /**
     * Print out a sequence of numbers from a vector, starting at index start and printing out len numbers
     * Input: start, len, v[] - integers numbers, vector of integers
     * Output: printing on the screen*/
    for(int i = start; i < start + len; i++)
    {
        printf("%d", v[i]);
        printf(" ");
    }
}

void print_subsequence(int start_max, int len_max, int v[])
{
    /**
     * Verifies if there is a subsequence with the given property and prints it out if it exists, otherwise
     * it displays a message
     * Input: start, len, v[] - integers numbers, vector of integers
     * Output: printing on the screen*/
    if(start_max == -1)
        printf("\tNo subsequence found with the given property\n");
    else
    {
        printf("\tThe longest subsequence is: ");
        print_subsequence_numbers(start_max, len_max, v);
    }
}
/// lab activity
/// 1. Generate all the prime numbers smaller than a given natural number n.
int prime(int n)
{
    if(n < 2)
        return 0;
    for(int d = 2; d*d <= n; d++)
        if(n % d == 0)
            return 0;
    return 1;
}
void generate(int n, int v[], int* length)
{
    int i = 0;
    for(int d = 2; d < n; d++)
    {
        if(prime(d))
            v[i++] = d;
    }
    *length = i;
}
int main()
{
    print_menu();
    int option;

    printf("Option:");
    scanf("%d", &option);
    printf("\n");
    int v[100], nr;
    int option_1_selected = 0;
    while(option != 4)
    {
        if(option == 1)
        {
            option_1_selected = 1;
            nr = 0;
            read(&nr, v);
        }
        else if(option == 2)
        {
            int n, p;
            printf("Please introduce n\nn=");
            scanf("%d", &n);
            printf("Please introduce p\np=");
            scanf("%d", &p);
            int exponent = prime_decomposition(n, p);
            printf("The exponent of p in n is: %d", exponent);
        }
        else if(option == 3)
        {
            if(option_1_selected)
            {
                printf("Longest contiguous subsequence such that any two consecutive elements are relatively prime: \n");
                int start_max, len_max;
                subsequence(nr,v,&start_max, &len_max);
                print_subsequence(start_max,len_max, v);
            }
            else
                printf("No list was read, please choose option 1 before choosing option 3!");
        }
        else if(option == 5)
        {
            int n, a[100], len;
            printf("Please introduce a natural number: n=");
            scanf("%d", &n);
            generate(n, a, &len);
            printf("The prime numbers smaller than %d are:\n", n);
            printf("\t");
            print_subsequence_numbers(0, len, a);
        }
        else
            printf("Invalid command!");
        print_menu();
        printf("Option:");
        scanf_s("%d", &option);
        printf("\n");
    }

    return 0;
}
