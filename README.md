# Minimal Part 21 C++ example

## Install Prequisites

This is a bunch of examples for the STEPcode library: http://stepcode.github.io/

I use this project to walk you through the process of compiling the STEPcode library and setting up an environment for compiling these examples.

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

Just following the steps explained on: http://stepcode.github.io/ works almost. We need to specifiy a different schema because `ap214` does not exist anymore in the source tree, instead we'll use `ap242` since that seems to be the one that best fits our use case (there is also a schema named `ap214e3` which I assume would be what we would use if we wanted to build a version for the 214 schema). It is also possble to specify `ALL` as a schema, which should also be the default if nothing is specified.

I did the following to build STEPcode:

    cd stepcode/
    mkdir build
    cd build
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

    step/stepcode/build/lib
    step/sc-install/lib
    step/sc-install/include
    step/stepcode-example

If that is the case you should be able to run make in the `stepcode-example` directory:

    cd ../../stepcode-example
    make

and then:

    env LD_LIBRARY_PATH="../sc-install/lib:../stepcode/build/lib:$LD_LIBRARY_PATH" ./pretty

# Documentation

I am trying to find documentation that helps me understand stepcode:

## Overview of stepcode
- http://stepcode.github.io/docs/home/
- https://github.com/stepcode/stepcode/wiki/Files-in-SCL
- [Validation Testing System: Reusable Software Component Design](https://github.com/stepcode/stepcode/blob/master/doc/VTS_-_Reusable_Software_Component_Design_-_morris91.pdf)
- [Design of a C++ Software Library for Implementing EXPRESS](https://github.com/stepcode/stepcode/blob/master/doc/Design_of_SCL_-_sauder95.pdf)
- [NIST FASD STEP Class Library Data Structures](https://github.com/stepcode/stepcode/blob/master/doc/sclnotes.pdf)

## Example code using stepcode
- [Doxygen 0.5 (outdated?)](http://mpictor.github.io/scl/0.5/doc.StepClassLibrary/doxygen-html/index.html)
- [BRL-CAD](https://github.com/kanzure/brlcad/tree/master/src/conv/step)
- [OpenVSP](https://github.com/OpenVSP/OpenVSP/blob/f5ced1dfcf40b5cc1964663bf48421dac67eccd4/src/util/STEPutil.cpp)
- [STEPcode examples](https://github.com/stepcode/stepcode/tree/master/test/cpp/)

## Other code dealing with STEP
- [OpenCASCADE](https://www.opencascade.com/doc/occt-6.9.0/overview/html/occt_user_guides__step.html)
- [STEPtools Inc. SDAI C Library Reference Manual](https://dsiva.weebly.com/uploads/5/2/7/8/5278587/sdailib.pdf)

## More on STEP
- [ISO 10303 on Wikipedia](https://en.wikipedia.org/wiki/ISO_10303)
- [ISO 10303-21 part 21 files](https://en.wikipedia.org/wiki/ISO_10303-21)
- [Overview of ISO 10303](https://www.nist.gov/sites/default/files/documents/el/msid/16_aBarnardFeeney.pdf)
- [Recommended Practices for AP 203](https://www.oasis-open.org/committees/download.php/11728/recprac8.pdf)
- [Usage Guide for the STEP PDM Schema V1.2](https://www.prostep.org/fileadmin/downloads/ProSTEP-iViP_Implementation-Guideline_PDM-Schema_4.3.pdf)
- [AP 239 Specification](http://www.asd-ssg.org/c/document_library/get_file?uuid=3e01b539-7d77-48dc-a7a5-076511664054&groupId=11317)
- [Solidworks does not export materials to STEP (contains SLDPRT with materials)](https://forum.solidworks.com/thread/181689)
- [Solidworks MBD for STEP export with materials](https://www.cati.com/products/technical-communications/solidworks-mbd/)
- [STEP material property example text](https://www.eng-tips.com/viewthread.cfm?qid=398294)
- [STEPtools *huge* merged STEP schema (ap242,214,203,238,224,240,242,232)](https://www.steptools.com/stds/stp_aim/html/schema.html)
- [STEPtools EXPRESS schema archive](https://www.steptools.com/stds/archive/)

## STEP files/viewer
- [MBE PMI Validation and Conformance Testing Project](https://www.nist.gov/el/systems-integration-division-73400/mbe-pmi-validation-and-conformance-testing-project)
- [NIST PMI files in STEPtools viewer](https://www.steptools.com/demos/242/index.html)
- [NIST PMI files on Wikifactory](https://wikifactory.com/@rakete/nist-pmi-test-project)
- [Generic STEP webviewer](http://step3d.com/)
- [CAx-IF synthetic STEP examples (contains materials!)](https://www.cax-if.org/library/index.html)
