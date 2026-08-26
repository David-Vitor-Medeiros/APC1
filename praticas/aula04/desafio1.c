#include <stdio.h>

int main() {
    
    int x = 5 / 2; 
    
    int y = x++;   
    
    int z = x % 2; 

    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("z = %d\n", z);

    return 0;
}
