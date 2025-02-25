Before extracting logs, we preprocess the log file and create an index.
This index will store:

The date (YYYY-MM-DD)
The exact byte position in the file where that date's logs start

Now, instead of scanning the whole log file, we read the index file and jump directly to the required date’s logs.

Indexing allows fast jumping to logs, reducing search time from hours to seconds
Only reads necessary parts of the file, keeping memory usage low
Works efficiently even for 1TB log files

This method is production-ready and can handle massive log files efficiently! 
