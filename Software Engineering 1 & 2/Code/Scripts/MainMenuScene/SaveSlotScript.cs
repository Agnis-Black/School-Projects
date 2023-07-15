using System;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using System.Xml.Serialization;
using UnityEngine.SceneManagement;
using TMPro;

public class SaveSlotScript : MonoBehaviour{
    public GameObject slots;
    public MainMenu mainManuScript;
    public GameObject mainMenuGui;

    String xmlPath = Application.streamingAssetsPath + "/XML/";

    [Serializable, XmlRoot("StreamingData")]
    public struct PlayerData{
        public bool completedTutorial;
    }

    void Start(){
        for(int i = 0; i < slots.transform.childCount; i++){

            int slotNum = i;
            String fileName = xmlPath + "/Slot"+(slotNum+1)+".xml";

            Button slotBtn = slots.transform.GetChild(i).gameObject.GetComponent<Button>();
            slotBtn.onClick.AddListener(()=>onSaveSlotClicked(slotBtn, slotNum));
            TextMeshProUGUI fileButtonText = slotBtn.gameObject.transform.Find("Text").GetComponent<TextMeshProUGUI>(); 

            if(!File.Exists(fileName)){
                fileButtonText.text = "Empty File";
            }
            else{
                fileButtonText.text = "Save File " + (i+1);
                PlayerData data = loadData(fileName);
            }
        }
    }

    PlayerData getDefaultPlayerData(){
        PlayerData playerData = new PlayerData();
        playerData.completedTutorial = false;

        return playerData;
    }

    void createNewSave(String fileName){
        if(File.Exists(fileName)){
            Debug.Log("Overwrote existing save");
        } 

        PlayerData playerData = getDefaultPlayerData();

        // Create new file
        var newSave = File.Create(fileName);
        newSave.Close();

        // save new data to file 
        saveData(playerData, fileName);
    }

    void onSaveSlotClicked(Button slotBtn, int slotNumber){
        String fileName = xmlPath + "/Slot"+(slotNumber+1)+".xml";

        // Clicked the save slot in the 'new game' second, 
        if(mainManuScript.startingNewGame){
            createNewSave(fileName);
            SceneManager.LoadScene("Tutorial", LoadSceneMode.Single);
        } 

        // Clicked save slot in 'load game' section:
        else {
            // if the file exists load the save
            if(File.Exists(fileName)){
                // loads the players data:
                PlayerData data = loadData(fileName);
                // TODO: do something with the data here  

                // TODO: load whatever scene the player is in
                SceneManager.LoadScene("MainMap", LoadSceneMode.Single);
            } 
            // otherwise, ignore the attempt
            else {
                Debug.Log("No save on file for path:'" + fileName + "' Ignoring attempt");
            }
        }
    }

     void onBackButtonClicked(){
       mainMenuGui.SetActive(true);
       gameObject.SetActive(false);
    }

    public void saveData(PlayerData data, String fileName){
        if(!(File.Exists(fileName))){ 
            Debug.Log("File does not exist for " + fileName);
            return; 
        };

        XmlSerializer serializer = new XmlSerializer(typeof(PlayerData));

        using (FileStream stream = new FileStream(fileName, FileMode.Create)){
            serializer.Serialize(stream, data);
        }
    }

    public PlayerData loadData(String fileName){
        XmlSerializer serializer = new XmlSerializer(typeof(PlayerData));
        PlayerData data;

        using (FileStream stream = new FileStream(fileName, FileMode.Open)){
            data = (PlayerData) serializer.Deserialize(stream);
        }

        return data;
    }
}
