#include <linux/module.h>    /* Needed for all modules */
#include <linux/kernel.h>    /* Needed by KERN_INFO */
#include <linux/notifier.h>  /* Needed by notifier block */
#include <linux/suspend.h>   /* Needed for register_pm_notifier and unregister_pm_notifier */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Khairul Anuar Romli");

int notify_key(struct notifier_block *nblock, unsigned long code, void *__param) {
    /* Add in this block for actual working notifier */
    return (NOTIFY_OK);
}

/* Refer to notifier.h for  */
static struct notifier_block nb = {
        .notifier_call = notify_key
};

static int entry_point(void) {
    register_pm_notifier(&nb);
    printk(KERN_INFO "Sample notifier call module loaded!\n");
    return 0;
}

static void exit_point(void) {
    unregister_pm_notifier(&nb);
    printk(KERN_INFO "Sample notifier call module unloaded!\n");

}

module_init(entry_point);
module_exit(exit_point);
