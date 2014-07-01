﻿using UnityEngine;
using UnityEngine;
using System.Collections;

public class RayCastToPlanets : MonoBehaviour {
	public GameObject controler;
    public GameObject indicator; 
    private UILabel[] labels;
	private UIPopupList[] pops;
	public int x, y;
	public PlanetUpdater pu;
	public UILabel Pos;
	public UILabel materiel;
	public UILabel planet;
	public GameObject menuInGame;

    GameObject priv_indicator;
    float initial_particle_speed;
	// Use this for initialization
	void Start () {
        priv_indicator = (GameObject)GameObject.Instantiate(indicator);
        initial_particle_speed = priv_indicator.GetComponentInChildren<ParticleSystem>().startSpeed;
        priv_indicator.SetActive(false);
    }
	
	
	void ShowInformations(float x, float y, PlanetUpdater pu) {


		labels = controler.GetComponentsInChildren<UILabel>();
		
		Pos.text = x.ToString() + "," + y.ToString();
		planet.text = pu.name.ToString();
		pops = controler.GetComponentsInChildren<UIPopupList>();
		UIPopupList p = pops.Get(0);
		
		
		//creation de la fenetre dynamic
        p.items.Clear();
        foreach (var t in pu.materials)
        {
            if (selectedMat == null || pu.materials[selectedMat] == null)
                selectedMat = t.Key;
            p.items.Add(t.Key);
        }
        p.selection = selectedMat;

        Texture2D texture = pu.materials[selectedMat];

        Color c = ((Texture2D)texture).GetPixel((int)x, (int)y);
        //print("materiel selectionne : " + c.r + " " + c.g + " " + c.b);
        materiel.text = selectedMat + " : " + ((int)(((c.r + c.g + c.b) / 3.0F * 100.0F))).ToString() + 'p';
        //OnSelectionChange(selectedMat);
        //foreach (var t in pu.materials)
        //{
        //    p.selection = t.Key;
        //    Color c = ((Texture2D)t.Value).GetPixel ((int)x, (int)y);
        //    print("materiel selectionne : " + c.r + " " + c.g + " " + c.b);
        //    materiel.text = t.Key + " : " + ((int)(((c.r  + c.g  + c.b ) / 3.0F * 100.0F))).ToString() + 'p';
        //    return;
        //}
		
	}
    
    string selectedMat;

	void OnSelectionChange (string val)
	{
        selectedMat = val;
        
		foreach (var t in pu.materials)
		{
	        
            if (val == t.Key)
			{
				Color c = ((Texture2D)t.Value).GetPixel (x, y);
                print("materiel selectionne : " + c.r + " " + c.g + " " + c.b);
                materiel.text = t.Key + " : " + ((int)(((c.r + c.g + c.b) / 3.0F) * 100.0F)).ToString() + 'p';
				return;
			}
		}
	
	}

	// Update is called once per frame
	void Update () {

		if (Input.GetKeyDown(KeyCode.Escape))
		{
			if (menuInGame.GetComponent<UIPanel>().alpha == 0)
			{
				menuInGame.GetComponent<UIPanel>().alpha = 1;
				menuInGame.SetActive(true);
			}
			else
			{
				menuInGame.GetComponent<UIPanel>().alpha = 0;
			}
		}
		if (Input.GetButton("Fire1")) {
			Ray ray = Camera.main.ScreenPointToRay (Input.mousePosition);
			RaycastHit hit;
			
            //// TODO: singletooon !
            GameObject manager = GameObject.Find ("Manager");
			SystemLoader sys = manager.GetComponent<SystemLoader>();
            if (!sys || !sys.hasLoaded)
            {
                print("planet not leaded yet");
                return;
            }
            if (controler.activeInHierarchy)
            {
                foreach (GameObject p in sys.planets)
				{
                    Collider planetCollider = p.collider;
				    if (planetCollider != null && planetCollider.Raycast (ray, out hit, 1000.0f)) {
					    {
						    //Debug.DrawLine (ray.origin, hit.point);
						    //print ("hit! ");
						    Vector2 textureCoord = hit.textureCoord;
						    pu = p.GetComponent<PlanetUpdater>();
						    textureCoord.x *= pu.materials["rock"].width;
						    textureCoord.y *= pu.materials["rock"].height;
						    //print(hit.textureCoord);
						    x = (int)textureCoord.x;
						    y = (int)textureCoord.y;
                            //print("pixel rock : " + pu.materials["rock"].GetPixel(x, y));
                            //print("pixel water : " + pu.materials["water"].GetPixel(x, y));
                            if (controler.activeInHierarchy)
                            {
                                ShowInformations(x, y, pu);

                                // update the local indicator
                                priv_indicator.SetActive(true);
                                
                                priv_indicator.transform.parent = pu.gameObject.transform;
                                priv_indicator.transform.localPosition = Vector3.zero;
                                priv_indicator.transform.localRotation = Quaternion.Euler(Vector3.zero); 
                                priv_indicator.transform.localScale = new Vector3(1, 1, 1);
                                // average of each scales (x and y and z)

                                
                                priv_indicator.GetComponentInChildren<ParticleSystem>().startSpeed = initial_particle_speed * priv_indicator.transform.parent.localScale.x;
                                print(hit.normal);
                                Quaternion quatHit = Quaternion.FromToRotation(Vector3.up, hit.point - pu.transform.position);
                     
                                print("quatHit: " + quatHit);

                                priv_indicator.transform.rotation = quatHit;
                                print("rotation: " + priv_indicator.transform.rotation);

                            }
					    }
                    }
				}
			}
		}	
	}
}

