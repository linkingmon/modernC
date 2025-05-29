# Chapter 1: C++ 基礎快速回顧

## 一、基本概念

C++ 是一個強型、系統符合型的程式語言。為了練習 Modern C++（從 C++11 開始到 C++20）之新特性，首先需重新回顧 C++ 基礎的使用。

## 二、基礎組成元素

### 1. 變數與常數

```cpp
int x = 5;
const int y = 10; // y 不能被修改
```

### 2. 指標與參考

```cpp
int a = 10;
int* ptr = &a; // ptr 是指向 a 的指標
int& ref = a; // ref 是 a 的參考，等同於別名
```

### 3. 控制流程

```cpp
if (x > 0) {
    // ...
}

for (int i = 0; i < 10; ++i) {
    // ...
}

while (x < 100) {
    // ...
}
```

### 4. 函數

```cpp
int add(int a, int b) {
    return a + b;
}
```

## 三、RAII 與資源管理

RAII（Resource Acquisition Is Initialization）意即「取得資源即初始化」，資源於物件生命週期開始取得、結束時自動釋放。

```cpp
#include <iostream>
#include <fstream>

void readFile(const std::string& filename) {
    std::ifstream file(filename); // 開啟時即取得資源
    if (file) {
        std::string line;
        while (getline(file, line)) {
            std::cout << line << "\n";
        }
    } // 出範圍時自動關閉 file
}
```

## 四、nullptr 與 NULL

```cpp
int* p1 = NULL;      // C 風格，不建議使用
int* p2 = nullptr;   // Modern C++ 推薦使用
```

## 五、練習題（Practice）

### 題目一

寫一個函數 `int sum(const std::vector<int>& nums)`，返回 nums 總和，且不要修改 nums 內容。

### 題目二

寫一個函數 `void updateValue(int& ref)`，用參考來修改外部變數值。

### 題目三

請用指標寫出一個函數，將兩個 `int` 數值互相交換（swap）。

---

# Chapter 2: 智慧指標與資源管理

## 一、智慧指標概述

C++11 引入智慧指標（smart pointers）來自動管理記憶體與資源釋放，遵循 RAII 原則。
主要類型如下：

* `std::unique_ptr<T>`：唯一擁有權，無法複製
* `std::shared_ptr<T>`：共享擁有權，引用計數
* `std::weak_ptr<T>`：輔助 shared\_ptr，避免循環引用

## 二、unique\_ptr 使用範例

```cpp
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "Constructed\n"; }
    ~MyClass() { std::cout << "Destructed\n"; }
    void sayHello() { std::cout << "Hello\n"; }
};

int main() {
    std::unique_ptr<MyClass> ptr = std::make_unique<MyClass>();
    ptr->sayHello();
    // 不需要 delete，離開範圍後自動釋放
}
```

## 三、shared\_ptr 與 weak\_ptr

```cpp
#include <iostream>
#include <memory>

class Node {
public:
    std::shared_ptr<Node> next;
    ~Node() { std::cout << "Node destroyed\n"; }
};

void sharedCycle() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->next = b;
    b->next = a; // 產生循環引用
    // 解決方式：使用 weak_ptr
}
```

## 四、shared\_ptr 與 weak\_ptr 的差異與內部原理

### shared\_ptr 的運作原理

* `shared_ptr<T>` 是一種擁有 "引用計數 (reference count)" 的智慧指標
* 每有一個 `shared_ptr` 指向物件，該物件的引用計數就加一
* 當最後一個 `shared_ptr` 離開作用域時，引用計數歸零，自動呼叫 `delete`，釋放記憶體

### weak\_ptr 的特性與用途

* `weak_ptr<T>` 是對某個 `shared_ptr<T>` 所管理物件的「弱引用」
* 它**不會增加引用計數**
* 必須透過 `lock()` 檢查是否還有效（物件未被釋放），並轉換為 `shared_ptr` 使用

### 為什麼 weak\_ptr 可以避免循環引用？

* 若 A 與 B 互相擁有 `shared_ptr`，彼此引用計數都不會歸零，物件永遠無法被 `delete`
* 改用 `weak_ptr` 只做「觀察」，不影響引用計數
* 離開作用域後，只要沒有其他 `shared_ptr` 持有該物件，仍會自動釋放記憶體

### 示意：

```cpp
struct A {
    std::shared_ptr<A> other; // ❌ 循環引用：無法釋放
};

struct B {
    std::weak_ptr<B> other;   // ✅ 不增加引用計數，可釋放
};
```

## 五、練習題（Practice）

### 題目一

請建立一個類別 Resource，在建構時印出 "Acquired"，解構時印出 "Released"。
請使用 `unique_ptr` 來確保該資源自動釋放。

### 題目二

模擬一個聊天室 User 類別，包含 shared\_ptr<User> friend\_link。試著建立 2 個使用者互為朋友，並觀察解構是否發生。再改為使用 `weak_ptr` 減少記憶體洩漏風險。

---

# Chapter 3: Lambda 表達式

## 一、Lambda 是什麼？

Lambda 是 C++11 引入的匿名函數（function object），可用來快速定義一個可呼叫的函數區塊，常搭配 STL 使用。

基本語法如下：

```cpp
[capture](parameter) -> return_type {
    // 函數內容
}
```

範例：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    std::for_each(nums.begin(), nums.end(), [](int x) {
        std::cout << x * x << " ";
    });
    std::cout << "
";
}
```

## 二、捕獲列表（Capture List）

| 語法     | 說明          |
| ------ | ----------- |
| `[=]`  | 以值捕獲所有外部變數  |
| `[&]`  | 以參考捕獲所有外部變數 |
| `[x]`  | 以值捕獲變數 x    |
| `[&x]` | 以參考捕獲變數 x   |

範例：

```cpp
int a = 10, b = 20;

auto f1 = [=]() { return a + b; }; // 傳值
auto f2 = [&]() { a += b; };       // 傳參考
```

## 三、Lambda 作為回呼函數（Callback）

可傳遞 lambda 到 STL 容器操作中，如 `std::sort`, `std::find_if`：

```cpp
std::vector<int> data = {5, 1, 8, 3};
std::sort(data.begin(), data.end(), [](int a, int b) {
    return a > b; // 降冪排序
});
```

## 四、Lambda 的類型推導與 auto

你可以使用 `auto` 定義 lambda：

```cpp
auto add = [](int a, int b) { return a + b; };
std::cout << add(3, 4) << std::endl;
```

## 五、練習題（Practice）

### 題目一

請寫一個 lambda，接受 `std::vector<int>` 並印出所有偶數元素。

### 題目二

請使用 `std::sort` 與 lambda，將一組字串按照長度排序。

### 題目三

請用 lambda 實作一個 `std::transform`，將整數陣列每個元素乘 2。

### 題目四

請定義一個 lambda，捕獲外部變數 `sum`（以參考），對 `std::vector<int>` 執行 `for_each` 並累加總和至 `sum` 中。

### 題目五

定義一個 lambda，捕獲外部變數 `count`（以值捕獲），用於統計 `vector<string>` 中字串長度超過 5 的個數。觀察 lambda 執行完畢後 `count` 是否改變，並解釋原因。

### 題目六

請撰寫 lambda 接收兩個整數並比較其與外部參考變數 `ascending`，若為 `true` 則升冪，否則降冪排序，並應用於 `std::sort`。

# Chapter 4: auto 與型別推導

## 一、auto 關鍵字簡介

`auto` 可以讓編譯器自動根據初始化的表達式推導變數的型別。這能使程式更簡潔且減少冗長型別聲明。

### 範例：

```cpp
auto x = 3.14;         // x 是 double
auto y = 42;           // y 是 int
auto str = "hello";   // str 是 const char*
```

---

## 二、搭配 STL 使用 auto

使用 STL 容器時，元素型別通常很冗長，`auto` 可簡化迴圈與變數宣告：

```cpp
std::vector<std::pair<int, std::string>> data;

for (auto it = data.begin(); it != data.end(); ++it) {
    std::cout << it->second << std::endl;
}
```

範例：使用範圍 for 迴圈結合 auto

```cpp
for (const auto& [id, name] : data) {
    std::cout << name << std::endl;
}
```

---

## 三、decltype：從表達式中推導型別

`decltype(expr)` 會回傳 `expr` 的型別。

### 範例：

```cpp
int a = 10;
decltype(a) b = 20; // b 是 int

auto add = [](int x, int y) { return x + y; };
decltype(add) f2 = add; // f2 與 add 同型別（為 lambda 類型）
```

---

## 四、auto 與函式回傳型別

在 C++14 以後，可以使用 `auto` 搭配 `decltype` 定義函式回傳型別：

```cpp
template<typename T1, typename T2>
auto multiply(T1 a, T2 b) -> decltype(a * b) {
    return a * b;
}
```

C++14 起可以這樣寫（編譯器自行推導）：

```cpp
auto multiply(auto a, auto b) {
    return a * b;
}
```

---

## 五、練習題（Practice）

### 題目一

請寫出一個函式 `auto square(T x)`，可接受任意型別（int, double），回傳其平方值。

### 題目二

給定一個 map，使用範圍 for 搭配 auto 與解構來印出所有 key-value。

### 題目三

使用 `decltype` 搭配 `auto` 宣告一個變數，其型別與某個 vector 中元素相同，並對其初始化。

# Chapter 5: Templates 與 Type Traits

## 一、函式模板（Function Templates）

函式模板允許你撰寫可接受任意型別的泛用函式。

### 基本語法：

```cpp
template<typename T>
T max(T a, T b) {
    return a > b ? a : b;
}
```

也可以使用多個型別：

```cpp
template<typename T1, typename T2>
auto multiply(T1 a, T2 b) {
    return a * b;
}
```

---

## 二、類別模板（Class Templates）

類別模板可以創建泛用類別，例如 STL 的 `std::vector<T>`。

### 範例：

```cpp
template<typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T get() const { return value; }
};
```

---

## 三、Type Traits 與 SFINAE

### 1. Type Traits

Type Traits 提供型別的編譯期資訊與條件判斷，例如：

* `std::is_integral<T>::value`
* `std::is_same<T, U>::value`

### 2. enable\_if 與 SFINAE

`std::enable_if` 可限制模板函式僅接受某些型別：

```cpp
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
add(T a, T b) {
    return a + b;
}
```

這段程式只有在 T 是整數型別時才會編譯成功（SFINAE: Substitution Failure Is Not An Error）。

---

## 四、constexpr 與編譯期運算

`constexpr` 函式可於編譯期執行。

```cpp
constexpr int square(int x) {
    return x * x;
}

int arr[square(3)]; // OK：陣列大小為編譯期常數
```

---

## 五、練習題（Practice）

### 題目一

撰寫一個模板函式 `max_of_three(a, b, c)`，可接受任意型別並回傳最大值。

### 題目二

撰寫一個類別模板 `Pair<T1, T2>`，提供成員函式 `first()` 與 `second()` 回傳對應的值。

### 題目三

使用 `std::enable_if` 撰寫 `is_even(T val)`，僅允許整數型別。

# Chapter 6: STL 與範圍 for、演算法

## 一、STL 容器概觀

STL（Standard Template Library）是 C++ 提供的標準容器與演算法集合。常見容器如下：

| 容器              | 說明         |
| --------------- | ---------- |
| `vector`        | 動態陣列（最常用）  |
| `list`          | 雙向鏈結串列     |
| `deque`         | 雙端佇列       |
| `set`           | 唯一、排序集合    |
| `map`           | 鍵值對映，依鍵排序  |
| `unordered_map` | 雜湊表實作，鍵值無序 |

---

## 二、範圍 for 迴圈

使用 `range-based for`（C++11 起）可以更簡潔地走訪容器：

```cpp
std::vector<int> nums = {1, 2, 3};
for (int n : nums) {
    std::cout << n << std::endl;
}

// 搭配引用避免複製
for (auto& s : vec_of_strings) {
    s += " suffix";
}
```

---

## 三、常見 STL 演算法（<algorithm>）

### 排序 sort

```cpp
std::sort(vec.begin(), vec.end());
```

可搭配 lambda 自訂排序：

```cpp
std::sort(vec.begin(), vec.end(), [](int a, int b) {
    return a > b; // 降冪排序
});
```

### 搜尋 find, find\_if

```cpp
auto it = std::find(vec.begin(), vec.end(), 42);

auto it2 = std::find_if(vec.begin(), vec.end(), [](int x) {
    return x % 2 == 0;
});
```

### 轉換 transform

```cpp
std::transform(vec.begin(), vec.end(), vec.begin(), [](int x) {
    return x * 2;
});
```

### 統計 count, count\_if

```cpp
int count_even = std::count_if(vec.begin(), vec.end(), [](int x) {
    return x % 2 == 0;
});
```

---

## 四、練習題（Practice）

### 題目一

建立一個 `std::vector<string>`，請用範圍 for 印出所有字串。

### 題目二

使用 `std::sort` 排序一組浮點數，並用 lambda 實現降冪排序。

### 題目三

請用 `std::count_if` 計算 vector 中所有長度超過 5 的字串個數。

### 題目四

請用 `std::transform` 將整數 vector 中每個元素平方，儲存在另一個 vector 中。

# Chapter 7: Concurrency 與 Thread 支援

Modern C++ 自 C++11 起提供了原生的多執行緒支援工具，讓我們能以簡潔、安全的方式撰寫並行程式。

---

## 一、std::thread 基本用法

建立一條執行緒並執行函數：

```cpp
#include <iostream>
#include <thread>

void sayHello() {
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    std::thread t(sayHello); // 建立 thread 執行 sayHello
    t.join(); // 等待 thread 結束
}
```

也可以使用 lambda：

```cpp
std::thread t([]() {
    std::cout << "Running in lambda thread." << std::endl;
});
t.join();
```

---

## 二、std::async 與 future

`std::async` 會啟動非同步任務，回傳 `std::future` 可用來取得結果：

```cpp
#include <future>

int compute() {
    return 42;
}

int main() {
    std::future<int> result = std::async(compute);
    std::cout << "Result: " << result.get() << std::endl; // 阻塞直到完成
}
```

---

## 三、資料同步：mutex 與 lock\_guard

多執行緒若同時存取共享資料會導致資料競爭（race condition），需使用 `mutex` 保護：

```cpp
#include <mutex>

std::mutex mtx;

void safePrint(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Thread " << id << " printing\n";
}
```

---

## 四、thread 的 join 與 detach

* `join()`：主執行緒等待子執行緒完成
* `detach()`：讓子執行緒獨立運行，主執行緒不再管理它（小心 zombie threads）

```cpp
std::thread t([]{ work(); });
t.detach(); // 不再等待它結束
```

---

## 五、練習題（Practice）

### 題目一

建立兩個執行緒，分別印出 "Thread A" 與 "Thread B"，使用 `join()` 確保主執行緒等待它們結束。

### 題目二

使用 `std::async` 建立一個加總函數，讓 main 程式印出非同步結果。

### 題目三

建立多個執行緒共用一個 counter，使用 `std::mutex` 保護遞增操作，避免 race condition。

### 題目四

寫一個函數，模擬耗時運算（例如 `sleep_for(1s)`），透過 `std::future::wait_for` 監控是否在 100ms 內完成，若逾時則顯示 timeout。

### 題目五

建立 10 條執行緒，各自印出其編號（0\~9），確保輸出不交錯。

### 題目六

使用 `std::async` 並結合 `std::accumulate`，對大型 vector 進行平行加總。使用 8 thread 並且分析計算的花費是否縮短。

# Chapter 8: C++17 / C++20 新特性

Modern C++ 在 C++17 與 C++20 中加入許多實用的新語言功能與標準函式庫，讓程式更簡潔、類型更安全、效能更佳。

---

## 一、std::optional：可有可無的值（C++17）

`std::optional<T>` 表示一個可能有值也可能沒有值的變數，比回傳指標或特別值（如 -1）更安全。

```cpp
#include <optional>

std::optional<int> parseInt(const std::string& s) {
    if (s.empty()) return std::nullopt;
    return std::stoi(s);
}

int main() {
    auto result = parseInt("123");
    if (result.has_value()) {
        std::cout << "Parsed: " << result.value() << std::endl;
    }
}
```

---

## 二、std::variant：類型安全的聯集型別（C++17）

類似 union，但可安全追蹤目前使用哪個型別。

```cpp
#include <variant>
#include <iostream>

std::variant<int, std::string> getData(bool flag) {
    if (flag) return 42;
    else return std::string("hello");
}

int main() {
    auto v = getData(true);
    if (std::holds_alternative<int>(v)) {
        std::cout << "int: " << std::get<int>(v) << std::endl;
    }
}
```

---

## 三、結構化綁定（Structured Binding）

將 tuple、pair 或 struct 拆解為多個變數。

```cpp
std::pair<int, std::string> p = {1, "apple"};
auto [id, name] = p;
```

---

## 四、if constexpr（C++17）

在編譯期選擇不同邏輯，適用於 template 函式：

```cpp
template<typename T>
void printType(T val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "int: " << val << std::endl;
    } else {
        std::cout << "not int\n";
    }
}
```

---

## 五、C++20 Ranges Library

使用 range 與 view 對容器做懶惰運算（lazy evaluation）：

```cpp
#include <ranges>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    auto squares = nums | std::views::transform([](int x) { return x * x; });

    for (int n : squares) {
        std::cout << n << " ";
    }
}
```

---

## 六、練習題（Practice）

### 題目一

寫一個函式 parseId，輸入字串，回傳 `std::optional<int>`，若為有效整數則回傳值，否則回傳 nullopt。

### 題目二

設計一個 `std::variant<int, std::string>` 的變數，寫出程式檢查目前是 int 還是 string 並輸出對應值。

### 題目三

使用 structured binding 拆解一個 `std::tuple<int, double, std::string>` 並印出內容。

### 題目四

寫一個 template 函式 `describe()`，用 `if constexpr` 根據型別印出不同訊息。

### 題目五

用 C++20 Ranges 對一個整數 vector 濾出偶數並平方後印出。

# Chapter 9: 回顧：大型專案的應用

本章將整合前 1～8 章所學內容，設計兩個大型應用專案，讓你實際體會 Modern C++ 的優勢：可讀性、效能、與語法的簡潔度。每個專案都會強調傳統 C++ 難以做到的部分，並具備清晰的可視化輸出。

---

## 🧩 專案一：並行統計系統 + 現代化輸出報表

### 🎯 目標：

設計一個能對大量整數資料進行分析的系統，並透過現代 C++ 語法實作下列功能：

### ✅ 功能需求：

* 使用 `std::vector<int>` 儲存數據（可模擬讀入檔案）
* 利用 `std::async` 將資料平分給多條執行緒進行統計（如平均、最大、最小、偶數比例）
* 統計過程使用 `std::accumulate`、`std::ranges` 做變換與過濾
* 支援 `std::variant` 表示不同型別結果欄位（如整數、浮點）
* 將結果輸出為格式化表格
* 使用不同 thread 觀察變化 

## 🎮 專案二：互動式命令列 RPG 遊戲引擎原型

### 🎯 目標：

實作一個簡單的指令型角色扮演遊戲原型，支援動態角色狀態、技能邏輯、指令解析等，展現 Modern C++ 的資料建模能力與代碼整潔。

### ✅ 功能需求：

* 使用 `struct` 搭配 `std::tuple` 或 `std::variant` 建立角色資料模型
* 使用 `std::map<string, function<void()>>` 實作指令系統（Lambda + callback）
* 利用 `smart pointer` 管理動態角色與道具物件生命週期
* 使用 `std::optional` 處理「未選技能」、「沒有道具」等情況
* 透過 `std::thread` 或 `std::async` 實作戰鬥中的時間等待與事件觸發
* 使用 `ranges` 處理角色道具過濾與排序（如血量最低者、自動選擇武器）
* 具備簡易 CLI 視覺輸出（如角色狀態條、技能清單）

# Chapter 10: C++20 協程（Coroutines）與 Generator

本章將介紹 C++20 協程的基本概念與應用，並使用 `co_yield` 實作 generator。

---

## 一、協程概念

* 協程（coroutine）允許函式中間暫停與恢復
* 常用於 async IO、資料流處理、懶惰生成器（lazy generator）

協程需要三個關鍵元素：

* `promise_type`：協程狀態的持有者與控制器
* `co_await` / `co_yield`：控制暫停與輸出
* `std::coroutine_handle`：協程執行控制器

---

## 二、使用 co\_yield 建立 Generator

### 簡化版 Generator 範例：

```cpp
#include <coroutine>
#include <iostream>
#include <optional>

template<typename T>
struct Generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        T current_value;
        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        Generator get_return_object() {
            return Generator{handle_type::from_promise(*this)};
        }
        void return_void() {}
        void unhandled_exception() { std::exit(1); }
    };

    handle_type h;
    Generator(handle_type h) : h(h) {}
    ~Generator() { if (h) h.destroy(); }

    bool next() { return h.resume(), !h.done(); }
    T value() const { return h.promise().current_value; }
};

Generator<int> count_up_to(int n) {
    for (int i = 1; i <= n; ++i)
        co_yield i;
}

int main() {
    auto gen = count_up_to(5);
    while (gen.next()) {
        std::cout << gen.value() << " ";
    }
}
```

### 說明：

* `handle_type = std::coroutine_handle<promise_type>` 是一個控制協程的物件，能讓我們 resume() 或 destroy()。
* `handle_type::from_promise(*this)` 表示從 promise 中取得對應的 coroutine handle。
* `promise_type` 負責暫存值與控制協程流程。

> 💡 若把 `co_yield` 拿掉，整個協程不再有暫停點，會直接執行到底，無法逐步控制或查詢每個值。這就是 `co_yield` 的價值 —— 允許中途暫停、一次只處理一個值。

---

## 三、為何使用 co\_yield？哪些事情非用不可？

### ✅ 使用 co\_yield 的最佳情境：

| 情境                       | 優勢                      | 傳統寫法困難點              |
| ------------------------ | ----------------------- | -------------------- |
| 懶惰生成大量資料（如斐波那契數列）        | `co_yield` 可暫停函式並保存內部狀態 | 傳統需自行維護狀態變數與迴圈指標     |
| UI event 或 stream 資料逐筆處理 | 可用 `next()` 逐步取資料       | 傳統 callback 或狀態機邏輯複雜 |
| 實作 iterator-like 類別      | 自動管理生命周期與狀態跳躍           | 傳統需寫繁瑣的類別與 operator  |

### 🧠 範例比較：斐波那契產生器

#### co\_yield 寫法：

```cpp
Generator<int> fib(int max) {
    int a = 0, b = 1;
    while (a <= max) {
        co_yield a;
        std::tie(a, b) = std::make_pair(b, a + b);
    }
}
```

#### 傳統寫法：

```cpp
struct Fib {
    int a = 0, b = 1;
    int next() {
        int temp = a;
        std::tie(a, b) = std::make_pair(b, a + b);
        return temp;
    }
};
```

#### 呼叫端差異：

```cpp
// 使用 Generator 的方式
auto g = fib(20);
while (g.next()) {
    std::cout << g.value() << " ";
}

// 使用 struct 的方式
Fib f;
for (int i = 0; i < 10; ++i) {
    std::cout << f.next() << " ";
}
```

### 📘 什麼是「懶惰生成」（lazy generation）？

* 指的是「等你需要某個資料時才產生它，而不是一次產生所有資料」。
* 可以節省記憶體與運算量，特別適合用於處理無限序列、龐大檔案、streaming data。

---

## 四、效能比較說明

| 項目      | 傳統手寫 `struct`   | `co_yield` 協程           |
| ------- | --------------- | ----------------------- |
| ✨ 語法簡潔  | ❌（需寫 next()、狀態） | ✅（直接寫邏輯 + 暫停）           |
| 💡 可維護性 | ❌（難維護、易錯）       | ✅（類似寫普通函式）              |
| 🚀 執行效能 | ✅ 較快（無額外控制機制）   | ❌ 稍慢（需維護協程狀態）           |
| 🧠 狀態維持 | 手動變數維護          | 自動透過 promise/context 保存 |

對於高頻次呼叫（例如上百萬次），傳統 struct 效能可能更高；但若偏好程式碼簡潔、清楚、可抽換協程處理，`co_yield` 更具優勢。

---

## 五、應用場景

* 非同步資料來源的懶惰遍歷
* stream 處理（如 network stream）
* UI event 處理

---

## 六、練習題（Practice）

### 題目一

撰寫一個協程產生器 `even_numbers(n)`，每次 `next()` 回傳偶數直到 n。

### 題目二

修改 Generator 範例，使其能支援 `co_yield string` 並輸出一連串單字。

### 題目三

撰寫一段程式，使用傳統 struct 實作斐波那契產生器，並與 `Generator` 版本進行比較。請在 caller 端觀察兩者的使用差異與簡潔度差異。

# Chapter 11: C++ 容器底層原理與效能分析

本章將深入探討 C++ 標準容器的內部實作原理，並對比不同容器在各種使用情境下的效能表現，協助你作出更合適的選擇。

---

## 一、vector 的底層結構與擴容

* `std::vector` 是連續記憶體配置（如 C 陣列）
* 當容量不足時，會自動分配新空間並搬移資料
* 時間複雜度：

  * 隨機存取：O(1)
  * push\_back：平均 O(1)，最壞 O(n)
  * 插入/刪除中間：O(n)

### 範例：觀察容量成長

```cpp
std::vector<int> v;
for (int i = 0; i < 100; ++i) {
    v.push_back(i);
    std::cout << "size: " << v.size() << ", capacity: " << v.capacity() << std::endl;
}
```

---

## 二、list 與 forward\_list

* `std::list` 是雙向鏈結串列，適合頻繁插入/刪除
* `std::forward_list` 是單向鏈結串列，記憶體更省
* 插入/刪除：O(1)
* 存取：O(n)

### 使用時機：

* 不需要隨機存取，只需要大量插入/刪除
* 例如：任務排程器、編輯器行列表

---

## 三、set、map vs unordered\_set、unordered\_map

| 類型                                | 是否排序 | 底層實作         | 平均查找     | 最壞查找       |
| --------------------------------- | ---- | ------------ | -------- | ---------- |
| `set` / `map`                     | 有序   | 紅黑樹（RB-tree） | O(log n) | O(log n)   |
| `unordered_set` / `unordered_map` | 無序   | hash table   | O(1)     | O(n)（碰撞嚴重） |

### 注意事項：

* `unordered_map` 不保證元素順序
* Hash 函式與 Load Factor 會影響效能與碰撞率

---

## 四、效能選擇建議表

| 使用情境              | 建議容器                             |
| ----------------- | -------------------------------- |
| 快速查找/加入/刪除        | `unordered_map`, `unordered_set` |
| 順序敏感、需排序          | `vector`, `map`, `set`           |
| 插入/刪除頻繁           | `list`, `forward_list`           |
| 大量 push\_back 並保序 | `vector` + 預先 `reserve()`        |

---

## 五、練習題（Practice）

### 題目一

撰寫程式比較 `std::vector` 與 `std::list` 在尾端插入 1,000,000 個元素所需時間。

### 題目二

用 `unordered_map` 儲存英文單字對應出現次數，並統計一篇文章中 top 5 常見單字。

### 題目三

建立一個 task queue，使用 `list` 管理任務物件，支援中間插入與刪除。

# Chapter 12: 現代 C++ 設計模式實作

本章將以 Modern C++ 為基礎，實作幾個經典設計模式，並展示如何運用 lambda、smart pointer、variant、template 等語法寫出簡潔且安全的結構。

---

## 一、策略模式（Strategy Pattern）

### 傳統做法：使用虛擬類別

```cpp
struct Strategy {
    virtual void execute() = 0;
    virtual ~Strategy() = default;
};

struct StrategyA : Strategy {
    void execute() override { std::cout << "Strategy A\n"; }
};
```

### Modern C++：使用 `std::function`

```cpp
#include <functional>

std::function<void()> strategy;
strategy = [] { std::cout << "Strategy A\n"; };
strategy();
```

---

## 二、觀察者模式（Observer Pattern）

### 使用 `std::function` 與 `vector` 管理訂閱者：

```cpp
class Event {
    std::vector<std::function<void(int)>> subscribers;
public:
    void subscribe(std::function<void(int)> cb) {
        subscribers.push_back(cb);
    }
    void notify(int value) {
        for (auto& cb : subscribers) cb(value);
    }
};
```

---

## 三、狀態模式（State Pattern） + `variant`

### 使用 `std::variant` 搭配狀態類別

```cpp
struct Idle { void handle() { std::cout << "Idle\n"; } };
struct Running { void handle() { std::cout << "Running\n"; } };
using State = std::variant<Idle, Running>;

std::visit([](auto& state) { state.handle(); }, state);
```

---

## 四、工廠模式（Factory Pattern）

### 使用 `std::map<string, function<unique_ptr<Base>()>>`

```cpp
class Base { public: virtual void run() = 0; };
class Derived1 : public Base { public: void run() override { std::cout << "D1\n"; }};

std::map<std::string, std::function<std::unique_ptr<Base>()>> registry;
registry["d1"] = [] { return std::make_unique<Derived1>(); };
```

---

## 五、練習題（Practice）

### 題目一

實作策略模式，根據使用者選擇切換不同數學運算（加減乘除）。

### 題目二

撰寫一個 `Event` 類別，允許多個訂閱者印出事件值。

### 題目三

設計一個角色狀態系統，根據目前狀態印出不同訊息，使用 `std::variant` 表示狀態。

# Chapter 13: 測試與例外處理

本章介紹 Modern C++ 中的錯誤處理機制與基本單元測試觀念，幫助你撰寫更穩定與可驗證的程式。

---

## 一、例外處理（Exception Handling）

### 基本語法：

```cpp
try {
    // 潛在例外的程式碼
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

### 常見標準例外：

* `std::runtime_error`
* `std::invalid_argument`
* `std::out_of_range`

### 自訂例外類別：

```cpp
class MyError : public std::exception {
    const char* what() const noexcept override {
        return "My custom error";
    }
};
```

---

## 二、錯誤處理最佳實務

| 情境     | 建議做法                                       |
| ------ | ------------------------------------------ |
| 非致命錯誤  | 使用 `std::optional`, `std::expected`（C++23） |
| 可恢復錯誤  | 回傳錯誤碼或狀態 enum                              |
| 無法預測錯誤 | 使用 `throw` 與 `try/catch`                   |

---

## 三、斷言與防衛式程式設計

### 使用 `assert`

```cpp
#include <cassert>
assert(x > 0); // 若條件不滿足則中止程式
```

* 僅於 Debug 模式啟用
* 適合檢查邏輯假設、前置條件

---

## 四、單元測試：基本原則與範例

### 手動測試範例：

```cpp
int add(int a, int b) { return a + b; }
void test_add() {
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    std::cout << "test_add passed\n";
}
```

### 使用簡易測試框架（doctest / Catch2）

```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

int add(int a, int b) { return a + b; }

TEST_CASE("addition") {
    CHECK(add(2, 2) == 4);
    CHECK(add(-1, 1) == 0);
}
```

---

## 五、練習題（Practice）

### 題目一

撰寫一個 `divide(int a, int b)` 函數，當 b 為 0 時拋出例外。

### 題目二

設計一個簡單單元測試函數，驗證 `isEven(int)` 是否正確處理奇偶數。


# Chapter 14: Modern C++ 與效能優化實踐

本章介紹 Modern C++ 提供的效能優化工具與思維，協助你寫出高效能、低資源消耗的程式。

---

## 一、Move Semantics（移動語意）

### 差異比較：複製 vs 移動

```cpp
std::vector<int> a = {1, 2, 3};
std::vector<int> b = a;        // 複製（deep copy）
std::vector<int> c = std::move(a); // 移動（no copy, steal resource）
```

* 避免不必要的複製，提升效能
* 移動建構子、移動指派運算子：以 rvalue ref（T&&）實作

---

## 二、`emplace` vs `insert`/`push_back`

* `push_back(obj)`：複製或移動 obj
* `emplace_back(args...)`：原地建構物件

### 範例：

```cpp
std::vector<std::pair<int, std::string>> v;
v.emplace_back(1, "hello"); // 直接建構 pair<int, string>
```

---

## 三、Inline Function 與 Header-only Library

* `inline` 函式建議給小型頻繁呼叫的函式
* Header-only 實作可減少函式呼叫開銷，編譯器可最佳化
* 注意過度 `inline` 可能造成程式碼膨脹（code bloat）

---

## 四、Memory Allocation 與 Cache Awareness

* 頻繁 new/delete 將降低效能，應盡量使用 stack 變數或記憶體池
* `std::vector` 為連續記憶體，可提升 cache 命中率
* 使用 `reserve()` 預留空間可減少 realloc 次數

---

## 五、`constexpr` 與編譯期最佳化

* `constexpr` 函式可於編譯期運算
* 常用於數學運算、預設值、自動生成表格等

### 範例：

```cpp
constexpr int square(int x) { return x * x; }
static_assert(square(5) == 25);
```

---

## 六、練習題（Practice）

### 題目一

比較 `push_back` 與 `emplace_back` 的效能差異，對 10^6 個 string 加入 vector。

### 題目二

實作一個類別，並提供自訂的移動建構子與移動指派運算子，觀察其呼叫行為。

### 題目三

寫一個 `constexpr` 函式計算階乘，並於編譯期驗證結果。

# Chapter 15: Modern C++ 語言功能補遺與進階應用

本章收錄前面章節未完整涵蓋的重要 Modern C++ 技術與進階語法，補齊實務開發常用的語言特性，包括 `std::move`、atomic 操作、mutable 修飾、Concepts、Ranges 擴充用法、左值與右值引用、以及平行標準演算法。

---

## 一、std::move 與右值引用（rvalue reference）

### 語意

* `std::move(x)` 其實是轉型為 `T&&`，並不會真的移動，只是允許呼叫移動建構子。

```cpp
std::string a = "hello";
std::string b = std::move(a); // b 取得資源，a 變成空字串
```

---

## 二、std::atomic 與資料競爭避免

* `std::atomic<T>` 可保證多執行緒對變數操作的原子性
* 常用於簡單的旗標、計數器、lock-free queue

```cpp
std::atomic<int> counter = 0;

std::thread t1([&]() { for (int i = 0; i < 1000; ++i) counter++; });
std::thread t2([&]() { for (int i = 0; i < 1000; ++i) counter++; });
t1.join(); t2.join();
std::cout << counter << std::endl; // 正確為 2000
```

---

## 三、mutable 修飾符

* 用於 `const` 成員函式中允許特定資料成員被修改

```cpp
class Timer {
    mutable int count = 0;
public:
    void tick() const { count++; } // 合法
};
```

---

## 四、Concepts 與型別約束（C++20）

* 取代舊式 `enable_if`，使 template 條件更直觀

```cpp
template<typename T>
concept Integral = std::is_integral_v<T>;

template<Integral T>
T square(T x) { return x * x; }
```

---

## 五、Ranges 擴充應用

```cpp
#include <ranges>
#include <algorithm>

std::vector<int> v = {1, 2, 3, 4, 5};
auto result = v | std::views::filter([](int x){ return x % 2 == 0; })
                | std::views::transform([](int x){ return x * x; });
for (int x : result) std::cout << x << " ";
```

---

## 六、左值、右值引用與傳遞方式理解

| 語法         | 意義               |
| ---------- | ---------------- |
| `T&`       | 左值引用（lvalue ref） |
| `T&&`      | 右值引用（rvalue ref） |
| `const T&` | 接受左值與右值但不可修改     |

### 完美轉發（forwarding）

```cpp
template<typename T>
void wrapper(T&& arg) {
    process(std::forward<T>(arg));
}
```

---

## 七、平行演算法與 std::execution

### 平行 transform（C++17 + execution）

```cpp
#include <execution>
#include <algorithm>
std::vector<int> data = {1,2,3,4,5};
std::vector<int> result(5);

std::transform(std::execution::par, data.begin(), data.end(), result.begin(),
               [](int x){ return x * x; });
```

---

## 練習題（Practice）

### 題目一

撰寫一個 `Timer` 類別，記錄呼叫次數但介面為 `const`，使用 `mutable` 實作。

### 題目二

使用 `concept` 寫一個泛型 `print()` 函式，只允許容器類型印出元素。

### 題目三

使用 `std::execution::par` 對一組大型整數 vector 進行平方轉換，測量與序列版差異。
