#include <SoftwareSerial.h>
#include <Stepper.h>


const int speedRPM=10;  // 10 RPM
const int STEPS_PER_CIRCLE=2048;  // steps per circle
const int pnVrx=A0;
const int pnVry=A2;
const int pnSw=A4;  //Switch Pin

const int deltaWidth=72;   // X 方向，感測靈敏度 
const int deltaHeight=72;  // Y 方向，感測靈敏度, Height precision 


int Direction=0;  // 方向控制
  // 0  : 停止
  // +1 : 正值轉圈
  // -1 : 負值轉圈

Stepper stepper(STEPS_PER_CIRCLE, 11, 9, 10, 8); //28BY-48(STEPS, IN1, IN2, IN3, IN4)

void setup() {

  Serial.begin(9600);
  stepper.setSpeed(speedRPM);

  pinMode(pnVrx, INPUT);
  pinMode(pnVry, INPUT);
  pinMode(pnSw, INPUT);
  
}

//---------------------------------------------
int  CircleToStep( const float& Circle )  // circles to steps 
{
  return int( Circle*STEPS_PER_CIRCLE );
}

//-----------------------
void loop() {

  int x=analogRead(pnVrx);
  int y=analogRead(pnVry);
  int b=digitalRead(pnSw);  //button
  
  
  /*
  Serial.println(
    String("x=")+String(x)+String(",")+
    String("y=")+String(y)+String(",")+
    String("button=")+String(b)    );
  delay(200);  
  */
   
  //Position(X,Y): Left(0,512), Middle(512,512), Right(1023,512)
  if( x <= (0+deltaWidth) ){ // Left Position, (+) 正值方向
    Direction= +1 ;
  }
  else if( x >=(1023-deltaWidth) ){ // Right Position, (-)
    Direction= -1 ;
  }
  else if ( y <=(0+deltaHeight) || y >= (1023-deltaHeight) ){ //停止:0
    Direction = 0 ; 
  }
  else { 
    // 無改動，無做事
  }

  if( 0 != Direction ) { 
    int steps=CircleToStep( Direction*0.01 ); // 轉動:方向，乘以0.01 圈  
    stepper.step( steps );  
  }
  
}
