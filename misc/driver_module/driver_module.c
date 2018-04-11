#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define PARAM_TEST 		0
#define DEVICE_MODEL 		1
#define DEVICES_KOBJ_TEST 	0

/************************************ defined marco *****************************/
struct devm_attribute {
	struct attribute attr;
	ssize_t (*show)(char *buf);
	ssize_t (*store)(const char *buf, size_t count);
};
#define to_devm_attr(_attr) container_of(_attr, struct devm_attribute, attr)

/************************************ defined variable **************************/
#if PARAM_TEST
static int m_param = 0;
module_param(m_param, int, 0600);
static int m_param_name=0;
module_param_named(param_name, m_param_name, int, 0600);
static char m_param_string[32];
module_param_string(param_string, m_param_string, 32, 0644);
MODULE_PARM_DESC(param_string, "param string test.");
static int m_param_array[32];
static int nr_array = 0;
module_param_array(m_param_array, int, &nr_array, 0644);
#endif

#if DEVICE_MODEL
static struct kset *devm_kset = NULL;
static struct kobject *devm_root_kobj = NULL;
static struct kobject *devm_kobj = NULL;
#endif

#if DEVICES_KOBJ_TEST
extern struct kobject *kernel_kobj;
static struct kobject *kernt_kobj = NULL;
#endif

/************************************ defined function ************************/
#if DEVICE_MODEL
static unsigned int show = 0;
static ssize_t show_devm_attr(char *buf)
{
	return sprintf(buf, "%d\n", show);
}

static ssize_t store_devm_attr(const char *buf, size_t count)
{
	if(buf[0] == '0')
		show = 0;
	else
		show = 1;
	return count;
}

static struct devm_attribute devm_attr = 
{
	.attr = {
		.name = "devm_attr",
		.mode = 0666,
	},
	.show = show_devm_attr,
	.store = store_devm_attr,
};

static ssize_t devm_attr_show(struct kobject *kobj, struct attribute *attr, char *buf)
{
	ssize_t ret = 0;
	struct devm_attribute *devm_attr = to_devm_attr(attr);

	if(devm_attr->show)
		ret = devm_attr->show(buf);

	return ret;
}

static ssize_t devm_attr_store(struct kobject *kobj, struct attribute *attr, const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct devm_attribute *devm_attr = to_devm_attr(attr);

	if(devm_attr->store)
		ret = devm_attr->store(buf, count);

	return ret;
}

static struct sysfs_ops devm_sysfs_ops =
{
	.show = devm_attr_show,
	.store = devm_attr_store,
};

static struct kobj_type devm_ktype = 
{
	.sysfs_ops = &devm_sysfs_ops,
};

static int devm_register(void)
{
#if 1
	devm_root_kobj = kobject_create_and_add("devm", NULL);
	if(!devm_root_kobj)
		return -1;
	devm_kobj = kobject_create_and_add("devtest", devm_root_kobj);
	if(!devm_kobj)
		goto dev_kobj_err;
	devm_kobj->ktype = &devm_ktype;

	if(sysfs_create_file(devm_kobj, &devm_attr.attr))
		printk("sysfs create file failed\n");

	return 0;

dev_kobj_err:
	kobject_del(devm_root_kobj);
	return -1;
#else
	devm_kset = kset_create_and_add("devm", NULL, NULL);
	if(!devm_kset)
		return -1;
	devm_kobj = kobject_create_and_add("devtest", &devm_kset->kobj);
	if(!devm_kobj)
		goto dev_kobj_err;
	devm_kobj->kset = devm_kset;
	devm_kobj->ktype = &devm_ktype;

	if(sysfs_create_file(devm_kobj, &devm_attr.attr))
		printk("sysfs create file failed\n");

	return 0;

dev_kobj_err:
	kset_unregister(devm_kset);
	return -1;

#endif

}

static void devm_unregister(void)
{
	sysfs_remove_file(devm_kobj, &devm_attr.attr);

	if(devm_kobj)
		kobject_del(devm_kobj);
	if(devm_root_kobj)
		kobject_del(devm_root_kobj);
	if(devm_kset)
		kset_unregister(devm_kset);
}
#endif

#if DEVICES_KOBJ_TEST
static int show;
static ssize_t show_kernt_attr(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", show);
}

static ssize_t store_kernt_attr(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
#if 0
	if(buf[0] == '0')
		show = 0;
	else
		show = 1;
#else
	   sscanf(buf, "%du", &show);
#endif
	return count;
}

#if 1
static struct kobj_attribute kernt_attr = 
{
	.attr = {
		.name = "kernt_attr",
		.mode = 0666,
	},
	.show = show_kernt_attr,
	.store = store_kernt_attr,
};
#else
static struct kobj_attribute kernt_attr = __ATTR(kernt_attr, 0666, show_kernt_attr, store_kernt_attr);
#endif

static int kernt_register(void)
{
	kernt_kobj = kobject_create_and_add("dev_model", kernel_kobj);
	if(!kernt_kobj)
		goto dev_kobj_err;

	if(sysfs_create_file(kernt_kobj, &kernt_attr.attr))
		printk("sysfs create file failed\n");

	return 0;
dev_kobj_err:
	return -1;

}

static void kernt_unregister(void)
{
	sysfs_remove_file(kernt_kobj, &kernt_attr.attr);

	kobject_del(kernt_kobj);
}
#endif

#if PARAM_TEST
static void print_param(void)
{
	int i;
	printk("m_param:%d\n", m_param);
	printk("m_param_name:%d\n", m_param_name);
	printk("m_param_string:%s\n", m_param_string);
	printk("m_param_array: ");
	for(i=0; i<nr_array; i++)
		printk("%d ", m_param_array[i]);
	printk("\n");
}
#endif

static int __init driver_module_init(void)
{
	printk("This is a driver module!, parameter:\n");
#if PARAM_TEST
	print_param();
#endif
#if DEVICE_MODEL
	if(devm_register())
		printk("create device model failed\n");
#endif
#if DEVICES_KOBJ_TEST
	if(kernt_register())
		printk("create device model failed");
#endif
	return 0;
}

static void __exit driver_module_exit(void)
{
	printk("driver module is exit!\n");
#if DEVICE_MODEL
	devm_unregister();
#endif
#if DEVICES_KOBJ_TEST
	kernt_unregister();
#endif
}

module_init(driver_module_init);
module_exit(driver_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("coolice");

