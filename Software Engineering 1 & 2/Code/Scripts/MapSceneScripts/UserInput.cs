using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;
using StarterAssets;

public class UserInput : MonoBehaviour
{
    
    public FirstPersonController playerController;
    public GameObject inventoryGui;
    
    // Start is called before the first frame update
    void Start()
    {
        // print(fpScript.inputEnabled);
       // print(fpScript.inputEnabled);
        // GameObject.Find("PlayerCapsule").GetComponent<FirstPersonController>().enabled = false;
    }
 
    bool isOpen = false;
    // Update is called once per frame
    void Update()
    {
        var keyboard = Keyboard.current;
        if (keyboard == null)
            return;

        if (keyboard.escapeKey.wasPressedThisFrame){
            SceneManager.LoadScene("MainMenuScene", LoadSceneMode.Single);
        }
        
        if (keyboard.qKey.wasPressedThisFrame){
            if(isOpen){
                playerController.enabled = true;
                inventoryGui.SetActive(false);
                Cursor.visible = false;
                Cursor.lockState = CursorLockMode.Locked;
                isOpen = false;       
            }
            else{
                playerController.enabled = false;
                inventoryGui.SetActive(true);
                Cursor.visible = true;
                Cursor.lockState = CursorLockMode.None;
                isOpen = true;
            }

        }

    }
}
