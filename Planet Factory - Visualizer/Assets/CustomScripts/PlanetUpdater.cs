using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class PlanetUpdater : MonoBehaviour {
	public Dictionary<string, object> definition;
	public List<object> evolutions;
	UniverseTime time = new UniverseTime();

	// Use this for initialization
	void Start () {
	
	}

	public void setEvolutions(List<object> evol)
	{
		evolutions = evol;
		print ("evol: " + evolutions);
	}

	// Update is called once per frame
	void Update () {
		bool uPos = false;
		bool uRot = false;
		for (int i = evolutions.Count - 1; i >= 0; --i) {
			Dictionary<string, object> current = (Dictionary<string, object>)(evolutions[i]);
			if ((long)current["date"] < time.timer.ElapsedMilliseconds) {
				if (uPos == false && current.ContainsKey("pos"))
				{
					long x = (long) ((Dictionary<string, object>)current["pos"]) ["x"];
					long y = (long) ((Dictionary<string, object>)current["pos"]) ["y"];
					long z = (long) ((Dictionary<string, object>)current["pos"]) ["z"];
					// TODO: then extrapolate to the exact time.
					this.gameObject.transform.position = new Vector3(x, y, z);
					uPos = true;
				}
				if (uRot == false && current.ContainsKey("rotation"))
				{
					long x = (long) (current["rotation"]);
					print ("rotation: " + x);
					// TODO: then extrapolate to the exact time.
					this.gameObject.transform.eulerAngles = new Vector3(x, 0, 0);
					uRot = true;
				}
			}
		}
	}
}
