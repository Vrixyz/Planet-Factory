using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using MiniJSON;
using System.IO;
using System.Text;

public class extract : MonoBehaviour {
	public UIPopupList astre;
	public GameObject manager;
	private float time;
	private string planet;
	private UniverseTime w;
	private Vector3 angle;
	private Vector3 pos;
	private string disp;
	private long rad;
	private List<Dictionary<string, object>>mats;
	private List<object> res;
	private float rota;
	private Dictionary<string, object> collector;
	// Use this for initialization
	void Start () {
		w = manager.GetComponent<UniverseTime>();
		mats = new List<Dictionary<string, object>>();
		res = new List<object>();
		collector = new Dictionary<string, object> ();
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnClick () {

		GameObject manager = GameObject.Find ("Manager");
		SystemLoader sys = manager.GetComponent<SystemLoader>();
		foreach (GameObject p in sys.planets)
		{
			if (astre.selection == p.name)
			{
				planet = p.name;
				time = w.elapsed;
				res.Add(time);
				PlanetUpdater updater = p.GetComponent<PlanetUpdater>();
				extraction(planet, time, updater.evolutions);
			}
		}
	}

	void extraction(string planet, float time, List<object> evolutions)
	{
		bool uPos = false;
		bool uRot = false;
		Dictionary<string, object> nextPosition = new Dictionary<string, object>();
		Dictionary<string, object> nextRotation = new Dictionary<string, object>();

		//add secu when no mat
		Dictionary<string, object> first = (Dictionary<string, object>)(evolutions [0]);
		if (first.ContainsKey("radius"))
			rad = (long)first ["radius"];
		if (first.ContainsKey("materials"))
		{
			List<object> materials = (first["materials"])as List<object>;
			for (int i = 0; i < materials.Count; ++i)
			{
				Dictionary<string, object> materialEvolution = materials[i] as Dictionary<string, object>;
				mats.Add(materialEvolution);
			}
		}
		for (int i = evolutions.Count - 1; i >= 0; --i) 
		{
			Dictionary<string, object> current = (Dictionary<string, object>)(evolutions[i]);
			if ((long)current["date"] < time) {
				if (uPos == false && current.ContainsKey("pos"))
				{
					long x = (long) ((Dictionary<string, object>)current["pos"]) ["x"];
					long y = (long) ((Dictionary<string, object>)current["pos"]) ["y"];
					long z = (long) ((Dictionary<string, object>)current["pos"]) ["z"];
					// TODO: then extrapolate to the exact time.
					Vector3 currentP = new Vector3(x, y, z);
					if (nextPosition.ContainsKey("date"))
					{
						float progress = (((float)(time) - (float)((long)current["date"])) / (((float)((long)nextPosition["date"]) - (float)((long)current["date"]))));
						//print ("progress: " + progress);
						currentP.x += ((long)(((Dictionary<string, object>)nextPosition["pos"])["x"]) - currentP.x) * progress;
						currentP.y += ((long)(((Dictionary<string, object>)nextPosition["pos"])["y"]) - currentP.y) * progress;
						currentP.z += ((long)(((Dictionary<string, object>)nextPosition["pos"])["z"]) - currentP.z) * progress;
					}
					uPos = true;
					pos = currentP;
				}
				if (uRot == false && current.ContainsKey("rotation"))
				{
					float rot = (long) (current["rotation"]);
					//print ("rotation: " + x);
					if (nextPosition.ContainsKey("date"))
					{
						float progress = (((float)time - (float)((long)current["date"])) / (((float)((long)nextPosition["date"]) - (float)((long)current["date"]))));
						//print ("progress: " + progress);
						rot += (((long)(nextRotation["rotation"])) - rot) * progress;
						
					}
					rota = rot;
					angle = new Vector3(0, rot, 0);
				}
				
				uRot = true;
				if (current.ContainsKey("displacement"))
				{
					disp = (string)current["displacement"];
				}
				}
	          if (current.ContainsKey("pos"))
	          	nextPosition = current;
	          if (current.ContainsKey("rotation"))
	          	nextRotation = current;

		}
		collector.Add ("time", time);
		collector.Add ("radius", rad);
		collector.Add ("rotation", rota);
		collector.Add ("vectorRotation", angle);
		collector.Add ("pos", pos);
		collector.Add ("displacement", disp);	
		collector.Add ("materials", mats);	

		string resultat =  Json.Serialize(collector);
		var test = Application.dataPath + "/Resources/" + planet + "Evolution.json";
		TextWriter tw = new StreamWriter(test);
		tw.WriteLine(resultat);
		tw.Close();	
	}
	
}
