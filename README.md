# PHILOSOPHERS

This project uses multithreading to improve performance and allow for concurrent requests. It is based on the GPT-3.5 architecture and trained on a large corpus of philosophical texts from various traditions and periods.

<img width="931" alt="image" src="https://user-images.githubusercontent.com/113030191/235662395-887ba426-7f83-474b-8ed7-1f3c4be5516d.png">


<p align="center">
<img width="653" alt="image" src="https://user-images.githubusercontent.com/113030191/235662559-0c589e1e-6fc5-4325-af30-07c58cc44083.png">
<img width="606" alt="image" src="https://user-images.githubusercontent.com/113030191/235662899-c8af6317-ff82-46ee-95f0-05ff940ca68b.png">
<img width="651" alt="image" src="https://user-images.githubusercontent.com/113030191/235663056-ba08c498-2839-4e61-9844-b2383074b9ab.png">
</p>

In this project we have to take into account the times that they give us as arguments so that the philosophers can carry out their actions, the data provided is:

- Number of philosophers.
- Time to die.
- Time to eat.
- Time to sleep.
- Number of times they must eat. (This last parameter is not mandatory).

When collecting the data, we have to be careful with the **MAX_INT**, it is not necessary to consider the **MIN_INT** since we will not admit data less than 0, in the case of the **number of philosophers**, we will not accept 0 either.

To control the data well, I have resorted to slightly modifying some existing functions:

- ft_atoi : For this project, this function will store the number collected in a **long** type variable, with which we can more easily check if this number exceeds the **MAX_INT** and thus return a negative so that our program shows the error on the screen.

<p align="center">
<img width="581" alt="image" src="https://user-images.githubusercontent.com/113030191/235665863-52c51b40-c9d8-4e51-91b9-435f38f8eee8.png">
</p>

- ft_isdigit : This function checks if the data passed is non-numeric, but in this case, we'll pass a **char \***, instead of an int, to check the entire string before performing **ft_atoi**, where we'll check if the first data is a sign. **'+'** or **'-'** to pass ignore it and start checking the string from the next position.

<p align="center">
<img width="348" alt="image" src="https://user-images.githubusercontent.com/113030191/235667189-4e0557a3-6086-4874-8b2a-4914ac2db808.png">
</p>

## Summary

This project generates as many forks as philosophers receive, each philosopher needs two forks to eat and they have a time to eat and sleep and a time that cannot exceed the time elapsed since the last time they ate and when they do it again or they will die and end the program.
This program can also end when the 5th parameter is passed, the number of times they can eat, where a message will be displayed saying "All philos ate X times".
Each philosopher has their forks previously assigned, so that they always use the same ones.

### Thread functions used

- **pthread_mutex_init()** : is a function in the POSIX thread (pthread) library that initializes a mutex object with a set of attributes. A mutex is a synchronization object that is used to protect shared resources from simultaneous access by multiple threads.
- **pthread_create()** : is a function in the POSIX thread (pthread) library that creates a new thread of execution. A thread is a lightweight process that shares the same memory space as the parent process and can be scheduled independently by the operating system.
- **pthread_mutex_lock()** : is a function in the POSIX thread (pthread) library that locks a mutex object. A mutex is a synchronization object that is used to protect shared resources from simultaneous access by multiple threads.
- **pthread_mutex_unlock()** : is a function in the POSIX thread (pthread) library that unlocks a mutex object. A mutex is a synchronization object that is used to protect shared resources from simultaneous access by multiple threads.
- **pthread_join()** : is a function in the POSIX thread (pthread) library that waits for a thread to terminate and retrieves its return value.

## Usage

To compile the philo program, run the following command **make**.

Try running these possible fixes :

- A philosopher must die without doing any of the following actions, eat sleep or think.

      ./philo 1 800 200 200
      
- No philosopher should die

      ./philo 5 800 200 200
      
- Everyone must eat 7 times

      ./philo 5 800 200 200 7
      
- No philosopher should die

      ./philo 4 410 200 200
      
- A philosopher should die

      ./philo 4 310 200 100
      
- No philosopher should die

      ./philo 2 400 200 100
      

### Links to my other projects at 42:

- **[Main Page](../../../Clocon)**
- **[libft](../../../libft-42)**
- **[ft_printf](../../../ft_printf-42)**
- **[get_next_line](../../../get_next_line-42)**
- **[pipex](../../../pipex-42)**
- **[push_swap](../../../push_swap-42)**
- **[so_long](../../../so_long-42)**
