// Arduino Voting Machine - 2 Candidates (Buttons Only, No LEDs)
// Using INPUT_PULLUP for buttons - No resistors needed!

// WIRING GUIDE FOR ARDUINO UNO:
// =============================
// BUTTONS (with INPUT_PULLUP - No resistors needed):
//   Button A (Candidate 1): One leg to Digital Pin 2, other leg to GND
//   Button B (Candidate 2): One leg to Digital Pin 3, other leg to GND
//
// GND Connection: Connect both button GND legs to Arduino GND pin
// =============================

// Button pins
const int buttonA = 2;
const int buttonB = 3;

// Vote counters
int votesA = 0;
int votesB = 0;

// Button state tracking (for debouncing)
bool buttonAPressed = false;
bool buttonBPressed = false;

void setup() {
  // Initialize buttons with INPUT_PULLUP (no external resistors needed!)
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  
  // Start serial communication
  Serial.begin(9600);
  
  // Wait for serial to initialize
  delay(1000);
  
  Serial.println("===========================================");
  Serial.println("    VOTING MACHINE - 2 CANDIDATES");
  Serial.println("===========================================");
  Serial.println("Button A = Candidate A");
  Serial.println("Button B = Candidate B");
  Serial.println();
  Serial.println("Press any button to cast your vote!");
  Serial.println("===========================================");
  Serial.println();
}

void loop() {
  // Read button states (LOW = pressed because of INPUT_PULLUP)
  
  // Candidate A
  if (digitalRead(buttonA) == LOW && !buttonAPressed) {
    buttonAPressed = true;
    votesA++;
    
    Serial.println();
    Serial.println(">>> VOTE REGISTERED FOR CANDIDATE A <<<");
    Serial.println();
    
    showVotes();
    delay(300); // Debounce delay
  }
  if (digitalRead(buttonA) == HIGH) {
    buttonAPressed = false;
  }
  
  // Candidate B
  if (digitalRead(buttonB) == LOW && !buttonBPressed) {
    buttonBPressed = true;
    votesB++;
    
    Serial.println();
    Serial.println(">>> VOTE REGISTERED FOR CANDIDATE B <<<");
    Serial.println();
    
    showVotes();
    delay(300); // Debounce delay
  }
  if (digitalRead(buttonB) == HIGH) {
    buttonBPressed = false;
  }
}

// Display current vote count
void showVotes() {
  Serial.println("╔════════════════════════════════════╗");
  Serial.println("║      CURRENT VOTE COUNT            ║");
  Serial.println("╠════════════════════════════════════╣");
  Serial.print("║  Candidate A: ");
  Serial.print(votesA);
  if (votesA < 10) Serial.print(" ");
  if (votesA < 100) Serial.print(" ");
  Serial.println(" votes            ║");
  
  Serial.print("║  Candidate B: ");
  Serial.print(votesB);
  if (votesB < 10) Serial.print(" ");
  if (votesB < 100) Serial.print(" ");
  Serial.println(" votes            ║");
  
  Serial.println("╠════════════════════════════════════╣");
  
  // Calculate total votes
  int totalVotes = votesA + votesB;
  Serial.print("║  Total Votes: ");
  Serial.print(totalVotes);
  if (totalVotes < 10) Serial.print(" ");
  if (totalVotes < 100) Serial.print(" ");
  Serial.println("                 ║");
  
  Serial.println("╠════════════════════════════════════╣");
  
  // Show who's winning
  if (votesA > votesB) {
    Serial.println("║  🏆 CANDIDATE A IS LEADING! 🏆    ║");
  } else if (votesB > votesA) {
    Serial.println("║  🏆 CANDIDATE B IS LEADING! 🏆    ║");
  } else if (totalVotes > 0) {
    Serial.println("║  ⚖️  IT'S A TIE! ⚖️                ║");
  } else {
    Serial.println("║  Waiting for votes...              ║");
  }
  
  Serial.println("╚════════════════════════════════════╝");
  Serial.println();
}