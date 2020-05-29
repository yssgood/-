#include "Level1.h"
#define LEVEL1_WIDTH 28
#define LEVEL1_HEIGHT 8

//could be 11 
#define LEVEL1_ENEMYCOUNT 23
unsigned int level1_data[] =
{
 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 3, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
//GLuint fontID;

bool fail = false; 
int count = 0;
Mix_Chunk* sound2;
Mix_Chunk* lose;

void Level1::Initialize() {

    state.nextScene = -1; 

    sound2 = Mix_LoadWAV("round_1.wav");
    lose = Mix_LoadWAV("you_lose.wav");

    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

    Mix_PlayChannel(0, sound2, 0);

    //GLuint mapTextureID = Util::LoadTexture("tileset.png");
    GLuint mapTextureID = Util::LoadTexture("tile_09.png");
    fontID = Util::LoadTexture("font1.png");
    //bounce = Mix_LoadWAV("bounce.wav");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
    // Move over all of the player and enemy code from initialization.
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1.95f, -3.75f, 0);
    state.player->movement = glm::vec3(0);
    state.player->speed = 1.5f;
    state.player->textureID = Util::LoadTexture("soldier1_gun.png");

    state.player->height = 0.1f;
    state.player->width = 0.1f;

    state.enemies = new Entity[LEVEL1_ENEMYCOUNT];
    
    GLuint enemyTextureID = Util::LoadTexture("robot_blue.png");
    GLuint bossID = Util::LoadTexture("zombie_head.png");
    GLuint bossID2 = Util::LoadTexture("zombie_body.png");
    GLuint bossID3 = Util::LoadTexture("zombie_leg.png");
    GLuint bulletID = Util::LoadTexture("bullet.png");
    GLuint sampleID = Util::LoadTexture("letterR.png");
    GLuint failID = Util::LoadTexture("text_gameover.png");
    GLuint medalID = Util::LoadTexture("shaded_medal8.png");

    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(10.50f, -3.75f, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WALKER;
    state.enemies[0].aiState = IDLE;
    
    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(9.89, -1.65, 0);
    state.enemies[1].speed = 0.65; 
    state.enemies[1].aiType = WALKER;
    state.enemies[1].aiState = IDLE;

    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(8.90, -6.65f, 0);
    state.enemies[2].speed = 0.86;
    state.enemies[2].aiType = WALKER;
    state.enemies[2].aiState = IDLE;

    state.enemies[3].entityType = BULLET;
    state.enemies[3].textureID = bulletID;
    state.enemies[3].speed = 3;
    state.enemies[3].aiType = STRAIGHT;
    state.enemies[3].aiState = DEAD;

    state.enemies[5].entityType = ENEMY;
    state.enemies[5].textureID = enemyTextureID;
    state.enemies[5].position = glm::vec3(13.50, -2.75, 0);
    state.enemies[5].speed = 0.6;
    state.enemies[5].aiType = WALKER;


    state.enemies[6].entityType = ENEMY;
    state.enemies[6].textureID = enemyTextureID;
    state.enemies[6].position = glm::vec3(14.50, -3.75f, 0);
    state.enemies[6].speed = 0.6;
    state.enemies[6].aiType = WALKER;

    state.enemies[4].entityType = ENEMY;
    state.enemies[4].textureID = enemyTextureID;
    state.enemies[4].position = glm::vec3(15.50f, -4.75f, 0);
    state.enemies[4].speed = 0.6;
    state.enemies[4].aiType = WALKER;

    state.enemies[7].entityType = ENEMY;
    state.enemies[7].textureID = bossID;
    state.enemies[7].position = glm::vec3(20.0, -0.65, 0);
    state.enemies[7].speed = 0.3;
    state.enemies[7].aiType = WALKER;

    state.enemies[8].entityType = ENEMY;
    state.enemies[8].textureID = bossID2;
    state.enemies[8].position = glm::vec3(20.0, -1.65, 0);
    state.enemies[8].speed = 0.3;
    state.enemies[8].aiType = WALKER;

    state.enemies[9].entityType = ENEMY;
    state.enemies[9].textureID = bossID2;
    state.enemies[9].position = glm::vec3(20.0, -2.65, 0);
    state.enemies[9].speed = 0.3;
    state.enemies[9].aiType = WALKER;

    state.enemies[10].entityType = ENEMY;
    state.enemies[10].textureID = bossID2;
    state.enemies[10].position = glm::vec3(20.0, -3.65, 0);
    state.enemies[10].speed = 0.3;
    state.enemies[10].aiType = WALKER;

    state.enemies[11].entityType = ENEMY;
    state.enemies[11].textureID = bossID2;
    state.enemies[11].position = glm::vec3(20.0, -4.65, 0);
    state.enemies[11].speed = 0.3;
    state.enemies[11].aiType = WALKER;

    state.enemies[12].entityType = ENEMY;
    state.enemies[12].textureID = bossID2;
    state.enemies[12].position = glm::vec3(20.0, -5.65, 0);
    state.enemies[12].speed = 0.3;
    state.enemies[12].aiType = WALKER;

    state.enemies[13].entityType = ENEMY;
    state.enemies[13].textureID = bossID3;
    state.enemies[13].position = glm::vec3(20.0, -6.65, 0);
    state.enemies[13].speed = 0.3;
    state.enemies[13].aiType = WALKER;

    state.enemies[15].entityType = MEDAL;
    state.enemies[15].textureID = medalID;
    state.enemies[15].position = glm::vec3(21.0, -0.65, 0);
    state.enemies[15].speed = 0.3;

    state.enemies[16].entityType = MEDAL;
    state.enemies[16].textureID = medalID;
    state.enemies[16].position = glm::vec3(21.0, -1.65, 0);
    state.enemies[16].speed = 0.3;

    state.enemies[17].entityType = MEDAL;
    state.enemies[17].textureID = medalID;
    state.enemies[17].position = glm::vec3(21.0, -2.65, 0);
    state.enemies[17].speed = 0.3;

    state.enemies[18].entityType = MEDAL;
    state.enemies[18].textureID = medalID;
    state.enemies[18].position = glm::vec3(21.0, -3.65, 0);
    state.enemies[18].speed = 0.3;

    state.enemies[19].entityType = MEDAL;
    state.enemies[19].textureID = medalID;
    state.enemies[19].position = glm::vec3(21.0, -4.65, 0);
    state.enemies[19].speed = 0.3;

    state.enemies[20].entityType = MEDAL;
    state.enemies[20].textureID = medalID;
    state.enemies[20].position = glm::vec3(21.0, -5.65, 0);
    state.enemies[20].speed = 0.3;

    state.enemies[21].entityType = MEDAL;
    state.enemies[21].textureID = medalID;
    state.enemies[21].position = glm::vec3(21.0, -6.65, 0);
    state.enemies[21].speed = 0.3;

    state.enemies[22].entityType = MEDAL;
    state.enemies[22].textureID = medalID;
    state.enemies[22].position = glm::vec3(21.0, -7.65, 0);
    state.enemies[22].speed = 0.3;

    state.enemies[14].entityType = LETTER;
    state.enemies[14].textureID = failID;
    state.enemies[14].speed = 0.3;
    state.enemies[14].isActive = false;

}
void Level1::Update(float deltaTime) {
    state.player->UpdateforMenu(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
    for (int i = 0; i < LEVEL1_ENEMYCOUNT; ++i) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, state.enemies[3], LEVEL1_ENEMYCOUNT, state.map);
    }

    for (int i = 0; i < LEVEL1_ENEMYCOUNT; ++i) {
        if (state.enemies[i].collidedLeft && state.enemies[i].lastCollision != state.player) {
            state.enemies[i].aiState = DEAD; 
            state.enemies[3].aiState = DEAD;
        }

        else if (state.enemies[i].collidedLeft && state.enemies[i].lastCollision == state.player) {
            fail = true; 
            if (fail) {
                Mix_PlayChannel(0, lose, 0);
                state.enemies[14].position = glm::vec3(state.player->position.x, -3.75, 0);
                state.enemies[14].isActive = true;
                state.enemies[14].UpdateforMenu(deltaTime, state.player, state.enemies, LEVEL1_ENEMYCOUNT, state.map);
            }
            state.player->isActive = false;
            state.enemies[3].aiState = OVER;
            for (int i = 0; i < LEVEL1_ENEMYCOUNT-1; ++i) {
                if (i == 3) continue; 
                state.enemies[i].aiState = DEAD;
            }
        }
    }
    if (state.player->position.x >= 21) {
        state.nextScene = 2; 
    }
}
void Level1::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.player->Render(program);

    if (fail) {
        state.enemies[14].Render(program);
    }
    
    for (int i = 0; i < LEVEL1_ENEMYCOUNT-1; ++i) {
        state.enemies[i].Render(program);
    }
}

