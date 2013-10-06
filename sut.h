#ifndef SIMPLE_UNIT_TESTING_FRAMEWORK
#define SIMPLE_UNIT_TESTING_FRAMEWORK

#define DESCRIBE(system_under_test) \
auto main() -> int \
{ \
    int simple_failed_tests = 0; \
    const char * simple_current_test = nullptr; \
    fprintf(stdout, "\n%s\n  ", system_under_test); \

#define END() \
    fprintf(stdout, "\n\n%d failed tests\n\n", simple_failed_tests); \
    return simple_failed_tests; \
}

#define IT(simple_test_name, expr) \
    simple_current_test = simple_test_name; \
    try { [&](){ expr }(); fprintf(stdout, "."); } \
    catch (...) { simple_failed_tests++; fprintf(stdout, "f"); }

#define S_ASSERT(condition, msg) \
if( !(condition) ) { \
    fprintf(stderr, "\n  %s.\n  It %s! It\'s not!\n", msg, simple_current_test); \
    fprintf(stderr, "  Assertion: %s\n", #condition); \
    fprintf(stderr, "    at %s:%d\n\n\t", __FILE__, __LINE__); \
    throw 1; \
} \

#endif /* SIMPLE_UNIT_TESTING_FRAMEWORK */
