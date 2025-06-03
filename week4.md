<!-- layout: true -->

<!-- class: middle -->

---

<!-- class: center, middle, inverse -->

# MTE 241 Tutorial

.invisible-slide-comment[See [README](./README.md) to turn this markdown to a slide presentation]

## Practice Questions

### Chapter 3 & Chapter 8

Presented by Huanyi Chen

huanyi.chen@uwaterloo.ca

---

## Roadmap

- Practice questions

- Q&A

---

3.3 Most desktop and laptop processors have 64 registers. The 6800 has two
registers. Is it possible to have a processor with just a single data register?
(Your argument should use the requirements of the Turing machine.)

--

Answer:

Yes. The Turning machine itself only needs to track its state, so a data
register suffices. A real example is the Freescale RS08 microcontroller. It has
only one data register, an 8bit accumulator. All operations involve either
modifying this register, writing to the register, or saving the value to a
memory location. Any binary operation requires that one of the operands be
located in main memory where it is fetched using direct or indirect addressing,
possibly with an offset.

---

3.4 Which of the following is the correct definition of the word size of a
processor?

A. It is the width of the bus: the amount of data that can be transferred
   between the processor and main memory.

B. It is the width of the data registers: the amount of data that can be
   operated on by a single instruction.

C. The width of the bus equals the width of the data registers, so the word size
   is both of these.

--

Answer:

The correct answer is B.

Note that C is not correct. For example, Motorola 68000s (also known as the
M68k) had 16-bit words but it used 24 bits for addresses.

---

3.5 The address bus is 20 bits wide. What is the maximum amount of main memory
that can be accessed by such a bus?

--

Answer:

$2^{20}$ Bytes = 1MB

---

3.8 What does the following test do?

```c
#include <stdbool.h>
bool test() {
  int a = 1;
  char *p_char_a = (char *)( &a );
  return (*p_char_a) == 0;
}
```

--

Answer:

It tests whether the machine is big-endian or little-endian.

- `int a = 1;`
  Stores the integer 1 in memory.
  In binary: `0x00000001` (assuming 4-byte int)
- `char *p_char_a = (char *)(&a);`
  Casts the address of `a` to a `char*`, meaning we'll now examine the first byte of `a`.
- `return (*p_char_a) == 0;`
  Dereferences the first byte of a and checks whether it is zero.

On a little-endian system, the least significant byte is stored first: `a =
0x00000001 -> memory: [0x01][0x00][0x00][0x00]` So `*p_char_a == 1`, and the
function returns false.

On a big-endian system, the most significant byte is stored first: `a =
0x00000001 -> memory: [0x00][0x00][0x00][0x01]` So `*p_char_a == 0`, and the
function returns true.


---

3.12 What is the difference between Linux/Unix and POSIX?

--

Answer:

POSIX is a standard. Linux or Unix are implementations (some of which follow POSIX).

---

8.2 Why is a processor with a significantly shorter pipeline more desirable for
a real-time system, as opposed to one that has significantly longer pipeline.

--

Answer:

See Section 8.2.2 in the textbook. Basically it is because it allows for very
fast responses: the function called to deal with the interrupt must take
responsibility to leave the processor in the exact same state that it found it
in. This requires that at least parts of the ISR to be written in assembly;
however, this also ensures that the absolute minimal amount of work required is
performed: if the ISR only requires two data registers and one address register,
it only needs to store and then restore those values. This is the approach taken
by the developers of the Motorola 68000-based processors. Each ISR would have to
store the state of the processor and restore it prior to returning from the
interrupt.

---

### Midterm F23 Questions

---

#### Question 34

You've set up the thread stack so that xPSR and PC contain the correct values,
and the remaining registers contain the value `0xA`. You run your code and your
thread prints to UART a few times before you stop it and examine the registers
using the debugger. You notice that almost all registers still hold the value
`0xA`, but `R7` does not. What happened?

- A) R7 is a scratch register and is used by the compiler however it wishes. We
  cannot expect it to still have the original value after several function calls
  have happened
- B) The thread stack must not have been set up correctly, and a bad register
  value in the debugger is a good way for us to identify this type of error
- C) The thread's stack must have been corrupted when we loaded the stack. This
  can happen because multithreading is very susceptible to off-by-one errors.
  This indicates an error in the code.
- D) R7 is used for function arguments, and printf can take an arbitrary number
  of arguments, so printf's input arguments were placed in that register. This
  indicates that the thread is behaving correctly.

---

Answer:

The correct answer is A.

In ARM architecture (e.g., ARM Cortex-M), registers are categorized into:
- Caller-saved ("scratch") registers: R0–R3, R12
- Callee-saved ("variable") registers: R4–R11 (must be preserved across
  function calls)

Note that here caller is the function that calls another function, and callee is
the function that is called by another function.

R7 is often used by compilers as:
- A frame pointer (especially in debugging builds).
- A general-purpose scratch register (if frame pointers are omitted or optimized
  out).

This means compilers (especially when debug info is enabled) will insert
assembly instructions before your code runs, setting up R7. They will typically
restore R7 before the function returns. However, if you inspect R7 in the middle
of function execution, you'll see it has been overwritten.

Therefore, its value is not guaranteed to persist across function calls like
`printf()`. The fact that other registers still contain 0xA supports the idea
that the stack was correctly initialized and no corruption occurred. Only R7
changed is exactly what you'd expect if it were used by the compiler during
execution.

---

#### Question 38

Presume we are going to write our multithreading operating system and have
allocated 10000 bytes of stack space. Assuming each stack is 250 bytes long and
we are using the stack allocation scheme we've used in both labs 1 and 2, how
many threads can we create while still ensuring that all threads get the correct
stack space?

- A) 40
- B) 39
- C) 10
- D) 16

--

Answer:

It should be B. In total we can have 10000/250 stacks, but since one of them has
to be reserved for the kernel, so the answer is 39.


---

### Final F23 Questions

---

#### Question 17

`SVC` and `PendSv` are examples of:

- A) Hardware interrupts
- B) System calls
- C) Pendable IRCs
- D) Software interrupts

--

Answer:

D

- Hardware interrupts: these are triggered by external or peripheral hardware
- System calls: suitable for SVC, but the term "software interrupt" is more
  accurate.
- Pendable IRCs – Not a standard term. PendSV is pendable, but "IRCs" isn't a
  recognized abbreviation here.
- Software interrupts: interrupt triggered by software, which is accurate here.

---

### Final F24 Questions

---

1.5 Interrupts

In the Cortex M4, we use the `SVC` system call to send execution from the
current process to the interrupt handler. Simple system calls do not have
arguments, but more complex ones require the ability to pass arguments to a
function. There are two possible ways to move arguments from source to
destination: shared memory and putting them on the stack. Give one pro and con
of each approach.

--

Answer:

- Shared memory: Easy to access in both places, but limited in size.
- Stack: Can use as many stack variables as needed, but can be hard to reference
  in both places.

---

### Do some C programming

---

Use `typedef` to define the struct as `Demo`, and then print the size of `Demo`
as well as the size of each of its individual members.

```c
struct demo {
    char a;
    int b;
    char c;
    short d;
    char e;
    int f;
    long g;
};
```


Answer:

See Section 2.2.2 in the textbook.
