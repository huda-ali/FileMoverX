#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace FileManager {

    void ClearScreen() {
        cin.get();
        system("cls");
    }

    void OperationCompleted() {
        cout << "\n\n";
        cout << "---------------------------------------------------------------------\n";
        cout << "\n\t\tOperation Completed\t\t\n\n";
        cout << "---------------------------------------------------------------------\n\n";

    }

    void ChoicesScreen() {
        cout << " C: Copy a File \n M: Move a File\n";
    }

    void MainScreen() {
        cout << "\n\n---------------------------------------------------------------------\n";
        cout << "\n\t\tWelcome to FileMoverX\t\t\n\n";
        cout << "---------------------------------------------------------------------\n\n";
        cout << "Press Any Key to continue :)-";
    }

    bool FileExists(string& FileName) {
        fstream File;
        File.open(FileName, ios::in);
        bool Exists = File.is_open();
        File.close();
        return Exists;
    }

    bool ContinueOperation() {
        char ContinueChoice;
        cout << "Do you want to perform another operation? (y/n): ";
        cin >> ContinueChoice;
        cin.ignore();
        return (ContinueChoice == 'y' || ContinueChoice == 'Y');
    }

    string PromptFileName(const string& PromptMessage) {
        string FileName;
        cout << PromptMessage;
        getline(cin, FileName);
        return FileName;
    }

    char GetUserChoice() {
        char Choice;
        while (true) {
            FileManager::ChoicesScreen();
            cin >> Choice;
            cin.ignore();
            if (Choice == 'c' || Choice == 'C' || Choice == 'm' || Choice == 'M') {
                break;
            }
            cout << "Invalid choice. Please enter 'c' to copy or 'm' to move.\n";
        }
        return Choice;
    }

    string GetSourceFileName() {
        string SourceFileName;
        while (true) {
            SourceFileName = PromptFileName("Enter Source File Name (SourceFile.txt): ");
            if (FileExists(SourceFileName)) {
                break;
            }
            cout << "Error: Source file does not exist. Please enter source file again.\n";
        }
        return SourceFileName;
    }

    string GetDestinationFileName() {
        string DestinationFileName;
        while (true) {
            DestinationFileName = PromptFileName("Enter New File Name (NewFile.txt): ");
            if (!FileExists(DestinationFileName)) {
                break;
            }
            char OverwriteChoice;
            cout << "Warning: This file already exists. Do you want to overwrite it? (y/n): ";
            cin >> OverwriteChoice;
            cin.ignore();

            if (OverwriteChoice == 'y' || OverwriteChoice == 'Y') {
                break;
            }
            else if (OverwriteChoice == 'n' || OverwriteChoice == 'N') {
                continue;
            }
            else {
                cout << "Invalid choice. Please enter 'y' or 'n'.\n";
            }
        }
        return DestinationFileName;
    }

    void EndTheProgram() {
        cout << "---------------------------------------------------------------------\n";
        cout << "\n\t\tProgram ends\t\t\n\n";
        cout << "---------------------------------------------------------------------\n\n";
    }

    void CopyFileContent(string& SourceFileName, string& DestinationFileName) {
        fstream SourceFile(SourceFileName, ios::in);
        fstream DestinationFile(DestinationFileName, ios::out);

        if (SourceFile.is_open() && DestinationFile.is_open()) {
            string Line;
            while (getline(SourceFile, Line)) {
                DestinationFile << Line << "\n";
            }

            SourceFile.close();
            DestinationFile.close();
        }
        else {
            if (!SourceFile.is_open()) {
                cout << "Unable to open source file: " << SourceFileName << "\n";
            }
            if (!DestinationFile.is_open()) {
                cout << "Unable to open destination file: " << DestinationFileName << "\n";
            }
        }
    }

    void MoveFileContent(string& SourceFileName, string& DestinationFileName) {
        CopyFileContent(SourceFileName, DestinationFileName);
        if (remove(SourceFileName.c_str()) != 0) {
            cout << "Error deleting file: " << SourceFileName << "\n";
        }
    }

}
