using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using MiniJSON;
using System.IO;
using System.Text;


public class SystemLoader : MonoBehaviour {

	// Use this for initialization
	void Start () {
		string systemInfo;

		systemInfo = Load ("Assets/Resources/System/1/systeme.json");
		print(systemInfo);
		var dict = Json.Deserialize (systemInfo) as Dictionary<string, object>;
		print("dict['astres'][0]: " + ((List<object>) dict["astres"])[0]);

		string astreInfo = Load ("Assets/Resources/System/1/" + ((List<object>) dict["astres"])[0]);
		print(astreInfo);
		var dictPlanet = Json.Deserialize (astreInfo) as Dictionary<string, object>;
		print("dictPlanet['name']: " + dictPlanet["name"]);
		GameObject instance = Instantiate(Resources.Load("Prefabs/PlanetSphere")) as GameObject;

		string evolutionInfo = Load ("Assets/Resources/System/1/" + dictPlanet["evolution"]);
		var dictEvolutions =  Json.Deserialize (evolutionInfo) as Dictionary<string, object>;
		var evolutionList = dictEvolutions["evolutions"] as List< object >;

		var dictEvolution = evolutionList[0] as Dictionary<string, object>;
		print("full position: " + ((Dictionary<string, object>)dictEvolution["pos"])["x"] + ";" + ((Dictionary<string, object>)dictEvolution["pos"])["y"] + ";" + ((Dictionary<string, object>)dictEvolution["pos"])["z"]);
		long x = (long)((Dictionary<string, object>)dictEvolution ["pos"]) ["x"];
		long y = (long)((Dictionary<string, object>)dictEvolution ["pos"]) ["y"];
		long z = (long)((Dictionary<string, object>)dictEvolution ["pos"]) ["z"];
		instance.transform.position = new Vector3(x, y, z);

		SGT_SurfaceDisplacement surfDisp = (SGT_SurfaceDisplacement)instance.AddComponent ("SGT_SurfaceDisplacement");
		surfDisp.SourceSurfaceMesh.GetMultiMesh(CubemapFace.PositiveX).Add((Mesh)Resources.Load ("Sphere128 (Surface) (Sphere).asset"));

		PlanetUpdater updater = (PlanetUpdater)instance.AddComponent ("PlanetUpdater");
		updater.setEvolutions(evolutionList);
		updater.definition = dictPlanet;
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	string Load(string fileName)
	{
		// Handle any problems that might arise when reading the text
		try
		{
			string line = new string('c', 0);
			string entireFile = new string('c', 0);
			// Create a new StreamReader, tell it which file to read and what encoding the file
			// was saved as
			StreamReader theReader = new StreamReader(fileName, Encoding.Default);
			
			// Immediately clean up the reader after this block of code is done.
			// You generally use the "using" statement for potentially memory-intensive objects
			// instead of relying on garbage collection.
			// (Do not confuse this with the using directive for namespace at the 
			// beginning of a class!)
			using (theReader)
			{
				// While there's lines left in the text file, do this:
				do
				{
					line = theReader.ReadLine();
					
					if (line != null)
					{
						entireFile += line;
					}
				}
				while (line != null);
				
				// Done reading, close the reader and return true to broadcast success    
				theReader.Close();
				return entireFile;
			}
		}
		
		// If anything broke in the try block, we throw an exception with information
		// on what didn't work
		catch (IOException e)
		{
			print(e.Message);
			throw e;
		}
	}
}
