#include <stdio.h>
#include <string.h>

#include <ti/grlib/grlib.h> // Need to include this in order to use Graphics functions!
#include "LcdDriver/Crystalfontz128x128_ST7735.h" // Need these drivers to use the LCD!

void make_time_string(int min, int sec, unsigned char *string);
void initializeGraphics(Graphics_Context *g_sContext_p);


int main(void)
{
    // These functions here initialize the graphics so that you can draw strings to your LCD.
    // You will learn more about graphics in the future.
    Graphics_Context g_sContext;
    initializeGraphics(&g_sContext);

    // This statement declares string as an array of unsigned characters
    // This string allocates 6 characters in the memory. This means the string can have up to 5 ascii characters.
    // This is because all C strings should end in the NULL character, i.e. 0
    // We are initializing the array with 1's just so that our codes behaves similarly for everyone.
    // If we do not initialize the array, the debugging can have different outcome for some of you.
    unsigned char string0[6] = {1,1,1,1,1,1};

    // Let's manually create a string of letters
    string0[0] = 'a';
    string0[1] = 'b';
    string0[2] = 'c';
    string0[3] = 0; //the NULL or terminating character. This indicates the end of the string
    string0[4] = 'd';
    string0[5] = 'e';

    // This function prints the string to the LCD.
    // Look at your kit before and after stepping over this line
    // Notice how only "abc" is printed and the rest of the array is ignored when running this code.
    // This is because everything after the NULL character is NOT part of the string.
    Graphics_drawString(&g_sContext, (int8_t *) string0, -1, 5, 0, true);

    // Let's manually create a string that represents a number
    unsigned char string1[6] = {1,1,1,1,1,1};
    string1[0] = '1';
    string1[1] = '2';
    string1[2] = '3';
    string1[3] = '4';
    string1[4] = NULL; //the NULL or terminating character. This indicates the end of the string
    string1[5] = '5';


    // Look at your kit before and after stepping over this line
    Graphics_drawString(&g_sContext, (int8_t *) string1, -1, 5, 10, true);
    // Notice how only "1234" is displayed and the rest of the array is ignored when running this code.


    // Another way to create a string is using the snprintf
    // snprintf puts at most n characters in the destination array of characters where the last character is always NULL
    // The characters that are put in the destination follow a certain format dictated by the format argument
    // Below, see how 25 in the snprintf argument matches the size of the array we reserve for string2 beforehand. This is very important.
    // The parameter n, which is 25 should be less than or equal to the size you have reserved for string2.
    // Pay attention to how snprintf combines the "Welcome to" with 'F' character and the integer 2022 and adds a NULL to the end, all in one function.
    int year = 2023;
    char semester = 'S';
    unsigned char string2[25] = {1,1,1,1,1,
                                 1,1,1,1,1,
                                 1,1,1,1,1,
                                 1,1,1,1,1,
                                 1,1,1,1,1} ;
    snprintf((char *)string2, 25, "Welcome to %c %d!", semester, year);

    // Look at your kit before and after stepping over this line
    Graphics_drawString(&g_sContext, (int8_t *) string2, -1, 5, 40, true);


    //    If you do not include a NULL character at the end of your string bad things can happen in your program.
    //    This bug can manifest itself in different ways depending on where and when it happens.
    //    When a C code that has strings in it is misbehaving,
    //    it is important to go back and make sure all the strings have NULL characters in the space allocated for the string.


    // Another useful function beside snprintf when working with strings is strncpy.
    // This function copies n characters to a destination string (that should already have space for n characters)
    // Very important: unlike snprintf strncpy does not always add a NULL character. It simply copies n characters from source to destination.
    char string3[10] = {1,1,1,1,1,
                        1,1,1,1,1};
    // Copies 7 charactes from "Hokies!" to string3.
    strncpy (string3,"Hokies!", 7);
    // optional space for you to use

    // Look at your kit before and after stepping over this line
    Graphics_drawString(&g_sContext, (int8_t *) string3, -1, 5, 60, true);
    // You were hoping to see "Hokies!" and nothing else. Is this what happened? How can you fix this?
    // Hint1: If you read about strncpy, you might learn that there is a way for it to insert NULL automatically.
    // Hint2: You can manually add Null similar to line 30

    // Yet another useful function beside snprintf and strncpy when working with strings is strncat
    // This function concatenates n characters to a destination string (that should already have space for n extra characters)
    // The concatenation point is where the destination character has a NULL. This mean the destination should already be NULL-terminated but have more room after NULL.
    // Thankfully, the newly concatenated destination string has a new NULL and does not need manual intervention!
    char string4[20] = {1,1,1,1,1,
                        1,1,1,1,1,
                        1,1,1,1,1,
                        1,1,1,1,1};

    // Copies 11 characters from "Stay safe " to destination. Since "Stay safe " has a total of 10 characters and 11 is more than 10, string4 is NULL-terminated, which is great!!!
    strncpy (string4,"Stay safe ", 11);

    // Concatenates 7 characters from string3 to string4.
    strncat (string4, string3, 7);
    Graphics_drawString(&g_sContext, (int8_t *) string4, -1, 5, 70, true);

    // char is 8 bits and can be assigned any number 0 to 255. Here numeric1 is assigned 0.
    unsigned char numbers[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // ascii in here is a character and we are assigning '0' to it. This means ascci1 character 0 (not number 0) is assigned to it.
    unsigned char asciis[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // In the debugger's variables window, compare the content of the above two arrays. You must see a pattern that connects
    // each number to its ascii equivalent.


    unsigned char string5[6]= {1,1,1,1,1,1};

    make_time_string(0, 0, string5);
    Graphics_drawString(&g_sContext, (int8_t *) string5, -1, 5, 90, true);

    make_time_string(3, 14, string5);
    Graphics_drawString(&g_sContext, (int8_t *) string5, -1, 5, 100, true);

    make_time_string(42, 7, string5);
    Graphics_drawString(&g_sContext, (int8_t *) string5, -1, 5, 110, true);

}

/*******************************************************************
 * NAME :            make_time_string(int min, int sec, unsigned char *string)
 *
 * DESCRIPTION :     Creates a string from two numbers to represent time in minute and seconds
 *
 * INPUTS :
 *       PARAMETERS:
 *           int     min        minutes as a number
 *           int     sec        seconds as a number
 *
 * OUTPUTS :
 *       PARAMETERS:
 *           unsigned char    * string to hold the characters that show time
 *
 *       RETURN :
 *            Type:   none
 *
 * PROCESS:
 *       This function turns the min and sec into a string that shows time.
 *
 * EXAMPLES:
 *       If min = 0 and sec = 0, the string becomes "00:00"
 *       If min = 10 and sec = 5, the string becomes "10:05"
 *
 * NOTES:
 *       This function does not check to see if the min and sec are between 0 and 59.
 *       It simply converts them to string without checking
 *
 */

void make_time_string(int min, int sec, unsigned char *string) {


    //TODO: Write this function according to the above specification and the description in the homework assignment.
}

/*
 * ----------------------------------------
 * DO NOT EDIT THIS FUNCTION
 * ----------------------------------------
 *
 * This function sets up all of the proper initializations for using the LCD and
 * drawing graphics to the screen. For more information on how these functions work,
 * please refer to the Graphics > Initialization page on the Introduction to Embedded
 * Systems website.
 */
void initializeGraphics(Graphics_Context *g_sContext_p) {
    // Initialize the LCD
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    // Initialize context
    Graphics_initContext(g_sContext_p, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);

    // Set colors and fonts
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(g_sContext_p, &g_sFontFixed6x8);

    // Clear the screen
    Graphics_clearDisplay(g_sContext_p);
}

