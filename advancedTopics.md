# Understanding procfs in Linux

## Example: Reading from procfs

You can use standard tools like `cat` to read files in `/proc`. For example:

```bash
cat /proc/cpuinfo
```

This command displays detailed information about the CPU, such as its model, speed, and cache size.

Similarly, you can read memory usage details using:

```bash
cat /proc/meminfo
```

This provides information about total and available memory, swap usage, and other memory-related statistics.

## Writing to procfs

While most files in `/proc` are read-only, some allow writing to modify kernel parameters. For example, you can change the maximum number of open file descriptors by writing to `/proc/sys/fs/file-max`:

```bash
echo 100000 > /proc/sys/fs/file-max
```

**Note**: Writing to procfs requires root privileges and should be done with caution, as it directly affects kernel behavior.

## Creating Custom procfs Entries

Developers can create custom entries in `/proc` for their kernel modules. This is useful for exposing module-specific information or providing an interface for interaction. Here's a high-level overview of the steps:

1. **Include Necessary Headers**:
   Include `<linux/proc_fs.h>` and other relevant headers in your kernel module.

2. **Create procfs Entry**:
   Use `proc_create()` to create a new entry in `/proc`.

3. **Define Read/Write Handlers**:
   Implement functions to handle read and write operations for the procfs entry.

4. **Cleanup**:
   Remove the procfs entry in the module's cleanup function using `remove_proc_entry()`.

### Example Code Snippet

Below is a simple example of creating a procfs entry in a kernel module:

```c
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_NAME "example"
#define BUFFER_SIZE 128

static char proc_buffer[BUFFER_SIZE];
static ssize_t proc_read(struct file *file, char __user *buf, size_t count, loff_t *pos);
static ssize_t proc_write(struct file *file, const char __user *buf, size_t count, loff_t *pos);

static const struct proc_ops proc_fops = {
     .proc_read = proc_read,
     .proc_write = proc_write,
};

static ssize_t proc_read(struct file *file, char __user *buf, size_t count, loff_t *pos) {
     return simple_read_from_buffer(buf, count, pos, proc_buffer, strlen(proc_buffer));
}

static ssize_t proc_write(struct file *file, const char __user *buf, size_t count, loff_t *pos) {
     if (count > BUFFER_SIZE - 1)
          return -EINVAL;
     if (copy_from_user(proc_buffer, buf, count))
          return -EFAULT;
     proc_buffer[count] = '\0';
     return count;
}

static int __init proc_init(void) {
     proc_create(PROC_NAME, 0666, NULL, &proc_fops);
     return 0;
}

static void __exit proc_exit(void) {
     remove_proc_entry(PROC_NAME, NULL);
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple procfs example");
```

This module creates a `/proc/example` entry that allows reading and writing data. You can interact with it using `cat` and `echo`.

## Conclusion

The `procfs` filesystem is a powerful tool for accessing and modifying kernel data structures. It is widely used for system monitoring, debugging, and kernel module development. Understanding its structure and capabilities can greatly enhance your ability to work with Linux systems.
