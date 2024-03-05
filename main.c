#include <raylib.h>

static const int screenWidth  = 800;
static const int screenHeight = 400;
static Rectangle rec1 = { 0 };
static Rectangle rec2 = { 0 };
static Rectangle rec3 = { 0 };
//static int speed = 4;
static Vector2 speed = { 0 };
static bool collision = false;

void InitGame(void);
void UpdateFrame(void);
void DrawFrame(void);
void UpdateDrawFrame(void);

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Collision");
    InitGame();
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
       UpdateDrawFrame();
    } 
    CloseWindow();
    return 0;
}

void InitGame(void)
{
    rec1 = (Rectangle){screenWidth / 2 - 50, 50, 50, 50};
    rec2 = (Rectangle){screenWidth / 2 - 100, screenHeight / 2 - 50, 200, 100};
    collision = false;
    speed = (Vector2){4, 3};
}

void UpdateFrame(void)
{
   rec1.x = GetMouseX() - 25;
   rec1.y = GetMouseY() - 25;
   rec2.x += speed.x;  
   rec2.y += speed.y;

   if (rec2.x + rec2.width >= screenWidth || rec2.x <= 0)
       speed.x *= -1;
   else if(rec2.y <= 50 || rec2.y + rec2.height >= screenHeight)
       speed.y *= -1;
    collision = CheckCollisionRecs(rec1, rec2);

    if (collision) {
        rec3 =  GetCollisionRec(rec1, rec2);
    } 
}

void DrawFrame(void)
{
    BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangleRec(rec1, RED);
        DrawRectangleRec(rec2, BLUE);
        DrawLine(10, 49, screenWidth - 10, 49, BLACK);
        DrawLine(10, 50, screenWidth - 10, 50, BLACK);
        if (collision) {
            DrawRectangle(0, 0, screenWidth, 50, RED);
            DrawText("COLLISION!", screenWidth/2 - MeasureText("COLLISION!", 20)/2, 50/2 - 10, 20, WHITE);
            DrawRectangleRec(rec3, GREEN);
        }
    EndDrawing();
}

void UpdateDrawFrame(void)
{
    // Update
    UpdateFrame();
    // Draw
    DrawFrame();
}
