
#include <linucx/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Srijan-errorr");
MODULE_DESCRIPTION("Dynamically loadable Kernel module to perform read write on proc/ file system.");

#define MAX_PROC_WRITE_BUFFER 100 //maximum size of the message the user can enter
static char proc_read_user_data[MAX_PROC_WRITE_BUFFER]; //the buffer which will be read from/wrote to by the kernel/user



static struct proc_dir_entry *proc_entry; //create the cutom pointer node to hold the value returned by the proc_create function.
static struct proc_ops driver_proc_ops={
	.proc_read=read_func; //assigning the read function to the function pointer member function of the struct
	.proc_write=write_func;
}; //create a variable to the proc_ops class(structure) and access its member methods



static ssize_t read_func(struct file* file pointer, char* user_space_buffer, size_t count, loff_t* offset) //function with the same signature of the read function to perform read operation
{
	printk("Inside the read function\n");

	if(*offset>=len) return 0; //check if we have reached the end of file hence returning 0 to cat which indicates we have and cat sops to try to read
	
	size_t len=strlen(proc_read_user_data);
	int res= copy_to_user(user_space_buffer,proc_read_user_data,len); //copying from our written buffer (proc_read_user_data) to the user_space_buffer which the cat can read
	
	*offset+=len; //update the offset to point to the last line
	return len;
}


static ssize_t write_func(struct file* file pointer,const char* user_space_buffer, size_t count, loff_t* offset)
{
	if(count > MAX_PROC_WRITE_BUFFER) //since the write function reads count bytes at maximum from the buffer checking if the max count length exceeds 100,i.e, user entered more than 100 characters, setting it to read only the first 100
    	count = MAX_PROC_WRITE_BUFFER;
	if(copy_from_user(proc_read_user_data, user_space_buffer, count))//if this operation fails return segfault
    	return -EFAULT;

	return count;
}



static int srijan_module_init(void)
{
	printk("Module entry: init\n");
	proc_entry=proc_create("read_write_driver",0666,NULL,&driver_proc_ops); //the proc create function creates the file for us in the proc file system.
	return 0;
}
static void srijan_ module_exit(void)
{
	printk("Module exit: exit\n");
	proc_remove(proc_entry); //remove the file we created.
}



module_init(srijan_module_init);
module_exit(srijan_module_exit);

