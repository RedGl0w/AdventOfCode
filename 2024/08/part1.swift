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
      let possibleX = x2+(x2-x1);
      let possibleY = y2+(y2-y1);
      if (0 <= possibleX && possibleX < height && 0 <= possibleY && possibleY < width) {
        // We have an antinode
        if (antinodes[possibleX] == nil) {
          antinodes[possibleX] = [:];
        }
        antinodes[possibleX]![possibleY] = true;
      }
    }
  }
}

var total = 0;
for x in antinodes.keys {
  total += antinodes[x]!.count;
}
print(total);
