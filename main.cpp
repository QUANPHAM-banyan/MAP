#include <iostream>
using namespace std;

int main() {
    Map map;

    // Thêm các cặp <key, value>
    map.insert(1, 100);
    map.insert(3, 300);
    map.insert(2, 200);
    map.insert(5, 500);
    map.insert(4, 400);

    // In ra kích thước sau khi thêm
    cout << "Size of map: " << map.size() << endl;  // Kỳ vọng 5
    cout << "Value for key 3: " << map.get(3) << endl;  // Kỳ vọng 300
    cout << "Value for key 2: " << map.get(2) << endl;  // Kỳ vọng 200
    cout << "Value for key 5: " << map.get(5) << endl;  // Kỳ vọng 500

    // Kiểm tra sự tồn tại của một khóa
    map.check(3);  // Kỳ vọng "yes"
    map.check(10); // Kỳ vọng "no"

    // Xóa phần tử theo khóa
    map.remove(3);   // Xóa khóa 3
    map.remove(10);  // Không có khóa 10 để xóa

    // Kiểm tra lại giá trị sau khi xóa
    cout << "Value for key 3 after removal: " << map.get(3) << endl; // Kỳ vọng "NOTFOUND"

    // Xóa tất cả phần tử
    map.clear();
    cout << "Size of map after clearing: " << map.size() << endl;  // Kỳ vọng 0

    Multimap multimap;

    // Thêm các cặp <key, value>
    multimap.insert(1, 100);
    multimap.insert(3, 300);
    multimap.insert(2, 200);
    multimap.insert(3, 301);
    multimap.insert(2, 201);

    // In ra kích thước sau khi thêm
    cout << "Size of multimap: " << multimap.size() << endl;  // Kỳ vọng 5
    multimap.get(1);  // Kỳ vọng: 100
    multimap.get(3);  // Kỳ vọng: 300 301
    multimap.get(2);  // Kỳ vọng: 200 201

    // Kiểm tra sự tồn tại của một khóa
    multimap.check(3);  // Kỳ vọng "yes"
    multimap.check(4);  // Kỳ vọng "no"

    // Xóa phần tử theo khóa
    multimap.remove(3);   // Xóa tất cả phần tử có khóa 3
    multimap.remove(4);   // Không có khóa 4 để xóa

    // Kiểm tra lại giá trị sau khi xóa
    cout << "Values for key 3 after removal: ";
    multimap.get(3);  // Kỳ vọng "NOTFOUND"

    // Thêm giá trị mới cho khóa đã tồn tại
    multimap.insert(2, 202);
    multimap.get(2);  // Kỳ vọng: 200 201 202

    // Xóa tất cả phần tử
    multimap.clear();
    cout << "Size of multimap after clearing: " << multimap.size() << endl;  // Kỳ vọng 0

    return 0;
}
