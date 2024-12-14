#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct robot {
  int px;
  int py;
  int vx;
  int vy;
};

void printRobot(robot r) {
  cout << "Robot : " << r.px << " " << r.py << endl;
}

bool digit(char c) {
  return '0' <= c && c <= '9';
}

vector<robot> readFile(char *filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Couldn't open file " << filename << endl;
    exit(-1);
  }
  vector<robot> result;
  string line;
  while(getline(file, line)) {
    robot r = {.px = 0, .py = 0, .vx = 0, .vy = 0};
    int positive = 1;
    int *value = &r.px;
    for (char &c : line) {
      if (c == ',' || c == ' ') {
        *value *= positive;
        positive = 1;
        if (value == &r.px) {
          value = &r.py;
        } else if (value == &r.py) {
          value = &r.vx;
        } else if (value == &r.vx) {
          value = &r.vy;
        }
        continue;
      }
      if (c == '-') {
        positive = -1;
      }
      if (digit(c)) {
        *value *= 10;
        *value += c - '0';
      }
    }
    *value *= positive;
    result.push_back(r);
  }
  file.close();
  return result;
}

const int steps = 100;
const int width = 101;
const int height = 103;

robot simulate(robot r) {
  // We want the modulo to be positive, quick and dirty way :
  robot result = {
    .px = (((r.px + steps * r.vx) % width) + width) % width,
    .py = (((r.py + steps * r.vy) % height) + height) % height,
    .vx = r.vx,
    .vy = r.vy
  };
  return result;
}

vector<robot> simulate_all(vector<robot> input) {
  vector<robot> result;
  for (robot& r : input) {
    result.push_back(simulate(r));
  }
  return result;
}

int safetyFactor(vector<robot> input) {
  int topleftCount = 0;
  int toprightCount = 0;
  int bottomleftCount = 0;
  int bottomrightCount = 0;

  for(robot& r : input) {
    if (r.px < static_cast<int>(width/2)) {
      if (r.py < static_cast<int>(height/2)) {
        topleftCount++;
      } else if (r.py >= static_cast<int>(height/2 + 1)) {
        bottomleftCount++;
      }
    } else if (r.px >= static_cast<int>(width/2)+1) {
      if (r.py < static_cast<int>(height/2)) {
        toprightCount++;
      } else if (r.py >= static_cast<int>(height/2 + 1)) {
        bottomrightCount++;
      }
    }
  }
  return topleftCount * toprightCount * bottomleftCount * bottomrightCount;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Invalid usage : " << argv[0] << " filename" << endl;
    return -1;
  }
  vector<robot> input = readFile(argv[1]);
  vector<robot> transformed = simulate_all(input);
  cout << "Safety factor : " << safetyFactor(transformed) << endl;
  return 0;
}
