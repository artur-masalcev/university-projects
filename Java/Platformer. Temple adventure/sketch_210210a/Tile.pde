final class Tile {

  public float x;
  public float y;
  public int ID = 0;

  public Tile(int x, int y, int ID) {
    switch (ID) {
    case -1: 
      this.ID = 0;
      break;
    case 5:
      this.ID = 1;
      break;
    case 6:
      this.ID = 1;
      break;
    case 10:
      this.ID = 1;
      break;
    case 11:
      this.ID = 1;
      break;
    case 14:
      this.ID = 1;
      break;
    case 20:
      this.ID = 1;
      break;
    case 21:
      this.ID = 1;
      break;
    case 22:
      this.ID = 1;
      break;
    case 23:
      this.ID = 1;
      break;
    case 25:
      this.ID = 1;
      break;
    case 26:
      this.ID = 1;
      break;
    case 27:
      this.ID = 1;
      break;
    case 28:
      this.ID = 1;
      break;
    case 29:
      this.ID = 1;
      break;
    case 35:
      this.ID = 3;
      break;
    case 40:
      this.ID = 1;
      break;
    case 41:
      this.ID = 1;
      break;
    case 42:
      this.ID = 1;
      break;
    case 43:
      this.ID = 1;
      break;
    case 44:
      this.ID = 1;
      break;
    case 45:
      this.ID = 1;
      break;
    case 46:
      this.ID = 1;
      break;
    case 47:
      this.ID = 1;
      break;
    case 50:
      this.ID = 1;
      break;
    case 51:
      this.ID = 1;
      break;
    case 52:
      this.ID = 1;
      break;
    case 53:
      this.ID = 1;
      break;
    case 54:
      this.ID = 1;
      break;
    case 55:
      this.ID = 1;
      break;
    case 56:
      this.ID = 1;
      break;
    case 57:
      this.ID = 1;
      break;
    case 60:
      this.ID = 1;
      break;
    case 61:
      this.ID = 1;
      break;
    case 62:
      this.ID = 1;
      break;
    case 64:
      this.ID = 1;
      break;
    case 65:
      this.ID = 1;
      break;
    case 66:
      this.ID = 1;
      break;
    case 67:
      this.ID = 1;
      break;
    case 70:
      this.ID = 1;
      break;
    case 71:
      this.ID = 1;
      break;
    case 72:
      this.ID = 1;
      break;
    case 73:
      this.ID = 4;
      break;
    case 76:
      this.ID = 1;
      break;
    case 86:
      this.ID = 1;
      break;
    default:
      this.ID = 2;
    }
    this.x = x;
    this.y = y;
  }
}
