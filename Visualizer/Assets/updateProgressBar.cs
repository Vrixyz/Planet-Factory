using UnityEngine;
using System.Collections;

public class updateProgressBar : MonoBehaviour
{

    public GameObject manager;
    static float i = 0;
    public float totalTime = 0;
    bool pass = false;
    // Use this for initialization
    void Start()
    {

    }
    // Update is called once per frame
    void Update()
    {
        totalTime = manager.GetComponent<UniverseTime>().totalTime;
        this.GetComponent<UISlider>().sliderValue = (manager.GetComponent<UniverseTime>().getElapsed()) / totalTime;
    }
}