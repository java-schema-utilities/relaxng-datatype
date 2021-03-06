namespace org.relaxng.datatype {

using System;

/**
 * creates an user-defined type by adding parameters to the pre-defined type.
 * 
 * @author <a href="mailto:jjc@jclark.com">James Clark</a>
 * @author <a href="mailto:kohsuke.kawaguchi@eng.sun.com">Kohsuke KAWAGUCHI</a>
 */
public interface DatatypeBuilder {
	
	/**
	 * adds a new parameter.
	 *
	 * @param name
	 *		the name of the parameter to be added.
	 * @param strValue
	 *		the raw value of the parameter. Caller may not normalize this value
	 *		becuase any white space is potentially significant.
	 * @param context
	 *		The context information which can be used by the callee to
	 *		acquire additional information. This context object is valid only
	 *		during this method call. The callee may not keep the reference
	 *		to this object.
	 * @exception	DatatypeException
	 *		when the given parameter is inappropriate for some reason.
	 *		The callee is responsible to recover from this error.
	 *		That is, the object should behave as if no such error was occured.
	 */
	void AddParameter( String name, String strValue, ValidationContext context );
//		throws DatatypeException;
	
	/**
	 * derives a new Datatype from a Datatype by parameters that were already set
	 * through the addParameter method.
	 * 
	 * @exception DatatypeException
	 *		DatatypeException must be thrown if the derivation is somehow invalid.
	 *		For example, required parameter is missing, etc. The exception should
	 *		contain a diagnosis message if possible.
	 */
	Datatype CreateDatatype(); // throws DatatypeException;
}

}
