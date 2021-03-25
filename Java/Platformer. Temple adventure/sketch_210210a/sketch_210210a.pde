GameEngine gameEngine;
EditorEngine editorEngine;
Menu mainMenu;

final int SCREEN_WIDTH = 800;
final int SCREEN_HEIGHT = 600;

static Boolean key_A = false;
static Boolean key_W = false;
static Boolean key_D = false;
static Boolean key_P = false;

static Boolean isMousePressed = false;
static Boolean isMouseReleased = false;

private Boolean isStoryMode = false;
private Boolean isEditorMode = false;
private Boolean isCustomLevelMode = false;

void setup() {
  size(800, 600);
  frameRate(60);
  
  surface.setTitle("Temple adventure");
  
  mainMenu = new Menu();
  gameEngine = new GameEngine(1);
  editorEngine = new EditorEngine();
}

void draw() {
  if(mainMenu.showMenu){
    mainMenu.render();
    if(mainMenu.playButtonClicked){
      if(!isStoryMode) gameEngine = new GameEngine(1);
 
      isCustomLevelMode = false;
      isStoryMode = true;
      isEditorMode = false;
      
      mainMenu.showMenu = false;
    }
    else if(mainMenu.loadButtonClicked){
      if(!isCustomLevelMode) gameEngine = new GameEngine(0);
      
      isCustomLevelMode = true;
      isStoryMode = false;
      isEditorMode = false;
      
      mainMenu.showMenu = false;
    }
    else if(mainMenu.editButtonClicked){
      isStoryMode = false;
      isCustomLevelMode = false;
      isEditorMode = true;
      
      mainMenu.showMenu = false;
    }
  }
  
  if(!mainMenu.showMenu && (isStoryMode || isCustomLevelMode))gameEngine.render();
  if(!mainMenu.showMenu && isEditorMode)editorEngine.show();
  
  if(key_P){
    mainMenu.showMenu = true;
  }
  
  isMousePressed = false;
  isMouseReleased = false;
}

void keyPressed() {
  switch(key) {
  case 97:
    key_A = true;
    break;

  case 119:
    key_W = true;
    break;

  case 112:
    key_P = true;
    break;

  case 100:
    key_D = true;
    break;
  }
}

void keyReleased() {
  switch(key) {
  case 97:
    key_A = false;
    break;
    
    case 112:
    key_P = false;
    break;

  case 119:
    key_W = false;
    break;

  case 100:
    key_D = false;
    break;
  }
}

void mousePressed(){
    isMousePressed = true;
}

void mouseReleased(){
  isMouseReleased = true;  
}
