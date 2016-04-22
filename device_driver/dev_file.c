#include <linux/init.h>
#include <linux/module.h>

/* printk() */
#include <linux/kernel.h> 

/* kmalloc() */
#include <linux/slab.h>

/* file_operations struct */
#include <linux/fs.h> 

/* size_t */
#include <linux/types.h> 

/* O_ACCMODE */
#include <linux/fcntl.h>

/* copy_from/to_user */
#include <asm/uaccess.h> 

#define BUF_LEN 128
static int major_number=60;
/*The functions required to make the driver are:*/
int dev_file_init(void);
void dev_file_exit(void);
int dev_file_open(struct inode *inode, struct file *filp);
int dev_file_release(struct inode *inode, struct file *filp);
ssize_t dev_file_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t dev_file_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);

/* Declaration of the init and exit functions */
module_init(dev_file_init);
module_exit(dev_file_exit);

/*Data structure for using file functions:*/
struct file_operations dev_file_fops = {
  read: dev_file_read,
  write: dev_file_write,
  open: dev_file_open,
  release: dev_file_release
}; 



/* Define a buffer of to store input characters */
char *buffer;
int count_var = 0;
	
/*The functions below need to be completed as per the comments.*/

int dev_file_init(void) {
 	 int result;

  	/* Registering device */
  	result = register_chrdev(major_number, "dev_file", &dev_file_fops);

  	/* Handle error case for result.i.e. if device was not registered successfully */
	
	if(result < 0)
	{
		printk("Device was not registered successfully");		
		return result;
	}

  	/* Use kmalloc to alocate memory to buffer needed to store input values*/
	buffer = kmalloc(BUF_LEN, GFP_KERNEL);
	if(!buffer)
	{
	result = - ENOMEM;
	goto fail;	
	}
	memset(buffer,0,BUF_LEN);
	printk("Device was registered successfully \n");
	return 0;
fail:
	dev_file_exit();
	return result;

}

void dev_file_exit(void) {
  /* Unregistering device */
  unregister_chrdev(major_number, "dev_file");

  /* Free the buffer using kfree */
	if(buffer)	
		kfree(buffer);

}

/* To handle open and release, maintain a count variable to check how many times the file
    has been opened. Increment for every open and decrement for every release */


/* This is called when any process tries to open the device file such as cat /dev/dev_file*/
int dev_file_open(struct inode *inode, struct file *filp) {
	printk("\n dev file open");
  /* Check if device is already open, if so return error*/
  if( count_var == 0)
	{
		printk("\n First time file open");
		count_var = count_var + 1;
		return 0;
	}
  else
	{
		printk("\n File already open");
		return -1;
	}

	return 0;

}

/* This is called when any process closes the device file */
int dev_file_release(struct inode *inode, struct file *filp) {

 /* Close device */
	if( count_var > 0 )
	{
		count_var = count_var - 1;
		printk("\n Decremented the count value");
		return 0;
	}
	return 0;

}

ssize_t dev_file_read(struct file *filp, char *buf,
                    size_t count, loff_t *f_pos) {
	
	//ssize_t return_val;
	
	/*count = MIN(count, 128 - *f_pos);
	if(count == 0)
	{
		return_val = 0;
		goto out;
	}*/
  /* Use copy_to_user() to transfer data to user space */

  /* Return number of bytes read */
	if(count > BUF_LEN){
		count = BUF_LEN;
	}
	copy_to_user(buf, buffer, count);
	 /*if(copy_to_user(buf, buffer+*f_pos, 5))
	{
		return_val = -EFAULT;
		goto out; 
	}*/
	/*printk("buf = %s",buf);
	*f_pos += 5;
	return_val = 5;
out:
	return return_val;*/
	printk("buf = %s",buf);
	if(*f_pos == 0)
	{
	*f_pos +=count;
	return count;
	}
	else
	return 0;
}

ssize_t dev_file_write( struct file *filp, char *buf,
                      size_t count, loff_t *f_pos) {
	//char *tmp;
  /* Use copy_from_user() to transfer data from user space */
	printk("trying to write\n");
	memset(buffer,0,BUF_LEN);
  /* Return number of bytes written */
	if(count > BUF_LEN){
		count = BUF_LEN;
	}
	//tmp = buf + count -1;
	copy_from_user(buffer, buf, count);
	printk("buffer = %s \n",buffer);
	//copy_to_user(tmp, buffer, count);
	return count;
}
