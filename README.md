#
#
# hashitout - A program to output the MD5, SHA256, or SHA512 digest of a given
#             file.
#
# Author: Cosimo de' Medici (primus inter pares)
# Email: cosimodmed@gmail.com
#
#

 Compilation
-------------
At this point in the development of hashitout, the program is still comprised of
a single source file. This being the case, there is no need for a makefile or
build script.

The following line is used to build an executable for testing:

    gcc -Wall hashitout.c -o hashitout -lssl -lcrypto


 Testing
---------
The current testing method is very simple, with "hashdeep" being used to create
baseline digests for files.


 Dependencies
--------------
There is currently only one library dependency outside of a C standard library,
and that is OpenSSL. One of the OpenSSL forks would likely work as well, but at
this point none of them have been tested.


 Project Goals
---------------
The only real goal of this project is to create a statically linked executable
which contains everything needed for verifying the integrity of a file a Unix-
like platform.

It would be nice to come to a point where we have our own implementation of the
hashing algorithms which we choose to support. This may not be necessary to get
to the originally stated goal, though. More research is needed to determine
exactly what we can get away with shipping, while still meeting licensing
requirements.


 TODO
------
Please reference the seperate TODO file for this information.

