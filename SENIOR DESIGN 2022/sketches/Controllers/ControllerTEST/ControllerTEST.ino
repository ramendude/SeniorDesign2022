
//Controller TrueOpenVR

#define GRIP_BTN  0x0001
#define A_BTN   0x0004
#define B_BTN   0x0008
#define MENU_BTN  0x0010
#define SYS_BTN   0x0020

#define THUMB_BTN 0x0030

//Digital pins number 
const byte TriggerBtnPin = 3;
const byte GripBtnPin = 4;
const byte ThumbStickBtnPin = 5;
const byte MenuBtnPin = 6;
const byte SystemBtnPin = 7;


// JOY STICK
const int VRx = A0;
const int VRy = A1;
const int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;



float ctrl[12];

void setup() {
  //Setup pins
  pinMode(TriggerBtnPin, INPUT_PULLUP);
  pinMode(GripBtnPin, INPUT_PULLUP);
  pinMode(SystemBtnPin, INPUT_PULLUP);
  pinMode(MenuBtnPin, INPUT_PULLUP);

  //JOY STICK
  pinMode(VRx,INPUT);
  pinMode(VRy,INPUT);
  pinMode(SW, INPUT_PULLUP);



  Serial.begin(115200);
}

void loop() {
  //Position with bones rotation (two gyroscope, read more https://github.com/TrueOpenVR/TrueOpenVR-DIY)
  ctrl[0] = 0; ////x -0.1
  ctrl[1] = 0;  //y -0.3
  ctrl[2] = 0; //y -0.1
  //If X,Y,Z positions are zeros, then the position is calculated based on IMUs
  

  //Rotation controller - MPU 6050
  ctrl[3] = 0; //yaw
  ctrl[4] = 0; //pitch
  ctrl[5] = 0; //roll

  //Position shoulder
  ctrl[6] = 0; //yaw
  ctrl[7] = 0; //pitch

  //Buttons
  ctrl[8] = 0; //Buttons
  ctrl[9] = 0; //Trigger
  ctrl[10] = 0; //ThumbX
  ctrl[11] = 0; //ThumbY

  //Checking press buttons 
  int CtrlButtons = 0;
  if (digitalRead(GripBtnPin) == LOW)
  CtrlButtons |= GRIP_BTN;

  if (digitalRead(ThumbStickBtnPin) == LOW)
  CtrlButtons |= THUMB_BTN; 

  if (digitalRead(MenuBtnPin) == LOW)
  CtrlButtons |= MENU_BTN;

  if (digitalRead(SystemBtnPin) == LOW)
  CtrlButtons |= SYS_BTN;

  ctrl[8] = CtrlButtons;

  //Trigger
  if (digitalRead(TriggerBtnPin) == LOW)
  ctrl[9] = 1;

  //JOY STICK
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = !digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);


  

  //Output binary
//  Serial.write((byte*)&ctrl, sizeof(ctrl));
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button : ");
  Serial.println(SW_state);

  //delay(20);
}
