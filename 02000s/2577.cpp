#include<stdio.h>

int main() {
    int a, b, c, mul, count[10] = {0, };
    scanf("%d %d %d", &a, &b, &c);
    mul = a*b*c;
    while(mul) {
        count[mul%10]++;
        mul /= 10;
    }
    for(int i=0; i<10; i++) printf("%d\n", count[i]);
}
