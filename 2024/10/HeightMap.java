import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class HeightMap {
  int height = 0;
  int width = -1;
  int[][] map;

  public HeightMap(String filename) {
    try {
      File f = new File(filename);
      Scanner s = new Scanner(f);

      while (s.hasNextLine()) {
        String line = s.nextLine();
        if (line != "") {
          this.height++;
        }
        if (this.width == -1) {
          this.width = line.length();
        } else {
          assert line.length() == this.width;
        }
      }
      s.close();

      this.map = new int[this.height][this.width];
      int currentLine = 0;
      s = new Scanner(f);
      while (s.hasNextLine()) {
        String line = s.nextLine();
        for (int column = 0; column < line.length(); column++) {
          map[currentLine][column] = Character.getNumericValue(line.charAt(column));
        }
        currentLine++;
      }
      s.close();
    } catch (FileNotFoundException e) {
      System.err.println("Couldn't find file");
      e.printStackTrace();
    }
  }

  int scoreTrailHead(int i, int j, Boolean[][] visited) {
    int value = this.map[i][j];
    if (value == 9) {
      if (visited[i][j]) {
        return 0;
      }
      visited[i][j] = true;
      return 1;
    }
    // Check neighbours that increase by one
    int sum = 0;
    if (i - 1 >= 0 && this.map[i - 1][j] == value + 1) {
      sum += scoreTrailHead(i - 1, j, visited);
    }
    if (i + 1 < this.height && this.map[i + 1][j] == value + 1) {
      sum += scoreTrailHead(i + 1, j, visited);
    }
    if (j - 1 >= 0 && this.map[i][j - 1] == value + 1) {
      sum += scoreTrailHead(i, j - 1, visited);
    }
    if (j + 1 < this.width && this.map[i][j + 1] == value + 1) {
      sum += scoreTrailHead(i, j + 1, visited);
    }
    return sum;
  }

  int totalScoreTrailHead() {
    int sum = 0;
    for (int i = 0; i < this.height; i++) {
      for (int j = 0; j < this.width; j++) {
        if (this.map[i][j] == 0) {
          // This could be optimized : visited is only changed when score != 0
          // However, this runs quite fast already, no need to change :p
          Boolean[][] visited = new Boolean[this.height][this.width];
          for (int k = 0; k < this.height; k++) {
            for (int l = 0; l < this.width; l++) {
              visited[k][l] = false;
            }
          }
          int score = scoreTrailHead(i, j, visited);
          sum += score;
        }
      }
    }
    return sum;
  }

  int ratingTrailHead(int i, int j) {
    int value = this.map[i][j];
    if (value == 9) {
      return 1;
    }
    // Check neighbours that increase by one
    int sum = 0;
    if (i - 1 >= 0 && this.map[i - 1][j] == value + 1) {
      sum += ratingTrailHead(i - 1, j);
    }
    if (i + 1 < this.height && this.map[i + 1][j] == value + 1) {
      sum += ratingTrailHead(i + 1, j);
    }
    if (j - 1 >= 0 && this.map[i][j - 1] == value + 1) {
      sum += ratingTrailHead(i, j - 1);
    }
    if (j + 1 < this.width && this.map[i][j + 1] == value + 1) {
      sum += ratingTrailHead(i, j + 1);
    }
    return sum;
  }

  int totalRatingTrailHead() {
    int sum = 0;
    for (int i = 0; i < this.height; i++) {
      for (int j = 0; j < this.width; j++) {
        if (this.map[i][j] == 0) {
          int score = ratingTrailHead(i, j);
          sum += score;
        }
      }
    }
    return sum;
  }

  public static void main(String[] args) {
    HeightMap s = new HeightMap("input.txt");
    System.out.println("Score : " + s.totalScoreTrailHead());
    System.out.println("Rating : " + s.totalRatingTrailHead());
  }
}
