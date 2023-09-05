# Watchdog

Watchdog is a library that provides functionality to monitor a code block 
within a process and automatically restart it if terminated.

## About

The Watchdog module is designed to monitor a specific code block within a process. It continuously checks whether the process is still running. If the process terminates, the Watchdog library automatically restarts it. This ensures the uninterrupted execution of critical code blocks.

* Key features of the Watchdog library:
    - Monitors a code block within a process
    - Automatically restarts the process if it terminates
    - Provides functions to initiate and clean up the monitoring process

## Prerequisites

Before using the Watchdog library, ensure that you have the following prerequisites installed:

   - C compiler (e.g., GCC)
   - Make utility (optional, for using the provided Makefile)

## Getting Started

### Installation

To install the Watchdog library, follow these steps:

   1. Copy the dist folder to any place you like.
   2. Navigate to the folder where `dist` folder is and open a `C` file to start coding.

### Manual Compilation

The Watchdog library can be manually compiled using the following command:

gcc -Idist <compilation_flags>-L/dist -Wl,-rpath=/dist <your_file.c> dist/libwatchdog.so

### Using Makefile Compilation

   1. Copy the `makefile` from the `dist` folder to the parent folder where your 
      `C` file is
   2. Open the `makefile` and change the name of the `TARGET` and `SR`C` files to your 
      `C` file and desired executable name.

   3. Now you can type in the terminal `make` || `make run` || `make clean` || `make debug`

### Explanation of flags and shared library in the project:

- `-Idist` specifies the include directory where the header files are located.
- `-L/dist` specifies the library directory where the shared library is located.
- `-Wl,-rpath=/dist` adds the runtime library path for the shared library.
- `dist/libwatchdog.so` is the path to the shared library file.

### Usage

To use the Watchdog library in your code, follow these steps:

   1. Include the `watch_dog.h` header file in your source code.
   2. Call the `WDWatch` function to start monitoring the code block.
   3. Pass the time interval and command-line arguments to the `WDWatch` function.
   4. Use the monitored code block within your process.
   5. When you no longer need monitoring, call the `WDUnWatch` function to clean 
      up the resources.


### Limitations

* The smallest interval is 2 seconds. If 1 second is provided the `WDWatch` will 
return Error.

### Example usage:

```c
#include "watch_dog.h"

int main(int argc, char *argv[])
{
    /* Start monitoring the code block */
    wd_status_t status = WDWatch(10, argv);

    if(status != WD_SUCCESS)
    {
        /* Handle the error */
    }

    /* Your code goes here */

    /* Clean up and stop monitoring */
    status = WDUnWatch();

    return (0);
}

```
### Contact

For any questions about the project:

# Name: Tal Aharon
# Email: anatolik241094@gmail.com