#ifndef __RESOURCE_POOL__
#define __RESOURCE_POOL__
#include<exception>
#include<iostream>

class myException : public std::exception
{
public:
    myException(const std::string& what_arg)
        : m_what_arg(what_arg)
    {
    }
    virtual const char* what(void) const noexcept override
    {
        auto text = "\r\nError: " + m_what_arg;
        return text.c_str();
    }
private:
    std::string m_what_arg;
};


template<typename T>
class ResourcePool {
private:
    struct Node {
        T data;
        int next;
    };
    int MAX_SIZE;
    Node* nodes;  // 静态链表的节点数组
    int head;  // 头节点的索引
    int freeList;  // 空闲节点链表的头节点索引

public:
    ResourcePool(int max_size) :
        MAX_SIZE(max_size), head(-1), freeList(0) {
        nodes = new Node[MAX_SIZE];
        for (int i = 0; i < MAX_SIZE - 1; i++) {
            nodes[i].next = i + 1;  // 初始化每个节点的next指针，使其指向下一个节点
        }
        nodes[MAX_SIZE - 1].next = -1;  // 最后一个节点的next指针为-1，表示链表结束
    }

    T operator[](int index) {
        return this->nodes[index].data;
    }

    int allocate() {
        if (freeList == -1) {
            throw myException("Resource pool has no Empty");
            return -1;  // 没有可用资源
        }

        int newIndex = freeList;
        freeList = nodes[freeList].next;

        nodes[newIndex].next = head;
        head = newIndex;

        return newIndex;
    }

    void deallocate(int index) {
        if (index < 0 || index >= MAX_SIZE) {
            throw myException("resource pool Invalid index.");
            return;
        }

        if (head == -1) {
            throw myException("resource pool is empty.");
            return;
        }

        if (index == head) {
            head = nodes[head].next;
        }
        else {
            int prevIndex = head;
            while (nodes[prevIndex].next != index) {
                prevIndex = nodes[prevIndex].next;
            }
            nodes[prevIndex].next = nodes[index].next;
        }

        nodes[index].next = freeList;
        freeList = index;
    }

    ~ResourcePool() {
        delete[] this->nodes;
    }
    void set(int index, const T& ele) {
        if (index < 0 || index >= MAX_SIZE) {
            throw myException("resource pool Invalid index.");
            return;
        }
        this->nodes[index].data = ele;
    }
};

#endif