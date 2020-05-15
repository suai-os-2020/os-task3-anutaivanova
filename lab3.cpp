#include "lab3.h"
#include <Windows.h>
#include <stdio.h>


#define MAX_SEM_COUNT 10
#define THREADCOUNT 11

HANDLE mutex;
HANDLE semA, semB, semC, semD, semE, semF, semG, semH, semI, semK, semM;
HANDLE aThread[THREADCOUNT];
DWORD ThreadID;


unsigned int lab3_thread_graph_id() 
{
    return 10;
}

const char* lab3_unsynchronized_threads()
{
    return "dghi";
}

const char* lab3_sequential_threads()
{
    return "bcde";
}

DWORD WINAPI ThreadA(LPVOID name)
{
    // a=1
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(semA, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "a" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semC, 1, NULL))
            printf("Release Semaphore C error: %d\n", GetLastError());
    }


    return TRUE;
}

DWORD WINAPI ThreadB(LPVOID name)
{
    //b=1
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semB, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "b" << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semC, 1, NULL))
            printf("Release Semaphore C error: %d\n", GetLastError());
    }
    return TRUE;
}

DWORD WINAPI ThreadC(LPVOID name)
{
    //c=1
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(semC, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "c" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semD, 1, NULL))
            printf("Release Semaphore D error: %d\n", GetLastError());
    }
    //c=2
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semC, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "c" << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semD, 1, NULL))
            printf("Release Semaphore D error: %d\n", GetLastError());
    }

    return TRUE;
}

DWORD WINAPI ThreadD(LPVOID name)
{
    //d=1
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(semD, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "d" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semE, 1, NULL))
            printf("Release Semaphore E error: %d\n", GetLastError());
    }
    //d=2
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(semD, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "d" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semE, 1, NULL))
            printf("Release Semaphore E error: %d\n", GetLastError());
    }
    //d=3
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(semD, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "d" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semF, 1, NULL))
            printf("Release Semaphore F error: %d\n", GetLastError());
    }
    //d=4
    WaitForSingleObject(semD, INFINITE);

    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "d" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }

    return TRUE;
}

DWORD WINAPI ThreadE(LPVOID name)
{
    //e=1
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(semE, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "e" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();    

        if (!ReleaseSemaphore(semA, 1, NULL))
            printf("Release Semaphore A error: %d\n", GetLastError());
    }
    // e->b
        if (!ReleaseSemaphore(semB, 1, NULL))
            printf("Release Semaphore B error: %d\n", GetLastError());
    //e=2
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(semE, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "e" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semB, 1, NULL))
            printf("Release Semaphore B error: %d\n", GetLastError());
    }
    // e->b
        if (!ReleaseSemaphore(semD, 1, NULL))
            printf("Release Semaphore D error: %d\n", GetLastError());
    //e=3
    for (int i = 0; i < 3; ++i) {
        WaitForSingleObject(semE, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "e" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semD, 1, NULL))
            printf("Release Semaphore D error: %d\n", GetLastError());
    }

    return TRUE;
}

DWORD WINAPI ThreadF(LPVOID name)
{
    for (int i = 0; i < 3; ++i) 
    {
        WaitForSingleObject(semF, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "f" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semG, 1, NULL))
            printf("Release Semaphore G error: %d\n", GetLastError());
    }

    return TRUE;
}

DWORD WINAPI ThreadG(LPVOID name)
{
    // g=1
    for (int i = 0; i < 3; ++i) 
    {
        WaitForSingleObject(semG, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "g" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semE, 1, NULL))
            printf("Release Semaphore E error: %d\n", GetLastError());
    }
      
    //g=2
    WaitForSingleObject(semG, INFINITE);

    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "g" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    
    return TRUE;
}

DWORD WINAPI ThreadH(LPVOID name)
{
    //h=1
    WaitForSingleObject(semH, INFINITE);

    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "h" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
   
    return TRUE;
}

DWORD WINAPI ThreadI(LPVOID name)
{
    WaitForSingleObject(semI, INFINITE);

    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "i" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    //ждем dgh
    WaitForSingleObject(aThread[3], INFINITE);
    WaitForSingleObject(aThread[7], INFINITE);
    WaitForSingleObject(aThread[6], INFINITE);
    //i->k
    if (!ReleaseSemaphore(semK, 1, NULL))
        printf("Release Semaphore K error: %d\n", GetLastError());
    //i=2
    for (int i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semI, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "i" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semK, 1, NULL))
            printf("Release Semaphore K error: %d\n", GetLastError());
    }

    return TRUE;
}

DWORD WINAPI ThreadK(LPVOID name)
{
    for (int i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semK, INFINITE);
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "k" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semI, 1, NULL))
            printf("Release Semaphore I error: %d\n", GetLastError());
    }
    return TRUE;
}

DWORD WINAPI ThreadM(LPVOID name)
{
    WaitForSingleObject(semM, INFINITE);
    for (int i = 0; i < 3; ++i) {
        
        // Функция для захвата семафора. 
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "m" << std::flush;
        // Функция, освобождающая мьютекс.
        ReleaseMutex(mutex);
        computation();
    }

    return TRUE;
}


int lab3_init()
{
    // Функция для инициализации мьютекса.
    mutex = CreateMutex(NULL, FALSE, NULL);

    // Create a semaphore with initial and max counts of MAX_SEM_COUNT
    // Создание семафора с начальным и максимальным значениями счетчика равными MAX_SEM_COUNT

    semA = CreateSemaphore(
        NULL, // default security attributes // аттрибуты безопасности по умолчанию
        1,    // initial count               // начальное значение счетчика
        1,    // maximum count               // максимальное значение счетчика
        NULL);// unnamed semaphore           // безымянный семафор
    if (semA == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semB = CreateSemaphore(NULL,0,1,NULL);  
    if (semB == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semC = CreateSemaphore(NULL, 0, 1, NULL);
    if (semC == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semD = CreateSemaphore(NULL, 0, 1, NULL);
    if (semD == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semE = CreateSemaphore(NULL, 0, 1, NULL);
    if (semE == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semF = CreateSemaphore(NULL, 0, 1, NULL);
    if (semF == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semG = CreateSemaphore(NULL, 0, 1, NULL);
    if (semG == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semH = CreateSemaphore(NULL, 0, 1, NULL);
    if (semH == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semI = CreateSemaphore(NULL, 0, 1, NULL);
    if (semI == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semK = CreateSemaphore(NULL, 0, 1, NULL);
    if (semK == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semM = CreateSemaphore(NULL, 0, 1, NULL);
    if (semM == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }


    // Create worker threads
    // Создаем потоки

    aThread[0] = CreateThread(
            NULL,       // default security attributes   // аттрибуты безопасности по умолчанию
            0,          // default stack size            // размер стека по умолчанию
            ThreadA,
            NULL,       // no thread function arguments  // отсутствуют аргументы для функции-тела потока
            0,          // default creation flags        // флаги создания потока по умолчанию
            &ThreadID); // receive thread identifier     // идентификатор потока

    aThread[1] = CreateThread(NULL,0,ThreadB,NULL,0,&ThreadID);
    aThread[2] = CreateThread(NULL,0,ThreadC,NULL,0,&ThreadID);
    aThread[3] = CreateThread(NULL,0,ThreadD,NULL,0,&ThreadID);
    aThread[4] = CreateThread(NULL,0,ThreadE,NULL,0,&ThreadID);
    aThread[5] = CreateThread(NULL,0,ThreadF,NULL,0,&ThreadID);
    aThread[6] = CreateThread(NULL,0,ThreadG,NULL,0,&ThreadID);
    aThread[7] = CreateThread(NULL,0,ThreadH,NULL,0,&ThreadID);
    aThread[8] = CreateThread(NULL,0,ThreadI,NULL,0,&ThreadID); 
    aThread[9] = CreateThread(NULL,0,ThreadK,NULL,0,&ThreadID);
    aThread[10] = CreateThread(NULL,0,ThreadM,NULL,0,&ThreadID);

    WaitForSingleObject(aThread[4], INFINITE);
     
    if (!ReleaseSemaphore(semG, 1, NULL))
        printf("Release Semaphore G error: %d\n", GetLastError());

    if (!ReleaseSemaphore(semH, 1, NULL))
        printf("Release Semaphore H error: %d\n", GetLastError());

    if (!ReleaseSemaphore(semI, 1, NULL))
        printf("Release Semaphore H error: %d\n", GetLastError());

    WaitForSingleObject(aThread[9],INFINITE);
    WaitForSingleObject(aThread[8], INFINITE);

    if (!ReleaseSemaphore(semM, 1, NULL))
        printf("ReleaseSemaphore M error: %d\n", GetLastError());

    // Wait for all threads to terminate
    // Ждем завершения всех потоков

    for (int i = 0; i < THREADCOUNT; i++) {
        WaitForSingleObject(aThread[i], INFINITE);
        CloseHandle(aThread[i]);
    }

    // Close thread and semaphore handles
    // Закрываем потоки и дескриптор семафора

    CloseHandle(semA);
    CloseHandle(semB);
    CloseHandle(semC);
    CloseHandle(semD);
    CloseHandle(semE);
    CloseHandle(semF);
    CloseHandle(semG);
    CloseHandle(semH);
    CloseHandle(semI);
    CloseHandle(semK);
    CloseHandle(semM);

    return 0;
}
