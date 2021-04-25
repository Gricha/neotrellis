# Neotrellis 8x8

This project includes a software I've built for [Neotrellis 8x8](https://www.adafruit.com/product/1929) as a toy for my kid.

It includes a couple of simple activities and animations that a toddler can play with. Most of them are well documented in [the toy manual](MANUAL.md).

# Demo 

### Snake

[Snake](https://user-images.githubusercontent.com/875316/115981162-c36e1f80-a546-11eb-8068-6705201ab84b.mp4)

### Light impulses

[Impulses](https://user-images.githubusercontent.com/875316/115981209-1516aa00-a547-11eb-9a1f-f562bc039dc1.mp4)

# Other activities and manual

Here you can find a manual for all implemented activities - there's a bunch more variations and animations.

# Setup

The entire project is written as a C++ library and is using Arduino ecosystem for actual building and flashing. You can see there's one top-level `.ino` file. I've been using VSCode with [Arduino plugin](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino).

The following steps are specific to using Feather M4 Express.

### 1. Board support
1. Cmd + Shift + P
2. Arduino Board Manager
3. Hit Additional URLs and add `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json` to the list.
4. Search for and install "Adafruit SAMD Boards"

### 2. Board configuration
1. Cmd + Shift + P
2. Arduino Board Configuration
3. Selected Board -> Adafruit Feather M4 Express
