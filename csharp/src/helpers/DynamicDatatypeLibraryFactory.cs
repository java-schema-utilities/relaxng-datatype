using System;
using System.IO;
using System.Reflection;

namespace org.relaxng.datatype.helpers
{
	/// <summary>
	/// Loads a datatype library dynamically.
	/// </summary>
	public class DynamicDatatypeLibraryFactory : DatatypeLibraryFactory
	{
		public DynamicDatatypeLibraryFactory() : this(GetBaseDir(),"*.rngdl") {}

		// compute the base directory name to search plug-in datatype libraries.
		private static string GetBaseDir() 
		{
			string baseName = Assembly.GetExecutingAssembly().Location;
			if(baseName=="")	return ".";
			else				return Path.GetDirectoryName(baseName);
		}

		public DynamicDatatypeLibraryFactory( string dir, string mask )
		{
			string[] fileNames = Directory.GetFiles( dir , mask);

			plugins = new DatatypeLibraryFactory[fileNames.Length];
			int idx=0;
			
			// load assembly files
			foreach( string name in fileNames ) 
			{
				try
				{
					AssemblyName n = new AssemblyName();
					n.CodeBase = name;
					Assembly a = Assembly.Load(n);
					plugins[idx++] = (DatatypeLibraryFactory)Activator.CreateInstance(
						a.GetType("DatatypeLibraryFactoryImpl"));
				} 
				catch( Exception ) {} // ignore this plug-in and proceed to next
			}
		}

		private readonly DatatypeLibraryFactory[] plugins;

		public DatatypeLibrary createDatatypeLibrary( string namespaceURI )
		{
			foreach( DatatypeLibraryFactory f in plugins )
			{
				try
				{
					DatatypeLibrary lib = f.createDatatypeLibrary(namespaceURI);
					if(lib!=null)	return lib;
				} 
				catch( Exception ) {} // ignore this plug-in and proceed to next
			}
			return null;
		}

	}
}
