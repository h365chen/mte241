<!-- layout: true -->

<!-- class: middle -->

---

<!-- class: center, middle, inverse -->

# MTE 241 Tutorial

.invisible-slide-comment[See [README](./README.md) to turn this markdown to a slide presentation]

## C Basics and Practice Questions

Presented by Huanyi Chen

huanyi.chen@uwaterloo.ca

---

## Roadmap

- `printf` in C using format specifiers such as `%d` and `%f`

- Bytes and bits

- Function pointers

- Practice question from Chapter 2

---

### Using printf in C

```c
#include <stdio.h>

int main() {
    int a = 5;
    float b = 0.3;
    long c = 5;
    double d = 0.3;
    printf("a: %d, b: %f\r\n", a, b);
    printf("c: %ld, d: %lf\r\n", c, d);
    return 0;
}
```

`%d`, `%f`, `%ld`, and `%lf` are all format specifiers.

---

The definition of `printf` usually looks like

```c
int printf(const char *format, ...);
```

You need to tell `printf` the number of bytes to retrieve for printing.

Think: what will be printed by the following code?

```c
    double d = 0.3;
    printf("d: %ld\r\n", d);
```

---

`0.3` in binary

```
0.3 x2 = 0.6  -> 0
0.6 x2 = 1.2  -> 1
0.2 x2 = 0.4  -> 0
0.4 x2 = 0.8  -> 0
0.8 x2 = 1.6  -> 1
0.6 x2 = 1.2  -> 1
0.2 x2 = 0.4  -> 0
      ...
```

```
0.3 = 0.0100 1100 1100 1100 (0.0011 repeating) = 1.00110011... x  2^(-2)
```

---

IEEE-754 binary64 encoding

```md
sign exponent    fraction
   0 01111111101 0011001100110011001100110011001100110011001100110011

0011 1111 1101 0011 0011 0011 0011 0011 0011 0011 0011 0011 0011 0011 0011 0011
   3    F    D    3    3    3    3    3    3    3    3    3    3    3    3    3  <- hexadecimal
```

And `0x3FD3333333333333` is `4599075939470750515` (base 10)

---

### Bytes and Bits

Have you heard about 32-bit machines and 64-bit machines? 

What do 32 and 64 mean in this context?

Is the Nucleo-F401RE 32-bit or 64-bit?

???

The numbers 32 and 64 refer to the width of the processor's registers. In a 32-bit system, registers are 32 bits wide, and in a 64-bit system, it is 64 bits wide.

---

1 Byte = 8 bits, or 1B = 8b (yea, that's it)

--

There is another more interesting unit, _word_, which corresponds to the width of the processor’s registers

| Unit     | Bits per unit | Bytes per unit | Typical usage                  |
| -------- | ------------- | -------------- | ------------------------------ |
| **Bit**  | 1             | 1/8            | Data rates (e.g. Mbps)         |
| **Byte** | 8             | 1              | Storage sizes (e.g. MB, GB)    |
| **Word** | 16, 32, 64 ...| 2, 4, 8 ...    | CPU register width & bus width |

---

```c
#include <stdio.h>

int main() {
    unsigned int a = 5;  // 0101 in bits
    unsigned int b = 9;  // 1001 in bits
    printf("a & b = %d\n", a & b);
    printf("a | b = %d\n", a | b);
    printf("a ^ b = %d\n", a ^ b);
    return 0;
}
```

---

### Function Pointers

Function pointers allow you to determine which function to call at runtime.

```c
#include <stdio.h>
int add1(int a, int b) { return a * 10 + b; }
int add2(int a, int b) { return a + b * 10; }

int main() {
    int (*operation)(int, int);
    int choice;
    printf("Choose function: 1 for add1, 2 for add2: ");
    scanf("%d", &choice);
    if (choice == 1) { operation = add1; } 
    else if (choice == 2) { operation = add2; } 
    else { printf("Invalid choice!\n"); return 1; }
    printf("Result: %d\n", operation(3, 4));
    return 0;
}
```

Think: what other use cases might you think of?

???

callback, user-defined function as parameters, etc. 

---

How would you implement a sorting function that accepts a user-defined `compare` function for comparison?

--

```c
// mysort.c
void sort(int *array, int n, int (*compare)(int, int)) {
  int i, j, tmp;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (compare(array[j], array[j+1]) > 0) {
        tmp = array[j];
        array[j] = array[j+1];
        array[j+1] = tmp;
      }
    }
  }
}

// others.c
int ascending(int a, int b) { return a - b; }
int descending(int a, int b) { return b - a; }

sort(numbers, n, ascending);
sort(numbers, n, descending);
```

---

## Practice Question

Think: which one compiles to a smaller set of instructions?

<div class="side-by-side">

.align-left[

```c
void insertion_sort(int *array, int n) {
  int i, j, tmp;
  i = 0;
start:
  if (++i == n) return;
  tmp = array[i];
  j = i - 1;
loop:
  if (array[j] > tmp) goto copy;
  array[j + 1] = tmp;
  goto start;
copy:
  array[j + 1] = array[j];
  if (--j >= 0) goto loop;
  array[0] = tmp;
  goto start;
}
```

]

.align-right[

```c
void insertion_sort(int *array, int n) {
  int i, j, tmp;
  bool found;
  for (i = 1; i < n; ++i) {
    tmp = array[i];
    found = false;
    for (j = i; !found && (j > 0); --j) {
      if (array[j - 1] > tmp) {
        array[j] = array[j - 1];
      } else {
        found = true;
      }
    }
    array[j] = tmp;
  }
}
```

]
</div>