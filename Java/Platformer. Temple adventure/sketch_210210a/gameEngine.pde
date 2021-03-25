final class GameEngine {
  //level tools//
  int level = 1;
  Boolean new_level = false;

  //Entities//
  private Player player;
  Boolean moveRight = false;

  //Physics//
  private float gravity = 0;
  private final float gravityAccelaration = 0.2;

  private Boolean isRectIntersect(float x1, float y1, float x2, float y2, int size1, int size2) {
    return (x1<(x2 + size2) && (x1 + size1) > x2) && (y1<(y2 + size2) && (y1 + size1) > y2);
  }

  //Map//
  PImage tileMap;
  PImage backgroundImage;
  Table levelTable;
  private final int MAP_WIDTH = 250;
  private final int MAP_HEIGHT = 20;
  private final int TILE_SIZE = 30;
  Tile[][] map = new Tile[MAP_WIDTH][MAP_HEIGHT];

  int renderLeftPos = 0;
  int renderRightPos = MAP_WIDTH;

  private void loadLevel(int level) {
    if(this.level == 0 || level == 0){
      levelTable = loadTable("myLevel.csv");
      this.level = 0;
    }
    else if (level == 1) {
      levelTable = loadTable("level1.csv");
      this.level = 1;    
    }
    else if (level == 2){
      levelTable = loadTable("level2.csv");
      this.level = 2;
    }
    else if (level == 3){
      levelTable = loadTable("level3.csv");
      this.level = 3;
    }
    else if(level > 3){
      levelTable = loadTable("level1.csv");
      this.level = 1;
    }
    
    player.respawn();
    cameraOffset = 0;

    for (int i = 0; i<MAP_WIDTH; ++i) {
      for (int j = 0; j<MAP_HEIGHT; ++j) {
        map[i][j] = new Tile(i * TILE_SIZE, j * TILE_SIZE, levelTable.getInt(j, i));
      }
    }
  }

  //Camera//
  float cameraOffset = 0;
  
  public GameEngine(int level) {
    player = new Player(0, 400);
    
    loadLevel(level);
    
    tileMap = loadImage("TILEMAP.png");
    backgroundImage = loadImage("level1_bg.png");
    player.texture = tileMap.get(6 * TILE_SIZE, 3 * TILE_SIZE, 30, 30);
  }

  public void render() {
    //Paint map//
    background(backgroundImage);

    if ((int) player.x / TILE_SIZE - 15 > 0) renderLeftPos = (int) player.x / TILE_SIZE - 15;
    else renderLeftPos = 0;

    if ((int) player.x / TILE_SIZE + 30<MAP_WIDTH) renderRightPos = (int) player.x / TILE_SIZE + 30;
    else renderRightPos = MAP_WIDTH;

    for (int i = renderLeftPos; i<renderRightPos; ++i) {
      for (int j = 0; j<MAP_HEIGHT; ++j) {
        if (map[i][j].ID != 0) image(tileMap.get(levelTable.getInt(j, i) % 10 * TILE_SIZE, levelTable.getInt(j, i) / 10 * TILE_SIZE, TILE_SIZE, TILE_SIZE), map[i][j].x + cameraOffset, map[i][j].y);
      }
    }

    player.prevX = player.x;
    player.prevY = player.y;

    //Apply gravity//
    gravity += gravityAccelaration;
    player.y += gravity;
    player.y -= player.accelarationY;

    //Check if player is out of map//
    if (player.y > SCREEN_HEIGHT) {
      player.respawn();
      cameraOffset = 0;
    }

    //Check for top and bottom collisions//
    for (int i = renderLeftPos; i<renderRightPos; ++i) {
      for (int j = 0; j<MAP_HEIGHT; ++j) {
        if (map[i][j].ID == 1) {
          if (isRectIntersect(player.x, player.y, map[i][j].x, map[i][j].y, player.w, TILE_SIZE)) {
            if (player.prevY - player.y<0) {
              player.y = map[i][j].y - player.w;
              gravity = 0;
              player.accelarationY = 0;
            } else if (player.prevY - player.y > 0) {
              player.y = map[i][j].y + player.h;
              player.accelarationY = gravity;
            }
          }
        }
      }
    }

    //Handle input and adjust camera//
    if (key_A) {
      if (player.x + cameraOffset > 1) player.x -= player.speed;

      //Check for left and rigth side collisions//
      for (int i = 0; i<MAP_WIDTH; ++i) {
        for (int j = 0; j<MAP_HEIGHT; ++j) {
          if (map[i][j].ID == 1 || map[i][j].ID == 3 || map[i][j].ID == 4) {
            if (isRectIntersect(player.x, player.y, map[i][j].x, map[i][j].y, player.w, TILE_SIZE)) {
              if(map[i][j].ID == 4){
                levelTable.setInt(j,i,38);
                break;
              }
              if (map[i][j].ID == 3) {
                new_level = true;
              }
              if (player.prevX - player.x<0) {
                player.x -= player.speed;
              } else if (player.prevX - player.x > 0) {
                player.x += player.speed;
              }
            }
          }
        }
      }
    }
    if (key_D) {
      if (player.x + cameraOffset > SCREEN_WIDTH / 2 && player.x + SCREEN_WIDTH / 2 + player.w<TILE_SIZE * MAP_WIDTH) {
        cameraOffset -= player.speed;
      }
      if (player.x + player.w<TILE_SIZE * MAP_WIDTH) player.x += player.speed;

      //Check for left and rigth side collisions//
      for (int i = 0; i<MAP_WIDTH; ++i) {
        for (int j = 0; j<MAP_HEIGHT; ++j) {
          if (map[i][j].ID == 1 || map[i][j].ID == 3 || map[i][j].ID == 4) {
            if (isRectIntersect(player.x, player.y, map[i][j].x, map[i][j].y, player.w, TILE_SIZE)) {
              if(map[i][j].ID == 4){
                levelTable.setInt(j,i,38);
                break;
              }
              if (map[i][j].ID == 3) {
                new_level = true;
              }
              if (player.prevX - player.x<0) {
                player.x -= player.speed;
              } else if (player.prevX - player.x > 0) {
                player.x += player.speed;
              }
            }
          }
        }
      }
    }
    if (key_W) {
      if (player.accelarationY == 0 && player.prevY == player.y) player.accelarationY = 7;
    }
    
     if (new_level) {
      loadLevel(level + 1);
      new_level = false;
    }

    //Paint player with animations//
    if (player.prevX > player.x) {
      if (frameCount % 60 == 0) player.texture = tileMap.get(90, 0, 30, 30);
      else if (frameCount % 60 == 30) player.texture = tileMap.get(120, 0, 30, 30);
      moveRight = true;
    } else if (player.prevX<player.x) {
      if (frameCount % 60 == 0) player.texture = tileMap.get(0, 0, 30, 30);
      else if (frameCount % 60 == 30) player.texture = tileMap.get(60, 0, 30, 30);
      moveRight = false;
    } else {
      if (!moveRight) player.texture = tileMap.get(6 * TILE_SIZE, 3 * TILE_SIZE, 30, 30);
      else player.texture = tileMap.get(1 * TILE_SIZE, 0 * TILE_SIZE, 30, 30);
    }
    
    image(player.texture, player.x + cameraOffset, player.y);
  }
}
