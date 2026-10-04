/*
 * Smart Home Character Device Driver
 *
 * Educational Linux kernel module demonstrating:
 * - character device registration
 * - file_operations
 * - open/read/write/release
 * - device creation under /dev
 *
 * The driver exposes simulated smart-home sensor information.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>

#define DEVICE_NAME "smart_home"
#define CLASS_NAME  "smart_home"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Capstone Project");
MODULE_DESCRIPTION("Smart Home Occupancy and HVAC Simulator Character Driver");
MODULE_VERSION("1.0");

static dev_t dev_number;
static struct class *smart_home_class;
static struct cdev smart_home_cdev;
static DEFINE_MUTEX(smart_home_mutex);

static char sensor_data[256] =
    "temperature=28.5;humidity=60;occupancy=1;motion=1\n";

static int smart_home_open(struct inode *inode, struct file *file)
{
    pr_info("smart_home: device opened\n");
    return 0;
}

static ssize_t smart_home_read(struct file *file, char __user *buffer,
                               size_t length, loff_t *offset)
{
    ssize_t bytes;

    if (*offset >= strlen(sensor_data))
        return 0;

    if (length > strlen(sensor_data) - *offset)
        length = strlen(sensor_data) - *offset;

    mutex_lock(&smart_home_mutex);

    if (copy_to_user(buffer, sensor_data + *offset, length)) {
        mutex_unlock(&smart_home_mutex);
        return -EFAULT;
    }

    *offset += length;
    bytes = length;

    mutex_unlock(&smart_home_mutex);
    return bytes;
}

static ssize_t smart_home_write(struct file *file, const char __user *buffer,
                                size_t length, loff_t *offset)
{
    size_t copy_length = length;

    if (copy_length >= sizeof(sensor_data))
        copy_length = sizeof(sensor_data) - 1;

    mutex_lock(&smart_home_mutex);

    if (copy_from_user(sensor_data, buffer, copy_length)) {
        mutex_unlock(&smart_home_mutex);
        return -EFAULT;
    }

    sensor_data[copy_length] = '\0';

    mutex_unlock(&smart_home_mutex);

    pr_info("smart_home: sensor data updated\n");
    return length;
}

static int smart_home_release(struct inode *inode, struct file *file)
{
    pr_info("smart_home: device closed\n");
    return 0;
}

static const struct file_operations smart_home_fops = {
    .owner = THIS_MODULE,
    .open = smart_home_open,
    .read = smart_home_read,
    .write = smart_home_write,
    .release = smart_home_release,
};

static int __init smart_home_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        pr_err("smart_home: failed to allocate device number\n");
        return ret;
    }

    cdev_init(&smart_home_cdev, &smart_home_fops);
    smart_home_cdev.owner = THIS_MODULE;

    ret = cdev_add(&smart_home_cdev, dev_number, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_number, 1);
        return ret;
    }

    smart_home_class = class_create(CLASS_NAME);
    if (IS_ERR(smart_home_class)) {
        cdev_del(&smart_home_cdev);
        unregister_chrdev_region(dev_number, 1);
        return PTR_ERR(smart_home_class);
    }

    if (IS_ERR(device_create(smart_home_class, NULL, dev_number,
                             NULL, DEVICE_NAME))) {
        class_destroy(smart_home_class);
        cdev_del(&smart_home_cdev);
        unregister_chrdev_region(dev_number, 1);
        return -EINVAL;
    }

    pr_info("smart_home: driver loaded successfully\n");
    pr_info("smart_home: device available at /dev/%s\n", DEVICE_NAME);

    return 0;
}

static void __exit smart_home_exit(void)
{
    device_destroy(smart_home_class, dev_number);
    class_destroy(smart_home_class);
    cdev_del(&smart_home_cdev);
    unregister_chrdev_region(dev_number, 1);

    pr_info("smart_home: driver unloaded\n");
}

module_init(smart_home_init);
module_exit(smart_home_exit);
