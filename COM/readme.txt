RELAX NG Datatype Interface COM Implementation
==============================================
       Copyright 2001, Kohsuke KAWAGUCHI
       Distributed under the BSD lincense


This implementation mimics Java version of the
interface. For the complete documentation, see
the javadoc documentation of Java version.

This implementation also contains the built-in
datatype library, as defined in the spec. You
can get an instance of the built-in datatype
library by:

VB:
Set lib = CreateObject("relaxngDatatype.BuiltinDatatypeLibrary");

JScript:
var lib = new ActiveXObject("relaxngDatatype.BuiltinDatatypeLibrary");


Feel free to contact me if you've found a bug
or something.

Enjoy!
