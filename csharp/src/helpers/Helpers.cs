namespace org.relaxng.datatype.helpers {

using org.relaxng.datatype;
using System.Text;

public class StreamingValidatorImpl : DatatypeStreamingValidator {
	
	private readonly StringBuilder buf = new StringBuilder();
	private readonly ValidationContext context;
	private readonly Datatype dt;
	
	public StreamingValidatorImpl( Datatype _dt, ValidationContext vc ) {
		this.context = vc;
		this.dt = _dt;
	}
	
	public void AddCharacters( char[] chs, int start, int len ) {
		buf.Append(chs,start,len);
	}
	public bool IsValid() {
		return dt.IsValid(buf.ToString(),context);
	}
	public void CheckValid() {
		dt.CheckValid(buf.ToString(),context);
	}
}

}