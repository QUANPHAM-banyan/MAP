#include <iostream>
#include <string>
using namespace std;

// Định nghĩa cấu trúc "Pair" để lưu trữ cặp <key, value>
struct Pair {
    int key;
    int value;
    Pair* next;  // Móc nối đến phần tử tiếp theo trong danh sách

    Pair(int k, int v) : key(k), value(v), next(nullptr) {}
};

class Map {
protected:
    Pair* head;   // Đầu danh sách
    int Size;   // Số phần tử trong danh sách

public:
    // Constructor khởi tạo danh sách rỗng
    Map() : head(nullptr), Size(0) {}

    // Hàm swap tùy chỉnh để hoán đổi giá trị giữa hai đối tượng Pair
    virtual void swap(Pair* a, Pair* b) {
        int tempKey = a->key;
        int tempValue = a->value;
        a->key = b->key;
        a->value = b->value;
        b->key = tempKey;
        b->value = tempValue;
    }

    // Hàm sắp xếp nổi bọt (bubble sort) để sắp xếp danh sách theo khóa
    virtual void bubbleSort() {
        if (head == nullptr || head->next == nullptr) return;

        for (Pair* i = head; i != nullptr; i = i->next) {
            for (Pair* j = i->next; j != nullptr; j = j->next) {
                if (i->key > j->key) {
                    swap(i, j); // Sử dụng hàm swap tùy chỉnh
                }
            }
        }
    }

    // Chèn hoặc cập nhật một cặp key-value
    virtual void insert(int k, int v) {
        // Tìm khóa và cập nhật giá trị nếu khóa đã tồn tại
        Pair* temp = head;
        while (temp != nullptr) {
            if (temp->key == k) {
                temp->value = v;
                return;
            }
            temp = temp->next;
        }

        // Nếu khóa không tồn tại, thêm một cặp mới
        Pair* newPair = new Pair(k, v);
        newPair->next = head;
        head = newPair;
        Size++;
        bubbleSort(); // Sắp xếp lại danh sách sau khi thêm
    }

    // Hàm truy cập giá trị theo khóa
    int get(int k) {
        Pair* temp = head;
        while (temp != nullptr) {
            if (temp->key == k) {
                return temp->value;
            }
            temp = temp->next;
        }
        cout << "NOTFOUND" << endl;
        return -1;
    }

    // Hàm xóa phần tử theo khóa
    void remove(int k) {
        Pair* temp = head;
        Pair* prev = nullptr;

        // Nếu khóa đầu tiên cần xóa
        if (temp != nullptr && temp->key == k) {
            head = temp->next;  // Di chuyển head sang phần tử tiếp theo
            delete temp;        // Xóa phần tử đầu
            Size--;
            return;
        }

        // Tìm phần tử cần xóa
        while (temp != nullptr && temp->key != k) {
            prev = temp;
            temp = temp->next;
        }

        // Nếu không tìm thấy khóa
        if (temp == nullptr) {
            cout << "NOTFOUND" << endl;
            return;
        }

        // Xóa phần tử khỏi danh sách
        prev->next = temp->next;
        delete temp;
        Size--;
    }

    // Hàm xóa tất cả các phần tử
    void clear() {
        while (head != nullptr) {
            Pair* temp = head;
            head = head->next;
            delete temp;
        }
        Size = 0;
    }

    // Hàm trả về số lượng phần tử hiện tại
    int size() {
        return Size;
    }

    // Kiểm tra xem khóa có tồn tại không
    bool check(int k) {
        Pair* temp = head;
        while (temp != nullptr) {
            if (temp->key == k) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // In "yes" nếu khóa tồn tại, ngược lại in "no"
    void checkYN(int k) {
        cout << (check(k) ? "yes" : "no") << endl;
    }

    // Hàm hủy để giải phóng bộ nhớ
    ~Map() {
        clear();
    }
};

// Định nghĩa cấu trúc PairMM cho Multymap
struct PairMM {
    int key;
    Pair* values; // Danh sách liên kết các giá trị
    PairMM* next; // Móc nối đến phần tử tiếp theo trong danh sách

    PairMM(int k) : key(k), values(nullptr), next(nullptr) {}

    // Gắn thêm 1 giá trị mới vào key
    void addValue(int v) {
        Pair* newValue = new Pair(v, 0); // Mỗi giá trị được lưu trong Pair, giá trị '0' không sử dụng
        newValue->next = values;
        values = newValue;
    }
};

class Multymap : public Map {
protected:
    PairMM* headMM; // Đầu danh sách các PairMM

public:
    // Hàm khởi tạo
    Multymap() : headMM(nullptr) {}

    // Hàm swap tùy chỉnh để hoán đổi giá trị giữa hai đối tượng PairMM
    void swap(PairMM* a, PairMM* b) {
        int tempKey = a->key;
        Pair* tempValues = a->values;
        a->key = b->key;
        a->values = b->values;
        b->key = tempKey;
        b->values = tempValues;
    }

    // Hàm sắp xếp nổi bọt cho Multymap
    void bubbleSort() override {
        if (headMM == nullptr || headMM->next == nullptr) return;

        for (PairMM* i = headMM; i != nullptr; i = i->next) {
            for (PairMM* j = i->next; j != nullptr; j = j->next) {
                if (i->key > j->key) {
                    swap(i, j); // Sử dụng hàm swap tùy chỉnh
                }
            }
        }
    }

    // Thêm mới key hoặc thêm mới giá trị cho key
    void insert(int k, int v) override {
        PairMM* temp = headMM;
        while (temp != nullptr) {
            if (temp->key == k) {
                temp->addValue(v);
                return;
            }
            temp = temp->next;
        }

        PairMM* newPairMM = new PairMM(k);
        newPairMM->addValue(v);
        newPairMM->next = headMM;
        headMM = newPairMM;
        Size++;
    }

    // Hàm in ra các giá trị value của key tương ứng
    void getValues(int k) {
        PairMM* temp = headMM;
        while (temp != nullptr) {
            if (temp->key == k) {
                cout << "Values for key " << k << ": ";
                Pair* value = temp->values;
                while (value != nullptr) {
                    cout << value->key << " ";  // In ra các giá trị
                    value = value->next;
                }
                cout << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "NOTFOUND" << endl;
    }

    // Hàm hủy để giải phóng bộ nhớ
    ~Multymap() {
        while (headMM != nullptr) {
            PairMM* temp = headMM;
            headMM = headMM->next;
            while (temp->values != nullptr) {
                Pair* valTemp = temp->values;
                temp->values = temp->values->next;
                delete valTemp;
            }
            delete temp;
        }
    }
};
