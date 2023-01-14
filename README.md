# lavat

Little program that simulates a lava lamp in the terminal.
![demo](https://github.com/AngelJumbo/demos/blob/main/lavat/3.gif?raw=true)
## Installation

Requirements: A Unix-like system, a C compiler and make.

```
git clone https://github.com/AngelJumbo/lavat
cd lavat
make install
```

### Arch Linux
Lavat is also available on the AUR [here](https://aur.archlinux.org/packages/lavat-git). Install it with your favourite AUR-helper or manually.
```
$ paru -S lavat-git
```
## Usage

```
Usage: lavat [OPTIONS]
OPTIONS:
  -c <COLOR>          Set color. Available colours: red, blue, yellow, green, cyan and magenta.
                      Besides those colors the default one is the normal foreground of your terminal.
  -s <SPEED>          Set the speed, from 1 to 10. (default 5)
  -r <RADIUS>         Set the radius of the metaballs, from 1 to 10. (default: 5)
  -R <RIM>            Set a rim for each metaball, sizes from 1 to 5.(default: none)
                      This option does not work with the default color
                      If you use Kitty or Alacritty you must use it with the -k option to see the rim.
  -k <COLOR>          Set the color of the rim if there is one. Available colours: red, blue, yellow, green, cyan and magenta.
  -b <NBALLS>         Set the number of metaballs in the simulation, from 5 to 20. (default: 10)
  -F <CHARS>          Allows for a custom set of chars to be used
                      Only ascii symbols are supported for now, wide/unicode chars may appear broken.
  -C                  Retain the entire lava inside the terminal.
                      It may not work well with a lot of balls or with a bigger radius than the default one.
  -h                  Print help.
RUNTIME CONTROLS:
  i                   Icrease radius of the metaballs.
  d                   Decrease radius of the metaballs.
  shift i             Icrease rim of the metaballs.
  shift d             Decrease rim of the metaballs.
  m                   Icrease the number of metaballs.
  l                   Decrease the number metaballs.
  +                   Icrease speed.
  -                   Decrease speed.
```

## Demo

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
