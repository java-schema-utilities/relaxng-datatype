
Set lib = CreateObject("RelaxngDatatype.BuiltinDatatypeLibrary")
Set dt1 = lib.CreateDatatype("string")
Set dt2 = lib.CreateDatatype("string")

WScript.Echo dt1.IsValid("abc",Nothing)
WScript.Echo "Token: " + dt2.CreateValue("  xy z   ",Nothing)
