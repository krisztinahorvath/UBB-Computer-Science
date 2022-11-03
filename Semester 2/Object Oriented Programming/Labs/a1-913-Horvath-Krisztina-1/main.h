//
// Created by krisz on 2/24/2022.
//

#ifndef A_1_MAIN_H
#define A_1_MAIN_H

int prime_decomposition(int  n, int p);
int relatively_prime(int a, int b);
void subsequence(int n, int v[], int* start_max, int* len_max);
void read(int* n,int v[]);
void print_list(int n, int v[]);
void print_menu();
void print_subsequence_numbers(int start, int len, int v[]);
void print_subsequence(int start_max, int len_max, int v[]);
int main();

#endif //A_1_MAIN_H
