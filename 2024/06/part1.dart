import 'dart:io';
import 'dart:convert';

enum orientation { top, left, right, bottom }

(int, int)? next_position(
    int x, int y, orientation direction, int width, int height) {
  switch (direction) {
    case orientation.top:
      x -= 1;
    case orientation.bottom:
      x += 1;
    case orientation.left:
      y -= 1;
    case orientation.right:
      y += 1;
  }
  if (x < 0 || x >= height || y < 0 || y >= width) {
    return null;
  }
  return (x, y);
}

orientation next_orientation(orientation direction) {
  // We could probably just use int value and modulos
  switch (direction) {
    case orientation.top:
      return orientation.right;
    case orientation.right:
      return orientation.bottom;
    case orientation.bottom:
      return orientation.left;
    case orientation.left:
      return orientation.top;
  }
}

void main() {
  File('input.txt').readAsString().then((String textInput) {
    const splitter = LineSplitter();
    var lines = splitter.convert(textInput);

    var obstacles = {};
    int x = 0;
    int y = 0;
    orientation direction = orientation.top;

    var height = lines.length;
    var width = lines[0].length;

    for (var i = 0; i < lines.length; i++) {
      assert(lines[i].length == width);
      for (var j = 0; j < lines[i].length; j++) {
        switch (lines[i][j]) {
          case '#':
            if (!obstacles.containsKey(i)) {
              obstacles[i] = {};
            }
            obstacles[i][j] = true;
          case '^':
            x = i;
            y = j;
          case '.':
            continue;
          default:
            assert(false);
        }
      }
    }

    var visited = {};
    while (true) {
      if (!visited.containsKey(x)) {
        visited[x] = {};
      }
      visited[x][y] = true;
      var nextposition = next_position(x, y, direction, width, height);
      if (nextposition == null) {
        break;
      }
      var (nextx, nexty) = nextposition;
      if (obstacles.containsKey(nextx) && obstacles[nextx].containsKey(nexty)) {
        direction = next_orientation(direction);
      } else {
        (x, y) = (nextx, nexty);
      }
    }
    var sum = 0;
    for (var i in visited.keys) {
      for (var j in visited[i].keys) {
        sum += 1;
      }
    }
    print(sum);
  });
}
