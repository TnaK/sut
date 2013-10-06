#ifndef SIMPLE_UNIT_TESTING_FRAMEWORK
#define SIMPLE_UNIT_TESTING_FRAMEWORK

#define DESCRIBE(system_under_test) \
auto main() -> int \
{ \
    int pico_failed_tests = 0; \
    const char * pico_current_test = nullptr; \
    fprintf(stdout, "\n%s\n  ", system_under_test); \

#define END() \
    fprintf(stdout, "\n\n%d failed tests\n\n", pico_failed_tests); \
    return pico_failed_tests; \
}

#define IT(pico_test_name, expr) \
    pico_current_test = pico_test_name; \
    try { [&](){ expr }(); fprintf(stdout, "."); } \
    catch (...) { pico_failed_tests++; fprintf(stdout, "f"); }

#define P_ASSERT(condition, msg) \
if( !(condition) ) { \
    fprintf(stderr, "\n  %s.\n  It %s! It\'s not!\n", msg, pico_current_test); \
    fprintf(stderr, "  Assertion: %s\n", #condition); \
    fprintf(stderr, "    at %s:%d\n\n\t", __FILE__, __LINE__); \
    throw 1; \
} \

#endif /* SIMPLE_UNIT_TESTING_FRAMEWORK */
