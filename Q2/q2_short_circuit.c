#include <stdio.h>
static unsigned long calls;
static int verify_card(int id) { (void)id; ++calls; return 1; }
int main(void) {
    unsigned long senior_first=0, card_first=0, bitwise_calls=0;
    /* Deterministic sample: 1000 passengers; 200 seniors, 500 eligible,
       100 disability-card holders. Pattern is fixed for reproducibility. */
    for (int i=0;i<1000;i++) {
        int senior = i < 200;
        int eligible = (i % 2 == 0);
        int disability = (i % 10 == 0);
        calls=0;
        int grant = (senior && eligible) || verify_card(i) && disability;
        (void)grant; senior_first += calls;
        calls=0;
        grant = (verify_card(i) && disability) || (senior && eligible);
        (void)grant; card_first += calls;
        calls=0;
        /* Bitwise operators evaluate both operands; the call is unconditional. */
        grant = ((senior & eligible) | (verify_card(i) & disability));
        (void)grant; bitwise_calls += calls;
    }
    printf("Passengers: 1000\nCalls, senior-first order: %lu\n", senior_first);
    printf("Calls, card-check-first order: %lu\n", card_first);
    printf("Calls, bitwise & and |: %lu\n", bitwise_calls);
    puts("Nested-if implementation can preserve short-circuit behaviour.");
    return 0;
}