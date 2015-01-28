using UnityEngine;
using System.Collections;

//This code makes it so the scene displays/ increments the score based on time and amount of kills.

public class KeepingScore : MonoBehaviour {

	public static int Score = 0;
	double timer = 0.0;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {

		timer += Time.deltaTime;
		Score += (int)timer;
	
	}

	void OnGUI() {
		GUI.Box (new Rect(50,50,100,50), Score.ToString());
	}
}
