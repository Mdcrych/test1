#include "sorted.h"
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <gtest/gtest.h>

class RandomObject {
private:
    int value;
    std::string word;

public:
    RandomObject(int temp_value = 0, std::string temp_word = "")
        : value(temp_value), word(temp_word) {}

    int getValue() const { return value; }
    void setValue(int val) { value = val; }
    void setWord(const std::string &wor) { word = wor; }
    std::string getWord() const { return word; }
    bool operator==(const RandomObject &b) const { return value == b.value; }
    bool operator<(const RandomObject &b) const { return value < b.value; }
    bool operator>(const RandomObject &b) const { return value > b.value; }
};

std::ostream &operator<<(std::ostream &strm, const RandomObject &a) {
    return strm << "[ value: " << a.getValue() << " word: " << a.getWord() << " ]";
}

template <class T>
void work(T arr[], int count) {
    std::cout << "Starting sorting..." << std::endl;

    // Запускаем сортировки в отдельных потоках
    std::thread t1(&Sorting::insertionSort<T>, arr, count);
    std::thread t2(&Sorting::bubbleSort<T>, arr, count);
    std::thread t3(&Sorting::heapSort<T>, arr, count);
    
    t1.join();
    t2.join();
    t3.join();

    std::cout << "Sorting completed." << std::endl;
}

// Тесты GTest
TEST(SortingTest, InsertionSort_EmptyArray) {
    RandomObject arr[0];
    Sorting::insertionSort(arr, 0);
}

TEST(SortingTest, InsertionSort_SingleElement) {
    RandomObject arr[1] = { RandomObject(5, "single") };
    Sorting::insertionSort(arr, 1);
    EXPECT_EQ(arr[0].getValue(), 5);
}

TEST(SortingTest, InsertionSort_MultipleElements) {
    RandomObject arr[5] = {
        RandomObject(5, "five"),
        RandomObject(3, "three"),
        RandomObject(2, "two"),
        RandomObject(4, "four"),
        RandomObject(1, "one")
    };
    Sorting::insertionSort(arr, 5);
    EXPECT_EQ(arr[0].getValue(), 1);
    EXPECT_EQ(arr[1].getValue(), 2);
    EXPECT_EQ(arr[2].getValue(), 3);
    EXPECT_EQ(arr[3].getValue(), 4);
    EXPECT_EQ(arr[4].getValue(), 5);
}

TEST(SortingTest, BubbleSort_EmptyArray) {
    RandomObject arr[0];
    Sorting::bubbleSort(arr, 0);
}

TEST(SortingTest, BubbleSort_SingleElement) {
    RandomObject arr[1] = { RandomObject(5, "single") };
    Sorting::bubbleSort(arr, 1);
    EXPECT_EQ(arr[0].getValue(), 5);
}

TEST(SortingTest, BubbleSort_MultipleElements) {
    RandomObject arr[5] = {
        RandomObject(5, "five"),
        RandomObject(3, "three"),
        RandomObject(2, "two"),
        RandomObject(4, "four"),
        RandomObject(1, "one")
    };
    Sorting::bubbleSort(arr, 5);
    EXPECT_EQ(arr[0].getValue(), 1);
    EXPECT_EQ(arr[1].getValue(), 2);
    EXPECT_EQ(arr[2].getValue(), 3);
    EXPECT_EQ(arr[3].getValue(), 4);
    EXPECT_EQ(arr[4].getValue(), 5);
}

TEST(SortingTest, HeapSort_EmptyArray) {
    RandomObject arr[0];
    Sorting::heapSort(arr, 0);
}

TEST(SortingTest, HeapSort_SingleElement) {
    RandomObject arr[1] = { RandomObject(5, "single") };
    Sorting::heapSort(arr, 1);
    EXPECT_EQ(arr[0].getValue(), 5);
}

TEST(SortingTest, HeapSort_MultipleElements) {
    RandomObject arr[5] = {
        RandomObject(5, "five"),
        RandomObject(3, "three"),
        RandomObject(2, "two"),
        RandomObject(4, "four"),
        RandomObject(1, "one")
    };
    Sorting::heapSort(arr, 5);
    EXPECT_EQ(arr[0].getValue(), 1);
    EXPECT_EQ(arr[1].getValue(), 2);
    EXPECT_EQ(arr[2].getValue(), 3);
    EXPECT_EQ(arr[3].getValue(), 4);
    EXPECT_EQ(arr[4].getValue(), 5);
}

int main(int argc, char** argv) {
    // Запуск тестов
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    
    // Основная логика приложения
    try {
        RandomObject arr[6];

        // Инициализация первого набора данных
        arr[0] = RandomObject(10, "l");
        arr[1] = RandomObject(12, "fddf");
        arr[2] = RandomObject(3, "Jfve");
        arr[3] = RandomObject(1, "Sbroije");
        arr[4] = RandomObject(52, "ossldfwe");
        arr[5] = RandomObject(12, "dfwefwfwe");
        work(arr, std::size(arr));

        // Инициализация второго набора данных
        arr[0] = RandomObject(1, "abfere");
        arr[1] = RandomObject(2, "efwvwefw");
        arr[2] = RandomObject(3, "dfwverfve");
        arr[3] = RandomObject(4, "dfwrverw");
        arr[4] = RandomObject(5, "efwfererg");
        arr[5] = RandomObject(7, "dfbrtnter");
        work(arr, std::size(arr));

        // Неправильный индекс исправлен
        arr[0].setValue(10);
        arr[1].setValue(9);
        arr[2].setValue(8);
        arr[3].setValue(7);
        arr[4].setValue(6);
        arr[5].setValue(5);
        work(arr, std::size(arr));
    }
    catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Неизвестная ошибка!" << std::endl;
    }
    return 0;
}