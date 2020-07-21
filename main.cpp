#include <iostream>
#include <memory>

using namespace std;

template <class T>

class Stack
{
public:
    Stack() { init(); }

    explicit Stack(size_t numElements, const T &initialValue = T())
    {
        init(numElements, initialValue);
    }

    Stack(const Stack &q) { init(q.bottom(), q.top()); }
    Stack &operator=(const Stack &rhs)
    {
        if (&rhs != this)
        {
            destroy();
            init(rhs.bottom(), rhs.top());
        }
        return *this;
    }

    ~Stack() { destroy(); }
    T *top() { return stackDataEnd - 1; }
    const T *top() const { return stackDataEnd - 1; }
    T *bottom() { return stackData; }
    const T *bottom() const { return stackData; }
    size_t size() const { return stackDataEnd - stackData; }
    bool empty() const { return size() == 0; }

    void pop()
    {
        if (top() != 0)
        {
            alloc.destroy(top());
            stackDataEnd -= 1;
        }
    }

    void push(const T &element)
    {
        if (stackDataEnd == memLimit)
            resize();
        append(element);
    }

private:
    void init()
    {
        stackData = stackDataEnd = memLimit = 0;
    }

    void init(size_t numElements, const T &initialValue)
    {
        stackData = alloc.allocate(numElements);
        stackDataEnd = memLimit = stackData + numElements;
        uninitialized_fill(stackData, stackDataEnd, initialValue);
    }

    void init(T *front, T *back)
    {
        stackData = alloc.allocate(back - front);
        memLimit = stackDataEnd = uninitialized_copy(front, back, stackData);
    }

    void destroy()
    {
        if (stackData != 0)
        {
            T *it = stackDataEnd;

            while (it != stackData)
            {
                alloc.destroy(--it);
            }
            alloc.deallocate(stackData, memLimit - stackData);
        }

        stackData = stackDataEnd = memLimit = 0;
    }

    void resize()
    {
        size_t newSize = max(2 * (stackDataEnd - stackData), ptrdiff_t(1));
        T *newData = alloc.allocate(newSize);
        T *newDataEnd = uninitialized_copy(stackData, stackDataEnd, newData);
        destroy();
        stackData = newData;
        stackDataEnd = newDataEnd;
        memLimit = stackData + newSize;
    }

    void append(const T &newValue)
    {
        alloc.construct(stackDataEnd++, newValue);
    }

    // the allocator object
    allocator<T> alloc;
    T *stackData;
    T *stackDataEnd;
    T *memLimit; // one past the end of allocated memory
};

template <class T>
class Queue
{
public:
    Queue() { init(); }
    explicit Queue(size_t numElements, const T &initialValue = T())
    {
        init(numElements, initialValue);
    }
    Queue(const Queue &q) { init(q.front(), q.back()); }
    Queue &operator=(const Queue &rhs)
    {
        if (&rhs != this)
        {
            destroy();
            init(rhs.front(), rhs.back());
        }
        return *this;
    }
    ~Queue() { destroy(); }
    T *front() { return queueData; }
    const T *front() const { return queueData; }
    T *back() { return queueDataEnd - 1; }
    const T *back() const { return queueDataEnd - 1; }
    size_t size() const { return queueDataEnd - queueData; }
    bool empty() const { return size() == 0; }
    void pop()
    {
        if (queueData != 0)
        {
            alloc.destroy(queueData);
            for (int i = 0; i < size(); i++)
            {
                queueData[i] = queueData[i + 1];
            }
            queueDataEnd -= 1;
        }
    }
    void push(const T &element)
    {
        if (queueDataEnd == memLimit)
            resize();
        append(element);
    }

private:
    void init()
    {
        queueData = queueDataEnd = memLimit = 0;
    }
    void init(size_t numElements, const T &initialValue)
    {
        queueData = alloc.allocate(numElements);
        queueDataEnd = memLimit = queueData + numElements;
        uninitialized_fill(queueData, queueDataEnd, initialValue);
    }
    void init(T *front, T *back)
    {
        queueData = alloc.allocate(back - front);
        memLimit = queueDataEnd = uninitialized_copy(front, back, queueData);
    }
    void destroy()
    {
        if (queueData != 0)
        {
            T *it = queueDataEnd;
            while (it != queueData)
            {
                alloc.destroy(--it);
            }
            alloc.deallocate(queueData, memLimit - queueData);
        }

        queueData = queueDataEnd = memLimit = 0;
    }

    void resize()
    {
        size_t newSize = max(2 * (queueDataEnd - queueData), ptrdiff_t(1));
        T *newData = alloc.allocate(newSize);
        T *newDataEnd = uninitialized_copy(queueData, queueDataEnd, newData);
        destroy();
        queueData = newData;
        queueDataEnd = newDataEnd;
        memLimit = queueData + newSize;
    }

    void append(const T &newValue)
    {
        alloc.construct(queueDataEnd++, newValue);
    }
    // the allocator object
    allocator<T> alloc;

    T *queueData;
    T *queueDataEnd;
    T *memLimit; // one past the end of allocated memory
};
int main()
{
    int choice;
    cout << "GENERIC QUEUES AND STACK!!!\n";
    cout << "Choose what do you want to implement.!"
         << "\n"
         << "1. Stack \n2. Queues\n";
    cin >> choice;
    if (choice == 1)
    {
        Stack<int> testStack;
        int stackchoice, loop_var = 1;
        while (loop_var)
        {
            cout << "\nChoose which operation you want to implement.\n";
            cout << "\n1. Push\n2. Pop\n3. Display Elements\n4. Exit\n";
            cin >> stackchoice;
            if (stackchoice == 1)
            {
                int element;
                cout << "\nEnter the element to be pushed: \n";
                cin >> element;
                testStack.push(element);
                cout << "\nElement pushed!!\n";
            }
            else if (stackchoice == 2)
            {
                testStack.pop();
                cout << "\nElement popped!!\n";
            }
            else if (stackchoice == 3)
            {
                cout << "\nstack contains values: \n";

                for (auto it = testStack.bottom(); it != testStack.top() + 1; ++it)
                {
                    cout << *it << " ";
                }
            }
            else if (stackchoice == 4)
            {
                loop_var = 0;
            }
        }
    }
    else if (choice == 2)
    {
        Queue<int> testQueue;
        int queuechoice, loop_var = 1;
        while (loop_var)
        {
            cout << "\nChoose which operation you want to implement.\n";
            cout << "\n1. Push\n2. Pop\n3. Display Elements\n4. Exit\n";
            cin >> queuechoice;
            if (queuechoice == 1)
            {
                int element;
                cout << "\nEnter the element to be pushed: \n";
                cin >> element;
                testQueue.push(element);
                cout << "\nElement pushed!!\n";
            }
            else if (queuechoice == 2)
            {
                testQueue.pop();
                cout << "\nElement popped!!\n";
            }
            else if (queuechoice == 3)
            {
                cout << "\nQueue contains values: \n";

                for (auto it = testQueue.front(); it != testQueue.back() + 1; ++it)
                {
                    cout << *it << " ";
                }
            }
            else if (queuechoice == 4)
            {
                loop_var = 0;
            }
        }
    }
    else
        cout << "\nInvalid Choice!!! Please Enter a valid choice.\n";
    return 0;
}