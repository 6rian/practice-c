#include "robot_simulator.h"
#include <stdio.h>

#if DEBUG
void debug(robot_status_t *robot) {
    printf("DEBUG: Direction=%d, Position=(%d,%d)\n",
        robot->direction,
        robot->position.x,
        robot->position.y
    );
}
#endif

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
    robot_status_t robot;
    robot.direction = direction;

    robot_position_t position;
    position.x = x;
    position.y = y;
    robot.position = position;

    return robot;
}

void robot_move(robot_status_t *robot, const char *commands) {
    for (; *commands != '\0'; commands++) {
        switch (*commands) {
            case 'R':
                // turn right
                puts("right");
                robot->direction++;
                if (robot->direction == DIRECTION_MAX) {
                    robot->direction = DIRECTION_NORTH;
                }
                break;
            case 'L':
                // turn left
                puts("left");
                if (robot->direction == 0) {
                    robot->direction = DIRECTION_WEST;
                } else {
                    robot->direction--;
                }
                break;
            case 'A':
                // advance
                puts("advance");
                switch (robot->direction) {
                    case DIRECTION_NORTH:
                        robot->position.y++;
                        break;
                    case DIRECTION_SOUTH:
                        robot->position.y--;
                        break;
                    case DIRECTION_EAST:
                        robot->position.x++;
                        break;
                    case DIRECTION_WEST:
                        robot->position.x--;
                        break;
                    default:
                        puts("wrong");
                        continue;
                }
            default:
                // INVALID!
                continue;
        }

        #if DEBUG
        debug(robot);
        #endif

    }
}

int main(void) {
    robot_status_t r = robot_create(DIRECTION_NORTH, 7, 3);

    #if DEBUG
    debug(&r);
    #endif

    robot_move(&r, "RAALAL");
    return 0;
}