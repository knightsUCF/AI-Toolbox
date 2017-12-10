#include <AIToolbox/Game/Policies/LRPPolicy.hpp>

#include <boost/python.hpp>

void exportGameLRPPolicy() {
    using namespace AIToolbox;
    using namespace boost::python;

    class_<Game::LRPPolicy, bases<Game::PolicyInterface>>{"LRPPolicy",

         "@brief This class models the Linear Reward Penalty algorithm.\n"
         "\n"
         "This algorithm performs direct policy updates depending on whether a\n"
         "given action was a success or a penalty.\n"
         "\n"
         "In particular, the version called 'Linear Reward-Inaction' (where the\n"
         "'b' parameter is set to zero) is guaranteed to converge to optimal in a\n"
         "stationary environment.\n"
         "\n"
         "Additionally, this algorithm can also be used in multi-agent settings,\n"
         "and will usually result in the convergence to some Nash equilibria.\n"
         "\n"
         "The successful updates are in the form:\n"
         "\n"
         "    p(t + 1) = p(t) + a * (1 − p(t))          // For the action taken\n"
         "    p(t + 1) = p(t) − a * p(t)                // For all other actions\n"
         "\n"
         "The failure updates are in the form:\n"
         "\n"
         "    p(t + 1) = (1 - b) * p(t)                 // For the action taken\n"
         "    p(t + 1) = b / (|A| - 1) + (1 - b) * p(t) // For all other actions", no_init}

        .def(init<size_t, double, optional<double>>(
                 "@brief Basic constructor.\n"
                 "\n"
                 "These two parameters control learning. The 'a' parameter\n"
                 "controls the learning when an action results in a success, while\n"
                 "'b' the learning during a failure.\n"
                 "\n"
                 "Setting 'b' to zero results in an algorithm called 'Linear\n"
                 "Reward-Inaction', while setting 'a' == 'b' results in the\n"
                 "'Linear Reward-Penalty' algorithm. Setting 'a' to zero results\n"
                 "in the 'Linear Inaction-Penalty' algorithm.\n"
                 "\n"
                 "By default the policy is initialized with uniform distribution.\n"
                 "\n"
                 "@param A The size of the action space.\n"
                 "@param a The learning parameter on successful actions.\n"
                 "@param b The learning parameter on failed actions."
        , (arg("self"), "A", "a", "b")))

        .def("stepUpdateQ",             &Game::LRPPolicy::stepUpdateQ,
                 "This function updates the LRP policy based on the result of the action.\n"
                 "\n"
                 "Note that LRP works with binary rewards: either the action\n"
                 "worked or it didn't.\n"
                 "\n"
                 "Environments where rewards are in R can be simulated: scale all\n"
                 "rewards to the [0,1] range, and stochastically obtain a success\n"
                 "with a probability equal to the reward. The result is equivalent\n"
                 "to the original reward function.\n"
                 "\n"
                 "@param a The action taken.\n"
                 "@param result Whether the action taken was a success, or not."
        , (arg("self"), "a", "result"))

        .def("setAParam",             &Game::LRPPolicy::setAParam,
                 "This function sets the a parameter.\n"
                 "\n"
                 "The a parameter determines the amount of learning on successful actions.\n"
                 "\n"
                 "@param a The new a parameter."
        , (arg("self"), "a"))

        .def("getAParam",             &Game::LRPPolicy::getAParam,
                 "This function will return the currently set a parameter.\n"
                 "\n"
                 "@return The currently set a parameter."
        , (arg("self")))

        .def("setBParam",             &Game::LRPPolicy::setBParam,
                 "This function sets the b parameter.\n"
                 "\n"
                 "The b parameter determines the amount of learning on losing actions.\n"
                 "\n"
                 "@param a The new b parameter."
        , (arg("self"), "b"))

        .def("getBParam",             &Game::LRPPolicy::getBParam,
                 "This function will return the currently set b parameter.\n"
                 "\n"
                 "@return The currently set b parameter."
        , (arg("self")));
}
