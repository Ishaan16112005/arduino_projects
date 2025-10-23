// 2-Player Tournament Reaction Game
// Round 1: 7 games, Round 2: 6 games

// LED pins
const int centralLED = 8;  // Central game LED (RED)
const int led1 = 9;        // Player 1 LED (GREEN)
const int led2 = 10;       // Player 2 LED (BLUE)

// Button pins
const int button1 = 2;
const int button2 = 3;

// Game variables
int score1 = 0;
int score2 = 0;
int currentRound = 1;
int currentGame = 1;
int gamesInRound = 7; // Round 1 has 7 games
unsigned long reactionTime = 0;
unsigned long startTime = 0;
bool gameActive = false;

void setup() {
  Serial.begin(9600);
  
  // Initialize LED pins
  pinMode(centralLED, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  // Turn off all LEDs
  digitalWrite(centralLED, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  
  // Initialize button pins with internal pull-ups
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  
  randomSeed(analogRead(0));
  
  Serial.println("╔════════════════════════════════╗");
  Serial.println("║  REACTION TOURNAMENT GAME!     ║");
  Serial.println("╚════════════════════════════════╝");
  Serial.println("║ Round 1: 7 Games               ║");
  Serial.println("║ Round 2: 6 Games               ║");
  Serial.println("╚════════════════════════════════╝");
  Serial.println();
  delay(3000);
  
  startNewGame();
}

void loop() {
  if (gameActive) {
    // Check Player 1 button
    if (digitalRead(button1) == LOW) {
      handleButtonPress(1);
      delay(50);
      return;
    }
    
    // Check Player 2 button
    if (digitalRead(button2) == LOW) {
      handleButtonPress(2);
      delay(50);
      return;
    }
  }
}

void startNewGame() {
  gameActive = false;
  
  // Turn off all LEDs
  digitalWrite(centralLED, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  
  Serial.println("═══════════════════════════════════");
  Serial.println("ROUND " + String(currentRound) + " - GAME " + String(currentGame));
  Serial.println("═══════════════════════════════════");
  Serial.println("Get ready...");
  
  delay(1000);
  
  // Random blinking pattern (3-8 blinks)
  int numBlinks = random(3, 9);
  for (int i = 0; i < numBlinks; i++) {
    digitalWrite(centralLED, HIGH);
    delay(random(150, 400));
    digitalWrite(centralLED, LOW);
    delay(random(200, 600));
  }
  
  // Random pause before GO signal
  delay(random(500, 2500));
  
  // GO SIGNAL - Central LED stays ON
  digitalWrite(centralLED, HIGH);
  startTime = millis();
  gameActive = true;
  
  Serial.println(">>> GO! PRESS NOW! <<<");
}

void handleButtonPress(int player) {
  if (!gameActive) return;
  
  gameActive = false;
  reactionTime = millis() - startTime;
  
  // Turn off central LED
  digitalWrite(centralLED, LOW);
  
  // Award point
  if (player == 1) {
    score1++;
  } else {
    score2++;
  }
  
  // Blink winner's LED once
  if (player == 1) {
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
  } else {
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
  }
  
  // Display game result
  Serial.println();
  Serial.println(">>> Player " + String(player) + " WINS! <<<");
  Serial.println("Reaction time: " + String(reactionTime) + " ms");
  Serial.println();
  Serial.println("─── Current Scores ───");
  Serial.println("Player 1: " + String(score1));
  Serial.println("Player 2: " + String(score2));
  Serial.println("──────────────────────");
  Serial.println();
  
  currentGame++;
  
  // Check if round is complete
  if (currentGame > gamesInRound) {
    displayRoundComplete();
    
    if (currentRound == 1) {
      // Prepare for Round 2
      currentRound = 2;
      currentGame = 1;
      gamesInRound = 6;
      
      Serial.println();
      Serial.println("╔════════════════════════════════╗");
      Serial.println("║   ROUND 2 STARTS IN 15 SEC     ║");
      Serial.println("╚════════════════════════════════╝");
      Serial.println();
      
      delay(15000); // 15 second break
      startNewGame();
    } else {
      // Tournament complete
      displayFinalResults();
    }
  } else {
    // Continue to next game
    delay(2000);
    startNewGame();
  }
}

void displayRoundComplete() {
  Serial.println();
  Serial.println("╔════════════════════════════════╗");
  Serial.println("║      ROUND " + String(currentRound) + " COMPLETED!        ║");
  Serial.println("╚════════════════════════════════╝");
  Serial.println();
  Serial.println("━━━━━━ ROUND " + String(currentRound) + " TOTAL SCORES ━━━━━━");
  Serial.println("Player 1: " + String(score1));
  Serial.println("Player 2: " + String(score2));
  
  if (score1 > score2) {
    Serial.println(">>> Player 1 is LEADING! <<<");
  } else if (score2 > score1) {
    Serial.println(">>> Player 2 is LEADING! <<<");
  } else {
    Serial.println(">>> It's a TIE! <<<");
  }
  Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
}

void displayFinalResults() {
  Serial.println();
  Serial.println("╔════════════════════════════════╗");
  Serial.println("║    TOURNAMENT COMPLETE!        ║");
  Serial.println("╚════════════════════════════════╝");
  Serial.println();
  Serial.println("━━━━━━ FINAL SCORES ━━━━━━");
  Serial.println("Player 1: " + String(score1) + " / 13");
  Serial.println("Player 2: " + String(score2) + " / 13");
  Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━");
  Serial.println();
  
  if (score1 > score2) {
    Serial.println("╔════════════════════════════════╗");
    Serial.println("║  🏆 PLAYER 1 WINS! 🏆         ║");
    Serial.println("╚════════════════════════════════╝");
    
    // Flash Player 1 LED 5 times
    for (int i = 0; i < 5; i++) {
      digitalWrite(led1, HIGH);
      delay(300);
      digitalWrite(led1, LOW);
      delay(300);
    }
  } else if (score2 > score1) {
    Serial.println("╔════════════════════════════════╗");
    Serial.println("║  🏆 PLAYER 2 WINS! 🏆         ║");
    Serial.println("╚════════════════════════════════╝");
    
    // Flash Player 2 LED 5 times
    for (int i = 0; i < 5; i++) {
      digitalWrite(led2, HIGH);
      delay(300);
      digitalWrite(led2, LOW);
      delay(300);
    }
  } else {
    Serial.println("╔════════════════════════════════╗");
    Serial.println("║     IT'S A TIE! 🤝            ║");
    Serial.println("╚════════════════════════════════╝");
    
    // Flash both LEDs 5 times
    for (int i = 0; i < 5; i++) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      delay(300);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      delay(300);
    }
  }
  
  Serial.println();
  Serial.println("Game Over! Reset Arduino to play again.");
  
  // Stop the program
  while(true) {
    delay(1000);
  }
}