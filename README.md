*This project has been created as part of the 42 Curriculum by rodrpere.*

# Introduction:

In a room with many philosophers as there are forks, only you can organize them 
to eat their spaghetti, think and sleep without making a mess.

# Index:
1. [Description](#Description)
2. [Instructions](#instructions)
    1. [Running the Project](#running-the-project)
    2. [Makefile Commands](#makefile-commands)
3. [Project Cases](#project_cases)
4. [Tests](#tests)
    1. [Easy cases](#easy)
    2. [Medium cases](#medium)
    3. [Hard cases](#hard)
    4. [FIFO to LIFO](#fifo_to_lifo)
5. [Resources](#Resources)
    
# Description:

The Codexion Project depends on the concept that there is an N amount of coders,
in a circular table, where each share their USB dongles with the other in its right.

Meaning that if there is only 3 Coders then, the first dongle will be shared between,
the first and last coder, the second dongle will be between the first and second,
and the third dongle will be between second and last.

However it is not only dongles that coders live from, they also need to:

## Compile:

To compile a coder is required to have 2 dongles to start,
when a compilation starts, its own internal clock registers this,
and increases the amount of compiles until it reaches the amount required.

When the compilation ends, it releases the both dongles, setting their cooldown.

## Debug:

To debug the coder needs to have previously done a compilation,
and that the simulation has never ended.

## Refactor:

To refactor, the simulation cannot have ended.

Every coders need to compile regularly and should never burnout, if they do the simulation ends.
The only other time a simulation ends is when at least the minimum amount of required compilation
is reached between all coders.

# Instructions:

Safe to say no coder should burnout and so with that, we need to set a few arguments before starting
the program:

./program_name, number_of_coders, time_to_burnout, time_to_compile, time_to_debug,
time_to_refactor, number_of_compiles_required, dongle_cooldown, scheduler.

When no arguments are given a error shows in the terminal.

When the number_of_coders is set to 0 the program never even starts.

When the number_of_compiles_required is set to 0, the coders wont need to compile.

When the dongle_cooldown is set to 0, the coders will abide by it.

The scheduler has to be either FIFO or EDF to work anything else will exit the program with 1.

## Running the Project:

To run the program simply type `make` in your terminal in the root of the project,
and then `./codexion <args>` (args being the arguments discussed in the start of this section).

## Makefile Commands:

`all:` compiles the program, depends on `banner` and  `$(NAME)`
`$(NAME)`: compiles all the object files into one binary called codexion.
Depends on the CC, CFLAGS, INCS, NAME and OBJS variables
`$(BUILD)/%.o`: creates the build dir and compiles each .c file into a .o file, placing them in the build dir.
`clean`: removes the build/srcs directory from the build dir.
`fclean`: depends on `clean` and removes the program binary.
`re`: depends on `banner` `fclean` `$(NAME)`, recompiles the program.
`debug`: adds the -g flag to the CFLAGS variable and recompiles the program
`compdb`: depends on the COMPDB variable, runs the compdb tool, that runs `make`
`format`: depends on the FORMATTER, SRCS and HEADER variable, run the tool c_formatter_42
to format every source file and include file.
`lint`: depends on the LINTER, SRCS and HEADER variable, runs the norminette on all source files and include file.
`banner`: when called prints the codexion banner on the terminal.
`.PHONY`: lists all the rules that are to be able to run.

# Project structure:
.  
├── incs/  
│   └── codexion.h          # Shared types, structures, and function declarations  
├── srcs/  
│   ├── main.c              # Argument handling and program entry point  
│   ├── objects/  
│   │   ├── config.c        # Configuration parsing  
│   │   ├── coder.c         # Coder allocation and initialization  
│   │   ├── dongle.c        # Dongle allocation and initialization  
│   │   └── table.c         # Table setup and teardown  
│   ├── methods/  
│   │   ├── coder.c         # Thread-safe coder state accessors  
│   │   ├── dongle.c        # Dongle availability and acquisition helpers  
│   │   ├── pair.c          # Coordinated acquisition and release of dongle pairs  
│   │   ├── heap.c          # FIFO/EDF binary heap operations  
│   │   └── table.c         # Simulation state, logging, and shutdown helpers  
│   └── routine/  
│       ├── routine.c       # Coder compile/debug/refactor lifecycle  
│       ├── monitor.c      # Burnout detection and simulation lifecycle  
│       ├── helpers.c      # Time and small utility helpers  
│       └── utils.c        # Allocation and numeric conversion helpers  
├── Makefile  
└── README.md  

## Blocking cases handled:

### Deadlock prevention
A coder needs two dongles at the same time. The implementation orders the pair by dongle ID before locking them, so competing coders attempt to lock resources in a consistent order rather than taking one resource and waiting indefinitely for another. When a coder cannot proceed with both resources, the acquisition logic releases the mutex it does not need before waiting on the relevant dongle condition variable.

This addresses the circular-wait risk commonly associated with the dining philosophers problem. It does not rely on arbitrary delays to break deadlocks.

### Fairness and starvation
Each dongle maintains a priority queue of requests. Under FIFO, the ticket assigned when a request is created determines its arrival order. Under EDF, the request with the earliest deadline is selected; tickets provide a deterministic tie-breaker for equal deadlines.

The same scheduling policy is assigned to every dongle's queue. A coder must be eligible at the head of both relevant queues before acquiring the pair.

### Cooldown handling
When a coder releases a pair, each dongle is marked as not taken and receives a free_when timestamp equal to the release time plus its configured cooldown. A request is eligible only when the dongle is not taken, the requester is first in its queue, and the cooldown timestamp has passed. Condition-variable notifications wake waiters when dongle state changes.
Burnout detection and termination
A dedicated monitor thread periodically checks each coder's last compile-start timestamp against the configured burnout deadline. If a deadline is exceeded, it records the burnout and initiates shutdown. The monitor also checks whether every coder has reached the required compile count.

The monitor checks at approximately 1 ms intervals. Actual scheduling and wake-up precision still depend on the operating system and system load.

### Log serialization
All normal state messages use a shared logging mutex. This prevents messages from different coder threads from interleaving. Logging also checks whether the simulation has already ended, preventing normal state messages from being printed after shutdown has been recorded.

## Thread synchronization mechanisms:

### The implementation uses POSIX threads and the following primitives:
| Primitive | Role |
|-----------|------|
| pthread_t | Represents each coder thread and the monitor thread. | 
| pthread_mutex_t | Protects individual dongle state, coder counters/timestamps, simulation state, and log output. |
| pthread_cond_t | Allows threads to wait for dongle availability or cooldown completion and to be notified when relevant state changes. |
| pthread_cond_timedwait | Allows a waiter to sleep until a dongle's cooldown deadline or until a notification arrives. |
| pthread_cond_broadcast | Wakes relevant waiters when a dongle is released or the simulation is stopped. |


### Shared-state protection
- Dongles: each dongle has its own mutex protecting its taken state, cooldown timestamp, and request queue. Its condition variable coordinates waiting coders.
- Coders: each coder has a mutex protecting its last compile-start time and completed compile count. Accessor functions lock around reads and updates.
- Simulation: a table-level mutex protects the is_over flag and start timestamp. A table-level condition variable supports interruptible timed sleeps and shutdown signalling.
- Logging: a dedicated table-level mutex serializes output and protects request ticket assignment.
For example, a coder updates its last compile-start time through a mutex-protected setter, while the monitor reads that value through a mutex-protected getter. This prevents a read/write race between the coder and monitor threads. Similarly, a dongle cannot be marked as taken by two coders simultaneously because its state and queue are examined while holding its mutex.

During shutdown, the monitor sets the simulation's end state and broadcasts on the simulation and resource condition variables. This wakes threads that would otherwise remain blocked waiting for a dongle or cooldown event, allowing them to exit and be joined.

# Tests:

Below are supplied tests to check the program execution, the tool: 
codexion_tester can also be run to test everything.

## Easy:
./codexion 1 800 200 200 200 10 0 fifo
./codexion 5 2000 200 200 200 10 0 fifo
./codexion 5 2000 200 200 200 7 0 edf

## Medium:
./codexion 5 500 200 200 200 10 0 fifo

## Hard:
./codexion 5 3000 200 200 200 10 400 fifo
./codexion 5 3000 200 200 200 10 800 fifo

## FIFO to LIFO:

### Addendum:

The fifo to lifo test can only be run after modifing the original source files
to fit the lifo scheduler into the priotiry checker and parser.

Otherwise, only the fifo test will work.

./codexion 5 3000 200 200 200 10 800 lifo
./codexion 5 3000 200 200 200 10 800 lifo

# Resources:

AI was used in this program to only test and debug possible paths from bug fixes, no code was written by it.

The linux man pages: [man(7).org](https://man7.org/linux/man-pages/)  
The POSIX threads interface: [POSIX](https://pubs.opengroup.org/onlinepubs/9699919799/)  
The stackoverflow website: [Stackoverflow](https://stackoverflow.com/questions)  
The Dining Philosofers progblem on wikipedia: [wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)  
The Subject Provided by the 42 School: [intra](https://cdn.intra.42.fr/pdf/pdf/229796/en.subject.pdf)  
