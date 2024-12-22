// 定义哈希表的节点结构
// 定义哈希表的节点结构
typedef struct {
    int key;    // 数组值
    int value;  // 数组索引
} HashNode;

typedef struct {
    HashNode* data;   // 存储哈希表节点
    int size;         // 哈希表大小
    int capacity;     // 哈希表容量
} HashTable;

// 创建哈希表
HashTable* createHashTable(int capacity) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->data = (HashNode*)calloc(capacity, sizeof(HashNode));
    table->size = 0;
    table->capacity = capacity;
    return table;
}

// 哈希函数
int hashFunction(int key, int capacity) {
    return (key % capacity + capacity) % capacity;  // 防止负数
}

// 插入到哈希表
void insert(HashTable* table, int key, int value) {
    int hashIndex = hashFunction(key, table->capacity);

    while (table->data[hashIndex].key || table->data[hashIndex].value) { // 避免冲突
        if (table->data[hashIndex].key == key) {
            table->data[hashIndex].value = value;  // 更新索引
            return;
        }
        hashIndex = (hashIndex + 1) % table->capacity;  // 线性探测
    }
    table->data[hashIndex].key = key;
    table->data[hashIndex].value = value;
    table->size++;
}

// 查找哈希表中的值
int find(HashTable* table, int key) {
    int hashIndex = hashFunction(key, table->capacity);

    while (table->data[hashIndex].key || table->data[hashIndex].value) {
        if (table->data[hashIndex].key == key) {
            return table->data[hashIndex].value;
        }
        hashIndex = (hashIndex + 1) % table->capacity;
    }
    return -1;  // 未找到
}

// 两数之和函数
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // 创建哈希表
    HashTable* table = createHashTable(numsSize);

    // 遍历数组并寻找目标值
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int complementIndex = find(table, complement);

        if (complementIndex != -1 && complementIndex != i) {  // 找到结果且不是自己
            int* result = (int*)malloc(2 * sizeof(int));
            result[0] = complementIndex;
            result[1] = i;
            *returnSize = 2;

            // 释放哈希表
            free(table->data);
            free(table);
            return result;
        }
        insert(table, nums[i], i);  // 插入当前值到哈希表
    }

    // 如果没有找到结果，返回空指针
    *returnSize = 0;
    free(table->data);
    free(table);
    return NULL;
}
