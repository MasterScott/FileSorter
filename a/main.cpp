// 23.10.2019 AUTHOR: ROMANOVCODE or FORMATC
//                             _\___/_
//                            /       \
//                           |   -  -  |
//                           |    __   |
//                            \_______/
//                               ||
//                           ___/  \________\
//                           \________________\  
//                           |       |
//                           |        \
//                            \        |
//							   \ ______|
//                             |___|  \\  
// 25.10.2019 RELEASE. SUCCESS

// Import libraries
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>

using namespace std;

// Function prototype
// Function prototype for Move
void Move(string file, string dir, string dirMove); 
// Function prototype for Copy
void Copy(string file, string dirFile, string dirCopy);

// Main function
int main() {
	// Clear console
	system("cls");
	// Welcome window
	cout << "\n\t[WELCOME TO FILE-SORTER]" << endl;
	// Directory where to get files
	cout << "\n\tEnter directory: ";
	string dir = "";
	getline(cin, dir);

	// The directory in which the files will be copied\moved
	cout << "\n\tEnter directory for copy/move: ";
	string workDir = "";
	getline(cin, workDir);

	// Command for get files in directory       
	// Buffer to receive output
	char buffer[128];
	string result = "";
	// Command execution
	FILE* pipe = _popen(("dir /b /a-d " + dir).c_str(), "r");
	// Clear console
	system("cls");
	// The command didn't work
	if (!pipe) throw std::runtime_error("popen() failed!");
	// Try to get the output
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			// Put output in result
			result += buffer;
		}
	}
	// ERROR
	catch (...) {
		// Close and throw (exit)
		_pclose(pipe);
		throw;
	}
	// Close
	_pclose(pipe);

	// To distribute files on the array
	vector<string> files;
	// Symbol for distribute
	string delim("\n");
	size_t prev = 0;
	size_t next;
	size_t delta = delim.length();

	while ((next = result.find(delim, prev)) != string::npos) {
		string tmp = result.substr(prev, next - prev);
		files.push_back(result.substr(prev, next - prev));
		prev = next + delta;
	}
	string tmp = result.substr(prev);
	// Put
	files.push_back(result.substr(prev));
	
	// Not found files in directory
	if (result.empty()) {
		// Error: FIles not found!
		cout << "\n\tERROR: Files not found!" << endl;
		// Wait 1 second
		Sleep(1000);
		// Go to main
		main();
	}
	
	// Clear console and Start window
	system("cls");
	cout << "\n\t[STARTED]" << endl;
	// Show info
	cout << "\n\tDir: " + dir;

	string mode = "";
	// Loop
	for (unsigned short i = 0; i < files.size(); i++) {
		// Label for jump in start loop
	start_loop:
		// if there are files in the directory
		if (!files[i].empty()) {
			// Show info about file 
			cout << "\n\tFile: " + files[i];
			// Ask if the user wants to do something with it
			cout << "\n\t(y/n): ";
			string yn;
			getline(cin, yn);
			
			// If user wants to do something with it
			if (yn == "y") {
				// Ask him what he wanted to do with it
				cout << "\n\tEnter mode (copy, move, delete or skip?): ";
				getline(cin, mode);
				// Skip file
				if (mode == "skip") { goto skip; }

				// Copy to another directory
				else if (mode == "copy") {
					// call function copy
					Copy(files[i], dir, workDir);
				}

				// Move to another directory
				else if (mode == "move") {
					// Call function move 
					Move(files[i], dir, workDir);
				}
				
				// Delete file. Why not \(-_-)/
				else if (mode == "delete") {
					// Creating a full path to a file
					string full_dir = "";
					// Again prevent errors with the path to the file
					if (dir.back() == '\\') {
						full_dir += dir + "\"" + files[i] + "\"";
					}
					else {
						full_dir = dir + "\\\"" + files[i] + "\"";
					}
					// Delete file
					system(("del " + full_dir).c_str());
					// Success
					cout << "\n\tDeleted!" << endl;
				}
			}
			// If function not found - go to start
			else { goto start_loop; }
			// Skip someone else's function :)
			continue;
		skip:
			cout << "\n\tSkipped" << endl;
		}
		// If file name == "" (that is, it is not, it happens, because at the end of the output is always superfluous \n )
		// Skip him
		else { continue; }
	}

	// End. 
	cout << "\n\t[END]. Files not found." << endl;
	// Wait one second.
	Sleep(1000);
	// Not the end :D
	main();

	// If he still missed the transition to the beginning - pause the console
	system("pause");
	return 0;
}

// Function for move files in another directory
void Move(string file, string dirFile, string dirMove) {
	// Check if there is a slash at the end. If not-there may be a move error
	if (dirFile.back() != '\\') {
		// If not - add slash at the end
		dirFile.append("\\");
	}

	// Generate command
	string cmd = "copy " + dirFile + "\"" + file + "\"" + " " + dirMove;
	// Start command
	FILE* copy = _popen(cmd.c_str(), "r");
	// Buffer for keep output
	char buffer[128];
	// If found problems
	if (!copy) {
		// Print "error move error"
		cout << "\n\tERROR: Move error" << endl;
	}
	// If problems not found
	else {
		// Hide the output and print "SUCCESS"
		while (fgets(buffer, sizeof buffer, copy) != NULL) {};
		cout << "\n\tSUCCESS" << endl;
	}
}

void Copy(string file, string dirFile, string dirCopy) {
	// Check if there is a slash at the end. If not-there may be a copy error
	if (dirFile.back() != '\\') {
		// If not - add slash at the end
		dirFile.append("\\");
	}

	// Generate command
	string cmd = "copy " + dirFile + "\"" + file + "\"" + " " + dirCopy;
	// Start command
	FILE* copy = _popen(cmd.c_str(), "r");
	// Buffer for keep output
	char buffer[128];
	// If there is a problem
	if (!copy) {
		// print "error: copy error"
		cout << "\n\tERROR: Copy error!" << endl;
	}
	// If problems not found
	else {
		// To hide the output
		while (fgets(buffer, sizeof buffer, copy) != NULL) {  };
		// And print "Success"
		cout << "\n\tSUCCESS" << endl;
	}
}

// <- Oh my god!! :D 222 