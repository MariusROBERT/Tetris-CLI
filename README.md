# Tetris CLI


Welcome on this project, my goal here was to recreate the
famous tetris game in Command Line Interface (CLI).

I used the [FTXUI](https://github.com/ArthurSonzogni/FTXUI) library
to make my job easier. It's the only used library, everything else
is written in C++ by myself.

---
### Requirements

You will need `make` and `cmake` installed to compile the project.

If its already installed, compile it with `make` in the downloaded directory.

If you are on an azerty keyboard, you can compile with `make KEYBOARD=AZERTY` (default is qwerty).


### How to play ?

<details><summary>QWERTY version</summary>

Use the arrow keys or `a` and `d` to move the tetromino.

Use the `q` and `e` key to rotate the tetromino clockwise and counter-clockwise.

Use the `w` key to swap the current tetromino with the hold one.

You can speed up the tetromino fall by pressing the `arrow down` or `s` key 
or even teleport it to its shadow right beneath it by pressing `space`.

You can pause the game with the `p` key, resume it with the `Play` button or the `p` key again.
</details>

<details><summary>AZERTY version</summary>

Use the arrow keys or `q` `d` to move the tetromino.

Use the `a` and `e` key to rotate the tetromino clockwise and counter-clockwise.

Use the `z` key to swap the current tetromino with the hold one.

You can speed up the tetromino fall by pressing the `arrow down` or `s` key 
or even teleport it to its shadow right beneath it by pressing `space`.

You can pause the game with the `p` key, resume it with the `Play` button or the `p` key again.
</details>
