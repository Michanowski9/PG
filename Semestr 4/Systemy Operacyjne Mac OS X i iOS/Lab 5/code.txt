class Game {
  var map = Array(repeating: Array(repeating: " ", count: 3), count: 3)
  var player1: Player
  var player2: Player
  
  init(player1:Player, player2: Player) {
    self.player1 = player1
    self.player2 = player2
    drawMap()
  }

  func isEndOfGame() -> String {
    //wygrana O lub X
    for i in 0..<3{
      if map[i][0] != " " && map[i][0] == map[i][1] && map [i][1] == map[i][2] {
        return map[i][0] + " won"
      }
    }
    for i in 0..<3{
      if map[0][i] != " " && map[0][i] == map[1][i] && map [1][i] == map[2][i] {
        return map[0][i] + " won"
      }
    }
    if map[0][0] != " " && map[0][0] == map[1][1] && map [1][1] == map[2][2] {
      return map[0][0] + " won"
    }
    if map[0][2] != " " && map[0][2] == map[1][1] && map [1][1] == map[2][0] {
      return map[0][2] + " won"
    }

    //sprawdzenie czy jest jeszcze wolne pole na mapie
    for x in 0..<3 {
      for y in 0..<3 {
        if map[x][y] == " " {
          return " "
        }
      }
    }
    //wszystkie pola zajęte
    return "draw"
  }
  
  func gameLoop() {
    while true {
      //ruch pierwszego gracza
      map = player1.makeMove(map: map)
      let result1 = isEndOfGame()
      drawMap()
      if result1 != " " {
        print(result1)
        break
      }

      //ruch drugiego gracza
      map = player2.makeMove(map: map)
      
      let result2 = isEndOfGame()
      drawMap()
      if result2 != " " {
        print(result2)
        break
      }
    }
  }

  func drawMap() {
    for row in map {
      print(" -------------")
      print(" | ",terminator: "")
      for elem in row {
        print(elem, terminator: "")
        print(" | ",terminator: "")
      }
      print()
    }
    print(" -------------")
  }
}

class Player {
  var sign = "-"
  init(sign: String){
    self.sign = sign
  }
  func makeMove(map:[[String]]) -> [[String]] {
    var result = map
    if let position = readLine(){
      if var intPos = Int(position){
        intPos = intPos - 1
        let x = intPos / 3;
        let y = intPos % 3;
        if result[x][y] != " " {
          print("Field is not empty. Choose another one")
          return makeMove(map:map)
        }
        result[x][y] = sign
      }
    }
    return result
  }
}

class AI_Easy : Player {
  override init(sign: String){
    super.init(sign: sign)
  }
  override func makeMove(map:[[String]]) -> [[String]] {
    var result = map
    let x = Int.random(in: 0..<3);
    let y = Int.random(in: 0..<3);
    if result[x][y] != " " {
      return makeMove(map:map)
    }
    result[x][y] = sign
    return result
  }
}

class AI_Normal : Player {
  override init(sign: String){
    super.init(sign: sign)
  }
  override func makeMove(map:[[String]]) -> [[String]] {
    var result = map
    //horizontal
    // - X X
    for i in 0..<3{
      if map[i][0] == " " &&
          map[i][1] == map[i][2] &&
          map[i][1] != self.sign && map[i][1] != " " {
        result[i][0] = sign
        return result
      }
    }
    // X X -
    for i in 0..<3{
      if map[i][1] == " " &&
          map[i][0] == map[i][2] &&
          map[i][0] != self.sign && map[i][0] != " " {
        result[i][1] = sign
        return result
      }
    }
    // X - X
    for i in 0..<3{
      if map[i][2] == " " &&
          map[i][1] == map[i][0] &&
          map[i][1] != self.sign && map[i][1] != " " {
        result[i][2] = sign
        return result
      }
    }
    let x = Int.random(in: 0..<3);
    let y = Int.random(in: 0..<3);
    if result[x][y] != " " {
      return makeMove(map:map)
    }
    result[x][y] = sign
    return result
  }
}

class AI_Hard : Player {
  override init(sign: String){
    super.init(sign: sign)
  }
  override func makeMove(map:[[String]]) -> [[String]] {
    var result = map
    //horizontal
    // - X X
    for i in 0..<3{
      if map[i][0] == " " &&
          map[i][1] == map[i][2] &&
          map[i][1] != self.sign && map[i][1] != " " {
        result[i][0] = sign
        return result
      }
    }
    // X X -
    for i in 0..<3{
      if map[i][1] == " " &&
          map[i][0] == map[i][2] &&
          map[i][0] != self.sign && map[i][0] != " " {
        result[i][1] = sign
        return result
      }
    }
    // X - X
    for i in 0..<3{
      if map[i][2] == " " &&
          map[i][1] == map[i][0] &&
          map[i][1] != self.sign && map[i][1] != " " {
        result[i][2] = sign
        return result
      }
    }
    //vertical
    // - X X
    for i in 0..<3{
      if map[0][i] == " " &&
          map[1][i] == map[2][i] &&
          map[1][i] != self.sign && map[1][i] != " " {
        result[0][i] = sign
        return result
      }
    }
    // X X -
    for i in 0..<3{
      if map[1][i] == " " &&
          map[0][i] == map[2][i] &&
          map[0][i] != self.sign && map[0][i] != " " {
        result[1][i] = sign
        return result
      }
    }
    // X - X
    for i in 0..<3{
      if map[2][i] == " " &&
          map[1][i] == map[0][i] &&
          map[1][i] != self.sign && map[1][i] != " " {
        result[2][i] = sign
        return result
      }
    }
    let x = Int.random(in: 0..<3);
    let y = Int.random(in: 0..<3);
    if result[x][y] != " " {
      return makeMove(map:map)
    }
    result[x][y] = sign
    return result
  }
}

var playerX : Player
var playerO : Player
var game : Game

playerX = Player(sign:"X")
playerO = AI_Easy(sign:"O")

while true{
  print("Choose your opponent")
  print("1. player")
  print("2. AI easy")
  print("3. AI normal")
  print("4. AI hard")
  
  if let option = readLine(){
    if let optionNum = Int(option){
      if optionNum == 1 {
        playerO = Player(sign:"O")
      }
      else if optionNum == 2 {
        playerO = AI_Easy(sign:"O")
      }
      else if optionNum == 3 {
        playerO = AI_Normal(sign:"O")
      }
      else if optionNum == 4 {
        playerO = AI_Hard(sign:"O")
      }
    }
  }
  game = Game(player1: playerX, player2: playerO)
  game.gameLoop()

  print("type \"restart\" to restart")
  if let restart = readLine(){
    if restart != "restart" {
      break
    }
  }
}
