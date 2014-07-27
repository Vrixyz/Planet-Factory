using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using MiniJSON;
using System.IO;
using System.Text;


public class SystemLoader : MonoBehaviour {

    private static SystemLoader _instance = null;
    public bool hasLoaded = false;
    UniverseTime time = null;

    public static SystemLoader getInstance() {
        if (!_instance)
        {
            GameObject manager = GameObject.Find("Manager");
            _instance = manager.AddComponent<SystemLoader>();
            
        }
        return _instance;
    }

	public ArrayList planets = new ArrayList();

    //public ArrayList materials = new ArrayList();
	public string rootFolder = "Assets/Resources/System/1/";
	public string resourceFolder = "System/1/";
	public Dictionary<string, object> materialsDefinition;


	void loadFromAstralInfo(Dictionary<string, object> dictPlanet) {
		print("dictPlanet['name']: " + dictPlanet["name"]);
        GameObject instance;
        if (dictPlanet["type"].Equals("star"))
		    instance = Instantiate(Resources.Load("Prefabs/Star")) as GameObject;
		else
            instance = Instantiate(Resources.Load("Prefabs/PlanetSphere")) as GameObject;
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
        instance.name = (string)dictPlanet["name"];
        // print(dictPlanet["name"] + " : " + dictPlanet["type"] + "    (dictPlanet[\"type\"].Equals(\"star\") = " +  (dictPlanet["type"].Equals("star") ? "true" : "false"));
        PlanetUpdater updater = instance.AddComponent<PlanetUpdater>();

        updater.folder = resourceFolder;
        updater.setEvolutions(evolutionList, time);
        updater.definition = dictPlanet;

        if (!dictPlanet["type"].Equals("star"))
        {
            //Surface Displacement
		    SGT_SurfaceDisplacement surfDisp = instance.AddComponent<SGT_SurfaceDisplacement>();
		    surfDisp.SourceSurfaceMesh.GetMultiMesh(CubemapFace.PositiveX).Add((Mesh)Resources.Load ("Sphere128 (Surface) (Sphere).asset"));
		
            //print ("folder:" + updater.folder);
		    
            // materials evolution
            List<object> materialsEvolution = (dictEvolution["materials"]) as List<object>;


            print(dictEvolution["materials"]);
            for (int i = 0; i < materialsEvolution.Count; ++i)
            {
                Dictionary<string, object> materialEvolution = materialsEvolution[i] as Dictionary<string, object>;
            
                 // TODO : this won't work on linux !
                var path = "file://" + Application.dataPath + "/Resources/" + resourceFolder + materialEvolution["file"].ToString() + ".png";
                print("path : " + path);
                var www = new WWW(path);
                while (!www.isDone) ;
                updater.materials[materialEvolution["name"].ToString()] = www.texture;

                //print("tried to load : " + resourceFolder + materialEvolution["file"].ToString());
                //print(updater.materials[materialEvolution["name"].ToString()]);
            }
            updater.materialsDefinition = new Dictionary<string, object>(materialsDefinition);

            //TODO : put that in updater to update if materials evolve

            Texture2D t = TextureGenerator.generate(updater.materials, updater.materialsDefinition);
            // if (t == null)
            // WTF ???

            instance.GetComponent<SGT_Planet>().SurfaceTextureDay.SetTexture(t, 0);
            Texture2D t_n = TextureGenerator.MakeNight(t);
            instance.GetComponent<SGT_Planet>().SurfaceTextureNight.SetTexture(t_n, 0);
        }
        planets.Add(instance);
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
        time = this.gameObject.AddComponent<UniverseTime>();
        
        string systemInfo;
		systemInfo = Load (rootFolder + "systeme.json");
		print(systemInfo);
		var dict = Json.Deserialize (systemInfo) as Dictionary<string, object>;
        time.totalTime = (long)dict["totalTime"];
		print("dict['astres'][0]: " + ((List<object>) dict["astres"])[0]);
		materialsDefinition = dict ["materials"] as Dictionary<string, object>;
		//print ("rock : " + materialsDefinition ["rock"]);
		/*Dictionary<string, object> rmat = materialsDefinition ["rock"] as Dictionary<string, object>;
		print ("rock, each key...");
		foreach (var v in rmat) {
			print(v.Key + " : " + v.Value);
		} */
        print("materialsDefinition is null? " + (materialsDefinition == null));
		// store materials
		//materials.Add (((Dictionary<string, object>)((List<object>)dict ["materials"]) [0]));
		
		
		foreach (string obj in ((List<object>) dict["astres"])) {
			string astreInfo = Load (rootFolder + obj);
			print (astreInfo);
			var dictPlanet = Json.Deserialize (astreInfo) as Dictionary<string, object>;
            loadFromAstralInfo(dictPlanet);
		}
        print("System loaded");
        hasLoaded = true;
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
