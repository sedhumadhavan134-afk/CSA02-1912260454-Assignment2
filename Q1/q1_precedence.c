#include <stdio.h>
int main(void) {
    /* Integer arithmetic is retained to expose the original truncation. */
    int price, qty, senior;
    const int p[3] = {100, 250, 400};
    const int q[3] = {2, 3, 2};
    const int s[3] = {1, 0, 1};
    puts("price qty senior | original total/net | corrected total/net");
    for (int k=0;k<3;k++) {
        price=p[k]; qty=q[k]; senior=s[k];
        int total = price * qty - price * qty * 15 / 100 * senior
                    + price * qty * 5 / 100;
        int net = total > 1000 ? total - 50 : total;
        int gross = price * qty;
        double discount = senior ? gross * 0.15 : 0.0;
        double tax = (gross - discount) * 0.05;
        double correct = gross - discount + tax;
        double correct_net = correct > 1000.0 ? correct - 50.0 : correct;
        printf("%5d %3d %6d | %6d/%6d | %9.2f/%9.2f\n",
               price,qty,senior,total,net,correct,correct_net);
    }
    /* count = count++ + 1 has undefined behaviour: count is modified twice
       without a sequencing point. Do not execute this expression. */
    return 0;
}