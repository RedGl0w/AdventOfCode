import Foundation

let fileManager = FileManager.default
guard let fileData = fileManager.contents(atPath: "input.txt") 
else {
  fatalError("Couldn't find file")
}
guard let fileContent = String(data: fileData, encoding: .utf8)
else {
  fatalError("Couldn't read file")
}

// Start parsing the imput file
var sources: [Character:[(Int, Int)]] = [:];
let lines = fileContent.split(separator: "\n");
let height = lines.count;
let width = lines[0].count;
for i in 0..<lines.count {
  assert(lines[i].count == width);
  for j in 0..<lines[i].count {
    let c: Character = lines[i][lines[i].index(lines[i].startIndex, offsetBy: j)];
    switch (c) {
      case ".":
        continue;
      default:
        if (sources[c] == nil) {
          sources[c] = [];
        }
        sources[c]!.append((i,j))
        continue;
    }
  }
}

// Foreach frequency, compute antinodes
var antinodes: [Int:[Int:Bool]] = [:];
for frequency in sources.keys {
  // We check each pair of sources of same frequency, and we take care of
  // the order in the couple (we check one time to bottom right, the other top left)
  for fst in 0..<sources[frequency]!.count {
    for snd in 0..<sources[frequency]!.count {
      if fst == snd {
        continue;
      }
      let (x1, y1) = sources[frequency]![fst];
      let (x2, y2) = sources[frequency]![snd];
      // We start by computing the delta between to positions
      var deltaX = x2-x1;
      var deltaY = y2-y1;
      if (deltaX == 0) {
        deltaY = deltaY>0 ? 1 : -1;
      } else if (deltaY == 0) {
        deltaX = deltaX>0 ? 1 : -1;
      } else {
        if (deltaX <= deltaY) {
          if (deltaY % deltaX == 0) {
            deltaY /= abs(deltaX);
            deltaX = deltaX>0 ? 1 : -1;
          }
        } else {
          if (deltaX % deltaY == 0) {
            deltaX /= abs(deltaY);
            deltaY = deltaY>0 ? 1 : -1;
          }
        }
      }
      // print(x1+1,y1+1,x2+1,y2+1,deltaX, deltaY);
      // And we compute every position on the line
      var possibleX = x2;
      var possibleY = y2;
      while (true) {
        if (possibleX < 0 || possibleX >= height || possibleY < 0 || possibleY >= width) {
          break;
        }
        // We have an antinode
        if (antinodes[possibleX] == nil) {
          antinodes[possibleX] = [:];
        }
        antinodes[possibleX]![possibleY] = true;
        possibleX += deltaX;
        possibleY += deltaY;
      }
    }
  }
}

var total = 0;
for x in antinodes.keys {
  total += antinodes[x]!.count;
}

for i in 0..<height {
  var l = "";
  for j in 0..<width {
    if (antinodes[i] != nil && antinodes[i]![j] != nil) {
      l += "#";
      continue;
    }
    l += ".";
  }
  print(l);
}

print(total);
