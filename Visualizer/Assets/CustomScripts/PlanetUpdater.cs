using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class PlanetUpdater : MonoBehaviour {
	public Dictionary<string, object> definition;
	public List<object> evolutions;
	UniverseTime time = null;
	public Dictionary<string, Texture2D> materials = new Dictionary<string, Texture2D>();
    public Dictionary<string, object> materialsDefinition = null;

	public string folder = "System/1/";
	// Use this for initialization
	void Start () {

	}

	Dictionary<string, Texture2D> displacements;
	public void setEvolutions(List<object> evol, UniverseTime t)
	{
        time = t;
		evolutions = evol;
		//print ("evol: " + evolutions);
		displacements = new Dictionary<string, Texture2D> ();
		for (int i = 0; i < evolutions.Count; ++i) {
			Dictionary<string, object> current = (Dictionary<string, object>)(evolutions [i]);
			if (current.ContainsKey("displacement"))
			{
				//print("cur disp: " + "System/1/" + current["displacement"]);
				//print ((Texture2D)Resources.Load ( "System/1/" +  current["displacement"]));

				displacements.Add ((string)current["displacement"], (Texture2D)Resources.Load (folder + current["displacement"]));
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
		Dictionary<string, object> nextRotation = new Dictionary<string, object>();

		for (int i = evolutions.Count - 1; i >= 0; --i) {
			Dictionary<string, object> current = (Dictionary<string, object>)(evolutions[i]);
			if ((long)current["date"] < time.timer.ElapsedMilliseconds) {
				if (uPos == false && current.ContainsKey("pos"))
				{
					long x = (long) ((Dictionary<string, object>)current["pos"]) ["x"];
					long y = (long) ((Dictionary<string, object>)current["pos"]) ["y"];
					long z = (long) ((Dictionary<string, object>)current["pos"]) ["z"];
					// TODO: then extrapolate to the exact time.
					Vector3 currentP = new Vector3(x, y, z);
					if (nextPosition.ContainsKey("date"))
					{
						float progress = (((float)(time.timer.ElapsedMilliseconds) - (float)((long)current["date"])) / (((float)((long)nextPosition["date"]) - (float)((long)current["date"]))));
						//print ("progress: " + progress);
						currentP.x += ((long)(((Dictionary<string, object>)nextPosition["pos"])["x"]) - currentP.x) * progress;
						currentP.y += ((long)(((Dictionary<string, object>)nextPosition["pos"])["y"]) - currentP.y) * progress;
						currentP.z += ((long)(((Dictionary<string, object>)nextPosition["pos"])["z"]) - currentP.z) * progress;

					}
					this.gameObject.transform.position = currentP;
					uPos = true;
				}
				if (uRot == false && current.ContainsKey("rotation"))
				{
					float rot = (long) (current["rotation"]);
					//print ("rotation: " + x);
					if (nextPosition.ContainsKey("date"))
					{
						float progress = (((float)(time.timer.ElapsedMilliseconds) - (float)((long)current["date"])) / (((float)((long)nextRotation["date"]) - (float)((long)current["date"]))));
						//print ("progress: " + progress);
						rot += (((long)(nextRotation["rotation"])) - rot) * progress;

					}
					this.gameObject.transform.eulerAngles = new Vector3(0, rot, 0);
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
			if (current.ContainsKey("rotation"))
				nextRotation = current;
		}
        print("ca va planter !");
        Dictionary<string, object> mat_def = materialsDefinition;

        print(definition["name"]);
        if (mat_def == null)
            print("it's null");
        print(" mat_def : " + mat_def["rock"]);
        Dictionary<string, object> rmat = mat_def["rock"] as Dictionary<string, object>;
        print("rock : ");
        foreach (var v in rmat)
        {
            print(v.Key + " : " + v.Value);
        }
        //return;
        //Texture2D t = TextureGenerator.generate(materials, mat_def);
        //// if (t == null)
        //// WTF ???
        //print("should be white");
        //gameObject.GetComponent<SGT_Planet>().SurfaceTextureDay.SetTexture(t, 0);

	}
}
