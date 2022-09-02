#include "Enemy.h"

namespace Game
{
    void Enemy::Hurt(int damage)
    {
        if (_health - damage <= 0)
        {
            DestroyActor();
        }
        else
        {
            _health -= damage;
        }
    }

    void FindPathToPlayer()
    {

    }
}