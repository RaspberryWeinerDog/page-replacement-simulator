#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <windows.h>
#include <iomanip>
#include <algorithm>

using namespace std;

// Вывод состояния кадров памяти
void printFrames(const vector<int>& frames) {
    cout << " |";
    for (int frame : frames) {
        if (frame == -1) cout << "  -  |";
        else cout << "  " << frame << "  |";
    }
    cout << endl;
}

// АЛГОРИТМЫ

void fifo(int numFrames, const vector<int>& sequence) {
    vector<int> frames(numFrames, -1);
    queue<int> q;
    int pageFaults = 0;

    cout << "\n=== FIFO ===\n";
    for (int page : sequence) {
        bool isHit = false;
        for (int f : frames) {
            if (f == page) { isHit = true; break; }
        }

        if (!isHit) {
            pageFaults++;
            if (q.size() == numFrames) {
                int oldPage = q.front();
                q.pop();
                // Находим и заменяем старую страницу
                for (int& f : frames) {
                    if (f == oldPage) { f = page; break; }
                }
            } else {
                for (int& f : frames) {
                    if (f == -1) { f = page; break; }
                }
            }
            q.push(page);
        }
        cout << "Запрос: " << setw(2) << page << " | Страничных прерываний: " << pageFaults;
        printFrames(frames);
    }
    cout << "Итого прерываний: " << pageFaults << " | Коэффициент отказов: " 
         << fixed << setprecision(2) << (double)pageFaults / sequence.size() * 100 << "%\n";
}

void lru(int numFrames, const vector<int>& sequence) {
    vector<int> frames(numFrames, -1);
    unordered_map<int, int> lastUsed; // страница -> время последнего использования
    int time = 0;
    int pageFaults = 0;

    cout << "\n=== LRU ===\n";
    for (int page : sequence) {
        time++;
        bool isHit = false;
        for (int f : frames) {
            if (f == page) { isHit = true; break; }
        }

        if (!isHit) {
            pageFaults++;
            if (frames[0] != -1 && count(frames.begin(), frames.end(), -1) == 0) {
                // Памяти нет, ищем наименее недавно использованную страницу
                int lruPage = frames[0];
                int minTime = lastUsed[lruPage];
                for (int f : frames) {
                    if (lastUsed[f] < minTime) {
                        minTime = lastUsed[f];
                        lruPage = f;
                    }
                }
                for (int& f : frames) {
                    if (f == lruPage) { f = page; break; }
                }
            } else {
                // Есть свободное место
                for (int& f : frames) {
                    if (f == -1) { f = page; break; }
                }
            }
        }
        lastUsed[page] = time;
        cout << "Запрос: " << setw(2) << page << " | Страничных прерываний: " << pageFaults;
        printFrames(frames);
    }
    cout << "Итого прерываний: " << pageFaults << " | Коэффициент отказов: " 
         << fixed << setprecision(2) << (double)pageFaults / sequence.size() * 100 << "%\n";
}

void clock(int numFrames, const vector<int>& sequence) {
    vector<pair<int, bool>> frames(numFrames, {-1, false}); // Номер страницы, R-бит
    int hand = 0; // Указатель
    int pageFaults = 0;

    cout << "\n=== CLOCK ===\n";
    for (int page : sequence) {
        bool isHit = false;
        for (int i = 0; i < numFrames; i++) {
            if (frames[i].first == page) {
                isHit = true;
                frames[i].second = true; // Устанавливаем R-бит в 1 при обращении
                break;
            }
        }

        if (!isHit) {
            pageFaults++;
            while (true) {
                if (frames[hand].first == -1) {
                    frames[hand] = {page, true};
                    hand = (hand + 1) % numFrames;
                    break;
                }
                if (frames[hand].second == false) {
                    frames[hand] = {page, true};
                    hand = (hand + 1) % numFrames;
                    break;
                } else {
                    frames[hand].second = false; //R-бит сбрасывается
                    hand = (hand + 1) % numFrames;
                }
            }
        }
        cout << "Запрос: " << setw(2) << page << " | Страничных прерываний: " << pageFaults;
        
        // Вывод с указанием R-бита
        cout << " | Кадры: ";
        for (int i = 0; i < numFrames; i++) {
            if (frames[i].first == -1) cout << "[-] ";
            else cout << "[" << frames[i].first << (frames[i].second ? "R" : " ") << "] ";
        }
        cout << endl;
    }
    cout << "Итого прерываний: " << pageFaults << " | Коэффициент отказов: " 
         << fixed << setprecision(2) << (double)pageFaults / sequence.size() * 100 << "%\n";
}

// ГЛАВНАЯ ФУНКЦИЯ

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    // Пример входных данных
    int numFrames = 3;
    vector<int> sequence = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};

    int choice;
    do {
        cout << "\n========================================\n";
        cout << "  МОДЕЛИРОВАНИЕ АЛГОРИТМОВ ЗАМЕЩЕНИЯ\n";
        cout << "========================================\n";
        cout << "  1. FIFO\n";
        cout << "  2. LRU\n";
        cout << "  3. CLOCK\n";
        cout << "  0. Выход\n";
        cout << "Выберите операцию: ";
        cin >> choice;

        switch (choice) {
            case 1: fifo(numFrames, sequence); break;
            case 2: lru(numFrames, sequence); break;
            case 3: clock(numFrames, sequence); break;
            case 0: cout << "Завершение работы программы.\n"; break;
            default: cout << "Некорректный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
    
    cout << "\nНажмите Enter для выхода...";
    cin.ignore();
    cin.get();
    return 0;
=======
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <windows.h>
#include <iomanip>
#include <algorithm>

using namespace std;

// Вывод состояния кадров памяти
void printFrames(const vector<int>& frames) {
    cout << " |";
    for (int frame : frames) {
        if (frame == -1) cout << "  -  |";
        else cout << "  " << frame << "  |";
    }
    cout << endl;
}

// АЛГОРИТМЫ

void fifo(int numFrames, const vector<int>& sequence) {
    vector<int> frames(numFrames, -1);
    queue<int> q;
    int pageFaults = 0;

    cout << "\n=== FIFO ===\n";
    for (int page : sequence) {
        bool isHit = false;
        for (int f : frames) {
            if (f == page) { isHit = true; break; }
        }

        if (!isHit) {
            pageFaults++;
            if (q.size() == numFrames) {
                int oldPage = q.front();
                q.pop();
                // Находим и заменяем старую страницу
                for (int& f : frames) {
                    if (f == oldPage) { f = page; break; }
                }
            } else {
                for (int& f : frames) {
                    if (f == -1) { f = page; break; }
                }
            }
            q.push(page);
        }
        cout << "Запрос: " << setw(2) << page << " | Страничных прерываний: " << pageFaults;
        printFrames(frames);
    }
    cout << "Итого прерываний: " << pageFaults << " | Коэффициент отказов: " 
         << fixed << setprecision(2) << (double)pageFaults / sequence.size() * 100 << "%\n";
}

void lru(int numFrames, const vector<int>& sequence) {
    vector<int> frames(numFrames, -1);
    unordered_map<int, int> lastUsed; // страница -> время последнего использования
    int time = 0;
    int pageFaults = 0;

    cout << "\n=== LRU ===\n";
    for (int page : sequence) {
        time++;
        bool isHit = false;
        for (int f : frames) {
            if (f == page) { isHit = true; break; }
        }

        if (!isHit) {
            pageFaults++;
            if (frames[0] != -1 && count(frames.begin(), frames.end(), -1) == 0) {
                // Памяти нет, ищем наименее недавно использованную страницу
                int lruPage = frames[0];
                int minTime = lastUsed[lruPage];
                for (int f : frames) {
                    if (lastUsed[f] < minTime) {
                        minTime = lastUsed[f];
                        lruPage = f;
                    }
                }
                for (int& f : frames) {
                    if (f == lruPage) { f = page; break; }
                }
            } else {
                // Есть свободное место
                for (int& f : frames) {
                    if (f == -1) { f = page; break; }
                }
            }
        }
        lastUsed[page] = time;
        cout << "Запрос: " << setw(2) << page << " | Страничных прерываний: " << pageFaults;
        printFrames(frames);
    }
    cout << "Итого прерываний: " << pageFaults << " | Коэффициент отказов: " 
         << fixed << setprecision(2) << (double)pageFaults / sequence.size() * 100 << "%\n";
}

void clock(int numFrames, const vector<int>& sequence) {
    vector<pair<int, bool>> frames(numFrames, {-1, false}); // Номер страницы, R-бит
    int hand = 0; // Указатель
    int pageFaults = 0;

    cout << "\n=== CLOCK ===\n";
    for (int page : sequence) {
        bool isHit = false;
        for (int i = 0; i < numFrames; i++) {
            if (frames[i].first == page) {
                isHit = true;
                frames[i].second = true; // Устанавливаем R-бит в 1 при обращении
                break;
            }
        }

        if (!isHit) {
            pageFaults++;
            while (true) {
                if (frames[hand].first == -1) {
                    frames[hand] = {page, true};
                    hand = (hand + 1) % numFrames;
                    break;
                }
                if (frames[hand].second == false) {
                    frames[hand] = {page, true};
                    hand = (hand + 1) % numFrames;
                    break;
                } else {
                    frames[hand].second = false; //R-бит сбрасывается
                    hand = (hand + 1) % numFrames;
                }
            }
        }
        cout << "Запрос: " << setw(2) << page << " | Страничных прерываний: " << pageFaults;
        
        // Вывод с указанием R-бита
        cout << " | Кадры: ";
        for (int i = 0; i < numFrames; i++) {
            if (frames[i].first == -1) cout << "[-] ";
            else cout << "[" << frames[i].first << (frames[i].second ? "R" : " ") << "] ";
        }
        cout << endl;
    }
    cout << "Итого прерываний: " << pageFaults << " | Коэффициент отказов: " 
         << fixed << setprecision(2) << (double)pageFaults / sequence.size() * 100 << "%\n";
}

// ГЛАВНАЯ ФУНКЦИЯ

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    // Пример входных данных
    int numFrames = 3;
    vector<int> sequence = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};

    int choice;
    do {
        cout << "\n========================================\n";
        cout << "  МОДЕЛИРОВАНИЕ АЛГОРИТМОВ ЗАМЕЩЕНИЯ\n";
        cout << "========================================\n";
        cout << "  1. FIFO\n";
        cout << "  2. LRU\n";
        cout << "  3. CLOCK\n";
        cout << "  0. Выход\n";
        cout << "Выберите операцию: ";
        cin >> choice;

        switch (choice) {
            case 1: fifo(numFrames, sequence); break;
            case 2: lru(numFrames, sequence); break;
            case 3: clock(numFrames, sequence); break;
            case 0: cout << "Завершение работы программы.\n"; break;
            default: cout << "Некорректный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
    
    cout << "\nНажмите Enter для выхода...";
    cin.ignore();
    cin.get();
    return 0;
>>>>>>> 070fece (chore: add .gitignore and initial project files)
}