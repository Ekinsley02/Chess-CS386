# UChess: An interactive learning platform for chess

UChess is a desktop chess application that aims to teach beginner and casual chess players to avoid mistakes they are making in order to improve their overall chess strategy skills. Users download UChess on their supported operating system, create an account, and are met with a user-friendly desktop application that allows them to learn or play chess any time with a friend or AI.


## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

Provide a link for the system in production and describe how you are deploying your system. 





### Prerequisites



```
What you need to install to run the software: 
A C compiler (preferably GCC) 
Pygame for visuals 
Powershell or a similar terminal for running commands
```

### Installing

A step by step guide to get a development environment running

Download Zip file from {https://github.com/Ekinsley02/Chess-CS386}

```
1) Go to: UChess GitHub Repository
2) Use the "Code" button and select "Download ZIP" from the dropdown.
3) Select "Download ZIP" from the dropdown menu.
```

Extract the Downloaded ZIP File
```
1) Locate the downloaded ZIP file on your device.
2) Extract it to a preferred location. Remember the installation path for later deployment.

```
Open Windows PowerShell and Navigate to the Project Directory
```
# Change to the directory where the project files are located
cd .\[Specific File Path]\UChess
```

Compile the Source Code Using GCC
```
# Use GCC to compile the main files and create an executable named "chess"
gcc -Wall main.c chessUtility.c pieceUtility.c -o chess
```
```
See demo video below for a example compile and test run
```

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

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

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

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


