### 1. Description

**Provide 1-2 paragraphs to describe your system to help understand the context of your design decisions. You can reuse and update text from the previous deliverables.**

UChess is a desktop chess application that aims to teach beginner and casual chess players to avoid mistakes they are making in order to improve their overall chess strategy skills. Users download UChess on their supported operating system, create an account, and are met with a user-friendly desktop application that allows them to learn or play chess any time with a friend or AI.

UChess is still in development, the application offers a simple user interface, the ability to play local chess games, and will soon offer users the ability to learn chess from an AI Teacher. Ease of use is extremely important for success. We value a simple design that’s easy for everyone to understand, this approach that ensures UChess creates a stress free learning environment for users to experience chess at their own pace.
### 2. Architecture
**Present a diagram of the high-level architecture of your system. Use a UML package diagram to describe the main modules and their interrelation.**

**![](https://cdn.discordapp.com/attachments/1278784448514625651/1305295683531702392/image.png?ex=673282d6&is=67313156&hm=b23e990d09d67ce1f2afcd25f11614865e5dcbac21519cd722608a134c6f2d5d&)**

We designed it this way so we can have a front end interface using python, while using subprocess to use C as a backend. The way we layed out the architecture of this code allows the presentation and main game to remain as separate entity.

