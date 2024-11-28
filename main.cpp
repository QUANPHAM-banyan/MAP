#include <iostream>
#include <string>
#define MAX 1000

using namespace std;

// Định nghĩa cấu trúc "Pair" để lưu trữ cặp <key, value>
struct Pair {
    int key;
    int value;
    Pair(int k, int v) : key(k), value(v) {}
};

class Map {
    // Lớp Map chứa một mảng các đối tượng Pair
protected:
    Pair* units[MAX];   // Danh sách các cặp <key, value>
    int current = 0;
public:
    // Constructor để khởi tạo mảng
    Map() {
        for (int i = 0; i < MAX; i++) {
            units[i] = nullptr;
        }
    }

    // Hàm sắp xếp nổi bọt (bubble sort) để sắp xếp mảng theo khóa
    virtual void bubbleSort() {
        for (int i = 0; i < current - 1; ++i) {
            for (int j = 0; j < current - 1 - i; ++j) {
                // So sánh các khóa của hai phần tử và hoán đổi nếu cần
                if (units[j]->key > units[j + 1]->key) {
                    Pair* temp = units[j];
                    units[j] = units[j + 1];
                    units[j + 1] = temp;
                }
            }
        }
    }

    // Chèn hoặc cập nhật một cặp key-value
    virtual void insert(int k, int v) {
        // Tìm khóa và cập nhật giá trị nếu khóa đã tồn tại
        for (int i = 0; i < current; i++) {
            if (units[i] != nullptr && units[i]->key == k) {
                units[i]->value = v;
                return; // Thoát khỏi hàm sau khi cập nhật giá trị
            }
        }

        // Nếu khóa không tồn tại, thêm một cặp mới
        if (current < MAX) {
            units[current] = new Pair(k, v);
            current++;
            bubbleSort(); // Sắp xếp lại mảng sau khi thêm
        } else {
            cout << "FULL" << endl; // Nếu mảng đầy, in ra "FULL"
        }
    }

    // Hàm truy cập giá trị theo khóa
    int get(int k, int index = 0) {
        if (index >= current) {
            cout << "NOTFOUND" << endl;
            return -1;
        }
        if (units[index] != nullptr && units[index]->key == k) {
            return units[index]->value;
        }
        return get(k, index + 1);
    }

    // Hàm xóa phần tử theo khóa
    void remove(int k) {
        for (int i = 0; i < current; i++) {
            if (units[i] != nullptr && units[i]->key == k) {
                delete units[i]; // Giải phóng bộ nhớ của cặp <key, value>
                // Dịch các phần tử còn lại lên để lấp vào vị trí trống
                for (int j = i; j < current - 1; j++) {
                    units[j] = units[j + 1];
                }
                units[current - 1] = nullptr; // Xóa phần tử thừa cuối mảng
                current--; // Giảm biến current sau khi xóa
                return; // Dừng hàm sau khi xóa phần tử
            }
        }
        cout << "NOTFOUND" << endl;
    }

    // Hàm xóa tất cả các phần tử
    void clear(int index = 0){
        if(current > 0){
            delete units[index];
            units[index] = nullptr;
            current--;
            clear(index + 1);
        }
    }

    // Hàm trả về số lượng phần tử hiện tại
    int size(){
        return current;
    }

    // Kiểm tra xem khóa có tồn tại không
    bool check(int k) {
        for (int i = 0; i < current; i++) {
            if (units[i] != nullptr && units[i]->key == k) {
                return true;
            }
        }
        return false;
    }

    // In "yes" nếu khóa tồn tại, ngược lại in "no"
    void checkYN(int k) {
        cout << (check(k) ? "yes" : "no") << endl;
    }

    // Hàm hủy để giải phóng bộ nhớ
    ~Map() {
        for (int i = 0; i < current; i++) {
            delete units[i];
        }
    }
};

// Định nghĩa cấu trúc PairMM cho Multymap
struct PairMM {
    int key;
    int* values[MAX];
    int value_count;

    PairMM(int k) : key(k), value_count(0) {
        for (int i = 0; i < MAX; i++) {
            values[i] = nullptr;
        }
    }

    // Gắn thêm 1 giá trị mới vào key
    void addValue(int v) {
        if (value_count < MAX) {
            values[value_count] = new int(v);
            value_count++;
        } else {
            cout << "FULL" << endl;
        }
    }
};

// Khai báo lớp Multymap kế thừa lớp Map
class Multymap : public Map {
protected:
    PairMM* units[MAX];
    int current = 0;

public:
    // Hàm khởi tạo
    Multymap() {
        for (int i = 0; i < MAX; i++) {
            units[i] = nullptr;
        }
    }
    void bubbleSort() override{
        for (int i = 0; i < current - 1; ++i) {
            for (int j = 0; j < current - 1 - i; ++j) {
                // So sánh các khóa của hai phần tử và hoán đổi nếu cần
                if (units[j]->key > units[j + 1]->key) {
                    PairMM* temp = units[j];
                    units[j] = units[j + 1];
                    units[j + 1] = temp;
                }
            }
        }
    }

    // Thêm mới key hoặc thêm mới giá trị cho key
    void insert(int k, int v) override {
        for (int i = 0; i < current; i++) {
            if (units[i] != nullptr && units[i]->key == k) {
                units[i]->addValue(v);
                return;
            }
        }
        if (current < MAX) {
            units[current] = new PairMM(k);
            units[current]->addValue(v);
            current++;
        } else {
            cout << "FULL" << endl;
        }
    }

    // Hàm in ra các giá trị value của key tương ứng
    void getValues(int k) {
        for (int i = 0; i < current; i++) {
            if (units[i] != nullptr && units[i]->key == k) {
                cout << "Values for key " << k << ": ";
                for (int j = 0; j < units[i]->value_count; j++) {
                    if (units[i]->values[j] != nullptr) {
                        cout << *(units[i]->values[j]) << " ";
                    }
                }
                cout << endl;
                return;
            }
        }
        cout << "NOTFOUND" << endl;
    }

    // Hàm hủy để giải phóng bộ nhớ
    ~Multymap() {
        for (int i = 0; i < current; i++) {
            if (units[i] != nullptr) {
                for (int j = 0; j < units[i]->value_count; j++) {
                    delete units[i]->values[j];
                }
                delete units[i];
            }
        }
    }
};

int main() {
    Map map;
    map.insert(1, 100);
    map.insert(2, 200);
    cout << map.get(1) << endl; // In ra 100
    map.remove(1);
    map.checkYN(1);             // In ra "no"
    map.checkYN(2);             // In ra "yes"
    return 0;
}
