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

class Map { // class Map chứa mảng các Pair
protected:
    Pair* units[MAX];   // Danh sách các phần tử <key, value>
    int current = 0;
public:
    // Hàm khởi tạo
    Map() {
        for (int i = 0; i < MAX; i++) {
            units[i] = nullptr;
        }
    }

    // Hàm thêm hoặc cập nhật giá trị
    virtual void insert(int k, int v) {
        // Tìm khóa và cập nhật nếu đã tồn tại
        for (int i = 0; i < current; i++) {
            if (units[i] != nullptr && units[i]->key == k) {
                units[i]->value = v;
                return; // Dừng hàm ngay sau khi cập nhật
            }
        }

        // Nếu khóa chưa tồn tại, thêm mới
        if (current < MAX) {
            units[current] = new Pair(k, v);
            current++;
        } else {
            cout << "FULL" << endl;
        }
    }

    // Hàm truy cập giá trị theo khóa
    int get(int k, int index = 0) {
        if (index >= current) { // Sửa MAX thành current để tránh duyệt không cần thiết
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
//Khai báo lớp Multymap kế thừa lớp
class Multymap : public Map {
protected:
    PairMM* units[MAX];
    int current = 0;

public:
    //Hàm khởi tạo
    Multymap() {
        for (int i = 0; i < MAX; i++) {
            units[i] = nullptr;
        }
    }
//Thêm mới key hoặc thêm mới giá trị cho key
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
//Hàm in ra các gìá trị value của key tương ứng
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
