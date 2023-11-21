#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#endif

int main(void)
{
    const char *broker_ip = "";
    const char *topic = "ledProduct";
    boolean flag = TRUE;

    printf("Please Press: \n 1 - light on \n 2 - light off \n 3 - disconnect");
    while (flag)
    {
#ifdef _WIN32
        if (_kbhit())
        {
            char input = _getch(); 
#endif
            // Check user input
            if (input == '1' || input == '2')
            {
                // Send message for case 1 or 2
                char command[256];
                snprintf(command, sizeof(command), "mosquitto_pub -h %s -t %s -m \"%c\"", broker_ip, topic, input);
                system(command);
            }
            else if (input == '3')
            {
                // Exit the loop for case 3
                printf("\nExiting the program.\n");
                flag = FALSE;
            }
            else
            {
                // Invalid input
                printf("Invalid input. Please enter 1, 2, or 3.\n");
            }
        }
    }

    return 0;
}
