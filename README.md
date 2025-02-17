# Space Invader Clone 🚀👾  
*A modern C++ implementation of the classic arcade shooter with object-oriented design and JSON-powered configuration.*  

[![C++](https://img.shields.io/badge/C%2B%2B-17-%2300599C?logo=c%2B%2B)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/Build-CMake-%23008FBA)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)

**Gameplay Preview**  
<!-- Add gameplay GIF/screenshot here -->
![Gameplay Demo](media/demo.gif)

---

## 🎮 Key Features
- **Classic Arcade Mechanics**  
  - Player ship movement & shooting  
  - Multiple enemy types (Ships, UFOs)  
  - Asteroid hazards  
- **Modern Architecture**  
  - Factory pattern for enemy spawning (`EnemyFactory`)  
  - JSON configuration for entities (`EnemyShip.json`, `PlayerShip.json`)  
  - Save system (`save.json`)  
- **Extensible Design**  
  - Separated rendering system (`Render.h`)  
  - Game state management (`GameManager`)  

---

## 🛠️ Technical Implementation

### Core Classes
| Class | Responsibility |  
|-------|----------------|  
| `GameManager` | Central game loop & state control |  
| `EnemyFactory` | Spawns enemies using JSON configs |  
| `Render` | Handles graphics output |  
| `Projectile` | Manages bullet physics & collisions |  

### Enemy Factory System
```cpp
// EnemyFactory.cpp
Enemy* EnemyFactory::CreateEnemy(EnemyType type) {
    switch(type) {
        case EnemyType::Ship:
            return new EnemyShip(loadConfig("EnemyShip.json"));
        case EnemyType::UFO:
            return new EnemyUFO(loadConfig("EnemyUFO.json"));
        default:
            throw std::runtime_error("Invalid enemy type");
    }
}
```
## 🧠 Design Decisions
Factory Pattern

Enables easy addition of new enemy types

Decouples object creation from game logic

JSON Configuration

Allows designers to tweak gameplay without recompiling

Supports modding community integration

Component Separation

Clear division between rendering (Render.h/cpp) and game logic



