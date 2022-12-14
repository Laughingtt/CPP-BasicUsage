//
// Created by tian on 2022/8/8.
//

#ifndef LEARNING_FORKTEST_H
#define LEARNING_FORKTEST_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;


class ForkTest {
public:
    void test() {
        pid_t pid;
        char *msg;
        int k;
        pid = fork();
        switch (pid) {
            //子进程执行部分
            case 0:
                msg = "Child process is running.\n";
                k = 3;
                break;
            case -1:
                perror("Process creation failed.\n");
                break;
                //父进程执行部分
            default:
                msg = "Parent process is running.\n";
                k = 5;
                break;
        }
        //父子进程共同执行部分
        while (k > 0) {
            puts(msg);
            sleep(1);
            k--;
        }
    }
};


#endif //LEARNING_FORKTEST_H
