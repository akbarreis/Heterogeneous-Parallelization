#include <iostream>
#include <omp.h>
using namespace std;

// -----------------------------
// Односвязный список
// -----------------------------
struct Node {
    int data;
    Node* next;
};

// Добавление в начало
void listPushFront(Node*& head, int value) {
    Node* n = new Node{value, head};
    head = n;
}

// Удаление по значению
void listRemove(Node*& head, int value) {
    if (!head) return;

    if (head->data == value) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return;
    }

    Node* cur = head;
    while (cur->next && cur->next->data != value)
        cur = cur->next;

    if (cur->next) {
        Node* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
    }
}

// Поиск элемента
bool listSearch(Node* head, int value) {
    while (head) {
        if (head->data == value) return true;
        head = head->next;
    }
    return false;
}

// Печать списка
void listPrint(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}


// -----------------------------
// Стек
// -----------------------------
struct Stack {
    Node* top = nullptr;

    void push(int x) {
        Node* n = new Node{x, top};
        top = n;
    }

    int pop() {
        if (!top) return -1;
        Node* t = top;
        int val = t->data;
        top = top->next;
        delete t;
        return val;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};


// -----------------------------
// Очередь
// -----------------------------
struct Queue {
    Node* head = nullptr;
    Node* tail = nullptr;

    void enqueue(int x) {
        Node* n = new Node{x, nullptr};
        if (!tail) {
            head = tail = n;
            return;
        }
        tail->next = n;
        tail = n;
    }

    int dequeue() {
        if (!head) return -1;
        Node* tmp = head;
        int val = tmp->data;
        head = head->next;
        if (!head) tail = nullptr;
        delete tmp;
        return val;
    }

    bool isEmpty() { return head == nullptr; }
};


// -----------------------------
// Главная демонстрационная программа
// -----------------------------
int main() {
    cout << "=== Задание 2: Динамические структуры ===\n";

    // ----------------------------------------------------
    // Односвязный список
    // ----------------------------------------------------
    Node* head = nullptr;

    cout << "\n--- Односвязный список ---\n";
    listPushFront(head, 10);
    listPushFront(head, 20);
    listPushFront(head, 30);

    cout << "Список: ";
    listPrint(head);

    cout << "Поиск 20: " << (listSearch(head, 20) ? "найден" : "не найден") << endl;

    cout << "Удаление 20...\n";
    listRemove(head, 20);

    cout << "Список после удаления: ";
    listPrint(head);

    // ----------------------------------------------------
    // Стек
    // ----------------------------------------------------
    cout << "\n--- Стек ---\n";
    Stack st;
    st.push(5);
    st.push(15);
        st.push(25);

    cout << "pop: " << st.pop() << endl;
    cout << "pop: " << st.pop() << endl;
    cout << "Остался пустой? " << (st.isEmpty() ? "Да" : "Нет") << endl;

    // ----------------------------------------------------
    // Очередь
    // ----------------------------------------------------
    cout << "\n--- Очередь ---\n";
    Queue q;
    q.enqueue(100);
    q.enqueue(200);
    q.enqueue(300);

    cout << "dequeue: " << q.dequeue() << endl;
    cout << "dequeue: " << q.dequeue() << endl;
    cout << "Очередь пуста? " << (q.isEmpty() ? "Да" : "Нет") << endl;

    // ----------------------------------------------------
    // Параллельное добавление элементов
    // ----------------------------------------------------
    cout << "\n--- Параллельные операции (OpenMP) ---\n";

    Node* listParallel = nullptr;
    Queue queueParallel;

    int N = 20;

#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        #pragma omp critical  // защита списка
        listPushFront(listParallel, i);
    }

#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        #pragma omp critical  // защита очереди
        queueParallel.enqueue(i);
    }

    cout << "Список после параллельного добавления: ";
    listPrint(listParallel);

    cout << "Очередь после параллельного добавления: ";
    while (!queueParallel.isEmpty())
        cout << queueParallel.dequeue() << " ";
    cout << endl;

    return 0;
}

