namespace org.relaxng.datatype {

/**
 * Datatype object.
 * 
 * This object has the following functionalities:
 * 
 * <ol>
 *  <li> functionality to identifies a class of character sequences. This is
 *       done through the isValid method.
 * 
 *  <li> functionality to produce "value object" from a character sequence and
 *		 a context information.
 * 
 *  <li> functionality to test the equality of two value objects.
 * </ol>
 * 
 * This interface also defines optional createStreamingValidator method,
 * which is supposed to efficiently support the validation of
 * large character sequence.
 * 
 * @author <a href="mailto:jjc@jclark.com">James Clark</a>
 * @author <a href="mailto:kohsuke.kawaguchi@eng.sun.com">Kohsuke KAWAGUCHI</a>
 */
public interface Datatype {
	
	/**
	 * checks if the specified 'literal' matchs this Datatype
	 * under the current context.
	 * 
	 * @param literal
	 *		the lexical representation to be checked.
	 * @param context
	 *		context information that may be
	 *		necessary to validate the given literal.
	 * 
	 * @return
	 *		true if the 'literal' is a member of this Datatype;
	 *		false if it's not a member of this Datatype.
	 */
	bool IsValid( string literal, ValidationContext context );
	
	/**
	 * similar to the isValid method but throws an exception with diagnosis
	 * in case of errors.
	 * 
	 * <p>
	 * If the specified 'literal' is a valid lexical representation for this datatype,
	 * then this method must return without throwing any exception.
	 * If not, the callee must throw an exception (with diagnosis message, if possible.)
	 * 
	 * <p>
	 * The application can use this method to provide detailed error message to users.
	 * This method is kept separate from the isValid method to achieve
	 * higher performance during normal validation.
	 * 
	 * @exception DatatypeException
	 *		If the given literal is invalid, then this exception is thrown.
	 *		If the callee supports error diagnosis, then the exception should
	 *		contain a diagnosis message.
	 */
	void CheckValid( string literal, ValidationContext context );
//		throws DatatypeException;
	
	/**
	 * creates an instance of the streaming validator for this type.
	 * 
	 * <p>
	 * By using streaming validators instead of the isValid method,
	 * the caller can avoid keeping the entire string into the memory,
	 * which is sometimes quite big.
	 * 
	 * @param context
	 *		context information that may be
	 *		necessary to validate the given literal.
	 *		The callee may keep a reference to this context object
	 *		only while the returned streaming validator is being used.
	 * 
	 * @exception UnsupportedOperationException
	 *		if the streaming validation is not supported by the callee.
	 */
	DatatypeStreamingValidator CreateStreamingValidator( ValidationContext context );
	
	/**
	 * converts lexcial value and the current context to the corresponding
	 * value object.
	 * 
	 * <p>
	 * The caller cannot generally assume that the value object is a meaningful
	 * Java object. For example, the caller cannot expect this method to return
	 * java.lang.Number type for the "integer" type of XML Schema Part2.
	 * 
	 * <p>
	 * Also, the caller cannot assume that the equals method and the hashCode method
	 * of the value object is consistent with the semantics of the datatype.
	 * For that purpose, the sameValue method and the valueHashCode method have to
	 * be used. Note that this means you cannot use classes like
	 * <code>java.util.Hashtable</code> to store the value objects.
	 * 
	 * <p>
	 * The returned value object should be used solely for the sameValue method.
	 * 
	 * @return	null
	 *		when the given lexical value is not a valid lexical value for this type.
	 */
	object CreateValue( string literal, ValidationContext context );
	
	/**
	 * tests the equality of two value objects which was originally created by
	 * the createValue method of this object.
	 * 
	 * The bahavior is undefined if objects not created by this type is passed.
	 * It is the caller's responsibility to ensure that value objects
	 * belong to this type.
	 * 
	 * @return
	 *		true if two value objects are considered equal according to
	 *		the definition of this datatype; false if otherwise.
	 */
	bool SameValue( object value1, object value2 );
	
	
	/**
	 * computes the hash code for a value object,
	 * which is consistent with the sameValue method.
	 * 
	 * @return
	 *		hash code for the specified value object.
	 */
	int ValueHashCode( object value );

	/**
	 * Checks if the ID/IDREF semantics is associated with this
	 * datatype.
	 * 
	 * <p>
	 * This method is introduced to support the RELAX NG DTD
	 * compatibility spec. (Of course it's always free to use
	 * this method for other purposes.)
	 * 
	 * <p>
	 * If you are implementing a datatype library and have no idea about
	 * the "RELAX NG DTD compatibility" thing, just return
	 * <code>ID_TYPE_NULL</code> is fine.
	 * 
	 * @return
	 *		If this datatype doesn't have any ID/IDREF semantics,
	 *		it returns {@link #ID_TYPE_NULL}. If it has such a semantics
	 *		(for example, XSD:ID, XSD:IDREF and comp:ID type), then
	 *		it returns {@link #ID_TYPE_ID}, {@link #ID_TYPE_IDREF} or
	 *		{@link #ID_TYPE_IDREFS}.
	 */
	IDType IdType { get; }
	
	/**
	 * Checks if this datatype may need a context object for
	 * the validation.
	 * 
	 * <p>
	 * The callee must return true even when the context
	 * is not always necessary. (For example, the "QName" type
	 * doesn't need a context object when validating unprefixed
	 * string. But nonetheless QName must return true.)
	 * 
	 * <p>
	 * XSD's <code>string</code> and <code>short</code> types
	 * are examples of context-independent datatypes.
	 * Its <code>QName</code> and <code>ENTITY</code> types
	 * are examples of context-dependent datatypes.
	 * 
	 * <p>
	 * When a datatype is context-independent, then
	 * the {@link #isValid} method, the {@link #checkValid} method,
	 * the {@link #createStreamingValidator} method and
	 * the {@link #createValue} method can be called without
	 * providing a context object.
	 * 
	 * @return
	 *		<b>true</b> if this datatype is context-dependent
	 *		(it needs a context object sometimes);
	 * 
	 *		<b>false</b> if this datatype is context-<b>in</b>dependent
	 *		(it never needs a context object).
	 */
	bool IsContextDependent { get; }
}

public enum IDType {
	ID_TYPE_NULL	= 0,
	ID_TYPE_ID		= 1,
	ID_TYPE_IDREF	= 2,
	ID_TYPE_IDREFS	= 3
}

}
