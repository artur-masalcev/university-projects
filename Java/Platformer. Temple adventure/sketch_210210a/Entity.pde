class Entity {
  public float x, y;
  public int h = 30;
  public int w = 30;
  public float speed = 3;
  public float accelarationY = -1;
  public PImage texture;
  public float prevX, prevY;
}

final class Player extends Entity {
  public Player(int x, int y) {
    this.x = x;
    this.y = y;
  }

  public void respawn() {
    x = 0;
    y = 400;
    accelarationY = -1;
  }
}
