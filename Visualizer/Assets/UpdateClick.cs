using UnityEngine;
using System.Collections;

public class UpdateClick : MonoBehaviour {

    public GameObject manager;
    static float i = 0;
    float totalTime = 0;
    bool pass = false;
    // Use this for initialization
    void Start()
    {
    }

    void OnSliderChange()
    {

//		System.TimeSpan t = new System.TimeSpan(0,0,0, (int)((this.GetComponent<UISlider>().sliderValue * 100.0f)), (int)((this.GetComponent<UISlider>().sliderValue * 100.0f)  * 1000.0f) % 1000);
 //       manager.GetComponent<UniverseTime>().Reset();
//		manager.GetComponent<UniverseTime>().Start();
		manager.GetComponent<UniverseTime>().setElapsed((this.GetComponent<UISlider>().sliderValue * 100.0f));
//		print ( manager.GetComponent<UniverseTime>().timer.Elapsed.Seconds + "+" +manager.GetComponent<UniverseTime>().timer.Elapsed.Milliseconds);

//		print(t.Seconds +"-"+ t.Milliseconds);

    }
}
