#include"../queue.hpp"

void test_que()
{
    queue<int> q;
    q.enqueue(0);
    cout << q.empty() << endl;
    cout << q.front() << endl;
    q.dequeue();
    q.enqueue(1);
    cout << q.front() << endl;
    q.dequeue();
    cout << q.empty() << endl;
}

int main()
{
    test_que();
    return 0;
}