using UnityEngine;
using System.Collections;

public class ModifyPlanetHeight : MonoBehaviour {
	SGT_Planet _planetDefinition;
	ArrayList displacement;
	int displacementIndex;
	int maxIndex = 1;
	// Use this for initialization
	void Start () {
		displacement = new ArrayList ();
		Texture2D t = this.gameObject.GetComponent<SGT_SurfaceDisplacement> ().DisplacementTexture.GetTexture2D(CubemapFace.PositiveX);
		print ("t = " + t);
		print ("t == null = " + (t == null));
		displacement.Add(t);
		Texture2D t2 = (Texture2D)Resources.Load ("Earth_old_displacement_sphere");
		print ("t2 = " + t2);
		print ("t2 == null = " + (t2 == null));
		displacement.Add ( t2);
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKeyDown (KeyCode.Space)) {
			displacementIndex++;
			if (displacementIndex > maxIndex)
				displacementIndex = 0;
			SGT_SurfaceDisplacement surfDisp = this.gameObject.GetComponent<SGT_SurfaceDisplacement>();
			surfDisp.DisplacementTexture.SetTexture((Texture2D)displacement.ToArray().GetValue(displacementIndex), CubemapFace.PositiveX);
		}
	}
}
