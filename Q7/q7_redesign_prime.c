#include <stdio.h>
unsigned long long original_checks, redesigned_checks;
int original_prime(unsigned long n) {
    original_checks=0; if(n<2) return 0;
    for(unsigned long d=2;d<=n/d;d++){ original_checks++; if(n%d==0) return 0; }
    return 1;
}
int redesigned_prime(unsigned long n) {
    redesigned_checks=0; if(n<2) return 0;
    if(n==2) return 1;
    if(n%2==0){ redesigned_checks++; return 0; }
    for(unsigned long d=3;d<=n/d;d+=2){
        redesigned_checks++;
        if(n%d==0) return 0;
    }
    return 1;
}
int main(void) {
    unsigned long values[]={97,100,7919,1000003,2147483647UL};
    puts("n original_result original_checks redesigned_result redesigned_checks");
    for(unsigned i=0;i<sizeof values/sizeof values[0];i++){
        int a=original_prime(values[i]), b=redesigned_prime(values[i]);
        printf("%lu %d %llu %d %llu\n",values[i],a,original_checks,b,redesigned_checks);
    }
    return 0;
}