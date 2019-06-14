import processing.serial.*;

Serial myPort;  // Create object from Serial class

String rpm = "0";
long previousTime = 0;

int myWidth = 1280;
int myHeight = 720;
boolean detection = false;
PFont f;
Table myTable;
int count = 0;

void setup()
{
  // I know that the first port in the serial list on my mac
  // is Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
//fullScreen();
  background(20,30,40);
  size(1280,720);
  //list = Serial.list();
  //for(int i; i < 
  print(Serial.list()[0].toString());
  int lstLength = Serial.list().length;
  //println(Serial.list());
  String portName = Serial.list()[lstLength-1];
  //change the 0 to a 1 or 2 etc. to match your port
  print(Serial.list()[lstLength-1].toString());
  myPort = new Serial(this, portName, 9600);
  f = createFont("Helvetica",100,true);
  frameRate(240);
  //table.addColumn("RPM");
  myTable = new Table();
  //myTable.addColumn("Index",Table.INT);
  myTable.addColumn("RPM",Table.STRING);  //FIXME: RPM only reads integers
  
  smooth(8);
}

void draw()
{
  background(20,30,40);
  if ( myPort.available() > 0) {  // If data is available,
      rpm = (myPort.readStringUntil(59)); 
      myTable.addRow();
      myTable.setString((myTable.getRowCount()-1),"RPM",rpm);
      saveTable(myTable, "data.csv");
  }
      textFont(f);
      textSize(100);
      textAlign(CENTER);
      text((rpm + " rpm"), myWidth/2, myHeight/2);
}
