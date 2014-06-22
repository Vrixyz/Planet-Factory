using UnityEngine;
using System.Collections;

public class updateProgressBar : MonoBehaviour {

    public GameObject manager;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
        float totalTime = manager.GetComponent<UniverseTime>().totalTime;

        this.GetComponent<UISlider>().sliderValue = (manager.GetComponent<UniverseTime>().timer.Elapsed.Seconds) / totalTime;
	}
}
