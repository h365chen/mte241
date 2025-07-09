<!-- layout: true -->

<!-- class: middle -->

---

<!-- class: center, middle, inverse -->

# MTE 241 Tutorial

.invisible-slide-comment[See [README](./README.md) to turn this markdown to a slide presentation]

## Practice Questions on Scheduling

Presented by Huanyi Chen

huanyi.chen@uwaterloo.ca

---

## Roadmap

* We will review some of the practice questions about the scheduling knowledge covered in lectures

* Midterm Q&A

---

## S2024 Final

---

The entire Question 3 worth discussion.

---

## S2023 Final

---

Question 10

Given the following tasks and their respective worst-case execution time (WCET, in ms) and the time that a thread must run (Period, in ms):

* Task A: WCET = 1, Period = 6
* Task B: WCET = 12, Period = 18

Which of the following statements is true?

* A) Task A and Task B can be scheduled together without pre-emption.
* B) Task A and Task B cannot be scheduled together unless we use pre-emption.
* C) Task A must be adjusted so that its period is 10ms, then a schedule can be found. The problem originally is that WCET of A is an integer multiple of WCET of B.
* D) No schedule can be found for both tasks whether we use pre-emption or not, since CPU utilization is above 100%

--

Answer is B


---

Question 11

Consider a scenario where a thread is waiting for a network server to respond, and the server is busy.

Why is it practically impossible to know when the thread will be ready to run in such a case?

* A) Because the thread is CPU bound and it is uncertain how many cycles it must run before it is complete.
* B) Because the thread is memory bound and it is uncertain how long it will take to transfer the necessary data.
* C) Because the thread is IO bound and it is uncertain when the external server will respond.
* D) Because the thread is in a zombie state and it is uncertain whether the OS will reclaim its memory before it can run.

--

Answer is C

---

Question 12

In the co-operative multitasking scheme discussed in class, what is the expected behavior of threads after they have completed their work?

* A) They should immediately start a new task.
* B) They should keep voluntarily give up CPU control using `osYield`.
* C) They should call `osSched` to assign a new task.
* D) They should run the null task.

--

Answer is B

---

Question 21

What is the difference between deadline and slack in EDF (Earliest Deadline First) and LSF (Least Slack First) scheduling? Assume that we reset each one every thread period.

* A) Deadline refers to the amount of time left before a thread must be started or it will exceed its period, and slack refers to period in this scenario
* B) Deadline refers to the period in this scenario, and slack refers to the total amount of time left before a thread must be started or it will miss its deadline
* C) The two concepts are the same in LSF, but in EDF the deadline refers only to the period
* D) The two concepts are the same in EDF, but in LSF the slack refers only to the period

--

Answer is B

---

Question 27

What is priority inversion?

* A) A situation where lower-priority tasks pre-empt higher-priority tasks
* B) A situation where a higher-priority task is blocked due to the actions of a lower-priority task
* C) A situation where the scheduler is unfair, and prioritizes short-duration tasks regardless of their importance
* D) A technique to minimize context-switching overhead

--

Answer is B

---

Question 29

What does it mean to put a thread to sleep for a period of time?
* A) Set the thread to the ZOMBIE state and re-initialize it later
* B) Power down the processor with a wakeup interrupt schedule
* C) Temporarily ignore the thread for scheduling purposes
* D) Sleep and Yield are equivalent

--

Answer is C

---

Question 30

What does the WCET of a task actually tell us?

* A) The average execution time of a task
* B) An upper bound on the time it takes a task to complete
* C) The worst-case time it takes to switch between two CPU-bound threads
* D) It is equivalent to the big-Oh runtime of a thread, but specific to real-time systems

--

Answer is B

---

Question 33

What does the term “bound” mean in the context of a multi-threaded system?

* A) A bottleneck that dictates system responsiveness
* B) A waiting state where the thread is waiting on IO or memory
* C) The maximum number of threads a process can create
* D) The privileges of a thread in the real-time system

--

Answer is A

---

Question 44

What is the main attraction of EDF/LSF schedulers?

* A) They are actually not useful and are purely an academic object of study
* B) They are provably optimal schedulers, used as a gold-standard for other schedulers
* C) They are efficient and able to handle large numbers of tasks without missing deadlines regardless of how tasks arrive
* D) They provide a fast and reliable way to schedule multiple tasks but cannot ensure deadlines are met

--

Answer is B

---

Question 54

In our OS, what would happen if a thread's WCET is longer than its timeslice?

* A) The OS would crash, since the thread would be in the middle of a computation but then would be pre* emptively switched out
* B) The thread would miss deadlines repeatedly, essentially making the value of the system reduce until we are in system failure
* C) The thread would complete some of its tasks, then get switched out once its runtime expires, then when it gets switched back in it will resume from where it left off
* D) The OS would not able to create such a task, and we will get a hardfault at the last line of the runFirstThread assembly function

--

Answer is C

---

Question 56

Before we implemented timer-based, pre-emptive context switching, what would have happened if an otherwise correctly-written thread did not yield?

* A) The OS would crash, as the stack would be filled with calls to the thread’s function
* B) The OS would crash, since it would be unable to run any other threads
* C) The OS would still switch out the thread, since once a thread gets to the end of its while loop it acts as a call to yield
* D) The thread would take over the CPU and no other threads could run

--

Answer is D


<!-- pdf pages: 1-5,7,9,11,13,15,17,19,21,23,25,27 -->
