# Minimal Part 21 C++ example

## Install Prequisites

This is a minimal C++ example for STEPcode library from here: http://stepcode.github.io/docs/p21_cpp_example/

I use this project to walk you through the process of compiling the STEPcode library and setting up an environment in which the p21mini.cpp file can be successfully compiled into a binary.

STEPcode is a C++ project which uses cmake as build system, so it is going to be neccessary that you'll have cmake, make and gcc installed on your system so that they can be run from the command line (and git too):

    sudo apt install cmake make gcc git

As far as I have understood STEP, there exist different schemas which customize the STEP file format for different branches of manufacturing. STEPcode supports different schemas by generating C++ code according to the requested schema, and then compiles that generated code into a custom library that is specific the requested schema. Since we'll have to deal with object files and libraries, it might be useful to have the binutils package installed so that we can use nm to look at symbols an object file exposes.

    sudo apt install binutils

## Check out the Sources

We need a global directory where we'll put this repository and the STEPcode repository.

    mkdir step
    cd step/
    git clone https://github.com/stepcode/stepcode.git
    git clone https://github.com/wikifactory/stepcode-example

# Build STEPcode

Just following the steps explained on: http://stepcode.github.io/ works almost. We need to specifiy a different schema because `ap214` does not exist anymore in the source tree, instead we'll use `ap242` since that seems to be the one that best fits our use case (there is also a schema named `ap214e3` which I assume would be what we would use if we wanted to build a version for the 214 schema).

I did the following to build STEPcode:

    cd stepcode/
    mkdir ap242
    cd ap242
    cmake .. -DSC_BUILD_SCHEMAS="ap242"
    make -j4 all

That should compile several .so libs in `./lib/` and some executables in `./bin/`. But as far as I understand this has only compiled the generic functionality yet, to get the schema specific stuff you have to run:

    make sdai_ap242 generate_cpp_sdai_ap242 lazy_sdai_ap242 p21read_sdai_ap242

I don't know if all of these targets are actually necessary, but this will compile a schema specific library `./lib/libsdai_ap242.so.2.0.0` which we'll need to link to later.

There is also a `install` target will install the generic libraries and their includes into `../sc-install`. The Makefile I wrote for this example assumes that the STEPcode libraries and includes have been installed this way so you should run:

    make install

There are other possible targets that might be useful to know about in the future, you can take a look at all possible targets by running:

    make help

# Building stepcode-example

This should now be possible if you have followed the above instructions and ended up with a directory structure similar to mine:

    step/stepcode/ap242/lib
    step/sc-install/lib
    step/sc-install/include
    step/stepcode-example

If that is the case you should be able to run make in the `stepcode-example` directory and get an executable `./p21mini` compiled:

    cd ../../stepcode-example
    make

which you can then use to read a step file and write it out again by running:

    env LD_LIBRARY_PATH="../sc-install/lib:../stepcode/ap242/lib:$LD_LIBRARY_PATH" ./p21mini silla.step

getting output like this:

    Reading Data from /home/rakete/wikifactory/step/stepcode-example/silla.step...

    HEADER read:

    FIRST PASS complete:  14198 instances created.
        0  ERRORS	  0  WARNINGS


    SECOND PASS complete:  14198 instances valid.
        0  ERRORS	  0  WARNINGS

    Finished reading file.

Interestingly you can not run `./p21mini` on the output again without getting errors. But you can load the outputted file in a step viewer and see that is it indeed a valid step file.
