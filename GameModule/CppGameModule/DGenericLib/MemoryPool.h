#pragma once
#include <cstddef>
#include <list>

namespace DGeneric
{
    class DMemoryPool {
    private:
        struct Block {
            size_t size;
            bool used;
            Block* next;

            Block(size_t s) : size(s), used(false), next(nullptr) {}
        };

        char* pool;
        Block* blocks;
        const size_t poolSize;

    public:
        DMemoryPool(size_t size) : poolSize(size) {
            pool = new char[poolSize];
            blocks = new Block(poolSize);
            blocks->next = nullptr;
        }

        ~DMemoryPool() {
            delete[] pool;
            while (blocks) {
                Block* temp = blocks;
                blocks = blocks->next;
                delete temp;
            }
        }
        template <typename T>
        T* allocate() {
            size_t size = sizeof(T);
            this->allocate(size);
        }

        void* allocate(size_t size) {
            Block* current = blocks;
            while (current) {
                if (!current->used && current->size >= size) {
                    current->used = true;
                    // 메타데이터 공간 확보
                    char* blockAddr = pool + (current - blocks) * sizeof(Block);
                    return static_cast<void*>(blockAddr);
                }
                current = current->next;
            }
            throw std::bad_alloc();
        }

        void deallocate(void* ptr) {
            size_t index = static_cast<char*>(ptr) - pool;
            Block* block = &blocks[index / sizeof(Block)];
            block->used = false;
        }
    };
}