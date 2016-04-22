The ipc_bench program for three different IPC methods, named pipes,  shared memory, and files. in the submitted version it repeats the sharing 20 times for each method and reports the average time. At each iteration (outside timed area) leader and follower both verify that they have received the expected data from the other process. An observation from doing this assignment is that shared memory is much fater that the other methods, which is expected considerign the IO operations needed for the other two methods. 

-------------------------------------------------------------------------------------------------------------------


Is freebu) more efficient than freemem? (Chapters 10.1 to 10.7)
Freebuf is more effecient when compared to freemem.
Freemem design places no limit on the size of the memory for a given process can allocate nor the fucntion attempt to divide the free space freely.
Also the allocation functions honor based on the first come first serve until no free memory remain.Even after the free memory is exhausted the functions reject further requests without process block or waiting for the memory to be released.
Freebuf returns a buffer to the pool from which it was allocated. Freebuf moves back bytes from the beginning of the buffer and extracts the pool id.

Suppose a processor has support for paging. Describe paging hardware that can be used to protect a process's stack from access by other processes, even if demand paging is not implemented (i.e., all pages remain resident and no replacement is performed).
Without demand paging the allocated physical memory cannot be reallocated.  Using virtual memory hardware, each page can be a resident in any location of the physical memory, or be flagged as being protected. Virtual memory  allows to have a linear virtual memory address space and to use it to access blocks fragmented over physical memory address space.Hardware is needed to support paging in order to map the virtual address to the corresponding pysical memory address.Hence without the demand paging any given process's stacks memory is protected and does not allow other processes to gain access to this process.

References:
https://en.wikipedia.org/wiki/Memory_protection
Xinu Text Book
