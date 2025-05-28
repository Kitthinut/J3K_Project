# 🎮 FIBO XI DUNGEON V.1

## 📘 Game Manual / Explanation

**Overview:**  
*FIBO XI Dungeon* is a turn-based RPG where you play as a stressed (but brave!) engineering student trapped in a surreal, never-ending academic dungeon.  
Your mission? Survive each bizarre room, defeat subject-themed bosses, and plan your life one subject at a time.

This game is crafted from scratch with ❤️ and **no game engine required** — we use only **SFML (Simple and Fast Multimedia Library)** for rendering 2D graphics and handling input.  
The entire codebase is **object-oriented**, built with C++ classes and clean inheritance to ensure modularity, maintainability, and scalability.

All art and assets are lovingly hand-made by our team — simple, stylish, and full of personality!

  **Development Approach:**
- 🧱 Built using **SFML (C++ only)** — no external game engines involved.
- 🧠 Clean **OOP structure** — all game entities are classes with inheritance where needed 
- 🎨 Original artwork — designed by the team to match the theme and tone.
- 🔄 Game loop and mechanics handcrafted with attention to gameplay feel and responsiveness.

### 🎮 How to Play:
- Use `W`, `A`, `S`, `D` to move.
- Use `LShift` to run.
- Press `Space` to interact with objects.
- Engage in turn-based battles with subject-themed enemies.
- Access stats with `C` and exit additional popup with `Esc`.
- Upgrade your HP and Mana in the dorm room, at the wardrobe.

### 🧮 Scoring System:
- No traditional score — your progress is measured by:
  - Number of bosses defeated.
  - Days survived.
  - Stats progression and upgrades obtained.

### 📏 Rules:
- You lose a battle if your HP reaches 0, but you will revive with 50% of your max HP.
- All actions (interacting, fighting, resting) consume time.
- Skills consume different amounts of Mana depending on their power.
- Using normal attacks during battle helps restore Mana.
- You can only upgrade your stats when you're inside your dorm room.
- Defeating 5 bosses automatically starts a new day.
- Sleeping also triggers the start of a new day.
- Each day has 5 activity slots:
  - Fighting a boss consumes 1 slot.
  - Resting consumes 1 slot.

---

## ✅ Requirements

### 🔧 Functional Requirements 

- 🎮 The player can control the character using the keyboard. Movement = freedom!
- ❤️ The game must show HP (Health), MP (Mana), and EXP bars clearly — so you always know how close you are to greatness... or doom.
- 🛋️ Every room must allow interaction with cute (and possibly suspicious) objects like desks, appliances, or mystery consoles.
- ⚔️ Battles and stat upgrades must work seamlessly — tap that key, and feel the response instantly!
- ✨ Skills must have unique effects. Choose wisely — some sparkle, some boom.

### 🧠 Non-Functional Requirements 

- 🪟 The game must run smoothly on Windows — no hiccups, no drama.
- ⚡ A buttery-smooth 60 FPS is a must — your adventure deserves no lag!
- 🖼️ UI elements should be crisp and readable at 1920x1080. No squinting allowed.
- 🚪 Loading between rooms should take no more than 2 seconds — we’re speedrunning, baby!
- 📦 The game and its updates should stay light — no 10 GB surprises here.

---

## 🧑‍💻 User Manual

### Installation & Setup

1. **Download & Launch:**
   - Download the game [HERE](https://github.com/Kitthinut/J3K_Project/releases).
   - Extract to any folder.
   - Run `FIBO_XI_Dungeon.exe`.

2. **Objective:**
   - Survive in an infinite academic dungeon.
   - Defeat subject-themed bosses.
   - Upgrade your stats and endure.

3. **Core Gameplay:**
   - Move freely using the keyboard.
   - Interact with dorm objects, NPCs, and boss rooms.
   - Engage in battles and upgrade health/mana.
   - Manage your day count and plan each move.

4. **Upgrades:**
   - Upgrades are available via dorm room terminal.
   - Each boss gives you EXP and sometimes items.
   - Max HP and Mana are capped at 100 in v.1.

5. **End Condition:**
   - Endless loop until you fall (HP = 0).
   - Track your survival stats manually.

---

### ⌨️ Controls

| Action            | Key/Button         |
|-------------------|--------------------|
| Move Up           | `W`                |
| Move Down         | `S`                |
| Move Left         | `A`                |
| Move Right        | `D`                |
| Run               | `LShift`           |
| Interact          | `Space`            |
| Character Stats   | `C`                |
| Exit Popup Window | `Esc`              |

---

## ✨ Credits

| Role               | Contributor IDs                           |
|--------------------|-------------------------------------------|
| Game Design        | 6703, 6707, 6731                          |
| Art & UI           | 6703                                      |
| Programming        | 6707, 6731, 6740                          |
| Testing & Balance  | All Team Members                          |
| Library Used       | SFML (Simple and Fast Multimedia Library) |

> Inspired by FIBO Life, Engineered by pain, Built with ❤️

---

> _Version 1.0 — Endless loop, not completed, but full of soul._

So — grab your imaginary backpack, prep those formulas, and dive into the dungeon. Your GPA may not survive, but you will!
