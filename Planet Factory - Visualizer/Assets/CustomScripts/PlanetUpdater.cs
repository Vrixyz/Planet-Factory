using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class PlanetUpdater : MonoBehaviour {
	public Dictionary<string, object> definition;
	public List<object> evolutions;
	UniverseTime time = new UniverseTime(); // TODO: make this a singleton
	public Dictionary<string, Texture2D> materials = new Dictionary<string, Texture2D>();

	// Use this for initialization
	void Start () {
	
	}

	Dictionary<string, Texture2D> displacements;
	public void setEvolutions(List<object> evol)
	{
		evolutions = evol;
		//print ("evol: " + evolutions);
		displacements = new Dictionary<string, Texture2D> ();
		for (int i = 0; i < evolutions.Count; ++i) {
			Dictionary<string, object> current = (Dictionary<string, object>)(evolutions [i]);
			if (current.ContainsKey("displacement"))
			{
				//print("cur disp: " + "System/1/" + current["displacement"]);
				//print ((Texture2D)Resources.Load ( "System/1/" +  current["displacement"]));

				displacements.Add ((string)current["displacement"], (Texture2D)Resources.Load ("System/1/" + current["displacement"]));
			}
		}
		//Texture2D t2 = (Texture2D)Resources.Load ("Assets/Resources/System/1/Maps/soleilDisplacement2.png");
		//displacement.Add ( t2);
	}

	// Update is called once per frame
	void Update () {
		bool uPos = false;
		bool uRot = false;
		bool uDisplacement = false;
		Dictionary<string, object> nextPosition = new Dictionary<string, object>();

		for (int i = evolutions.Count - 1; i >= 0; --i) {
			Dictionary<string, object> current = (Dictionary<string, object>)(evolutions[i]);
			if ((long)current["date"] < time.timer.ElapsedMilliseconds) {
				if (uPos == false && current.ContainsKey("pos"))
				{
					long x = (long) ((Dictionary<string, object>)current["pos"]) ["x"];
					long y = (long) ((Dictionary<string, object>)current["pos"]) ["y"];
					long z = (long) ((Dictionary<string, object>)current["pos"]) ["z"];
					// TODO: then extrapolate to the exact time.
					Vector3 currentPosition = new Vector3(x, y, z);
					if (nextPosition.ContainsKey("date"))
					{
						float progress = (((float)(time.timer.ElapsedMilliseconds) - (float)((long)current["date"])) / (((float)((long)nextPosition["date"]) - (float)((long)current["date"]))));
						//print ("progress: " + progress);
						currentPosition.x += ((long)(((Dictionary<string, object>)nextPosition["pos"])["x"]) - currentPosition.x) * progress;
						currentPosition.y += ((long)(((Dictionary<string, object>)nextPosition["pos"])["y"]) - currentPosition.y) * progress;
						currentPosition.z += ((long)(((Dictionary<string, object>)nextPosition["pos"])["z"]) - currentPosition.z) * progress;

					}
					this.gameObject.transform.position = currentPosition;
					uPos = true;
				}
				if (uRot == false && current.ContainsKey("rotation"))
				{
					long x = (long) (current["rotation"]);
					//print ("rotation: " + x);
					// TODO: then extrapolate to the exact time.
					this.gameObject.transform.eulerAngles = new Vector3(x, 0, 0);
					uRot = true;
				}
				if (uDisplacement == false && current.ContainsKey("displacement"))
				{
					// TODO: probably no extrapolation to do, then update it differently

					this.gameObject.GetComponent<SGT_SurfaceDisplacement>().DisplacementTexture.SetTexture (displacements[(string)current["displacement"]], CubemapFace.PositiveX);
					uDisplacement = true;
				}
			}
			if (current.ContainsKey("pos"))
				nextPosition = current;
		}
	}
}
