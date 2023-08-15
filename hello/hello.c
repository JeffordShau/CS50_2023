#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Insert Name: ");
    printf("hello, %s\n", name);
}