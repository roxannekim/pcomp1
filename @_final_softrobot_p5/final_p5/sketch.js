//Time Tunnel Machine by Roxanne Kim
//NYU ITP 2016 Winter Show
//p5 Sketch

var serial; // variable to hold an instance of the serialport library
var changeVal = 0; // ellipse position
var sound, amplitude, cnv;
var x, y;


function preload() {
  sound = loadSound('Untitled.mp3');
}


function setup() {
  createCanvas(320, 240);
  serial = new p5.SerialPort(); // make a new instance of  serialport library
  serial.on('list', printList); // callback function for serialport list event
  serial.on('data', serialEvent); // callback for new data coming in
  serial.list(); // list the serial ports
  serial.open("/dev/cu.usbmodem1411"); // open a port

}


function draw() {
  background("#2307AF");
  fill(255);
  ellipse(total1, height / 2, 20, 20);
  text(total1, 20, 20);
}


// get the list of ports:
function printList(portList) {
  for (var i = 0; i < portList.length; i++) {
    // Display the list the console:
    println(i + " " + portList[i]);
  }
}


function serialEvent() {

  var total1 = serial.readLine();

  if (total1 > 100) {
    inString = inString.trim();
    total1 = Number(inString);
    println(total1);

    amplitude = new p5.Amplitude();
    sound.loop();
  
   // masterVolume(0.3 + changeVal * 0.1);
  }
}