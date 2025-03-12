#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

// Функция для вычисления части суммы векторов
void addVectorsPart(const std::vector<int>& vec1,
                    const std::vector<int>& vec2,
                    std::vector<int>& result,
                    size_t start,
                    size_t end) {
  for (size_t i = start; i < end; ++i) {
    result[i] = vec1[i] + vec2[i];
  }
}

int main() {
  std::vector<size_t> sizes = {1000, 10000, 100000, 1000000};
  std::vector<int> threadCounts = {1, 2, 4, 8, 16};

  std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << std::endl << std::endl;

  // Таблица для вывода результатов
  std::cout << std::setw(15) << "Потоков";
  for (const auto& size : sizes) {
    std::cout << std::setw(15) << size;
  }
  std::cout << std::endl << std::string(75, '-') << std::endl;

  // Цикл по количеству потоков
  for (const auto& threadCount : threadCounts) {
    std::cout << std::setw(15) << threadCount;

    // Цикл по размерам массивов
    for (const auto& size : sizes) {
      // Создание двух векторов и заполнение их случайными значениями
      std::vector<int> vec1(size, 1);
      std::vector<int> vec2(size, 2);
      std::vector<int> result(size, 0);

      // Записываем время начала выполнения
      auto startTime = std::chrono::high_resolution_clock::now();

      // Создание вектора потоков
      std::vector<std::thread> threads;
      size_t chunkSize = size / threadCount;

      // Запуск потоков
      for (int i = 0; i < threadCount; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == threadCount - 1) ? size : start + chunkSize;
        threads.emplace_back(addVectorsPart, std::cref(vec1), std::cref(vec2), std::ref(result), start, end);
      }

      // Ожидание завершения всех потоков
      for (auto& thread : threads) {
        thread.join();
      }

      // Записываем время окончания выполнения
      auto endTime = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> duration = endTime - startTime;

      // Выводим результаты в таблицу
      std::cout << std::fixed << std::setprecision(7) << std::setw(14) << duration.count();
    }
    std::cout << std::endl;
  }

  return 0;
}
