
#include <linucx/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Srijan-errorr");
MODULE_DESCRIPTION("My first kernel module");

static int srijan_module_init(void)
{
	printk("Hello, world!\n");
	return 0;
}
static void srijan_ module_exit(void)
{
	printk("Good,Bye\n");
}

module_init(srijan_module_init);
module_exit(srijan_module_exit);

