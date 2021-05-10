About & requirements

This package installs the Free Pascal Compiler 3.0rc1 for JVM. It requires the JDK 1.5 or later to be installed and the "java" executable to be in the PATH.

This package can be used to compile for
  • Java JVM 1.5 or later
  • the Dalvik VM for Android 4.0 or later


Notes

This is a pure compiler port. This means that most of the standard Pascal run time library (RTL) is not available at this time. The reason is that all Pascal language features cannot be supported when targeting the JVM, and as a result large parts of the run time library have to be rewritten.

You can find an overview of the supported language and RTL features at http://wiki.freepascal.org/FPC_JVM/Language

Instead of the standard FPC RTL and packages, you can make use of the standard JDK (1.5)/Android DK (r14) classes via resp. the jdk15 and androidr14 units.


Usage

The compiler binary's name is ppcjvm, and it can also be invoked using fpc -Pjvm.

If you wish to create additional Pascal units to interface with other Java classes, you can use the javapp utility. See http://wiki.freepascal.org/FPC_JVM/Building#Creating_interfaces_for_other_Java_classes for more information.