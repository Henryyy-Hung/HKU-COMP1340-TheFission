# **Proposal on The Fission**

Author: Hung Ka Hing  

## **0. Annotation from Developers**

### **0.1 Game demonstration**

https://drive.google.com/file/d/1YvInbssXRoN5IQSVp3k-D905KWejQ9iA/view?usp=sharing


### **0.2 Quick Start**

  Environment: Linux terminal
 
  Execution Instruction: execute “./start.sh” in root dictionary of the repo

    
## **1.Introduction of Game**

### **1 Introduction of Game Type**

  The proposed game, "The Fission", is an "open-world" adventure RPG game. The player could enjoy the fun of battle, survive, explore, and storyline.  Not only does it uses traditional turn-based combat, but it also extends the battlefield from 1D to 2D. The background and four significant elements will be introduced in the following section.
  
### **1.2 Introduction of Game Background**

  The storyline is set in a post-war period. The hydrogen bomb was applied during World War IV. Eventually, the world is full of corpses and radiation. One day, a mutated virus is derived from the corpse and hide in the refugee's body. Soon, the virus spread to all the continents. At the "Black Christmas", the virus outbreaks. All the virus carriers, including humans and animals, are mutated into aggressive monsters. Since all the resources were inputted into the war, humans failed to defeat the virus. As a result, 80% of humans were "converted", the remaining survivor then follow the army and escape to the sanctuary. As everything was derived from the fission, the year next was named T.F. 00.
  
  A year after the "Black Christmas". The character and the non-player character, Amy, wake up from the dormancy device. As a participant of human hibernation, they are needed to escape from the laboratory and run to the sanctuary. In order to back to human society, characters are going to travel through the city ruins and wasteland and facing the challenge of food resources and attack from monsters. During this journey, characters are also going to experience a series of stories and make their choice. All the choices will affect the ending of the story.
  
## **2 Rules of the Game**

### **2.1 Rules of Battle**

#### **2.1.1 Player-related Rules**

  The fundamental mechanism of battle is turn-based combat on a 7 x 5 2D battlefield. The player is able to make two commands during his round. These commands can be moving, attacking, using an item, and escaping from the combat. The details and validity of such command will be mentioned in the following paragraph, respectively. When the command is invalid, the player can re-enter his command.

  Firstly, regarding the mechanism of moving. Basically, the player can use w/a/s/d to move in up, left, down, right directions, respectively. There are two situations of invalid moving, which are zero Stamina Point of player and encountering obstacles on the battlefield. On the one hand, the player cannot move when the stamina point becomes zero. On the other hand, players cannot pass through obstacles on the battlefields, including monsters and the 9 x 7 wall that surrounding the battlefield.
  
  Secondly, regarding the mechanism of attacking, the attack damage of the player is base on the player's Attack Point and distance between player and monster. When a player attacks, an area of effect (AOE) is produced, and all the monsters on the battlefield will be attacked. However, the valid attack damage suffered by each monster is base on the following formula: Attack Point/distance^2. That is, the valid attack damage drops exponentially with a longer distance. If and only if no valid attack damage is done on any monster, the attack will be invalid.
  
  Thirdly, regarding the mechanism of using of items. The player can enter the bag page to use restorative items he collected during exploring. The player can only use 1 item when consuming one command. If the player quits the bag page without using any item, a valid command will not be counted.
  
  Fourthly, regarding the mechanism of escaping from combat, the player can have a 34% chance to escape from combat. Regardless of the success or failure of escaping, all escape commands will be counted as one valid command.
 
#### **2.1.2 Monster-related Rules**

  Firstly, regarding the number of monsters on the battlefield, it is a random number from 1 to 10—however, the chance of encountering more monster at same time drop exponentially.
  
  Secondly, regarding the location of monsters, they are randomly allocated within the 7 x 5 battlefields. Each grid of battlefield can only have either one monster or one player. That is, monsters will be randomly allocated to different grids on the battlefield.
  
  Third, regarding the Health Point and Attack Point of the monster, it is randomly generated from 30 to 99 and from 10 to 30, respectively.
  
  Fourthly, each monster also has two commands in each round. They can either move or attack. The mechanism of its move and attack is the same as that of the player.
  
#### **2.1.3 Outcome-related Rules**

  Once the player kills all monsters within the battlefield, the player wins; if the player's Health Point drops to zero, the player losses.
  
  If the player wins, he will get an item - "meat", which is a restorative item in the game. The quantity of "meat" positively related to the number of monsters that the player encountered.
  
#### **2.1.4 Summerize**
  
  In a word, the core of battle is to survive during combat, make damage on monsters as much as possible, keep distance with the monster during their round to diminish the loss of HP, and escape when the situation is not optimistic.
  
### **2.2 Rules of Survival**

  Character status is the survival parameter of the game. It includes three inter-related parameters: Healthy Point(HP), Stamina Point(SP), Hunger Point(Hr). Health Point determines the continuity of the game. When a player's HP becomes zero, the game is over. Stamina Point is needed for moving of character. Hunger Point is related to "starving," which induces drop-in Health Point and Stamina Point. There are four major factors of changing character status.
  
  Firstly, time is one of the factors. When time passed by, the Hunger point will gradually increase. When Hunger Point increased to 100%, the character is starving. The further pass of time under starving causes a drop in Stamina Point and Health Point. Time is passed by during the moving and resting of the player.
  
  Secondly, the character's action is also one of the factors. When the player chooses to "rest" in the main menu, time will pass by while HP and SP will recover a bit. When the player chooses to "move" in either exploring or battle, time pass by, and SP will be consumed.
  
  Thirdly, using of items is also one of the factors. By exploration and battle, the player can collect restorative items. Each item may have both positive effects and side effects. The use of these items can modify the character status. For example, when players use "radiated meat", there will be an effect that decreases in both Hr and HP.
  
  Fourthly, the battle is also one of the factors. When attacked by monsters, HP will decrease according to the formula mentioned in the previous section.
  
  In a word, the core of survival is to allocate the action of character wisely, use items wisely and combat with monsters only when necessary.

### **2.3 Rules of Exploring**

  Player can make commands during exploring on the world map, including "move", "rest", "bag", "navigator", "save", "manual" and "quit".
  
  For the moving command, the player can move horizontally or vertically on the world map. During moving, the player may encounter different buildings, battles, and events. (1) When encountered with buildings, the player will have random chances to obtain different restorative items, which will be further discussed in the game feature part. (2) When encountered with monsters, the player will enter the battlefield with is based on the world map, which will be further discussed in the game feature. (3) When encountered with events, the story will be trigger out, which will be further discussed in the following part. (4) When an encounter with the event (maze), a random maze will be generated and trap the player. Each event or building can only be trigger out once.
  
  For the "rest" command, it has been mentioned in 2.2. 
  
  For the "bag" command, the player can enter the bag interface and use different restorative items. This will be further discussed in the game feature part.
  
  For the "navigator" command, the player can obtain the direction and distance to 
  
  For the "save" command, the player can export the player's profile, which is the game status, to an external file.
  
  For the "manual" command, the player can enter the manual page and read the instruction.
  
  For the "quit" command, the player can quit the game.
  
### **2.4 Rules of Storyline**

  Players can experience a story within the game. Basically, the player needs to use the Navigator to go to the target position, where triggers out story event. In the storyline, there are three themes: Find the human city, protect the NPC - Amy, and daily life in the wasteland.

  In the story, every decision of the player will determine where the story goes. For example, the player may need to decide whether they would save a thief they meet in the wasteland. If yes, the thief may steal all the food of the character, and Amy will die due to lack of food.
  
  By the way, one developer is called Amy, "I'm so sad. 555555" :(

## **3 Game Features and mechanism**

  All the required code implementation will be in the next part, which is section 4. We apologize for the separation between feature and implementation. However, we have too many features and if we put the features and implementations together, the readability of the proposal will be critically low. Since there are too many features in our game, **we just select the most important features to emphasize**. Some important but not special feature like **moving** won't be introduce here.
  
### **3.1 Dynamic User Interface**

  The user interface is the feature responsible for input and output, displaying the visualized game on the terminal and receiving the user input from the terminal. There will be three regions for display: status interface, main interface, and text interface, respectively. For user input, there will be only one region - the user input line. 

  The status interface, main interface, text interface, and user input line are arranged in a top-down manner. The detail about the three interfaces and user input lines will be discussed later. The update of the interface is based on the command from the user. Once the function received user input and processed the datum, the interface will be updated automatically. Thus, it is expected to provide an interactive interface to the user.
  
  Regarding the Status Interface, it is mainly for displaying instantaneous character-related information. It could display the Health Point, Stamina Point, and Hunger Point in a percentage manner and a visualized bar manner. Besides, it could numerically display the Attack Point.

  Regarding the Main Interface, it is mainly for displaying instantaneous game content. It could display the map with different buildings (i.e., explorable buildings, maze, battlefields, and etc.), different ASCII art logo (i.e., "Fission," "Win", "Story", and etc.), the manual page (i.e., rules), and the bag interface (i.e., an instantaneous quantity of belongings and their attributes). For further information, please refer to "interface. cpp".
  
  Regarding the Text User Interface, it is mainly for displaying text-based information. With its sub-functions, it could separate the lines by the last space in the line(i.e., "Hello \n World" instead of "Hell \n oWorld"), allocate 3 string into 3 lines, or allocate 4 strings into 4 equal grids on a line. We can say that the Text User Interface is a fully functional text formatter! Regarding the content, it would display manipulation instruction(e.g., how to move), instantaneous information(e.g., direction, location, target location, distance, information of monster and etc.), notification(e.g., starving, low SP, invalid input, and etc.) and story content. We have done a lot of sub-functions for the text user interface. For further information, please refer to the code at "interface.cpp".
 
 Regarding the User Input line, it is mainly for Receiving the input from the user and pass to the processor functions. It could receive the input char without pressing "Enter". That is, accompanied by the refresh() function, it could refresh all the interface to show the instantaneous content once the user makes a command. To declare, the same function could be achieved by our original code, but it needs pressing "Enter". To facilitate the user experience, we decide to implement the code from the internet to avoid pressing the "Enter" button. Here is the only part we refer to other's work. The non-original part is around 10 / 3000+ lines, that is, less than 1%. We will cite the reference at the end of the file.

  Regarding the refresh of the interface, it is base on while loop and print interfaces repeatedly. You may use the stop-motion animation as a reference. This is how the game achieves the dynamic visual effect. For example, like **Moving** Hope it could bring surprise to our user. For further information, please refer to code at "interface.cpp" and "main.cpp".

### **3.2 Data Storage and Loading**  

  To provide continuity of gaming experience, temporary and permanent data storage are necessary. The former offers instantaneous game continuity during the game, while the latter offers long-term continuity when exiting the game.

  Permanent data storage is manual storage that refreshes only if the specific user command is received. During this process, all the character-related data, including status (HP, SP, Hr, ATK), time, location, story progress, belongings, will be exported to an external file and will have permanent storage. Obviously, this external file could be load into the game if the user wants. The save and load commands are 'z' and 'l', respectively. The former could only be applied during exploring. The latter could only be used during the initiating of the game.

  Temporary data storage is automatic storage that refreshes whenever the user makes a command. Apart from character-related datum, it also stores the 2D dynamic int array map, the tree structure of storyline in a divergent linked list, the dynamic array of monster information, and all the datum that "Initiate only when necessary".

### **3.3 Data Processing** 
  
  As we know, all the content displayed on the screen is based on continuously updated data. Therefore, we can conclude that all the displayed game content is actually regarding "Data Processing". With collective data processing functions, a different game feature can be created. 
  In the following section, we would discuss the game-content-related features conclusively and conceptually and briefly introduce their mechanism.

#### **3.3.1 Survival - Simulation of Real World in Physical Parameter**

  Players could experience the physical parameter like the real world in the game. This part integrates many other functions, but we just combine all of them for your reading experience. In general, such simulation provides a sense of nervousness to the player. The following paragraph will discuss the time, spatial, and biological-related parameter simulation.

  Regarding the time-related parameter simulation. From sections 2.2, we could know that character's actions will cause the physical parameter – time – to pass by. With the time passed by and the actions the character has done, the character's status varies. For example, the moving causes drop in Stamina Point, the resting causes recover in Health Point and Stamina Point, and the starving causes in drop-in Health Point. Thus, we can see an interactive relationship between the character and the world in the game. Base on this interactive relationship, we adjust all the parameters to fit the real-world situation. For instance, the maximum distance the character can move is 50km per day in the game. The character must rest when stamina point is used up, walk for 1 day will induce starving status, etc. All the above features are simulating the time-related physical parameter.

  Apart from simulating the time-related parameter, we also simulate spatial-related parameters. In the game, the character is allowed to move in any direction and have an infinite world to travel, which will be discussed later. However, when encountering a wall, obstacles, or non-player characters like monsters, the player could not move across them as they have a solid body. Thus, the player could experience the spatial-related parameter limitation in the game.

  Last, the game also simulates the biological parameters. Apart from the biological limitations mentioned in time-related parameters, all the settings won't break the real-world limitation. For example, the monster's attributes are always in a reasonable range, the food and drug item from the bag can recover the character's status. 

  In conclusion, our game tries to simulate a real-world for our players with the inter-related update of different data. For further information, please refer to main.cpp, survival.cpp (time & biological) and explore.cpp (spatial).

#### **3.3.2 Explore - Map with Random Distribution and Extendable Size**

  The player could enjoy an entirely random and almost infinite map during exploration in our game. Basically, the map is formed by a 2D dynamic int array. It is initiated with an initial size of 64 x 64. Different buildings (resources), events (monster and maze), and stories are randomly allocated on the different map grid. Some of them will be displayed by the interface, some will not. For example, the monsters and maze triggerer won't be shown. This could increase the fun and excitement of the game.

  Regarding the randomness of the map. The map is formed by different int. Each map[x][y] contains a int value. Different int values represent different buildings or events. For instance, 1 is an unknown building, 2 is a water source, 3 is a hospital. During initiation, each map[x][y] will be randomly allocated with an int value, for example, 69% chance to have nothing (0), 10% chance to have a monster (10), 1% chance to have maze (11) on that grid. By such a method, we create a map randomly distributed with different events. When the corresponding coordinate of the player on the map contains an event, it will be triggered out. This will be further discussed in the following section.

  Regarding the extendable feature of the map. As mentioned, we are not sure how much map the player wants to explore; therefore, whenever the player enters or re-enter the game, the game will only initiate a 64 x 64 dynamic 2d int array. If the player walks close to the boundary of the original map, say, less than 20 units from the boundary, the map will extend. This extension is basically initializing a new map with doubled side length and random allocated events, then copying the values in the original map to the new map, and deleting the original map, and pointing the pointer to the new map. To minimize the delay brought by the copying process, we will reset the player's location to be the center of the new map and copy the original map correspondingly. By this, the distance between the player and boundary could be maximized whenever the map is refresh. Thus the chance of refresh will be minimized. Due to the limitation of the int type, the maximum size of the map is 2^(32) x 2^(32) square units. However, this could be solved easily by re-entering the game to refresh the map. To conclude, in a single game time, the minimum distance needs to approach the map boundary is 4,294,966,712 steps; by saving and re-enter the game, the map is infinitive!

  Regarding the read, write for the map, the map can be written with an obstacle (998) and then form a maze on the map. Or it can be registered with a wall (999) to create the battlefield or wall at 2^(32) boundary. Also, the map could be read by the main interface to display the map content on the screen with different representations. These will be further discussed in the later sections.

  In conclusion, this feature try to create an open world that full of myth for the player to explore. And the algorithm mentioned try to facilitate the game experience. For further information, please refer to explore.cpp.

#### **3.3.3 Explore - Random Maze**

  As mentioned above, the player has a chance to encounter the random maze. Once the maze is triggered, a 31 x 31 maze centered at the player will be generated on the world map. The exit of the maze will be in the bottom-left and top-right corner. The density of resources (buildings) inside the labyrinth is two times that of outside. Besides, there is no monster in the maze.

  Apart from the basic properties of the maze, this part will focus on the algorism of generating a random maze. Basically, the maze is generated by breaking walls between nodes in a random direction with recursive algorism. That is, develop the path of the maze in a random direction until the boundary of the maze, and then develop another path from the previous node if possible. If not, use the previous node of the previous node to develop. It is hard to explain the concept by verbal description. You may imagine it as a tree structure with main branches and sub-branches. Please refer to the code at explore.cpp for a clearer understanding. To declare, the code of maze algorism is 100% original. Since the path could be developed in 4 directions with random sequence, like down, left, upright, there is an uncountable combination of maze path could be formed. 

  In conclusion, every maze that the player encountered is brand new to him to a certain extent. Besides, as the interface could only display part of the maze, it provides a sense of immersion.

#### **3.3.4 Explore - Random Resources from Buildings**

  As mentioned in 3.3.2, the distribution of buildings is totally random. To further increase the randomness and fun feature of the game, each type of building may produce different kinds of resources, some with side effects, some without side effects. The chance of getting a specific type of resource is entirely random again. For instance, when encountering a water source, there is an 80% chance to get radiated water with side effects and only a 20% chance to get pure water.

  This feature could further provide fun to our players.

#### **3.3.5 Explore – Game Items**

  As mentioned in 2.1 and 2.2, there are different game items in the game and can be obtained by defeating the monster or explore the buildings. Each item has either 1 or 2 effects. Effects can be a negative or positive effect. After using the item, some funny annotations from the developer will be shown in the chatbox. For instance, the player will see "Woohoo ! You feel like superman !" after drinking the radiated water and increasing SP and decreased HP. Please investigate it in the game. It will be messy if we write all the content of items here.

  The items could be used by entering the bag page, which has been introduced in section 3.1. To re-emphasize, the bag page can show the instantaneous quantity and attributes of different items. And it can allow the user to use items. By pressing "0-8" according to instructions, items can be used.

  The side effects of items increase the game's difficulty and boost the complexity of the game.

#### **3.3.6 Battle – Battlefield Generation and Recovery**

  A battlefield with 7 x 5 will be generated centered at players' location on the world map when the player encounters a monster(s). After the generation, all the elements (int values) within the range of the battlefield will be reset to 0 (nothing), and the 7 x 5 battlefield will be surrounded by a wall.

  After the battle (win or escape), the battlefield will be erased and recover all the original elements in the world map stored in a dynamic 2D int array before battlefield generation.

  To conclude, the battlefield provides the player with an enclosed environment without interference to battle. Besides, it won't change the original landform of the map. Therefore, it could provide a sense of immersion to players.

#### **3.3.7 Battle – Random Monster Generation**

  After encountered the event of a monster attack on the map, monsters will also be generated. As the quantity, health point, attack point of monster(s), and location are all random. Therefore, the information of monster(s) is stored in a Monster type dynamic 1D array according to the quantity of monster appears. 

  By algorithms, we set the chance of more monsters to appear at one time to decrease exponentially. This could avoid the bad game experience that was suddenly killed by 10 monsters. Besides, another algorithm is applied to avoid overlapping of the position of monsters on the battlefield. Furthermore, the monster(s) will be labeled by their HP on the map.

  In conclusion, we generate the monster within a reasonable range to provide a moderate game difficulty. For sure, if the player wants some challenge, he can choose not to escape when encountered with 10 monsters.

#### **3.3.8 Battle – Simulation of Monster in Real World**

  To provide a more vivid experience to our player, we adjust the algorithm of the monster to behave more like a real organism. By the algorithm, although there is still a random component of monsters' behavior, they would perform chase and attack like a zombie. To simplify, the monster will chase the player no matter there is an obstacle or not. If there is an obstacle or the player is in a suitable range of attack, the monster will start to attack the player. Of course, the single monster is never a problem. However, when multiple monsters chase the character and attack, it is pretty hard to survive without some strategies.

#### **3.3.9 Story – Choice dependent Storyline**

  To provide an interactive experience when users read our story, they can choose after each story section. For instance, there are choices 1 or choice 2. Their choice will then affect what the next story is. For instance 1->11 / 2->3.

  We use divergent linked lists to build the storyline. Each story node stores an id and a location. The id is consecutive, and the location is always within 40 units around the previous story triggering location by random allocation. Only if both story id matches the story and the player's location fit with triggering location will the story display be triggered. Players can use the Navigator in the main interface to found the direction and walk to the triggering location of the next story. 

  To facilitate the storyline building, we simulate the master branch, branch, and merge of the Github. Furthermore, we create our own tools – extend, link and search. By applying these tools, we could develop the storyline directly, link one story module to the other in the master branch, and search the pointer of the story module with a specific id. Please refer to story.cpp for further information.

#### **3.3.10 Story – Read Story from External File**

  The story's display is based on the script we prepared in an external file, "story.txt". Regardless of the user experience, this is just for efficient writing of the story. Our program will search for the starting command for a specific story node, which is "#id start," and display the following storyline by line until the "#end" is detected. If there is "#id choice", the program will display 2 options under the command and allow users to choose. And to determine the development of the story.

## **4 Code Requirement Implementation**

### **4.1 Generation of random game sets or events**

  The following are the feature we apply the random to support. The method will be discussed later.

1.	The world map is randomly distributed with buildings, monsters, maze event (from section 3.3.2)
2.	The generation of the path in the maze are random (from section 3.3.3)
3.	The type of resource generated from buildings are random (from section 3.3.4)
4.	The attribute and locations of monsters are randomly generated, and the number of monsters. (from section 3.3.7)
5.	The behavior of monsters are partial random (from section 3.3.8)
6.	The randomly allocated story triggering locations (from section 3.3.9)

  For 1 3 4 5 6, we use rand()%number to simulate probability or generate random location. For 2, we use vector<char> {……} with random_shuffle(begin(), end()) to create a random sequence of direction for developing the maze.

### **4.2 Data structures for storing game status**

  There is totally 7 self-defined structure in our game for storing game status. They will be introduced one by one.

  First, the structure **Point** can store the x and y coordinate on the 2D surface. It is mainly for recording the location of the player, monster, and triggering location of stories. Thus it supports map function and the general exploration system.

  Secondly, the structure **Time** can store the hour and mins of 24-hour time. It is mainly for simulating the time parameter of the real world and providing an anchor for updating the user status. For example, the change in HP, SP, Hr are all base on time passed. Thus, it supports the features like simulating the physical parameter in the game.

  Thirdly, the structure **Status** can store the quantity of the status like HP, SP, Hr. It is mainly for recording the user status. 

  The above 3 structures are mainly sub-structure of other structures. Therefore, we build functions inside it. There are two standard functions, set and change. The set is primarily for setting the value more intuitively, and the change is to change the value according to the specific carrying system of the particular structure. For instance, the 60 mins add 1 hour. 

  Fourthly, the structure **Item** can hold the information of game items. It is mainly for support of the overall surviving and exploring system, especially for the bag sub-system. The developer can define a game item more efficiently and display the item's attribute on the screen more easily with the structure.

  Fifthly, the structure **Profile** holds all the player's information, including Time, Status HP, SP, Hr, destiny, attack point, and the number of belongings. It supports data storage regarding player and save and load function by facilitating reading and writing.

 Sixthly, the structure **Monster** holds the location, HP, and attack point of the monster. It supports the battle and monster feature.

 Seventhly, the structure **Node** holds the id and triggering location (Point) of a story segment., and 2 pointer points to 2 branches of 2 other story nodes. It can be used to build a divergent linked list and support the branch storyline development.

### **4.3 Dynamic memory management**

  There are mainly 3 sites of dynamic structure application: 2D dynamic int array map, 1D dynamic **Monster** array list, divergent linked list. As some of the other implements are not of vital importance, they won't be mention here.

  For the map, the dynamic feature allows it to extend only when necessary. This could be achieved by copying the old one to a new large map, deleting the old map, and pointing the pointer to a new map. For details of how it supports the game feature map, please refer back to section 3.3.2.

From 3.3.2:
Regarding the extendable feature of the map. As mentioned, we are not sure how much map the player wants to explore; therefore, whenever the player enters or re-enter the game, the game will only initiate a 64 x 64 dynamic 2d int array. If the player walks close to the boundary of the original map, say, less than 20 units from the boundary, the map will extend. This extension is basically initializing a new map with doubled side length and random allocated events, then copying the values in the original map to the new map, and deleting the original map, and pointing the pointer to the new map. To minimize the delay brought by the copying process, we will reset the player's location to be the center of the new map and copy the original map correspondingly. By this, the distance between the player and boundary could be maximized whenever the map is refresh. Thus the chance of refresh will be minimized. Due to the limitation of the int type, the maximum size of the map is 2^(32) x 2^(32) square units. However, this could be solved easily by re-entering the game to refresh the map. To conclude, in a single game time, the minimum distance needs to approach the map boundary is 4,294,966,712 steps; by saving and re-enter the game, the map is infinitive!

For the list of monsters, the dynamic feature allows it to extend only when necessary. This could be achieved by copying the old one to the new large list, delete the old list and point the pointer to the new list. This property allows us to store information on the random number of monsters. For further details, please refer back to section 3.3.7.

From 3.3.7:
After encountered the event of a monster attack on the map, monsters will also be generated. As the quantity, health point, attack point of monster(s), and location are all random. Therefore, the information of monster(s) is stored in a Monster type dynamic 1D array according to the quantity of monster appears.

  For the divergent linked list, one node can point to 2 another node, while the subsequent node could be itself or any others. This allows us to create a "network" of stories. Apart from facilitating the building of the story, our user can decide and the corresponding pointer will direct him to the corresponding storyline. For further details and feature support, please refer back to section 3.3.9.

From 3.3.9:
To provide an interactive experience when users read our story, they can choose after each story section. For instance, there are choices 1 or choice 2. Their choice will then affect what the next story is. For instance 1->11 / 2->3.
We use divergent linked lists to build the storyline. Each story node stores an id and a location. The id is consecutive, and the location is always within 40 units around the previous story triggering location by random allocation. Only if both story id matches the story and the player's location fit with triggering location will the story display be triggered. Players can use the Navigator in the main interface to found the direction and walk to the triggering location of the next story.

  To conclude, the dynamic data structure is used to construct the framework of the game.

### **4.4 File input/output**

  2 features use file input: (1) load and (2) read the story. (1) is reading the data of structure **Profile** from external file "profile.txt". (2) is reading lines of the story from the external file "story.txt" and display to the player. For further details, please refer back to sections 3.2 and 3.3.10.

  There is 1 feature that uses file output: save. It directs the data of structure **Profile** to external file "profile.txt". It provides permanent data storage for the game. For further details, please refer back to section 3.2.

### **4.5 Program codes in multiple files**

  Files: "makefile", "structure.h", "main.cpp", "interface.h", "interface.cpp", "game_status.h", "game_status.cpp", "survival.h", "survival.cpp", "explore.h", "explore.cpp", "battle.h", "battle.cpp"."story.h", "story.cpp"

  Obviously, we put our game structures in the "structure.h", put all the functions in different *.cpp files according to their categories, link them together through *.h files, and assemble all the functions by "main.cpp". Then, compile them together by the "makefile".

  By including the 'structure.h" in all .h files, then include .h files to corresponding .cpp files, all the source code can share the same structure. This allows us to pass the self-defined structures between the main function and other functions in different files. Especially when writing the function prototype in .h files, this is critically important.

  By include the *.h files of other files, *.cpp files can have their function prototype and use the functions in other files. This allows us to use the same function in multiple files, especially the interface.h provides a display function for functions in many files.

  Therefore, coding in different files allows us to improve modularization and allow corporation by writing different files according to each's responsibility.

## **5 Problem Statements**

### **5.1 Setting**

#### **5.1.1 Concept of game**

  The proposed game, "The Fission", is an "open-world" adventure RPG game. The player could enjoy the fun of battle, survive, explore, and storyline.  Not only does it uses traditional turn-based combat, but it also extends the battlefield from 1D to 2D. The background and four significant elements will be introduced in the following section. For further game background and setting, please refer to section 1.

#### **5.1.2 Reason for Choosing**

  Although we are just beginners, we still want to make a game that is not following some fixed rules like Greedy Snake or Tetris and creates an infinite world like Minecraft to allow our users to explore freely in the game. Besides, we want to give a sense of immersion to our users. Therefore, we try to create an open-world game for our users. However, a world without conflict and emotions is void. Therefore, we try to add these elements by using a storyline and involve a battle sub-system in the game. To further fill the world with excitement, we add maze, buildings, and branching storylines. That's how the game is being designed.

#### **5.1.3 Bug avoiding settings**

  We are sorry that we cannot explain too much here because it is a lot of conditions and limitations in the game to avoid bug, like setting the NULL pointer at the end of the linked list or bool return values function. Please refer to the code we wrote. To be honest, we have written a lot in the readme. It is not a problem that we don't want to write the bug-avoiding settings, but they are everywhere in the code. I believe you will very clear about our code because I almost write annotation in every line.

### **5.2 Assumptions**

#### **5.2.1 Environment Assumption**

1.	The execution environment is in a Linux terminal, like the X2go terminal.
2.	The memory is large enough to bear the extended map array of the game.
3.	The version of the Linux system can display Unicode in the terminal.

#### **5.2.2 Input Assumption**

1.	All the input char commands are included in the ASCII table or is an ASCII char.
2.	The player won't walk 4,294,966,712 toward a single direction within a single game time and trigger out a maze there, and then further walk toward the boundary through the maze. This is the only method to make our game collapse…… but I don't think anyone will do so……..
3.	The player will re-enter the game instead of keeping playing it without saving and load. This is because it takes a long time to load a map if an extensive map is needed.
4.	The number of players' items and attack point won't greater than 2^(32), as it will cause some bugs to become a negative number.

#### **5.2.3 Output Assumption**

1.	Every output char are with same length and width. (because some ascii char have different width compare to Unicode char)

## **6. Reference List**

1.	https://jensen-lee.blog.csdn.net/article/details/89390231?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-4.control&dist_request_id=1332041.934.16191819751048611&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-4.control





