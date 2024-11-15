# UChess: An interactive learning platform for chess

UChess is a desktop chess application that aims to teach beginner and casual chess players to avoid mistakes they are making in order to improve their overall chess strategy skills. Users download UChess on their supported operating system, create an account, and are met with a user-friendly desktop application that allows them to learn or play chess any time with a friend or AI.


## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

Project Repository: https://github.com/Ekinsley02/Chess-CS386

### Prerequisites
```
What you need to install to run the software: 
 - A C compiler (preferably GCC) 
 - Pygame for visuals 
 - Powershell or a similar terminal for running commands
```

### Installing UChess
A step by step guide to get a development environment running

Step 1) Download Zip file from {https://github.com/Ekinsley02/Chess-CS386}
```
1) Go to: UChess GitHub Repository
2) Use the "Code" button and select "Download ZIP" from the dropdown.
3) Select "Download ZIP" from the dropdown menu.
```
Step 2) Extract the Downloaded ZIP File
```
1) Locate the downloaded ZIP file on your device.
2) Extract it to a preferred location. Remember the installation path for later deployment.
```
Step 3) Open Windows PowerShell and Navigate to the Project Directory
```
# Change to the directory where the project files are located
cd .\[Specific File Path]\UChess
```

Compile the Source Code Using GCC
```
# Use GCC to compile the main files and create an executable named "chess"
gcc -Wall main.c chessUtility.c pieceUtility.c -o chess
```
See steps below for a example compile and test run

## Running the tests

Explain how to run the automated tests for this system

### Test Script Overview

The test script, `test_output.sh`, automates the testing of the chess application by compiling the code, simulating user moves, and verifying the output against expected results.

1. **Compile the Code**: Uses `gcc` to compile the necessary C files into the executable `chess_output`.
2. **Run the Program**: Starts the chess application and sends initial moves to simulate a game.
3. **Output Comparison**: Captures the program's output and compares it with the expected board layout.
4. **Validation**: Checks if the last line of output is either `0` or `1` to confirm successful execution.

### GitHub Actions Workflow

The following YAML file configures GitHub Actions to automate the testing process on every push or pull request:

```yaml
name: Chess Application Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout repository
        uses: actions/checkout@v2

      - name: Set up Expect environment
        run: |
          sudo apt-get update
          sudo apt-get install -y expect

      - name: Run tests with Expect
        run: |
          chmod +x test_output.sh
          ./test_output.sh | tee test_log.txt  # Capture output for visibility in GitHub logs

      - name: Display Test Log
        run: cat test_log.txt
```

**Screenshot of script running:**
**![](https://i.ibb.co/VVmD5yJ/Screenshot-2024-10-27-205522.png)**

## Deployment

 - Ensure all prerequisites are installed
 - Compile the release build
 - Upload and run on the server or designated platform

## Built With

* [Pygame](https://pygame-web.github.io/wiki/pygbag/) - Graphics and User Interface
* [C](https://www.iso.org/standard/74528.html) - Backend Processing and Executable 
* [MYSQL](https://www.mysql.com/) - Database management 

## Contributing

Please read [CONTRIBUTING.md](https://github.com/Ekinsley02/Chess-CS386/blob/main/project_documentation/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

For the versions releases available, see the ([https://github.com/your/project/tags](https://github.com/Ekinsley02/Chess-CS386/releases/tag/Release)). 

## Authors

* **Elliot Kinsley** - *C Backend* - [Ekinsley02](https://github.com/Ekinsley02)
* **Noah Carges** - *Pygame Implementation* - [strictlyrare](https://github.com/strictlyrare)
* **Trsten Calder** - *Database* - [TristenCalder](https://github.com/TristenCalder)
* **Ryan Todd** - *Deployment / Database* - [r2neatha](https://github.com/r2neatha)




See also the list of [contributors](https://github.com/Ekinsley02/Chess-CS386/blob/main/project_documentation/CONTRIBUTING.md) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/Ekinsley02/Chess-CS386/blob/main/project_documentation/LICENSE) 


## Acknowledgments

* Special thanks to Elliot for being a big contributor to uploading code
* Inspiration came from several open-source chess engines.


