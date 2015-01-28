using UnityEngine;
using System.Collections;

public class guitest2: MonoBehaviour {

    //Booleans/counters for buttons
    bool notesbool = false;
    int notebuttoncount = 0;
    bool inventorybool = false;
    int inventorypushcount = 0;
    bool mapbool = false;
    int mappushcount = 0;
    bool promotionbool = false;
    int promotionpushcount = 0;
    bool contactsbool = false;
    int contactspushcount = 0;

    bool menubar_out =false;
    int menubarpushcount = 0;
    
    //Misc. Variables
    public Texture2D icon;

    public GUIStyle inventoryButton;
    public GUIStyle mapButton;
    public GUIStyle noteButton;
    public GUIStyle promotionButton;
    

    //public GUIStyle 
    public GUIStyle xbutton;
    public GUIStyle customButton2;
    public GUIStyle inventory;
    public GUIStyle playerFace;
    public GUIStyle buttonBG;
    public GUIStyle map;
    public GUIStyle promotionMap;
    //public GUIStyle mapBG;
    private string textAreaString = "Write notes here!";

    void Update()
    {
        //Note pad button click ****************************************************************************************************
        if (Input.GetKeyDown(KeyCode.N))
        {
            Debug.Log ("received character N");
            notesbool = true;
            notebuttoncount += 1;
            if (notebuttoncount % 2 == 0)
            {
                notesbool = false;
            }
        }
        //******************************************************************************************************************************
        //Inventory Button Click********************************************************************************************************
        if (Input.GetKeyDown(KeyCode.I))
        {
            Debug.Log ("received character I");
            inventorybool = true;
            inventorypushcount += 1;
            if (inventorypushcount % 2 == 0)
            {
                inventorybool = false;
            }
        }

        //map
        if (Input.GetKeyDown(KeyCode.M))
        {
            Debug.Log ("received character M");
            mapbool = true;
            mappushcount += 1;
            if (mappushcount % 2 == 0)
            {
                mapbool = false;
            }
        }
        // Kill menu bar
        if (Input.GetKeyDown(KeyCode.K)){

            Debug.Log ("received K, kill the menubar");
            menubar_out = true;
            menubarpushcount +=1;
            if (menubarpushcount % 2 == 0) {
                menubar_out = false;
            }
        }

        
        //Contacts Button Click*****************************************************************************************************
        if (Input.GetKeyDown(KeyCode.T))
        {
            contactsbool = true;
            contactspushcount += 1;
            if (contactspushcount % 2 == 0)
            {
                contactsbool = false;
            }
        }
    }
    
    void OnGUI()
    {
        //GUI.Box (new Rect (0, 0, Screen.width, Screen.height), "", buttonBG);

        //Buttons displayed on the left side.*********************************************************************************************************

        //When mouse hover to the left side of the screen, the menu bar come out
        

        if(GUI.Button (new Rect (0, 0, 50,Screen.height), "menu", buttonBG)){

           
            menubar_out = true;
            menubarpushcount +=1;
            if (menubarpushcount % 2 == 0) {
                menubar_out = false;
            }
        }

        if(menubar_out){
            //Inventory button implementation
            //if (GUI.Button (new Rect (10, 1*Screen.height/7, Screen.width/7,Screen.height/7), "Inventory", inventoryButton)) {
            if(GUI.Button (new Rect (10, 1*Screen.height/7, Screen.width/14,Screen.height/11), "", inventoryButton)) {
                inventorybool = true;
                inventorypushcount += 1;
                if (inventorypushcount % 2 == 0) {
                    inventorybool = false;
                }
                
            }
            if (inventorybool == true) {
                GUI.Box (new Rect (Screen.width / 2 - 300, Screen.height / 2 - 250, 600, 500), "", inventory);
                //If statement that implements 'X' button for inventory
                if (GUI.Button (new Rect(950, 1*Screen.height / 7 - 60, Screen.width/20, Screen.height/11), "", xbutton)) {
                    inventorybool = false;
                    inventorypushcount = 2;
                }
            }
            
            //End of inventory button implementation********************************************************************************
            
            
            
            //Promotion Implementation
            if (GUI.Button (new Rect (10, 2*Screen.height/7, Screen.width/14,Screen.height/11), "", promotionButton)) {
                promotionbool = true;
                promotionpushcount += 1;
                if (promotionpushcount % 2 == 0) {
                    promotionbool = false;
                }
            }

            if (promotionbool == true) {
                GUI.Box (new Rect (Screen.width / 2 - 300, Screen.height / 2 - 250, 600, 500), "Promotion", promotionMap);
                // 'X' button implementation for promotion tree window
                if (GUI.Button (new Rect(950, 1*Screen.height / 7 - 60, Screen.width/20, Screen.height/11), "", xbutton)) {
                    promotionbool = false;
                    promotionpushcount = 2;
                }
            }

            //Map button implementation

            //End of map button implementation*************************************************************************************
            if (GUI.Button (new Rect (10, 3*Screen.height/7, Screen.width/14,Screen.height/11), "", mapButton)){
                mapbool = true;
                mappushcount += 1;
                if (mappushcount % 2 == 0) {
                    mapbool = false;
                }

            }

            if (mapbool == true) {
                //GUI.Box (new Rect (Screen.width / 2 - 325, Screen.height / 2 - 230, 650, 450), "", mapBG);
                GUI.Box (new Rect (Screen.width / 2 - 300, Screen.height / 2 - 200, 600, 400), "", map);
                // 'X' button implementation for map window
                if (GUI.Button (new Rect(950, 1*Screen.height / 7 - 60, Screen.width/20, Screen.height/11), "", xbutton)) {
                    mapbool = false;
                    mappushcount = 2;
                }
                
            }
            
            //Notepad button implementation 
            if (GUI.Button (new Rect (10, 4*Screen.height/7, Screen.width/14,Screen.height/11), "", noteButton)) {
                notesbool = true;
                notebuttoncount += 1;
                if (notebuttoncount % 2 == 0) {
                    notesbool = false;
                }
            }
            if (notesbool == true) {
                textAreaString = GUI.TextArea (new Rect (Screen.width / 2 - 300, Screen.height / 2 - 250, 600, 500), textAreaString);
                if (GUI.Button (new Rect(950, 1*Screen.height / 7 - 60, Screen.width/20, Screen.height/11), "", xbutton)) {
                    notesbool = false;
                    notebuttoncount = 2;
                }
            }
            //End of Notepad button implementation***************************************************************************************
            
            //GUI.Button(new Rect(20, 210, 80, 50), "Contacts", customButton);
            //GUI.Button(new Rect(20, 260, 80, 50), "Available \npositions", customButton);

        }
        //GUI.Box(new Rect(Screen.width - 200, Screen.height - 200, 200, 200), "", customButton2);
        //Avatar's face
        //GUI.Box(new Rect(Screen.width - 350, Screen.height - 300, 490, 450), "", playerFace);



    }
}   
