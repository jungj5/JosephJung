using UnityEngine;
using System.Collections;

/*Code for displaying the score on the game over scene*/

public class DisplayScoreGameOver : MonoBehaviour {


	void OnGUI() {
		GUI.Box (new Rect(Screen.width / 2, Screen.height / 2, 100,50), KeepingScore.Score.ToString());
	}
}
