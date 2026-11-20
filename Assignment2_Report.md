# C Programming Assignment 2 – CO2 Report

**Student:** Sedhu Madhavan V  
**Register number:** 1912260454  
**Institution:** SIMATS, Chennai  
**Course:** Electronics and Communication Engineering  
**GitHub:** https://github.com/sedhumadhavan134-afk/CSA02-1912260454-Assignment2

> Verification note: source files and predicted/test data are supplied here. Run the commands in README on the target GCC installation, replace the compiler-version placeholder with the actual version, and attach genuine terminal screenshots. Do not describe an unrun local test as executed evidence.

## Q1 – Precedence, associativity and billing
Multiplication, division and remainder bind more tightly than addition/subtraction; operators of the same precedence associate left-to-right. Assignment associates right-to-left. The conditional operator has lower precedence than arithmetic and relational operators. In the supplied expression, `price * qty * 15 / 100 * senior` is evaluated left-to-right within the multiplicative group; with integer operands, division truncates. GST is calculated on gross rather than on the discounted subtotal, which differs from the intended tax base. The expression `count = count++ + 1` has undefined behaviour because the same scalar is modified more than once without sequencing; do not rely on any output or compiler warning to define its result. `-Wall` may warn, but a warning is not guaranteed to diagnose every undefined behaviour.

Recommended design: calculate gross, discount, taxable subtotal and tax as named intermediate values, preferably using double for currency calculations, then apply the Rs 50 threshold discount. The number of arithmetic operations remains O(1), and temporary storage is O(1); readability and auditability improve.

| Price | Qty | Senior | Original total | Intended calculation (before threshold) |
|---:|---:|---:|---:|---:|
| 100 | 2 | 1 | 181 | Rs 178.50 |
| 250 | 3 | 0 | 787 | Rs 787.50 |
| 400 | 2 | 1 | 724 | Rs 714.00 |

These are hand-derived expected values; confirm with the compiled program. The sample C program prints original and corrected totals.

## Q2 – Short-circuit evaluation
C guarantees left-to-right short-circuit behaviour for `&&` and `||`: the right operand is skipped when the left operand determines the result. Bitwise `&` and `|` evaluate both operands and are not substitutes for logical operators. The sample program uses 1,000 deterministic passenger records and counts calls to the simulated server verification function for two operand orders and for bitwise evaluation. Because the verification function is also specified to write an audit record, a deployment decision must consider audit completeness: if every passenger must be logged, do not skip the audit call; perform it explicitly and store its result before applying the logical policy. For nested if statements, place cheap/high-rejection tests first when the expensive check is safe to skip. With mandatory auditing, perform the audit unconditionally.

Complexity: O(n) total passenger processing and O(1) auxiliary space; the number of expensive calls ranges from fewer than n to n depending on condition order and policy.

## Q3 – Bitwise device register
Each device is represented by bit `dev` in an unsigned byte. Set: `reg | (1u << dev)`; clear: `reg & ~(1u << dev)`; toggle: `reg ^ (1u << dev)`; test: `(reg & (1u << dev)) != 0`. Trace: initial 00000000; LIGHT on -> 00000001; AC on -> 00000101; FAN toggle -> 00000111; LIGHT off -> 00000110. Expected display: `00000101`, then `00000110`; AC ON and PUMP OFF. The expression `reg & 1 << dev` parses as `reg & (1 << dev)` because shift has higher precedence than bitwise AND; `(reg & 1) << dev` tests only bit zero before shifting, so it is different. Use unsigned types: signed left shifts and signed high-bit representations can be problematic.

Alternative array: `char state[8]`. Both update and test operations are O(1); counting ON devices is O(8)=O(1) for a fixed eight devices. A packed byte uses 1 byte per home, while eight char flags use 8 bytes per home: for one million homes, approximately 1 MB versus 8 MB (excluding metadata/alignment).

## Q4 – Decision-making and switch
The else-if ladder checks ordered ranges directly. A switch on `marks / 10` groups integer tens and needs a special case for 100 (marks/10 == 10). Input validation must happen before either decision structure. Boundary test set: -1, 0, 49, 50, 59, 60, 69, 70, 79, 80, 89, 90, 99, 100, 101. Missing break/return causes fall-through into later cases. A switch cannot directly express arbitrary relational ranges; the controlling expression is matched against constant case labels. A lookup table gives O(1) grade lookup with O(11) storage; the ladder has up to six comparisons; switch is typically constant-time in this small mapping but the C standard does not promise a particular implementation. For scholarship logic, validate marks and income first, determine grade, then use a clearly documented nested decision or table.

## Q5 – Prime checking and loop counts
A composite integer n has a factor no greater than its square root. Use `i <= n / i` to avoid multiplication overflow from `i*i`; increment the division counter once per modulo test. The do-while loop needs an explicit boundary check before its first test for n=2 or 3. Trial division through n-1 is O(n); square-root trial division is O(sqrt(n)) time and O(1) space. For the supplied square-root loop, expected modulo-test counts are:

| n | Result | Divisor tests |
|---:|---|---:|
| 97 | prime | 8 |
| 100 | not prime | 1 |
| 7919 | prime | 87 |
| 1000003 | prime | 999 |

The Sieve of Eratosthenes is O(N log log N) preprocessing and O(1) per lookup with O(N) memory; it is useful for many queries up to a fixed N.

## Q6 – Loan repayment and termination
Use a while loop because the number of months is not known in advance and the loop continues while a positive balance remains. Each month: interest = opening balance × monthly rate; amount due = opening balance + interest; payment = min(fixed repayment, amount due); closing balance = amount due − payment. Set a small tolerance to zero to avoid floating-point equality checks. If repayment is no greater than the monthly interest, principal does not decrease; detect this and stop with a clear warning. Apply a 360-month safety limit. For Rs 10,000 at 2% with Rs 2,000 repayment, hand-check the opening balance and interest month by month against program output. A direct logarithmic formula can estimate the month count in O(1), but periodic rounding and a smaller final payment make month-by-month simulation preferable for a statement schedule. Simulation takes O(m) time and O(1) space for m months; the formula is O(1) time and O(1) space but is sensitive to assumptions and floating-point precision.

## Q7 – Day-4 design challenge: skip even divisors
**Bottleneck:** the baseline square-root trial division tests every integer divisor from 2 through floor(sqrt(n)); even candidates above 2 cannot divide an odd n.  
**Measurable objective:** reduce modulo operations for odd candidates by at least approximately 40% while preserving the same primality result.  
**Redesign:** handle n<2, n==2 and even n separately; then test only odd divisors starting at 3, using `d <= n/d`.  
**Pseudocode:**
```
if n < 2: composite
if n == 2: prime
if n is even: composite
for d = 3; d <= n/d; d = d + 2:
    count one modulo operation
    if n mod d == 0: composite
prime
```
**Prediction:** for large odd primes, the redesigned loop performs roughly half as many modulo operations as the all-integer square-root loop. It uses O(1) extra space and remains O(sqrt(n)) time, with a smaller constant factor. The Q7 program compares both methods on identical inputs and prints measured test counts. For tiny inputs the added branches may outweigh the saved work; for a very large number of queries, a sieve or probabilistic/deterministic advanced primality method may be more appropriate.

## Final recommendation
Use named intermediate values for financial expressions, logical operators for conditions, unsigned bit masks for registers, explicit boundary validation, square-root divisor limits, and a bounded loan simulation. Keep raw operation counts and screenshots generated on the student's own compiler as evidence. Review and understand every program before the viva.
