using UnityEngine;
using System.Collections;

[System.Serializable]
//Class that sets the boundaries for which the player can exist.
public class Boundary
{
    public float xMin, xMax, yMin, yMax;
}

public class PlayerController : MonoBehaviour
{
	//Public Variables used for player control
    public float speed;
    public float tilt;
    public Boundary boundary;

    public GameObject shot;
    public Transform shotSpawn1; 
    public Transform shotSpawn2;

    //Variables used to calculate the rate at which the player can fire projectiles
    public float fireRate;

    private float nextFire;

    void Update() {
    	
    	//"Fire1" will be whenever the player pushes the spacebar.

    	/*If the player pushes the button AND the amount of time that has gone by
    	since the last shot is large enough, then shoot another projectile.*/

    	if (Input.GetButton("Fire1") && Time.time > nextFire) {
    		nextFire = Time.time + fireRate;
    		Instantiate (shot, shotSpawn1.position, shotSpawn1.rotation);
    		Instantiate (shot, shotSpawn2.position, shotSpawn2.rotation);
    	}
    	
    }

    void FixedUpdate ()
    {
        float moveHorizontal = Input.GetAxis ("Horizontal");
        float moveVertical = Input.GetAxis ("Vertical");

        //Player movement variable of Vector3 type
        Vector3 movement1 = new Vector3 (moveHorizontal, moveVertical, 0.0f );
        rigidbody.velocity = movement1 * speed;

        //Boundaries set for the player to move it. Player will not be able to move outside the boundaries.
        //Player will automatically spawn within the set boundaries.
        rigidbody.position = new Vector3 
        (
            Mathf.Clamp (rigidbody.position.x, boundary.xMin, boundary.xMax), 
            Mathf.Clamp (rigidbody.position.y, boundary.yMin, boundary.yMax), 
            0.0f
        );

        rigidbody.rotation = Quaternion.Euler (0.0f, 0.0f, rigidbody.velocity.x * -tilt);
    }
}

