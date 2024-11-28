int main() {
    Map map;

    // Thêm các cặp <key, value>
    map.insert(1, 100);
    map.insert(3, 300);
    map.insert(2, 200);
    map.insert(5, 500);
    map.insert(4, 400);

    // In ra các giá trị sau khi thêm
    cout << "Size of map: " << map.size() << endl;  // Kỳ vọng 5
    cout << "Value for key 3: " << map.get(3) << endl;  // Kỳ vọng 300
    cout << "Value for key 2: " << map.get(2) << endl;  // Kỳ vọng 200
    cout << "Value for key 1: " << map.get(1) << endl;  // Kỳ vọng 100
    cout << "Value for key 4: " << map.get(4) << endl;  // Kỳ vọng 400

    // Kiểm tra sự tồn tại của một khóa
    map.checkYN(3);  // Kỳ vọng "yes"
    map.checkYN(10); // Kỳ vọng "no"

    // Xóa phần tử theo khóa
    map.remove(3);   // Xóa khóa 3
    map.remove(10);  // Không có khóa 10 để xóa

    // Kiểm tra lại các giá trị sau khi xóa
    cout << "Value for key 3 after removal: " << map.get(3) << endl; // Kỳ vọng "NOTFOUND"

    // Xóa tất cả phần tử
    map.clear();
    cout << "Size of map after clearing: " << map.size() << endl;  // Kỳ vọng 0

    Multymap multymap;

    // Thêm các cặp <key, value>
    multymap.insert(1, 100);
    multymap.insert(3, 300);
    multymap.insert(2, 200);
    multymap.insert(3, 301);
    multymap.insert(2, 201);

    // In ra các giá trị sau khi thêm
    cout << "Size of multymap: " << multymap.size() << endl;  // Kỳ vọng 3
    multymap.getValues(1);  // Kỳ vọng: 100
    multymap.getValues(3);  // Kỳ vọng: 300 301
    multymap.getValues(2);  // Kỳ vọng: 200 201

    // Kiểm tra sự tồn tại của một khóa
    multymap.checkYN(3);  // Kỳ vọng "yes"
    multymap.checkYN(4);  // Kỳ vọng "no"

    // Xóa phần tử theo khóa
    multymap.remove(3);   // Xóa khóa 3
    multymap.remove(4);   // Không có khóa 4 để xóa

    // Kiểm tra lại các giá trị sau khi xóa
    cout << "Values for key 3 after removal: ";
    multymap.getValues(3);  // Kỳ vọng "NOTFOUND"

    // Thêm giá trị mới cho khóa đã tồn tại
    multymap.insert(2, 202);
    multymap.getValues(2);  // Kỳ vọng: 200 201 202
    // Xóa tất cả phần tử
    multymap.clear();
    cout << "Size of multymap after clearing: " << multymap.size() << endl;  // Kỳ vọng 0

    return 0;
    }
