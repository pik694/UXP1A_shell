//
// Created by Piotr Żelazko on 13.06.2018.
//
#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "MockTasks.hpp"

#include <shell/tasks/domain/TasksManager.hpp>
#include <shell/tasks/domain/tasks/decorator/BackgroundTask.hpp>

using namespace shell::tasks;
using namespace test::shell::tasks;

BOOST_AUTO_TEST_SUITE(tasks_manager_test_suite)

    BOOST_AUTO_TEST_CASE(newly_constructed_manager_should_have_no_children) {

        TasksManager manager;
        TasksManagerTester tester(manager);

        BOOST_CHECK_EQUAL(tester.getChildrenExited(), false);
        BOOST_CHECK_EQUAL(tester.getLastExitedChildren().empty(), true);
        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);


        manager.close();
    }


    BOOST_AUTO_TEST_CASE(newly_created_manager_should_close_and_leave_no_children) {

        TasksManager manager;
        TasksManagerTester tester(manager);

        manager.close();

        BOOST_CHECK_EQUAL(tester.getChildrenExited(), false);
        BOOST_CHECK_EQUAL(tester.getLastExitedChildren().empty(), true);
        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);

    }

    BOOST_AUTO_TEST_CASE(when_added_a_background_task_it_should_be_added_to_running_tasks) {


        TasksManager manager;
        TasksManagerTester tester(manager);


        auto task = std::unique_ptr<Task> (new MockChildProcessTask());
        auto decoratedTask = std::unique_ptr<Task>(new decorators::BackgroundTask(std::move(task)));

        manager.addTask(std::move(decoratedTask));

        BOOST_CHECK_EQUAL(tester.getChildrenExited(), false);
        BOOST_CHECK_EQUAL(tester.getLastExitedChildren().empty(), true);
        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), false);

        manager.close();
    }

    BOOST_AUTO_TEST_CASE(when_added_a_background_task_it_should_be_ereased_from_list_when_finished) {

        using namespace std::chrono_literals;

        TasksManager manager;
        TasksManagerTester tester(manager);


        auto task = std::unique_ptr<Task> (new MockChildProcessRunningTask());
        auto decoratedTask = std::unique_ptr<Task>(new decorators::BackgroundTask(std::move(task)));

        manager.addTask(std::move(decoratedTask));

        std::this_thread::sleep_for(100ms);

        manager.close();

        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);

    }

    BOOST_AUTO_TEST_CASE(when_added_a_non_background_task_manager_should_not_add_it_to_running_childen) {

        TasksManager manager;
        TasksManagerTester tester(manager);

        auto task = std::unique_ptr<Task> (new MockChildProcessRunningTask());

        manager.addTask(std::move(task));

        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);

        manager.close();


    }


    BOOST_AUTO_TEST_CASE(should_not_crash_even_though_it_lost_some_child) {

        TasksManager manager;
        TasksManagerTester tester(manager);

        auto task = std::unique_ptr<Task> (new MockChildProcessTask());
        auto decoratedTask = std::unique_ptr<Task>(new decorators::BackgroundTask(std::move(task)));

        manager.addTask(std::move(decoratedTask));

        manager.close();

        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), false);


    }


BOOST_AUTO_TEST_SUITE_END()


#endif //BOOST_TEST_DYN
