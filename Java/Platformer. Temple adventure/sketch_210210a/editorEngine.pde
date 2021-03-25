class EditorEngine{
 private Button moveLeftButton, moveRightButton;
 private Button saveButton, loadButton;
 private Button pickButton;
 
 private PImage tileMap;
 
 private int[][] map;
 private Button[][] editorField;
 private Button[][] pickField;
 private int offset = 0;
 
 private int pickedId = 10;
 private PImage pickedImage;
 
 private Boolean isPickMode = false;
  
 public EditorEngine(){
   moveLeftButton = new Button(0, SCREEN_HEIGHT - 50);
   moveLeftButton.w = 100;
   moveLeftButton.text = "<-";
   
   moveRightButton = new Button(100, SCREEN_HEIGHT - 50);
   moveRightButton.w = 100;
   moveRightButton.text = "->";
   
   saveButton = new Button(200, SCREEN_HEIGHT - 50);
   saveButton.w = 200;
   saveButton.text = "Save";
   
   loadButton = new Button(400, SCREEN_HEIGHT - 50);
   loadButton.w = 200;
   loadButton.text = "Load";
   
   pickButton = new Button(600, SCREEN_HEIGHT - 50);
   pickButton.w = 200;
   pickButton.text = "Pick tile";
   
   tileMap = loadImage("TILEMAP.png");
   pickedImage = tileMap.get(0,30,30,30);
   
   map = new int[20][250];
   for(int i = 0; i < 20; ++i){
      for(int j = 0; j < 250; ++j)map[i][j] = -1;
   }
   
   editorField = new Button[29][20];
   for(int i = 0; i < 29; ++i){
     for(int j = 0; j < 20; ++j){
       editorField[i][j] = new Button(i*27, j*27);
       editorField[i][j].w = 27;
       editorField[i][j].h = 27;
       editorField[i][j].text = "";
     }
   }
   
   pickField = new Button[10][10];
   for(int i = 0; i < 10; ++i){
      for(int j = 0; j < 10; ++j){
        pickField[i][j] = new Button(i*30 + SCREEN_WIDTH / 2 - 300 / 2, j*30 + 300 / 2 + 10);
        pickField[i][j].texture = tileMap.get(i * 30, j * 30, 30, 30);
        pickField[i][j].w = 30;
        pickField[i][j].h = 30;
        pickField[i][j].text = "";
      }
   }
   
 }
   
   public void show(){
     if(!isPickMode){
     background(50, 50, 50);
     moveLeftButton.showRect();
     moveRightButton.showRect();
     saveButton.showRect();
     loadButton.showRect();
     pickButton.showRect();
     
     for(int i = 0; i < 29; ++i){
     for(int j = 0; j < 20; ++j){
       if(map[j][i + offset] != -1){
         editorField[i][j].texture = tileMap.get(map[j][i + offset] % 10 * 30, map[j][i + offset] / 10 * 30, 27, 27);
         editorField[i][j].showImage();
       }
       else editorField[i][j].showRect();
      }
    }
    
    if(isMouseReleased){
      if(pickButton.isMouseOver()){
         isPickMode = true; 
      }
      if(moveLeftButton.isMouseOver()){
        if(offset != 0)--offset;
      }
      if(moveRightButton.isMouseOver()){
        if(offset < 250-29)++offset;
      }
      if(saveButton.isMouseOver()){
         saveMap(); 
      }
      if(loadButton.isMouseOver()){
        loadMap();
      }
     }
     
     if(mousePressed){
     for(int i = 0; i < 29; ++i){
      for(int j = 0; j < 20; ++j){
         if(editorField[i][j].isMouseOver() && isMousePressed){
            if(map[j][i + offset] == -1)map[j][i + offset] = pickedId;
            else map[j][i + offset] = -1;
         }
       }
      }
     }
    
    image(pickedImage, mouseX, mouseY);
   }
   else{
     showPickMenu();
   }
 }
 
 private void showPickMenu(){
     background(50,50,50);
     fill(0,0,0);
     rect(SCREEN_WIDTH / 2 - 310/2, 310/2, 310, 310);
     
     fill(255,255,255);
     rect(SCREEN_WIDTH / 2 - 300 / 2, 300 / 2 + 10, 300, 300);
     
     for(int i = 0; i < 10; ++i){
      for(int j = 0; j < 10; ++j){
        pickField[i][j].showImage();
      }
      }
      
      if(mousePressed){
        for(int i = 0; i < 10; ++i){
          for(int j = 0; j < 10; ++j){
            if(pickField[i][j].isMouseOver()){
              pickedId = i + j * 10;
              pickedImage = tileMap.get(i*30,j*30,30,30);
              isPickMode = false;
            }
        }
      }
      
   }
  }
  
  private void saveMap(){
    String[] lines = new String[20];
    
    for(int i = 0; i < 20; ++i)lines[i] = "";
    
    for(int i = 0; i < 20; ++i){
       for(int j = 0; j < 250; ++j){
         if(j != 249)lines[i] += String.valueOf(map[i][j]) + ",";
         else lines[i] += String.valueOf(map[i][j]);
       }
    }
    
    saveStrings("myLevel.csv", lines);
  }
  
  private void loadMap(){
    try{
     Table table = loadTable("myLevel.csv");
     for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 250; ++j){
          map[i][j] = table.getInt(i,j);
        }
     }
   } catch(Exception e){
     e.printStackTrace();
   }
  }
}
