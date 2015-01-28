using UnityEngine;
using System.Collections;


/*A very CRAPPY game AI that will make game objects follow the main player*/

public class FollowAI : MonoBehaviour {

	Transform Leader;
	public float AISpeed;
	public float MaxDistance;
	public float MinDistance;

	// Use this for initialization
	void Start () {
		
		Leader = GameObject.FindGameObjectWithTag("Player").transform;
	
	}
	
	// Update is called once per frame
	void Update () {

		AI();
	
	}

	void AI() {
		if (Vector3.Distance(transform.position, Leader.position) >= MinDistance) {
			transform.position = Vector3.MoveTowards(transform.position, Leader.position, AISpeed * Time.deltaTime);
		}
	}
}
