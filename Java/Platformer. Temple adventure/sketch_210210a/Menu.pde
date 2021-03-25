class Menu{
  public Boolean showMenu = true;
  
  public Boolean playButtonClicked = false;
  public Boolean editButtonClicked = false;
  public Boolean loadButtonClicked = false;
  
  private Button playButton, editButton, loadButton;
  
  public Menu(){
    playButton = new Button(250,300);
    playButton.text = "Story mode";
    
    editButton = new Button(250,400);
    editButton.text = "Level editor";
    
    loadButton = new Button(250,500);
    loadButton.text = "Load level";
  }
  
  void render(){
    
    if(showMenu){
    playButtonClicked = false;
    editButtonClicked = false;
    loadButtonClicked = false;
      
    background(loadImage("menu_bg.png"));
    playButton.showRect();
    editButton.showRect();
    loadButton.showRect();
    
    if(isMousePressed){
      if(playButton.isMouseOver()){
        playButtonClicked = true;
      }
      if(loadButton.isMouseOver()){
        loadButtonClicked = true;
      }
      if(editButton.isMouseOver()){ 
        editButtonClicked = true;
      }
    }
   }
  }
}

class Button{
   public float x,y;
   public float w,h;
   public String text = "Button";
   public PImage texture;
   
   public Button(float x, float y){
     this.x = x;
     this.y = y;
     w = 300;
     h = 50;
   }
   
   boolean isMouseOver()  {
    if (mouseX >= x && mouseX <= x + w && 
      mouseY >= y && mouseY <= y + h) {
    return true;
    } else {
    return false;
    }
  }
   
   public void showRect(){
     //Draw rectangle//
     fill(50,50,50);
     rect(x,y,w,h);
     
     //Paint button text//
     textSize(30);
     textAlign(CENTER, CENTER);
     fill(255,255,255);
     text(text,x + w/2, y + h/2 - 5);
   }
   
   public void showImage(){
     image(texture, x, y);
   }
}
