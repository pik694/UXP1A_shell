//
// Created by Piotr Żelazko on 27.04.2018.
//
#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <shell/tasks/domain/tasks/ChildProcess.hpp>
#include <shell/tasks/domain/tasks/Pipeline.hpp>
#include <sys/wait.h>

using namespace shell::tasks;

BOOST_AUTO_TEST_SUITE(task_test_suite)


    BOOST_AUTO_TEST_CASE(run_simple_echo) {

        ChildProcess childProcess("echo", {"1", "2"});

        auto pid = childProcess.run();

        BOOST_REQUIRE(*pid > 0);

        int status;

        pid_t returnedPid;

        while ((returnedPid = waitpid(-1, &status, 0)) == -1) {
            if (errno != EINTR)
                throw std::system_error(errno, std::system_category());
        }

        BOOST_CHECK_EQUAL(returnedPid, *pid);

        BOOST_CHECK_EQUAL(status >> 8, 0);

        waitpid(-1, &status, 0);
        BOOST_CHECK_EQUAL(errno, ECHILD);

    }

    BOOST_AUTO_TEST_CASE(fifo_should_be_created_and_automatically_removed) {

        {
            Pipeline pipeline;

            BOOST_CHECK_EQUAL(pipeline.getName().empty(), false);
            BOOST_CHECK_EQUAL(pipeline.getName(), "/tmp/uxp1a_shell/pipelines/pipe0");

            BOOST_CHECK_NE(access("/tmp/uxp1a_shell/pipelines/pipe0", F_OK), -1);


            BOOST_CHECK_GT(pipeline.getInDescriptor(), 0);
            BOOST_CHECK_GT(pipeline.getOutDescriptor(), 0);
        }

        BOOST_CHECK_EQUAL(access("/tmp/uxp1a_shell/pipelines/pipe0", F_OK), -1);


    }


BOOST_AUTO_TEST_SUITE_END()


#endif //BOOST_TEST_DYN_LINK