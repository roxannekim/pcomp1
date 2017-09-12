function preload() {
  sound = loadSound('final_sound.mp3');
}


function setup() {
  cnv = createCanvas(400, 300);
  amplitude = new p5.Amplitude();
  sound.loop();
}


function draw() {
  background("#000000");
  fill(255);
  //ellipse(changeVal, height / 2, 20, 20);
  textSize(100);
  textAlign(CENTER);


  var speed = map(mouseX, 1, 400, 1, 8);
  text(nfc(speed, 3), width / 2, height / 2 + 30);
  speed = constrain(speed, 0, 2.3);
  sound.rate(speed);

  masterVolume(0.3 + speed * 0.1);
  
  
  // var level = amplitude.getLevel();
  // var size = map(level, 0, 1, 0, 200);
  // noStroke();

  // for (var i = 0; i <= width; i += 10) {
  //   for (var j = 0; j <= height - 10; j += 10)
  //     rectMode(CENTER);
  //     stroke(speed*10);
  //     //strokeCap(ROUND);
  //     //strokeWeight(0.1);
  //   //rect(i + 1, height - size*5, 1, size*2);
  //   rect(size*5, i + 10, size*5, 1);
  // }


  // var noiseScale=0.02;
  // for (var x=0; x < width; x++) {
  //   var noiseVal = noise((mouseX+x)*noiseScale, mouseY*noiseScale);
  //   stroke(noiseVal*255);
  //   line(x, mouseY+noiseVal*80, x, height);
  // }


}