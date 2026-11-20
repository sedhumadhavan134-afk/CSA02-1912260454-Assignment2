#include <stdio.h>
int main(void) {
    double balance=10000.0, rate=0.02, repayment=2000.0, total_interest=0.0;
    int month=0, limit=360;
    puts("Month Opening Interest Payment Closing");
    while(balance>0.005 && month<limit) {
        ++month;
        double interest=balance*rate;
        double due=balance+interest;
        double payment=repayment<due?repayment:due;
        balance=due-payment;
        if(balance<0.005) balance=0.0;
        total_interest+=interest;
        printf("%5d %7.2f %8.2f %7.2f %7.2f\n",month,due-interest,interest,payment,balance);
        if(repayment<=interest && balance>0.0) { puts("Repayment does not reduce principal; loan cannot amortize."); break; }
    }
    if(balance==0.0) printf("Repaid in %d months; total interest = Rs %.2f\n",month,total_interest);
    else if(month>=limit) printf("Safety limit reached; outstanding = Rs %.2f\n",balance);
    return 0;
}