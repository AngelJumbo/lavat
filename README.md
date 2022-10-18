# lavat

Little program that simulates a lava lamp in the terminal.
![demo](https://github.com/AngelJumbo/lavat/blob/demo/demo/3.gif?raw=true)
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
Usage: lavaterm [OPTIONS]
OPTIONS:
  -c COLOR          Set color. Available colours: red, blue, yellow, green, cyan and magenta.
                    Besides those colors the default one is the normal foreground of your terminal.
  -s SPEED          Set the speed, from 1 to 5. (default 1)
  -r RADIUS         Set the radius of the metaballs, from 1 to 10. (default: 5)
  -R RIM            Set a "rim" for each metaball, sizes from 1 to 5. (default: none)
                    This option does not work with the default color
  -b NBALLS         Set the number of metaballs in the simulation, from 2 to 20. (default: 10)
  -F CHARS          Allows for a custom set of chars to be used
  -h                Print help.
```

## Demo

`lavat -c red -R 1`

![demo 1](https://github.com/AngelJumbo/lavat/blob/demo/demo/1.gif?raw=true)


`lavat -c cyan -R 4 -b 20 -r 2`

![demo 2](https://github.com/AngelJumbo/lavat/blob/demo/demo/2.gif?raw=true)

If you send more than one character to the -F option you can have 3d-ish effect.

`lavat -c blue -R2 -F @:::::: -r10`

![demo 2](https://github.com/AngelJumbo/lavat/blob/demo/demo/4.gif?raw=true)

(The colors depend on your color scheme.)

## Credits

  - This program is made with [Termbox2](https://github.com/termbox/termbox2).
  - [Metaballs](https://en.wikipedia.org/wiki/Metaballs).
  - [Lava lamp in JavaScript](https://codeguppy.com/site/tutorials/lava-lamp.html)
