//
// Created by egor on 2/8/22.
//

#ifndef AZATHOTH_AZATHOTHASSERT_HPP
#define AZATHOTH_AZATHOTHASSERT_HPP

#define STR(x) #x

//#ifdef ASSERTIONS_ENABLED
#define AZATHOTH_ASSERT(x, msg) { \
    if (!(x)) {                   \
        printf("%s: (%s), function %s, file %s, line %d.\n", msg, STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); \
        abort();                      \
    }                             \
}
//#else
//#define AZATHOTH_ASSERT(x, msg) {}
//#endif

#endif //AZATHOTH_AZATHOTHASSERT_HPP
