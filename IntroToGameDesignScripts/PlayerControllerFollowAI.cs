using UnityEngine;
using System.Collections;

[System.Serializable]
//Class that sets the boundaries for which the player can exist.
public class Boundary7
{
    public float xMin, xMax, yMin, yMax;
}

public class PlayerControllerFollowAI : MonoBehaviour
{
	//Public Variables used for player control
    public float speed;
    public float tilt;
    public Boundary7 boundary;



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

