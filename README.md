conversion
==========

Intro
=========================================

Conversion provides processes with version-controlled memory, allowing both strong
isolation and the ability to update to receive modifications from others. Generally speaking, 
Conversion can be thought of us a system for controlling memory propogation between processes.

You can read more about Conversion here:

http://eurosys2013.tudos.org/wp-content/uploads/2013/paper/Merryfield.pdf



Installation
=========================================

Begin by getting the conversion enabled kernel (v. 2.6.37) available here: 

https://github.com/tmerrifi/conversion_linux

Compile, install and boot it before continuing.

Once this is complete, cd into the root of the conversion project (this one) and 
type:

make; //does an install automatically
make tests;

See the file tests/simple_test/simple.c for an example of how to use Conversion.

**Conversion used to be called ksnap....so some of the libraries and header
files still use that name.**

Usage
=============================================

*Creates a new conversion segment*
```C
conv_seg * conv_checkout_create(int size_of_segment, 
         char * segment_name, void * desired_address);
```

*Performs a commit of any modifications and retrieves all modifications to the repository since
the last update. If no local modications exist, an update is still performed*


```C
void conv_fence(conv_seg * seg);
```

**The original paper described an update/commit API, but the fence call handles both case in a cleaner way.**

*does the same thing as conv_fence (just a longer and more specific name). Kept around to support some earlier 
software that used this function.*
```C
void conv_commit_and_update(conv_seg * seg);
```

*The garbage collector won't collect any versions with a higher version number than minimum version number
for all "active" threads. For example, if the parent thread goes to is sleeping (waiting on a condition
variable or joining) than any subsequent versions won't be collected. By calling conv_sleep, that is a hint
to conversion that we don't need to worry about concurrent updates from this thread. We can collect obsolete
versions without considering this thread's version number. conv_wake undoes this bahavior.*
```C
void conv_sleep(conv_seg * seg);
void conv_wake(conv_seg * seg);
```

*how many pages are currently dirty*
```C
unsigned int conv_get_dirty_page_count(conv_seg * seg); 
```

*how many pages did we retrieve on our last commit?*
```C
unsigned int conv_get_updated_page_count(conv_seg * seg);
```

*how many pages were merged on our last commit?*
```C
unsigned int conv_get_merged_page_count(conv_seg * seg);
```