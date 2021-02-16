#include <iostream>
#include <fstream>


#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "hacker.h"
#include "simulation.h"

using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(cont));
}

int main(int argc, char const* argv[]) { 

    //string inputFile = "input_9.txt";
    //string outputFile = "output_9.txt";

    string inputFile = argv[1];
    string outputFile = argv[2];

    ifstream infile(inputFile);
    vector<int> hackerIds;

    string line;
    getline(infile, line);
    vector<string> words;
    split1(line, words);


    // Store relevant commit times
    getline(infile, line);
    int commitNo = stoi(line);

    vector<int> relevantCommitHacker;
    vector<int> relevantCommitLine;
    vector<vector<int>> allCommitLine;
    vector<float> relevantCommitTime;
    vector<vector<float>> allCommitTime;
    double changeCommitLineCount = 0;
    
    for (int i = 0; i < commitNo; i++) {
        getline(infile, line);
        vector<string> commit;
        split1(line, commit);
        relevantCommitHacker.push_back(stod(commit[0]));
        relevantCommitLine.push_back(stod(commit[1]));
        relevantCommitTime.push_back(stod(commit[2]));

        changeCommitLineCount += stod(commit[1]);
    }

    for (int j = 1; j <= stod(words[0]); j++)
    {
        vector<float> tempAllCommits;
        for (int i = 0; i < commitNo; i++)
        {
            if (relevantCommitHacker[i] == j)
                tempAllCommits.push_back(relevantCommitTime[i]);
        }
        allCommitTime.push_back(tempAllCommits);
    }

    for (int j = 1; j <= stod(words[0]); j++)
    {
        vector<int> tempAllCommits;
        for (int i = 0; i < commitNo; i++)
        {
            if (relevantCommitHacker[i] == j)
                tempAllCommits.push_back(relevantCommitLine[i]);
        }
        allCommitLine.push_back(tempAllCommits);
    }

    // Generate Hackers
    vector<Hacker> hackers(stod(words[0]));
    for (int i = 0; i < stod(words[0]); i++) {
        hackers[i] = Hacker(i+1, stod(words[i + 1]), allCommitTime[i], allCommitLine[i]);
    }

    // Store queue attempt times
    getline(infile, line);
    int queueAttemptNo = stoi(line);
    vector<int> attemptIds;
    vector<float> attemptTimes;

    for (int i = 0; i < queueAttemptNo; i++) {
        getline(infile, line);
        vector<string> queueAttempts;
        split1(line, queueAttempts);
        attemptIds.push_back(stod(queueAttempts[0]));
        attemptTimes.push_back(stod(queueAttempts[1]));
    }

    getline(infile, line);
    vector<string> stickerInfo;
    split1(line, stickerInfo);
    vector<float> stickerServiceTime;
    for (int i = 0; i < stod(stickerInfo[0]); i++) {
        stickerServiceTime.push_back(stod(stickerInfo[i+1]));
    }

    getline(infile, line);
    vector<string> hoodieInfo;
    split1(line, hoodieInfo);
    vector<float> hoodieServiceTime;
    for (int i = 0; i < stod(hoodieInfo[0]); i++) {
        hoodieServiceTime.push_back(stod(hoodieInfo[i+1]));
    }

    Simulation simulation(stod(stickerInfo[0]), stod(hoodieInfo[0]), stickerServiceTime, hoodieServiceTime, &hackers, attemptIds, attemptTimes);  //stod(stickerInfo[0]), stod(hoodieInfo[0]), & input
   
    //cout << "hacker count: " << stod(words[0]) << endl << endl;
    /*cout << "max sticker queue length: " << simulation.getMaxStickerQueueLength() << endl;
    cout << "max hoodie queue length: " << simulation.getMaxHoodieQueueLength() << endl;
    cout << "gift count: " << simulation.getGiftCount() / (stod(words[0]) * 2) << endl;
    cout << "sticker queue waiting time: " << simulation.getStickerQueueWaitingTime() / (simulation.getGiftCount()/2) << endl;
    cout << "hoodie queue waiting time: " << simulation.getHoodieQueueWaitingTime() / (simulation.getGiftCount()/2) << endl;
    cout << "ave number of code commit per hacker: " << commitNo/stod(words[0]) << endl;
    cout << "ave number of changed commit line per hacker: " << changeCommitLineCount/commitNo << endl;
    cout << "ave turn around time: " << simulation.getTurnAroundTime() / (simulation.getGiftCount()/2) << endl;
    cout << "invalid sticker attempt count: " << simulation.getInvalidStickerAttempCount() << endl;
    cout << "invalid gift attempt count: " << simulation.getInvalidGiftAttempCount() << endl;
    int hacker; float waitingTime;
    simulation.getMostWaitingHacker(&hacker, &waitingTime);
    cout << "most waiting hacker is: " << hacker << " time is: " << waitingTime << endl;
    int hacker2; float waitingTime2;
    simulation.getThreeGiftHacker(&hacker2, &waitingTime2);
    cout << "three gift hacker is: " << hacker2 << " time is: " << waitingTime2 << endl;
    cout << "total time: " << simulation.getTotalTime() << endl;*/

    ofstream myfile(outputFile);
    myfile << std::fixed;
    myfile << std::setprecision(3);
    myfile << simulation.getMaxStickerQueueLength() << endl;
    myfile << simulation.getMaxHoodieQueueLength() << endl;
    myfile << simulation.getGiftCount() / (stod(words[0]) * 2) << endl;
    myfile << simulation.getStickerQueueWaitingTime() / (simulation.getGiftCount() / 2) << endl;
    myfile << simulation.getHoodieQueueWaitingTime() / (simulation.getGiftCount() / 2) << endl;
    myfile << commitNo / stod(words[0]) << endl;
    myfile << changeCommitLineCount / commitNo << endl;
    myfile << simulation.getTurnAroundTime() / (simulation.getGiftCount() / 2) << endl;
    myfile << simulation.getInvalidStickerAttempCount() << endl;
    myfile << simulation.getInvalidGiftAttempCount() << endl;
    int hacker; float waitingTime;
    simulation.getMostWaitingHacker(&hacker, &waitingTime);
    myfile << hacker << " " << waitingTime << endl;
    int hacker2; float waitingTime2;
    simulation.getThreeGiftHacker(&hacker2, &waitingTime2);
    myfile << hacker2 << " " << waitingTime2 << endl;
    myfile << simulation.getTotalTime();

    return 0;

}