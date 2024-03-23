/*
Team: A2 - The Sids 
Names: Siddarth Tummala, Sidney Choo
Instructor: Ethan Joll
Class Time: 12:40 PM
Date: 12/4/23
*/


#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"
#include "LCDColors.h"
#include "time.h"
#include "stdio.h"

// calling all our classses
// fruit player classes
class strawberry;
class watermelon;
class mango;

// opponent classes
class burger;
class cookie;
class cupcake;

// misc
class AttackScreen;
class Stats;
class PlayScreen;
class CharacterSelection;
class Difficulty;
class MainMenu;

// displaying player and opponent health during gameplay
FEHIcon::Icon charHealth;
FEHIcon::Icon bossHealth;

// struct for all our stats (Siddarth)
struct statistics
{
    int wins = 0;
    int losses = 0;
    int damageDealt = 0;
    int bestTime = 1000000000;
}stats;

// struct to hold what fruit and opponent the player picked, in order to display correctly during gameplay (Siddarth)
struct playerSelections
{
    int bossSelect;
    int characterSelect;
    FEHImage charPic;
    FEHImage oppPic;
}selections;

// setImages functon displays the chosen fruit and opponent in the arena during gameplay (Siddarth)
void setImages()
{
    switch (selections.characterSelect)
        {
            case 1:
            selections.charPic.Open("CharacterClasses/strawberryFEH.pic");
            

            LCD.Update();
            break;

            case 2:

            selections.charPic.Open("CharacterClasses/watermelonFEH.pic");
            

            LCD.Update();
            break;

            case 3: 
            
            selections.charPic.Open("CharacterClasses/mangoFEH.pic");
            

            LCD.Update();
            break;
        }

        switch (selections.bossSelect)
        {
            case 1:
            
            selections.oppPic.Open("CharacterClasses/cookieFEH.pic");
            
            break;

            case 2:
    
            selections.oppPic.Open("CharacterClasses/cupcakeFEH.pic");
            break;

            case 3:
            
            selections.oppPic.Open("CharacterClasses/burgerFEH.pic");
            break;
        }
        
}

// drawBatllefield function displays the background image and the ability selection GUI (Sidney)
void drawBattlefield()
{
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();
    FEHImage fruitBackground;
    fruitBackground.Open("FruitPunchBackgroundFEH.pic");
    fruitBackground.Draw(0, 0);

    LCD.SetFontColor(BLACK);
        
    LCD.FillRectangle(0, 0, 35, 25);
    LCD.FillRectangle(275, 0, 35, 25);

    selections.charPic.Draw(10, 70);
    selections.oppPic.Draw(210, 70);

    charHealth.Draw();
    bossHealth.Draw();
}

// struct to set the characters healths (Siddarth)
struct charHealths
{
    int character = 100;
    int boss = 100;
}health;

// struct to contain all of the strawberry's abilities' names (Siddarth)
struct strawberryAttacks
{
    char option1Name[30] = "Seed Cyclone";
    int option1Damage = 45;

    char option2Name[30] = "Berry Mend";
    int option2Damage = -10;

    char option3Name[30] = "Attack Buff";

    char option4Name[30] = "Dodge";

}strawberryOptions;

// struct to contain all of the watermelon's abilities' names (Siddarth)
struct watermelonAttacks
{
    char option2Name[30] = "Melon Splash";
    int option2Damage = 30;

    char option1Name[30] = "Melonado";
    int option1Damage = 40;

    char option3Name[30] = "Attack Buff";

    char option4Name[30] = "Dodge";

    //char option4Name[30] = "Dodge";
    //int option1Damage = 45;
}watermelonOptions;

// struct to contain all of the mango's abilities' names (Siddarth)
struct mangoAttacks
{
    char option1Name[30] = "Mango Tango";
    int option1Damage = 30;

    char option2Name[30] = "Mango Mend";
    int option2Damage = -10;

    char option3Name[30] = "Attack Buff";

    char option4Name[30] = "Dodge";

    //char option4Name[30] = "Dodge";
    //int option1Damage = 45;
}mangoOptions;

// struct to contain all of the cupcake's abilities' names (Siddarth)
struct cupcakeAttacks
{
    char option1Name[30] = "Frosting Fury";
    int option1Damage = 45;

    char option2Name[30] = "Quick Heal";
    int option2Damage = -5;

    char option3Name[30] = "Sugary Soothe";
    int option3Damage = -10;

    //char option4Name[30] = "Dodge";
    //int option1Damage = 45;
}cupcakeOptions;

// struct to contain all of the cookie's abilities' names (Siddarth)
struct cookieAttacks
{
    char option1Name[30] = "Cookie Crunch";
    int option1Damage = 30;

    char option2Name[30] = "Cookie Cyclone";
    int option2Damage = 40;

    char option3Name[30] = "Cookie Comfort";
    int option3Damage = -10;
}cookieOptions;

// struct to contain all of the burger's abilities' names (Siddarth)
struct burgerAttacks
{
    char option1Name[30] = "Beef Blitz";
    int option1Damage = 35;

    char option2Name[30] = "Cheese Chaos";
    int option2Damage = 40;

    char option3Name[30] = "Tomatonado";
    int option3Damage = 45;
}burgerOptions;

// class with functions to draw the strawberry, and display the abilites chosen (Sidney)
class strawberry
{
    private:
    int attackX = 80;

    public:

    // to animate strawberry's first attack ability: Seed Cyclone
    void att1Animation()
    {   
        
        // opening the two frames of Seed Cyclone
        FEHImage cyclone1;
        cyclone1.Open("Attacks/seedCyclone1FEH.pic");

        FEHImage cyclone2;
        cyclone2.Open("Attacks/seedCyclone2FEH.pic");

        bool isCyclone1 = true;

        // display attack
        while (attackX <= 210) 
        {
            drawBattlefield();
            if(isCyclone1)
            {
                cyclone1.Draw(attackX, 70);
            }
            else
            {
                cyclone2.Draw(attackX, 70);
            }

            isCyclone1 = !isCyclone1;

            LCD.Update();

            // moving the attack across the screen, from fruit to opponent
            attackX += 7;
        
            Sleep(0.07);
        }

        LCD.Update();
        cyclone1.Close();
        cyclone2.Close();
        LCD.Clear();
        drawBattlefield();

    }

    // to animate strawberry's healing ability
    void att2Animation()
    {   
        
        // opening the heal ability images/frames
        FEHImage heal1;
        heal1.Open("Attacks/heal1FEH.pic");

        FEHImage heal2;
        heal2.Open("Attacks/heal2FEH.pic");

        // display heal ability
        bool isHeal1 = true;
        
        for(int i = 0; i < 5; i++)
        {
            if(isHeal1)
            {
                heal1.Draw(10, 70);
                Sleep(0.25);
                LCD.Clear();
                drawBattlefield();
            }
            else
            {
                heal2.Draw(10, 70);
                Sleep(0.25);
                LCD.Clear();
                drawBattlefield();
            }

            isHeal1 = !isHeal1;
        }

        LCD.Update();
        heal1.Close();
        heal2.Close();
        LCD.Clear();
        drawBattlefield();

    }
    
};

// class with functions to draw the watermelon, and display the abilities chosen (Sidney)
class watermelon
{
    private:
    int attackX = 80;

    public:
    
    // to animate watermelon's first attack: Melon Nado (Sidney)
    void att1Animation()
    {   
        
        // opening the image frames for the attack
        FEHImage attPic1;
        attPic1.Open("Attacks/melonNado1FEH.pic");

        FEHImage attPic2;
        attPic2.Open("Attacks/melonNado2FEH.pic");

        bool isAtt1 = true;

        // display attack
        while (attackX <= 210) 
        {
            drawBattlefield();
            if(isAtt1)
            {
                attPic1.Draw(attackX, 70);
            }
            else
            {
                attPic2.Draw(attackX, 70);
            }

            isAtt1 = !isAtt1;

            LCD.Update();

            // moving the attack graphics from fruit to opponent
            attackX += 7;
        
            Sleep(0.07);
        }

        LCD.Update();
        attPic1.Close();
        attPic2.Close();
        LCD.Clear();
        drawBattlefield();

    }

    // to animate watermelon's second attack: Watermelon Splash (Sidney)
    void att2Animation()
    {   
        int attackY = 0;
        
        // opening the attack image and frames
        FEHImage attPic1;
        attPic1.Open("Attacks/watermelonSplash1FEH.pic");

        FEHImage attPic2;
        attPic2.Open("Attacks/watermelonSplash2FEH.pic");

        bool isAtt1 = true;

        // display attack
        while (attackY <= 70) 
        {
            drawBattlefield();
            if(isAtt1)
            {
                attPic1.Draw(210, attackY);
            }
            else
            {
                attPic2.Draw(210, attackY);
            }

            isAtt1 = !isAtt1;

            LCD.Update();

            // moving the frames from above the opponent to the opponent
            attackY += 5;
        
            Sleep(0.05);
        }

        LCD.Update();
        attPic1.Close();
        attPic2.Close();
        LCD.Clear();
        drawBattlefield();

    }

};

// class with functions to draw the mango, and display the abilities chosen (Sidney)
class mango
{
    private:
    int attackX = 80;
    
    public:

    // to animate mango's first attack: Mango Tango (Sidney)
    void att1Animation()
    {   
        
        // opening image frames for attack
        FEHImage attPic1;
        attPic1.Open("Attacks/mangoTango1FEH.pic");

        FEHImage attPic2;
        attPic2.Open("Attacks/mangoTango2FEH.pic");

        bool isAtt1 = true;

        // display attack
        while (attackX <= 210) 
        {
            drawBattlefield();
            if(isAtt1)
            {
                attPic1.Draw(attackX, 70);
            }
            else
            {
                attPic2.Draw(attackX, 70);
            }

            isAtt1 = !isAtt1;

            LCD.Update();

            // moving the attack graphics from left to right 
            attackX += 7;
        
            Sleep(0.07);
        }

        LCD.Update();
        attPic1.Close();
        attPic2.Close();
        LCD.Clear();
        drawBattlefield();

    }

    // to animate mango's healing ability (Sidney)
    void att2Animation()
    {   
        
        // opening heal image frames
        FEHImage heal1;
        heal1.Open("Attacks/heal1FEH.pic");

        FEHImage heal2;
        heal2.Open("Attacks/heal2FEH.pic");

        // display heal ability
        bool isHeal1 = true;
        for(int i = 0; i < 5; i++){
            if(isHeal1)
            {
                heal1.Draw(10, 70);
                Sleep(0.25);
                LCD.Clear();
                drawBattlefield();
            }
            else
            {
                heal2.Draw(10, 70);
                Sleep(0.25);
                LCD.Clear();
                drawBattlefield();
            }

            isHeal1 = !isHeal1;
        }

        LCD.Update();
        heal1.Close();
        heal2.Close();
        LCD.Clear();
        drawBattlefield();

    }
    
};

// class with functions to draw the burger, and display the abilities chosen (Sidney)
class burger
{
    private:
    int attackX = 140;

    public:

    // to animate the burger's first attack: Beef Blitz
    void att1Animation()
    {   
        // to open attack's image frames
        FEHImage attPic1;
        attPic1.Open("Attacks/beefblitz1FEH.pic");

        FEHImage attPic2;
        attPic2.Open("Attacks/beefblitz2FEH.pic");

        bool isAtt1 = true;

        // display attack
        while (attackX >= 10) 
        {
            drawBattlefield();
            if(isAtt1)
            {
                attPic1.Draw(attackX, 70);
            }
            else
            {
                attPic2.Draw(attackX, 70);
            }

            isAtt1 = !isAtt1;

            LCD.Update();

            // move the graphic from right to left (opponent to player)
            attackX -= 7;
        
            Sleep(0.02);
        }

        LCD.Update();
        attPic1.Close();
        attPic2.Close();
        LCD.Clear();
        drawBattlefield();

    }

    // to animate the burger's second attack: Cheese Chaos
    void att2Animation()
    {   
        // opening attack imaage pics
        FEHImage attPic1;        
        attPic1.Open("Attacks/cheesechaos1FEH.pic");

        FEHImage attPic2;
        attPic2.Open("Attacks/cheesechaos2FEH.pic");

        bool isAtt1 = true;

        // display attack
        while (attackX >= 10) 
        {
            drawBattlefield();
            if(isAtt1)
            {
                attPic1.Draw(attackX, 70);
            }
            else
            {
                attPic2.Draw(attackX, 70);
            }

            isAtt1 = !isAtt1;

            LCD.Update();

            // moving attack from right to left (opponent to player)
            attackX -= 7;    
            Sleep(0.07);
        }

        LCD.Update();
        attPic1.Close();
        attPic2.Close();
        LCD.Clear();
        drawBattlefield();

    }

    void att3Animation()
    {   
        
        // Draw Racer 1
        FEHImage attPic1;
        attPic1.Open("Attacks/tomatonado1FEH.pic");

        FEHImage attPic2;
        attPic2.Open("Attacks/tomatonado2FEH.pic");

        bool isAtt1 = true;

        // display attack
        while (attackX >= 10) 
        {
            drawBattlefield();
            if(isAtt1){
                attPic1.Draw(attackX, 70);
            }
            else{
                attPic2.Draw(attackX, 70);
            }

            isAtt1 = !isAtt1;

            LCD.Update();

            // Update racer coordinates
            attackX -= 7;
        
            Sleep(0.07);
        }

        LCD.Update();
        attPic1.Close();
        attPic2.Close();
        LCD.Clear();
        drawBattlefield();

    }


};

class cookie
{
    private:
    int attackX = 140;

    public:
    void att1Animation()
    {   
        
        // Draw Racer 1
        FEHImage attPic1;
        attPic1.Open("Attacks/cookiecrunch1FEH.pic");

        FEHImage attPic2;
        attPic2.Open("Attacks/cookiecrunch2FEH.pic");

        bool isAtt1 = true;

        // display attack
        while (attackX >= 10) 
        {
            drawBattlefield();
            if(isAtt1){
                attPic1.Draw(attackX, 70);
            }
            else{
                attPic2.Draw(attackX, 70);
            }

            isAtt1 = !isAtt1;

            LCD.Update();

            // Update racer coordinates
            attackX -= 7;
        
            Sleep(0.05);
        }

        LCD.Update();
        attPic1.Close();
        attPic2.Close();
        LCD.Clear();
        drawBattlefield();

    }

    void att2Animation()
    {   
        
        // Draw Racer 1
        FEHImage attPic1;
        attPic1.Open("Attacks/cookieCyclone1FEH.pic");

        FEHImage attPic2;
        attPic2.Open("Attacks/cookieCyclone2FEH.pic");

        bool isAtt1 = true;

        // display attack
        while (attackX >= 10) 
        {
            drawBattlefield();
            if(isAtt1){
                attPic1.Draw(attackX, 70);
            }
            else{
                attPic2.Draw(attackX, 70);
            }

            isAtt1 = !isAtt1;

            LCD.Update();

            // Update racer coordinates
            attackX -= 7;
        
            Sleep(0.05);
        }

        LCD.Update();
        attPic1.Close();
        attPic2.Close();
        LCD.Clear();
        drawBattlefield();

    }

    void att3Animation()
    {   
        
        // Draw Racer 1
        FEHImage heal1;
        heal1.Open("Attacks/heal1FEH.pic");
        FEHImage heal2;
        heal2.Open("Attacks/heal2FEH.pic");

        // display attack
        bool isHeal1 = true;
        for(int i = 0; i < 5; i++){
            if(isHeal1){
                heal1.Draw(210, 70);
                Sleep(0.25);
                LCD.Clear();
                drawBattlefield();
            }
            else{
                heal2.Draw(210, 70);
                Sleep(0.25);
                LCD.Clear();
                drawBattlefield();
            }
            isHeal1 = !isHeal1;
        }

        LCD.Update();
        heal1.Close();
        heal2.Close();
        LCD.Clear();
        drawBattlefield();

    }


};

class cupcake
{
    private:
    int attackX = 140;

    public:
    void att1Animation()
    {   
        
        // Draw Racer 1
        FEHImage attPic1;
        attPic1.Open("Attacks/frostingfury1FEH.pic");

        FEHImage attPic2;
        attPic2.Open("Attacks/frostingfury2FEH.pic");

        bool isAtt1 = true;

        // display attack
        while (attackX >= 10) 
        {
            drawBattlefield();
            if(isAtt1){
                attPic1.Draw(attackX, 70);
            }
            else{
                attPic2.Draw(attackX, 70);
            }

            isAtt1 = !isAtt1;

            LCD.Update();

            // Update racer coordinates
            attackX -= 7;
        
            Sleep(0.05);
        }

        LCD.Update();
        attPic1.Close();
        attPic2.Close();
        LCD.Clear();
        drawBattlefield();

    }
    void att2Animation()
    {   
        
        // Draw Racer 1
        FEHImage heal1;
        heal1.Open("Attacks/heal1FEH.pic");
        FEHImage heal2;
        heal2.Open("Attacks/heal2FEH.pic");

        // display attack
        bool isHeal1 = true;
        for(int i = 0; i < 5; i++){
            if(isHeal1){
                heal1.Draw(210, 70);
                Sleep(0.25);
                LCD.Clear();
                drawBattlefield();
            }
            else{
                heal2.Draw(210, 70);
                Sleep(0.25);
                LCD.Clear();
                drawBattlefield();
            }
            isHeal1 = !isHeal1;
        }

        LCD.Update();
        heal1.Close();
        heal2.Close();
        LCD.Clear();
        drawBattlefield();

    }

    void att3Animation()
    {   
        
        // Draw Racer 1
        FEHImage heal1;
        heal1.Open("Attacks/heal1FEH.pic");
        FEHImage heal2;
        heal2.Open("Attacks/heal2FEH.pic");

        // display attack
        bool isHeal1 = true;
        for(int i = 0; i < 5; i++){
            if(isHeal1){
                heal1.Draw(210, 70);
                Sleep(0.25);
                LCD.Clear();
                drawBattlefield();
            }
            else{
                heal2.Draw(210, 70);
                Sleep(0.25);
                LCD.Clear();
                drawBattlefield();
            }
            isHeal1 = !isHeal1;
        }

        LCD.Update();
        heal1.Close();
        heal2.Close();
        LCD.Clear();
        drawBattlefield();

    }


};



class WinLossScreen{
    private:
    int buttonWidth = 160, buttonHeight = 30;
    int buttonX = (320/2) - (buttonWidth / 2);
    int replayY =(240 / 2) - (buttonHeight / 2);
    int menuY = replayY + 45;

    FEHIcon::Icon mainMenu;
    FEHIcon::Icon replay;

    public:
    void drawScreen(){
        LCD.Clear(BLACK);
        
        LCD.SetFontColor(LIGHTBLUE);
        if(health.character > 0){
            LCD.WriteAt("You Won!", 160 - (strlen("You Won!") * 6), 20);
        }
        else{
            LCD.WriteAt("You Lost! Try Again!", 160 - (strlen("You Lost! Try Again!") * 6), 20);
        }

        mainMenu.SetProperties("Main Menu", buttonX, menuY, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);
        replay.SetProperties("Replay", buttonX, replayY, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);

        mainMenu.Draw();
        replay.Draw();
    }

    int optionSelected(){
        float x, y;
        float xTouch, yTouch;
        float xTrash, yTrash;

        while(true){
            LCD.Touch(&x, &y);
            if(mainMenu.Pressed(x, y, 0)){
                while(mainMenu.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= buttonX + buttonWidth && xTouch >= buttonX) && (yTouch <= menuY + buttonHeight && yTouch >= menuY)){
                            return 2;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                mainMenu.Deselect();

                
            }
            else if(replay.Pressed(x, y, 0)){
                while(replay.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= buttonX + buttonWidth && xTouch >= buttonX) && (yTouch <= replayY + buttonHeight && yTouch >= replayY)){
                            return 1;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                replay.Deselect();

                
            }
        }
    }

};


class AttackScreen{
    private:
    int screenWidth = 320;
    int screenHeight = 80;

    int buttonWidth = 150;
    int buttonHeight = 30;

    int option1X = (320/4) - (buttonWidth / 2), option1Y = 240 - screenHeight + 8;
    int option2X = (320/4) - (buttonWidth / 2), option2Y = option1Y + buttonHeight + 5;
    int option3X = (320/2) + 5, option3Y = option1Y;
    int option4X = (320/2) + 5, option4Y = option2Y;

    char attName1[30];
    char attName2[30];
    char attName3[30];
    char attName4[30];

    int damage1;
    int damage2;

    char charName[30];
    char oppName[30];

    char oppAttName1[30];
    char oppAttName2[30];
    char oppAttName3[30];

    int oppAtt1;
    int oppAtt2;
    int oppAtt3;

    bool buffed = false;
    int buff = 0;
    int randDodge = -1;
    bool dodge = false;

    FEHIcon::Icon option1;
    FEHIcon::Icon option2;
    FEHIcon::Icon option3;
    FEHIcon::Icon option4;

    //FEHIcon::Icon charHealth;
    //FEHIcon::Icon bossHealth;
    public:
    void drawAttackScreen(){
        
        //LCD.Clear();
        LCD.SetFontColor(BLACK);
        LCD.FillRectangle(0, 240 - screenHeight, screenWidth, screenHeight);

        LCD.SetFontColor(GREEN);
        LCD.DrawVerticalLine(320 / 2, 240 - screenHeight, 240);
        LCD.DrawHorizontalLine(240 - (screenHeight / 2), 0, 320);

        if(selections.characterSelect == 1){
            strcpy(attName1, strawberryOptions.option1Name);
            strcpy(attName2, strawberryOptions.option2Name);
            strcpy(attName3, strawberryOptions.option3Name);
            strcpy(attName4, strawberryOptions.option4Name);
            
            option1.SetProperties(attName1, option1X, option1Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);
            option2.SetProperties(attName2, option2X, option2Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);
            option3.SetProperties(attName3, option3X, option3Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);
            option4.SetProperties(attName4, option4X, option4Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);

            if(buff == 0){
                damage1 = strawberryOptions.option1Damage;
                damage2 = strawberryOptions.option2Damage;
            }
            
            strcpy(charName, "You");
        }
        else if(selections.characterSelect == 2){
            strcpy(attName1, watermelonOptions.option1Name);
            strcpy(attName2, watermelonOptions.option2Name);
            strcpy(attName3, watermelonOptions.option3Name);
            strcpy(attName4, watermelonOptions.option4Name);

            option1.SetProperties(attName1, option1X, option1Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);
            option2.SetProperties(attName2, option2X, option2Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);
            option3.SetProperties(attName3, option3X, option3Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);
            option4.SetProperties(attName4, option4X, option4Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);

            if(buff == 0){
                damage1 = watermelonOptions.option1Damage;
                damage2 = watermelonOptions.option2Damage;
            }

            strcpy(charName, "You");
        }
        else{
            strcpy(attName1, mangoOptions.option1Name);
            strcpy(attName2, mangoOptions.option2Name);
            strcpy(attName3, mangoOptions.option3Name);
            strcpy(attName4, mangoOptions.option4Name);

            option1.SetProperties(attName1, option1X, option1Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);
            option2.SetProperties(attName2, option2X, option2Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);
            option3.SetProperties(attName3, option3X, option3Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);
            option4.SetProperties(attName4, option4X, option4Y, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);

            if(buff == 0){
                damage1 = mangoOptions.option1Damage;
                damage2 = mangoOptions.option2Damage;
            }

            strcpy(charName, "You");
        }

        if(selections.bossSelect == 1){
            strcpy(oppAttName1, cookieOptions.option1Name);
            strcpy(oppAttName2, cookieOptions.option2Name);
            strcpy(oppAttName3, cookieOptions.option3Name);
            
            oppAtt1 = cookieOptions.option1Damage;
            oppAtt2 = cookieOptions.option2Damage;
            oppAtt3 = cookieOptions.option3Damage;
            strcpy(oppName, "Cookie");
        }
        else if(selections.bossSelect == 2){
            strcpy(oppAttName1, cupcakeOptions.option1Name);
            strcpy(oppAttName2, cupcakeOptions.option2Name);
            strcpy(oppAttName3, cupcakeOptions.option3Name);
            
            oppAtt1 = cupcakeOptions.option1Damage;
            oppAtt2 = cupcakeOptions.option2Damage;
            oppAtt3 = cupcakeOptions.option3Damage;
            strcpy(oppName, "Cupcake");
        }
        else{
            strcpy(oppAttName1, burgerOptions.option1Name);
            strcpy(oppAttName2, burgerOptions.option2Name);
            strcpy(oppAttName3, burgerOptions.option3Name);
            
            oppAtt1 = burgerOptions.option1Damage;
            oppAtt2 = burgerOptions.option2Damage;
            oppAtt3 = burgerOptions.option3Damage;
            strcpy(oppName, "Burger");
        }
        //option4.SetProperties(strawBerry.option4Name, (320/2) + 5, 240 - screenHeight + buttonHeight + 5, buttonWidth, buttonHeight, LIGHTBLUE, WHITE);
        LCD.SetFontColor(BLACK);
        
        LCD.FillRectangle(0, 0, 35, 25);
        LCD.FillRectangle(275, 0, 35, 25);
        charHealth.SetProperties("", 0, 0, 35, 25, DARKGRAY, WHITE);
        bossHealth.SetProperties("", 275, 0, 35, 25, DARKGRAY, WHITE);

        charHealth.ChangeLabelInt(health.character);
        bossHealth.ChangeLabelInt(health.boss);

        option1.Draw();
        option2.Draw();
        option3.Draw();
        option4.Draw();

        charHealth.Draw();
        bossHealth.Draw();
        LCD.Update();

    }
    void optionSelected(){
        float x, y;
        float xTouch, yTouch;
        float xTrash, yTrash;
        char damage[20];
        strawberry strawberryAnimation;
        watermelon watermelonAnimation;
        mango mangoAnimation;

        while(true){
            LCD.Touch(&x, &y);
            if(option1.Pressed(x, y, 0)){
                strcpy(damage, std::to_string(damage1).c_str());
                if(damage1 > 0){
                    strcat(damage, " Damage");
                }
                else{
                    strcpy(damage, std::to_string(damage1 * -1).c_str());
                    strcat(damage, " Heal");
                }
                option1.ChangeLabelString(damage);

                while(option1.Pressed(x, y, 1)){
                    //option1.ChangeLabelString("10 Damage");
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= option1X + buttonWidth && xTouch >= option1X) && (yTouch <= option1Y + buttonHeight && yTouch >= option1Y)){
                            displayAttack(charName, attName1);
                            switch (selections.characterSelect)
                            {
                                case 1:
                                strawberryAnimation.att1Animation();
                                
                                LCD.Update();
                                break;

                                case 2:
                                watermelonAnimation.att1Animation();
                                
                                LCD.Update();
                                break;

                                case 3:
                                mangoAnimation.att1Animation();
                                
                                LCD.Update();
                                break;
                            }
                            
                            if(damage1 > 0){
                                health.boss -= damage1;
                                stats.damageDealt += damage1;
                                if(health.boss < 0){
                                    health.boss = 0;
                                    bossHealth.ChangeLabelInt(health.boss);
                                    stats.wins++;
                                }
                            }
                            else{
                                health.character -= damage1;
                            }
                            return;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                option1.ChangeLabelString(attName1);
                option1.Deselect();

                
            }
            else if(option2.Pressed(x, y, 0)){
                strcpy(damage, std::to_string(damage2).c_str());
                if(damage2 > 0){
                    strcat(damage, " Damage");
                }
                else{
                    strcpy(damage, std::to_string(damage2 * -1).c_str());
                    strcat(damage, " Heal");
                }

                option2.ChangeLabelString(damage);
                while(option2.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= option2X + buttonWidth && xTouch >= option2X) && (yTouch <= option2Y + buttonHeight && yTouch >= option2Y)){
                            displayAttack(charName, attName2);
                            switch (selections.characterSelect)
                            {
                                case 1:
                                strawberryAnimation.att2Animation();
                                
                                LCD.Update();
                                break;

                                case 2:
                                watermelonAnimation.att2Animation();
                                
                                LCD.Update();
                                break;

                                case 3:
                                mangoAnimation.att2Animation();
                                
                                LCD.Update();
                                break;
                            }
                            if(damage2 > 0){
                                health.boss -= damage2;
                                stats.damageDealt += damage2;
                                if(health.boss < 0){
                                    health.boss = 0;
                                    bossHealth.ChangeLabelInt(health.boss);
                                    stats.wins++;
                                }
                            }
                            else{
                                health.character -= damage2;
                            }
                            //Sleep(3.0);
                            return;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                option2.ChangeLabelString(attName2);
                option2.Deselect();

                
            }
            
            else if(option3.Pressed(x, y, 0)){
                strcpy(damage, "+ 0-15 Att");

                option3.ChangeLabelString(damage);
                while(option3.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= option3X + buttonWidth && xTouch >= option3X) && (yTouch <= option3Y + buttonHeight && yTouch >= option3Y)){
                            buffed = true;
                            buff = Random.RandInt() % 15;
                            damage1 += buff;
                            displayAttack(charName, attName3);
                            LCD.Update();
                            return;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                option3.ChangeLabelString(attName3);
                option3.Deselect();

                
            }

            else if(option4.Pressed(x, y, 0)){
                strcpy(damage, "50% Chance");

                option4.ChangeLabelString(damage);
                while(option4.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= option4X + buttonWidth && xTouch >= option4X) && (yTouch <= option4Y + buttonHeight && yTouch >= option4Y)){
                            randDodge = Random.RandInt() % 2;
                            dodge = (randDodge == 1);
                            displayAttack(charName, attName3);
                            LCD.Update();
                            //Sleep(3.0);
                            return;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                option4.ChangeLabelString(attName4);
                option4.Deselect();

                
            }
            
        }
    }
    void randomBossAttack(){
        if(dodge){
            dodge = false;
            health.boss -= 7;
            return;
        }
        int randOption = Random.RandInt() % 3 + 1;

        cookie cookieAnimation;
        cupcake cupcakeAnimation;
        burger burgerAnimation;


        switch(randOption){
            case 1:
                displayAttack(oppName, oppAttName1);
                switch (selections.bossSelect)
                {
                    case 1:
                    cookieAnimation.att1Animation();
                    
                    LCD.Update();
                    break;

                    case 2:
                    cupcakeAnimation.att1Animation();
                    
                    LCD.Update();
                    break;

                    case 3:
                    burgerAnimation.att1Animation();
                    
                    LCD.Update();
                    break;
                }
                if(oppAtt1 > 0){
                    health.character -= oppAtt1;
                    if(health.character <= 0){
                        health.character = 0;
                        charHealth.ChangeLabelInt(health.character);
                        stats.losses++;
                        Sleep(1.0);
                        return;
                    }
                    
                }
                else{
                    health.boss -= oppAtt1;
                }
                charHealth.ChangeLabelInt(health.character);
                bossHealth.ChangeLabelInt(health.boss);
                LCD.Update();
                //Sleep(1.0);
                break;
            case 2:
                displayAttack(oppName, oppAttName2);
                switch (selections.bossSelect)
                {
                    case 1:
                    cookieAnimation.att2Animation();
                    
                    LCD.Update();
                    break;

                    case 2:
                    cupcakeAnimation.att2Animation();
                    
                    LCD.Update();
                    break;

                    case 3:
                    burgerAnimation.att2Animation();
                    
                    LCD.Update();
                    break;
                }
                if(oppAtt2 > 0){
                    health.character -= oppAtt2;
                    if(health.character <= 0){
                        health.character = 0;
                        charHealth.ChangeLabelInt(health.character);
                        stats.losses++;
                        Sleep(1.0);
                        return;
                    }
                }
                else{
                    health.boss -= oppAtt2;
                }
                charHealth.ChangeLabelInt(health.character);
                bossHealth.ChangeLabelInt(health.boss);
                LCD.Update();
                //Sleep(1.0);
                break;
            case 3:
                displayAttack(oppName, oppAttName3);
                switch (selections.bossSelect)
                {
                    case 1:
                    cookieAnimation.att3Animation();
                    
                    LCD.Update();
                    break;

                    case 2:
                    cupcakeAnimation.att3Animation();
                    
                    LCD.Update();
                    break;

                    case 3:
                    burgerAnimation.att3Animation();
                    
                    LCD.Update();
                    break;
                }
                if(oppAtt3 > 0){
                    health.character -= oppAtt3;
                    if(health.character <= 0){
                        health.character = 0;
                        charHealth.ChangeLabelInt(health.character);
                        stats.losses++;
                        Sleep(1.0);
                        return;
                    }
                }
                else{
                    health.boss -= oppAtt3;
                }
                charHealth.ChangeLabelInt(health.character);
                bossHealth.ChangeLabelInt(health.boss);
                LCD.Update();
                //Sleep(1.0);
                break;

        }
    }

    void displayAttack(char name[], char attName[]){
        LCD.SetFontColor(GRAY);
        LCD.FillRectangle(0, 240 - screenHeight, screenWidth, screenHeight);
        LCD.SetFontColor(BLACK);

        char message[65];
        if(randDodge != -1){
            if(dodge){
                strcpy(message, "Dodge Successful!");
            }
            else{
                strcpy(message, "Dodge Failed!");
            }
            LCD.WriteAt(message, (320 / 2) - strlen(message) * 6, 240 - (screenHeight / 2) - 9);
            LCD.Update();
            randDodge = -1;
        }
        else if(!buffed){
            strcpy(message, name);
            strcat(message, " used ");
            strcat(message, attName);
            strcat(message, "!");
        }
        else{
            strcpy(message, "Attack buffed ");
            strcat(message, std::to_string(buff).c_str());
            strcat(message, " damage!");
            buffed = false;
        }

        LCD.WriteAt(message, (320 / 2) - strlen(message) * 6, 240 - (screenHeight / 2) - 9);
        LCD.Update();
        Sleep(1.5);

    }



    
};
class Stats
{
    private:
    int middleX = 320/2;
    public:
    void displayStat(){
        LCD.Clear();
        LCD.SetBackgroundColor(BLACK);

        LCD.WriteAt("Stats:", middleX - (strlen("Stats:") * 6), 20);
        LCD.DrawHorizontalLine(38, middleX - (strlen("Stats:") * 6),  middleX + (strlen("Stats:") * 6));

        char winsText[40] = "Wins: ";
        char lossText[40] = "Losses: ";
        char rateText[40] = "Win Rate: ";
        char timeText[40] = "Best Time: ";
        char damageText[40] = "Damage Dealt: ";

        LCD.WriteAt(winsText, 0, 60);
        LCD.WriteAt(std::to_string(stats.wins), strlen(winsText) * 12, 60);
        LCD.WriteAt(lossText, 0, 90);
        LCD.WriteAt(std::to_string(stats.losses), strlen(lossText) * 12, 90);
        LCD.WriteAt(rateText, 0, 120);
        if(stats.losses + stats.wins == 0){
            LCD.WriteAt("N/A", strlen(rateText) * 12, 120);
        }
        else{
            char rate[30];
            strcpy(rate, std::to_string(100.0 * stats.wins / (stats.losses + stats.wins)).c_str());
            strcat(rate, "%");
            LCD.WriteAt(rate, strlen(rateText) * 12, 120);
        }
        LCD.WriteAt(timeText, 0, 150);
        if(stats.bestTime == 1000000000){
            LCD.WriteAt("N/A", strlen(timeText) * 12, 150);
        }
        else{
            char time[30];
            strcpy(time, std::to_string(stats.bestTime).c_str());
            strcat(time, " Seconds");
            LCD.WriteAt(time, strlen(timeText) * 12, 150);
        }
        LCD.WriteAt(damageText, 0, 180);
        LCD.WriteAt(std::to_string(stats.damageDealt), strlen(damageText) * 12, 180);
    }
};

class CharacterSelection
{
    private:
    int base1 = 93, base1X = 10;
    int base2 = 93, base2X = 113;
    int base3 = 94, base3X = 217;

    int height = 169;
    int buttonY = (240 / 2) - (height / 2) + 10;

    FEHIcon::Icon button1;
    FEHIcon::Icon button2;
    FEHIcon::Icon button3;

    int backButtonBase = 50;
    int backButtonHeight = 27;

    public:
    
    int fruitSelection = 0;

    void pickCharacter()
    {   
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();

        button1.SetProperties("", base1X, buttonY, base1, height, LIGHTBLUE, WHITE);
        button2.SetProperties("", base2X, buttonY, base2, height, LIGHTBLUE, WHITE);
        button3.SetProperties("", base3X, buttonY, base3, height, LIGHTBLUE, WHITE);

        button1.Draw();
        FEHImage strawberryDraw;
        strawberryDraw.Open("CharacterClasses/strawberryFEH.pic");
        strawberryDraw.Draw(base1X + (base1 / 2) - 50, buttonY + (height / 2) - 50);

        button2.Draw();
        FEHImage watermelonDraw;
        watermelonDraw.Open("CharacterClasses/watermelonFEH.pic");
        watermelonDraw.Draw(base2X + (base2 / 2) - 50, buttonY + (height / 2) - 50);

        button3.Draw();
        FEHImage mangoDraw;
        mangoDraw.Open("CharacterClasses/mangoFEH.pic");
        mangoDraw.Draw(base3X + (base3 / 2) - 50, buttonY + (height / 2) - 50);


        LCD.Update();
    }

    int characterSelection(){
        float x, y;
        float xTouch, yTouch;
        float xTrash, yTrash;

        LCD.WriteAt("BERRY", (base1X + (base1 / 2)) - (strlen("BERRY") * 6), buttonY + height - 30);
        LCD.WriteAt("MELON", (base2X + (base2 / 2)) - (strlen("MELON") * 6), buttonY + height - 30);
        LCD.WriteAt("MANGO", (base3X + (base3 / 2)) - (strlen("MANGO") * 6), buttonY + height - 30);

        while(true){
            LCD.Touch(&x, &y);
            if(button1.Pressed(x, y, 0)){
                while(button1.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= base1X + base1 && xTouch >= base1X) && (yTouch <= buttonY + height && yTouch >= buttonY)){
                            return 1;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                button1.Deselect();

                
            }

            else if(button2.Pressed(x, y, 0)){
                while(button2.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= base2X + base2 && xTouch >= base2X) && (yTouch <= base2 + height && yTouch >= buttonY)){
                            return 2;
                        }
                    }
                    LCD.Touch(&x, &y);
                }
                button2.Deselect();
                
            }

            else if(button3.Pressed(x, y, 0)){
                while(button3.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= base3X + base3 && xTouch >= base3X) && (yTouch <= base3 + height && yTouch >= buttonY)){
                            return 3;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                button3.Deselect();
                
            }
            else{
                LCD.ClearBuffer();
                if(LCD.Touch(&xTouch, &yTouch)){
                    while(LCD.Touch(&xTrash, &yTrash)){};
                    if(xTouch <= backButtonBase && yTouch <= backButtonHeight){
                        return 4;
                    }
                }

                LCD.Touch(&x, &y);

            }
        }

        
    }
};

class Difficulty
{
    private:
    int cookieBase = 93;
    int cookieHeight = 169;
    int cupcakeBase = 93;
    int cupcakeHeight = 169;
    int burgerBase = 94;
    int burgerHeight = 169;

    int cookieX = 10, cookieY = 120 - (cookieHeight / 2) + 10;
    int cupcakeX = 113, cupcakeY = 120 - (cupcakeHeight / 2) + 10;
    int burgerX = 217, burgerY = 120 - (burgerHeight / 2) + 10;

    FEHIcon::Icon cookieButton;
    FEHIcon::Icon cupcakeButton;
    FEHIcon::Icon burgerButton;

    int backButtonBase = 50;
    int backButtonHeight = 27;

    FEHIcon::Icon backButton;
    
    public:

    void pickBossScreen()
    {
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();

        cookieButton.SetProperties("", cookieX, cookieY, cookieBase, cookieHeight, LIGHTBLUE, WHITE);
        cupcakeButton.SetProperties("", cupcakeX, cupcakeY, cupcakeBase, cupcakeHeight, LIGHTBLUE, WHITE);
        burgerButton.SetProperties("", burgerX, burgerY, burgerBase, burgerHeight, LIGHTBLUE, WHITE);
        
        cookieButton.Draw();
        FEHImage cookieDraw;
        cookieDraw.Open("CharacterClasses/cookieFEH.pic");
        cookieDraw.Draw(cookieX + (cookieBase / 2) - 50, cookieY + (cookieHeight / 2) - 50);

        cupcakeButton.Draw();
        FEHImage cupcakeDraw;
        cupcakeDraw.Open("CharacterClasses/cupcakeFEH.pic");
        cupcakeDraw.Draw(cupcakeX + (cupcakeBase / 2) - 50, cupcakeY + (cupcakeHeight / 2) - 50);

        burgerButton.Draw();
        FEHImage burgerDraw;
        burgerDraw.Open("CharacterClasses/burgerFEH.pic");
        burgerDraw.Draw(burgerX + (burgerBase / 2) - 50, burgerY + (burgerHeight / 2) - 50);

        LCD.Update();

    }
    int difficultySelect(){
        float x, y;
        float xTouch, yTouch;
        float xTrash, yTrash;

        LCD.WriteAt("EASY", (cookieX + (cookieBase / 2)) - (strlen("EASY") * 6), cookieY + cookieHeight - 30);
        LCD.WriteAt("MEDIUM", (cupcakeX + (cupcakeBase / 2)) - (strlen("MEDIUM") * 6), cupcakeY + cupcakeHeight - 30);
        LCD.WriteAt("HARD", (burgerX + (burgerBase / 2)) - (strlen("HARD") * 6), burgerY + burgerHeight - 30);

        while(true){
            LCD.Touch(&x, &y);
            if(cookieButton.Pressed(x, y, 0)){
                while(cookieButton.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= cookieX + cookieBase && xTouch >= cookieX) && (yTouch <= cookieY + cookieHeight && yTouch >= cookieY)){
                            return 1;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                cookieButton.Deselect();

                
            }
            else if(cupcakeButton.Pressed(x, y, 0)){
                while(cupcakeButton.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= cupcakeX + cupcakeBase && xTouch >= cupcakeX) && (yTouch <= cupcakeY + cupcakeHeight && yTouch >= cupcakeY)){
                            return 2;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                cupcakeButton.Deselect();
                
            }
            else if(burgerButton.Pressed(x, y, 0)){
                while(burgerButton.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= burgerX + burgerBase && xTouch >= burgerX) && (yTouch <= burgerY + burgerHeight && yTouch >= burgerY)){
                            return 3;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                burgerButton.Deselect();
                
            }
            else{
                LCD.ClearBuffer();
                if(LCD.Touch(&xTouch, &yTouch)){
                    while(LCD.Touch(&xTrash, &yTrash)){};
                    if(xTouch <= backButtonBase && yTouch <= backButtonHeight){
                        return 4;
                    }
                }

                LCD.Touch(&x, &y);

            }
        }

        
    }

    
};

class MainMenu {
    private:
    int middleX = 319 / 2;
    int buttonHeight = 30;
    int playBase = 164, playY = 95;
    int statBase = 164, statY = playY + 37;
    int instructBase = 164, instructY = statY + 37;
    int credBase = 164, credY = instructY + 37;

    int backButtonBase = 50;
    int backButtonHeight = 27;

    FEHIcon::Icon backButton;
    
    public:
    void drawMenu(){
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();
        FEHImage background;
        background.Open("menuBackGround-2FEH.pic");
        background.Draw(0, 0);
        background.Close();
        LCD.SetFontColor(WHITE);

        FEHIcon::Icon playButton;
        FEHIcon::Icon statButton;
        FEHIcon::Icon instructButton;
        FEHIcon::Icon credButton;

        playButton.SetProperties("Play", middleX - (playBase / 2), playY, playBase, buttonHeight, LIGHTBLUE, WHITE);
        statButton.SetProperties("Statistics", middleX - (statBase / 2), statY, statBase, buttonHeight, LIGHTBLUE, WHITE);
        instructButton.SetProperties("Instructions", middleX - (instructBase / 2), instructY, instructBase, buttonHeight, LIGHTBLUE, WHITE);
        credButton.SetProperties("Credits", middleX - (credBase / 2), credY, credBase, buttonHeight, LIGHTBLUE, WHITE);
        
        FEHImage logo;
        logo.Open("fruitpunchLOGOFEH.pic");
        logo.Draw(160 - (95 / 2), 0);
        
        LCD.SetFontColor(BLACK);
        LCD.FillRectangle(middleX - (playBase / 2), playY, playBase, buttonHeight);
        LCD.FillRectangle(middleX - (statBase / 2), statY, statBase, buttonHeight);
        LCD.FillRectangle(middleX - (instructBase / 2), instructY, instructBase, buttonHeight);
        LCD.FillRectangle(middleX - (credBase / 2), credY, credBase, buttonHeight);
        
        LCD.SetFontColor(SEAGREEN);
        LCD.FillRectangle(middleX - (playBase / 2) + 4, playY + 4, playBase - 8, buttonHeight - 8);
        LCD.FillRectangle(middleX - (statBase / 2) + 4, statY + 4, statBase - 8, buttonHeight - 8);
        LCD.FillRectangle(middleX - (instructBase / 2) + 4, instructY + 4, instructBase - 8, buttonHeight - 8);
        LCD.FillRectangle(middleX - (credBase / 2) + 4, credY + 4, credBase - 8, buttonHeight - 8);

        playButton.Draw();
        statButton.Draw();
        instructButton.Draw();
        credButton.Draw();

        buttonsSelect(playButton, statButton, instructButton, credButton);

        LCD.Update();
    }

    void buttonsSelect(FEHIcon::Icon playButton, FEHIcon::Icon statButton, FEHIcon::Icon instructButton, FEHIcon::Icon credButton){
        float x, y;
        float xTouch, yTouch;
        float xTrash, yTrash;

        while(true){
            LCD.Touch(&x, &y);
            if(playButton.Pressed(x, y, 0)){
                while(playButton.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= middleX + (playBase / 2) && xTouch >= middleX - (playBase / 2)) && (yTouch <= playY + buttonHeight && yTouch >= playY)){
                            startPlay();
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                playButton.Deselect();

                
            }
            else if(statButton.Pressed(x, y, 0)){
                while(statButton.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= middleX + (statBase / 2) && xTouch >= middleX - (statBase / 2)) && (yTouch <= statY + buttonHeight && yTouch >= statY)){
                            Stats StatDisplay;
                            StatDisplay.displayStat();
                            drawBackButton();
                            isBackPressed();
                            return;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                statButton.Deselect();
                
            }
            else if(instructButton.Pressed(x, y, 0)){
                while(instructButton.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= middleX + (instructBase / 2) && xTouch >= middleX - (instructBase / 2)) && (yTouch <= instructY + buttonHeight && yTouch >= instructY)){
                            displayInstruct();
                            drawBackButton();
                            isBackPressed();
                            return;
                            
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                instructButton.Deselect();
                
            }
            else if(credButton.Pressed(x, y, 0)){
                while(credButton.Pressed(x, y, 1)){
                    LCD.ClearBuffer();
                    if(LCD.Touch(&xTouch, &yTouch)){
                        while(LCD.Touch(&xTrash, &yTrash)){};
                        if((xTouch <= middleX + (credBase / 2) && xTouch >= middleX - (credBase / 2)) && (yTouch <= credY + buttonHeight && yTouch >= credY)){
                            displayCred();
                            drawBackButton();
                            isBackPressed();
                            return;
                        }
                    }

                    LCD.Touch(&x, &y);
                }
                credButton.Deselect();
                
            }
        }

        
    }
    void startPlay(){
        Difficulty difficultyScreen;
        difficultyScreen.pickBossScreen();
        drawBackButton();
        selections.bossSelect = difficultyScreen.difficultySelect();
        bool playStart = true;
        while(selections.bossSelect != 4){
            CharacterSelection selection;
            selection.pickCharacter();
            drawBackButton();
            selections.characterSelect = selection.characterSelection();
            if(selections.characterSelect != 4){
                setImages();
                int replay = 1;
                int currentWins = stats.wins;
                while(replay == 1){
                    int startTime = time(NULL);
                    health.boss = 100;
                    health.character = 100;
                    LCD.Clear();
                    drawBattlefield();
                    AttackScreen attackStart;
                    while(health.boss > 0 && health.character > 0){
                        attackStart.drawAttackScreen();
                        attackStart.optionSelected();
                        if(health.boss > 0 && health.character > 0){
                            attackStart.drawAttackScreen();
                            attackStart.randomBossAttack();
                            drawBattlefield();
                        }
                        else{
                            Sleep(1.0);
                            break;
                        }
                    }
                    int totalTime = time(NULL) - startTime;
                    if(totalTime < stats.bestTime && (stats.wins == currentWins + 1)){
                        stats.bestTime = totalTime;
                    }
                    WinLossScreen endScreen;
                    endScreen.drawScreen();
                    replay = endScreen.optionSelected();
                }
                drawMenu();
                return;
            }
            difficultyScreen.pickBossScreen();
            drawBackButton();
            selections.bossSelect = difficultyScreen.difficultySelect();
        }
        if(selections.bossSelect == 4){
            drawMenu();
            return;
        }
    }

    //display stat function moved to stats.h

    void displayInstruct(){
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();
            
        LCD.SetFontColor(LIGHTBLUE);

        LCD.WriteAt("Instructions:", middleX - (strlen("Instructions:") * 6), 20);
        LCD.DrawHorizontalLine(38, middleX - (strlen("Instructions:") * 6),  middleX + (strlen("Instructions:") * 6));
        
        LCD.WriteAt("1. Select Difficulty.", 0, 60);
        LCD.WriteAt("2. Select Fruit Character", 0, 90);
        LCD.WriteAt("3. Exchange attacks with", 0, 120);
        LCD.WriteAt("the opponent", 0, 150);
        LCD.WriteAt("Last Player Standing Wins!", 160 - (strlen("Last Player Standing Wins!") * 6), 200);
        LCD.DrawHorizontalLine(218, middleX - (strlen("Last Player Standing Wins!") * 6),  middleX + (strlen("Last Player Standing Wins!") * 6));

        LCD.Update();
    }
    void displayCred(){
        LCD.Clear();
        LCD.SetBackgroundColor(BLACK);
            
        LCD.SetFontColor(LIGHTBLUE);

        LCD.WriteAt("Credits:", middleX - (strlen("Credits:") * 6), 20);
        LCD.DrawHorizontalLine(38, middleX - (strlen("Credits:") * 6),  middleX + (strlen("Credits:") * 6));
        LCD.WriteAt("Fruit Punch was created by", 0, 50);
        LCD.WriteAt("Sidney Choo and", middleX - (strlen("Sidney Choo and") * 6), 70);
        LCD.WriteAt("Siddarth Tummala.", middleX - (strlen("Siddarth Tummala.") * 6), 90);
        LCD.WriteAt("Resources:", 0, 170);
        LCD.DrawHorizontalLine(188, 0,  strlen("Resources:") * 12);
        LCD.WriteAt("OSU FEH Proteus Guide", 0, 200);
                
        LCD.Update();
    }

    void drawBackButton(){
        
        backButton.SetProperties("<-", 0, 0, backButtonBase, backButtonHeight, LIGHTBLUE, WHITE);
        backButton.Draw();

    }

    bool isBackPressed(){
        float x, y;
        float xTouch, yTouch;
        float xTrash, yTrash;
        
            LCD.ClearBuffer();
            while(!LCD.Touch(&xTouch, &yTouch)){};
            while(LCD.Touch(&xTrash, &yTrash)){};
            if(xTouch <= backButtonBase && yTouch <= backButtonHeight){
                
                drawMenu();
            }
            

        
    }


};

int main() {
    // Clear background
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    MainMenu menu;
    menu.drawMenu();
    
    while (1) {
        LCD.Update();
        // Never end
    }
    return 0;
};