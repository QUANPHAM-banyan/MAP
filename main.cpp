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
    void insert(int k, int v) {
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
