# ITC/IPC

This project focuses on the ITC/[IPC][wiki-IPC] problems.(inter-thread communication and Inter-process communication)

 By learning [Modern Operating Systems][wiki-MOS], I began to solve some of the classic ITC/IPC problems.This project is the result of my attempt to solve the classic ITC/IPC problems.
 
 Thanks to `anqurvanillapy` for his `Issues`.
 
## Notice
- About **ITC**:  
"Focusing on constructs like semaphore, mutex, condition variable, atomic variable, memory barrier, STM, etc, and even some locks with alternative implementations like spinlock for atomics. They synchronize code in a single process"(from `anqurvanillapy`)

- About **IPC**:  
"Focusing on constructs like FIFO (named pipe), shm-based/mmap-based shared memory, message queue, message broker, naming service, balancer, etc, that are usually heavily based on sockets with specific protocols (e.g. TCP, UDP), and it's often prone to fail. Other subproblems include RPC (remote procedure call), IDL (interface description language), load-balancing or API gateway, consensus algorithms, single point of failure, high availability (a higher-level problem, actually), etc"(from `anqurvanillapy`)

- About **C library**:   
In most C language programs, we need to use [C POSIX library][wiki-C-POSIX] (instead of [C standard library][wiki-C-S]). For example, we need to use [POSIX thread][wiki-Pt] like `pthread.h`. So if you want to run those programs successfully, you should ensure that your compiler can support C POSIX library.   
And I will mark those programs that can only use C standard library. 
 
##  Solution List

 **To be continue...**
 
 - [Dining philosophers problem][wiki-DPP]
     + [C](./Dining_philosophers_problem/Dining_philosophers_problem.c) (ITC)  
     Use `semaphore.h`. But it also can slove by using `pthread_mutex_t` and `pthread_cond_t` (from `pthread.h`).
     + [Java](./Dining_philosophers_problem/Dining_philosophers_problem.java) (ITC)  
     Use `synchronized`.
     
- [Producer–consumer problem][wiki-PCP]
    + [C](./Producer–consumer_problem/Producer–consumer_problem.c) (ITC)  
    Use `pthread_mutex_t` and `pthread_cond_t` (from `pthread.h`).
    + [Java](./Producer–consumer_problem/Producer_consumer_problem.java) (ITC)  
    Use `synchronized`.

- [Readers–writers problem][wiki-RWP]
    + Readers-preference
        - [C](./Readers–writers_problem/shm.c) (IPC)  
        Use `semaphore.h` and `sys/shm.h`. If something goes wrong, we should run `rm_shm.c` to delete the shared memory.
    + Writers-preference
    +  Other
        - [C](./Readers–writers_problem/rwlock.c) (ITC)  
        Use `pthread_rwlock_t` (from `pthread.h`).

## My Compiler

`gcc` and `clang` compiler should use `-pthread`.

- `gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0`
- `g++ (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0`
- `clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)`
- `openjdk version "9-internal"` `javac 1.8.0_151`

## Other
"Synchronization constructs are mainly about wise/unwise choices of design and good/bad uses of abstractions, which you could take into a deeper consideration."(from `anqurvanillapy`)

**I will later make a document for analysis and discussion (Focus on my solutions).** But this is very difficult and complicated, so it may be a long time to come true.



## License
See the [LICENSE](./LICENSE) file for license rights and limitations.
 
[wiki-IPC]: https://en.wikipedia.org/wiki/Inter-process_communication
[wiki-MOS]:https://en.wikipedia.org/wiki/Modern_Operating_Systems
[wiki-DPP]:https://webcache.googleusercontent.com/search?q=cache:XbLm7i_FXu0J:https://en.wikipedia.org/wiki/Dining_philosophers_problem+&cd=4&hl=zh-CN&ct=clnk&gl=tw
[wiki-PCP]:https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
[wiki-RWP]:https://en.wikipedia.org/wiki/Readers%E2%80%93writers_problem

[wiki-C-POSIX]:https://en.wikipedia.org/wiki/C_POSIX_library
[wiki-C-S]:https://en.wikipedia.org/wiki/C_standard_library
[wiki-Pt]:https://en.wikipedia.org/wiki/POSIX_Threads