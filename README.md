# IPC

This project focuses on the [IPC][wiki-IPC] problems.

Typically, applications can use IPC, categorized as clients and servers, where the client requests data and the server responds to client requests. Many applications are both clients and servers, as commonly seen in distributed computing.

 By learning [Modern Operating Systems][wiki-MOS], I began to contact some of the classic IPC problems.This project is the result of my attempt to solve the classic IPC problems(by different programming languages).
 
##  Problem List
 
 - [Dining philosophers problem][wiki-DPP]
     + [Solve by C](./Dining_philosophers_problem/Dining_philosophers_problem.c):It's a good solution.
     Use `semaphore.h`. But it also can slove by using `pthread_mutex_t` and `pthread_cond_t`.
     + [Solve by java](./Dining_philosophers_problem/Dining_philosophers_problem.java):It's a bad solution.
     Use `synchronized` and `Math.random()`. It's low concurrency and unreliable.
     
- [Producer–consumer problem][wiki-PCP]
    + [Solve by C](./Producer–consumer_problem/Dining_philosophers_problem.c):It's a good solution.
    Use `pthread_mutex_t` and `pthread_cond_t`.
     
## Environment
- `gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0`
- `g++ (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0`
- `openjdk version "9-internal"` `javac 1.8.0_151`

## License
See the [LICENSE](./LICENSE) file for license rights and limitations.
 
[wiki-IPC]: https://en.wikipedia.org/wiki/Inter-process_communication
[wiki-MOS]:https://en.wikipedia.org/wiki/Modern_Operating_Systems
[wiki-DPP]:https://webcache.googleusercontent.com/search?q=cache:XbLm7i_FXu0J:https://en.wikipedia.org/wiki/Dining_philosophers_problem+&cd=4&hl=zh-CN&ct=clnk&gl=tw
[wiki-PCP]:https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem