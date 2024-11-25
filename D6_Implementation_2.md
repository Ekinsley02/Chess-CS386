## 1. Introduction
Our system is a desktop chess application that uses a wide variety of technologies from C for the backend to Python/PyGame for the graphics to SQLite databases hosted in the cloud for data storage. The system has a graphical user interface where the user can select between pass-and-play functionality as well as some other game modes that are potentially coming soon such as cloud gaming and an AI teacher for people who don't know how to play chess.  
The system is snappy and responsive due to much of the game logic being written in C. The game runs at a consistent 60 frames per second while using minimum system resources so it can be played on slower systems without a problem.

[GitHub Repository Link](https://github.com/Ekinsley02/Chess-CS386)

## 2. Implemented Requirements

## 2.a
**Requirement:** As a player, I want to play a game of chess against another player so that I can enjoy a competitive match
Requirement: As a player, I want to play a game of chess against another player so that I can enjoy a competitive match

**Issue:**
https://github.com/Ekinsley02/Chess-CS386/issues/2

**Pull request:**
https://github.com/Ekinsley02/Chess-CS386/pull/52

**Implemented by:**
Noah Carges

**Approved by:**
Tristen Calder

**Print screen:**

![UI](https://media.discordapp.net/attachments/1278784448514625651/1310473363256508476/image.png?ex=674558ed&is=6744076d&hm=5de26364839df3670a38cd1e54676caaaf421ce85fbccd0eeab2721c14fd9419&=&format=webp&quality=lossless&width=891&height=920)

## 2.b
**Requirement:** As a player I want to be able to create my own account and be able to login to see my past games
Requirement: As a player I want to be able to create my own account and be able to login to see my past games

**Issue:**
https://github.com/Ekinsley02/Chess-CS386/issues/62

**Pull request:**
https://github.com/Ekinsley02/Chess-CS386/pull/61

**Implemented by:**
Ryan Todd

**Approved by:**
Tristen Calder

**Print screen:**

![Account Login](https://media.discordapp.net/attachments/1278784448514625651/1310473530130956318/image.png?ex=67455915&is=67440795&hm=dc20929001c2652eab7aa4107c6c1f6043c88a73aed2ec29ed0a45f9fc1de74c&=&format=webp&quality=lossless&width=1440&height=765)

## 2.c
Requirement: “As a player, I want the chessboard and UI to be visually appealing so that I have an enjoyable and engaging experience while playing.”

**Issue:** https://github.com/Ekinsley02/Chess-CS386/issues/15

*Issue:**
https://github.com/Ekinsley02/Chess-CS386/issues/15

**Pull request:**
https://github.com/Ekinsley02/Chess-CS386/pull/58

**Implemented by:**
Elliot Kinsley

**Approved by:**
Tristen Calder

**Print screen:**

![Chessboard](https://media.discordapp.net/attachments/1278784448514625651/1310473648921903146/image.png?ex=67455931&is=674407b1&hm=6e7e485d046851159ded5a1d64ea2718422278fac6f6a39356cde2f524ebcfa8&=&format=webp&quality=lossless&width=886&height=920)

## 2.d
Requirement: “ In terms of technology, the only requirement is to adopt a client-server architecture and use a database system. You need some server-side code and data storage”

**Issue:** https://github.com/Ekinsley02/Chess-CS386/issues/63

**Pull request:** https://github.com/Ekinsley02/Chess-CS386/pull/67

**Implemented by:** Tristen Calder

**Approved by:** Tristen Calder

**Print screen:**

![Server-side Architecture](https://media.discordapp.net/attachments/1278784448514625651/1310473725618950144/image.png?ex=67455943&is=674407c3&hm=6f32ac9577b1c424ba8e6380f32985678dd68652d9b49bb75b6f69a2b0886f13&=&format=webp&quality=lossless&width=1144&height=287)


## 3. Tests

### 3.1 Unit Tests
A unit test is an automated test that aims to verify the behavior of a component isolated from the rest of the system. For this deliverable, show an example of a unit test that uses mock objects to isolate the class from the rest of the system.

- Test framework you used to develop your tests (e.g., JUnit, unittest, pytest, etc.)
    - unittest

- Link to your GitHub folder where your automated unit tests are located
    - [Workflow Folder] (https://github.com/Ekinsley02/Chess-CS386/tree/main/.github/workflows)
    - [Test Folder](https://github.com/Ekinsley02/Chess-CS386/blob/main/tests)

- An example of a test case that makes use of mock objects. Include in your answer a GitHub link to the class being tested and to the test
    - [Castling test] (https://github.com/Ekinsley02/Chess-CS386/blob/main/tests/test_castling.py)
    - This script is a unit test that uses unittest to automate the testing of queenside castling in a chess engine. It initializes a chess engine, simulates a series of moves leading up to a castling maneuver, and verifies the correct execution of each move. The script checks for proper piece selection, movement validation, and ensures the chess engine's board state matches expected results.


- A screenshot showing the result of the unit test execution
![Unit Test Execution Result](https://gcdnb.pbrd.co/images/Bb8YG5lM169a.png?o=1)
    - The current tests are not correct, however, the program works. Will be updated.

### 3.2 Acceptance Tests
An acceptance test is a test that verifies the correct implementation of a feature from the user interface perspective. An acceptance test is a black box test (the system is tested without knowledge about its internal implementation). Provide the following information:

- Test framework you used to develop your tests (e.g., Selenium, Katalon Studio, Espresso2, Cucumber, etc.)
    - pyautogui

- Link to your GitHub folder where your automated acceptance tests are located
    - [Workflow Folder] (https://github.com/Ekinsley02/Chess-CS386/tree/main/.github/workflows)
    - [Test Folder] (https://github.com/Ekinsley02/Chess-CS386/blob/main/automated_tests)

- An example of an acceptance test. Include a GitHub link to the test and an explanation about the tested feature in your answer.
    - [Acceptance Test] (https://github.com/strictlyrare/Chess-CS386/blob/main/acceptance_tests/test_user_login.py)
    - This Python script uses unittest and pyautogui to automate testing of a user login feature in a Pygame application. It interacts with the login GUI by simulating mouse clicks and keyboard input for both valid and invalid login attempts, ensuring the application handles these correctly. The script manages the Pygame application as a subprocess and checks if it continues to run or exits unexpectedly during the tests.


- A screenshot/video showing the acceptance test execution
![Acceptance Test Execution Result](https://gcdnb.pbrd.co/images/YlvLmQN7Rlzz.png?o=1)

## 4. Demo
Include a link to a video showing the system working.  
[Video Demo](https://youtu.be/jKw09Ix0Jyk)

## 5. Code Quality
Describe how your team managed code quality. What were your policies, conventions, adopted best practices, etc., to foster high-quality code?

Our team managed code quality by commenting all code in a way that would make sense to someone that didn't work on that section of code. We attempted to keep the comments descriptive to the point where you could hit ctrl+F and search by comment if you were looking for some code. To do that we made sure to have obvious keywords in the comments and have them spelled correctly.

We also made sure to adhere to a rigid code review process where manual checks would be run by the group leaders, Elliott and Noah who pushed everybody’s code to the GitHub where it was reviewed by someone else to ensure we have multiple people looking over all code. In addition to automatic tests, manual checks were also run on the code, mainly by playing the chess game to ensure it worked as expected.

## 6. Lessons Learned
In retrospect, describe what your team learned during this second release and what you would change if you would continue developing the project.

The main thing we learned is we always want to keep adding on to our project. Everytime we write code we come up with new ideas on how to make the project better and add more features. We also learned throughout the semester that Discord calls where we can just chat about what we are working on without waiting for a text reply boosts productivity massively. Being able to share your screen, explain the code you just wrote and ask for feedback is massively valuable for team collaboration.


