🎮 Third-Person Shooter Game - CO2301 Games Development 1
👤 Student Name: [Andreas Pnevmatikas]

🎯 Engine: Unreal Engine 5
💻 Language: C++

🌟 Project Overview
This is a third-person shooter game developed in Unreal Engine 5 using C++. The player must eliminate 5 AI enemies to win while managing health and avoiding enemy fire. 
The game features a complete HUD, trigger-based pickups, raycasting weapon system, and AI enemies with automatic targeting.

✨ Game Features
🎯 Core Gameplay

📷 Third-person camera system with spring arm for smooth following
🎮 WASD movement controls with camera-relative directional input
🖱️ Mouse look for camera control (pitch and yaw)
🔫 Raycasting weapon system with line trace for hit detection
❤️ Health system with real-time HUD updates
💊 Health pickups using trigger overlap events
🎯 5 enemy kill requirement to win
🗺️ Minimap functionality for player awareness


🏃 Player Character (MainCharacter)

⚡ Character movement with configurable walk speed (900 units/s)
❤️ Health management (100 HP max)
💥 Damage system using TakeDamage() function
💚 Healing functionality via health pickups
☠️ Death state handling
👤 Visual mesh component
🎯 Projectile spawn point for weapon firing


🤖 Enemy AI (EnemyAICharacter)

🧠 AI-controlled enemies with player detection
🔫 Raycasting attack system with configurable damage (10 HP default)
⏱️ Fire rate limiting with timer system
❤️ Health pool and damage handling
💀 Death and destruction on health depletion
🎨 Visual and audio feedback on attack
📡 Trigger-based detection sphere for player awareness


🖥️ User Interface

📊 Main HUD displaying:

❤️ Health bar (progress bar with percentage)
💯 Health text (current/max format)
 + CrossHair   (displaying where the character shoots)


🏠 Main Menu with start and quit options
🏆 Win Screen displayed after eliminating all enemies

🔄 Restart button (returns to game)
🚪 Quit button


💀 Game Over Screen displayed on player death

🔄 Restart button
🚪 Quit button



🎲 Game Rules (GameMode)

📊 Tracks enemies killed vs. total enemies
✅ Win Condition: Kill all 10 enemies
❌ Lose Condition: Player health reaches 0
🔄 Automatic level transition to win/lose screens
🎬 Uses UGameplayStatics::OpenLevel() for transitions

⚙️ Technical Features

🎯 Raycasting using LineTraceSingleByChannel for weapon hits
💥 Damage System using UGameplayStatics::ApplyDamage()
🔔 Trigger Events with OnComponentBeginOverlap for health pickups
⏰ Timer System for fire rate control (FTimerHandle)
🎮 PlayerController manages HUD creation and updates
📱 Widget system for UI (created via C++ and displayed dynamically)


🎮 Controls
InputAction⬆️ WMove Forward⬇️ SMove Backward⬅️ AStrafe Left➡️ DStrafe Right🖱️ Mouse MovementLook Around🖱️ Left Mouse ButtonFire Weapon⬆️ SpacebarJump⏸️ ESCPause/Menu

📁 Project Structure
💻 C++ Classes
👥 Character Classes

MainCharacter 🦸 - Player character with movement, shooting, and health
EnemyAICharacter 🤖 - AI enemy with raycasting attacks

🎮 Game Framework

ThirdPersonShooterGameModeBase 🎲 - Game rules, win/lose conditions
MainPlayerController 🎯 - HUD management and player input


🎁 Pickups & Triggers

HealthPickup 💊 - Collectible health restoration item with overlap triggers


🎨 Blueprint Assets

BP_MainCharacter 🦸 - Player character blueprint
BP_EnemyAICharacter 🤖 - Enemy AI blueprint
BP_ThirdPersonShooterGameMode 🎲 - Game mode blueprint
BP_MainPlayerController 🎮 - Player controller blueprint
BP_HealthPickup 💊 - Health pickup blueprint


🖼️ UI Widgets

PlayerHUD_Widget 📊 - In-game HUD (health bar and text)
WinScreen_Widget 🏆 - Victory screen UI
LoseScreen_Widget 💀 - Game over screen UI
Minimap_Widget    🗺️  -Functionality for player awareness


🗺️ Levels

MainMenuMap 🏠 - Main menu level
ThirdPerson 🎮 - Main gameplay level


✅ Requirements Checklist
📋 Basic Requirements (40%)

✅ Multiple screens (Main Menu, Game, Win, Lose)
✅ C++ Pawn/Character class with movement controls
✅ Shootable Actor class (Enemy AI)
✅ Collision handling (OnComponentBeginOverlap)
✅ Basic enemy AI (movement behavior)
✅ C++ GameMode with win/lose conditions
✅ In-game sound (weapon fire, impacts,etc)
✅ 3rd person camera using SpringArmComponent components created in C++


🌟 Advanced Requirements (50%)

✅ Blueprint-friendly properties with UPROPERTY
✅ Basic HUD display (health bar, text, crosshair)
✅ PlayerController class to initializes HUD and other implementations
✅ UGameplayStatics::ApplyDamage for damage system
✅ Use of the UProjectileComponent to launch projectile actors (that will deal damage to an opponent)
✅ In-game timer (fire rate cooldown) created in C++
✅ Trigger events (OnComponentBeginOverlap for pickups)



🌟 More Advanced Requirements (60%)
✅ Assignment uses Source Control and is integrated into your Unreal Project 
✅ Destructible mesh actors in level that can be damaged/destroyed by the player
✅ Use of Physics Forces (E.g. Impulse, Radial Impulse, Force)
✅ C++ AIPlayerController class handling taking damage and behaviour
✅ Pathfinding using a navigation mesh
✅ Basic Behavior Tree / Blackboard system



🌟 First Class Requirements (70%)
✅ Behavior tree allows enemies to chase players
✅ Behavior tree allows enemies to attack players from range
✅ Custom Written (in C++) Behavior Tree Services and Behavior Tree Tasks
✅ Mini Map using SceneCaptureComponent/RenderTarget
✅ Raycasting with LineTraceSingleByChannel


🚀 How to Run

📥 Clone/Download the project
📂 Open the .uproject file with Unreal Engine 5
🔨 Compile the C++ code (Build → Compile)
▶️ Play from the editor or package for standalone

🎯 First-Time Setup

⚙️ Ensure Default GameMode is set to BP_ThirdPersonShooterGameMode:

Edit → Project Settings → Maps & Modes


✅ Verify PlayerController is set to BP_MainPlayerController in GameMode
🎨 Check that HUD Widget Class is assigned in PlayerController Blueprint
🤖 Place enemies in the ThirdPerson level (at least 10)





🔮 Future Improvements
If given more time, the following features would enhance the game:

🧠 AI Behavior Trees for more intelligent enemy behavior
🔫 Multiple weapon types with different stats
📦 Ammo system with reload mechanics
🏆 Score system with combo multipliers
📈 Difficulty scaling over time
🎭 More enemy variety (different types/behaviors)



🙏 Credits & Resources

🎮 Unreal Engine 5 by Epic Games
💻 C++ Programming using Unreal's API




📧 Contact
👤 Student: [Andreas Pnevmatikas]
📧 Email: [andreaspnevmatikas@gmail.com]


📅 Last Updated: [Date]

🎉 Thank you for reviewing my project! 🎮✨
