#include <raylib.h>

int playerScore = 0;
int cpuScore = 0;

class Ball{
    public:
    float x,y;
    int radius,speed_x,speed_y;

    void Draw(){
        DrawCircle(x, y, radius, WHITE);
    }

    void Update(){
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0){
            speed_y *= -1;
        }
        if(x + radius >= GetScreenWidth()){
            cpuScore++;
            ResetBall();
        } 
        if(x - radius <= 0){
            playerScore++;
            ResetBall();
        }
    }

    void ResetBall(){
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int choices[2] = {-1,1};

        speed_x *= choices[GetRandomValue(0,1)];
        speed_y *= choices[GetRandomValue(0,1)];
    }
};

class Player{
    protected:
    void LimitMovement(){
        if(y <= 0){
            y = 0;
        }if(y + height >= GetScreenHeight()){
            y = GetScreenHeight() - height;
        }
    }
    public:
    float x,y;
    float width,height;
    int speed;

    void Draw(){
        DrawRectangle(x,y,width,height,WHITE);
    }

    void Update(){
        if(IsKeyDown(KEY_UP)){
            y -= speed;
        }
        if(IsKeyDown(KEY_DOWN)){
            y += speed;
        }
        LimitMovement();
    }
};

class CPU: public Player{
    public:

    void Draw(){
        DrawRectangle(x,y,width,height,WHITE);
    }

    void Update(int ball_y){
        if(y + height/2 > ball_y){
            y += speed;
        }if(y + height/2 <= ball_y){
            y -= speed;
        }
        LimitMovement();
    }

    void ResetPosition(){
        x = GetScreenHeight()/2 - height/2;

    }
};

Ball ball;
Player player;
CPU cpu;

int main(){

    int screenWidth = 1280;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "My first raylib game");
    SetTargetFPS(60);

    ball.radius = 16;
    ball.x = screenWidth/2;
    ball.y = screenHeight/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width=25;
    player.height=120;
    player.x=screenWidth-35;
    player.y=screenHeight/2-player.height/2;
    player.speed=6;

    cpu.width=25;
    cpu.height=120;
    cpu.x=10;
    cpu.y=screenHeight/2-cpu.height/2;
    cpu.speed=6;

    //Game Loop
    while(WindowShouldClose() == false){
        //Event Handling

        //Updating Drawing

        //Drawing
        BeginDrawing();

        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})){
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})){
            ball.speed_x *= -1;
        }

        ClearBackground(BLACK);

        DrawLine(screenWidth/2,0,screenWidth/2,screenHeight,WHITE);
        ball.Draw();
        player.Draw();
        cpu.Draw();

        DrawText(TextFormat("%i", cpuScore), 70, 10, 34, WHITE);
        DrawText(TextFormat("%i", playerScore), screenWidth - 70, 10, 34, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;

}