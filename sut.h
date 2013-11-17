#ifndef SIMPLE_UNIT_TESTING_FRAMEWORK
#define SIMPLE_UNIT_TESTING_FRAMEWORK

#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class assertion_failure : public std::exception
{
public:
    
    explicit assertion_failure(const std::string& what_arg) noexcept
    {
        this->what_arg.assign(what_arg);
    }
    
    explicit assertion_failure(const char* what_arg) noexcept
    {
        this->what_arg.assign(what_arg);
    }
    
    virtual const char* what() const noexcept
    {
        return what_arg.c_str();
    }
    
private:
    std::string what_arg;
};

#define DESCRIBE(system_under_test) \
auto main() -> int \
{ \
    int simple_failed_tests = 0; \
    const char * simple_current_test = nullptr; \
    const char * simple_current_system = system_under_test; \
    std::function<void()> sut_setup = [&]{ }; \
    std::function<void()> sut_teardown = [&]{ }; \

#define END() \
    fprintf(stdout, "\n\n%d failed tests\n\n", simple_failed_tests); \
    return simple_failed_tests; \
}

#define BEFORE(...) { \
    sut_setup = [&] { __VA_ARGS__ }; \
}

#define AFTER(...) { \
    sut_teardown = [&] { __VA_ARGS__ }; \
}

#define IT(simple_test_name, ...) {\
    simple_current_test = simple_test_name; \
        try { sut_setup(); [&](){ __VA_ARGS__ }(); sut_teardown(); fprintf(stdout, "."); } \
    catch (assertion_failure &f) { \
        simple_failed_tests++; \
        std::cout << "f"; \
        std::cerr << std::endl; \
        std::cerr << "Scenario : " << simple_current_system << " " << simple_current_test << std::endl; \
        std::cerr << f.what() << std::endl; \
        std::cerr << "  at " << __FILE__ << ":" << __LINE__ << std::endl; \
    } \
    catch (std::exception &e) { \
        simple_failed_tests++; \
        std::cout << "e"; \
        std::cerr << std::endl; \
        std::cerr << "Scenario : " << simple_current_system << " " << simple_current_test << std::endl; \
        std::cerr << "Error    : " << e.what(); \
        std::cerr << "at " << __FILE__ << ":" << __LINE__ << std::endl; \
    } \
}

#define S_ASSERT(condition, msg) \
if( !(condition) ) { \
    std::stringstream what_arg; \
    what_arg << "Assertion: " << #condition << " failed!" << std::endl; \
    what_arg << "Message  : " << msg; \
    throw assertion_failure(what_arg.str()); \
} \

#define ASSERT(condition) \
if( !(condition) ) { \
    std::stringstream what_arg; \
    what_arg << "Assertion: " << #condition << " failed!" << std::endl; \
    throw assertion_failure(what_arg.str()); \
} \

#endif /* SIMPLE_UNIT_TESTING_FRAMEWORK */
