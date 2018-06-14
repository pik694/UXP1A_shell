//
// Created by Piotr Żelazko on 13.06.2018.
//
#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "MockTasks.hpp"

#include <shell/tasks/domain/tasks/decorator/BackgroundTask.hpp>
#include <shell/tasks/domain/tasks/ChildProcess.hpp>
#include <shell/tasks/domain/tasks/PipelinedTasks.hpp>
#include <shell/tasks/domain/tasks/decorator/StandardOutputRedirector.hpp>
#include <fcntl.h>
#include <shell/tasks/domain/tasks/Pipeline.hpp>
#include <shell/tasks/domain/tasks/decorator/StandardInputRedirector.hpp>

using namespace shell::tasks;
using namespace test::shell::tasks;

BOOST_AUTO_TEST_SUITE(tasks_manager_test_suite)

    BOOST_AUTO_TEST_CASE(newly_constructed_manager_should_have_no_children) {

        TasksManager manager;
        TasksManagerTester tester(manager);

        BOOST_CHECK_EQUAL(tester.getLastExitedChildren().empty(), true);
        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);


        manager.close();
    }


    BOOST_AUTO_TEST_CASE(newly_created_manager_should_close_and_leave_no_children) {

        TasksManager manager;
        TasksManagerTester tester(manager);

        manager.close();

        BOOST_CHECK_EQUAL(tester.getLastExitedChildren().empty(), true);
        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);

    }

    BOOST_AUTO_TEST_CASE(when_added_a_background_task_it_should_be_added_to_running_tasks) {


        TasksManager manager;
        TasksManagerTester tester(manager);


        auto task = std::unique_ptr<Task>(new MockChildProcessTask(1));
        auto decoratedTask = std::unique_ptr<Task>(new decorators::BackgroundTask(std::move(task)));

        manager.addTask(std::move(decoratedTask));

        BOOST_CHECK_EQUAL(tester.getLastExitedChildren().empty(), true);
        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), false);

        manager.close();
    }

    BOOST_AUTO_TEST_CASE(when_added_a_background_task_it_should_be_ereased_from_list_when_finished) {

        using namespace std::chrono_literals;

        TasksManager manager;
        TasksManagerTester tester(manager);


        auto task = std::unique_ptr<Task>(new MockChildProcessRunningTask(0));
        auto decoratedTask = std::unique_ptr<Task>(new decorators::BackgroundTask(std::move(task)));

        manager.addTask(std::move(decoratedTask));

        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), false);

        std::this_thread::sleep_for(1s);

        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);

        manager.close();


    }

    BOOST_AUTO_TEST_CASE(when_added_a_non_background_task_manager_should_not_add_it_to_running_childen) {

        TasksManager manager;
        TasksManagerTester tester(manager);

        auto task = std::unique_ptr<Task>(new MockChildProcessRunningTask(0));

        manager.addTask(std::move(task));

        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);

        manager.close();


    }


    BOOST_AUTO_TEST_CASE(should_not_crash_even_though_it_lost_some_child) {

        TasksManager manager;
        TasksManagerTester tester(manager);

        auto task = std::unique_ptr<Task>(new MockChildProcessTask(1));
        auto decoratedTask = std::unique_ptr<Task>(new decorators::BackgroundTask(std::move(task)));

        manager.addTask(std::move(decoratedTask));

        manager.close();

        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), false);


    }

    BOOST_AUTO_TEST_CASE(add_several_tasks_and_exit) {

        TasksManager manager;
        TasksManagerTester tester(manager);

        auto task = std::unique_ptr<Task>(new MockChildProcessRunningTask());
        auto decoratedTask = std::unique_ptr<Task>(new decorators::BackgroundTask(std::move(task)));

        manager.addTask(std::move(decoratedTask));


        task = std::unique_ptr<Task>(new MockChildProcessRunningTask());
        decoratedTask = std::unique_ptr<Task>(new decorators::BackgroundTask(std::move(task)));

        manager.addTask(std::move(decoratedTask));

        task = std::unique_ptr<Task>(new MockChildProcessRunningTask());
        decoratedTask = std::unique_ptr<Task>(new decorators::BackgroundTask(std::move(task)));

        manager.addTask(std::move(decoratedTask));

        manager.close();

        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);


    }

    BOOST_AUTO_TEST_CASE(cannot_add_task_when_already_closed) {

        TasksManager manager;
        TasksManagerTester tester(manager);

        auto task = std::unique_ptr<Task>(new MockChildProcessTask(1));
        auto decoratedTask = std::unique_ptr<Task>(new decorators::BackgroundTask(std::move(task)));

        manager.close();

        manager.addTask(std::move(decoratedTask));

        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);

    }

    BOOST_AUTO_TEST_CASE(run_child_task) {


        TasksManager manager;
        TasksManagerTester tester(manager);

        auto task = std::unique_ptr<Task>(new ChildProcess("echo", {"1", "2"}));

        manager.addTask(std::move(task));

        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);

        manager.close();
    }

    BOOST_AUTO_TEST_CASE(create_pipeline_manually) {

        Pipeline pipeline;

        auto writeTask = std::unique_ptr<Task>(new MockWriteTask("10"));
        auto readTask = std::unique_ptr<Task>(new MockReadTask());

        auto decoratedWrite = std::unique_ptr<Task>(
                new decorators::StandardOutputRedirector(std::move(writeTask), pipeline.getOutDescriptor())
        );

        auto decoratedRead = std::unique_ptr<Task>(
                new decorators::StandardInputRedirector(std::move(readTask), pipeline.getInDescriptor())
        );

        decoratedWrite->run();
        auto result = decoratedRead->run();

        BOOST_CHECK_EQUAL(*result, 10);

    }

    BOOST_AUTO_TEST_CASE(create_pipeline_manually_1) {

        Pipeline pipeline;

        auto writeTask = std::unique_ptr<Task>(new MockWriteProcessTask("10"));
        auto readTask = std::unique_ptr<Task>(new MockReadTask());

//        auto decoratedWrite = std::unique_ptr<Task>(
//                new decorators::StandardOutputRedirector(std::move(writeTask), pipeline.getOutDescriptor())
//        );

        auto decoratedRead = std::unique_ptr<Task>(
                new decorators::StandardInputRedirector(std::move(readTask), pipeline.getInDescriptor())
        );


//        decoratedWrite->run();

        writeTask->run();
        auto result = decoratedRead->run();

        BOOST_CHECK_EQUAL(*result, 10);

    }

    BOOST_AUTO_TEST_CASE(create_pipeline_manually_2) {

        Pipeline pipeline;

        auto writeTask = std::unique_ptr<Task>(new MockWriteTask("10"));
        auto readTask = std::unique_ptr<Task>(new ChildProcess("cat", {"/tmp/uxp1a_shell/pipe0"}));

        auto decoratedWrite = std::unique_ptr<Task>(
                new decorators::StandardOutputRedirector(std::move(writeTask), pipeline.getOutDescriptor())
        );


        decoratedWrite->run();
        readTask->run();

    }

//
//    BOOST_AUTO_TEST_CASE(mock_pipeline) {
//
//        TasksManager manager;
//        TasksManagerTester tester(manager);
//
//        auto readTaskPtr = new MockReadTask();
//
//        auto writeTask = std::unique_ptr<Task>(new MockWriteTask("10"));
//        auto readTask = std::unique_ptr<Task>(readTaskPtr);
//
//        std::list<std::unique_ptr<Task>> list;
//        list.emplace_back(std::move(writeTask));
//        list.emplace_back(std::move(readTask));
//
//        auto pipeline = std::unique_ptr<Task>(
//                new PipelinedTasks(manager, std::move(list))
//        );
//
//        manager.addTask(std::move(pipeline));
//        manager.close();
//
//
//
//    }
//
//    BOOST_AUTO_TEST_CASE(run_pipeline) {
//
//        TasksManager manager;
//        TasksManagerTester tester(manager);
//
//        auto echoTask = std::unique_ptr<Task>(new ChildProcess("echo", {"Sample Text\nHello World"}));
//        auto grepTask = std::unique_ptr<Task>(new ChildProcess("cat", {}));
////        auto grepTask = std::unique_ptr<Task>(new ChildProcess("cat", {"Hello"}));
//
//
//        std::list<std::unique_ptr<Task>> list;
//        list.emplace_back(std::move(echoTask));
//        list.emplace_back(std::move(grepTask));
//
//        auto pipeline = std::unique_ptr<Task>(
//                new PipelinedTasks(manager, std::move(list))
//        );
//
//        manager.addTask(std::move(pipeline));
//
//        manager.close();
//
//        BOOST_CHECK_EQUAL(tester.getRunningChildren().empty(), true);
//    }
//
//    BOOST_AUTO_TEST_CASE(playground) {
//
//
//        int inDesc = open("./fifo", O_RDONLY | O_NONBLOCK);
//        int outDesc = open("./fifo", O_WRONLY | O_NONBLOCK);
//
//
//        int descriptorCopy = dup(STDOUT_FILENO);
//        dup2(outDesc, STDOUT_FILENO);
//
//        std::cout << "Hello" << std::endl;
//
////        write(outDesc, "12345\n\0", 7);
//
//        dup2(descriptorCopy, STDOUT_FILENO);
//        close(descriptorCopy);
//
//        descriptorCopy = dup(STDIN_FILENO);
//        dup2(inDesc, STDIN_FILENO);
//
//
////        char str [10];
////        read(inDesc, str, 7);
//        std::string str;
//        std::cin >> str;
//
//        dup2(descriptorCopy, STDIN_FILENO);
//        close(descriptorCopy);
//
//        close(inDesc);
//
//
//        BOOST_CHECK_EQUAL(str, "Hello");
//
////        auto writeTask = std::unique_ptr<Task>(new MockWriteTask("HelloWorld"));
////        auto decorated = std::unique_ptr<Task>(
////                new decorators::StandardOutputRedirector(std::move(writeTask), "./file"));
////
////        decorated->run();
//    }


BOOST_AUTO_TEST_SUITE_END()


#endif //BOOST_TEST_DYN
