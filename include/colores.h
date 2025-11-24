#ifndef UI_H
#define UI_H

typedef enum {
    COL_RESET = 0,
    COL_RED,
    COL_GREEN,
    COL_YELLOW,
    COL_BLUE,
    COL_MAGENTA,
    COL_CYAN,
    COL_WHITE,
    COL_BRIGHT_RED,
    COL_BRIGHT_GREEN,
    COL_BRIGHT_YELLOW,
    COL_BRIGHT_BLUE,
    COL_BRIGHT_MAGENTA,
    COL_BRIGHT_WHITE,
    COL_BRIGHT_WHITE
} tColor;

/*
 * Igual que printf, pero con un parámetro extra para el color.
 * Ejemplo: cprintf(COL_RED, "Error %d\n", codigo);
 */
void cprintf(tColor color, const char *fmt, ...);

/*------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdarg.h>

static const char *color_to_ansi(tColor c) {
    switch (c) {
        case COL_RED:            return "\033[31m";
        case COL_GREEN:          return "\033[32m";
        case COL_YELLOW:         return "\033[33m";
        case COL_BLUE:           return "\033[34m";
        case COL_MAGENTA:        return "\033[35m";
        case COL_CYAN:           return "\033[36m";
        case COL_WHITE:          return "\033[37m";

        case COL_BRIGHT_RED:     return "\033[91m";
        case COL_BRIGHT_GREEN:   return "\033[92m";
        case COL_BRIGHT_YELLOW:  return "\033[93m";
        case COL_BRIGHT_BLUE:    return "\033[94m";
        case COL_BRIGHT_MAGENTA: return "\033[95m";
        case COL_BRIGHT_WHITE:    return "\033[96m";
        case COL_BRIGHT_WHITE:   return "\033[97m";

        case COL_RESET:
        default:                 return "\033[0m";
    }
}

void cprintf(tColor color, const char *fmt, ...) {
    va_list args;

    /* Seteo color */
    fputs(color_to_ansi(color), stdout);

    /* Imprimo como printf normal */
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    /* Reseteo color para no romper el resto de la consola */
    fputs("\033[0m", stdout);
}

#endif