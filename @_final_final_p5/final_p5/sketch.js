//Time Tunnel Machine by Roxanne Kim
//NYU ITP 2016 Winter Show
//p5 Sketch

var serial; // variable to hold an instance of the serialport library
var changeVal = 0; // ellipse position
var sound, amplitude, cnv;
var x, y;


function preload() {
  sound = loadSound('final_sound.mp3');
}


function setup() {
  createCanvas(320, 240);
  serial = new p5.SerialPort(); // make a new instance of  serialport library
  serial.on('list', printList); // callback function for serialport list event
  serial.on('data', serialEvent); // callback for new data coming in
  serial.list(); // list the serial ports
  serial.open("/dev/cu.usbmodem1411"); // open a port

  amplitude = new p5.Amplitude();
  sound.loop();
}


function draw() {
  background("#2307AF");
  fill(255);
  ellipse(changeVal, height / 2, 20, 20);
  text(changeVal, 20, 20);
}


// get the list of ports:
function printList(portList) {
  for (var i = 0; i < portList.length; i++) {
    // Display the list the console:
    println(i + " " + portList[i]);
  }
}


function serialEvent() {

  var inString = serial.readLine();

  if (inString.length > 0) {
    inString = inString.trim();
    changeVal = Number(inString);
    println(changeVal);
    
    var speed = map(changeVal, 1, 10, 1, 2);
    
    speed = constrain(speed, 0.01, 2);
    sound.rate(speed);

    masterVolume(0.3 + changeVal * 0.1);
  }
}