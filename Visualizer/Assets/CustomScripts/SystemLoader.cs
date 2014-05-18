using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using MiniJSON;
using System.IO;
using System.Text;


public class SystemLoader : MonoBehaviour {

    private static SystemLoader _instance = null;

    public static SystemLoader getInstance() {
        if (!_instance)
            _instance = new SystemLoader();
        return _instance;
    }

	public ArrayList planets = new ArrayList();

    //public ArrayList materials = new ArrayList();
	public string rootFolder = "Assets/Resources/System/1/";
	public string resourceFolder = "System/1/";
	public Dictionary<string, object> materialsDefinition;
    public string flavour = "generated";



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
		
        //TODO: load all materials and evolutions

		print (dictEvolution ["materials"]);
        for (int i = 0; i < materialsEvolution.Count; ++i)
        {
		    Dictionary<string, object> materialEvolution = materialsEvolution [i] as Dictionary<string, object>;
		    print (materialEvolution);
		    print (materialEvolution ["name"].ToString ());
		    print (materialEvolution ["file"].ToString ());
		
		    updater.materials [ materialEvolution["name"].ToString()] = (Texture2D)Resources.Load (resourceFolder + materialEvolution["file"].ToString());

		    print ("tried to load : " + resourceFolder + materialEvolution["file"].ToString());
		    print (updater.materials [materialEvolution ["name"].ToString ()]);
		}

		updater.setEvolutions(evolutionList);
		updater.definition = dictPlanet;
        updater.materialsDefinition = new Dictionary<string,object>(materialsDefinition);
        
        //TODO : put that in updater to update if materials evolve

        Texture2D t = TextureGenerator.generate(updater.materials, updater.materialsDefinition);
        // if (t == null)
        // WTF ???
        print("should be white");
        instance.GetComponent<SGT_Planet>().SurfaceTextureDay.SetTexture(t, 0);
        
        planets.Add (instance);
	}

	// Use this for initialization
	void Start () {
	}

	// Update is called once per frame
	void Update () {
	
	}

    private SystemLoader() { }

	public void initialize()
	{
		string systemInfo;
		print("Loading system.. by a script " + flavour);
		systemInfo = Load (rootFolder + "systeme.json");
		print(systemInfo);
		var dict = Json.Deserialize (systemInfo) as Dictionary<string, object>;
		print("dict['astres'][0]: " + ((List<object>) dict["astres"])[0]);
		materialsDefinition = dict ["materials"] as Dictionary<string, object>;
		print ("rock : " + materialsDefinition ["rock"]);
		Dictionary<string, object> rmat = materialsDefinition ["rock"] as Dictionary<string, object>;
		print ("rock, each key...");
		foreach (var v in rmat) {
			print(v.Key + " : " + v.Value);
		}
        print("materialsDefinition is null? " + (materialsDefinition == null));
		// store materials
		//materials.Add (((Dictionary<string, object>)((List<object>)dict ["materials"]) [0]));
		
		
		foreach (string obj in ((List<object>) dict["astres"])) {
			string astreInfo = Load (rootFolder + obj);
			print (astreInfo);
			var dictPlanet = Json.Deserialize (astreInfo) as Dictionary<string, object>;
            loadFromAstralInfo(dictPlanet);
		}
    }

	string Load(string fileName)
	{
		// Handle any problems that might arise when reading the text
		try
		{
            print("reading file");
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
                print("file has been read");

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
