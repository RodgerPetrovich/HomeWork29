#include <mutex>
#include <iostream>
#include <thread>

struct Node
{
    int value;
    Node* next;
    std::mutex* node_mutex;
};

class FineGrainedQueue
{
    Node* head;
    std::mutex* queue_mutex;
public:
    void insertIntoMiddle(int value, int pos)
    {
        Node* newNode = new Node();
        newNode->value = value;
        int curPos = 0;

        Node* cur, *prev;
        queue_mutex->lock();
        prev = this->head;
        cur = this->head->next;
        prev->node_mutex->lock();
        queue_mutex->unlock();
        cur->node_mutex->lock();
        
        while (cur)
        {
            if (curPos == pos)
            {
               
                prev->next = newNode;
                newNode->next = cur;
                prev->node_mutex->unlock();
                cur->node_mutex->unlock();
                return;
            }
            if (!cur->next)
            {
                cur->next = newNode;
                prev->node_mutex->unlock();
                cur->node_mutex->unlock();
                return;
            }
            Node* oldPrev = prev;
            prev = cur;
            cur->next->node_mutex->lock();
            cur = cur->next;
            curPos++;
            oldPrev->node_mutex->unlock();
        }
    }
};

int main()
{
    

    return 0;
}
