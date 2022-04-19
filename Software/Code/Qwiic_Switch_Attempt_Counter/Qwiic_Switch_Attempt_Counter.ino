/******************************************************************************
  Title: Qwiic Switch Attempt Counter
  File: Qwiic_Switch_Attempt_Counter.ino
  Created: April 16, 2022
  https://github.com/milador/Qwiic-Switch-Attempt-Counter

******************************************************************************/

#include <Wire.h>
#include "SparkFun_TCA9534.h"
#include"TFT_eSPI.h"
#include"Free_Fonts.h" 

TFT_eSPI tft;

TCA9534 inputModule;            //Input
TCA9534 outputModule;           //Output 


#define INPUT_ADDR               0x27
#define OUTPUT_ADDR              0x26

#define NUM_SWITCH 2            //Switch A and B
#define UPDATE_SWITCH_RATE 100  //100ms
#define NUM_SESSION 254
#define NUM_LIST_ITEM 4         //Display how many sessions in main page list

bool inputPinMode[NUM_SWITCH] = {GPIO_IN, GPIO_IN};
bool outputPinMode[NUM_SWITCH] = {GPIO_OUT, GPIO_OUT};

String switchConnectionMessage = "";        //Qwiic modules connection state message 

bool switchStatus[NUM_SWITCH];              //Switch A and B status

//Session data struct
typedef struct {
  String sessionTitle;
  unsigned long sessionCountA;
  unsigned long sessionCountB;
} sessionType;

//Menu struct
typedef struct {
  String menuButtonATitle;
  String menuButtonBTitle;
  String menuButtonCTitle;
} menuType;

const menuType menuProperty[] {                         //C, B , A
    {"", "", ""},                                       //Intro
    {"Conf", "Save", "Enter"},                          //Main
    {"Back", "Reset", "Edit"},                          //Session
    {"Cancel", "", "Save"},                             //Config
    {"Cancel", "", "Save"}                              //Edit Session
};

sessionType sessionAttempt[NUM_SESSION];                //Array of sessions 

unsigned long sessionNumber = 0;                        //Current session number

int pageNumber = 0;                                     //Current app page number

int listItemNumber = 0;                                 //Current main page item number 

int listPageNumber = 0;                                 //Current main page item page number 

void setup() {
  
  Serial.begin(115200);

  tft.begin();

  initData();                                 //Initialize data

  showIntro();                                //Show intro page

  Wire.begin();
  
  showMain();                                 //Show main page
  
  while (1) { //Both input and output modules are successfully detected 
    if (inputModule.begin(Wire,INPUT_ADDR) == true && outputModule.begin(Wire,OUTPUT_ADDR) == true ) {
      switchConnectionMessage = "Success: Qwiic Modules are detected";
      Serial.println(switchConnectionMessage);
      showConnection();
      break;
    } else {
      switchConnectionMessage = "Error: Qwiic Modules are not detected";
      Serial.println(switchConnectionMessage);
      showConnection();
      delay(3000);
    }
  }
  inputModule.pinMode(inputPinMode);
  outputModule.pinMode(outputPinMode);

  pinMode(WIO_KEY_A, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
}


/*** Show Intro Page***/
void showIntro() {

  pageNumber = 0;                                  //Set intro page number 

  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);                       //Black background

  tft.setTextColor(TFT_WHITE, TFT_BLACK); 

  tft.setFreeFont(FF24);                           
  tft.drawString("Milador.ca", 50, 110);

  tft.setFreeFont(FF18);           
  tft.drawString("Qwiic Switch Attempt Counter", 0, 160);

  delay(4000);
}


/*** Show Main Page***/
void showMain() {

  pageNumber = 1;
  
  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);                      //Black background

  showMenu();

  listItemNumber = sessionNumber % NUM_LIST_ITEM;
  listPageNumber = (int)(sessionNumber / NUM_LIST_ITEM);

  String listItemTitle = "";

  tft.drawRect(2, 35, 50, 160, TFT_WHITE); 

 for (uint8_t itemIndex = 0; itemIndex < NUM_LIST_ITEM; itemIndex++) {
  
  if(listItemNumber==itemIndex){
    
    tft.drawRect(56, 35+(itemIndex*40), 262, 40, TFT_RED);
    
    tft.fillRect(18, 45+(itemIndex*40), 20, 20, TFT_WHITE);

    listItemTitle = getItemTitle(itemIndex,listPageNumber);
    tft.setFreeFont(FF17);  
    tft.setTextColor(TFT_RED, TFT_BLACK);                       
    tft.drawString(listItemTitle, 70, 50+(itemIndex*40));
    
  } else {
    
    tft.drawRect(56, 35+(itemIndex*40), 262, 40, TFT_BLUE);   

    listItemTitle = getItemTitle(itemIndex,listPageNumber);
    tft.setFreeFont(FF17);  
    tft.setTextColor(TFT_WHITE, TFT_BLACK);                       
    tft.drawString(listItemTitle, 70, 50+(itemIndex*40));
  }
 }
  /*

  tft.drawRect(56, 35, 262, 40, TFT_BLUE);        //Row 1

  tft.drawRect(56, 75, 262, 40, TFT_BLUE);        //Row 2

  tft.drawRect(56, 115, 262, 40, TFT_BLUE);       //Row 3

  tft.drawRect(56, 155, 262, 40, TFT_BLUE);       //Row 4
  */
  
}

/*** Show Session Page***/
void showSession(){
  pageNumber = 2;
  
  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);                      //Black background

  showMenu();

  tft.drawRect(2, 35, 316, 55, TFT_WHITE);        //Session title
  tft.setFreeFont(FF17);   
  tft.setTextColor(TFT_WHITE, TFT_BLACK);                       
  tft.drawString("Title: ", 20, 55);
  tft.drawString(sessionAttempt[sessionNumber].sessionTitle, 70, 55);
  

  tft.drawRect(2, 95, 316, 70, TFT_RED); 
  tft.setFreeFont(FF18);                        //Session switch A attempt count
  tft.setTextColor(TFT_RED, TFT_BLACK); 
  tft.drawString("SW A:", 20, 120);
  tft.setTextColor(TFT_WHITE, TFT_BLACK); 
  tft.drawString((String)sessionAttempt[sessionNumber].sessionCountA, 100, 120);
      
  tft.drawRect(2, 170, 316, 70, TFT_RED);       //Session switch B attempt count
  tft.setFreeFont(FF18);       
  tft.setTextColor(TFT_RED, TFT_BLACK); 
  tft.drawString("SW B:", 20, 200);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);                  
  tft.drawString((String)sessionAttempt[sessionNumber].sessionCountB, 100, 200);

  
}

/*** Show Top Menu***/
void showMenu() {

  String buttonATitle = menuProperty[pageNumber].menuButtonATitle;
  String buttonBTitle = menuProperty[pageNumber].menuButtonBTitle;
  String buttonCTitle = menuProperty[pageNumber].menuButtonCTitle;

  tft.setTextColor(TFT_WHITE, TFT_BLACK);  

  tft.drawRect(146, 0, 70, 30, TFT_BLUE);         //Button A 
  tft.setFreeFont(FF17);                        
  tft.drawString(buttonCTitle, 160, 6);

  tft.drawRect(74, 0, 70, 30, TFT_BLUE);          //Button B
  tft.setFreeFont(FF17);                      
  tft.drawString(buttonBTitle, 89, 6);


  tft.drawRect(2, 0, 70, 30, TFT_BLUE);           //Button C
  tft.setFreeFont(FF17);                        
  tft.drawString(buttonATitle, 17, 6);
}

/*** Show Qwiic modules connection state***/
void showConnection() {
  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawRect(0,200,320,40,TFT_BLUE); 
  tft.setFreeFont(FF17);                           // Select the font
  tft.drawString(switchConnectionMessage, 10, 210);// Display connection state
  
}

/*** Initialize Session Data***/
void initData() {
  for (uint8_t sessionIndex = 0; sessionIndex < NUM_SESSION; sessionIndex++) {
    sessionAttempt[sessionIndex].sessionTitle = "Session #"+(String)(sessionIndex+1);
    sessionAttempt[sessionIndex].sessionCountA = 0;
    sessionAttempt[sessionIndex].sessionCountB = 0;
  }
}

/*** Initialize Session Data***/
void resetSessionData(int sessionIndex) {
  sessionAttempt[sessionIndex].sessionTitle = "Session #"+(String)(sessionIndex+1);
  sessionAttempt[sessionIndex].sessionCountA = 0;
  sessionAttempt[sessionIndex].sessionCountB = 0;
}


/***Get the Session title to display in the menu list***/
String getItemTitle(int itemIndex, int itemPageIndex){
  String itemTitle = sessionAttempt[itemIndex+itemPageIndex*NUM_LIST_ITEM].sessionTitle 
  + " , "
  + (String)sessionAttempt[itemIndex+itemPageIndex*NUM_LIST_ITEM].sessionCountA
  + " , "
  + (String)sessionAttempt[itemIndex+itemPageIndex*NUM_LIST_ITEM].sessionCountB;

  return itemTitle;
}

/***Decrease session number***/
void decreaseSessionNumber() {
  if(sessionNumber>0){
    --sessionNumber;
  }
}

/***Increase session number***/
void increaseSessionNumber() {
  if(sessionNumber<NUM_SESSION){
    ++sessionNumber;
  }  
}

/***Main Loop***/
void loop() {
  //Perform input action based on page number 
  switch (pageNumber) {
    case 0:
      introLoop();
      break;
    case 1:
      mainLoop();
      break;
    case 2:
      sessionLoop();
      break;
    default:
      // statements
      break;
  }

  delay(UPDATE_SWITCH_RATE);
}

/***Intro Page Loop***/
void introLoop() {

}

/***Main Page Loop***/
void mainLoop() {

  //Enter or start session 
  if (digitalRead(WIO_KEY_A) == LOW) {
    showSession();    
  } //Save data in SD Card
  else if (digitalRead(WIO_KEY_B) == LOW) {
    
  } // Show configuration 
  else if (digitalRead(WIO_KEY_C) == LOW) {

  }
  //Highlight previous session 
  if (digitalRead(WIO_5S_UP) == LOW) {
    decreaseSessionNumber();
    showMain();  
    showConnection();
  } //Highlight next session 
  else if (digitalRead(WIO_5S_DOWN) == LOW) {
    increaseSessionNumber();
    showMain();  
    showConnection();
  } //Enter or start session 
  else if (digitalRead(WIO_5S_PRESS) == LOW) {
    showSession();
  }


  switchStatus[0] = !inputModule.digitalRead(0);
  outputModule.digitalWrite(0, switchStatus[0]);
  switchStatus[1] = !inputModule.digitalRead(1);
  outputModule.digitalWrite(1, switchStatus[1]);
  
//  for (uint8_t arrayPosition = 0; arrayPosition < NUM_SWITCH; arrayPosition++) {
//    switchStatus[arrayPosition] = !inputModule.digitalRead(arrayPosition);
//    outputModule.digitalWrite(arrayPosition, switchStatus[arrayPosition]);
//  }
}

/***Session Page Loop***/
void sessionLoop() {
  //Edit session 
  if (digitalRead(WIO_KEY_A) == LOW) {
  
  } //Reset session data
  else if (digitalRead(WIO_KEY_B) == LOW) {
    resetSessionData(sessionNumber);
    showSession();
  } //Back to main page
  else if (digitalRead(WIO_KEY_C) == LOW) {
    showMain();  
    showConnection();
  }

  //Switch A input and output 
  switchStatus[0] = !inputModule.digitalRead(0);
  outputModule.digitalWrite(0, switchStatus[0]);

  //Switch B input and output 
  switchStatus[1] = !inputModule.digitalRead(1);
  outputModule.digitalWrite(1, switchStatus[1]);
  
  if(switchStatus[0]) { //Increment switch A count
    ++sessionAttempt[sessionNumber].sessionCountA;
    showSession();
  };
  if(switchStatus[1]) { //Increment switch B count
    ++sessionAttempt[sessionNumber].sessionCountB;
    showSession();
  };
}
