using UnityEngine;
using System.Collections;

/*Controls the speed of the waves that spawn*/

public class Mover : MonoBehaviour {

	public float speed;

	void Start () {
		rigidbody.velocity = transform.up * speed;
	}

}
