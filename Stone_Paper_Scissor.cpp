#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
using namespace std;

enum enChoice { Rock = 1, Paper = 2, Scissor = 3 };

string ChoiceToString(enChoice choice) {
    switch (choice) {
    case Rock: return "Rock";
    case Paper: return "Paper";
    case Scissor: return "Scissor";
    }
    return "Unknown";
}

struct stRoundResult {
    int roundNumber;
    enChoice playerChoice;
    enChoice computerChoice;
    string result;
};

struct stGame {
    int PlayerScore = 0;
    int ComputerScore = 0;
    int Ties = 0;
    int TotalRounds = 0;
    vector<stRoundResult> RoundsHistory;
};

stGame game;

enChoice ComputerChoice() {
    return (enChoice)(rand() % 3 + 1);
}

string DetermineWinner(enChoice player, enChoice computer) {
    if (player == computer) return "Draw";
    if ((player == Rock && computer == Scissor) ||
        (player == Paper && computer == Rock) ||
        (player == Scissor && computer == Paper))
        return "Player Wins";
    return "Computer Wins";
}

void PrintRoundStats(const stRoundResult& round) {
    cout << setw(6) << round.roundNumber << setw(15)
        << ChoiceToString(round.playerChoice) << setw(20)
        << ChoiceToString(round.computerChoice) << setw(20)
        << round.result << endl;
}

void ShowStatistics() {
    cout << "\n======== Game Summary ========\n";
    cout << setw(6) << "Round" << setw(15) << "Player Choice"
        << setw(20) << "Computer Choice" << setw(20) << "Result" << endl;

    for (const auto& round : game.RoundsHistory) {
        PrintRoundStats(round);
    }

    cout << "\nFinal Score:\n";
    cout << "Player: " << game.PlayerScore << endl;
    cout << "Computer: " << game.ComputerScore << endl;
    cout << "Ties: " << game.Ties << endl;
    cout << "Total Rounds: " << game.TotalRounds << endl;

    float playerWinRate = (game.PlayerScore * 100.0f) / game.TotalRounds;
    float computerWinRate = (game.ComputerScore * 100.0f) / game.TotalRounds;

    cout << fixed << setprecision(2);
    cout << "Player Win Rate: " << playerWinRate << "%\n";
    cout << "Computer Win Rate: " << computerWinRate << "%\n";
}

void PlayRound(int roundNumber) {
    int playerChoice;
    cout << "Enter your choice: [1]Rock [2]Paper [3]Scissor (0 to exit): ";
    cin >> playerChoice;

    if (playerChoice == 0) {
        cout << "Exiting round...\n";
        return;
    }

    if (playerChoice < 1 || playerChoice > 3) {
        cout << "Invalid choice! Round skipped." << endl;
        return;
    }

    enChoice player = (enChoice)playerChoice;
    enChoice computer = ComputerChoice();
    string result = DetermineWinner(player, computer);

    if (result == "Player Wins") game.PlayerScore++;
    else if (result == "Computer Wins") game.ComputerScore++;
    else game.Ties++;

    game.TotalRounds++;

    stRoundResult round = { roundNumber, player, computer, result };
    game.RoundsHistory.push_back(round);

    cout << "Computer chose: " << ChoiceToString(computer) << endl;
    cout << "Result: " << result << endl;
}

void StartGame() {
    srand((unsigned)time(0));
    char playAgain;

    do {
        int rounds;
        cout << "How many rounds do you want to play? ";
        cin >> rounds;

        game = {};

        for (int i = 0; i < rounds; ++i) {
            cout << "\n--- Round " << (i + 1) << " ---\n";
            PlayRound(i + 1);
        }

        ShowStatistics();

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
}

int main() {
    cout << "==============================\n";
    cout << " Welcome to Rock Paper Scissor!\n";
    cout << "==============================\n\n";
    StartGame();
    cout << "\nThanks for playing!\n";
    return 0;
}
