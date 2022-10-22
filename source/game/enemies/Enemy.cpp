#include "Enemy.h"

#include "../../engine/controllers/EnemyController.h"

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

    EnemyController* Enemy::GetEnemyController() { return dynamic_cast<EnemyController*>(_controller); }
}