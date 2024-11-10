### 1. Description

**Provide 1-2 paragraphs to describe your system to help understand the context of your design decisions. You can reuse and update text from the previous deliverables.**

UChess is a desktop chess application that aims to teach beginner and casual chess players to avoid mistakes they are making in order to improve their overall chess strategy skills. Users download UChess on their supported operating system, create an account, and are met with a user-friendly desktop application that allows them to learn or play chess any time with a friend or AI.

UChess is still in development, the application offers a simple user interface, the ability to play local chess games, and will soon offer users the ability to learn chess from an AI Teacher. Ease of use is extremely important for success. We value a simple design that’s easy for everyone to understand, this approach that ensures UChess creates a stress free learning environment for users to experience chess at their own pace.
### 2. Architecture
**Present a diagram of the high-level architecture of your system. Use a UML package diagram to describe the main modules and their interrelation.**

**![](https://cdn.discordapp.com/attachments/1278784448514625651/1305295683531702392/image.png?ex=673282d6&is=67313156&hm=b23e990d09d67ce1f2afcd25f11614865e5dcbac21519cd722608a134c6f2d5d&)**

We designed it this way so we can have a front end interface using python, while using subprocess to use C as a backend. The way we layed out the architecture of this code allows the presentation and main game to remain as separate entity.

### 3. Class Diagram

**Present a refined class diagram of your system, including implementation details such as visibilities, attributes to represent associations, attribute types, return types, parameters, etc.**

**![](https://cdn.discordapp.com/attachments/1278784448514625651/1305295592276230264/image.png?ex=673282c0&is=67313140&hm=db596b80371de1171796106fc83657b6525d073a788467aae65e48ebf5922cf0&)**


### 4. Sequence Diagram

**Present a sequence diagram that represents how the objects in your system interact for a specific use case. Also include the use case's description in this section. The sequence diagram should be consistent with the class diagram and architecture. **

**![](https://cdn.discordapp.com/attachments/1278784448514625651/1305295683267596348/Screenshot_2024-11-10_142707.png?ex=673282d6&is=67313156&hm=c4c02c485dcc7bc48a2f6aa0077806070cee345b6ef4313a9d48a45d0ea24231&)**
