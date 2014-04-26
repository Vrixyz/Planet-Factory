using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using MiniJSON;
using System.IO;
using System.Text;


public class SystemLoader : MonoBehaviour {

	public ArrayList planets = new ArrayList();
	//public ArrayList materials = new ArrayList();
	public string rootFolder = "Assets/Resources/System/1/";
	public string resourceFolder = "System/1/";

	void loadFromAstralInfo(Dictionary<string, object> dictPlanet) {
		print("dictPlanet['name']: " + dictPlanet["name"]);
		GameObject instance = Instantiate(Resources.Load("Prefabs/PlanetSphere")) as GameObject;
		
		string evolutionInfo = Load (rootFolder + dictPlanet["evolution"]);
		var dictEvolutions =  Json.Deserialize (evolutionInfo) as Dictionary<string, object>;
		var evolutionList = dictEvolutions["evolutions"] as List< object >;
		
		var dictEvolution = evolutionList[0] as Dictionary<string, object>;
		print("full position: " + ((Dictionary<string, object>)dictEvolution["pos"])["x"] + ";" + ((Dictionary<string, object>)dictEvolution["pos"])["y"] + ";" + ((Dictionary<string, object>)dictEvolution["pos"])["z"]);
		long x = (long)((Dictionary<string, object>)dictEvolution ["pos"]) ["x"];
		long y = (long)((Dictionary<string, object>)dictEvolution ["pos"]) ["y"];
		long z = (long)((Dictionary<string, object>)dictEvolution ["pos"]) ["z"];
		long size = (long)dictEvolution ["radius"];
		instance.transform.position = new Vector3(x, y, z);
		instance.transform.localScale = new Vector3(size, size, size);
		
		SGT_SurfaceDisplacement surfDisp = instance.AddComponent<SGT_SurfaceDisplacement>();
		surfDisp.SourceSurfaceMesh.GetMultiMesh(CubemapFace.PositiveX).Add((Mesh)Resources.Load ("Sphere128 (Surface) (Sphere).asset"));
		
		PlanetUpdater updater = instance.AddComponent<PlanetUpdater>();

		updater.folder = resourceFolder;
		print ("folder:" + updater.folder);
		// materials evolution
		
		List<object> materialsEvolution = (dictEvolution ["materials"]) as List<object>;
		
		print (dictEvolution ["materials"]);
		Dictionary<string, object> materialEvolution1 = materialsEvolution [0] as Dictionary<string, object>;
		print (materialEvolution1);
		print (materialEvolution1 ["name"].ToString ());
		print (materialEvolution1 ["file"].ToString ());
		
		updater.materials [ materialEvolution1["name"].ToString()] = (Texture2D)Resources.Load (resourceFolder + materialEvolution1["file"].ToString());
		print (updater.materials [materialEvolution1 ["name"].ToString ()]);
		
		updater.setEvolutions(evolutionList);
		updater.definition = dictPlanet;
		planets.Add (instance);
	}

	// Use this for initialization
	void Start () {
	}

	// Update is called once per frame
	void Update () {
	
	}

	public void initialize()
	{
		string systemInfo;
		
		systemInfo = Load (rootFolder + "systeme.json");
		print(systemInfo);
		var dict = Json.Deserialize (systemInfo) as Dictionary<string, object>;
		print("dict['astres'][0]: " + ((List<object>) dict["astres"])[0]);
		
		
		// store materials
		//materials.Add (((Dictionary<string, object>)((List<object>)dict ["materials"]) [0]));
		
		
		foreach (string obj in ((List<object>) dict["astres"])) {
		string astreInfo = Load (rootFolder + obj);
		print (astreInfo);
		var dictPlanet = Json.Deserialize (astreInfo) as Dictionary<string, object>;
		loadFromAstralInfo (dictPlanet);
	}
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
