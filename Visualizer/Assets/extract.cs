using UnityEngine;
using System.Collections;
using System.Diagnostics;

public class extract : MonoBehaviour {
	public UIPopupList astre;
	public GameObject manager;
	private float time;
	private string planet;
	private UniverseTime w;
	// Use this for initialization
	void Start () {
		w = manager.GetComponent<UniverseTime>();

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
				planet = p.name;
		}
		time = w.elapsed;
		UnityEngine.Debug.LogError("time : " + time + "; planet : " + planet);
	}
}
