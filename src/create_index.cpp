#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

void createIndex(const std::string& logFile, const std::string& indexFile) {
    std::ifstream inFile(logFile);
    if (!inFile) {
        std::cerr << "Error: Cannot open log file.\n";
        return;
    }

    std::ofstream outFile(indexFile);
    if (!outFile) {
        std::cerr << "Error: Cannot create index file.\n";
        return;
    }

    std::unordered_map<std::string, std::streampos> index;
    std::string line;
    std::streampos position = inFile.tellg();  

    while (std::getline(inFile, line)) {
        std::string date = line.substr(0, 10);  
        if (index.find(date) == index.end()) {
            index[date] = position;
            outFile << date << " " << position << "\n";  
        }
        position = inFile.tellg();
    }

    std::cout << "Index file created \n";
    inFile.close();
    outFile.close();
}

int main() {
    std::string logFile = "path/to/large_log_file.log";  
    std::string indexFile = "log_index.txt";
    createIndex(logFile, indexFile);
    return 0;
}
