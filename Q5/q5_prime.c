#include <stdio.h>
unsigned long checks;
int prime_basic(unsigned long n) {
    checks=0; if(n<2) return 0;
    for(unsigned long i=2;i<n;i++){ checks++; if(n%i==0) return 0; }
    return 1;
}
int prime_sqrt_for(unsigned long n) {
    checks=0; if(n<2) return 0;
    for(unsigned long i=2;i<=n/i;i++){ checks++; if(n%i==0) return 0; }
    return 1;
}
int prime_sqrt_while(unsigned long n) {
    checks=0; if(n<2) return 0;
    unsigned long i=2;
    while(i<=n/i){ checks++; if(n%i==0) return 0; ++i; }
    return 1;
}
int prime_sqrt_do(unsigned long n) {
    checks=0; if(n<2) return 0;
    unsigned long i=2;
    do { if(i>n/i) break; checks++; if(n%i==0) return 0; ++i; } while(1);
    return 1;
}
int main(void) {
    unsigned long a[]={97,100,7919,1000003};
    for(int k=0;k<4;k++){
        int p=prime_sqrt_for(a[k]);
        printf("%8lu %-9s divisions = %lu\n",a[k],p?"prime":"not prime",checks);
    }
    puts("Loop variants (while and do-while), same inputs:");
    for(int k=0;k<4;k++) {
        int a1=prime_sqrt_while(a[k]); unsigned long w=checks;
        int a2=prime_sqrt_do(a[k]); unsigned long d=checks;
        printf("%8lu while=%d/%lu do-while=%d/%lu\n",a[k],a1,w,a2,d);
    }
    puts("Sieve alternative: O(N log log N) preprocessing, O(1) per query, O(N) memory.");
    return 0;
}