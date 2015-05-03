# FOREWORD

Hi. First, I would like to direct you to the file called 'README' (without
extension) -- it is the file where you will find information on the
sbase ("suck less") project, written by the authors.

This file is only about the Android "port" (if it can be called that)

I created this project because:

1. I am tired of some limitations of Busybox -- while an excellent
project, due to its own lightweight nature, the lack of certain command
line modifiers has been driving me up the wall.
A good example is that when I am checking files on my phone, I would like,
as in my other shells, to be able to type 'ls -ltr' to sort them
most recent last. Alas, I cannot.

2. While sbase is a well written project that compiles almost anywhere,
Android was not put together with POSIX compatibility as its first and
foremost goal. Thus, the "upstream" sbase repository does not build.

# A LAUNDRY LIST

Note: this is now sbase + some interesting utils from ubase
as well. _ubase_, by the same less sucky people!

Some of the things I have done to please the Android ndk:

* Fixed some imports, such as termios.
* Added some imports and code such as fmemopen
* Stubbed out some missing functions such as linkat()
* Added missing default functions such as stdtold()
* Added missing POSIX definitions (now more than 1 :))
* Created Android-specific Makefiles and Android.mk

I also borrowed some code from OpenBSD. Unlike Linux's GNU utils, there is no
license incompatibility. It is:

* regex.h
* libutil/regex2.h
* libutil/cclass.h
* libutil/cname.h
* libutil/engine.c
* libutil/fmemopen.c|h
* libutil/getline.c
* libutil/regcomp.c
* libutil/regerror.c
* libutil/regexec.c
* libutil/regfree.c
* libutil/utils.c

# LIMITATIONS

At this point, there are several:

* The code could be cleaner, especially the way I mix BSD imports with the 
  original code.
* This only builds for ARM. This could be easily fixed by adding a few
  targets to the build files.
* Others, than I cannot think of right now but I am sure they are there
  nontheless.

## Command (current) limitations

* lsusb could not be implemented because /sys/bus/usb/devices is empty
* ps, who could not be implemented in their raw form as they rely on u/wtmp
* same goes for last
* hwclock needs to be rewritten
* halt is only to be called if you wish to freeze your phone, e.g. to
  interrupt an otherwise dangerous operation (rm -rf?)

# BUILDING

    make

# CONTACT

My favorite ways to be contacted are:
* Google+ (https://plus.google.com/+ChrisRavenscroft/posts)
* XDA! ("cyansmoker")

Cheers,

Chris F. Ravenscroft

!["This sucks less!" from stocksnap.io](res/apic.jpg)
