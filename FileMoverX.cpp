#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "FileManager.h"

using namespace std;

enum UserChoice {
    COPY = 'c',
    MOVE = 'm'
};

void ShiftSync() {
    while (true) {
        FileManager::MainScreen();
        FileManager::ClearScreen();
        string sourceFileName = FileManager::GetSourceFileName();
        string destinationFileName = FileManager::GetDestinationFileName();
        char choice = FileManager::GetUserChoice();
        switch (choice) {
        case COPY:
        case 'C':
            FileManager::CopyFileContent(sourceFileName, destinationFileName);
            cout << "File copied successfully.\n";
            break;
        case MOVE:
        case 'M':
            FileManager::MoveFileContent(sourceFileName, destinationFileName);
            cout << "File moved successfully.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        FileManager::OperationCompleted();
        if (!FileManager::ContinueOperation()) {
            break;
        }

        FileManager::ClearScreen();
    }
    FileManager::EndTheProgram();
}

int main() {
    ShiftSync();
    system("pause>0");
    return 0;
}
