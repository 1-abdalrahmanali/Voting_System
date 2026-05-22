#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_CANDIDATES = 10;

struct Candidate {
    string name;
    int voteCount;
};

Candidate candidateList[MAX_CANDIDATES];
int currentCandidateCount = 0;

void addCandidate();
void castVote();
void displayResults();
void declareWinner();
void saveResultsToFile();

int main() {
    int choice;

    do {
        cout << "\n=== VOTING MENU ===\n";
        cout << "1. Add a Candidate\n";
        cout << "2. Vote\n";
        cout << "3. View Scores\n";
        cout << "4. Declare Winner & Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }

        switch (choice) {
        case 1:
            addCandidate();
            break;

        case 2:
            castVote();
            break;

        case 3:
            displayResults();
            break;

        case 4:
            declareWinner();
            saveResultsToFile();
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}

void addCandidate() {
    if (currentCandidateCount >= MAX_CANDIDATES) {
        cout << "Candidate list is full.\n";
        return;
    }

    cout << "Enter candidate name: ";
    cin >> candidateList[currentCandidateCount].name;

    candidateList[currentCandidateCount].voteCount = 0;
    currentCandidateCount++;

    cout << "Candidate added successfully.\n";
}

void castVote() {
    if (currentCandidateCount == 0) {
        cout << "No candidates available.\n";
        return;
    }

    int userChoice;

    cout << "\n--- Candidates ---\n";

    for (int i = 0; i < currentCandidateCount; i++) {
        cout << i + 1 << ". " << candidateList[i].name << endl;
    }

    cout << "Enter candidate number: ";
    cin >> userChoice;

    if (userChoice < 1 || userChoice > currentCandidateCount) {
        cout << "Invalid candidate number.\n";
        return;
    }

    int index = userChoice - 1;
    candidateList[index].voteCount++;

    cout << "Vote counted for "
         << candidateList[index].name << ".\n";
}

void displayResults() {
    if (currentCandidateCount == 0) {
        cout << "No candidates available.\n";
        return;
    }

    cout << "\n--- Results ---\n";

    for (int i = 0; i < currentCandidateCount; i++) {
        cout << candidateList[i].name
             << ": "
             << candidateList[i].voteCount
             << " votes\n";
    }
}

void declareWinner() {
    if (currentCandidateCount == 0) {
        cout << "No candidates available.\n";
        return;
    }

    int highestVotes = -1;
    int winnerIndex = -1;

    for (int i = 0; i < currentCandidateCount; i++) {
        if (candidateList[i].voteCount > highestVotes) {
            highestVotes = candidateList[i].voteCount;
            winnerIndex = i;
        }
    }

    cout << "\nWinner: "
         << candidateList[winnerIndex].name
         << endl;
}

void saveResultsToFile() {
    if (currentCandidateCount == 0) return;

    ofstream myFile("election_results.txt");

    if (!myFile.is_open()) {
        cout << "Error creating file.\n";
        return;
    }

    myFile << "--- FINAL RESULTS ---\n";

    for (int i = 0; i < currentCandidateCount; i++) {
        myFile << candidateList[i].name
               << ": "
               << candidateList[i].voteCount
               << " votes\n";
    }

    myFile.close();

    cout << "Results saved successfully.\n";
}