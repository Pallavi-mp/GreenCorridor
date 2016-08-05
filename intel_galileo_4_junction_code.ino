int s1[3]={5,6,7}; //initialising an array s1 with pin numbers 5,6,7.
int s2[3]={2,3,4};//initialising array s2 with pin numbers 2,3,4.
int s4[3]={8,9,10};//initialising array s3 with pin numbers 8,9,10.
int s3[3]={11,12,13};//initialising array s4 with pin numbers 11,12,13.
int val1,val2,val3,val4,c,i,f;//Declaring variables of integer type
int freq=0;//initialising variable frequency of integer type to 0. This reads the output from the frequency sensing circuit.


void interrupt1();//declaration of function interrupt1().
void interrupt2();//declaration of function interrupt2().
void interrupt3();//declaration of function interrupt3().
void interrupt4();//declaration of function interrupt4().

void setup() //all instructions given here will be executed once at the starting of the program.
{

  for(i=0;i<3;i++)//loop to initialise each pin.
  {
    pinMode(s1[i],OUTPUT);//initialising pins as OUTPUT pins.
    pinMode(s2[i],OUTPUT);
    pinMode(s3[i],OUTPUT);
    pinMode(s4[i],OUTPUT);
  } 
  Serial.begin(9600);//Setting the baud rate to 9600.
 
}

void readval()//function readval() that doesnt return any type and doesnt take any arguments. It reads analog values from the analog input pins.
{
   val1 = analogRead(A0);//variable val1 stores the analogRead value of analog input pin A0 of the intel Galileo.
   val2 = analogRead(A1);
   val3 = analogRead(A2);
   val4 = analogRead(A3);

}

int sensor()// function sensor() prints the analogRead values on the analog input pins on the serial monitor.
{
  readval();//function readval() is called.
  Serial.print("val1: ");//command to print on the serial monitor.
  Serial.println(val1);
  Serial.print("val2: ");
  Serial.println(val2);
  Serial.print("val3: ");
  Serial.println(val3);
  Serial.print("val4: ");
  Serial.println(val4);
}


void check()//function that checks for the presence of the ambulance. 
{
 if(freq>0) //if the frequency sensor gives a digital high output the following commands are executed.
 {
    sensor();//calling of function sensor().
   if((val2>val1) && (val2>val3) && (val2>val4)) //checks if analogPin A1 gives the highest output
    {
      interrupt1();//function interrupt1() is called.
    }
   if((val3>val2) && (val3>val1) && (val3>val4))//checks if analogPin A1 gives the highest output
    {
      interrupt2();//function interrupt2() is called.
    }
    if((val4>val2) && (val4>val3) && (val4>val1))//checks if analogPin A1 gives the highest output
    {
      interrupt3();//function interrupt3() is called.
    }
   if((val1>val2) && (val1>val3) && (val1>val4))//checks if analogPin A1 gives the highest output
    {
      interrupt4();//function interrupt4() is called.
    }
 }
 
} 
 
void interrupt4()
{
  while(val1>val2 && val1>val3 && val1>val4)//enclosed instructions are executed as long as val1 is the greatest among val1, val2, val3 and val4.
  {
  digitalWrite(s1[0],HIGH);//output pin 5 is made HIGH, indicating that the red light is on.
  digitalWrite(s1[1],LOW);//output pin 6 is made LOW, indicating that the yellow light is off.
  digitalWrite(s1[2],LOW);//output pin 7 is made LOW, indicating that the green light is off.
 
  digitalWrite(s2[0],HIGH);
  digitalWrite(s2[1],LOW);
  digitalWrite(s2[2],LOW);

  digitalWrite(s3[0],HIGH);
  digitalWrite(s3[1],LOW);
  digitalWrite(s3[2],LOW);
 
  digitalWrite(s4[0],LOW);
  digitalWrite(s4[1],LOW);
  digitalWrite(s4[2],HIGH);
  for(i=0, c=0; i<6; i++)//to ensure that discrepancies in the microphone do not affect the state of the signal till the ambulance has passed.
  {
  sensor();//function sensor() is called.
  
  if(val1<=val2 || val1<=val3 || val1<=val4)//checks if val1 is lesser than any of the other analog inputs.
  c++;//increments variable c;
  Serial.print("c: ");//prints c on the serial monitor.
  Serial.println(c);}
  if(c>6)//checks if c is greater than 6 
    break;//the while loop is exited.
}
}

void interrupt3()
{
 while(val4>val2 && val4>val3 && val4>val1)
  {
  digitalWrite(s1[0],HIGH);
  digitalWrite(s1[1],LOW);
  digitalWrite(s1[2],LOW);
 
  digitalWrite(s2[0],HIGH);
  digitalWrite(s2[1],LOW);
  digitalWrite(s2[2],LOW);

  digitalWrite(s3[0],LOW);
  digitalWrite(s3[1],LOW);
  digitalWrite(s3[2],HIGH);
 
  digitalWrite(s4[0],HIGH);
  digitalWrite(s4[1],LOW);
  digitalWrite(s4[2],LOW);
 for(i=0, c=0; i<6; i++)
  {
  sensor();
  
  if(val4<=val1 || val4<=val3 || val4<=val2)
  c++;
  
  Serial.print("c: ");
  Serial.println(c);}
  if(c>6)
    break;
}
}

void interrupt1()
{
  while(val2>val1 && val2>val3 && val2>val4)
  {
  digitalWrite(s1[0],LOW);
  digitalWrite(s1[1],LOW);
  digitalWrite(s1[2],HIGH);
 
  digitalWrite(s2[0],HIGH);
  digitalWrite(s2[1],LOW);
  digitalWrite(s2[2],LOW);

  digitalWrite(s3[0],HIGH);
  digitalWrite(s3[1],LOW);
  digitalWrite(s3[2],LOW);
 
  digitalWrite(s4[0],HIGH);
  digitalWrite(s4[1],LOW);
  digitalWrite(s4[2],LOW);
 for(i=0, c=0; i<6; i++)
  {
  sensor();
 
  if(val2<=val1 || val2<=val3 || val2<=val4)
  c++;
  
  Serial.print("c: ");
  Serial.println(c);
  if(c>6)
    break;
}
}

void interrupt2()
{
  while(val3>val2 && val3>val1 && val3>val4)
  {
  digitalWrite(s1[0],HIGH);
  digitalWrite(s1[1],LOW);
  digitalWrite(s1[2],LOW);
 
  digitalWrite(s2[0],LOW);
  digitalWrite(s2[1],LOW);
  digitalWrite(s2[2],HIGH);

  digitalWrite(s3[0],HIGH);
  digitalWrite(s3[1],LOW);
  digitalWrite(s3[2],LOW);
 
  digitalWrite(s4[0],HIGH);
  digitalWrite(s4[1],LOW);
  digitalWrite(s4[2],LOW);
  for(i=0, c=0; i<6; i++)
  {
  sensor();
  
  if(val3<=val2 || val3<=val1 || val3<=val4)
  c++;
  
  Serial.print("c: ");
  Serial.println(c);}
  if(c>6)
    break;
}
}

void default1()//function default() to define the regular pattern of signal lights in the absence of an EMV.
{
  check();//function check() is called.
  digitalWrite(s1[0],LOW);
  digitalWrite(s1[1],LOW);
  digitalWrite(s1[2],HIGH);
  check();
  digitalWrite(s2[0],HIGH);
  digitalWrite(s2[1],LOW);
  digitalWrite(s2[2],LOW);
  check();
  digitalWrite(s3[0],HIGH);
  digitalWrite(s3[1],LOW);
  digitalWrite(s3[2],LOW);
  check();
  digitalWrite(s4[0],HIGH);
  digitalWrite(s4[1],LOW);
  digitalWrite(s4[2],LOW);
 for(int i=0; i<5; i++)//the function check() is called once every second to keep checking for the presence of an EMV.
  {
    check();
    delay(1000);//gives a delay of 1 second in the program.
  }
  
  digitalWrite(s1[0],HIGH);
  digitalWrite(s1[1],LOW);
  digitalWrite(s1[2],LOW);
  check();
  digitalWrite(s2[0],LOW);
  digitalWrite(s2[1],HIGH);
  digitalWrite(s2[2],LOW);
  check();
  delay(1000);
  check();

  digitalWrite(s1[0],HIGH);
  digitalWrite(s1[1],LOW);
  digitalWrite(s1[2],LOW);
  check();
  digitalWrite(s2[0],LOW);
  digitalWrite(s2[1],LOW);
  digitalWrite(s2[2],HIGH);
  
  for(int i=0; i<5; i++)
  {
    check();
    delay(1000);
  }
  
  
  digitalWrite(s1[0],HIGH);
  digitalWrite(s1[1],LOW);
  digitalWrite(s1[2],LOW);
  check();
  digitalWrite(s2[0],HIGH);
  digitalWrite(s2[1],LOW);
  digitalWrite(s2[2],LOW);
  check();
  digitalWrite(s3[0],LOW);
  digitalWrite(s3[1],HIGH);
  digitalWrite(s3[2],LOW);
  check();
  delay(1000);

  
  check();
  digitalWrite(s1[0],HIGH);
  digitalWrite(s1[1],LOW);
  digitalWrite(s1[2],LOW);
  check();
  digitalWrite(s2[0],HIGH);
  digitalWrite(s2[1],LOW);
  digitalWrite(s2[2],LOW);
  check();
  digitalWrite(s3[0],LOW);
  digitalWrite(s3[1],LOW);
  digitalWrite(s3[2],HIGH);
 
for(int i=0; i<5; i++)
  {
    check();
    delay(1000);
  }
 
  
  digitalWrite(s1[0],HIGH);
  digitalWrite(s1[1],LOW);
  digitalWrite(s1[2],LOW);
  check();
  digitalWrite(s2[0],HIGH);
  digitalWrite(s2[1],LOW);
  digitalWrite(s2[2],LOW);
 check();
  digitalWrite(s3[0],HIGH);
  digitalWrite(s3[1],LOW);
  digitalWrite(s3[2],LOW);
  check();
  digitalWrite(s4[0],LOW);
  digitalWrite(s4[1],HIGH);
  digitalWrite(s4[2],LOW);
  check();
  delay(1000);

  check();
  
  digitalWrite(s1[0],HIGH);
  digitalWrite(s1[1],LOW);
  digitalWrite(s1[2],LOW);
  check();
  digitalWrite(s2[0],HIGH);
  digitalWrite(s2[1],LOW);
  digitalWrite(s2[2],LOW);
  check();
  digitalWrite(s3[0],HIGH);
  digitalWrite(s3[1],LOW);
  digitalWrite(s3[2],LOW);
  check();
  digitalWrite(s4[0],LOW);
  digitalWrite(s4[1],LOW);
  digitalWrite(s4[2],HIGH);
  //delay(5000);
for(int i=0; i<5; i++)
  {
    check();
    delay(1000);
  }
  digitalWrite(s1[0],LOW);
  digitalWrite(s1[1],HIGH);
  digitalWrite(s1[2],LOW);
  check();
  digitalWrite(s2[0],HIGH);
  digitalWrite(s2[1],LOW);
  digitalWrite(s2[2],LOW);
  check();
  digitalWrite(s3[0],HIGH);
  digitalWrite(s3[1],LOW);
  digitalWrite(s3[2],LOW);
  check();
  digitalWrite(s4[0],HIGH);
  digitalWrite(s4[1],LOW);
  digitalWrite(s4[2],LOW);
  check();
  delay(1000);
  

}


void loop() //command in this function will be repeated continuously in a loop till the program ends.
{
 
  default1();//function default1 is called.
 
}


