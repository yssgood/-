#include "Menu.h"
#define Menu_WIDTH 14
#define Menu_HEIGHT 8

#define Menu_ENEMYCOUNT 3
unsigned int menu_data[] =
{
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

Mix_Chunk* sound;

void Menu::Initialize() {
    state.nextScene = -1;
    sound = Mix_LoadWAV("ready.wav");

    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

    Mix_PlayChannel(0, sound, 0);

    //GLuint mapTextureID = Util::LoadTexture("tileset.png");
    GLuint mapTextureID = Util::LoadTexture("tile_09.png");
    fontID = Util::LoadTexture("font1.png");
    //bounce = Mix_LoadWAV("bounce.wav");
    state.map = new Map(Menu_WIDTH, Menu_HEIGHT, menu_data, mapTextureID, 1.0f, 4, 1);
    // Move over all of the player and enemy code from initialization.
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1.95f, -3.75f, 0);
    state.player->movement = glm::vec3(0);
    //state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 1.5f;
    //state.player->textureID = Util::LoadTexture("george_0.png");
    //state.player->textureID = Util::LoadTexture("spritesheet_characters.png");
    //state.player->textureID = Util::LoadTexture("player_tilesheet.png");
    state.player->textureID = Util::LoadTexture("soldier1_gun.png");

    //state.player->animRight = new int[4]{ 3, 7, 11, 15 };
    //state.player->animLeft = new int[4]{ 1, 5, 9, 13 };
    //state.player->animUp = new int[4]{ 2, 6, 10, 14 };
    //state.player->animDown = new int[4]{ 0, 4, 8, 12 };

    //state.player->animIndices = state.player->animRight;
    //state.player->animFrames = 4;
    //state.player->animIndex = 0;
    //state.player->animTime = 0;
    //state.player->animCols = 4;
    //state.player->animRows = 4;


    state.player->height = 0.1f;
    state.player->width = 0.1f;

    //state.player->jumpPower = 7.0f;
    //GLuint enemyTextureID = Util::LoadTexture("tile_183.png");
    state.enemies = new Entity[Menu_ENEMYCOUNT];


    GLuint enemyTextureID = Util::LoadTexture("robot_blue.png");
    GLuint letterR = Util::LoadTexture("letterR.png");
    GLuint letterS = Util::LoadTexture("letterS.png");
    GLuint bulletID = Util::LoadTexture("bullet.png");
    GLuint readyID = Util::LoadTexture("text_ready.png");
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = letterR;
    //state.enemies[0].position = glm::vec3(5, -0.65, 0);
    state.enemies[0].position = glm::vec3(4.50, -1.65f, 0);
    state.enemies[0].speed = 1;
    //state.enemies[0].aiType = WALKER;
    state.enemies[0].aiState = IDLE;

    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = letterS;
    state.enemies[1].position = glm::vec3(5.50, -1.65, 0);
    state.enemies[1].speed = 0.65;
    state.enemies[1].aiState = IDLE;

    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = readyID;
    state.enemies[2].position = glm::vec3(5, -3.75, 0);
    state.enemies[2].speed = 0.65;
    state.enemies[2].aiState = IDLE;

    state.player->isMenu = true; 

}
void Menu::Update(float deltaTime) {
    //state.player->Update(deltaTime, state.player, state.enemies, state.enemies[3], Menu_ENEMYCOUNT, state.map);
    state.player->UpdateforMenu(deltaTime, state.player, state.enemies, Menu_ENEMYCOUNT, state.map);
    for (int i = 0; i < Menu_ENEMYCOUNT; ++i) {
        //state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
        //state.enemies[i].Update(deltaTime, state.player, state.enemies, state.enemies[3], Menu_ENEMYCOUNT, state.map);
        state.enemies[i].UpdateforMenu(deltaTime, state.player, state.enemies, Menu_ENEMYCOUNT, state.map);
    }
    if (state.player->exitMenu == true) {
        state.nextScene = 1;
    }
}
void Menu::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.player->Render(program);
    for (int i = 0; i < Menu_ENEMYCOUNT; ++i) {
        state.enemies[i].Render(program);
    }
}