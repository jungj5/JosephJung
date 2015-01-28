using UnityEngine;
using System.Collections;

/*This code takes care of enemy interaction with other game objects, 
causing in different results based what game object was contacted*/

public class DestroyByContact : MonoBehaviour {

	void OnTriggerEnter(Collider other) {
		if (other.tag == "Boundary") {
			return;
		}
		if (other.tag == "Bullet") {
			KeepingScore.Score += 100;
		}

		if (other.tag == "Player") {
			Debug.Log("Player Died");
			Application.LoadLevel ("GameOver"); 
		}
		if (other.tag == "Civilian") {
			Debug.Log("Civilian Died");
			Application.LoadLevel("GameOver");
		}
		Destroy(other.gameObject);
		Destroy(gameObject);
	}
}
