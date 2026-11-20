#include <stdio.h>
char grade_switch(int marks) {
    if(marks<0 || marks>100) return '?';
    switch(marks/10) {
        case 10: case 9: return 'S';
        case 8: return 'A';
        case 7: return 'B';
        case 6: return 'C';
        case 5: return 'D';
        default: return 'F';
    }
}
char grade_ladder(int m) {
    if(m<0 || m>100) return '?';
    if(m>=90) return 'S';
    else if(m>=80) return 'A';
    else if(m>=70) return 'B';
    else if(m>=60) return 'C';
    else if(m>=50) return 'D';
    return 'F';
}
int main(void) {
    int tests[]={100,90,89,84,80,79,75,70,69,60,59,50,49,0,-1,101};
    for(unsigned i=0;i<sizeof tests/sizeof tests[0];i++)
        printf("%3d : ladder=%c switch=%c\n",tests[i],grade_ladder(tests[i]),grade_switch(tests[i]));
    puts("Scholarship example: grade S/A and income <= 300000 => full; grade B/C and income <= 200000 => partial.");
    return 0;
}