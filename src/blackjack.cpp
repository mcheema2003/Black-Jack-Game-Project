#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

struct Card {
    int value;
    string suit;
    string name;
};

class Deck {
private:
    vector<Card> cards;
    vector<Card> dealtCards;
    
public:
    Deck() {
        string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        string names[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        int values[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
        
        for (int s = 0; s < 4; s++) {
            for (int n = 0; n < 13; n++) {
                Card card;
                card.value = values[n];
                card.suit = suits[s];
                card.name = names[n];
                cards.push_back(card);
            }
        }
    }
    
    void shuffle() {
        srand(time(0));
        for (int i = cards.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(cards[i], cards[j]);
        }
    }
    
    Card dealCard() {
        Card card = cards.back();
        cards.pop_back();
        dealtCards.push_back(card);
        return card;
    }
    
    vector<Card> getRemainingCards() {
        return cards;
    }
    
    int getRemainingCount() {
        return cards.size();
    }
};

class Hand {
private:
    vector<Card> cards;
    
public:
    void addCard(Card card) {
        cards.push_back(card);
    }
    
    int getValue() {
        int total = 0;
        int aces = 0;
        
        for (int i = 0; i < cards.size(); i++) {
            total += cards[i].value;
            if (cards[i].name == "Ace") {
                aces++;
            }
        }
        
        while (total > 21 && aces > 0) {
            total -= 10;
            aces--;
        }
        
        return total;
    }
    
    bool isSoft() {
        int total = 0;
        int aces = 0;
        
        for (int i = 0; i < cards.size(); i++) {
            total += cards[i].value;
            if (cards[i].name == "Ace") {
                aces++;
            }
        }
        
        while (total > 21 && aces > 0) {
            total -= 10;
            aces--;
        }
        
        return aces > 0 && total <= 21;
    }
    
    bool isBusted() {
        return getValue() > 21;
    }
    
    bool isBlackjack() {
        return cards.size() == 2 && getValue() == 21;
    }
    
    vector<Card> getCards() {
        return cards;
    }
    
    void display(string owner, bool hideFirst = false) {
        cout << owner << "'s Hand: ";
        for (int i = 0; i < cards.size(); i++) {
            if (i == 0 && hideFirst) {
                cout << "[Hidden] ";
            } else {
                cout << cards[i].name << " of " << cards[i].suit;
                if (i < cards.size() - 1) cout << ", ";
            }
        }
        if (!hideFirst) {
            cout << " (Total: " << getValue();
            if (isSoft()) cout << " soft";
            cout << ")";
        }
        cout << endl;
    }
};

class ProbabilityCalculator {
public:
    static double calculateBustProbability(int currentTotal, vector<Card>& remainingCards) {
        if (remainingCards.size() == 0) return 0.0;
        
        int bustCards = 0;
        for (int i = 0; i < remainingCards.size(); i++) {
            int cardValue = remainingCards[i].value;
            if (remainingCards[i].name == "Ace") {
                cardValue = (currentTotal + 11 > 21) ? 1 : 11;
            }
            if (currentTotal + cardValue > 21) {
                if (remainingCards[i].name == "Ace") {
                    if (currentTotal + 1 > 21) {
                        bustCards++;
                    }
                } else {
                    bustCards++;
                }
            }
        }
        
        return (double)bustCards / remainingCards.size() * 100.0;
    }
    
    static double calculateDealerBustProbability(int dealerUpCard, vector<Card>& remainingCards) {
        int bustCount = 0;
        int simulations = 1000;
        
        srand(time(0));
        
        for (int sim = 0; sim < simulations; sim++) {
            int dealerTotal = dealerUpCard;
            int aces = (dealerUpCard == 11) ? 1 : 0;
            
            int holeCardIndex = rand() % remainingCards.size();
            int holeValue = remainingCards[holeCardIndex].value;
            if (remainingCards[holeCardIndex].name == "Ace") aces++;
            dealerTotal += holeValue;
            
            while (dealerTotal > 21 && aces > 0) {
                dealerTotal -= 10;
                aces--;
            }
            
            while (dealerTotal < 17) {
                int nextCardIndex = rand() % remainingCards.size();
                int nextValue = remainingCards[nextCardIndex].value;
                if (remainingCards[nextCardIndex].name == "Ace") aces++;
                dealerTotal += nextValue;
                
                while (dealerTotal > 21 && aces > 0) {
                    dealerTotal -= 10;
                    aces--;
                }
            }
            
            if (dealerTotal > 21) {
                bustCount++;
            }
        }
        
        return (double)bustCount / simulations * 100.0;
    }
    
    static double calculateWinProbability(int playerTotal, int dealerUpCard, vector<Card>& remainingCards, bool playerCanHit) {
        int winCount = 0;
        int simulations = 1000;
        
        for (int sim = 0; sim < simulations; sim++) {
            int dealerTotal = dealerUpCard;
            int aces = (dealerUpCard == 11) ? 1 : 0;
            
            int holeCardIndex = rand() % remainingCards.size();
            int holeValue = remainingCards[holeCardIndex].value;
            if (remainingCards[holeCardIndex].name == "Ace") aces++;
            dealerTotal += holeValue;
            
            while (dealerTotal > 21 && aces > 0) {
                dealerTotal -= 10;
                aces--;
            }
            
            while (dealerTotal < 17) {
                int nextCardIndex = rand() % remainingCards.size();
                int nextValue = remainingCards[nextCardIndex].value;
                if (remainingCards[nextCardIndex].name == "Ace") aces++;
                dealerTotal += nextValue;
                
                while (dealerTotal > 21 && aces > 0) {
                    dealerTotal -= 10;
                    aces--;
                }
            }
            
            if (dealerTotal > 21) {
                winCount++;
            } else if (playerTotal > dealerTotal) {
                winCount++;
            }
        }
        
        return (double)winCount / simulations * 100.0;
    }
    
    static void displayProbabilities(Hand& playerHand, int dealerUpCard, vector<Card>& remainingCards) {
        int playerTotal = playerHand.getValue();
        
        cout << "\n--- Probability Analysis ---" << endl;
        cout << fixed << setprecision(2);
        
        double bustProb = calculateBustProbability(playerTotal, remainingCards);
        cout << "Probability of busting on next hit: " << bustProb << "%" << endl;
        
        double dealerBustProb = calculateDealerBustProbability(dealerUpCard, remainingCards);
        cout << "Estimated dealer bust probability: " << dealerBustProb << "%" << endl;
        
        double winProb = calculateWinProbability(playerTotal, dealerUpCard, remainingCards, true);
        cout << "Current winning probability (if standing): " << winProb << "%" << endl;
        
        double safeHitProb = 100.0 - bustProb;
        cout << "Safe hit probability: " << safeHitProb << "%" << endl;
        
        cout << "----------------------------\n" << endl;
    }
};

class BlackjackGame {
private:
    Deck deck;
    Hand playerHand;
    Hand dealerHand;
    double bet;
    double playerMoney;
    
public:
    BlackjackGame() {
        playerMoney = 1000.0;
        bet = 0.0;
    }
    
    void play() {
        cout << "========================================" << endl;
        cout << "     BLACKJACK - CASINO CARD GAME      " << endl;
        cout << "========================================" << endl;
        cout << "\nWelcome to Blackjack!" << endl;
        cout << "Your starting balance: $" << playerMoney << endl;
        
        char playAgain = 'y';
        
        while (playAgain == 'y' || playAgain == 'Y') {
            if (playerMoney <= 0) {
                cout << "\nYou're out of money!" << endl;
                char addMore;
                cout << "Would you like to add more balance? (y/n): ";
                cin >> addMore;
                
                if (addMore == 'y' || addMore == 'Y') {
                    double addAmount;
                    cout << "How much would you like to add? $";
                    cin >> addAmount;
                    if (addAmount > 0) {
                        playerMoney += addAmount;
                        cout << "New balance: $" << playerMoney << endl;
                    } else {
                        cout << "Invalid amount. Game over." << endl;
                        break;
                    }
                } else {
                    cout << "Thanks for playing! Game over." << endl;
                    break;
                }
            }
            
            deck = Deck();
            playerHand = Hand();
            dealerHand = Hand();
            
            deck.shuffle();
            cout << "\n----------------------------------------" << endl;
            cout << "Current Balance: $" << playerMoney << endl;
            cout << "Enter your bet: $";
            cin >> bet;
            
            if (bet > playerMoney) {
                cout << "You don't have enough money. Betting all: $" << playerMoney << endl;
                bet = playerMoney;
            }
            
            playerHand.addCard(deck.dealCard());
            dealerHand.addCard(deck.dealCard());
            playerHand.addCard(deck.dealCard());
            dealerHand.addCard(deck.dealCard());
            
            cout << "\n========== INITIAL DEAL ==========" << endl;
            dealerHand.display("Dealer", true);
            playerHand.display("Player");
            
            vector<Card> remaining = deck.getRemainingCards();
            int dealerUpCard = dealerHand.getCards()[1].value;
            
            ProbabilityCalculator::displayProbabilities(playerHand, dealerUpCard, remaining);
            
            if (playerHand.isBlackjack()) {
                cout << "BLACKJACK! You win 1.5x your bet!" << endl;
                playerMoney += bet * 1.5;
                dealerHand.display("Dealer");
                
                cout << "\nPlay again? (y/n): ";
                cin >> playAgain;
                continue;
            }
            
            char choice;
            bool playerStands = false;
            
            while (!playerHand.isBusted() && !playerStands) {
                cout << "Choose action - (H)it or (S)tand: ";
                cin >> choice;
                
                if (choice == 'h' || choice == 'H') {
                    playerHand.addCard(deck.dealCard());
                    cout << "\n========== AFTER HIT ==========" << endl;
                    dealerHand.display("Dealer", true);
                    playerHand.display("Player");
                    
                    remaining = deck.getRemainingCards();
                    
                    if (!playerHand.isBusted()) {
                        ProbabilityCalculator::displayProbabilities(playerHand, dealerUpCard, remaining);
                    }
                } else if (choice == 's' || choice == 'S') {
                    playerStands = true;
                }
            }
            
            if (playerHand.isBusted()) {
                cout << "\n*** BUST! You lose $" << bet << " ***" << endl;
                playerMoney -= bet;
            } else {
                cout << "\n========== DEALER'S TURN ==========" << endl;
                dealerHand.display("Dealer");
                
                while (dealerHand.getValue() < 17) {
                    cout << "Dealer hits..." << endl;
                    dealerHand.addCard(deck.dealCard());
                    dealerHand.display("Dealer");
                }
                
                cout << "\n========== FINAL RESULT ==========" << endl;
                dealerHand.display("Dealer");
                playerHand.display("Player");
                
                int playerTotal = playerHand.getValue();
                int dealerTotal = dealerHand.getValue();
                
                if (dealerHand.isBusted()) {
                    cout << "\nDealer BUSTS! You win $" << bet << "!" << endl;
                    playerMoney += bet;
                } else if (playerTotal > dealerTotal) {
                    cout << "\nYou WIN $" << bet << "!" << endl;
                    playerMoney += bet;
                } else if (playerTotal < dealerTotal) {
                    cout << "\nDealer wins. You lose $" << bet << "." << endl;
                    playerMoney -= bet;
                } else {
                    cout << "\nPUSH! It's a tie. Your bet is returned." << endl;
                }
            }
            
            cout << "\nYour balance: $" << playerMoney << endl;
            cout << "\nPlay again? (y/n): ";
            cin >> playAgain;
        }
        
        cout << "\n========================================" << endl;
        cout << "Thanks for playing! Final balance: $" << playerMoney << endl;
        cout << "========================================" << endl;
    }
};

