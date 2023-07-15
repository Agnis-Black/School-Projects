using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainMenu : MonoBehaviour{
  public GameObject saveSlotsContainer;
  public bool startingNewGame = false;
  
  void Start(){
  }
  public void onLoadClick(){
    saveSlotsContainer.SetActive(true);
    gameObject.SetActive(false);
    startingNewGame = false;
  }

  public void onNewGameClick(){
    saveSlotsContainer.SetActive(true);
    gameObject.SetActive(false);
    startingNewGame = true;
  }

  public void onExitClicked(){
    Application.Quit();
  }
}
