# Arabic Memory Engine (HLR-Based)

A desktop-based spaced repetition system (SRS) designed for rapid Arabic vocabulary acquisition. Unlike standard flashcard apps, this engine uses **Half-Life Regression (HLR)** to predict exactly when a word is slipping from your memory.

### Features

* **HLR Core:** Implements the exponential decay formula $$R = 2^{-\frac{\Delta t}{h}}$$ to calculate real-time recall probability.
* **Stability Tiers:** Categorizes words into 6 distinct tiers (from **FOCUS** to **EXPERT**) based on their calculated half-life (h).
* **Dual Modes:** * **Learning Mode:** Introduces new words with full translations.
  * **Practice Mode:** Interactive testing where the engine selects the "weakest" words for review.
* **Dynamic UI:** Built with Qt Creator, featuring a deep dark slate theme, real-time progress bars, and color-coded stability metrics.

### Stability Tier Logic

The engine evaluates word strength based on the following half-life (h) thresholds:

| Tier | Range (Days) | Visual Indicator |
| :--- | :--- | :--- |
| **EXPERT** | h >= 30.0 | Purple |
| **VERY STRONG** | h >= 7.0 | Green |
| **STRONG** | h >= 1.0 | Lime |
| **WEAK** | h >= 0.5 | Yellow |
| **VERY WEAK** | h >= 0.2 | Orange |
| **FOCUS** | h < 0.2 | Red |

### Technical Stack

* **Language:** C++17
* **Framework:** Qt 6.x (QtWidgets)
* **Build System:** qmake / Qt Creator
* **Logic:** Half-Life Regression (Custom Implementation)

---
*Note: This project is currently being migrated to a modern web stack (React + Vite + Tailwind) for enhanced data visualization and mobile accessibility.*
