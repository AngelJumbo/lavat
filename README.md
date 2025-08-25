# lavat

Little program that simulates a lava lamp in the terminal.
![demo](https://github.com/AngelJumbo/demos/blob/main/lavat/3.gif?raw=true)
## Installation

Requirements: A Unix-like system, a C compiler and make.

```
git clone https://github.com/AngelJumbo/lavat
cd lavat
sudo make install
```

This program is also available from the following repositories:

[![Packaging status](https://repology.org/badge/vertical-allrepos/lavat.svg)](https://repology.org/project/lavat/versions)


## Usage

```
Usage: lavat [OPTIONS]
OPTIONS:
  -g                  Enable gradient mode with truecolor support.
                      Changes how -c and -k options work.
  -c <COLOR>          Set color. In normal mode, available colors are: red, blue, yellow, green, cyan, magenta, white, and black.
                      In gradient mode (-g), use hex format: RRGGBB (e.g., FF0000 for red).
  -k <COLOR>          Set the rim color. Same format options as -c.
                      In gradient mode, this sets the second color for the gradient.
  -s <SPEED>          Set the speed, from 1 to 10. (default 5)
  -r <RADIUS>         Set the radius of the metaballs, from 1 to 10. (default: 5)
  -R <RIM>            Set a rim for each metaball, sizes from 1 to 5.(default: none)
                      This option does not work with the default color
                      If you use Kitty or Alacritty you must use it with the -k option to see the rim.
  -b <NBALLS>         Set the number of metaballs in the simulation, from 5 to 20. (default: 10)
  -F <CHARS>          Allows for a custom set of chars to be used
                      Only ascii symbols are supported for now, wide/unicode chars may appear broken.
  -C                  Retain the entire lava inside the terminal.
                      It may not work well with a lot of balls or with a bigger radius than the default one.
  -p <MODE>           PARTY!! THREE MODES AVAILABLE (p1, p2 and p3).
  -h                  Print help.
RUNTIME CONTROLS:
  i                   Increase radius of the metaballs.
  d                   Decrease radius of the metaballs.
  shift i             Increase rim of the metaballs.
  shift d             Decrease rim of the metaballs.
  m                   Increase the number of metaballs.
  l                   Decrease the number metaballs.
  c                   Change the color of the metaballs.
  k                   Change the rim color of the metaballs.
  +                   Increase speed.
  -                   Decrease speed.
  p                   TURN ON THE PARTY AND CYCLE THROUGH THE PARTY MODES (it can also turns off the party).
(Tip: Zoom out in your terminal before running the program to get a better resolution of the lava).
EXAMPLES:
  lavat -c green -k red        Use named colors in normal mode
  lavat -g -c 00FF00 -k FF0000 Use hex colors in gradient mode
```

## Demo

`lavat -p3`

![demo 1](https://github.com/AngelJumbo/demos/blob/main/lavat/6.gif?raw=true)

PARTY MODE!!!

`lavat -c red -R 1`

![demo 1](https://github.com/AngelJumbo/demos/blob/main/lavat/1.gif?raw=true)


`lavat -c cyan -R 4 -b 20 -r 2`

![demo 2](https://github.com/AngelJumbo/demos/blob/main/lavat/2.gif?raw=true)

If you send more than one character to the -F option you can have 3d-ish effect.

`lavat -c blue -R2 -F @@:::::: -r10`

![demo 2](https://github.com/AngelJumbo/demos/blob/main/lavat/4.gif?raw=true)

For the Alacritty and Kitty users I know that the -R option haven't been working for you, but now you can set the color of the rim independently. Try:

`lavat -c yellow -R1 -k red`

![demo 2](https://github.com/AngelJumbo/demos/blob/main/lavat/5.gif?raw=true)

(The colors depend on your color scheme.)

## Credits

  - This program is made with [Termbox2](https://github.com/termbox/termbox2).
  - [Lava lamp in JavaScript](https://codeguppy.com/site/tutorials/lava-lamp.html)
