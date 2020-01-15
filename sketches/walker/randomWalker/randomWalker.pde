// RandomWalker to show stochastic processes
// daniel buzzo 2019
// http://buzzo.com


// create a new instance of our walker object
walker myWalker = new walker(300, 300, 1);

void setup(){ 
  size(600,600);
}

void draw(){
  myWalker.update();
  myWalker.draw();
}

// define a class of object walker with three methods
class walker {
  float xPos, yPos, radius;
  // construct a new walker object
  walker(float startX, float startY, float startRad){
   yPos = startX;
   xPos = startY;
   radius = startRad;
  }
  
  // update the walker object
  void update(){
    xPos = xPos + random(4)-2;
    yPos = yPos + random(4)-2;
  }
  
  // draw the walker object
  void draw(){
    circle(xPos, yPos, radius);
  }    
}
