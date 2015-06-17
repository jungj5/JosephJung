using UnityEngine;
using System.Collections;



/*This code makes it so if an object were to hit the boundaries set within unity,
the object would be destroyed.*/

public class DestroyByBoundary : MonoBehaviour {

	void OnTriggerExit(Collider other) {
		Destroy(other.gameObject);
	}
	
}
