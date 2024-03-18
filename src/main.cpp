#include <raylib.h>

int main(){
    InitWindow(1000, 1000, "My first raylib game");
    SetTargetFPS(60);
    Color yellow = {2,255,65,255};

    int ballX = 500;
    int ballY = 500;
    //Game Loop
    while(WindowShouldClose() == false){
        //Event Handling

        if(IsKeyDown(KEY_RIGHT))
        {
            ballX+=3;
        }else if (IsKeyDown(KEY_LEFT))
        {
            ballX-=3;
        }else if (IsKeyDown(KEY_UP))
        {
            ballY-=3;
        }else if (IsKeyDown(KEY_DOWN))
        {
            ballY+=3;
        }

        //Updating Drawing

        //Drawing
        BeginDrawing();
        ClearBackground(yellow);
        DrawCircle(ballX, ballY, 16, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}