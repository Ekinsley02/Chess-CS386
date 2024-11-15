### 1. Introduction 

**Provide a short paragraph that describes your system. This paragraph should contain the value proposition and the description of the main features of the software. At the end of the introduction, include links to your project on GitHub and Trello.**

UChess is a desktop chess application that aims to teach beginner and casual chess players to avoid mistakes they are making in order to improve their overall chess strategy skills. Users download UChess on their supported operating system, create an account, and are met with a user-friendly desktop application that allows them to learn or play chess any time with a friend or AI.

UChess is still in early development, the application offers a simple user interface, the ability to play local chess games, and will soon offer users the ability to learn chess from an AI Teacher. Ease of use is extremely important for success. We value a simple design that’s easy for everyone to understand, this approach that ensures UChess creates a stress free learning environment for users to experience chess at their own pace.

Project repo: [https://github.com/Ekinsley02/Chess-CS386)

### 2. Implemented requirements 

**List in this section, the requirements (user stories, issues, or use cases) that you
implemented for this release. We expect that you implement/prototype features you
specified in your MVP (c.f. D.2 Requirements). Include who worked on each of the
features. We expect that all the members of the group have been involved in some
programming activities. BTW, we will check if you are using Trello to manage the
implementation tasks.**

- User story 3: “As a player, I want to move my pieces by clicking so that the gameplay feels intuitive and user-friendly.”
	Issue Link: https://github.com/Ekinsley02/Chess-CS386/issues/4
- Implemented By: Elliott Kinsley
- Approved by: Noah Carges
**![](https://i.ibb.co/T8RPgSt/Screenshot-2024-10-27-200642.png)** 


- User story 7: “As a player, I want the game to highlight valid moves when I select a piece so that I can easily see my options and make better decisions.”
	Issue Link: https://github.com/Ekinsley02/Chess-CS386/issues/12
- Implemented By: Tristen Calder
-  Approved by: Tristen Calder
**![](https://i.ibb.co/hgfb9Pc/Screenshot-2024-10-27-200628.png)** 


 

### 3. Tests 
- Link to github folder containing tests: (https://github.com/Ekinsley02/Chess-CS386/blob/main/test_output.sh)

- Type of test used: 
Script test using github to test output

- What is being tested: 
The output of the initial c board that is initialized with pieces, sides, highlight and game condition information, is being checked to make sure that it fits the necessary subprocess parameters.

**![](https://i.ibb.co/VVmD5yJ/Screenshot-2024-10-27-205522.png)**



### 4. Adopted technologies 

**Include a list of adopted technologies with a brief description and justification for
choosing them.**

**PyGame:**

Pygame is a set of Python modules designed for writing video games. It provides the ability to create 2D games, including graphics, sound, and event handling. We chose Pygame for its simplicity and its integration with Python. Pygame is ideal for creating a visually pleasing and interactive chess board. It allows for smooth rendering of game pieces, animations, and handling user inputs.


**Github:**

GitHub is a platform for hosting code repositories, version control, and collaborative development. GitHub allows easy distribution of the game to users, who can download the latest version directly. We will be using github for collaboration in creating the code. Additionally, github will serve as a homepage for our program allowing users to download directly from our github repository.


**C (Backend Logic)**

We chose C as our backend programming language due to its efficiency and fast response time. It allows direct control over system resources. The use of C provides efficient control over the game logic, move validation, turn management, and rule enforcement. We chose C for its performance capabilities to ensure the game runs smoothly without delays or lag.

**MySQL**

MySQL is a popular database management system that is widely used across many similar applications. It allows for structured data storage and efficient querying. In our system MySQL will be used to manage game data, such as user profiles, game history, and settings. We chose MYSQL for its ability to handle multiple queries and maintain the state of data. This will allow our program to have consistent and reliable storage of game-related information.

**Summary:**

By adopting a combination of Pygame, C, MySQL, and GitHub, we have outlined all of the necessary deployment technologies for our pass-and-play chess game. Our product design is implemented this way to ensure our final product is simple, expandable, and compatible. By integrating Pygame, C, MySQL, and GitHub, each technology is separated and individually implemented, ensuring smooth interaction and easy future upgrades. Pygame and C provide cross-platform compatibility, while MySQL provides reliable data management for game records and user profiles. This approach ensures a lightweight, user-friendly game that we can easily expand with new features without sacrificing performance.




### 5. Learning/training 

**Describe the strategies employed by the team to learn the adopted technologies.**

Our team’s primary learning strategy has been to split the research between different group members according to interests and time available during our weeks. Our original idea was to implement our C and Python programs to make a web application using PyGame and PygBag, but soon found out that the functionality of our program would not work using PygBag because of our C executable needing to be accessed by the sub-processes part of our code. We then got together and divided up research in order to work around the issue, brainstorming different ideas and finding out different ways to implement our program.

When research is needed, 1 or 2 members research together/independently, then during our in person or discord meetings they will educate the rest of the group on what they have found out. Because some people had prior knowledge (Elliott having already had some experience in chess game creation), we were able to cover some topics early on during our weekly meetings.

### 6. Deployment 
**Your system should use containers and Docker. Describe how you are deploying your
system in production. Remember that AWS Educate offers free credits for students. See
the tutorial at https://docker-curriculum.com/ on how to create a container and deploy
it on AWS. Provide a link for the system in production.**

UChess is a standalone desktop application that users can download directly from our GitHub repository. By packaging the application for Windows, macOS, and Linux, we ensure accessibility across major operating systems. To simplify installation, we provide instructions for the user in our README.md file.

### 7. Licensing

**Inform the license you adopted for your source code (remember to configure GitHub
accordingly) and why you adopted this license. For more information, check [https://choosealicense.com/](https://choosealicense.com/) and [http://redhat.slides.com/glikins/open-sourcelicensing-101#/](http://redhat.slides.com/glikins/open-sourcelicensing-101#/)**

**MIT License**

- [MIT license overview](https://choosealicense.com/licenses/mit/) 

- [Our License](https://github.com/Ekinsley02/Chess-CS386/blob/main/project_documentation/LICENSE) 


We chose the MIT License to allow people maximum flexibility with UChess. This license lets others use, modify, and even distribute their own versions of the application, making UChess as accessible as possible for those who want to learn from or contribute to the project.

### 8. Readme File

**You should also prepare your repository for receiving new contributors. See an example
of a Readme.md file at [https://gist.github.com/PurpleBooth/109311bb0361f32d87a2](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
Besides the Readme.md file, your repository should contain a CONTRIBUTING.md
file, a LICENSE file, and a CODE_OF_CONDUCT.md file. Search online for some
examples of these files. In this section of the deliverable, put links to these files on GitHub.**

- [README.md](https://github.com/Ekinsley02/Chess-CS386#)

- [CONTRIBUTING.md](https://github.com/Ekinsley02/Chess-CS386/blob/main/project_documentation/CONTRIBUTING.md) 

- [CODE_OF_CONDUCT.md](https://github.com/Ekinsley02/Chess-CS386/blob/main/project_documentation/CODE_OF_CONDUCT.md) 

- [LICENSE](https://github.com/Ekinsley02/Chess-CS386/blob/main/project_documentation/LICENSE) 


### 9. Look & feel

**Describe the approach you adopted to design your user interface. Include some
Screenshots.**

When we were first trying to figure out how our chess game would look, we thought we should start with a simple design and add customization later. At this point we have focused on the logic behind the game then our user interface. As of now we have a fully functional highlighting system, we thought of the apple chess game when designing the highlighting layout. As for the board pieces, we tried to keep the coloring and design simple for now. We also have the current turn displayed as well in the top right corner.

**![](https://i.ibb.co/H7JJ6xT/Screenshot-2024-10-27-200411.png)** 







### 10. Lessons learned

**In retrospective, describe what your team learned during this first release and what you
are planning to change for the second release.**

As stated previously in section 5, our initial idea of how we were going to implement our program did not work out the way we had planned. However, we learned that we could easily create our program as a desktop application that the user can install on their own devices. As we transitioned to a desktop application, we realized that this approach offered much more flexibility for integrating our C backend and Python front-end components. We learned the importance of adaptability, as shifting our deployment method allowed us to continue to use our code without compromising on core features. Additionally, this process made us aware of the need for testing strategies and effective team collaboration. Moving forward, we plan to enhance our automated testing, refine the user interface, and explore more feature expansions that leverage the strengths of the desktop deployment.




### 11. Demo

**Include a link to a video showing the system working.**

Demo Link - [https://nau.zoom.us/rec/share/lw_x5hs4tgP5nnKYqEH1ccWzGr5eazTbMiOsE0rM-Xcpam7rXduUdK89Hb_QJa0N.Zr6XsjXMVRh-1CnP?startTime=1730084240000)
