#include <linux/module.h>   // Needed for all modules
#include <linux/kernel.h>   // Needed for kernel macro
#include <linux/fs.h>       // Needed for file operations
#include <linux/proc_fs.h>  // Needed for proc fs constants/structures
#include <linux/seq_file.h> // Needed for seq read, seek, file

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Sample Proc FS with Parameter");

static struct proc_dir_entry *proc_top_dir;  // initialization to create dir in /proc
static char *proc_dir_name = "procfsparam"; // the dir name initialization
static char *proc_fs_name = "paramfs";

int uparam = 2016; // user parameter
module_param(uparam, int, S_IRUSR | S_IWUSR | S_IRGRP);

int param_show(struct seq_file *m, void *v) {
    seq_printf(m, "%d\n", uparam);
    return 0;
}

// open param
int param_open(struct inode *inode, struct file *f) {
    return single_open(f, param_show, NULL);
}

// file operations struct
const struct file_operations fops = {
    .owner      = THIS_MODULE,
    .open       = param_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};

int my_entry_point (void)
{

   // enumerate dir in /proc with proffsparam
   // refer to proc_fs.h for prototype
   proc_top_dir = proc_mkdir(proc_dir_name, NULL);
   

   // check if the dir is present in /proc
   if(!proc_top_dir)
           return ENOENT;
    
   printk(KERN_INFO "Loading sample proc fs module with uparam = %d.\n", uparam);
   proc_create(proc_fs_name, 0, proc_top_dir, &fops);  
   return (0);
}

void my_exit_point (void)
{
   // unload and remove the proc fs and dir
   remove_proc_entry(proc_fs_name, proc_top_dir);
   printk(KERN_INFO "Unloading sample proc fs module with uparam = %d.\n", uparam);
   proc_remove(proc_top_dir);
}

module_init(my_entry_point);
module_exit(my_exit_point); 
