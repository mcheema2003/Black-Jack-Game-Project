# Blackjack Casino Card Game

## Project Description

This is a C++ implementation of a Blackjack casino card game that simulates the classic casino experience with real-time probability calculations. The program uses a standard 52-card deck and implements all standard Blackjack rules including dealer behavior, Ace handling (soft/hard hands), and blackjack payouts.

The unique feature of this program is its dynamic probability analysis system, which calculates and displays the player's chances of winning, busting, and other outcomes based on the current game state and remaining cards in the deck. This educational tool helps players understand the mathematics behind Blackjack decision-making.

## Programming Approaches

- **Object-Oriented Design**: The program uses C++ classes (Deck, Hand, ProbabilityCalculator, BlackjackGame) to encapsulate game components and logic.
- **Monte Carlo Simulation**: Probability calculations use statistical simulation with 1000 iterations to estimate dealer bust probability and winning chances.
- **Fisher-Yates Shuffle Algorithm**: Ensures uniform random card distribution for fair gameplay.
- **Dynamic Probability Calculation**: Real-time probability updates based on remaining deck composition after each card dealt.

## Features

- Single 52-card deck simulation
- Real-time probability analysis (bust probability, win probability, safe hit probability)
- Proper Ace handling (valued as 1 or 11)
- Dealer AI following standard casino rules (hit on 16 or less, stand on 17+)
- Betting system with balance management
- Option to add more funds when balance reaches zero

## Authors

Muhammad Cheema

## Date Published

December 2025

## How to Use

### Compilation

```bash
g++ src/blackjack.cpp -o blackjack
```

### Running the Program

```bash
./blackjack
```

### Gameplay Instructions

1. **Start**: The program displays your starting balance of $1000
2. **Place Bet**: Enter the amount you want to bet
3. **Initial Deal**: You receive 2 cards, dealer receives 2 cards (one hidden)
4. **View Probabilities**: The program shows your winning chances and bust probability
5. **Make Decision**: 
   - Press `H` to Hit (receive another card)
   - Press `S` to Stand (keep your current hand)
6. **Dealer's Turn**: After you stand, the dealer reveals their hand and plays
7. **Result**: The winner is determined and your balance is updated
8. **Continue**: Choose to play again or quit

### Game Rules

- Cards 2-10 are worth their face value
- Face cards (Jack, Queen, King) are worth 10
- Aces are worth 11 or 1 (automatically adjusted to prevent busting)
- Blackjack (Ace + 10-value card) pays 1.5x your bet
- Dealer must hit on 16 or less and stand on 17 or more
- If you exceed 21, you bust and lose your bet
- If dealer busts, you win
- Closest to 21 without going over wins

## File Structure

```
/
├── README.md                  # This file
├── Project_Documentation.txt  # Detailed project documentation
└── src/
    └── blackjack.cpp         # Main source code
```

## Requirements

- C++ compiler (g++, clang++, or similar)
- Standard C++ library support
