#include "graph.h"
#include "rpn.h"
#include <stdio.h>
#include <math.h>

void plot_function(const char* rpn) {
    char grid[HEIGHT][WIDTH];
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = '.';
        }
    }
    
    const double x_min = 0;
    const double x_max = 4 * PI;
    const double y_min = -1.0;
    const double y_max = 1.0;
    const double x_step = (x_max - x_min) / WIDTH;
    
    for (int px = 0; px < WIDTH; px++) {
        double x = x_min + px * x_step;
        double y_val = evaluate_rpn(rpn, x);
        
        int py = (int)round((y_val - y_min) * (HEIGHT - 1) / (y_max - y_min));
        py = HEIGHT - 1 - py;
        
        if (py >= 0 && py < HEIGHT && px >= 0 && px < WIDTH) {
            grid[py][px] = '*';
        }
    }
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            putchar(grid[y][x]);
        }
        putchar('\n');
    }
}