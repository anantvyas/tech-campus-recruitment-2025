#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

std::map<std::string, std::streampos> loadIndex(const std::string& indexFile) {
    std::ifstream inFile(indexFile);
    std::map<std::string, std::streampos> index;
    std::string date;
    std::streampos pos;

    while (inFile >> date >> pos) {
        index[date] = pos;
    }
    inFile.close();
    return index;
}

void extractLogs(const std::string& logFile, const std::string& indexFile, const std::string& targetDate) {
    auto index = loadIndex(indexFile);
    
    if (index.find(targetDate) == index.end()) {
        std::cerr << "Error: Date not found in index.\n";
        return;
    }

    std::ifstream inFile(logFile);
    if (!inFile) {
        std::cerr << "Error: Cannot open log file.\n";
        return;
    }

    std::string outputFile = "output/output_" + targetDate + ".txt";
    std::ofstream outFile(outputFile);
    
    if (!outFile) {
        std::cerr << "Error: Cannot create output file.\n";
        return;
    }

    inFile.seekg(index[targetDate]);  

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.substr(0, 10) != targetDate) break;  
        outFile << line << "\n";
    }

    std::cout << "Logs for " << targetDate << " saved to " << outputFile << "\n";

    inFile.close();
    outFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./extract_logs YYYY-MM-DD\n";
        return 1;
    }

    std::string logFile = "path/to/large_log_file.log";  
    std::string indexFile = "log_index.txt";
    std::string targetDate = argv[1];

    extractLogs(logFile, indexFile, targetDate);
    return 0;
}
