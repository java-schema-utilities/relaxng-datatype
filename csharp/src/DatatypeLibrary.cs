namespace org.relaxng.datatype {

/**
 * A Datatype library
 * 
 * @author <a href="mailto:jjc@jclark.com">James Clark</a>
 * @author <a href="mailto:kohsuke.kawaguchi@eng.sun.com">Kohsuke KAWAGUCHI</a>
 */
public interface DatatypeLibrary {
	
	/**
	 * creates a new instance of DatatypeBuilder.
	 * 
	 * The callee should throw a DatatypeException in case of an error.
	 * 
	 * @param baseTypeLocalName
	 *		The local name of the base type.
	 * 
	 * @return
	 *		A non-null valid datatype object.
	 */
	DatatypeBuilder CreateDatatypeBuilder( string baseTypeLocalName );
//		throws DatatypeException;
	
	/**
	 * gets or creates a pre-defined type.
	 * 
	 * This is just a short-cut of createDatatypeBuilder(name).createDatatype();
	 * 
	 * The callee should throw a DatatypeException in case of an error.
	 * 
	 * @return
	 *		A non-null valid datatype object.
	 */
	Datatype CreateDatatype( string localTypeName ); // throws DatatypeException;
}

/**
* Factory class for the DatatypeLibrary class.
* 
* <p>
* The datatype library should provide the implementation of
* this interface if it wants to be found by the schema processors.
* The implementor also have to place a file in your jar file.
* See the reference datatype library implementation for detail.
* 
* @author <a href="mailto:jjc@jclark.com">James Clark</a>
* @author <a href="mailto:kohsuke.kawaguchi@sun.com">Kohsuke KAWAGUCHI</a>
*/
public interface DatatypeLibraryFactory
{
	/**
	* Creates a new instance of a DatatypeLibrary that supports 
	* the specified namespace URI.
	* 
	* @return
	*		<code>null</code> if the specified namespace URI is not
	*		supported.	
	*/
	DatatypeLibrary createDatatypeLibrary( string namespaceURI );
}

}
