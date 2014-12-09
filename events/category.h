#ifndef CATEGORY_H
#define CATEGORY_H

namespace Category
{
    enum Type
    {
        None            = 0,
        SoundEffect     = 1 << 0,
        ParticleSystem  = 1 << 1,
        Player          = 1 << 2,
        Enemy           = 1 << 3,
        Trap            = 1 << 4,
        Explosion       = 1 << 5,
        Traplist        = 1 << 6,
        EntityLayer     = 1 << 7,
        FriendlyBullet  = 1 << 8,
        EnemyBullet     = 1 << 9,
        Camera          = 1 << 10,
        WaveGenerator   = 1 << 11
        // ...
        //MixedCategory        = Category1 | Category2,

    };
}

#endif // CATEGORY_H
