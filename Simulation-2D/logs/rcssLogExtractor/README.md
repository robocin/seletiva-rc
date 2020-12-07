# Log Extractor Manual

The log extractor can be found in _./bin/rcssLogExtractor_ for Linux and _./bin/rcssLogExtractor.bat_ for Windows.

## Installation

    $ sudo apt install openjdk-11-jdk-headless

## Usage

    $ cd ./bin
    $ ./rcssLogExtractor --in <PATH_TO_LOG_DIRECTORY> --out <PATH_TO_OUTPUT_DIRECTORY>

If no output directory is given, the output will appear in the default path.

    $ ./rcssLogExtractor  # Extract all .rcg files in current directory to .rcg.csv

For more informations use:

    $ ./rcssLogExtractor -h
or 

    $ ./rcssLogExtractor --help

---



