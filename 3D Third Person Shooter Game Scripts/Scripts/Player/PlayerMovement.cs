using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    public float speed = 6f;
    Vector3 movement;
    Animator anim;
    Rigidbody playerRigidbody;
    int floorMask;
    float camRayLength = 100f;

    //Function that initializes things
    void Awake()
    {
    	floorMask = LayerMask.GetMask("Floor");
    	anim = GetComponent<Animator> ();
    	playerRigidbody = GetComponent<Rigidbody> ();
    }

    //Function to call and update the player movement.
    void FixedUpdate() {
    	float h = Input.GetAxisRaw ("Horizontal");
    	float v = Input.GetAxisRaw ("Vertical");

    	Move(h, v);
    	Turning();
    	Animating(h, v);

    }

    //Function that takes care of basic player movement and rigidbody movement
    void Move(float h, float v) {
    	movement.Set (h, 0f, v);

    	movement = movement.normalized * speed * Time.deltaTime; 
    																

    	playerRigidbody.MovePosition (transform.position + movement); 
    }

    /*Function takes care of turning and makes it so the character will look
    wherever the mouse is pointing*/
    void Turning() {
    	Ray camRay = Camera.main.ScreenPointToRay(Input.mousePosition);
    	RaycastHit floorHit;
    	if (Physics.Raycast (camRay, out floorHit, camRayLength, floorMask)) {
    		Vector3 playerToMouse = floorHit.point - transform.position;
    		playerToMouse.y = 0f;

    		Quaternion newRotation = Quaternion.LookRotation (playerToMouse);
    		playerRigidbody.MoveRotation (newRotation);
    	}
    }

    /*This function updates the "IsWalking" boolean based on whether or not
    the player is actually moving. Takes care of setting off the animation.*/
    void Animating(float h, float v) {
    	bool walking = h != 0f || v != 0f;
    	anim.SetBool ("IsWalking", walking);

    }
}
