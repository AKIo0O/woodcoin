#ifndef HASHBLOCK_H
#define HASHBLOCK_H

#include "uint256.h"
#include "sph_skein.h"

#ifndef QT_NO_DEBUG
#include <string>
#endif

#ifdef GLOBALDEFINED
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL sph_skein512_context     z_skein;

#define fillz() do { \
    sph_skein512_init(&z_skein); \
} while (0) 

#define ZSKEIN (memcpy(&ctx_skein, &z_skein, sizeof(z_skein)))

template<typename T1>
inline uint256 Hash2(const T1 pbegin, const T1 pend)

{
    sph_skein512_context     ctx_skein;
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif

    uint512 mask = 8;
    uint512 zero = 0;
    
    uint512 hash[3];

    sph_skein512_init(&ctx_skein);
    // SKEIN;
    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[0]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[1]));


    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[1]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[2]));


    return hash[2].trim256();
}






#endif // HASHBLOCK_H
