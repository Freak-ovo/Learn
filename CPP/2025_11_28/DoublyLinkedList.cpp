#include <stdexcept>
#include <string>

// 双链表类（带头节点）
class DoublyLinkedList {
private:
    // 节点结构体
    struct Node {
        int data;       // 数据域
        Node* prev;     // 指针域：指向前驱节点
        Node* next;     // 指针域：指向后继节点
        Node(int val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;         // 头节点
    int length;         // 链表长度

public:
    // 构造函数
    DoublyLinkedList() : length(0) {
        head = new Node(0); // 头节点prev和next均为nullptr
    }

    // 析构函数
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    /**
     * @brief 插入元素到指定位置
     */
    void insert(int pos, int val) {
        if (pos < 0 || pos > length) {
            throw std::out_of_range("insert: 位置非法");
        }

        // 找到插入位置的前驱节点
        Node* prev = head;
        for (int i = 0; i < pos; ++i) {
            prev = prev->next;
        }

        Node* newNode = new Node(val);
        Node* nextNode = prev->next; // 前驱的后继节点

        // 建立新节点与前驱的关系
        newNode->prev = prev;
        prev->next = newNode;

        // 建立新节点与后继的关系（若后继存在）
        if (nextNode != nullptr) {
            newNode->next = nextNode;
            nextNode->prev = newNode;
        }

        length++;
    }

    /**
     * @brief 删除指定位置的元素
     */
    void remove(int pos) {
        if (isEmpty()) {
            throw std::runtime_error("remove: 链表为空");
        }
        if (pos < 0 || pos >= length) {
            throw std::out_of_range("remove: 位置非法");
        }

        // 找到待删除节点
        Node* delNode = head->next;
        for (int i = 0; i < pos; ++i) {
            delNode = delNode->next;
        }

        Node* prevNode = delNode->prev; // 前驱节点
        Node* nextNode = delNode->next; // 后继节点

        // 修改前驱和后继的指针
        prevNode->next = nextNode;
        if (nextNode != nullptr) {
            nextNode->prev = prevNode;
        }

        delete delNode;
        length--;
    }

    /**
     * @brief 查找元素位置
     */
    int find(int val) const {
        Node* current = head->next;
        int index = 0;
        while (current != nullptr) {
            if (current->data == val) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }

    /**
     * @brief 反向遍历（验证双链表特性）
     */
    void reverseTraverse() const {
        if (isEmpty()) {
            std::cout << "双链表为空" << std::endl;
            return;
        }

        // 找到最后一个节点
        Node* current = head->next;
        while (current->next != nullptr) {
            current = current->next;
        }

        std::cout << "双链表反向元素: ";
        while (current != head->next) {
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << current->data << std::endl; // 输出第一个元素
    }

    bool isEmpty() const { return length == 0; }
    int getLength() const { return length; }

    /**
     * @brief 正向遍历
     */
    void traverse() const {
        std::cout << "双链表元素: ";
        Node* current = head->next;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};


int main() {

    // 测试双链表
    try {
        std::cout << "\n=== 测试双链表 ===" << std::endl;
        DoublyLinkedList dList;
        dList.insert(0, 1);
        dList.insert(1, 3);
        dList.insert(1, 2);
        dList.traverse();        // 输出：1 2 3
        dList.reverseTraverse(); // 输出：3 2 1

        dList.remove(1);
        dList.traverse(); // 输出：1 3
    } catch (const std::exception& e) {
        std::cerr << "双链表错误: " << e.what() << std::endl;
    }

    return 0;
}