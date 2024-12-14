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

const int steps = 1;
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

bool isTree(vector<robot> input) {
  bool* visited = new bool[width * height];
  for (int i = 0; i < width * height; i++) {
    visited[i] = false;
  }
  for (robot& r : input) {
    if (visited[r.px*width + r.py]) {
      delete[] visited;
      return false;
    }
    visited[r.px * width + r.py] = true;
  }
  delete[] visited;
  return true;
}

int stepsRequired(vector<robot> input) {
  int i = 0;
  while(!isTree(input)) {
    input = simulate_all(input);
    i++;
  }
  return i;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Invalid usage : " << argv[0] << " filename" << endl;
    return -1;
  }
  vector<robot> input = readFile(argv[1]);
  cout << "Steps required : " << stepsRequired(input) << endl;
  return 0;
}
