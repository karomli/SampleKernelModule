# Link to the kernel sources

#Fedora
#KDIR := /usr/lib/modules/$(shell uname -r)/build
#Ubuntu
KERNDIR := /lib/modules/$(shell uname -r)/build

# Link to the current directory
PWD := $(shell pwd)

# Override make to build my module only
obj-m := notifiercallskeleton.o

# we are making our module by recursing into
# kernel make modules, and overriding only our module

default:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNDIR) M=$(PWD) clean
