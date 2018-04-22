# IPC

This project focuses on the [IPC][wiki-IPC] problems.

Typically, applications can use IPC, categorized as clients and servers, where the client requests data and the server responds to client requests. Many applications are both clients and servers, as commonly seen in distributed computing.

 By learning [Modern Operating Systems][wiki-MOS], I began to solve some of the classic IPC problems.This project is the result of my attempt to solve the classic IPC problems.
 
 If you want to know more detail about my solutions.
 You can see my [Solution_docs](./docs/solution).
 
##  Solution List
 
 - [Dining philosophers problem][wiki-DPP]
     + [C](./Dining_philosophers_problem/Dining_philosophers_problem.c)
     Use `semaphore.h`. But it also can slove by using `pthread_mutex_t` and `pthread_cond_t`.
     + [Java](./Dining_philosophers_problem/Dining_philosophers_problem.java)
     Use `synchronized`.
     
- [Producer–consumer problem][wiki-PCP]
    + [C](./Producer–consumer_problem/Producer–consumer_problem.c)
    Use `pthread_mutex_t` and `pthread_cond_t`.
    + [Java](./Producer–consumer_problem/Producer_consumer_problem.java)
    Use `synchronized`.

- [Readers–writers problem][wiki-RWP]
    + Readers-preference
        - [C](./Readers–writers_problem/shm.c)
        Use `semaphore.h` and `sys/shm.h`.
    + Writers-preference
    +  Other
        - [C](./Readers–writers_problem/rwlock.c)
        Use `pthread_rwlock_t`.

## Notice
- Some solutions use `thread`, and some sulutions use `process`.
- `C`: When we use `thread`, we should add `-pthread`.

## Environment
- `gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0`
- `g++ (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0`
- `clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)`
- `openjdk version "9-internal"` `javac 1.8.0_151`

## License
See the [LICENSE](./LICENSE) file for license rights and limitations.
 
[wiki-IPC]: https://en.wikipedia.org/wiki/Inter-process_communication
[wiki-MOS]:https://en.wikipedia.org/wiki/Modern_Operating_Systems
[wiki-DPP]:https://webcache.googleusercontent.com/search?q=cache:XbLm7i_FXu0J:https://en.wikipedia.org/wiki/Dining_philosophers_problem+&cd=4&hl=zh-CN&ct=clnk&gl=tw
[wiki-PCP]:https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
[wiki-RWP]:https://en.wikipedia.org/wiki/Readers%E2%80%93writers_problem