# What is a thread?
A thread is a Entity that is scheduled by the kernel to execute code

A thread maintains:
The state of CPU registers, used to know the state, if the thread is stopped from using the process saves the state and when this process is up, it continue in the same point thanks to the state
• Current access mode (user mode or kernel mode)
• 2 stacks: Reserved for user space and kernel space
• State: Running, ready, waiting
• Optional message queue and windows the thread creates

Threads sometimes has a security token to impersonate clients in multithreaded applications

A private storage area (TLS) for use by subsystems, run time libraries and DLLs

switching between threads involves the kernel scheduler, it can be a expensive operation, Windows implements two methods to reduces the computationalk cost: Fibers and User-Mode Scheduling

Every thread shares the process's virtual address space, meaning all the threads in a process have full read write access to the process virtual address space

## FIBER THREADS
Fiber allow an application to schedule its own threads  of execution rather than rely on the priority-based scheduling mecanism built into windows.
Fibers are implemented in user mode and are invisible to the kernel

USE fiber

1* Make a call to the Windows ConvertThreadToFiber function
2* The newly converted fiber can create an additional fibers via CreateFiber function.

A fiber doesn't begin execution until it's manually selected through a call to the SwitchFiber function.

using fiber is not recommended because
1* Are inbvisible to kernel (the kernel cannot manage the fibers)
2* They have issues with TLS because several fibers can run on a single process (Although Fiber Local Storage Exists)
3* Fibers cannot run concurrently
4* Are limited to cooperate multitasking.

It's best to let the Windows kenrel handle scheduling by using the appropiated threads.

## User Mode Scheduler
UMS threads provides the same basic advantages as fibers. UMS has their own kernel thread state therefore visible for the kernel, which allows, which allows for example, when two or more UMS threads need to perform work in user mode, they can periodically switch execution in user mode rather than involving the scheduler. 

From the kernel perspective, the same kernel thread is still running and nothing change

## Jobs
Windows provides an extension to the process model called a job. A job object's main function is to allow the management and manipulation of groups processes as a unit.
It also recors basic accounting information for all processes associated with the job and for all processes that were associated with the job but have since terminated.

In some way, the job objects compensates for the lack of a structured process tree in windows
