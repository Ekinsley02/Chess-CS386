# Design


_Group 09 – “UChess!”\
Date: Nov. 10, 2024\
Group Members: Noah Carges, Elliott Kinsley, Tristen Calder, Ryan Todd


## 1. Description


**Provide 1-2 paragraphs to describe your system to help understand the context of your design decisions. You can reuse and update text from the previous deliverables.**


UChess is a desktop chess application that aims to teach beginner and casual chess players to avoid mistakes they are making in order to improve their overall chess strategy skills. Users download UChess on their supported operating system, create an account, and are met with a user-friendly desktop application that allows them to learn or play chess any time with a friend or AI.


UChess is still in development, the application offers a simple user interface, the ability to play local chess games, and will soon offer users the ability to learn chess from an AI Teacher. Ease of use is extremely important for success. We value a simple design that’s easy for everyone to understand, this approach that ensures UChess creates a stress free learning environment for users to experience chess at their own pace.


## 2. Architecture
**Present a diagram of the high-level architecture of your system. Use a UML package diagram to describe the main modules and their interrelation.**


**![](https://cdn.discordapp.com/attachments/1278784448514625651/1305379139276111893/image.png?ex=6732d08f&is=67317f0f&hm=cb3f6deee36669dd2691d6f1b2044ef7b293a96f0f7439317d37ba1b7bae9e28&)**


We designed it this way so we can have a front end interface using python, while using subprocess to use C as a backend. The way we layed out the architecture of this code allows the presentation and main game to remain as separate entity.


## 3. Class Diagram


**Present a refined class diagram of your system, including implementation details such as visibilities, attributes to represent associations, attribute types, return types, parameters, etc.**


**![](https://cdn.discordapp.com/attachments/1278784448514625651/1305295592276230264/image.png?ex=673282c0&is=67313140&hm=db596b80371de1171796106fc83657b6525d073a788467aae65e48ebf5922cf0&)**




## 4. Sequence Diagram


**Present a sequence diagram that represents how the objects in your system interact for a specific use case. Also include the use case's description in this section. The sequence diagram should be consistent with the class diagram and architecture. **

** Use case: The user initiates a new game, and the system sets up the game board. The board updates based on moves made by either the user or the AI, depending on the chosen game mode**


**![](https://cdn.discordapp.com/attachments/1278784448514625651/1305380765172891648/image.png?ex=6732d213&is=67318093&hm=89af5db659d2774481eb95729fff2ef0d763322acc10bf3a0eced78374c56c30&)**


## 5. Design Patterns


**Split this section into two subsections. For each subsection, present a UML class diagram showing the application of a design pattern to your system (a different pattern for each section). Each class diagram should contain only the classes involved in the specific pattern (you don’t need to represent the whole system). You are not limited to design patterns studied in class. You can pick any pattern, including those outside the Gang of Four (GoF) patterns.**


5-1) Pattern Name: MVC Pattern
Inital_Board, Current_Board, Move_Board: https://github.com/Ekinsley02/Chess-CS386/blob/main/main.c
Chess Utility: https://github.com/Ekinsley02/Chess-CS386/blob/main/chessUtility.c


**![](https://cdn.discordapp.com/attachments/1278784448514625651/1305295259659403304/Blank_diagram_-_Page_1.png?ex=67328271&is=673130f1&hm=9c65d7dbc711cb1b7b9b219ad19399ff961622ac4d5bde5243142b6b59893e13&)**


5-2) Pattern Name: Command Pattern
Subproccess https://github.com/Ekinsley02/Chess-CS386/blob/main/SubProcess.py
Python Interface: https://github.com/Ekinsley02/Chess-CS386/blob/main/main.py


**![](https://cdn.discordapp.com/attachments/1278784448514625651/1305296033940766801/Blank_diagram_-_Page_1_1.png?ex=67328329&is=673131a9&hm=0448f2c2a91952ecb8eaea86447863ab9be6083fca240aa73777c2453a6f2535&)**


## 6. Design Principles


**How does your design observe design principles? Provide a short description of the principles followed and concrete examples from your code. Describe at least two principles.**


1. **Modularity**: The design follows modularity by separating different functionalities into distinct files, such as `main.c`, `chessUtility.c`, and `pieceUtility.c`. Each file handles specific parts of the chess application, like game logic and utility functions, which enables easier development, maintenance, and testing.


2. **Encapsulation**: Encapsulation is observed through the use of functions within `chessUtility.c` and `pieceUtility.c`, which contain internal logic and expose only necessary methods to `main.c`. This keeps implementation details private, providing a clear interface for interacting with other components.


For more information, refer to the [project repository](https://github.com/Ekinsley02/Chess-CS386).
