// 10. Write a kernel program and print “Hello World” using insmod, rmmod, lsmod etc.

#include <linux/module.h>    // Core header for loading kernel modules
#include <linux/kernel.h>    // Core header for kernel functions
#include <linux/init.h>      // Macros for module initialization and cleanup

// Function prototypes
static int __init start(void);
static void __exit stop(void);

// INITIALIZE
static int __init start(void) {
    printk(KERN_INFO "Hello, World! (kernel module loaded)\n");
    return 0;
}

// EXIT
static void __exit stop(void) {
    printk(KERN_INFO "Goodbye, World! (kernel module unloaded)\n\n");
}

// Define module entry and exit points
module_init(start);
module_exit(stop);

// Module metadata
MODULE_LICENSE("GPL");            
MODULE_AUTHOR("Name");     
MODULE_DESCRIPTION("A simple Hello World Linux module"); 
MODULE_VERSION("1.0");          


// CONTENT OF MAKEFILE
// gedit Makefile 
/* //////////////////////////////////////////////////////////////////
obj-m += 10kernel.o

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

////////////////////////////////////////////////////////////////////
HOW TO RUN
make
(Generates file `10kernel.ko`, which is the kernel module)

sudo insmod /home/uname/10kernel/10kernel.ko
(Load the module)

lsmod | grep 10kernel
(Check if module is loaded)

sudo dmesg | tail -2
(View the kernel log to see the "Hello, World!" message)

sudo rmmod 10kernel
(Unload the module)
*/