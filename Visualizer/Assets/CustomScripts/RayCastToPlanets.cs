using UnityEngine;
using System.Collections;

public class RayCastToPlanets : MonoBehaviour {
	public GameObject controler;
    public GameObject indicator; 
    private UILabel[] labels;
	private UIPopupList[] pops;
	public UIPopupList mat;
	public UIPopupList astre;
	public int x, y;
	public PlanetUpdater pu;
	public UILabel Pos;
	public UILabel materiel;
	public UILabel planet;
	public UIPopupList res;
	public UILabel current;
	public UILabel total;
	public GameObject menuInGame;
	public UICheckbox b;
	public GameObject extractOK; 
	public UICheckbox screen;
	public Camera cam;
	/*private Vector3 positionCamDefault;
	private Quaternion rotationCamDefault;
	private Transform transformCamDefault;
    */

    GameObject priv_indicator;
    float initial_particle_speed;
	// Use this for initialization
	void Start () {
		initRes();
        priv_indicator = (GameObject)GameObject.Instantiate(indicator);
        initial_particle_speed = priv_indicator.GetComponentInChildren<ParticleSystem>().startSpeed;
        priv_indicator.SetActive(false);
        /*
		GameObject cam = GameObject.Find("Main Camera");
		positionCamDefault = cam.transform.position;
		rotationCamDefault = cam.transform.rotation;
		transformCamDefault = GameObject.Find ("Main Camera").transform.parent;
*/    }
	
	
	void ShowInformations(float x, float y, PlanetUpdater pu) {


		labels = controler.GetComponentsInChildren<UILabel>();
		
		Pos.text = x.ToString() + "," + y.ToString();
		planet.text = pu.name.ToString();
				
		//creation de la fenetre dynamic
		mat.items.Clear();
        foreach (var t in pu.materials)
        {
            if (selectedMat == null || pu.materials[selectedMat] == null)
                selectedMat = t.Key;
			mat.items.Add(t.Key);
        }
		mat.selection = selectedMat;

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

	void initPlanetList()
	{
		if (astre.items.Count != 0)
			return;
		GameObject manager = GameObject.Find ("Manager");
		SystemLoader sys = manager.GetComponent<SystemLoader>();
		foreach (GameObject p in sys.planets)
		{
			astre.items.Add(p.name);
		}

	}

	void initRes()
	{
		foreach (var r in Screen.resolutions)
		{
			if (r.width >= 1024)
				res.items.Add(r.width+" x "+r.height);
		}
	}

	void OnActivate()
	{
		astre.selection = "Choose";
		//GameObject cam = GameObject.Find("Main Camera");
		//GameObject.Find("Main Camera").transform.parent = transformCamDefault;
		//cam.transform.position = positionCamDefault;
		// cam.transform.rotation = rotationCamDefault;
        setCamFree();
	}

	void OnSreenMode()
	{
		if (!screen.isChecked)
			Screen.fullScreen = !Screen.fullScreen;
	}

	void OnSelectionAstre(string val)
	{
		print("ONSELECTIONASTRE");
		GameObject manager = GameObject.Find ("Manager");
		SystemLoader sys = manager.GetComponent<SystemLoader>();
		foreach (GameObject p in sys.planets)
		{
			print(p);
			if (val == p.name)
			{
				//setCamFree();
				setCamLookAt(p);
			}
		}
		
	}

	void OnSelectionRes(string val)
    {
		foreach (Resolution r in Screen.resolutions)
		{
			if (r.width+" x "+r.height == val)
			{
				if (screen.isChecked)
					Screen.SetResolution(r.width, r.height, true);
				else
					Screen.SetResolution(r.width, r.height, false);
			}
		}

	}

	void OnVolumeChange(float val)
	{
		cam.audio.volume = val;
	}


    private GameObject planetLookedAt = null;

    public void setCamLookAt(GameObject planet)
    {
        print("setCamLookAt");
        if (planetLookedAt == planet)
            return;
        GameObject manager = GameObject.Find ("Manager");
        if (manager && manager.GetComponent<UniverseTime>())
        {
            UniverseTime time = manager.GetComponent<UniverseTime>();
            time.Stop();
        }
        print("setCamLookAt does it");
        PlanetUpdater po = planet.GetComponent<PlanetUpdater>();
        GameObject cam = GameObject.Find("Main Camera");
        //if (cam.transform.parent == po.gameObject.transform)
           // return;
//        setCamFree();

        priv_indicator.SetActive(false);
        cam.GetComponent<SGT_CameraFreeLook>().enabled = false;
        cam.GetComponent<SGT_CameraFreeOrbit>().enabled = true;
        float avgScale = (float)((planet.gameObject.transform.localScale.x + planet.gameObject.transform.localScale.y + planet.gameObject.transform.localScale.z) / 3.0);
        cam.GetComponent<SGT_CameraFreeOrbit>().Distance = (float)(avgScale + avgScale);
        print(cam.GetComponent<SGT_CameraFreeOrbit>().Distance);
        cam.GetComponent<SGT_CameraFreeOrbit>().DistanceMin = cam.GetComponent<SGT_CameraFreeOrbit>().Distance;
        cam.GetComponent<SGT_CameraFreeOrbit>().DistanceMax = cam.GetComponent<SGT_CameraFreeOrbit>().Distance;
        cam.transform.LookAt(planet.transform);
        planetLookedAt = planet;
//        cam.transform.position = cam.transform.position + (cam.transform.forward * (cam.transform.DistanceTo(planet.transform.position) - 1000));
        cam.transform.parent.transform.position = planet.transform.position;
    }

    public void setCamFree()
    {
        GameObject cam = GameObject.Find("Main Camera");
        if (cam.transform.parent != null)
        {
            //cam.transform.position = cam.transform.position + cam.transform.parent.position;
             // cam.transform.rotation.eulerAngles = Vector3(0,0,0)
            // cam.GetComponent<SGT_CameraFreeLook>().Rotation = cam.GetComponent<SGT_CameraFreeLook>().Rotation * Quaternion.Inverse(cam.transform.parent.rotation);
            //cam.transform.parent = null;
        
        }
        //Quaternion initialRot = cam.transform.rotation;
        cam.GetComponent<SGT_CameraFreeOrbit>().enabled = false;
        cam.GetComponent<SGT_CameraFreeLook>().enabled = true;
        cam.GetComponent<SGT_CameraFreeLook>().camera.transform.rotation = cam.GetComponent<SGT_CameraFreeLook>().camera.transform.rotation;
        //cam.GetComponent<SGT_CameraFreeLook>().Update();
        //cam.transform.rotation = cam.transform.rotation * initialRot;
        if (priv_indicator)
            priv_indicator.SetActive(false);
        //cam.transform.LookAt(planetLookedAt.transform);
        planetLookedAt = null;
    }

	void timer()
	{
		GameObject manager = GameObject.Find ("Manager");
        if (manager && manager.GetComponent<UniverseTime>())
        {
            total.text = manager.GetComponent<UniverseTime>().totalTime.ToString();
            current.text = ((int)(manager.GetComponent<UniverseTime>().getElapsed())).ToString();
        }
    }

	// Update is called once per frame
	void Update () {
		timer();
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

			extractOK.SetActive(false);

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

			UniverseTime w = manager.GetComponent<UniverseTime>();
		
            if (controler.activeInHierarchy)
            {
				initPlanetList();
                foreach (GameObject p in sys.planets)
				{
                    Collider planetCollider = p.collider;
				    if (planetCollider != null && planetCollider.Raycast (ray, out hit, 1000.0f)) {
					    {
						    //Debug.DrawLine (ray.origin, hit.point);
						    //print ("hit! ");
						    Vector2 textureCoord = hit.textureCoord;
						    pu = p.GetComponent<PlanetUpdater>();
                            foreach (var t in pu.materials)
                            {
                                if (selectedMat == null || pu.materials[selectedMat] == null)
                                    selectedMat = t.Key;
                            }
                            textureCoord.x *= pu.materials[selectedMat].width;
                            textureCoord.y *= pu.materials[selectedMat].height;
						    //print(hit.textureCoord);
						    x = (int)textureCoord.x;
						    y = (int)textureCoord.y;
                            //print("pixel rock : " + pu.materials["rock"].GetPixel(x, y));
                            //print("pixel water : " + pu.materials["water"].GetPixel(x, y));
                            if (controler.activeInHierarchy)
                            {
                                ShowInformations(x, y, pu);

                                // parent the camera to the object looked at
                                //setCamFree();
                                setCamLookAt(p);

                                // update the local indicator
                                priv_indicator.SetActive(true);
                                
                                priv_indicator.transform.parent = pu.gameObject.transform;
                                priv_indicator.transform.localPosition = Vector3.zero;
                                priv_indicator.transform.localRotation = Quaternion.Euler(Vector3.zero); 
                                priv_indicator.transform.localScale = new Vector3(1, 1, 1);
                                // average of each scales (x and y and z)

                                
                                priv_indicator.GetComponentInChildren<ParticleSystem>().startSpeed = initial_particle_speed * priv_indicator.transform.parent.localScale.x;
                                //print(hit.normal);
                                Quaternion quatHit = Quaternion.FromToRotation(Vector3.up, hit.point - pu.transform.position);
                     
                                //print("quatHit: " + quatHit);

                                priv_indicator.transform.rotation = quatHit;
                                //print("rotation: " + priv_indicator.transform.rotation);

                                return;
                            }
					    }
                    }
				}
			}
		}	
	}
}

