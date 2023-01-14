#define TB_IMPL

#include "termbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MIN_NBALLS 5
#define MAX_NBALLS 20

typedef struct {
  int x;
  int y;
  int dx;
  int dy;
} Ball;

static char *custom = NULL;
static char *custom2 = NULL;
static short color = TB_DEFAULT;
static short color2 = TB_DEFAULT;
static int nballs = 10;
static short speedMult = 5;
static short rim = 0;
static short contained = 0;
static float radiusIn = 100;
static float radius;
static int margin;
static float sumConst;
static float sumConst2;
static int maxX, maxY;
static int speed;
static Ball balls[MAX_NBALLS] = {0};
static struct tb_event event = {0};

void init_params();
void event_handler();
int parse_options(int argc, char *argv[]);
void print_help();

int main(int argc, char *argv[]) {

  if (!parse_options(argc, argv))
    return 0;

  if (color == TB_DEFAULT && !custom)
    rim = 0;

  time_t t;
  // Ball *balls = malloc(sizeof(Ball) * nballs);

  srand((unsigned)time(&t));

  tb_init();

  tb_hide_cursor();

  init_params();

  while (1) {

    // move balls
    for (int i = 0; i < nballs; i++) {

      if (balls[i].x + balls[i].dx >= maxX - margin ||
          balls[i].x + balls[i].dx < margin)
        balls[i].dx *= -1;

      if (balls[i].y + balls[i].dy >= maxY - margin ||
          balls[i].y + balls[i].dy < margin)
        balls[i].dy *= -1;

      balls[i].x += balls[i].dx;
      balls[i].y += balls[i].dy;
    }

    // render
    for (int i = 0; i < maxX; i++) {
      for (int j = 0; j < maxY / 2; j++) {
        // calculate the two halfs of the block at the same time
        float sum[2] = {0};

        for (int j2 = 0; j2 < (!custom ? 2 : 1); j2++) {

          for (int k = 0; k < nballs; k++) {
            int y = j * 2 + j2;
            sum[j2] += (radius * radius) /
                       ((float)((i - balls[k].x) * (i - balls[k].x) +
                                (y - balls[k].y) * (y - balls[k].y)));
          }
        }

        if (!custom) {
          if (sum[0] > sumConst) {
            if (sum[1] > sumConst) {
              tb_printf(i, j, color2, 0, "█");
            } else {
              tb_printf(i, j, color2, 0, "▀");
            }
          } else if (sum[1] > sumConst) {
            tb_printf(i, j, color2, 0, "▄");
          }

          if (rim) {
            if (sum[0] > sumConst2) {
              if (sum[1] > sumConst2) {
                tb_printf(i, j, color, 0, "█");
              } else {
                tb_printf(i, j, color2, color, "▄");
              }
            } else if (sum[1] > sumConst2) {
              tb_printf(i, j, color2, color, "▀");
            }
          }
        } else {
          if (sum[0] > sumConst) {
            tb_printf(i, j, color2, 0, custom2);
          }

          if (rim) {
            if (sum[0] > sumConst2) {
              tb_printf(i, j, color, 0, custom);
            }
          }
        }
      }
    }
    tb_present();
    usleep(speed);
    tb_clear();

    tb_peek_event(&event, 10);

    event_handler();
  }

  tb_shutdown();

  // free(balls);
}

void event_handler() {
  if (event.type == TB_EVENT_RESIZE) {
    do
      tb_peek_event(&event, 10);
    while (event.type == TB_EVENT_RESIZE);

    init_params();
  } else if (event.type == TB_EVENT_KEY) {

    if (event.key == TB_KEY_CTRL_C || event.key == TB_KEY_ESC) {
      tb_shutdown();
      exit(0);
    }

    switch (event.ch) {
    case '-':
    case '_':
      if (speedMult < 10) {
        speedMult++;
        speed = (((1 / (float)(maxX + maxY)) * 1000000) + 10000) * speedMult;
      }
      break;
    case '+':
    case '=':
      if (speedMult > 1) {
        speedMult--;
        speed = (((1 / (float)(maxX + maxY)) * 1000000) + 10000) * speedMult;
      }
      break;
    case 'm':
    case 'M':
      if (nballs + 1 <= MAX_NBALLS) {
        nballs++;
      }
      break;
    case 'l':
    case 'L':
      if (nballs - 1 >= MIN_NBALLS) {
        nballs--;
      }
      break;
    case 'i':
      if (radiusIn + 10 <= 150) {
        radiusIn += 10;
        radius = (radiusIn * radiusIn + (float)(maxX * maxY)) / 15000;
        margin = contained ? radius * 10 : 0;
      }
      break;
    case 'd':
      if (radiusIn - 10 >= 50) {
        radiusIn -= 10;
        radius = (radiusIn * radiusIn + (float)(maxX * maxY)) / 15000;
        margin = contained ? radius * 10 : 0;
      }
      break;
    case 'I':

      if (color != TB_DEFAULT || custom)
        if (rim + 1 <= 5) {
          rim++;
          sumConst2 = sumConst * (1 + (float)(0.25 * rim));
        }
      break;
    case 'D':

      if (color != TB_DEFAULT || custom)
        if (rim - 1 >= 0) {
          rim--;
          sumConst2 = sumConst * (1 + (float)(0.25 * rim));
        }
      break;

    case 'q':
    case 'Q':
      tb_shutdown();
      exit(0);
      break;
    }
  }
}

void init_params() {

  maxX = tb_width();
  maxY = tb_height() * 2;
  speedMult = 11 - speedMult;
  speed = (((1 / (float)(maxX + maxY)) * 1000000) + 10000) * speedMult;
  radius = (radiusIn * radiusIn + (float)(maxX * maxY)) / 15000;

  margin = contained ? radius * 10 : 0;

  sumConst = 0.0225;
  sumConst2 = sumConst * (1 + (float)(0.25 * rim));

  custom2 = custom;

  if (color2 == TB_DEFAULT || !rim)
    color2 = color | TB_BOLD;

  if (custom && strlen(custom) > 1 && rim) {
    custom2 = custom + 1;
  }

  for (int i = 0; i < MAX_NBALLS; i++) {
    balls[i].x = rand() % (maxX - 2 * margin) + margin;
    balls[i].y = rand() % (maxY - 2 * margin) + margin;
    balls[i].dx = (rand() % 2 == 0) ? -1 : 1;
    balls[i].dy = (rand() % 2 == 0) ? -1 : 1;
  }
}

int set_color(short *var, char *optarg) {

  if (strcmp(optarg, "red") == 0) {
    *var = TB_RED;
  } else if (strcmp(optarg, "yellow") == 0) {
    *var = TB_YELLOW;
  } else if (strcmp(optarg, "blue") == 0) {
    *var = TB_BLUE;
  } else if (strcmp(optarg, "green") == 0) {
    *var = TB_GREEN;
  } else if (strcmp(optarg, "magenta") == 0) {
    *var = TB_MAGENTA;
  } else if (strcmp(optarg, "cyan") == 0) {
    *var = TB_CYAN;
  } else {
    printf("Unknown color: %s\n", optarg);
    return 0;
  }
  return 1;
}

int parse_options(int argc, char *argv[]) {
  if (argc == 1)
    return 1;
  int c;
  while ((c = getopt(argc, argv, ":c:k:s:r:R:b:F:Ch")) != -1) {
    switch (c) {
    case 'c':
      if (!set_color(&color, optarg))
        return 0;
      break;
    case 'k':
      if (!set_color(&color2, optarg))
        return 0;
      break;
    case 's':
      speedMult = atoi(optarg);
      if (speedMult > 10 || speedMult <= 0) {
        printf("Invalid speed, only values between 1 and 10 are allowed\n");
        return 0;
      }
      break;
    case 'R':
      rim = atoi(optarg);
      if (rim > 5 || rim < 1) {
        printf("Invalid rim, only values between 1 and 5 are allowed\n");
        return 0;
      }
      break;
    case 'r':
      radiusIn = 50 + atoi(optarg) * 10;
      if (radiusIn > 150 || radiusIn < 50) {
        printf("Invalid radius, only values between 1 and 10 are allowed\n");
        return 0;
      }
      break;

    case 'b':
      nballs = atoi(optarg);
      if (nballs > MAX_NBALLS || nballs < MIN_NBALLS) {

        printf("Invalid number of metaballs, only values between %i and %i are"
               "allowed\n",
               MIN_NBALLS, MAX_NBALLS);
        return 0;
      }
      break;
    case 'F':
      custom = optarg;
      break;
    case 'C':
      contained = 1;
      break;
    case 'h':
      print_help();
      return 0;
      break;
    case ':': /* -f or -o without operand */
      fprintf(stderr, "Option -%c requires an operand\n", optopt);
      return 0;
      break;
    case '?':
      fprintf(stderr, "Unrecognized option: -%c\n", optopt);
      return 0;
    }
  }
  return 1;
}

void print_help() {
  printf(
      "Usage: lavat [OPTIONS]\n"
      "OPTIONS:\n"
      "  -c <COLOR>          Set color. Available colours: red, blue, yellow, "
      "green, cyan and magenta. \n"
      "                      Besides those colors the default one is the normal"
      " foreground of your terminal.\n"
      "  -s <SPEED>          Set the speed, from 1 to 10. (default 5)\n"
      "  -r <RADIUS>         Set the radius of the metaballs, from 1 to 10. "
      "(default: 5)\n"
      "  -R <RIM>            Set a rim for each metaball, sizes from 1 to 5."
      "(default: none)\n"
      "                      This option does not work with the default "
      "color\n"
      "                      If you use Kitty or Alacritty you must use it "
      "with the -k option to see the rim.\n"
      "  -k <COLOR>          Set the color of the rim if there is one."
      " Available colours: red, blue, yellow, green, cyan and magenta. \n"
      "  -b <NBALLS>         Set the number of metaballs in the simulation, "
      "from %i to %i. (default: 10)\n"
      "  -F <CHARS>          Allows for a custom set of chars to be used\n"
      "                      Only ascii symbols are supported for now, "
      "wide/unicode chars may appear broken.\n"
      "  -C                  Retain the entire lava inside the terminal.\n"
      "                      It may not work well with a lot of balls or with"
      " a bigger radius than the default one.\n"
      "  -h                  Print help.\n"
      "RUNTIME CONTROLS:\n"
      "  i                   Increase radius of the metaballs.\n"
      "  d                   Decrease radius of the metaballs.\n"
      "  shift i             Increase rim of the metaballs.\n"
      "  shift d             Decrease rim of the metaballs.\n"
      "  m                   Increase the number of metaballs.\n"
      "  l                   Decrease the number metaballs.\n"
      "  +                   Increase speed.\n"
      "  -                   Decrease speed.\n"
      "(Tip: Zoom out in your terminal before running the program to get a "
      "better resolution of the lava).\n",
      MIN_NBALLS, MAX_NBALLS);
}
